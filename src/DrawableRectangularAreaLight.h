#pragma once

#include "Light.h"
#include "DrawableShape.h"

namespace cgCourse {

	class DrawableRectangularAreaLight : public DrawableShape, public SamplableLight
	{
	public:
		DrawableRectangularAreaLight(glm::vec3 center, glm::vec3 lightColor, glm::vec3 halfAxisH, glm::vec3 halfAxisV);

		std::vector<glm::vec3> getSamplePositions(SampleAmount amount) override;
	private:
		glm::vec3 halfAxisH;
		glm::vec3 halfAxisV;

		glm::vec3 main[4];
	};
}

