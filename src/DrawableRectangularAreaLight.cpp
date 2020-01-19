#include "DrawableRectangularAreaLight.h"

#include <vector>

namespace cgCourse {

	DrawableRectangularAreaLight::DrawableRectangularAreaLight(glm::vec3 center, glm::vec3 lightColor, glm::vec3 halfAxisH, glm::vec3 halfAxisV) : SamplableLight(center, lightColor), halfAxisH(halfAxisH), halfAxisV(halfAxisV) {
		
		main[0] = center + halfAxisH + halfAxisV;
		main[1] = center - halfAxisH + halfAxisV;
		main[2] = center - halfAxisH - halfAxisV;
		main[3] = center + halfAxisH - halfAxisV;

		this->positions.assign(main, main + 4);


		this->faces = {
			{ 0, 1, 2 }, { 2, 3, 0 },
		};

		this->primitiveType = triangle;

	}

	std::vector<glm::vec3> DrawableRectangularAreaLight::getSamplePositions(SampleAmount amount) {
		std::vector<glm::vec3> result;

		//always sample mid point
		result.push_back(position);

		glm::vec3 halfH = halfAxisH / 2.0f;
		glm::vec3 halfV = halfAxisV / 2.0f;

		switch (amount) { // fall through to always add the lesser sampleamounts!
		case SampleAmount::High:
			//add 5*5 points (together with medium + low)
			result.push_back(position + halfH);
			result.push_back(position + halfV);
			result.push_back(position - halfH);
			result.push_back(position - halfV);

			result.push_back(position + halfH + halfV);
			result.push_back(position + halfH - halfV);
			result.push_back(position - halfH + halfV);
			result.push_back(position - halfH - halfV);

			result.push_back(position + halfAxisH + halfV);
			result.push_back(position + halfAxisH + halfV);
			result.push_back(position - halfAxisH + halfV);
			result.push_back(position - halfAxisH - halfV);

			result.push_back(position + halfAxisV + halfH);
			result.push_back(position + halfAxisV + halfH);
			result.push_back(position - halfAxisV + halfH);
			result.push_back(position - halfAxisV - halfH);
		case SampleAmount::Medium:
			//add midpoints
			result.push_back(position + halfAxisH);
			result.push_back(position - halfAxisH);
			result.push_back(position + halfAxisV);
			result.push_back(position - halfAxisV);
		case SampleAmount::Low:
		default:
			//just add the 4 vertices
			result.insert(result.end(), positions.begin(), positions.end());
			break;
		}
		return result;
	}
}