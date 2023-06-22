#include "tracer.h"

Tracer::Tracer(){
    __scene = nullptr;
}

Tracer::Tracer(std::shared_ptr<Scene> scene){
    __scene = scene;
}

Tracer::~Tracer(){}