#ifndef PLANE_H
#define PLANE_H

#include "objectBase.h"
#include "../DataStructures/matrix.h"

class Plane : public ObjectBase {
    private:
      Vec3 __normal;
      Point3 __planePoint;

    public:
      Plane();
      ~Plane();
      Plane(Point3 __planePoint, Vec3 __normal);
      bool computeIntersection(const Ray & ray, HitMemory & hitData) override;

};

#endif