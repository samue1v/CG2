#ifndef MATTE_H
#define MATTE_H

#include "../BRDFs/lambertian.h"
#include "material.h"

class Matte : public Material{
    public:
    Matte();
    ~Matte() = default;
    RGBcolor shade(HitMemory & hitmem) override;
    RGBcolor areaLightShade(HitMemory & hitmem) override;
    RGBcolor getLe(HitMemory & hitmem) const override;
    private:
    Lambertian ambient_brdf;
    Lambertian diffuse_brdf;

};

#endif



