#include <vector>
#include "GUIMyFrame1.h"
#include "Drawable.h"
#include "Line.h"

Line::Line(double x1, double y1, double z1, double x2, double y2, double z2) : _start(x1, y1, z1), _end(x2, y2, z2), _color(line_color) {}
Line::Line(Position start, Position end) : Line(start.x, start.y, start.z,end.x, end.y, end.z ){}


Position Line::start() {
	return _start;
}

Position Line::end() {
	return _end;
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
	//TODO
}

void Line::draw_front(wxDC& dc) {
	//TODO
	dc.SetPen(wxPen(_color));
	dc.DrawLine(_start.x, _start.y, _end.x, _end.y);
}

void Line::draw_top(wxDC& dc) {
	//TODO
	dc.SetPen(wxPen(_color));
	dc.DrawLine(_start.x, _start.z, _end.x, _end.z);
}

void Line::draw_side(wxDC& dc) {
	//TODO
	dc.SetPen(wxPen(_color));
	dc.DrawLine(_start.y, _start.z, _end.y, _end.z);
}

void Line::draw_perspective(wxDC& dc) {
	//TODO

	dc.SetPen(wxPen(_color));

	// C Position camera_pos; /// @brief Pozycja kamery z perspektywa
	// L Position camera_look; /// @brief Punkt na ktory patrzy kamera
	// FOV double camera_fov; /// @brief FOV kamery z perspektywa (w stopniach)

	// _start, _end

}

void Line::draw(wxDC& dc1, wxDC& dc2, wxDC& dc3, wxDC& dc4)
{
	draw_front(dc1);
	draw_top(dc2);
	draw_side(dc3);
	draw_perspective(dc4);
}