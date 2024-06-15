#include "Cone.h"

Cone::Cone(const Position& base1, double radius1, const Position& base2, double radius2, int sides, const wxColour& color, const std::vector<Position>& vertices)
	: DrawableObject(color, "Cone"), _base1(base1), _baseRadius1(radius1), _base2(base2), _baseRadius2(radius2), _sides(sides) {
	if (vertices.size() > 0)
	{
		_vertices = vertices;
	}
	else
		computeVertices();
}

Cone::Cone(double x1, double y1, double z1, double radius1, double x2, double y2, double z2, double radius2, int sides, wxColour color, const std::vector<Position>& vertices)
	: Cone(Position(x1, y1, z1), radius1, Position(x2, y2, z2), radius2, sides, color, vertices) {}

std::string Cone::save() const
{
	std::string toSave;

	toSave += DrawableObject::save();

	toSave += _base1.toString() + " " + std::to_string(_baseRadius1) + " ";
	toSave += _base2.toString() + " " + std::to_string(_baseRadius2) + " ";
	toSave += std::to_string(_sides) + "\n";

	return  toSave;
}

void Cone::render(wxDC& dc, wxPoint(*projectionFunc)(const Position&)) const
{
	for (int i = 0; i < _vertices.size(); i += 4)
	{
		const wxPoint p1 = projectionFunc(_vertices[i]);
		const wxPoint p2 = projectionFunc(_vertices[i + 1]);
		const wxPoint p3 = projectionFunc(_vertices[i + 2]);
		const wxPoint p4 = projectionFunc(_vertices[i + 3]);

		dc.DrawLine(p1.x, p1.y, p2.x, p2.y);
		dc.DrawLine(p2.x, p2.y, p3.x, p3.y);
		dc.DrawLine(p3.x, p3.y, p4.x, p4.y);
		dc.DrawLine(p4.x, p4.y, p1.x, p1.y);
	}
}

void Cone::rotate(double xPivot, double yPivot, double zPivot, double alpha, double beta, double gamma)
{
	DrawableObject::rotate(xPivot, yPivot, zPivot, alpha, beta, gamma);

	// Update base's position to proper save
	_base1.rotate(Position(xPivot, yPivot, zPivot), alpha, beta, gamma);
	_base2.rotate(Position(xPivot, yPivot, zPivot), alpha, beta, gamma);
}

void Cone::computeVertices() {
	const double angleStep = 2 * M_PI / _sides;

	for (int i = 0; i < _sides; ++i) {
		const double angle1 = i * angleStep;
		const double angle2 = (i + 1) * angleStep;

		const Position v1(_base1.x + _baseRadius1 * cos(angle1), _base1.y, _base1.z + _baseRadius1 * sin(angle1));
		const Position v2(_base1.x + _baseRadius1 * cos(angle2), _base1.y, _base1.z + _baseRadius1 * sin(angle2));
		const Position v3(_base2.x + _baseRadius2 * cos(angle2), _base2.y, _base2.z + _baseRadius2 * sin(angle2));
		const Position v4(_base2.x + _baseRadius2 * cos(angle1), _base2.y, _base2.z + _baseRadius2 * sin(angle1));

		_vertices.push_back(v1);
		_vertices.push_back(v2);
		_vertices.push_back(v3);
		_vertices.push_back(v4);
	}
}