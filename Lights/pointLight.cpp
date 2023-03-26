#include "pointLight.h"

PointLight::PointLight(){
    __position = Point3(0,0,0);
    __intensity = Vec3(0,0,0);
}

PointLight::PointLight(Point3 position, Vec3 intensity){
    __position = position;
    __intensity = intensity;
}

bool PointLight::computeLightning(HitMemory & hitdata, const Ray & ray, const std::vector<std::shared_ptr<ObjectBase>> & objects){
    HitMemory tempHitData;
    Ray tempRay(__position,hitdata.poi);
    double poiLen = (__position - hitdata.poi).len();
    tempHitData.closest_t = DOUBLE_INFINITY;
    bool hasIntersection;
    for (auto obj : objects){
        hasIntersection = obj->computeIntersection(tempRay,tempHitData);
        if(hasIntersection){
            double tempPoilen = (hitdata.poi - tempHitData.poi).len();
            if(tempPoilen < poiLen){
                return false;
            }
        }
    }
    
    Vec3 intContrib;
    
    Vec3 L = tempRay.getUnitRay();
    double n_dot_l = dot(hitdata.poiNormal,L);
    if(n_dot_l>0){
        intContrib += (__intensity * hitdata.material.kd * n_dot_l);
    }
    
    if(hitdata.material.shininess > 0){
        
        Vec3 R = (hitdata.poiNormal*2.0*n_dot_l) - L;
        R = unit(R);
        Vec3 V = -ray.getUnitRay();
        double r_dot_v = dot(R,V);
        if(r_dot_v > 0){
            intContrib += (__intensity * hitdata.material.ke * pow(r_dot_v,hitdata.material.shininess));
        }
    }
    
    
    hitdata.pIntensity += intContrib; 
    return true;
}

Vec3 PointLight::getIntensity(){
    return __intensity;
}

void PointLight::setIntensity(Vec3 intensity){
    __intensity = intensity;
}

Point3 PointLight::getPosition(){
    return __position;
}

void PointLight::setPosition(Point3 position){
    __position = position;
}

