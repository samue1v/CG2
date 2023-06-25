#ifndef AMBIENT_LIGHT_H
#define AMBIENT_LIGHT_H

#include "lightBase.h"
#include "../DataStructures/matrix.h"
class AmbientLight : public LightBase{

    public:
        AmbientLight();
        AmbientLight(Vec3 intensity);
        ~AmbientLight() = default;
        Vec3 getIntensity();
        void setIntensity(Vec3 intensity);
        Vec3 getDirection(const HitMemory & hitmem);
        double G(const HitMemory & hitmem);
        double pdf(const HitMemory & hitmem);
        RGBcolor L(HitMemory & hitmem);
        bool inShadow(const Ray & ray, const HitMemory & hitmem);


};

void inline AmbientLight::setIntensity(Vec3 intensity){
    __intensity = intensity;
}

#endif