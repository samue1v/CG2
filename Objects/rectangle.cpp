#include "rectangle.h"

Rectangle::Rectangle() : ObjectBase(){
    __p0 = Vec3();
    __l1 = Vec3();
    __l2 = Vec3();
    __invArea = 0;
}

Rectangle::Rectangle(Vec3 p0,Vec3 l1, Vec3 l2) : ObjectBase(){
    __p0 = p0;
    __l1 = l1;
    __l2 = l2;
    __normal = unit(cross(__l1,__l2));
    __area = __l1.len() * __l2.len();
    __invArea = 1.0/__area;
}

Rectangle::~Rectangle(){}

bool Rectangle::computeIntersection(const Ray & ray, HitMemory & hitmem){
    Vec3 p_minuspi = __p0 - ray.getOrigin();
    Vec3 rayDir = ray.getUnitRay();
    double denom = dot(rayDir,__normal);
    
    if(-denom < 1e-20 ){
      return false;
    }
    double t = dot(p_minuspi,__normal) / denom;

    Point3 poi = ray.getOrigin() + t*ray.getUnitRay();
    Vec3 d = poi - __p0;

    double ddotl1 = dot(d,__l1);
    if(ddotl1 < 0 || ddotl1 > dot(__l1,__l1)){
        return false;
    } 

    double ddotl2 = dot(d,__l2);
    if(ddotl2 < 0 || ddotl2 > dot(__l2,__l2)){
        return false;
    } 
    hitmem.poiNormal = __normal;
    hitmem.poi = poi;
    return true;
}

Vec3 Rectangle::getNormal(const Point3 p) const{
    return __normal;
}

double Rectangle::pdf(const HitMemory & hitmem) const{
    return __invArea;
}

Vec3 Rectangle::sample() const{
    
}



