#ifndef PATH_TRACER_H
#define PATH_TRACER_H

#include "tracer.h"

class PathTracer : public Tracer{
    public:
    PathTracer();
    PathTracer(std::shared_ptr<Scene> scene);
    ~PathTracer() = default;

    RGBcolor traceRay(const Ray & ray,int depth) override ;
};

#endif