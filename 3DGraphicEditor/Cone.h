#pragma once
#include "Drawable.h"
class Cone :public Drawable
{
public:
	Cone(const Position& base1, double radius1, const Position& base2, double radius2, int n, wxColour color = Drawable::penColor)
		:Drawable(color), _base1(base1), _radius1(radius1), _base2(base2), _radius2(radius2), _n(n) {}
	Cone(const double x1, const double y1, const double z1, const double radius1, const double x2, const double y2, const double z2, const double radius2, const int n, wxColour color = Drawable::penColor)
		:Cone(Position(x1, y1, z1), radius1, Position(x2, y2, z2), n, radius2, color) {}

	void draw(wxDC& dc1, wxDC& dc2, wxDC& dc3, wxDC& dc4) override {
		//draw_front(dc1);
		//draw_top(dc2);
		//draw_side(dc3);
		//draw_perspective(dc4);
	}
	std::string save() const override
	{
		return "Cone " + _base1.toString() + " " + std::to_string(_radius1) + " "
			+ _base2.toString() + " " + std::to_string(_radius2) + " " + std::to_string(_n) + " "
			+ std::to_string(_color.GetRGB()) + "\n";
	}
	std::string getInfo() const override
	{
		return "Cone";
	}
protected:

	void move(double x_shift, double y_shift, double z_shift) override
	{
		_base1.x += x_shift;
		_base1.y += y_shift;
		_base1.z += z_shift;
		_base2.x += x_shift;
		_base2.y += y_shift;
		_base2.z += z_shift;
	}
	void rotate(double x_cord, double y_cord, double z_cord, double alpha, double beta, double gamma) override {
		// Move the base points to the origin
		move(-x_cord, -y_cord, -z_cord);

		std::vector<std::vector<double>> rotationMatrix = generateRotationMatrix(alpha, beta, gamma);

		double x = _base1.x * rotationMatrix[0][0] + _base1.y * rotationMatrix[0][1] + _base1.z * rotationMatrix[0][2];
		double y = _base1.x * rotationMatrix[1][0] + _base1.y * rotationMatrix[1][1] + _base1.z * rotationMatrix[1][2];
		double z = _base1.x * rotationMatrix[2][0] + _base1.y * rotationMatrix[2][1] + _base1.z * rotationMatrix[2][2];
		_base1.x = x;
		_base1.y = y;
		_base1.z = z;

		x = _base2.x * rotationMatrix[0][0] + _base2.y * rotationMatrix[0][1] + _base2.z * rotationMatrix[0][2];
		y = _base2.x * rotationMatrix[1][0] + _base2.y * rotationMatrix[1][1] + _base2.z * rotationMatrix[1][2];
		z = _base2.x * rotationMatrix[2][0] + _base2.y * rotationMatrix[2][1] + _base2.z * rotationMatrix[2][2];
		_base2.x = x;
		_base2.y = y;
		_base2.z = z;

		// Move the base points back to their original positions
		move(x_cord, y_cord, z_cord);
	}

	//void draw_front(wxDC& dc) {
	//	dc.SetPen(wxPen(_color));
	//	dc.SetBrush(*wxTRANSPARENT_BRUSH);

	//	// Calculate the step angle
	//	double angle_step = 2 * M_PI / _n;

	//	// Iterate over each side of the cone
	//	for (int i = 0; i < _n; ++i) {
	//		// Calculate the current and next angles
	//		double angle1 = i * angle_step;
	//		double angle2 = (i + 1) * angle_step;

	//		// Calculate the vertices for the current and next sides
	//		Position v1(_base1.x + _radius1 * cos(angle1), _base1.y, _base1.z + _radius1 * sin(angle1));
	//		Position v2(_base1.x + _radius1 * cos(angle2), _base1.y, _base1.z + _radius1 * sin(angle2));
	//		Position v3(_base2.x + _radius2 * cos(angle2), _base2.y, _base2.z + _radius2 * sin(angle2));
	//		Position v4(_base2.x + _radius2 * cos(angle1), _base2.y, _base2.z + _radius2 * sin(angle1));

	//		// Project vertices to 2D screen coordinates
	//		wxPoint p1 = Camera::projectFront(v1);
	//		wxPoint p2 = Camera::projectFront(v2);
	//		wxPoint p3 = Camera::projectFront(v3);
	//		wxPoint p4 = Camera::projectFront(v4);

	//		// Draw quadrilateral
	//		dc.DrawLine(p1.x, p1.y, p2.x, p2.y);
	//		dc.DrawLine(p2.x, p2.y, p3.x, p3.y);
	//		dc.DrawLine(p3.x, p3.y, p4.x, p4.y);
	//		dc.DrawLine(p4.x, p4.y, p1.x, p1.y);
	//	}
	//}
	//void draw_top(wxDC& dc) {
	//	dc.SetPen(wxPen(_color));
	//	dc.SetBrush(*wxTRANSPARENT_BRUSH);

	//	// Calculate the step angle
	//	double angle_step = 2 * M_PI / _n;

	//	// Iterate over each side of the cone
	//	for (int i = 0; i < _n; ++i) {
	//		// Calculate the current and next angles
	//		double angle1 = i * angle_step;
	//		double angle2 = (i + 1) * angle_step;

	//		// Calculate the vertices for the current and next sides
	//		Position v1(_base1.x + _radius1 * cos(angle1), _base1.y, _base1.z + _radius1 * sin(angle1));
	//		Position v2(_base1.x + _radius1 * cos(angle2), _base1.y, _base1.z + _radius1 * sin(angle2));
	//		Position v3(_base2.x + _radius2 * cos(angle2), _base2.y, _base2.z + _radius2 * sin(angle2));
	//		Position v4(_base2.x + _radius2 * cos(angle1), _base2.y, _base2.z + _radius2 * sin(angle1));

	//		// Project vertices to 2D screen coordinates
	//		wxPoint p1 = Camera::projectTop(v1);
	//		wxPoint p2 = Camera::projectTop(v2);
	//		wxPoint p3 = Camera::projectTop(v3);
	//		wxPoint p4 = Camera::projectTop(v4);

	//		// Draw line connecting the vertices
	//		dc.DrawLine(p1.x, p1.y, p2.x, p2.y);
	//		dc.DrawLine(p2.x, p2.y, p3.x, p3.y);
	//		dc.DrawLine(p3.x, p3.y, p4.x, p4.y);
	//		dc.DrawLine(p4.x, p4.y, p1.x, p1.y);
	//	}
	//}
	//void draw_side(wxDC& dc) {
	//	dc.SetPen(wxPen(_color));
	//	dc.SetBrush(*wxTRANSPARENT_BRUSH);

	//	// Calculate the step angle
	//	double angle_step = 2 * M_PI / _n;

	//	// Iterate over each side of the cone
	//	for (int i = 0; i < _n; ++i) {
	//		// Calculate the current and next angles
	//		double angle1 = i * angle_step;
	//		double angle2 = (i + 1) * angle_step;

	//		// Calculate the vertices for the current and next sides
	//		Position v1(_base1.x + _radius1 * cos(angle1), _base1.y, _base1.z + _radius1 * sin(angle1));
	//		Position v2(_base2.x + _radius2 * cos(angle1), _base2.y, _base2.z + _radius2 * sin(angle1));
	//		Position v3(_base2.x + _radius2 * cos(angle2), _base2.y, _base2.z + _radius2 * sin(angle2));
	//		Position v4(_base1.x + _radius1 * cos(angle2), _base1.y, _base1.z + _radius1 * sin(angle2));

	//		// Project vertices to 2D screen coordinates
	//		wxPoint p1 = Camera::projectSide(v1);
	//		wxPoint p2 = Camera::projectSide(v2);
	//		wxPoint p3 = Camera::projectSide(v3);
	//		wxPoint p4 = Camera::projectSide(v4);

	//		// Draw quadrilateral
	//		dc.DrawLine(p1.x, p1.y, p2.x, p2.y);
	//		dc.DrawLine(p2.x, p2.y, p3.x, p3.y);
	//		dc.DrawLine(p3.x, p3.y, p4.x, p4.y);
	//		dc.DrawLine(p4.x, p4.y, p1.x, p1.y);
	//	}
	//}
	//void draw_perspective(wxDC& dc) {
	//	dc.SetPen(wxPen(_color));
	//	dc.SetBrush(*wxTRANSPARENT_BRUSH);

	//	// Calculate the step angle
	//	double angle_step = 2 * M_PI / _n;

	//	// Iterate over each side of the cone
	//	for (int i = 0; i < _n; ++i) {
	//		// Calculate the current and next angles
	//		double angle1 = i * angle_step;
	//		double angle2 = (i + 1) * angle_step;

	//		// Calculate the vertices for the current and next sides
	//		Position v1(_base1.x + _radius1 * cos(angle1), _base1.y, _base1.z + _radius1 * sin(angle1));
	//		Position v2(_base1.x + _radius1 * cos(angle2), _base1.y, _base1.z + _radius1 * sin(angle2));
	//		Position v3(_base2.x + _radius2 * cos(angle2), _base2.y, _base2.z + _radius2 * sin(angle2));
	//		Position v4(_base2.x + _radius2 * cos(angle1), _base2.y, _base2.z + _radius2 * sin(angle1));

	//		// Project vertices to 2D screen coordinates
	//		wxPoint p1 = Camera::projectPerspective(v1);
	//		wxPoint p2 = Camera::projectPerspective(v2);
	//		wxPoint p3 = Camera::projectPerspective(v3);
	//		wxPoint p4 = Camera::projectPerspective(v4);

	//		// Draw quadrilateral
	//		dc.DrawLine(p1.x, p1.y, p2.x, p2.y);
	//		dc.DrawLine(p2.x, p2.y, p3.x, p3.y);
	//		dc.DrawLine(p3.x, p3.y, p4.x, p4.y);
	//		dc.DrawLine(p4.x, p4.y, p1.x, p1.y);
	//	}
	//}

private:
	Position _base1;    // Base position 1
	double _radius1;    // Radius of base 1
	Position _base2;    // Base position 2
	double _radius2;    // Radius of base 2
	int _n;             // Number of quadrilaterals
};
