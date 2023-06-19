#ifndef CAMERA_H
#define CAMERA_H
#include "DataStructures/matrix.h"
#include "ray.h"
#include "Samplers/haltonSampler.h"
#include "Samplers/pureRandom.h"
#include <memory>
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
        std::shared_ptr<Sampler> sampler;
        //Vec3 alignmentVector;
        //Vec3 projectionScreenU;
        //Vec3 projectionScreenV;
        
        Point3 projectionScreenCenter;

    public:
        Camera();
        Camera(std::shared_ptr<Sampler> & sampler);
        ~Camera();
        void setPosition(const Point3 & position);
        void setLookAt(const Point3 & lookAt);
        void setUp(const Point3 & up);
        void setDistance(double newLength);
        void setWidth(double newWidth);
        void setHeight(double newHeight);
        void setAspect(double newAspect);
        void setFovAngle(double newFov);
        void setSampler(std::shared_ptr<Sampler> & newSampler);

        
        Point3 getPosition() const;
        Point3 getLookAt() const;
        Point3 getUp() const;
        //Vec3 getU();
        //Vec3 getV();
        Point3 getScreenCentre() const;
        double getDistance() const;
        double getWidth() const;
        double getHeight() const;
        double getAspect() const;
        double getFovAngle() const;

        bool generateRay(double proScreenX, double proScreenY, Ray & ray) const;
        void updateCameraGeometry();



};

#endif