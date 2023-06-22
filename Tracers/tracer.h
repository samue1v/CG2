#ifndef TRACER_H
#define TRACER_H

#include "../ray.h"
#include "../hitMemory.h"
#include "memory"
#include "../DataStructures/vec3.h"

class Scene;

class Tracer{

    public:
    Tracer();
    Tracer(std::shared_ptr<Scene> scene);
    virtual ~Tracer();

    virtual RGBcolor traceRay(const Ray & ray,int depth) = 0;

    //protected:
    std::shared_ptr<Scene> __scene;

};

#endif