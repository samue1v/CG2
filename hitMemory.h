#ifndef HIT_MEM_H
#define HIT_MEM_H

#include "DataStructures/matrix.h"
#include <memory>

class Scene;
class Material;

class HitMemory{
    public:
        HitMemory(){}
        double closest_t;
        int depth;
        Point3 poi;
        Vec3 rayDir;
        Vec3 poiNormal;
        Vec3 pIntensity;
        std::shared_ptr<Material> material;
        std::shared_ptr<Scene> scene;
};

#endif