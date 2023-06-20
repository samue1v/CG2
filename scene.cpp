#include "scene.h"
#include "Misc/global.h"
#include "material.h"

Scene::Scene() {}

void Scene::build()
{
    std::shared_ptr<Sampler> hs = std::make_shared<HaltonSampler>(NUM_CHUNKS, NUM_SAMPLES);
    std::shared_ptr<Sampler> pr = std::make_shared<PureRandom>();

    camera.setWidth(SCREEN_W);
    camera.setHeight(SCREEN_H);
    camera.setAspect(4 / 3);
    camera.setFovAngle(90);
    camera.setPosition(Point3(0, 0, 0));
    camera.setDistance(-1);
    camera.setSampler(hs);

    /*
    //teste paulo
    Material material1 ,material2, material3;
    material1.kd = Vec3(0,1,0);
    material1.ke = Vec3(0,1,0);
    material1.ka = Vec3(0,1,0);
    material1.shininess = 10;
    material1.reflectiveIndex = 0;
    material1.transparency = 0.2;
    material1.refractIndex = 1.5;
    material1.type = refractive;

    material2.kd = Vec3(0,0,1);
    material2.ke = Vec3(0,0,1);
    material2.ka = Vec3(0,0,1);
    material2.shininess = 500;
    material2.reflectiveIndex = 0;
    material2.transparency = 0;
    material2.refractIndex = 1.5;
    material2.type = opaque;

    material3.kd = Vec3(1,0,0);
    material3.ke = Vec3(1,0,0);
    material3.ka = Vec3(1,0,0);
    material3.shininess = 1000;
    material3.reflectiveIndex = 0.5;
    material3.transparency = 0;
    material3.refractIndex = 1.5;
    material3.type = opaque;

    auto sphere1 = std::make_shared<Sphere>(Point3(0,0,-3),1);
    sphere1->__material = material1;

    auto sphere2 = std::make_shared<Sphere>(Point3(-1,0,-5),1);
    sphere2->__material = material2;

    auto sphere3 = std::make_shared<Sphere>(Point3(1,0,-5),1);
    sphere3->__material = material3;

    objects.push_back(sphere1);
    objects.push_back(sphere2);
    objects.push_back(sphere3);

    auto plight = std::make_shared<PointLight>(Point3(2,1,0),Vec3(0.6,0.6,0.6));
    auto alight = std::make_shared<AmbientLight>(Vec3(0.2,0.2,0.2));

    lights.push_back(alight);
    lights.push_back(plight);


    */

    // O que eu estava usando!

    Material material1, material2, material3, material4, material5, material6;
    material1.kd = Vec3(0.7, 0, 0);
    material1.ke = Vec3(0.7, 0, 0);
    material1.ka = Vec3(0.2, 0, 0);
    material1.shininess = 400;
    material1.type = refractive;
    material1.transparency = 0.9;
    material1.refractIndex = 1.05;

    material2.kd = Vec3(0, 0, 0.7);
    material2.ke = Vec3(0, 0, 0.7);
    material2.ka = Vec3(0, 0, 0.2);
    material2.shininess = 500;
    material2.type = opaque;
    material2.reflectiveIndex = 0.7;

    material3.kd = Vec3(0, 0.7, 0);
    material3.ka = Vec3(0, 0.9, 0);
    material3.ke = Vec3(0, 0.7, 0);
    material3.shininess = 10;
    material3.type = reflective;
    material3.reflectiveIndex = 0.7;

    material4.kd = Vec3(0.7, 0.7, 0);
    material4.ke = Vec3(0.7, 0.7, 0);
    material4.ka = Vec3(1, 1, 0);
    material4.shininess = 1000;
    material4.type = opaque;
    // material4.reflectiviness = 0.5;

    material5.kd = Vec3(0.7, 0, 0.5);
    material5.ke = Vec3(0.7, 0, 0.5);
    material5.ka = Vec3(1, 0, 1);
    material5.shininess = 500;
    material5.type = opaque;
    material5.reflectiveIndex = 0.6;

    material6.kd = Vec3(0.7, 0.7, 0);
    material6.ke = Vec3(0.7, 0.7, 0);
    material6.ka = Vec3(0.5, 0.5, 0);
    material6.shininess = 500;
    material6.type = opaque;
    material6.reflectiveIndex = 0.6;

    auto plane1 = std::make_shared<Plane>(Point3(1, -1, -30), Vec3(0, 0, 1));
    auto plane2 = std::make_shared<Plane>(Point3(1, -1, -30), Vec3(0, 1, 0));
    plane1->__material = material5;
    plane2->__material = material4;

    auto sphere1 = std::make_shared<Sphere>(Point3(-1, 1, -5), 1);
    auto sphere2 = std::make_shared<Sphere>(Point3(0, 1, -3), 1);
    auto sphere3 = std::make_shared<Sphere>(Point3(0, 0, -12), 1);
    auto sphere4 = std::make_shared<Sphere>(Point3(0, -5001, 0), 5000);
    sphere1->__material = material3;
    sphere2->__material = material1;
    sphere3->__material = material3;
    sphere4->__material = material4;

    auto plight = std::make_shared<PointLight>(Point3(2, 5, 0), Vec3(1, 1, 1));
    auto alight = std::make_shared<AmbientLight>(Vec3(0.3, 0.3, 0.3));

    objects.push_back(sphere1);
    objects.push_back(plane1);
    objects.push_back(plane2);
    objects.push_back(sphere2);
    // objects.push_back(sphere3);

    // objects.push_back(sphere4);
    lights.push_back(plight);
    lights.push_back(alight);
    // std::cout<< material5.type<<std::endl;

    /*
   Material material1 ,material2, material3, material4, material5, material6;
    material1.kd = Vec3(0.7,0,0);
    material1.ke = Vec3(0.7,0,0);
    material1.ka = Vec3(0.2,0,0);
    material1.shininess = 500;
    material1.type = reflective;
    material1.reflectiveIndex = 0.7;
    material1.refractIndex = 1.2;

    material2.kd = Vec3(0,0,0.7);
    material2.ke = Vec3(0,0,0.7);
    material2.ka = Vec3(0,0,0.2);
    material2.shininess = 500;
    material2.type = materialType::reflective;
    material2.reflectiveIndex = 0.7;

    material3.kd = Vec3(0,0.7,0);
    material3.ka = Vec3(0,0.9,0);
    material3.ke = Vec3(0,0.7,0);
    material3.shininess = 10;
    material3.type = reflective;
    material3.transparency = 0.9;
    material3.refractIndex = 1.2;
    material3.reflectiveIndex = 0.7;


    material4.kd = Vec3(0.7,0.7,0);
    material4.ke = Vec3(0.7,0.7,0);
    material4.ka = Vec3(0.2,0.2,0);
    material4.shininess = 1000;
    material4.type = opaque;
    //material4.reflectiviness = 0.5;

    material5.kd = Vec3(0.7,0,0.5);
    material5.ke = Vec3(0.7,0,0.5);
    material5.ka = Vec3(0.2,0,0.5);
    material5.shininess = 500;
    material5.type = reflective;
    material5.reflectiveIndex = 0.6;

    material6.kd = Vec3(0.7,0.7,0);
    material6.ke = Vec3(0.7,0.7,0);
    material6.ka = Vec3(0.2,0.2,0);
    material6.shininess = 500;
    material6.type = reflective;
    material6.reflectiveIndex = 0.6;


    auto plane1 = std::make_shared<Plane>(Point3(1,0,-15),Vec3(0,0,1));
    auto plane2 = std::make_shared<Plane>(Point3(1,-1,-5),Vec3(0,1,0));
    plane1->__material = material5;
    plane2->__material = material5;

    auto sphere1 = std::make_shared<Sphere>(Point3(0,1,-5),1);
    auto sphere2 = std::make_shared<Sphere>(Point3(-2,0,-5),1);
    auto sphere3 = std::make_shared<Sphere>(Point3(2,0,-5),1);
    auto sphere4 = std::make_shared<Sphere>(Point3(0,-5001,0),5000);
    sphere1->__material = material1;
    sphere2->__material = material2;
    sphere3->__material = material3;
    sphere4->__material = material4;




    auto plight = std::make_shared<PointLight>(Point3(2,1,0),Vec3(1,1,1));
    auto alight = std::make_shared<AmbientLight>(Vec3(0.3,0.3,0.3));
    //objects.push_back(plane1);
    objects.push_back(plane2);
    objects.push_back(sphere1);
    objects.push_back(sphere2);
    objects.push_back(sphere3);
    //objects.push_back(sphere4);
    lights.push_back(plight);
    lights.push_back(alight);
    //std::cout<< material5.type<<std::endl;
    */
}

bool Scene::render(std::unique_ptr<uint8_t[]> &data)
{
    Ray ray;
    HitMemory hitdata;
    bool foundSmth;
    int recursionDepth = 3;
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
                foundSmth = castRay(ray, hitdata, recursionDepth);
                if (foundSmth)
                {
                    intensitySum += hitdata.pIntensity;
                }
            }
            intensitySum = intensitySum / double(NUM_SAMPLES);

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
        localTransparency = hitdata.material.transparency;
        localReflect = hitdata.material.reflectiveIndex;
        localIntensity = hitdata.pIntensity;
    }

    if (hitdata.material.type == opaque || depth <= 0)
    {
        return true;
    }

    else if (hitdata.material.type == reflective)
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

bool Scene::fresnel(const Ray &incidentRay, const HitMemory &hitdata, double &kr) const
{
    double i_dot_n = dot(incidentRay.getUnitRay(), hitdata.poiNormal);
    double etaI = 1.0;
    double etaT = hitdata.material.refractIndex;
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
    return true;
}