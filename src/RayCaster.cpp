#include "RayCaster.h"


namespace cgCourse {
    std::future<float*> RayCaster::start(const Camera &cam, const unsigned int &samples){
        return std::async(RayCaster::trace, cam, scene, width, height, samples, this->antiAliasing);
    }
    
    float* RayCaster::trace(const Camera &cam, std::shared_ptr<Scene> scene, int width, int height, const unsigned int &samples, int aa){
        float * frame = new float[width * height * 3];
		int n = sqrt(samples);
		float offset = (float) (1 / n) / 2;

		std::random_device rd;
		std::uniform_real_distribution<> dist(-1, 1);
        
        float a = width / (float)height;
        float f = tan(cam.getFieldOfView()/2);

		for (int x = 0 ; x < width ; x++) {
            for (int y = 0; y < height; y++) {
				if (aa == 0) {
					float first = (2 * (x + 0.5)) / width - 1;
					float second = (2 * (y + 0.5)) / height - 1;
					glm::vec3 s = a * f*first*cam.getRightVector() - f * second*cam.getUpVector() + cam.getForwardVector();

					s = glm::normalize(s);

					auto ray = ray_hit(cam.getPosition(), s);

					if (intersect(scene->getRTCScene(), ray)) {

						auto output = scene->shadeLocal(ray, false);
						auto rgb = glm::vec3(glm::clamp(output.x, 0.0f, 1.0f), glm::clamp(output.y, 0.0f, 1.0f), glm::clamp(output.z, 0.0f, 1.0f));

						frame[3 * (y * width + x)] = rgb.r;
						frame[3 * (y * width + x) + 1] = rgb.g;
						frame[3 * (y * width + x) + 2] = rgb.b;
					}
					else {
						frame[3 * (y * width + x)] = 0.0;
						frame[3 * (y * width + x) + 1] = 0.0;
						frame[3 * (y * width + x) + 2] = 0.0;
					}
				} 
				// Jitterd sampling
				else {
					auto rgb = glm::vec3(0.0);

					for (int xx = 0; xx < n; xx++) {
						for (int yy = 0; yy < n; yy++) {
							float first = (2 * (x + (offset + ((1/n)*xx)  + (offset * dist(rd))))) / width - 1;
							float second = (2 * (y + (offset + ((1 / n)*yy) + (offset * dist(rd))))) / height - 1;
							glm::vec3 s = a * f*first*cam.getRightVector() - f * second*cam.getUpVector() + cam.getForwardVector();
							
							s = glm::normalize(s);

							auto ray = ray_hit(cam.getPosition(), s);

							if (intersect(scene->getRTCScene(), ray)) {
								auto output = scene->shadeLocal(ray, false);
								rgb = rgb + output;
							}
							else {
								rgb = rgb + glm::vec3(0.0);
							}
						}
					}
					rgb /= samples;
					rgb = glm::vec3(glm::clamp(rgb.x, 0.0f, 1.0f), glm::clamp(rgb.y, 0.0f, 1.0f), glm::clamp(rgb.z, 0.0f, 1.0f));

					frame[3 * (y * width + x)] = rgb.r;
					frame[3 * (y * width + x) + 1] = rgb.g;
					frame[3 * (y * width + x) + 2] = rgb.b;
				}
            }
        }
        return frame;
    }
    
    bool RayCaster::intersect(RTCScene scene, ray_hit &r){
        RTCIntersectContext context;
        rtcInitIntersectContext(&context);
        rtcIntersect1(scene, &context, &r);
        
        return r.hit.geomID != RTC_INVALID_GEOMETRY_ID;
    }
}
