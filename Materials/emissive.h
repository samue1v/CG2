#ifndef EMISSEVE_H
#define EMISSIVE_H

#include "material.h"

class Emissive : public Material{
    public:
    Emissive();
    ~Emissive();
    RGBcolor shade(HitMemory & hitmem) override;
    RGBcolor areaLightShade(HitMemory & hitmem) override;
    RGBcolor getLe(HitMemory & hitmem) const override;
    void setce(RGBcolor ce);
    void setls(double ls);
    private:
    RGBcolor __ce;
    double __ls;
};

void inline Emissive::setce(RGBcolor ce){
    __ce = ce;
}

void inline Emissive::setls(double ls){
    __ls = ls;
}

#endif