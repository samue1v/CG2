#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "BRDF.h"

class Lambertian : public BRDF{
    public:
    Lambertian();
    Lambertian(RGBcolor cd,double kd,std::shared_ptr<Sampler> sampler);
    RGBcolor f(const HitMemory & hitmem,const Vec3 & wo,const Vec3 & wi) const override;
    RGBcolor sample_f(const HitMemory & hitmem, const Vec3 & wo, Vec3 & wi) const override;
    RGBcolor sample_f(const HitMemory & hitmem, const Vec3 & wo, Vec3 & wi,double & pdf) const override;
    RGBcolor rho(const HitMemory& hitmem, const Vec3 & wo) const override; 
    protected:
    Vec3 cd;
    double kd;
};


#endif