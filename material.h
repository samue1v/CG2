#ifndef MATERIAL_H
#define MATERIAL_H

#include <vector>
#include "DataStructures/matrix.h"

enum materialType{
    opaque,
    reflective,
    refractive
};

class Material{
    public:
        Vec3 kd , ke, ka;
        double shininess;
        double transparency;
        double reflectiveIndex;
        double refractIndex;
        materialType type;
};



#endif