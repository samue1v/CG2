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
    void setcd(Vec3 cd);
    void setkd(double kd);
    void setka(double ka);
    void setSampler(std::shared_ptr<Sampler> sampler);
    private:
    Vec3 __cd;
    double __kd,__ka;
};

void inline Lambertian::setcd(Vec3 cd){
    __cd = cd;
}

void inline Lambertian::setkd(double kd){
    __kd = kd;
}
void inline Lambertian::setka(double ka){
    __ka = ka;
}

void inline Lambertian::setSampler(std::shared_ptr<Sampler> sampler){
    __sampler = sampler;
}


#endif