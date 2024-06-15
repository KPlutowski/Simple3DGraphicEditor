#include "Sphere.h"

Sphere::Sphere(double x, double y, double z, double radius, int numMeridians, int numParallels, const wxColour& color, const std::vector<Position>& vertices)
	: Sphere(Position(x, y, z), radius, numMeridians, numParallels, color, vertices) {}

Sphere::Sphere(const Position& center, double radius, int numMeridians, int numParallels, const wxColour& color, const std::vector<Position>& vertices)
	: DrawableObject(color, "Sphere"), _center(center), _radius(radius), _numMeridians(numMeridians), _numParallels(numParallels) {
	if (vertices.size() > 0)
	{
		_vertices = vertices;
	}
	else
		computeVertices();
}

std::string Sphere::save() const {
	std::string toSave;

	toSave += DrawableObject::save();

	toSave += _center.toString() + " ";
	toSave += std::to_string(_radius) + " " + std::to_string(_numMeridians) + " " + std::to_string(_numParallels) + "\n";

	return  toSave;
}

void Sphere::render(wxDC& dc, wxPoint(*projectionFunc)(const Position&)) const {
	for (size_t i = 0; i < _vertices.size(); i += (_numMeridians + 1)) {
		for (size_t j = 0; j < _numMeridians; ++j) {
			size_t idx = i + j;
			if (idx + 1 < _vertices.size()) {
				dc.DrawLine(projectionFunc(_vertices[idx]).x, projectionFunc(_vertices[idx]).y,
					projectionFunc(_vertices[idx + 1]).x, projectionFunc(_vertices[idx + 1]).y);
			}
			if (i + _numMeridians + 1 < _vertices.size()) {
				dc.DrawLine(projectionFunc(_vertices[idx]).x, projectionFunc(_vertices[idx]).y,
					projectionFunc(_vertices[idx + _numMeridians + 1]).x, projectionFunc(_vertices[idx + _numMeridians + 1]).y);
			}
		}
	}
}

void Sphere::rotate(double xPivot, double yPivot, double zPivot, double alpha, double beta, double gamma)
{
	DrawableObject::rotate(xPivot, yPivot, zPivot, alpha, beta, gamma);

	// Update _center position to proper save sphere
	_center.rotate(Position(xPivot, yPivot, zPivot), alpha, beta, gamma);
}
void Sphere::computeVertices()
{
	const double phiStep = M_PI / _numParallels;
	const double lambdaStep = 2 * M_PI / _numMeridians;

	for (int i = 0; i <= _numParallels; ++i) {
		double phi = i * phiStep;
		for (int j = 0; j <= _numMeridians; ++j) {
			double lambda = j * lambdaStep;
			const Position v1(
				_center.x + _radius * sin(phi) * cos(lambda),
				_center.y + _radius * sin(phi) * sin(lambda),
				_center.z + _radius * cos(phi));

			_vertices.push_back(v1);
		}
	}
}