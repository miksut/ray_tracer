#pragma once

#include "Camera.h"
#include "Scene.h"

#include <memory>
#include <future>
#include <iostream>
#include <random>

namespace cgCourse {
    class RayTracer {
    public:
        RayTracer(int width, int height, std::shared_ptr<Scene> scene);
        virtual std::future<float*> start(const Camera & cam, const unsigned & samples, int startY, int endY) = 0;
        
    protected:
        int width, height;
        std::shared_ptr<Scene> scene;
    };
}
