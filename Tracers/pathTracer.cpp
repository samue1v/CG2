#include "pathTracer.h"

#include "../Scene/scene.h"
#include "../Materials/material.h"

PathTracer::PathTracer() : Tracer(){}

PathTracer::PathTracer(std::shared_ptr<Scene> scene) : Tracer(scene){
    __scene = scene;
}

RGBcolor PathTracer::traceRay(const Ray & ray, int depth){
    RGBcolor rad;
    HitMemory hitmem;
    //__scene->__tracer = std::make_shared<PathTracer>(*this);
    //std::cout<<(__scene->objects.size()) <<std::endl;
    //exit(-1);
    hitmem.scene = __scene;
    
    //exit(-1);
    //std::cout<<(__scene->objects[0]->getNormal(Vec3())) <<std::endl;
    //exit(-1);
    if(depth>=MAX_DEPTH){
        //std::cout<<"maxima profundidade alcançada\n";
        return RGBcolor();
    }
    //deve apenas procurar por interseções nos objetos
    std::cout<<"raydir no tracer: " <<  ray.getUnitRay();
    if(__scene->objHit(ray,hitmem)){
        //std::cout<<"achei algum objeto\n";
        hitmem.depth = depth;
        hitmem.rayDir = ray.getUnitRay();
        //std::cout<<(__scene->__tracer == nullptr) <<std::endl;
        //exit(-1);
        //std::cout<<"aq\n";
        return hitmem.material->shade(hitmem);//TODO
    }
    //std::cout<<"não achou nada\n";
    return RGBcolor();

}