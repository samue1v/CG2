#include "scene.h"
#include "../Tracers/pathTracer.h"
#include "../Materials/matte.h"
#include "../Materials/emissive.h"
#include "../camera.h"
#include "../Objects/sphere.h"
#include "../Objects/plane.h"
#include "../Objects/rectangle.h"
#include "../Lights/pointLight.h"
#include "../Lights/ambientLight.h"
#include "../Lights/areaLight.h"

void Scene::sceneBuild(){
    //Samplers construction
    std::shared_ptr<Sampler> hs2 = std::make_shared<HaltonSampler>(NUM_CHUNKS, 20,true);
    std::shared_ptr<Sampler> hs = std::make_shared<HaltonSampler>(NUM_CHUNKS, NUM_SAMPLES,false);
    std::shared_ptr<Sampler> pr = std::make_shared<PureRandom>(NUM_CHUNKS, NUM_SAMPLES);
    std::shared_ptr<Sampler> pr2 = std::make_shared<PureRandom>(NUM_CHUNKS, 64);

    //Materials constructor
    std::shared_ptr<Matte> matte1 = std::make_shared<Matte>();
    //matte1->setcd(Vec3(0.41,0.08,0.56));
    matte1->setcd(Vec3(29, 27, 168)/255.0);
    matte1->setkd(1);
    matte1->setSampler(pr);

    std::shared_ptr<Matte> matte2 = std::make_shared<Matte>();
    matte2->setcd(Vec3(1,1,0));
    matte2->setkd(1);
    matte2->setSampler(pr);

    std::shared_ptr<Matte> matte3 = std::make_shared<Matte>();
    matte3->setcd(Vec3(66, 191, 8)/255.0);
    matte3->setkd(1);
    matte3->setSampler(pr);

    std::shared_ptr<Matte> matte4 = std::make_shared<Matte>();
    matte4->setcd(Vec3(214, 6, 6)/255.0);
    matte4->setkd(1);
    matte4->setSampler(pr);


    std::shared_ptr<Matte> matte5 = std::make_shared<Matte>();
    matte5->setcd(Vec3(1,1,1));
    matte5->setkd(1);
    matte5->setSampler(pr);

    std::shared_ptr<Matte> matte6 = std::make_shared<Matte>();
    matte6->setcd(Vec3(1,1,1));
    matte6->setkd(1);
    matte6->setSampler(pr);

    std::shared_ptr<Matte> matte7 = std::make_shared<Matte>();
    matte7->setcd(Vec3(1,1,1));
    matte7->setkd(1);
    matte7->setSampler(pr);

    std::shared_ptr<Emissive> emissionmat = std::make_shared<Emissive>();
    emissionmat->setce(RGBcolor(1,1,1));
    emissionmat->setls(8);

    //rectangle light
    //std::shared_ptr<Rectangle> rect = std::make_shared<Rectangle>(Point3(-0.75,0.5,-1.25),Vec3(0,0,-0.5),Vec3(0.5,0,0));
    //rect->setMaterial(emissionmat);
    //rect->setSampler(hs);

    std::shared_ptr<Rectangle> rect = std::make_shared<Rectangle>(Point3(0.35,0.98,-0.8),Vec3(-0.8,0,0),Vec3(0,0,-0.8));
    rect->setMaterial(emissionmat);
    rect->setSampler(hs2);
    

    std::shared_ptr<AreaLight> rectlight = std::make_shared<AreaLight>();
    rectlight->setMaterial(emissionmat);
    rectlight->setObject(rect);

    lights.push_back(rectlight);


    //Plane definition
    //std::shared_ptr<Plane> plane1 = std::make_shared<Plane>(Vec3(0.3,-1.5,-4),Vec3(0,1,0));
    //plane1->setMaterial(matte1);

    //objects.push_back(plane1);

    //std::shared_ptr<Plane> plane2 = std::make_shared<Plane>(Vec3(0.3,4,-7),Vec3(0,-1,0));
    //plane2->setMaterial(matte2);

    //objects.push_back(rect);
    //objects.push_back(plane2);


    std::shared_ptr<Rectangle> floor = std::make_shared<Rectangle>(Point3(1,-1,-0.7),Vec3(0,0,-2),Vec3(-2,0,0));
    floor->setMaterial(matte1);
    floor->setSampler(pr);

    std::shared_ptr<Rectangle> ceil = std::make_shared<Rectangle>(Point3(-1,1,-0.7),Vec3(0,0,-2),Vec3(2,0,0));
    ceil->setMaterial(matte2);
    ceil->setSampler(pr);

    std::shared_ptr<Rectangle> wallleft = std::make_shared<Rectangle>(Point3(-1,-1,-0.7),Vec3(0,0,-2),Vec3(0,2,0));
    wallleft->setMaterial(matte3);
    wallleft->setSampler(pr);

    std::shared_ptr<Rectangle> wallright = std::make_shared<Rectangle>(Point3(1,-1,-0.7),Vec3(0,2,0),Vec3(0,0,-2));
    wallright->setMaterial(matte4);
    wallright->setSampler(pr);

    std::shared_ptr<Rectangle> wallfront = std::make_shared<Rectangle>(Point3(1,-1,-2.7),Vec3(0,2,0),Vec3(-2,0,0));
    wallfront->setMaterial(matte5);
    wallfront->setSampler(pr);

    std::shared_ptr<Rectangle> wallback = std::make_shared<Rectangle>(Point3(-1,-1,0.3),Vec3(0,2,0),Vec3(2,0,0));
    wallback->setMaterial(matte6);
    wallback->setSampler(pr);

    std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(Point3(0.4,-0.3,-1.6),0.4);
    sphere->setMaterial(matte7);
    sphere->setSampler(pr);



    
    objects.push_back(floor);
    objects.push_back(ceil);
    objects.push_back(wallleft);
    objects.push_back(wallright);
    objects.push_back(wallfront);
    objects.push_back(wallback);
    objects.push_back(rect);
    objects.push_back(sphere);


    
    
    /*
    camera.setWidth(SCREEN_W);
    camera.setHeight(SCREEN_H);
    camera.setAspect(4 / 3);
    camera.setFovAngle(90);
    camera.setPosition(Point3(0, 0, 0));
    camera.setDistance(-1);
    camera.setSampler(pr2);
    */


    camera.setWidth(SCREEN_W);
    camera.setHeight(SCREEN_H);
    camera.setAspect(1);
    camera.setFovAngle(90);
    camera.setPosition(Point3(0, 0, 0));
    camera.setDistance(-1);
    camera.setSampler(hs);

    //Tracer constructor
    __tracer = std::make_shared<PathTracer>();
    __tracer->__scene = std::make_shared<Scene>(*this);


    //std::cout<<(__tracer->__scene->objects[0]->getNormal(Vec3())) <<std::endl;
    //exit(-1);
    //std::cout<<tracer->__scene->objects[0]->getNormal(Vec3())<<std::endl;
    //exit(-1);

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
    /*

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
    */

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