#ifndef RayCaster_h
#define RayCaster_h

#include <stdio.h>

#include "RayTracer.h"

namespace cgCourse {
    class RayCaster : public RayTracer {
    public:
        RayCaster(int width, int height, std::shared_ptr<Scene> scene) : RayTracer(width, height, scene) {};
        virtual std::future<float*> start(const Camera & cam, const unsigned & samples, int startY, int endY);
    private:
        
        static float* trace(const Camera & cam, std::shared_ptr<Scene> scene, int width, int height, const unsigned & samples, int startY, int endY);
        static bool intersect(RTCScene scene, ray_hit & r);
    };
}

#endif
