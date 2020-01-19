#pragma once

#include "DrawableShape.h"
#include "Light.h"

namespace cgCourse {
	class DrawableCircularAreaLight : public DrawableShape, public SamplableLight
	{
	public:
		DrawableCircularAreaLight(glm::vec3 center, glm::vec3 lightColor, float radius);
		
		std::vector<glm::vec3> getSamplePositions(SampleAmount amount) override;
	private:
		float radius;

		void addPointsInCircle(std::vector<glm::vec3>& vec, float radius, int amount);
	};
}

