#pragma once

#include "Camera.h"
#include "embree.h"

#include <future>
#include <iostream>

namespace cgCourse {
    class RayTracer {
    public:
        RayTracer(int width, int height, RTCScene scene);
        virtual std::future<float*> start(const Camera & cam, const unsigned & samples) = 0;
        
    protected:
        int width, height;
        RTCScene scene;
        
    };
}
