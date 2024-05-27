#include "Line.h"

Line::Line(double x1, double y1, double z1, double x2, double y2, double z2, wxColour color)
	: Line(Position(x1, y1, z1), Position(x2, y2, z2), color) {}

Line::Line(Position start, Position end, wxColour color)
	: Drawable(color), _start(start), _end(end) {}

Position Line::getStart() const {
	return _start;
}

void Line::setStart(const Position& newStart) {
	_start = newStart;
}

Position Line::getEnd() const {
	return _end;
}

void Line::setEnd(const Position& newEnd) {
	_end = newEnd;
}

void Line::move(double xShift, double yShift, double zShift) {
	_start.shift(xShift, yShift, zShift);
	_end.shift(xShift, yShift, zShift);
}

void Line::rotate(double xPivot, double yPivot, double zPivot, double alpha, double beta, double gamma) {
	// Move line to origin for rotation
	move(-xPivot, -yPivot, -zPivot);

	std::vector<std::vector<double>> rotationMatrix = generateRotationMatrix(alpha, beta, gamma);

	// Rotate start point
	double x = _start.x * rotationMatrix[0][0] + _start.y * rotationMatrix[0][1] + _start.z * rotationMatrix[0][2];
	double y = _start.x * rotationMatrix[1][0] + _start.y * rotationMatrix[1][1] + _start.z * rotationMatrix[1][2];
	double z = _start.x * rotationMatrix[2][0] + _start.y * rotationMatrix[2][1] + _start.z * rotationMatrix[2][2];
	_start.x = x;
	_start.y = y;
	_start.z = z;

	// Rotate end point
	x = _end.x * rotationMatrix[0][0] + _end.y * rotationMatrix[0][1] + _end.z * rotationMatrix[0][2];
	y = _end.x * rotationMatrix[1][0] + _end.y * rotationMatrix[1][1] + _end.z * rotationMatrix[1][2];
	z = _end.x * rotationMatrix[2][0] + _end.y * rotationMatrix[2][1] + _end.z * rotationMatrix[2][2];
	_end.x = x;
	_end.y = y;
	_end.z = z;

	// Move line back to its original position
	move(xPivot, yPivot, zPivot);
}

void Line::draw(wxDC& dcFront, wxDC& dcTop, wxDC& dcSide, wxDC& dcPerspective) {
	// Draw line in different views
	renderLine(dcFront, Camera::projectFront);
	renderLine(dcTop, Camera::projectTop);
	renderLine(dcSide, Camera::projectSide);
	renderLine(dcPerspective, Camera::projectPerspective);
}

inline std::string Line::getInfo() const {
	return "Line " + _start.toString() + " " + _end.toString();
}

void Line::renderLine(wxDC& dc, wxPoint(*projectionFunc)(const Position&)) const {
	wxPoint p1 = projectionFunc(_start);
	wxPoint p2 = projectionFunc(_end);
	dc.DrawLine(p1.x, p1.y, p2.x, p2.y);
}

std::string Line::save() const {
	return "Line "
		+ std::to_string(_start.x) + " " + std::to_string(_start.y) + " " + std::to_string(_start.z) + " "
		+ std::to_string(_end.x) + " " + std::to_string(_end.y) + " " + std::to_string(_end.z) + " "
		+ std::to_string(_color.GetRGB()) + "\n";
}