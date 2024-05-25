#include <vector>
#include "GUIMyFrame1.h"
#include "Drawable.h"
#include "Line.h"

Line::Line(double x1, double y1, double z1, double x2, double y2, double z2, wxColour color) : _start(x1, y1, z1), _end(x2, y2, z2), _color(color) {}
Line::Line(Position start, Position end, wxColour color) : Line(start.x, start.y, start.z,end.x, end.y, end.z, color){}


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
	//TODO
	dc.SetPen(wxPen(_color));
	dc.SetBrush(*wxTRANSPARENT_BRUSH);

	dc.DrawLine(_start.x, panel_height-_start.y, _end.x, panel_height-_end.y);
}

void Line::draw_top(wxDC& dc) {
	//TODO
	dc.SetPen(wxPen(_color));
	dc.SetBrush(*wxTRANSPARENT_BRUSH);

	dc.DrawLine(_start.x, panel_height - _start.z-1, _end.x, panel_height - _end.z-1);
}

void Line::draw_side(wxDC& dc) {
	//TODO
	dc.SetPen(wxPen(_color));
	dc.SetBrush(*wxTRANSPARENT_BRUSH);

	dc.DrawLine(_start.z, panel_height - _start.y-1, _end.z, panel_height - _end.y-1);
}

void Line::draw_perspective(wxDC& dc) {
	dc.SetPen(wxPen(_color));
	dc.SetBrush(*wxTRANSPARENT_BRUSH);

	double aspect_ratio = panel_width / panel_height;

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

	// Compute right vector
	Position rightVec = {
		camera_dir.y * 0 - camera_dir.z * 1,
		camera_dir.z * 0 - camera_dir.x * 0,
		camera_dir.x * 1 - camera_dir.y * 0 
	};

	// Normalize right vector
	length = sqrt(rightVec.x * rightVec.x + rightVec.y * rightVec.y + rightVec.z * rightVec.z);
	rightVec.x /= length;
	rightVec.y /= length;
	rightVec.z /= length;

	// Compute up vector
	double up_x = rightVec.y * camera_dir.z - rightVec.z * camera_dir.y;
	double up_y = rightVec.z * camera_dir.x - rightVec.x * camera_dir.z;
	double up_z = rightVec.x * camera_dir.y - rightVec.y * camera_dir.x;

	// Field of view and projection parameters
	double near_plane = 1.0; // Distance to near clipping plane
	double far_plane = 1000.0; // Distance to far clipping plane
	double fov_rad = camera_fov * (M_PI / 180.0);
	double tan_fov = tan(fov_rad / 2.0);

	// Project a 3D point to 2D screen space
	auto project = [&](const Position& pos) -> wxPoint {
		// Transform the point to camera space
		double px = pos.x - camera_pos.x;
		double py = pos.y - camera_pos.y;
		double pz = pos.z - camera_pos.z;

		// Apply rotation (camera orientation)
		double cam_x = px * rightVec.x + py * rightVec.y + pz * rightVec.z;
		double cam_y = px * up_x + py * up_y + pz * up_z;
		double cam_z = px * camera_dir.x + py * camera_dir.y + pz * camera_dir.z;

		// Perspective projection
		double screen_x = (cam_x / (cam_z * tan_fov * aspect_ratio)) * (panel_width / 2) + (panel_width / 2);
		double screen_y = (cam_y / (cam_z * tan_fov)) * (panel_height / 2) + (panel_height / 2);

		return wxPoint(screen_x, panel_height - screen_y); // Flip y-axis for drawing
	};

	// Project the start and end points of the line
	wxPoint start_2d = project(_start);
	wxPoint end_2d = project(_end);

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
		+ std::to_string(_color.GetRGB()) +"\n";
	return result;
}
