#ifndef WhittedTracer_h
#define WhittedTracer_h

#include "RayTracer.h"

namespace cgCourse {
    class WhittedTracer : public RayTracer {
    public:
		WhittedTracer(int width, int height, std::shared_ptr<Scene> scene, int recursions) : RayTracer(width, height, scene), recursions(recursions) {};
        virtual std::future<float*> start(const Camera & cam, const unsigned & samples);
    private:
        
        static float* trace(const Camera & cam, std::shared_ptr<Scene> scene, int width, int height, const unsigned & samples, int recursions);
        static bool intersect(RTCScene scene, ray_hit & r);

		int recursions;
    };
}

#endif