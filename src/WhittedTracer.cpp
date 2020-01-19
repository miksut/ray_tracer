#include "WhittedTracer.h"

namespace cgCourse {
    std::future<float*> WhittedTracer::start(const Camera &cam, const unsigned int &samples, int startY, int endY){
        return std::async(WhittedTracer::trace, cam, scene, width, height, samples, recursions, startY, endY);
    }
    
    float* WhittedTracer::trace(const Camera &cam, std::shared_ptr<Scene> scene, int width, int height, const unsigned int &samples, int recursions, int startY, int endY){
        float * frame = new float[(endY - startY) * width * 3];
        
        float a = width / (float)height;
        float f = tan(cam.getFieldOfView()/2);
        
        for (int x = 0 ; x < width ; x++) {
            for (int y = startY; y < endY; y++) {
                float first = (2*(x+0.5))/width - 1;
                float second = (2*(y+0.5))/height - 1;
                glm::vec3 s = a*f*first*cam.getRightVector() - f*second*cam.getUpVector() + cam.getForwardVector();
                
                s = glm::normalize(s);
                
                auto ray = ray_hit(cam.getPosition(), s);

                if (intersect(scene->getRTCScene(), ray)) {
                    
					auto output = scene->shadeWhitted(ray, recursions);
					auto rgb = glm::vec3(glm::clamp(output.x, 0.0f, 1.0f), glm::clamp(output.y, 0.0f, 1.0f), glm::clamp(output.z, 0.0f, 1.0f));
                    
                    frame[3 * ((y - startY) * width + x)] = rgb.r;
                    frame[3 * ((y - startY) * width + x) + 1] = rgb.g;
                    frame[3 * ((y - startY) * width + x) + 2] = rgb.b;
                }else{
                    frame[3 * ((y - startY) * width + x)] = 0.0;
                    frame[3 * ((y - startY) * width + x) + 1] = 0.0;
                    frame[3 * ((y - startY) * width + x) + 2] = 0.0;
                }
            }
        }
        
        return frame;
    }
    
    bool WhittedTracer::intersect(RTCScene scene, ray_hit &r){
        RTCIntersectContext context;
        rtcInitIntersectContext(&context);
        rtcIntersect1(scene, &context, &r);
        
        return r.hit.geomID != RTC_INVALID_GEOMETRY_ID;
    }
}
