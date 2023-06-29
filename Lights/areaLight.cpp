#include "areaLight.h"
#include "../Objects/objectBase.h"

AreaLight::AreaLight(){
    __object = nullptr;
}

AreaLight::AreaLight(std::shared_ptr<ObjectBase> object){
    __object = object;
}

AreaLight::~AreaLight(){}

bool AreaLight::inShadow(const Ray & ray,const HitMemory & hitmem){
 HitMemory tempHitData;
    double pointsDistance = (currentSamplePoint - hitmem.poi).len();
    tempHitData.closest_t = DOUBLE_INFINITY;
    bool hasIntersection = false;
    for (auto obj : hitmem.scene->objects){
        if(obj == __object){continue;}
        
        hasIntersection = obj->computeIntersection(ray,tempHitData);
        if(hasIntersection){
    
            double tempPointsDistance = (hitmem.poi - tempHitData.poi).len();
            if(tempPointsDistance < pointsDistance){
                //std::cout<<"sombra\n"<<std::endl;
                //exit(-1);
                return true;
            }
        }
    }
    return false;
}

Vec3 AreaLight::getDirection(const HitMemory & hitmem){
    currentSamplePoint = __object->sample();
    currentNormal = __object->getNormal(currentSamplePoint);
    currentWi = unit(currentSamplePoint - hitmem.poi);
    return currentWi;
}

//lembra de fazer
double AreaLight::G(const HitMemory & hitmem){
    double ndotd = dot(currentNormal,-currentWi);
    double distance = (currentSamplePoint - hitmem.poi).len();
    double distanceSquared =  distance * distance;

    return ndotd / distanceSquared;
}

RGBcolor AreaLight::L(HitMemory & hitmem){
    double ndotd = dot(-currentNormal,currentWi);

    if (ndotd > 0.0) {
        return __material->getLe(hitmem);
    } else {
        return RGBcolor();
    }
}

double AreaLight::pdf(const HitMemory & hitmem){
    return __object->pdf(hitmem);
}

double AreaLight::getNumSamples(){
    return __object->getSampler()->getNumSamples();
}