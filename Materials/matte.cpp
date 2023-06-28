#include "matte.h"
#include "../Tracers/tracer.h"

Matte::Matte() : Material(){}

RGBcolor Matte::shade(HitMemory & hitmem){
    RGBcolor L;
    if (hitmem.depth == 0) {
        L = areaLightShade(hitmem);
    }
    Vec3 wi,wo;
    double pdf;
    //std::cout<<L;
    //std::cout<<"terminei o area shade!\n";
    for(int i = 0;i<10;i++){
        wo = -hitmem.rayDir;

        RGBcolor f = diffuse_brdf.sample_f(hitmem, wo, wi, pdf);
        //std::cout<<"terminei a brdf!\n";
        double ndotwi = dot(hitmem.poiNormal, wi);
        Ray reflected_ray(wi + hitmem.poi, hitmem.poi + wi*0.01);
        //std::cout<<"Antes de chamr traceray\n";
        //->__scene->objects[0]->getNormal(Vec3())<<std::endl;
        //std::cout<<(hitmem.scene == nullptr)<<std::endl;
        //std::cout<<"depois do teste\n";

        //if(L.x()>0 || L.y()>0){std::cout<<L;}
        L += f * hitmem.scene->__tracer->traceRay(reflected_ray, hitmem.depth + 1) * ndotwi / pdf;
    }
    return L/((double)10);
}


RGBcolor Matte::areaLightShade(HitMemory & hitmem){
    Vec3 wo = -hitmem.rayDir;
    RGBcolor L; //= ambient_brdf.rho(hitmem, wo) * sr.w.ambient_ptr->L(sr); Caso use iluminação ambiente
    int num_lights = hitmem.scene->lights.size();

    for (int j = 0; j < num_lights; j++) {
        RGBcolor T;
        for(int i = 0;i<NUM_SAMPLES*30;i++){
            Vec3 wi = hitmem.scene->lights[j]->getDirection(hitmem);
            double ndotwi = dot(hitmem.poiNormal,wi);
            if (ndotwi > 0.0) {
                //std::cout<<ndotwi<<std::endl;
                //bool in_shadow = false;

                /*Used for internal refraction, not useful yet
                if (sr.w.lights[j]->casts_shadows()) {
                    Ray shadow_ray(sr.hit_point, wi);
                    in_shadow = sr.w.lights[j]->in_shadow(shadow_ray, sr);
                }
                */
                Ray shadow_ray(hitmem.poi + wi,hitmem.poi + wi*0.1);
                if (!hitmem.scene->lights[j]->inShadow(shadow_ray, hitmem)) {
                    T += diffuse_brdf.f(hitmem, wo, wi) * hitmem.scene->lights[j]->L(hitmem) * hitmem.scene->lights[j]->G(hitmem) * ndotwi/ hitmem.scene->lights[j]->pdf(hitmem);
                }
            }
        }
        T /= (double)NUM_SAMPLES*30.0;
        L+=T;
    }
    

    return L;
}


RGBcolor Matte::getLe(HitMemory & hitmem) const{
    return RGBcolor();
}