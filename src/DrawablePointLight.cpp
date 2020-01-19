#include "DrawablePointLight.h"

namespace cgCourse {


	std::vector<glm::vec3> DrawablePointLight::getSamplePositions(SampleAmount amount) {
		std::vector<glm::vec3> result;
		//point lights always just return their own position when sampled. no need to return more than one.
		result.push_back(getLightPosition());
		return result;
	}
}