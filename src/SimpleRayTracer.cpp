#include "SimpleRayTracer.h"

namespace cgCourse {
    std::future<float*> SimpleRayTracer::start(const Camera &cam, const unsigned int &samples){
        return std::async(SimpleRayTracer::trace, cam, scene, width, height, samples);
    }
    
    float* SimpleRayTracer::trace(const Camera &cam, std::shared_ptr<Scene> scene, int width, int height, const unsigned int &samples){
        float * frame = new float[width * height * 3];
        
        float a = width / (float)height;
        float f = tan(cam.getFieldOfView()/2);
        
        for (int x = 0 ; x < width ; x++) {
            for (int y = 0; y < height; y++) {
                float first = (2*(x+0.5))/width - 1;
                float second = (2*(y+0.5))/height - 1;
                glm::vec3 s = a*f*first*cam.getRightVector() - f*second*cam.getUpVector() + cam.getForwardVector();
                
                s = glm::normalize(s);
                
                auto ray = ray_hit(cam.getPosition(), s);
                
                if (intersect(scene->getRTCScene(), ray)) {
                    frame[3 * (y * width + x)] = 1.0;
                    frame[3 * (y * width + x) + 1] = 1.0;
                    frame[3 * (y * width + x) + 2] = 1.0;
                }else{
                    frame[3 * (y * width + x)] = 0.0;
                    frame[3 * (y * width + x) + 1] = 0.0;
                    frame[3 * (y * width + x) + 2] = 0.0;
                }
            }
        }
        
        return frame;
    }
    
    bool SimpleRayTracer::intersect(RTCScene scene, ray_hit &r){
        RTCIntersectContext context;
        rtcInitIntersectContext(&context);
        rtcIntersect1(scene, &context, &r);
        
        return r.hit.geomID != RTC_INVALID_GEOMETRY_ID;
    }
}