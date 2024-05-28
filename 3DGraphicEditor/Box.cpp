#include "Box.h"

Box::Box(double x1, double y1, double z1, double x2, double y2, double z2, const wxColour& color, const std::vector<Position>& vertices)
	: Box(Position(x1, y1, z1), Position(x2, y2, z2), color, vertices) {}

Box::Box(const Position& start, const Position& end, const wxColour& color, const std::vector<Position>& vertices)
	: Drawable(color, "Box"), _start(start), _end(end)
{
	if (vertices.size() > 0)
	{
		_vertices = vertices;
	}
	else
		computeVertices();
}

std::string Box::getInfo() const {
	return "Box from " + _start.toString() + " to " + _end.toString();
}

std::string Box::save() const {
	std::string toSave;

	toSave += Drawable::save();

	toSave += _start.toString() + " " + _end.toString() + "\n";

	return  toSave;
}

void Box::render(wxDC& dc, wxPoint(*projectionFunc)(const Position&)) const {
	std::vector<wxPoint> projectedCorners;
	projectedCorners.reserve(8);
	for (const auto& corner : _vertices) {
		projectedCorners.push_back(projectionFunc(corner));
	}

	// Draw the edges of the box
	for (size_t i = 0; i < 4; ++i) {
		dc.DrawLine(projectedCorners[i], projectedCorners[(i + 1) % 4]);
		dc.DrawLine(projectedCorners[i + 4], projectedCorners[(i + 1) % 4 + 4]);
		dc.DrawLine(projectedCorners[i], projectedCorners[i + 4]);
	}
}

void Box::computeVertices() {
	_vertices.clear();
	_vertices.reserve(8);

	_vertices.push_back(_start); // 1 (x1, y1, z1)
	_vertices.emplace_back(_end.x, _start.y, _start.z); // 2 (x2, y1, z1)
	_vertices.emplace_back(_end.x, _start.y, _end.z); // 3 (x2, y1, z2)
	_vertices.emplace_back(_start.x, _start.y, _end.z); // 4 (x1, y1, z2)
	_vertices.emplace_back(_start.x, _end.y, _start.z); // 5 (x1, y2, z1)
	_vertices.emplace_back(_end.x, _end.y, _start.z); // 6 (x2, y2, z1)
	_vertices.push_back(_end); // 7 (x2, y2, z2)
	_vertices.emplace_back(_start.x, _end.y, _end.z); // 8 (x1, y2, z2)
}