#include "lambertian.h"

Lambertian::Lambertian() : __kd(0),__cd(Vec3()),__ka(0),BRDF(){}

Lambertian::Lambertian(RGBcolor cd,double kd,std::shared_ptr<Sampler> sampler) : __ka(0),__kd(kd),__cd(cd),BRDF(sampler){}

RGBcolor Lambertian::f(const HitMemory & hitmem,const Vec3 & wo,const Vec3 & wi) const{
    return __kd*__cd*INV_PI;
}

RGBcolor Lambertian::sample_f(const HitMemory & hitmem, const Vec3 & wo, Vec3 & wi ) const {
    Vec3 w = hitmem.poiNormal;
    Vec3 v = cross(Vec3(0.0034, 1.0, 0.0071),w);
    v = unit(v);
    Vec3 u = cross(v,w);

    Point3 sp = __sampler->sampleHemisphere();
    wi = sp.x()*u + sp.y()*v + sp.z()*w;
    wi = unit(wi);
    return __kd * __cd * INV_PI;

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
    return __kd * __cd * INV_PI;

}

RGBcolor Lambertian::rho(const HitMemory& hitmem, const Vec3 & wo) const{
    return __kd*__cd;
}