#include "DrawablePointLight.h"

namespace cgCourse {


	std::vector<glm::vec3> DrawablePointLight::getSamplePositions(unsigned amount) {
		std::vector<glm::vec3> result;
		result.push_back(getLightPosition());
		return result;
	}
}