#ifndef OBJECT_BASE_H
#define OBJECT_BASE_H
#include "../material.h"
#include "../hitMemory.h"
#include "../ray.h"

class ObjectBase{
    public:
        virtual ~ObjectBase(){}
        virtual bool computeIntersection(const Ray & ray,HitMemory & hitData) = 0;
        Material __material;
    protected:
        
};

#endif