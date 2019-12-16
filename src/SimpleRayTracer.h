#pragma once

#include "RayTracer.h"

#include <stdio.h>
#include <thread>

namespace cgCourse {
    class SimpleRayTracer : public RayTracer {
    public:
        SimpleRayTracer(int width, int height, RTCScene scene) : RayTracer(width, height, scene) {};
        virtual std::future<float*> start(const Camera & cam, const unsigned & samples);
    private:
        
        static float* trace(const Camera & cam, RTCScene scene, int width, int height, const unsigned & samples);
        static bool intersect(RTCScene scene, ray_hit & r);
    };
}
