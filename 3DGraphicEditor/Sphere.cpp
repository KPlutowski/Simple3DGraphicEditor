#include "Sphere.h"

Sphere::Sphere(double x, double y, double z, double radius, int numMeridians, int numParallels, const wxColour& color)
	: Sphere(Position(x, y, z), radius, numMeridians, numParallels, color) {}

Sphere::Sphere(const Position& center, double radius, int numMeridians, int numParallels, const wxColour& color)
	: Drawable(color), _center(center), _radius(radius), _numMeridians(numMeridians), _numParallels(numParallels) {}

void Sphere::move(double xShift, double yShift, double zShift) {
	_center.shift(xShift, yShift, zShift);
}

void Sphere::rotate(double xPivot, double yPivot, double zPivot, double alpha, double beta, double gamma) {
	// Rotate the center point around the pivot point
	_center = rotatePoint(_center, Position(xPivot, yPivot, zPivot), alpha, beta, gamma);

	// Update rotation angles
	_alpha = fmod((_alpha + alpha + 360.0), 360.0);
	_beta = fmod((_beta + beta + 360.0), 360.0);
	_gamma = fmod((_gamma + gamma + 360.0), 360.0);
}

void Sphere::draw(wxDC& dcFront, wxDC& dcTop, wxDC& dcSide, wxDC& dcPerspective) {
	// Render sphere in different views
	renderSphere(dcFront, Camera::projectFront);
	renderSphere(dcTop, Camera::projectTop);
	renderSphere(dcSide, Camera::projectSide);
	renderSphere(dcPerspective, Camera::projectPerspective);
}

std::string Sphere::getInfo() const {
	return "Sphere " + _center.toString();
}

std::string Sphere::save() const {
	std::string result = "Sphere "
		+ std::to_string(_center.x) + " " + std::to_string(_center.y) + " " + std::to_string(_center.z) + " "
		+ std::to_string(_radius) + " " + std::to_string(_numMeridians) + " " + std::to_string(_numParallels) + " "
		+ std::to_string(_color.GetRGB()) + "\n";
	return result;
}

Position Sphere::rotatePoint(const Position& point, const Position& center, double alpha, double beta, double gamma) const {
	// Translate the point so that the center becomes the origin
	double x = point.x - center.x;
	double y = point.y - center.y;
	double z = point.z - center.z;

	// Precompute trigonometric values
	double cosAlpha = cos(alpha * M_PI / 180.0);
	double sinAlpha = sin(alpha * M_PI / 180.0);
	double cosBeta = cos(beta * M_PI / 180.0);
	double sinBeta = sin(beta * M_PI / 180.0);
	double cosGamma = cos(gamma * M_PI / 180.0);
	double sinGamma = sin(gamma * M_PI / 180.0);

	// Perform rotation
	double x_rot = cosBeta * cosGamma * x + (cosAlpha * sinGamma + sinAlpha * sinBeta * cosGamma) * y + (sinAlpha * sinGamma - cosAlpha * sinBeta * cosGamma) * z;
	double y_rot = -cosBeta * sinGamma * x + (cosAlpha * cosGamma - sinAlpha * sinBeta * sinGamma) * y + (sinAlpha * cosGamma + cosAlpha * sinBeta * sinGamma) * z;
	double z_rot = sinBeta * x - sinAlpha * cosBeta * y + cosAlpha * cosBeta * z;

	// Translate the rotated point back to its original position
	x_rot += center.x;
	y_rot += center.y;
	z_rot += center.z;

	return Position(x_rot, y_rot, z_rot);
}

Position Sphere::computeVertex(double phi, double lambda) const {
	return Position(
		_center.x + _radius * sin(phi) * cos(lambda),
		_center.y + _radius * sin(phi) * sin(lambda),
		_center.z + _radius * cos(phi)
	);
}

inline Position Sphere::rotateVertex(const Position& vertex) const {
	return rotatePoint(vertex, _center, _alpha, _beta, _gamma);
}

void Sphere::renderSphere(wxDC& dc, wxPoint(*projectionFunc)(const Position&)) const {
	const double phiStep = M_PI / _numParallels;
	const double lambdaStep = 2 * M_PI / _numMeridians;

	// Precompute vertices can be do parallel
	std::vector<std::vector<Position>> vertices(_numParallels + 1, std::vector<Position>(_numMeridians + 1));
	for (int i = 0; i <= _numParallels; ++i) {
		double phi = i * phiStep;
		for (int j = 0; j <= _numMeridians; ++j) {
			double lambda = j * lambdaStep;
			vertices[i][j] = rotateVertex(computeVertex(phi, lambda));
		}
	}

	// Draw sphere
	for (int i = 0; i < _numParallels; ++i) {
		for (int j = 0; j < _numMeridians; ++j) {
			const Position& v1 = vertices[i][j];
			const Position& v2 = vertices[i][j + 1];
			const Position& v3 = vertices[i + 1][j + 1];
			const Position& v4 = vertices[i + 1][j];

			wxPoint p1 = projectionFunc(v1);
			wxPoint p2 = projectionFunc(v2);
			wxPoint p3 = projectionFunc(v3);
			wxPoint p4 = projectionFunc(v4);

			dc.DrawLine(p1.x, p1.y, p2.x, p2.y);
			dc.DrawLine(p2.x, p2.y, p3.x, p3.y);
			dc.DrawLine(p3.x, p3.y, p4.x, p4.y);
			dc.DrawLine(p4.x, p4.y, p1.x, p1.y);
		}
	}
}