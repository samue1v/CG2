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

double Ray::getCurrentRefracIndex() const{
    return __currentRefracIndex;
}

void Ray::setCurrentRefracIndex(double currentRefracIndex){
    __currentRefracIndex = currentRefracIndex;
}


/*
bool Ray::reflectRay(const HitMemory & hitdata,Ray & reflectedRay) const{
    Vec3 minusDir = -__unitRay;
    Vec3 reflectedVec = unit(2*hitdata.poiNormal*dot(hitdata.poiNormal,minusDir) - minusDir);
    reflectedRay =  Ray(reflectedVec + hitdata.poi,hitdata.poi + reflectedVec*0.01);
    return true;
}

bool Ray::refractRay(const HitMemory & hitdata, Ray & refractedRay) const{
    Vec3 refN = hitdata.poiNormal;
    double etaT = hitdata.material->refractIndex;
    //std::cout<<etaT<<std::endl;
    double etaI = 1.0;
    double i_dot_n = dot(__unitRay,hitdata.poiNormal);
    if(i_dot_n<0){
        i_dot_n = -i_dot_n;
    }
    else{
        refN = hitdata.poiNormal * -1;
        etaT = 1.0;
        etaI = hitdata.material->refractIndex;
    }
    double eta = etaI/etaT;
    double k = 1.0 - (eta*eta) * (1 - i_dot_n * i_dot_n);
    if(k<0){
        return false;
    }
    Vec3 refractVec3Ray =  unit((__unitRay + (i_dot_n * refN)) * eta - refN*sqrt(k));
    refractedRay = Ray(hitdata.poi +refractVec3Ray,hitdata.poi + refractVec3Ray*0.01);
    return true;
}
*/