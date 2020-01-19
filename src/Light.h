#pragma once

#include <vector>
#include "glm/common.hpp"

namespace cgCourse {
	class Light {
	public:
		Light(glm::vec3 lightColor) : lightColor(lightColor) {};

		glm::vec3 getLightColor() {
			return lightColor;
		}

	protected:
		glm::vec3 lightColor;
	};

	class SamplableLight : public Light {
	public:
		SamplableLight(glm::vec3 position, glm::vec3 lightColor) : Light(lightColor), position(position) {};

		glm::vec3 getLightPosition() {
			return position;
		}

		virtual std::vector<glm::vec3> getSamplePositions(unsigned amount) = 0;

	protected:
		glm::vec3 position;
	};
}

