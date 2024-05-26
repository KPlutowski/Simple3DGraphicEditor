#include <vector>
#include "GUIMyFrame1.h"
#include "Drawable.h"
#include "Line.h"

Line::Line(double x1, double y1, double z1, double x2, double y2, double z2, wxColour color) : Line(Position(x1, y1, z1), Position(x2, y2, z2), color) {}
Line::Line(Position start, Position end, wxColour color) : Drawable(color), _start(start), _end(end) {}

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

void Line::move(double x_shift, double y_shift, double z_shift) {
	_start.x += x_shift;
	_start.y += y_shift;
	_start.z += z_shift;

	_end.x += x_shift;
	_end.y += y_shift;
	_end.z += z_shift;
}

void Line::rotate(double x_cord, double y_cord, double z_cord, double alpha, double beta, double gamma) {
	move(-x_cord, -y_cord, -z_cord);

	std::vector<std::vector<double>> rotationMatrix = generate_rotation_matrix(alpha, beta, gamma);

	double x = _start.x * rotationMatrix[0][0] + _start.y * rotationMatrix[0][1] + _start.z * rotationMatrix[0][2];
	double y = _start.x * rotationMatrix[1][0] + _start.y * rotationMatrix[1][1] + _start.z * rotationMatrix[1][2];
	double z = _start.x * rotationMatrix[2][0] + _start.y * rotationMatrix[2][1] + _start.z * rotationMatrix[2][2];
	_start.x = x;
	_start.y = y;
	_start.z = z;

	x = _end.x * rotationMatrix[0][0] + _end.y * rotationMatrix[0][1] + _end.z * rotationMatrix[0][2];
	y = _end.x * rotationMatrix[1][0] + _end.y * rotationMatrix[1][1] + _end.z * rotationMatrix[1][2];
	z = _end.x * rotationMatrix[2][0] + _end.y * rotationMatrix[2][1] + _end.z * rotationMatrix[2][2];
	_end.x = x;
	_end.y = y;
	_end.z = z;

	move(x_cord, y_cord, z_cord);
}

void Line::draw_front(wxDC& dc) {
	dc.SetPen(wxPen(_color));
	dc.SetBrush(*wxTRANSPARENT_BRUSH);

	wxPoint p1 = Camera::projectFront(_start);
	wxPoint p2 = Camera::projectFront(_end);

	dc.DrawLine(p1.x, p1.y, p2.x, p2.y);
}

void Line::draw_top(wxDC& dc) {
	dc.SetPen(wxPen(_color));
	dc.SetBrush(*wxTRANSPARENT_BRUSH);

	wxPoint p1 = Camera::projectTop(_start);
	wxPoint p2 = Camera::projectTop(_end);

	dc.DrawLine(p1.x, p1.y, p2.x, p2.y);
}

void Line::draw_side(wxDC& dc) {
	dc.SetPen(wxPen(_color));
	dc.SetBrush(*wxTRANSPARENT_BRUSH);

	wxPoint p1 = Camera::projectSide(_start);
	wxPoint p2 = Camera::projectSide(_end);

	dc.DrawLine(p1.x, p1.y, p2.x, p2.y);
}

void Line::draw_perspective(wxDC& dc) {
	dc.SetPen(wxPen(_color));
	dc.SetBrush(*wxTRANSPARENT_BRUSH);

	// Project the start and end points of the line
	wxPoint start_2d = Camera::projectPerspective(_start);
	wxPoint end_2d = Camera::projectPerspective(_end);

	// Draw the line in 2D
	dc.DrawLine(start_2d.x, start_2d.y, end_2d.x, end_2d.y);
}

void Line::draw(wxDC& dc1, wxDC& dc2, wxDC& dc3, wxDC& dc4)
{
	draw_front(dc1);
	draw_top(dc2);
	draw_side(dc3);
	draw_perspective(dc4);
}

std::string Line::save() const
{
	std::string result = "Line "
		+ std::to_string(_start.x) + " " + std::to_string(_start.y) + " " + std::to_string(_start.z) + " "
		+ std::to_string(_end.x) + " " + std::to_string(_end.y) + " " + std::to_string(_end.z) + " "
		+ std::to_string(_color.GetRGB()) + "\n";
	return result;
}