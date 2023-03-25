#ifndef MATERIAL_H
#define MATERIAL_H

#include <vector>
#include "DataStructures/matrix.h"

class Material{
    public:
        Vec3 kd , ke, ka;
        double shininess;
        double reflectiviness;
        double refractiviness;
};

#endif