#ifndef RAY_H
#define RAY_H
#include "DataStructures/vec3.h"

class Ray{
    private:
        Vec3 __origin;
        Vec3 __dest;
        Vec3 __ray;
    public:
        Ray();
        ~Ray() = default;
        Ray(const Vec3 & dest, const Vec3 & origin);
        Vec3 getOrigin () const;
        void setOrigin(Vec3 newDest);
        Vec3 getDest () const;
        void setDest(Vec3 newDest);
        Vec3 getRay() const;
        void setRay(Vec3 newRay);


};



#endif