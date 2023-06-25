#include "plane.h"

Plane::Plane() : ObjectBase(){
    __planePoint = Vec3(0,0,0);
}

Plane::~Plane(){}

Plane::Plane(Point3 planePoint, Vec3 normal) : ObjectBase(){
    __planePoint = planePoint;
    __normal = normal;
}

bool Plane::computeIntersection(const Ray & ray, HitMemory & hitdata){
    Vec3 p_minuspi = __planePoint - ray.getOrigin();
    Vec3 rayDir = ray.getUnitRay();
    double denom = dot(rayDir,__normal);
    
    if(-denom < 1e-20 ){
      return false;
    }
    double t = dot(p_minuspi,__normal) / denom;
    if(t>=1e-20 && t<=1e20 && hitdata.closest_t > t){
    	Point3 poi  = ray.getOrigin() + rayDir*t;
        hitdata.poi = poi;
        hitdata.closest_t = t;
        hitdata.poiNormal = __normal;
        hitdata.material = __material;
        return true;
    }
    return false;
}

Vec3 Plane::sample() const{
    
}

double Plane::pdf(const HitMemory & hitmem) const{
    return 0.0;
}

Vec3 Plane::getNormal(const Point3 p) const {
    return __normal;
}
