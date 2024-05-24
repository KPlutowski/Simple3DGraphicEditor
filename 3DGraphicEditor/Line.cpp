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
	move(-x_cord, -y_cord, -z_cord);

	std::vector<std::vector<double>> rotationMatrix = generate_rotation_matrix(alpha,beta,gamma);

	double sx = _start.x * rotationMatrix[0][0] + _start.y * rotationMatrix[0][1] + _start.z * rotationMatrix[0][2];
	double sy = _start.x * rotationMatrix[1][0] + _start.y * rotationMatrix[1][1] + _start.z * rotationMatrix[1][2];
	double sz = _start.x * rotationMatrix[2][0] + _start.y * rotationMatrix[2][1] + _start.z * rotationMatrix[2][2];
	
	double ex = _end.x * rotationMatrix[0][0] + _end.y * rotationMatrix[0][1] + _end.z * rotationMatrix[0][2];
	double ey = _end.x * rotationMatrix[1][0] + _end.y * rotationMatrix[1][1] + _end.z * rotationMatrix[1][2];
	double ez = _end.x * rotationMatrix[2][0] + _end.y * rotationMatrix[2][1] + _end.z * rotationMatrix[2][2];

	_start.x = sx;
	_start.y = sy;
	_start.z = sz;

	_end.x = ex;
	_end.y = ey;
	_end.z = ez;

	move(x_cord, y_cord, z_cord);
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
    // Compute camera direction
    Position camera_dir = {
        camera_look.x - camera_pos.x,
        camera_look.y - camera_pos.y,
        camera_look.z - camera_pos.z
    };

    // Normalize camera direction
    double length = sqrt(camera_dir.x * camera_dir.x + camera_dir.y * camera_dir.y + camera_dir.z * camera_dir.z);
    camera_dir.x /= length;
    camera_dir.y /= length;
    camera_dir.z /= length;

    // Convert field of view to radians
    double fov_rad = camera_fov * M_PI / 180.0;

    // Compute screen dimensions
    int screen_width = dc.GetSize().GetWidth();
    int screen_height = dc.GetSize().GetHeight();

    // Compute vertices positions in 3D
    double x1 = _start.x;
    double y1 = _start.y;
    double z1 = _start.z;

    double x2 = _end.x;
    double y2 = _end.y;
    double z2 = _end.z;

    // Compute vectors from camera to vertices
    double vec1_x = x1 - camera_pos.x;
    double vec1_y = y1 - camera_pos.y;
    double vec1_z = z1 - camera_pos.z;

    double vec2_x = x2 - camera_pos.x;
    double vec2_y = y2 - camera_pos.y;
    double vec2_z = z2 - camera_pos.z;

    // Compute dot products of camera direction and vectors to vertices
    double dot_product1 = vec1_x * camera_dir.x + vec1_y * camera_dir.y + vec1_z * camera_dir.z;
    double dot_product2 = vec2_x * camera_dir.x + vec2_y * camera_dir.y + vec2_z * camera_dir.z;

    // Apply perspective projection
    double projected_x1 = (screen_width / 2) + (vec1_x / (tan(fov_rad / 2) * dot_product1)) * (screen_width / 2);
    double projected_y1 = (screen_height / 2) - (vec1_y / (tan(fov_rad / 2) * dot_product1)) * (screen_height / 2);

    double projected_x2 = (screen_width / 2) + (vec2_x / (tan(fov_rad / 2) * dot_product2)) * (screen_width / 2);
    double projected_y2 = (screen_height / 2) - (vec2_y / (tan(fov_rad / 2) * dot_product2)) * (screen_height / 2);

    // Draw line
    dc.SetPen(wxPen(_color));
    dc.DrawLine(projected_x1, projected_y1, projected_x2, projected_y2);
}

void Line::draw(wxDC& dc1, wxDC& dc2, wxDC& dc3, wxDC& dc4)
{
	draw_front(dc1);
	draw_top(dc2);
	draw_side(dc3);
	draw_perspective(dc4);
}


