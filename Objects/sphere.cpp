#include "sphere.h"

Sphere::Sphere(){
    __radius = 1;
    __center = Point3(0,0,0);
}

Sphere::Sphere(Point3 center, double radius){
    __radius = radius;
    __center = center;
}

bool Sphere::computeIntersection(const Ray & ray, HitMemory & hitdata){
    Vec3 oc = ray.getOrigin() - __center;
    Vec3 rayDir = ray.getUnitRay();
    double a = dot(rayDir,rayDir);
    double b = 2 * dot(oc,rayDir);
    double c = dot(oc,oc) - __radius * __radius;

    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
      return false;
    }

    double t1 = (-b + sqrt(discriminant)) / (2.0 * a);
    double t2 = (-b - sqrt(discriminant)) / (2.0 * a);

    double local_t;
    bool t1_cond = (t1>=1e-20 && t1<=1e20);
    bool t2_cond = (t2>=1e-20 && t2<=1e20);

    if(!(t1_cond || t2_cond)) {
        return false;
    } 
    else if (!t1_cond) {
        local_t = t2;
    } 
    else if (!t2_cond) {
        local_t = t1;
    } 
    else {
        t1<t2 ? local_t = t1 : local_t = t2;
    }

    if(local_t < hitdata.closest_t){
        Point3 poi = ray.getOrigin() + rayDir*local_t;
        hitdata.poi = poi;
        hitdata.closest_t = local_t;
        hitdata.poiNormal = unit(poi - __center);
        hitdata.material = __material;
    }
    return true;
}