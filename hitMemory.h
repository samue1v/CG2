#ifndef HIT_MEM_H
#define HIT_MEM_H

#include "DataStructures/matrix.h"
#include "material.h"


class HitMemory{
    public:
        double closest_t;
        Point3 poi;
        Vec3 poiNormal;
        Vec3 pIntensity;
        Material material;
};

#endif