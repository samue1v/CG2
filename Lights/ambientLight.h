#ifndef AMBIENT_LIGHT_H
#define AMBIENT_LIGHT_H

#include "lightBase.h"
#include "../DataStructures/matrix.h"
class AmbientLight : public LightBase{

    public:
        AmbientLight();
        AmbientLight(Vec3 intensity);
        ~AmbientLight() = default;
        bool computeLightning(HitMemory & hitdata, const Ray & ray, const std::vector<std::shared_ptr<ObjectBase>> & objects);
        Vec3 getIntensity();
        void setIntensity(Vec3 intensity);


};

#endif