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
        bool computeLightning(HitMemory & hitdata, const Ray & ray, const std::vector<std::shared_ptr<ObjectBase>> & objects);
        Point3 getPosition();
        void setPosition(Point3 position);
        Vec3 getIntensity();
        void setIntensity(Vec3 intensity);

};

#endif