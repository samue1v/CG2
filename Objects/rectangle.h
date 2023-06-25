#include "objectBase.h"

class Rectangle : public ObjectBase{
    public:
    Rectangle();
    Rectangle(Vec3 p0, Vec3 l1, Vec3 l2);
    ~Rectangle();
    bool computeIntersection(const Ray & ray,HitMemory & hitData);
    double pdf(const HitMemory & hitmem) const;
    Vec3 getNormal(const Point3 p) const;
    Vec3 sample() const;
    private:
    Vec3 __p0,__l1,__l2;
    double __invArea;

};