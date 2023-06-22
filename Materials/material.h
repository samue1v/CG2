#ifndef MATERIAL_H
#define MATERIAL_H

#include <vector>
#include "../DataStructures/vec3.h"
#include "../hitMemory.h"
#include "../Scene/scene.h"

enum materialType{
    opaque,
    reflective,
    refractive
};

class Material{
    public:

    Material();
    virtual ~Material();
    virtual RGBcolor shade(HitMemory & hitmem) = 0;
    virtual RGBcolor areaLightShade(HitMemory & hitmem) = 0;
    virtual RGBcolor getLe(HitMemory & hitmem) const = 0; 

    //protected:
    //Vec3 kd , ke, ka;
    //double shininess;
    //double transparency;
    //double reflectiveIndex;
    //double refractIndex;
    //materialType type;
};



#endif