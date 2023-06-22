#include "matte.h"
#include "../Tracers/tracer.h"

Matte::Matte() : Material(){}

RGBcolor Matte::shade(HitMemory & hitmem){
    RGBcolor L;

    if (hitmem.depth == 0) {
        L = areaLightShade(hitmem);
    }

    Vec3 wi;
    Vec3 wo = -hitmem.rayDir;
    double pdf;
    RGBcolor f = diffuse_brdf.sample_f(hitmem, wo, wi, pdf);
    double ndotwi = dot(hitmem.poiNormal, wi);
    Ray reflected_ray(wi + hitmem.poi, hitmem.poi + wi*0.01);

    L += f * hitmem.scene->tracer->traceRay(reflected_ray, hitmem.depth + 1) * ndotwi / pdf;

    return L;
}


RGBcolor Matte::areaLightShade(HitMemory & hitmem){
    Vec3 wo = -hitmem.rayDir;
    RGBcolor L; //= ambient_brdf.rho(hitmem, wo) * sr.w.ambient_ptr->L(sr); Caso use iluminação ambiente
    int num_lights = hitmem.scene->lights.size();

    for (int j = 0; j < num_lights; j++) {
        Vec3 wi = hitmem.scene->lights[j]->getDirection(hitmem);
        double ndotwi = dot(hitmem.poiNormal,wi);

        if (ndotwi > 0.0) {
            //bool in_shadow = false;

            /*Used for internal refraction, not useful yet
            if (sr.w.lights[j]->casts_shadows()) {
                Ray shadow_ray(sr.hit_point, wi);
                in_shadow = sr.w.lights[j]->in_shadow(shadow_ray, sr);
            }
            */
           Ray shadow_ray(hitmem.poi, wi);

            if (hitmem.scene->lights[j]->inShadow(shadow_ray, hitmem)) {
                L += diffuse_brdf.f(hitmem, wo, wi) * hitmem.scene->lights[j]->L(hitmem) * hitmem.scene->lights[j]->G(hitmem) * ndotwi / hitmem.scene->lights[j]->pdf(hitmem);
            }
        }
    }

    return L;
}


RGBcolor Matte::getLe(HitMemory & hitmem) const{

}