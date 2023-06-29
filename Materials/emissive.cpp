#include "emissive.h"
#include "../Misc/global.h"

Emissive::Emissive() : Material(){}

Emissive::~Emissive(){};

RGBcolor Emissive::shade(HitMemory & hitmem){
    /*
    if (hitmem.depth == 1) {
        return RGBcolor();
    }
    */
    if (dot(-hitmem.poiNormal,hitmem.rayDir) > 0.0 && hitmem.depth == 0) {
        return __ls * __ce;
    } 
    
    return RGBcolor();
}

RGBcolor Emissive::areaLightShade(HitMemory & hitmem){
    if (dot(-hitmem.poiNormal,hitmem.rayDir) > 0.0) {
        return __ls * __ce;
    } else {
        return RGBcolor();
    }
}

RGBcolor Emissive::getLe(HitMemory & hitmem) const{
    return __ls * __ce;
}

