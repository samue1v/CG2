#include "ray.h"

Ray::Ray(){}


Ray::Ray(const Vec3& dest, const Vec3& origin){
    __origin = origin;
    __dest = dest;
    __ray = dest - origin;
    __unitRay = unit(dest - origin);

}

Vec3 Ray::getOrigin() const{
    return __origin;
}

void Ray::setOrigin(Vec3 origin){
    __origin = origin;
}

Vec3 Ray::getDest() const{
    return __dest;
}

void Ray::setDest(Vec3 dest){
    __dest = dest;
}

Vec3 Ray::getRay() const{
    return __ray;
}

void Ray::setRay(Vec3 ray){
    __ray = ray;
}

Vec3 Ray::getUnitRay() const {
    return __unitRay;
}

void Ray::setUnitRay(Vec3 unitRay){
    __unitRay = unitRay;
}