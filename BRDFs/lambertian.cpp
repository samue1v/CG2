#include "lambertian.h"

Lambertian::Lambertian() : kd(0),cd(Vec3()),BRDF(){}

Lambertian::Lambertian(RGBcolor cd,double kd,std::shared_ptr<Sampler> sampler) : kd(kd),cd(cd),BRDF(sampler){}

RGBcolor Lambertian::f(const HitMemory & hitmem,const Vec3 & wo,const Vec3 & wi) const{
    return kd*cd*INV_PI;
}

RGBcolor Lambertian::sample_f(const HitMemory & hitmem, const Vec3 & wo, Vec3 & wi ) const {
    Vec3 w = hitmem.poiNormal;
    Vec3 v = cross(Vec3(0.0034, 1.0, 0.0071),w);
    v = unit(v);
    Vec3 u = cross(v,w);

    Point3 sp = __sampler->sampleHemisphere();
    wi = sp.x()*u + sp.y()*v + sp.z()*w;
    wi = unit(wi);
    return kd * cd * INV_PI;

}

RGBcolor Lambertian::sample_f(const HitMemory & hitmem, const Vec3 & wo, Vec3 & wi, double & pdf ) const {
    Vec3 w = hitmem.poiNormal;
    Vec3 v = cross(Vec3(0.0034, 1.0, 0.0071),w);
    v = unit(v);
    Vec3 u = cross(v,w);

    Point3 sp = __sampler->sampleHemisphere();
    wi = sp.x()*u + sp.y()*v + sp.z()*w;
    wi = unit(wi);
    pdf = dot(hitmem.poiNormal,wi) * INV_PI;
    return kd * cd * INV_PI;

}

RGBcolor Lambertian::rho(const HitMemory& hitmem, const Vec3 & wo) const{
    return kd*cd;
}