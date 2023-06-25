#include "objectBase.h"


ObjectBase::ObjectBase(){
    __sampler = nullptr;
    __material = nullptr;
    __area = 0;
    __normal = Vec3();
}

ObjectBase::~ObjectBase(){}

std::shared_ptr<Material> ObjectBase::getMaterial(){
    return __material;
}

std::shared_ptr<Sampler> ObjectBase::getSampler(){
    return __sampler;
}



