#include "scene.h"
#include "Misc/global.h"
#include "material.h"

Scene::Scene(){}

void Scene::build(){

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
    int recursionDepth = 1;
    for (int l = 0; l < SCREEN_W; l++) {
        double y = hj / 2 - dy / 2 - l * dy;
        for (int c = 0; c < SCREEN_H; c++) {
            double x = -wj / 2 + dx / 2 + c * dx;
            canvasPoint = Point3(x, y, -canvasDistance);
            Ray ray(canvasPoint,P0);
            ray.setOrigin(canvasPoint);

            foundSmth = castRay(ray, hitdata, recursionDepth); 
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
                data[begin] = uint8_t(0);
                data[begin+1] = uint8_t(0);
                data[begin+2] = uint8_t(0);
            }
            
        }
    }
    return true;
}
    
    
bool Scene::castRay(const Ray & ray, HitMemory & hitdata,int depth){
    hitdata.closest_t = DOUBLE_INFINITY;
    hitdata.pIntensity = Vec3(0,0,0);
    double localTransparency = hitdata.material.transparency;
    bool objIntersect = false;
    bool iterIntersect = false;
    double kr = 1.0;
    double localReflect;
    Vec3 localIntensity,refractedIntensity,reflectedIntensity;
    
    for (auto obj : objects){
        iterIntersect = obj->computeIntersection(ray,hitdata);
        if(iterIntersect){
            objIntersect = true;
        }
    }
    
    if(!objIntersect){
        hitdata.pIntensity = Vec3(0,0,0);
        return false;
    }

    if(objIntersect){
        
        for (auto light : lights){
            light->computeLightning(hitdata,ray,objects);
        }
    }

    localIntensity = hitdata.pIntensity;

    if(hitdata.material.type == opaque || depth <= 0){
        return true;
    }

    else if(hitdata.material.type == reflective){
        
        localReflect = hitdata.material.reflectiveIndex;
        Vec3 minusDir = -ray.getRay();
        Vec3 reflectedVec = 2*hitdata.poiNormal*dot(hitdata.poiNormal,minusDir) - minusDir;
        //std::cout<<reflectedVec<<std::endl;
        Ray reflectedRay(reflectedVec +hitdata.poi,hitdata.poi);
        bool ReflectedRecursion = castRay(reflectedRay,hitdata,--depth);
        reflectedIntensity = hitdata.pIntensity;
        hitdata.pIntensity = hitdata.pIntensity * localReflect + (localIntensity * (1-localReflect));
        return true; 

    }

    

    else{
        //assumindo kr para debugar a recursao
        kr = 0.3;
        //if(fresnel(ray,hitdata.poiNormal,kr)){
            Ray refractedRay;
            ray.refractRay(hitdata,refractedRay);
            bool refractRecursion = castRay(refractedRay,hitdata,--depth);
            refractedIntensity = hitdata.pIntensity;
        //}
        Vec3 minusDir = -ray.getRay();
        Vec3 reflectedVec = 2*hitdata.poiNormal*dot(hitdata.poiNormal,minusDir) - minusDir;
        Ray reflectedRay(reflectedVec +hitdata.poi,hitdata.poi);
        //bool ReflectedRecursion = castRay(reflectedRay,hitdata,--depth);
        //reflectedIntensity = hitdata.pIntensity;
        std::cout<<hitdata.poi<<std::endl;
        hitdata.pIntensity =  localIntensity * localTransparency *  (reflectedIntensity * kr + refractedIntensity * (1.0 - kr));
        return true;
    }

    
    
    /*
    else if(hitdata.material.reflective){
        
    }
    */

    /*
    double localReflect = hitdata.material.reflectiviness;
    if( localReflect <= 0 || hitdata.recursion_depth <= 0){
        return true;
    }
    
    Vec3 localContrib = hitdata.pIntensity * (1-localReflect);
    Vec3 minusDir = -ray.getRay();
    Vec3 reflectedVec = 2*hitdata.poiNormal*dot(hitdata.poiNormal,minusDir) - minusDir;
    Ray reflectedRay(reflectedVec +hitdata.poi,hitdata.poi);

    bool recursion = castRay(reflectedRay,hitdata);
    */
    //hitdata.pIntensity = hitdata.pIntensity*localReflect + localContrib; 


    return true;
}

bool Scene::fresnel(const Ray & incidentRay,const Vec3 & normal,double & kr) const{
    double i_dot_n = dot(incidentRay.getUnitRay(),normal);
    double etaI = 1.0;
    double etaT = incidentRay.getCurrentRefracIndex();
    if(i_dot_n > 0){
        etaI = etaT;
        etaT = 1.0;
    }

    double sinT = etaI/etaT * sqrt(std::max(0.0,1-sinT*sinT));
    if(sinT>1.0){
        kr = 1.0;
        return false;
    }

    double cosT = sqrt(std::max(0.0,1.0 - sinT * sinT));
    double cosI = std::abs(cosT);
    double RS = ((etaT * cosI) - (etaI * cosT)) / ((etaT * cosI) + (etaI * cosT));
    double RP = ((etaI * cosI) - (etaT * cosT)) / ((etaI * cosI) + (etaT * cosT));
    kr =  (RS * RS + RP * RP) / 2.0;
    return true;
}