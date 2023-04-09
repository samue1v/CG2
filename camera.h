#ifndef CAMERA_H
#define CAMERA_H
#include <cstdlib>
#include <time.h>
#include "DataStructures/matrix.h"
#include "ray.h"
class Camera{

    private:
        Point3 cameraPosition;
        Point3 cameraLookAt;
        Point3 cameraUp;
        double cameraDistance;
        double screenWidth;
        double screenHeight;
        double aspectRatio;
        double fovAngle;

        //Vec3 alignmentVector;
        //Vec3 projectionScreenU;
        //Vec3 projectionScreenV;
        Point3 projectionScreenCenter;

    public:
        Camera();
        ~Camera();
        void setPosition(const Point3 & position);
        void setLookAt(const Point3 & lookAt);
        void setUp(const Point3 & up);
        void setDistance(double newLength);
        void setWidth(double newWidth);
        void setHeight(double newHeight);
        void setAspect(double newAspect);
        void setFovAngle(double newFov);

        
        Point3 getPosition();
        Point3 getLookAt();
        Point3 getUp();
        //Vec3 getU();
        //Vec3 getV();
        Point3 getScreenCentre();
        double getDistance();
        double getWidth();
        double getHeight();
        double getAspect();
        double getFovAngle();

        bool generateRay(double proScreenX, double proScreenY, Ray & ray);
        void updateCameraGeometry();



};

#endif