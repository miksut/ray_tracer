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
        // every raytracer takes image dimensions, and a scene
        RayTracer(int width, int height, std::shared_ptr<Scene> scene);
        
        // every raytracer needs a method which create a future float* (image)
        // this method takes a camera, amount of AA samples, and a startY and endY integer which tells the raytracer which part of the image it is tracing (startY and endY are y coordinates of the image)
        virtual std::future<float*> start(const Camera & cam, const unsigned & samples, int startY, int endY) = 0;
        
    protected:
        int width, height;
        std::shared_ptr<Scene> scene;
    };
}
