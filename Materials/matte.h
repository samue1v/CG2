#ifndef MATTE_H
#define MATTE_H

#include "../BRDFs/lambertian.h"
#include "material.h"

class Sampler;

class Matte : public Material{
    public:
    Matte();
    ~Matte() = default;
    RGBcolor shade(HitMemory & hitmem) override;
    RGBcolor areaLightShade(HitMemory & hitmem) override;
    RGBcolor getLe(HitMemory & hitmem) const override;
    void setkd(double kd);
    void setka(double ka);
    void setcd(Vec3 cd);
    void setSampler(std::shared_ptr<Sampler> sampler);
    private:
    Lambertian ambient_brdf;
    Lambertian diffuse_brdf;

};

#endif


void inline Matte::setkd(double kd){
    diffuse_brdf.setkd(kd);
}
void inline Matte::setka(double ka){
    ambient_brdf.setka(ka);
}
void inline Matte::setcd(Vec3 cd){
    diffuse_brdf.setcd(cd);
}

void inline Matte::setSampler(std::shared_ptr<Sampler> sampler){
    diffuse_brdf.setSampler(sampler);
    ambient_brdf.setSampler(sampler);
}