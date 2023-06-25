#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "lightBase.h"

class PointLight : public LightBase{
    private:
        Point3 __position;
    public:
        PointLight();
        ~PointLight() = default;
        PointLight(Point3 position, Vec3 intensity);
        RGBcolor L(HitMemory & hitdata);
        bool inShadow(const Ray & ray, const HitMemory & hitmem);
        Vec3 getDirection(const HitMemory & hitmem);
        double G(const HitMemory & hitmem);
        double pdf(const HitMemory & hitmem);
        Point3 getPosition();
        void setPosition(Point3 position);
        Vec3 getIntensity();
        void setIntensity(Vec3 intensity);

};
void inline PointLight::setPosition(Point3 position){
    __position = position;
}

void inline PointLight::setIntensity(Vec3 intensity){
    __intensity = intensity;
}
#endif