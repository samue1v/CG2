#ifndef HIT_MEM_H
#define HIT_MEM_H

#include "DataStructures/matrix.h"
#include <memory>

class Scene;
class Material;

class HitMemory{
    public:
        HitMemory(){closest_t = DOUBLE_INFINITY;
                    depth = 0;
                    material =nullptr;
                    scene = nullptr;
                    }
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