#include <vector>
#include "GUIMyFrame1.h"
#include "Drawable.h"
#include "Line.h"
#include "Sphere.h"
#include "Box.h"
#include "Cone.h"
#include "Cylinder.h"

double Drawable::Camera::frontDistance = 200.0;
double Drawable::Camera::topDistance = 200.0;
double Drawable::Camera::rightDistance = 200.0;
Position Drawable::Camera::cameraPosition = Position(200, 200, 200);
Position Drawable::Camera::lookAtPosition = Position(0, 0, 0);
double Drawable::Camera::fieldOfView = 60.0;

double Drawable::Camera::fovInRadians = fieldOfView * (M_PI / 180.0);
double Drawable::Camera::tanFov = tan(fovInRadians / 2.0);
double Drawable::Camera::aspectRatio = panelWidth / panelHeight;

double Drawable::Camera::panelHeight = 200.0;
double Drawable::Camera::panelWidth = 200.0;

Position Drawable::Camera::cameraDirection = {
			lookAtPosition.x - cameraPosition.x,
			lookAtPosition.y - cameraPosition.y,
			lookAtPosition.z - cameraPosition.z
};
Position Drawable::Camera::rightVector = {
			cameraDirection.y * 0 - cameraDirection.z * 1,
			cameraDirection.z * 0 - cameraDirection.x * 0,
			cameraDirection.x * 1 - cameraDirection.y * 0
};
Position Drawable::Camera::upVector = {
			rightVector.y * cameraDirection.z - rightVector.z * cameraDirection.y,
			rightVector.z * cameraDirection.x - rightVector.x * cameraDirection.z,
			rightVector.x * cameraDirection.y - rightVector.y * cameraDirection.x
};

wxPoint Drawable::Camera::projectPerspective(const Position& point) {
	// Transform the point to camera space
	double px = point.x - cameraPosition.x;
	double py = point.y - cameraPosition.y;
	double pz = point.z - cameraPosition.z;

	// Apply rotation (camera orientation)
	double camX = px * rightVector.x + py * rightVector.y + pz * rightVector.z;
	double camY = px * upVector.x + py * upVector.y + pz * upVector.z;
	double camZ = px * cameraDirection.x + py * cameraDirection.y + pz * cameraDirection.z;

	// Ensure camZ is not too close to zero to prevent division by zero
	if (camZ < nearPlane) {
		camZ = nearPlane;
	}

	// Perspective projection
	double screenX = (camX / (camZ * tanFov * aspectRatio)) * (panelWidth / 2) + (panelWidth / 2);
	double screenY = (camY / (camZ * tanFov)) * (panelHeight / 2) + (panelHeight / 2);

	return wxPoint(screenX, panelHeight - screenY); // Flip y-axis for drawing
}

wxPoint Drawable::Camera::projectFront(const Position& pos)
{
	// Project X and Y coordinates for front view, ignoring Z
	double screenX = (pos.x / frontDistance) * (panelWidth / 2) + (panelWidth / 2);
	double screenY = (pos.y / frontDistance) * (panelHeight / 2) + (panelHeight / 2);
	return wxPoint(screenX, panelHeight - screenY); // Flip y-axis for drawing
}

wxPoint Drawable::Camera::projectTop(const Position& pos)
{
	// Project X and Z coordinates for top view, ignoring Y
	double screenX = (pos.x / topDistance) * (panelWidth / 2) + (panelWidth / 2);
	double screenY = (pos.z / topDistance) * (panelHeight / 2) + (panelHeight / 2);
	return wxPoint(screenX, panelHeight - screenY); // Flip y-axis for drawing
}

wxPoint Drawable::Camera::projectSide(const Position& pos)
{
	// Project Y and Z coordinates for side view, ignoring X
	double screenX = (pos.y / rightDistance) * (panelWidth / 2) + (panelWidth / 2);
	double screenY = (pos.z / rightDistance) * (panelHeight / 2) + (panelHeight / 2);
	return wxPoint(screenX, panelHeight - screenY); // Flip y-axis for drawing
}

void Drawable::Camera::setPosition(const double x, const double y, const double z)
{
	cameraPosition = { x, y, z };
	Camera::update();
}

Position Drawable::Camera::getPosition() { return cameraPosition; }

void Drawable::Camera::setLookAt(const double x, const double y, const double z)
{
	lookAtPosition = { x, y, z };
	Camera::update();
}

Position Drawable::Camera::getLookAt() { return lookAtPosition; }

void Drawable::Camera::setFov(const double newFov)
{
	fieldOfView = newFov;
	Camera::update();
}

void Drawable::Camera::update() {
	fovInRadians = fieldOfView * (M_PI / 180.0);
	tanFov = tan(fovInRadians / 2.0);
	aspectRatio = panelWidth / panelHeight;

	cameraDirection = {
		lookAtPosition.x - cameraPosition.x,
		lookAtPosition.y - cameraPosition.y,
		lookAtPosition.z - cameraPosition.z
	};
	// Normalize camera direction
	double length = sqrt(cameraDirection.x * cameraDirection.x + cameraDirection.y * cameraDirection.y + cameraDirection.z * cameraDirection.z);
	cameraDirection.x /= length;
	cameraDirection.y /= length;
	cameraDirection.z /= length;

	rightVector = {
		cameraDirection.y * 0 - cameraDirection.z * 1,
		cameraDirection.z * 0 - cameraDirection.x * 0,
		cameraDirection.x * 1 - cameraDirection.y * 0
	};
	// Normalize right vector
	length = sqrt(rightVector.x * rightVector.x + rightVector.y * rightVector.y + rightVector.z * rightVector.z);
	rightVector.x /= length;
	rightVector.y /= length;
	rightVector.z /= length;

	upVector = {
		rightVector.y * cameraDirection.z - rightVector.z * cameraDirection.y,
		rightVector.z * cameraDirection.x - rightVector.x * cameraDirection.z,
		rightVector.x * cameraDirection.y - rightVector.y * cameraDirection.x
	};
}

double Drawable::Camera::getFov() { return fieldOfView; }

double Drawable::Camera::getFrontDistance() { return frontDistance; }

double Drawable::Camera::getTopDistance() { return topDistance; }

double Drawable::Camera::getRightDistance() { return rightDistance; }

void Drawable::Camera::setFrontDistance(const double front) { frontDistance = front; }

void Drawable::Camera::setTopDistance(const double top) { topDistance = top; }

void Drawable::Camera::setRightDistance(const double right) { rightDistance = right; }

void Drawable::Camera::SetViewSize(const double x, const double y) {
	panelWidth = x;
	panelHeight = y;
	Camera::update();
}