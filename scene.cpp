#include "scene.h"
#include "Misc/global.h"
#include "material.h"

Scene::Scene(){}

void Scene::build(){
    Material material1 ,material2, material3;
    material1.kd = Vec3(0.7,0,0);
    material1.ke = Vec3(0.7,0,0);
    material1.ka = Vec3(0.2,0,0);


    material2.kd = Vec3(0,0.7,0);
    material2.ka = Vec3(0,0.5,0);
    material2.ke = Vec3(0,0.7,0);

    material3.kd = Vec3(0,0,0.7);
    material3.ke = Vec3(0,0,0.7);
    material3.ka = Vec3(0,0,0.2);
    material1.shininess = 1000;
    material2.shininess = 100;
    material3.shininess = 100;

    auto sphere1 = std::make_shared<Sphere>(Point3(0,0,-40),2);
    auto sphere2 = std::make_shared<Sphere>(Point3(0,0,-120),50);
    auto sphere3 = std::make_shared<Sphere>(Point3(0,0,-25),2);
    sphere1->__material = material1;
    sphere2->__material = material2;
    sphere3->__material = material3;

    auto plight = std::make_shared<PointLight>(Point3(0,0,-30),Vec3(1,1,1));
    auto alight = std::make_shared<AmbientLight>(Vec3(0.3,0.3,0.3));
    objects.push_back(sphere1);
    objects.push_back(sphere2);
    //objects.push_back(sphere3);
    lights.push_back(plight);
    lights.push_back(alight);

}

bool Scene::render(std::unique_ptr<uint8_t[]> & data){
    double wj = 60;
    double hj = 60;
    float canvasDistance = 20;
    float dx = wj / SCREEN_W;
    float dy = hj / SCREEN_H;
    Point3 canvasPoint;
    Vec3 dr;
    Point3 P0(0,0,0);
    HitMemory hitdata;
    bool foundSmth;
    for (int l = 0; l < SCREEN_W; l++) {
        double y = hj / 2 - dy / 2 - l * dy;
        for (int c = 0; c < SCREEN_H; c++) {
            double x = -wj / 2 + dx / 2 + c * dx;
            canvasPoint = Point3(x, y, -canvasDistance);
            Ray ray(canvasPoint,P0);
            ray.setOrigin(canvasPoint);
            foundSmth = castRay(ray, hitdata); 
            int begin = (l*SCREEN_H + c)*3;
            
            if(foundSmth){
                Vec3 intensities = hitdata.pIntensity;
                if(intensities.x() > 1 || intensities.y() > 1 || intensities.z() > 1){
                    intensities = normalize(intensities);
                }
                Vec3 colorRes = Vec3(255.0,255.0,255.0) * intensities;
                data[begin] = uint8_t(colorRes.x());
                data[begin+1] = uint8_t(colorRes.y());
                data[begin+2] = uint8_t(colorRes.z());
            }   
            else{ 
                //std::cout<<"entrei\n";
                data[begin] = uint8_t(0);
                data[begin+1] = uint8_t(0);
                data[begin+2] = uint8_t(0);
            }
            
        }
    }
    return true;
}
    
    
bool Scene::castRay(const Ray & ray, HitMemory & hitdata){
    hitdata.closest_t = DOUBLE_INFINITY;
    hitdata.pIntensity = Vec3(0,0,0);
    bool objIntersect = false;
    bool iterIntersect = false;
    
    for (auto obj : objects){
        iterIntersect = obj->computeIntersection(ray,hitdata);
        if(iterIntersect){
            objIntersect = true;
        }
    }
    
    if(objIntersect){
        
        for (auto light : lights){
            light->computeLightning(hitdata,ray,objects);
        }
    }
    else{
        return false;
    }
    return true;
}