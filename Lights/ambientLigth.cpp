#include "ambientLight.h"

AmbientLight::AmbientLight(){}

AmbientLight::AmbientLight(Vec3 intensity){
    __intensity = intensity;
}

void AmbientLight::setIntensity(Vec3 intensity){
    __intensity = intensity;
}

Vec3 AmbientLight::getIntensity(){
    return __intensity;
}

bool AmbientLight::computeLightning(HitMemory & hitdata, const Ray & ray, const std::vector<std::shared_ptr<ObjectBase>> & objects){
    hitdata.pIntensity += __intensity*hitdata.material.ka;
    return true;
}