#include "pointLight.h"
#include "../Materials/material.h"
#include "../Objects/objectBase.h"

PointLight::PointLight(){
    __position = Point3(0,0,0);
    __intensity = Vec3(0,0,0);
}

PointLight::PointLight(Point3 position, Vec3 intensity){
    __position = position;
    __intensity = intensity;
}

RGBcolor PointLight::L(HitMemory & hitdata){
    return __intensity*ls;
    /*
    Ray tempRay(__position,hitdata.poi);
    
    if(inShadow(tempRay,hitdata)){
        return RGBcolor();
    }
    
    Vec3 intContrib;
    Vec3 L = tempRay.getUnitRay();
    double n_dot_l = dot(hitdata.poiNormal,L);
    if(n_dot_l>0){
        return __intensity * ls;
    }
    return RGBcolor();
    */
    /*
    if(hitdata.material->shininess > 0){
        
        Vec3 R = (hitdata.poiNormal*2.0*n_dot_l) - L;
        R = unit(R);
        Vec3 V = -ray.getUnitRay();
        double r_dot_v = dot(R,V);
        if(r_dot_v > 0){
            intContrib += (__intensity * hitdata.material->ke * pow(r_dot_v,hitdata.material->shininess));
        }
    }
    */
    
    
    //hitdata.pIntensity += intContrib; 
}


bool PointLight::inShadow(const Ray & ray, const HitMemory & hitdata){
    HitMemory tempHitData;
    double pointsDistance = (__position - hitdata.poi).len();
    tempHitData.closest_t = DOUBLE_INFINITY;
    bool hasIntersection;
    for (auto obj : hitdata.scene->objects){
        hasIntersection = obj->computeIntersection(ray,tempHitData);
        if(hasIntersection){
            double tempPointsDistance = (hitdata.poi - tempHitData.poi).len();
            if(tempPointsDistance < pointsDistance){
                return true;
            }
        }
    }
    return false;
}

Vec3 PointLight::getIntensity(){
    return __intensity;
}



Point3 PointLight::getPosition(){
    return __position;
}



Vec3 PointLight::getDirection(const HitMemory & hitmem){
    return unit(__position - hitmem.poi);
}

double PointLight::G(const HitMemory & hitmem){
    return 1;
}

double PointLight::pdf(const HitMemory & hitmem){
    return 1;
}
