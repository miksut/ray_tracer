#include "SimpleRayTracer.h"

namespace cgCourse {
    std::future<float*> SimpleRayTracer::start(const Camera &cam, const unsigned int &samples){
        return std::async(SimpleRayTracer::trace, cam, scene, width, height, samples);
    }
    
    float* SimpleRayTracer::trace(const Camera &cam, RTCScene scene, int width, int height, const unsigned int &samples){
        float * frame = new float[width * height];
        
        std::cout << "Working Threads!" << std::endl;
        return frame;
    }
    
    bool SimpleRayTracer::intersect(RTCScene scene, ray_hit &r){
        RTCIntersectContext context;
        rtcInitIntersectContext(&context);
        rtcIntersect1(scene, &context, &r);
        
        return r.hit.geomID != RTC_INVALID_GEOMETRY_ID;
    }
}
