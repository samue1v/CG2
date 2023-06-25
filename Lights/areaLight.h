#include "lightBase.h"
#include "material.h"
class ObjectBase;

class AreaLight : public LightBase{
    public:
    AreaLight();
    AreaLight(std::shared_ptr<ObjectBase> object);
    ~AreaLight();
    void setObject(std::shared_ptr<ObjectBase> object);
    void setMaterial(std::shared_ptr<Material> material);
    bool inShadow(const Ray & ray, const HitMemory & hitmem);
    Vec3 getDirection(const HitMemory & hitmem);
    RGBcolor L(HitMemory & hitmem);
    double G(const HitMemory & hitmem);
    double pdf(const HitMemory & hitmem);
    private:
    std::shared_ptr<ObjectBase> __object;
    std::shared_ptr<Material> __material;
    Vec3 currentSamplePoint;
    Vec3 currentNormal;
    Vec3 currentWi;

};

void inline AreaLight::setObject(std::shared_ptr<ObjectBase> object){
    __object = object;
} 

void inline AreaLight::setMaterial(std::shared_ptr<Material> material){
    __material = material;
}