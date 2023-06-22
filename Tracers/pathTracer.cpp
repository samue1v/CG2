#include "pathTracer.h"

#include "../Scene/scene.h"
#include "../Materials/material.h"

PathTracer::PathTracer() : Tracer(){}

PathTracer::PathTracer(std::shared_ptr<Scene> scene) : Tracer(scene){}

RGBcolor PathTracer::traceRay(const Ray & ray, int depth){
    RGBcolor rad;
    HitMemory hitmem;
    if(depth>MAX_DEPTH){
        return RGBcolor();
    }
    //deve apenas procurar por interseções nos objetos
    if(__scene->objHit(ray,hitmem)){
        hitmem.depth = depth;
        hitmem.rayDir = ray.getUnitRay();
        return hitmem.material->shade(hitmem);//TODO
    }
    return RGBcolor();

}