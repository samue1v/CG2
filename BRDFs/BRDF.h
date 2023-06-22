#ifndef BRDF_H
#define BRDF_H

#include <memory>
#include "../Misc/global.h"
#include "../hitMemory.h"
#include "../DataStructures/vec3.h"
#include "../Samplers/sampler.h"

class BRDF{
    public:
    BRDF();
    BRDF(std::shared_ptr<Sampler> sampler);
    virtual ~BRDF();
    virtual RGBcolor f(const HitMemory & hitmem,const Vec3& wo, const Vec3& wi) const = 0;
    virtual RGBcolor sample_f(const HitMemory & hitmem, const Vec3 & wo, Vec3 & wi) const = 0;
    virtual RGBcolor sample_f(const HitMemory & hitmem, const Vec3 & wo, Vec3 & wi,double & pdf) const = 0;
    virtual RGBcolor rho(const HitMemory& hitmem, const Vec3 & wo) const = 0;
    void setSampler(std::shared_ptr<Sampler> sampler);
    
    protected:
    std::shared_ptr<Sampler> __sampler;


};

#endif