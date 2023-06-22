#include "ambientLight.h"
#include "../Materials/material.h"

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

Vec3 AmbientLight::getDirection(const HitMemory & hitmem){
    return Vec3();
}

RGBcolor AmbientLight::L(HitMemory & hitmem){
    return __intensity*ls;
}

double AmbientLight::G(const HitMemory & hitmem){
    return 1;
}

double AmbientLight::pdf(const HitMemory & hitmem){
    return 1;
}