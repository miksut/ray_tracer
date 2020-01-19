#pragma once

#include "Light.h"
#include "Sphere.h"

namespace cgCourse {
	class DrawablePointLight : public Sphere, public SamplableLight
	{
	public:
		DrawablePointLight(glm::vec3 position, glm::vec3 lightColor) : SamplableLight(position, lightColor), Sphere(glm::vec4(position, 0.1)) {};
		
		virtual std::vector<glm::vec3> getSamplePositions(unsigned amount) override;
	};
}

