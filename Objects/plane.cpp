#include "plane.h"

Plane::Plane() : ObjectBase(){
    __planePoint = Vec3(0,0,0);
}

Plane::~Plane(){}

Plane::Plane(Point3 planePoint, Vec3 normal) : ObjectBase(){
    __planePoint = planePoint;
    __normal = unit(normal);
}

bool Plane::computeIntersection(const Ray & ray, HitMemory & hitdata){
    Vec3 p_minuspi = __planePoint - ray.getOrigin();
    Vec3 rayDir = ray.getUnitRay();
    std::cout<<"raydir no plano: "<<rayDir;
    //std::cout<<rayDir;
    //Vec3 minusraydir = -rayDir;
    double denom = dot(rayDir,__normal);
    //std::cout<<denom<<std::endl;
    
    if((-denom) < 1e-10){
      return false;
    }
    double t = dot(p_minuspi,__normal) / denom;
    if(hitdata.closest_t < t){
        std::cout<<"dada!\n";
        exit(-1);
    }
    if(t>=1e-20 && t<=1e20 && hitdata.closest_t > t){
    	Point3 poi  = ray.getOrigin() + rayDir*t;
        hitdata.poi = poi;
        hitdata.closest_t = t;
        hitdata.poiNormal = __normal;
        hitdata.material = __material;
        //std::cout<<"com intersecção\n";
        return true;
    }
     //std::cout<<"sem intersecção\n";
    return false;
}

Vec3 Plane::sample() const{
    return Vec3();
}

double Plane::pdf(const HitMemory & hitmem) const{
    return 1.0;
}

Vec3 Plane::getNormal(const Point3 p) const {
    return __normal;
}
