#include <vector>
#include "GUIMyFrame1.h"
#include "Drawable.h"
#include "Line.h"

Line::Line(double x1, double y1, double z1, double x2, double y2, double z2) : _start(x1, y1, z1), _end(x2, y2, z2), _color(line_color) {}

Position Line::start() {
	return _start;
}

Position Line::end() {
	return _end;
}

void Line::move(double x_shift, double y_shift, double z_shift) {
	//TODO
}

void Line::rotate(double x_cord, double y_cord, double z_cord, double alpha, double beta, double gamma) {
	//TODO
}

void Line::draw_front(wxDC& dc) {
	//TODO
}

void Line::draw_top(wxDC& dc) {
	//TODO
}

void Line::draw_side(wxDC& dc) {
	//TODO
}

void Line::draw_perspective(wxDC& dc) {
	//TODO
}
