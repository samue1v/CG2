#include "scene.h"
#include "Misc/global.h"
#include "material.h"

Scene::Scene(){}

void Scene::build(){
    Material material1 ,material2, material3, material4;
    material1.kd = Vec3(0.7,0,0);
    material1.ke = Vec3(0.7,0,0);
    material1.ka = Vec3(0.2,0,0);
    material1.shininess = 500;
    material1.reflectiviness = 0.2;

    material2.kd = Vec3(0,0,0.7);
    material2.ke = Vec3(0,0,0.7);
    material2.ka = Vec3(0,0,0.2);
    material2.shininess = 500;
    material2.reflectiviness = 0.7;

    material3.kd = Vec3(0,0.7,0);
    material3.ka = Vec3(0,0.5,0);
    material3.ke = Vec3(0,0.7,0);
    material3.shininess = 10;
    material3.reflectiviness = 0.4;


    material4.kd = Vec3(0.7,0.7,0);
    material4.ke = Vec3(0.7,0.7,0);
    material4.ka = Vec3(0.2,0.2,0);
    material4.shininess = 1000;
    material4.reflectiviness = 0.5;    
    

    auto sphere1 = std::make_shared<Sphere>(Point3(0,-1,-3),1);
    auto sphere2 = std::make_shared<Sphere>(Point3(-2,1,-3),1);
    auto sphere3 = std::make_shared<Sphere>(Point3(2,1,-3),1);
    auto sphere4 = std::make_shared<Sphere>(Point3(0,-5001,0),5000);
    sphere1->__material = material1;
    sphere2->__material = material2;
    sphere3->__material = material3;
    sphere4->__material = material4;

    auto plight = std::make_shared<PointLight>(Point3(2,1,0),Vec3(1,1,1));
    auto alight = std::make_shared<AmbientLight>(Vec3(0.3,0.3,0.3));
    objects.push_back(sphere1);
    objects.push_back(sphere2);
    objects.push_back(sphere3);
    objects.push_back(sphere4);
    lights.push_back(plight);
    lights.push_back(alight);

}

bool Scene::render(std::unique_ptr<uint8_t[]> & data){
    double wj = 1;
    double hj = 1;
    float canvasDistance = 1;
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

            hitdata.recursion_depth = 3;

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
        hitdata.pIntensity = Vec3(0,0,0);
        return false;
    }


    double localReflect = hitdata.material.reflectiviness;
    if( localReflect <= 0 || hitdata.recursion_depth <= 0){
        return true;
    }
    hitdata.recursion_depth -= 1;
    Vec3 localContrib = hitdata.pIntensity * (1-localReflect);
    Vec3 minusDir = -ray.getRay();
    Vec3 reflectedVec = 2*hitdata.poiNormal*dot(hitdata.poiNormal,minusDir) - minusDir;
    Ray reflectedRay(reflectedVec +hitdata.poi,hitdata.poi);

    bool recursion = castRay(reflectedRay,hitdata);

    hitdata.pIntensity = hitdata.pIntensity*localReflect + localContrib; 


    return true;
}