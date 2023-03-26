#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include <memory>
#include "ray.h"
#include "hitMemory.h"
#include "camera.h"
#include "Objects/sphere.h"
#include "Lights/pointLight.h"
#include "Lights/ambientLight.h"

class Scene{

    private:
        std::vector<std::shared_ptr<ObjectBase>> objects;
        std::vector<std::shared_ptr<LightBase>> lights;
    public:
        Scene();
        ~Scene() = default;
        void build();
        bool render(std::unique_ptr<uint8_t[]> & data );
        bool castRay(const Ray & ray, HitMemory & hitdata);

};

#endif