#include "DrawableCircularAreaLight.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace cgCourse {
	DrawableCircularAreaLight::DrawableCircularAreaLight(glm::vec3 center, glm::vec3 lightColor, float radius) : SamplableLight(center, lightColor), radius(radius) {
		
        // add center vertex
		positions.push_back(position);
        
        // create circular disc with 32 subdivision
		int subdiv = 32;
        
        // vertices
		for (int i = 0; i < subdiv; i++) {
			float ratio = i / (float) subdiv;

			float r = ratio * M_PI * 2;
			float x = cosf(r) * radius;
			float z = sinf(r) * radius;

			positions.push_back(position + glm::vec3(x, 0, z));

		}
		
		for (int i = 0; i < subdiv - 1; i++) {
			faces.push_back(glm::vec3(0, i + 1, i + 2));
		}
        
        // faces
		faces.push_back(glm::vec3(0, 32, 1));

		this->primitiveType = triangle;
	}

	std::vector<glm::vec3> DrawableCircularAreaLight::getSamplePositions(SampleAmount amount) {
		std::vector<glm::vec3> result;

		//always sample mid point
		result.push_back(position);

		switch (amount) {
		case SampleAmount::High:
            // add points along different radii
			addPointsInCircle(result, radius, 16);
			addPointsInCircle(result, radius * 0.75, 8);
			addPointsInCircle(result, radius * 0.5, 4);
			addPointsInCircle(result, radius * 0.25, 2);
			break;
		case SampleAmount::Medium:
            // add points along different radii
			addPointsInCircle(result, radius, 8);
			addPointsInCircle(result, radius * 0.5, 4);
			break;
		case SampleAmount::Low:
		default:
			// 5 points along circle
			addPointsInCircle(result, radius, 5);
			break;
		}
		return result;
	}

	void DrawableCircularAreaLight::addPointsInCircle(std::vector<glm::vec3>& vec, float radius, int amount) {
        
        // sample points along circle with radius radius
		for (int i = 0; i < amount; i++) {
			float ratio = i / (float)amount;

			float r = ratio * M_PI * 2;
			float x = cosf(r) * radius;
			float z = sinf(r) * radius;

			vec.push_back(position + glm::vec3(x, 0, z));
		}
	}
}
