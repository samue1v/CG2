#ifndef RAY_H
#define RAY_H
#include "DataStructures/vec3.h"
#include "hitMemory.h"

class Ray{
    private:
        Vec3 __origin;
        Vec3 __dest;
        Vec3 __ray;
        Vec3 __unitRay;
        double __currentRefracIndex;
    public:
        Ray();
        ~Ray() = default;
        Ray(const Vec3 & dest, const Vec3 & origin);
        bool refractRay(const HitMemory & hitdata, Ray & refractedRay) const;
        bool reflectRay(const HitMemory & hitdata, Ray & reflectedRay) const;
        Vec3 getOrigin () const;
        void setOrigin(Vec3 origin);
        Vec3 getDest () const;
        void setDest(Vec3 dest);
        Vec3 getRay() const;
        void setRay(Vec3 ray);
        Vec3 getUnitRay() const;
        void setUnitRay(Vec3 unitRay);
        double getCurrentRefracIndex() const;
        void setCurrentRefracIndex(double index);


};



#endif