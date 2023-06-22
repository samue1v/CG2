#ifndef LIGHT_BASE_H
#define LIGHT_BASE_H

#include "../DataStructures/vec3.h"
#include <memory>
#include <vector>
#include "../hitMemory.h"
#include "../ray.h"

class LightBase{
    protected:
        Vec3 __intensity;
        double ls;
    public:
        virtual bool inShadow(const Ray & ray, const HitMemory & hitmem) = 0;
        virtual Vec3 getDirection(const HitMemory & hitmem) = 0;
        virtual RGBcolor L(HitMemory & hitmem) = 0;
        virtual double G(const HitMemory & hitmem) = 0;
        virtual double pdf(const HitMemory & hitmem) = 0;
        virtual ~LightBase() = default;
};

#endif