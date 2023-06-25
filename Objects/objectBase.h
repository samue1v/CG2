#ifndef OBJECT_BASE_H
#define OBJECT_BASE_H

#include "../hitMemory.h"
#include "../ray.h"

class Material;
class Sampler;
class ObjectBase{
    public:
        ObjectBase();
        virtual ~ObjectBase();
        virtual bool computeIntersection(const Ray & ray,HitMemory & hitData) = 0;
        virtual double pdf(const HitMemory & hitmem) const = 0;
        virtual Vec3 getNormal(const Point3 p) const = 0;
        virtual Vec3 sample() const = 0;
        virtual std::shared_ptr<Material> getMaterial();
        virtual std::shared_ptr<Sampler> getSampler();
        virtual void setMaterial(std::shared_ptr<Material> material);
        virtual void setSampler(std::shared_ptr<Sampler> sampler);
    protected:
        std::shared_ptr<Material> __material;
        std::shared_ptr<Sampler> __sampler;
        double __area;
        Vec3 __normal;
        
        
};

void inline ObjectBase::setMaterial(std::shared_ptr<Material> material){
    __material = material;
}

void inline ObjectBase::setSampler(std::shared_ptr<Sampler> sampler){
    __sampler = sampler;
}

#endif