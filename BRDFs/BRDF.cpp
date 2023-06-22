#include "BRDF.h"

BRDF::BRDF(){
    __sampler = nullptr;
}

BRDF::~BRDF(){}

BRDF::BRDF(std::shared_ptr<Sampler> sampler) : __sampler(sampler){}

void BRDF::setSampler(std::shared_ptr<Sampler> sampler){
    __sampler = sampler;
}