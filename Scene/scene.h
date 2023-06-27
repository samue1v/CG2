#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include <memory>
#include <iomanip>
#include "../ray.h"
#include "../hitMemory.h"
#include "../camera.h"
#include "../Objects/objectBase.h"
#include "../Lights/lightBase.h"


class Tracer;

class Scene{

    public:
        std::vector<std::shared_ptr<ObjectBase>> objects;
        std::vector<std::shared_ptr<LightBase>> lights;
        std::shared_ptr<Tracer> __tracer;
        Camera camera;
        
        
    public:
        Scene();
        ~Scene() = default;
        bool render(std::unique_ptr<uint8_t[]> & data );
        bool objHit(const Ray & ray, HitMemory & hitdata);
        bool fresnel(const Ray & incidentRay,const HitMemory & hitdata,double & kr) const;
        void sceneBuild();
};

#endif