#include "BaseTracer.h"

namespace cgCourse {
    std::future<float*> BaseTracer::start(const Camera &cam, const unsigned int &samples, int startY, int endY){
        return std::async(BaseTracer::trace, cam, scene, width, height, samples, recursions, this->antiAliasing, this->whitted, startY, endY);
    }
    
    float* BaseTracer::trace(const Camera &cam, std::shared_ptr<Scene> scene, int width, int height, const unsigned int &samples, int recursions, bool aa, bool whitted, int startY, int endY){
        
        // final image
        float * frame = new float[(endY - startY) * width * 3];
        
        // number of subpixels in each dimension (width or height)
        float n = sqrt(samples);
        
        // offset for each subpixel to reach center of it
		float offset = (1 / n) / 2.0f;
        
		std::random_device rd;
		std::uniform_real_distribution<> dist(-1, 1);
        
        // a and f from the slides
        float a = width / (float)height;
        float f = tan(cam.getFieldOfView()/2);
        
        // loop through relevan image pixels
		for (int x = 0; x < width; x++) {
			for (int y = startY; y < endY; y++) {
                // if not antiAliasing
				if (aa == 0) {
                    // first and second parenthesis in slides
					float first = (2 * (x + 0.5)) / width - 1;
					float second = (2 * (y + 0.5)) / height - 1;
                    
                    // s according to slides
					glm::vec3 s = a * f*first*cam.getRightVector() - f * second*cam.getUpVector() + cam.getForwardVector();

					s = glm::normalize(s);
                    
					auto ray = ray_hit(cam.getPosition(), s);

					if (intersect(scene->getRTCScene(), ray)) {
                        auto output = glm::vec3(0);
                        
                        if (whitted){
                            output = scene->shadeWhitted(ray, recursions);
                        } else {
                            output = scene->shadeLocal(ray, false);
                        }
                        
                        // clamp color values between 0 and 1
						auto rgb = glm::vec3(glm::clamp(output.x, 0.0f, 1.0f), glm::clamp(output.y, 0.0f, 1.0f), glm::clamp(output.z, 0.0f, 1.0f));
                        
                        // set colors of final image
						frame[3 * ((y - startY) * width + x)] = rgb.r;
						frame[3 * ((y - startY) * width + x) + 1] = rgb.g;
						frame[3 * ((y - startY) * width + x) + 2] = rgb.b;
					}
					else {
                        // set colors of final image (if not hit anything)
						frame[3 * ((y - startY) * width + x)] = 0.0;
						frame[3 * ((y - startY) * width + x) + 1] = 0.0;
						frame[3 * ((y - startY) * width + x) + 2] = 0.0;
					}
				}
				// Jittered sampling
				else {
					auto rgb = glm::vec3(0.0);
                    
                    // go through subpixels
					for (int xx = 0; xx < n; xx++) {
						for (int yy = 0; yy < n; yy++) {
                            
                            // first and second parentheses with jittering in sub pixels
                            float first = (2 * (x + (offset + ((1 / n)*xx) + (offset * dist(rd))))) / width - 1;
                            float second = (2 * (y + (offset + ((1 / n)*yy) + (offset * dist(rd))))) / height - 1;
                            
                            // s according to slides
                            glm::vec3 s = a * f*first*cam.getRightVector() - f * second*cam.getUpVector() + cam.getForwardVector();

							s = glm::normalize(s);

							auto ray = ray_hit(cam.getPosition(), s);

							if (intersect(scene->getRTCScene(), ray)) {
                                auto output = glm::vec3(0);
                                if (whitted){
                                    output = scene->shadeWhitted(ray, recursions);
                                } else {
                                    output = scene->shadeLocal(ray, false);
                                }
                                
                                // clamp color values between 0 and 1
                                output = glm::vec3(glm::clamp(output.x, 0.0f, 1.0f), glm::clamp(output.y, 0.0f, 1.0f), glm::clamp(output.z, 0.0f, 1.0f));
								rgb = rgb + output;
							}
							else {
                                // set color to 0 if nothing hit
								rgb = rgb + glm::vec3(0.0);
							}
						}
					}
                    // divide through number of samples to get average color of all sub pixel rays
					rgb /= samples;
                    
                    // set final color of anti aliasied image
					frame[3 * ((y - startY) * width + x)] = rgb.r;
					frame[3 * ((y - startY) * width + x) + 1] = rgb.g;
					frame[3 * ((y - startY) * width + x) + 2] = rgb.b;
				}
			}
		}
        return frame;
    }
    
    bool BaseTracer::intersect(RTCScene scene, ray_hit &r){
        RTCIntersectContext context;
        rtcInitIntersectContext(&context);
        rtcIntersect1(scene, &context, &r);
        
        return r.hit.geomID != RTC_INVALID_GEOMETRY_ID;
    }
}
