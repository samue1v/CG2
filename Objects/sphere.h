#ifndef SPHERE_H
#define SPHERE_H
#include "objectBase.h"

class Sphere : public ObjectBase{
    private:
        double __radius;
        Point3 __center;
    
    public:
        Sphere();
        ~Sphere() = default;
        Sphere(Point3 center, double radius);
        bool computeIntersection(const Ray & ray, HitMemory & hitData) override;
        double pdf(const HitMemory & hitmem) const override;
        Vec3 getNormal(const Point3 p) const override;


};

#endif