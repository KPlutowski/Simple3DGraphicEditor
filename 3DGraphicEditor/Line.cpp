#include "Line.h"

Line::Line(double x1, double y1, double z1, double x2, double y2, double z2, wxColour color, const std::vector<Position>& vertices)
	: Line(Position(x1, y1, z1), Position(x2, y2, z2), color, vertices) {}

Line::Line(Position start, Position end, wxColour color, const std::vector<Position>& vertices)
	: DrawableObject(color, "Line"), _start(start), _end(end)
{
	if (vertices.size() > 0)
	{
		_vertices = vertices;
	}
	else
		computeVertices();
}

void Line::render(wxDC& dc, wxPoint(*projectionFunc)(const Position&)) const {
	wxPoint p1 = projectionFunc(_vertices[0]);
	wxPoint p2 = projectionFunc(_vertices[1]);
	dc.DrawLine(p1.x, p1.y, p2.x, p2.y);
}
std::string Line::getInfo() const {
	return "Line " + _vertices[0].toString() + " " + _vertices[1].toString();
}
std::string Line::save() const {
	std::string toSave;

	toSave += DrawableObject::save();

	toSave += _start.toString() + " " + _end.toString() + "\n";

	return  toSave;
}
void Line::computeVertices() {
	_vertices = { _start, _end };
}