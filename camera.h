#ifndef CAMERA_H
#define CAMERA_H
#include "DataStructures/matrix.h"
#include "ray.h"
class Camera{

    private:
        Point3 cameraPosition;
        Point3 cameraLookAt;
        Point3 cameraUp;
        double cameraLength;
        double cameraHorzSize;
        double cameraAspectRatio;

        Vec3 alignmentVector;
        Vec3 projectionScreenU;
        Vec3 projectionScreenV;
        Point3 projectionScreenCenter;

    public:
        Camera();
        void setPosition(const Point3 & position);
        void setLookAt(const Point3 & lookAt);
        void setUp(const Point3 & up);
        void setLength(double newLength);
        void setHorzSize(double newSize);
        void setAspect(double newAspect);

        Point3 getPosition();
        Point3 getLookAt();
        Point3 getUp();
        Vec3 getU();
        Vec3 getV();
        Point3 getScreenCentre();
        double getLength();
        double getHorzSize();
        double getAspect();

        bool generateRay(double proScreenX, double proScreenY, Ray & ray);
        void updateCameraGeometry();



};

#endif