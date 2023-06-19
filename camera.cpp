#include "camera.h"


Camera::Camera()
{
	cameraPosition = Point3(0,0,-10);
	cameraLookAt = Point3(0,0,0);
	cameraUp = Point3(0,10,0);
	cameraDistance = 1.0;
	screenWidth = 1.0;
	aspectRatio = 1.0;
}

Camera::Camera(std::shared_ptr<Sampler> & samplerPtr)
{
	cameraPosition = Point3(0,0,-10);
	cameraLookAt = Point3(0,0,0);
	cameraUp = Point3(0,10,0);
	cameraDistance = 1.0;
	screenWidth = 1.0;
	aspectRatio = 1.0;
	sampler = samplerPtr;
}

Camera::~Camera(){}

void Camera::setPosition(const Point3 &newPosition)
{
	cameraPosition = newPosition;
}

void Camera::setLookAt(const Point3 &newLookAt)
{
	cameraLookAt = newLookAt;
}

void Camera::setUp(const Point3 &upVector)
{
	cameraUp = upVector;
}

void Camera::setDistance(double newDistance)
{
	cameraDistance = newDistance;
}

void Camera::setWidth(double newWidth)
{
	screenWidth = newWidth;
}

void Camera::setHeight(double newHeight){
	screenHeight = newHeight;
}

void Camera::setAspect(double newAspect)
{
	aspectRatio = newAspect;
}

void Camera::setFovAngle(double newFovAngle){
	fovAngle = newFovAngle;
}

void Camera::setSampler(std::shared_ptr<Sampler> & newSampler){
	sampler = newSampler;
}

Point3 Camera::getPosition() const
{
	return cameraPosition;
}

Point3 Camera::getLookAt()  const
{
	return cameraLookAt;
}

Point3 Camera::getUp()  const
{
	return cameraUp;
}

double Camera::getDistance()  const
{
	return cameraDistance;
}

double Camera::getWidth()  const
{
	return screenWidth;
}

double Camera::getHeight()  const
{
	return screenHeight;
}

double Camera::getAspect()  const
{
	return aspectRatio;
}
/*
Vec3 Camera::getU()
{
	return projectionScreenU;
}

Vec3 Camera::getV()
{
	return projectionScreenV;
}
*/
Vec3 Camera::getScreenCentre()  const
{
	return projectionScreenCenter;
}

double Camera::getFovAngle()  const
{
	return fovAngle;
}

void Camera::updateCameraGeometry()
{
	// First, compute the vector from the camera position to the LookAt position.
	//alignmentVector = cameraLookAt - cameraPosition;
    //alignmentVector = unit(alignmentVector);
	//
	//// Second, compute the U and V vectors.
	//projectionScreenU = cross(alignmentVector, cameraUp);
	//projectionScreenU = unit(projectionScreenU);
	//projectionScreenV = cross(projectionScreenU, alignmentVector);
	//projectionScreenV = unit(projectionScreenV);
	//
	//// Thirdly, compute the positon of the centre point of the screen.
	//projectionScreenCenter = cameraPosition + (cameraDistance * alignmentVector);
	//
	//// Modify the U and V vectors to match the size and aspect ratio.
	//projectionScreenU = projectionScreenU * screenWidth;
	//projectionScreenV = projectionScreenV * (screenWidth / aspectRatio);
}

bool Camera::generateRay(double proScreenX, double proScreenY, Ray &cameraRay)  const
{	
	/*
	// Compute the location of the screen point in world coordinates.
	Vec3 screenWorldPart1 = projectionScreenCenter + (projectionScreenU * proScreenX);
	Vec3 screenWorldCoordinate = screenWorldPart1 + (projectionScreenV * proScreenY);
	
	// Use this point along with the camera position to compute the ray.
	cameraRay.setOrigin(cameraPosition);
	cameraRay.setDest(screenWorldCoordinate);
	cameraRay.setRay(screenWorldCoordinate - cameraPosition);
	*/
	Pair pixelSample = sampler->getSample(); 
	double px = (2 * ( (proScreenX + pixelSample[0])/ screenWidth ) - 1) * tan(fovAngle / 2 * M_PI / 180) * aspectRatio;
	double py = (1 - 2* ((proScreenY + pixelSample[1]) / screenHeight)) * tan(fovAngle / 2 * M_PI / 180);
	Point3 canvasPoint(px,py,cameraDistance);
	cameraRay = Ray(canvasPoint,Point3(0,0,0));
	cameraRay.setOrigin(canvasPoint);
	
	
	return true;
}