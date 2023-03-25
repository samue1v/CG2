#include "ray.h"

Ray::Ray(){}

Ray::Ray(const Vec3& dest, const Vec3& origin){
    __origin = origin;
    __dest = dest;
    __ray = unit(dest - origin);

}

Vec3 Ray::getOrigin() const{
    return __origin;
}

void Ray::setOrigin(Vec3 newOrigin){
    __origin = newOrigin;
}

Vec3 Ray::getDest() const{
    return __dest;
}

void Ray::setDest(Vec3 newDest){
    __dest = newDest;
}

Vec3 Ray::getRay() const{
    return __ray;
}

void Ray::setRay(Vec3 newRay){
    __ray = newRay;
}