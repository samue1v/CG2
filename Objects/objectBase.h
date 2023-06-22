#ifndef OBJECT_BASE_H
#define OBJECT_BASE_H

#include "../hitMemory.h"
#include "../ray.h"

class Material;

class ObjectBase{
    public:
        virtual ~ObjectBase(){}
        virtual bool computeIntersection(const Ray & ray,HitMemory & hitData) = 0;
        std::shared_ptr<Material> __material;
    protected:
        
};

#endif