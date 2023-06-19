#ifndef LIGHT_BASE_H
#define LIGHT_BASE_H

#include "../DataStructures/vec3.h"
#include <memory>
#include <vector>
#include "../hitMemory.h"
#include "../Objects/objectBase.h"

class LightBase{
    protected:
        Vec3 __intensity;
    public:
        virtual bool computeLightning(HitMemory & hitData, const Ray & ray,  const std::vector<std::shared_ptr<ObjectBase>> & objects) = 0;
        virtual ~LightBase(){}
};

#endif