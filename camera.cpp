#include "camera.h"


Camera::Camera()
{
	
	cameraPosition = Point3(0,0,-10);
	cameraLookAt = Point3(0,0,0);
	cameraUp = Point3(0,10,0);
	cameraLength = 1.0;
	cameraHorzSize = 1.0;
	cameraAspectRatio = 1.0;
}

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

void Camera::setLength(double newLength)
{
	cameraLength = newLength;
}

void Camera::setHorzSize(double newHorzSize)
{
	cameraHorzSize = newHorzSize;
}

void Camera::setAspect(double newAspect)
{
	cameraAspectRatio = newAspect;
}

Point3 Camera::getPosition()
{
	return cameraPosition;
}

Point3 Camera::getLookAt()
{
	return cameraLookAt;
}

Point3 Camera::getUp()
{
	return cameraUp;
}

double Camera::getLength()
{
	return cameraLength;
}

double Camera::getHorzSize()
{
	return cameraHorzSize;
}

double Camera::getAspect()
{
	return cameraAspectRatio;
}

Vec3 Camera::getU()
{
	return projectionScreenU;
}

Vec3 Camera::getV()
{
	return projectionScreenV;
}

Vec3 Camera::getScreenCentre()
{
	return projectionScreenCenter;
}

void Camera::updateCameraGeometry()
{
	// First, compute the vector from the camera position to the LookAt position.
	alignmentVector = cameraLookAt - cameraPosition;
    alignmentVector = unit(alignmentVector);
	
	// Second, compute the U and V vectors.
	projectionScreenU = cross(alignmentVector, cameraUp);
	projectionScreenU = unit(projectionScreenU);
	projectionScreenV = cross(projectionScreenU, alignmentVector);
	projectionScreenV = unit(projectionScreenV);
	
	// Thirdly, compute the positon of the centre point of the screen.
	projectionScreenCenter = cameraPosition + (cameraLength * alignmentVector);
	
	// Modify the U and V vectors to match the size and aspect ratio.
	projectionScreenU = projectionScreenU * cameraHorzSize;
	projectionScreenV = projectionScreenV * (cameraHorzSize / cameraAspectRatio);
}

bool Camera::generateRay(double proScreenX, double proScreenY, Ray &cameraRay)
{
	// Compute the location of the screen point in world coordinates.
	Vec3 screenWorldPart1 = projectionScreenCenter + (projectionScreenU * proScreenX);
	Vec3 screenWorldCoordinate = screenWorldPart1 + (projectionScreenV * proScreenY);
	
	// Use this point along with the camera position to compute the ray.
	cameraRay.setOrigin(cameraPosition);
	cameraRay.setDest(screenWorldCoordinate);
	cameraRay.setRay(screenWorldCoordinate - cameraPosition);
	
	return true;
}