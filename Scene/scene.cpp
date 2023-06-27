#include "scene.h"
#include "../Misc/global.h"
#include "../Tracers/tracer.h"

Scene::Scene() {}


bool Scene::render(std::unique_ptr<uint8_t[]> &data)
{
    Ray ray;
    //HitMemory hitdata;
    //bool foundSmth;
    //int MAX_DEPTH = 3;
    std::cout << "Start.\n";
    std::cout << std::fixed;
    std::cout << std::setprecision(3);
    for (int c = 0; c < SCREEN_H; c++)
    {
        for (int l = 0; l < SCREEN_W; l++)
        {

            Vec3 intensitySum;
            int begin = (c * SCREEN_W + l) * 3;
            for (int s = 0; s < NUM_SAMPLES; s++)
            {
                camera.generateRay(l, c, ray); // randomize here
                //foundSmth = true;//castRay(ray, hitdata, MAX_DEPTH);
                //if (foundSmth)
                //{
                intensitySum += __tracer->traceRay(ray,0);
                //}
            }
            intensitySum = intensitySum / double(NUM_SAMPLES);
            //if(intensitySum.x() == 0 && intensitySum.y() == 0 && intensitySum.z() == 0){std::cout<<"sdjmklad\n";exit(-1);}

            if (intensitySum.x() > 1 || intensitySum.y() > 1 || intensitySum.z() > 1)
            {
                intensitySum = normalize(intensitySum);
            }

            Vec3 colorRes = Vec3(255.0, 255.0, 255.0) * intensitySum;
            // std::cout<< "line: "<< l << " column: " << c << " intensity: " << colorRes <<std::endl;
            data[begin] = uint8_t(colorRes.x());
            data[begin + 1] = uint8_t(colorRes.y());
            data[begin + 2] = uint8_t(colorRes.z());
        }
    }
    std::cout << "end" << std::endl;
    return true;
}

bool Scene::objHit(const Ray &ray, HitMemory &hitdata)
{
    hitdata.closest_t = DOUBLE_INFINITY;
    hitdata.pIntensity = Vec3(0, 0, 0);
    bool objIntersect = false;

    //std::cout<<objects.size()<<std::endl;]

    for (auto obj : objects)
    {
        
        if (obj->computeIntersection(ray, hitdata))
        {
            objIntersect = true;
        }
    }
    return objIntersect;
}


/*
bool Scene::castRay(const Ray &ray, HitMemory &hitdata, int depth)
{
    
    hitdata.closest_t = DOUBLE_INFINITY;
    hitdata.pIntensity = Vec3(0, 0, 0);
    double localTransparency;
    bool objIntersect = false;
    bool iterIntersect = false;
    double kr;
    double localReflect;
    Vec3 localIntensity, refractedIntensity, reflectedIntensity;

    for (auto obj : objects)
    {
        iterIntersect = obj->computeIntersection(ray, hitdata);
        if (iterIntersect)
        {
            objIntersect = true;
        }
    }

    if (!objIntersect)
    {
        hitdata.pIntensity = Vec3(0, 0, 0);
        return false;
    }

    if (objIntersect)
    {

        for (auto light : lights)
        {
            light->computeLightning(hitdata, ray, objects);
        }
        localTransparency = hitdata.material->transparency;
        localReflect = hitdata.material->reflectiveIndex;
        localIntensity = hitdata.pIntensity;
    }

    if (hitdata.material->type == opaque || depth <= 0)
    {
        return true;
    }

    else if (hitdata.material->type == reflective)
    {
        Ray reflectedRay;
        ray.reflectRay(hitdata, reflectedRay);
        bool ReflectedRecursion = castRay(reflectedRay, hitdata, depth - 1);
        reflectedIntensity = hitdata.pIntensity;
        hitdata.pIntensity = hitdata.pIntensity * localReflect + (localIntensity * (1 - localReflect));
        return true;
    }

    else
    {
        Ray reflectedRay;
        Ray refractedRay;
        if (fresnel(ray, hitdata, kr))
        {

            ray.refractRay(hitdata, refractedRay);
            ray.reflectRay(hitdata, reflectedRay);
            bool refractRecursion = castRay(refractedRay, hitdata, depth - 1);
            refractedIntensity = hitdata.pIntensity;
            bool reflectRecursion = castRay(reflectedRay, hitdata, depth - 1);
            reflectedIntensity = hitdata.pIntensity;
        }
        else
        {

            ray.reflectRay(hitdata, reflectedRay);
            bool ReflectedRecursion = castRay(reflectedRay, hitdata, depth - 1);
            reflectedIntensity = hitdata.pIntensity;
        }
        // std::cout<<hitdata.poi<<std::endl;
        // hitdata.pIntensity = hitdata.pIntensity *0.3;
        hitdata.pIntensity = refractedIntensity * (1 - kr) + reflectedIntensity * kr; // (reflectedIntensity * kr + refractedIntensity * (1.0 - kr));
        // hitdata.pIntensity = hitdata.pIntensity * localTransparency * localIntensity;
        hitdata.pIntensity += localTransparency * localIntensity;
        return true;
    }
    
    return true;
}
*/

bool Scene::fresnel(const Ray &incidentRay, const HitMemory &hitdata, double &kr) const
{
    /*
    double i_dot_n = dot(incidentRay.getUnitRay(), hitdata.poiNormal);
    double etaI = 1.0;
    double etaT = hitdata.material->refractIndex;
    if (i_dot_n > 0)
    {
        etaI = etaT;
        etaT = 1.0;
    }

    double sinT = etaI / etaT * sqrt(std::max(0.0, 1 - i_dot_n * i_dot_n));
    if (sinT > 1.0)
    {
        kr = 1.0;
        return false;
    }

    double cosT = sqrt(std::max(0.0, 1.0 - sinT * sinT));
    double cosI = std::abs(cosT);
    double RS = ((etaT * cosI) - (etaI * cosT)) / ((etaT * cosI) + (etaI * cosT));
    double RP = ((etaI * cosI) - (etaT * cosT)) / ((etaI * cosI) + (etaT * cosT));
    kr = (RS * RS + RP * RP) / 2.0;
    */
    return true;
}