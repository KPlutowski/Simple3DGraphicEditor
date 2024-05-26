#include "Box.h"

Box::Box(double x1, double y1, double z1, double x2, double y2, double z2, const wxColour& color) :Box(Position(x1, y1, z1), Position(x2, y2, z2), color) {};
Box::Box(const Position& start, const Position& end, const wxColour& color) : Drawable(color)
{
	_corners.push_back(start); // 1 (0, 0, 0)
	_corners.push_back(Position(end.x, start.y, start.z)); // 2 (100, 0, 0)
	_corners.push_back(Position(end.x, start.y, end.z)); // 3 (100, 0, 200)
	_corners.push_back(Position(start.x, start.y, end.z)); // 4 (0, 0, 200)
	_corners.push_back(Position(start.x, end.y, start.z)); // 5 (0, 150, 0)
	_corners.push_back(Position(end.x, end.y, start.z)); // 6 (100, 150, 0)
	_corners.push_back(end); // 7 (100, 150, 200)
	_corners.push_back(Position(start.x, end.y, end.z)); // 8 (0, 150, 200)
}

void Box::rotate(double x_cord, double y_cord, double z_cord, double alpha, double beta, double gamma) {
	move(-x_cord, -y_cord, -z_cord);

	std::vector<std::vector<double>> rotationMatrix = generate_rotation_matrix(alpha, beta, gamma);

	for (auto& corner : _corners)
	{
		double x = corner.x * rotationMatrix[0][0] + corner.y * rotationMatrix[0][1] + corner.z * rotationMatrix[0][2];
		double y = corner.x * rotationMatrix[1][0] + corner.y * rotationMatrix[1][1] + corner.z * rotationMatrix[1][2];
		double z = corner.x * rotationMatrix[2][0] + corner.y * rotationMatrix[2][1] + corner.z * rotationMatrix[2][2];
		corner.x = x;
		corner.y = y;
		corner.z = z;
	}

	move(x_cord, y_cord, z_cord);
}

void Box::move(double x_shift, double y_shift, double z_shift) {
	for (auto& corner : _corners)
	{
		corner.x += x_shift;
		corner.y += y_shift;
		corner.z += z_shift;
	}
}

void Box::draw_front(wxDC& dc) {
	dc.SetPen(wxPen(_color));
	dc.SetBrush(*wxTRANSPARENT_BRUSH);

	std::vector<wxPoint> projectedCorners;
	for (const auto& corner : _corners) {
		projectedCorners.push_back(Camera::projectFront(corner));
	}

	// Draw lines connecting the points to form the box
	dc.DrawLine(projectedCorners[0].x, projectedCorners[0].y, projectedCorners[1].x, projectedCorners[1].y);
	dc.DrawLine(projectedCorners[1].x, projectedCorners[1].y, projectedCorners[2].x, projectedCorners[2].y);
	dc.DrawLine(projectedCorners[2].x, projectedCorners[2].y, projectedCorners[3].x, projectedCorners[3].y);
	dc.DrawLine(projectedCorners[3].x, projectedCorners[3].y, projectedCorners[0].x, projectedCorners[0].y);
	dc.DrawLine(projectedCorners[4].x, projectedCorners[4].y, projectedCorners[5].x, projectedCorners[5].y);
	dc.DrawLine(projectedCorners[5].x, projectedCorners[5].y, projectedCorners[6].x, projectedCorners[6].y);
	dc.DrawLine(projectedCorners[6].x, projectedCorners[6].y, projectedCorners[7].x, projectedCorners[7].y);
	dc.DrawLine(projectedCorners[7].x, projectedCorners[7].y, projectedCorners[4].x, projectedCorners[4].y);
	dc.DrawLine(projectedCorners[0].x, projectedCorners[0].y, projectedCorners[4].x, projectedCorners[4].y);
	dc.DrawLine(projectedCorners[1].x, projectedCorners[1].y, projectedCorners[5].x, projectedCorners[5].y);
	dc.DrawLine(projectedCorners[2].x, projectedCorners[2].y, projectedCorners[6].x, projectedCorners[6].y);
	dc.DrawLine(projectedCorners[3].x, projectedCorners[3].y, projectedCorners[7].x, projectedCorners[7].y);
}

void Box::draw_top(wxDC& dc) {
	dc.SetPen(wxPen(_color));
	dc.SetBrush(*wxTRANSPARENT_BRUSH);

	std::vector<wxPoint> projectedCorners;
	for (const auto& corner : _corners) {
		projectedCorners.push_back(Camera::projectTop(corner));
	}

	// Draw lines connecting the points to form the box
	dc.DrawLine(projectedCorners[0].x, projectedCorners[0].y, projectedCorners[1].x, projectedCorners[1].y);
	dc.DrawLine(projectedCorners[1].x, projectedCorners[1].y, projectedCorners[2].x, projectedCorners[2].y);
	dc.DrawLine(projectedCorners[2].x, projectedCorners[2].y, projectedCorners[3].x, projectedCorners[3].y);
	dc.DrawLine(projectedCorners[3].x, projectedCorners[3].y, projectedCorners[0].x, projectedCorners[0].y);
	dc.DrawLine(projectedCorners[4].x, projectedCorners[4].y, projectedCorners[5].x, projectedCorners[5].y);
	dc.DrawLine(projectedCorners[5].x, projectedCorners[5].y, projectedCorners[6].x, projectedCorners[6].y);
	dc.DrawLine(projectedCorners[6].x, projectedCorners[6].y, projectedCorners[7].x, projectedCorners[7].y);
	dc.DrawLine(projectedCorners[7].x, projectedCorners[7].y, projectedCorners[4].x, projectedCorners[4].y);
	dc.DrawLine(projectedCorners[0].x, projectedCorners[0].y, projectedCorners[4].x, projectedCorners[4].y);
	dc.DrawLine(projectedCorners[1].x, projectedCorners[1].y, projectedCorners[5].x, projectedCorners[5].y);
	dc.DrawLine(projectedCorners[2].x, projectedCorners[2].y, projectedCorners[6].x, projectedCorners[6].y);
	dc.DrawLine(projectedCorners[3].x, projectedCorners[3].y, projectedCorners[7].x, projectedCorners[7].y);
}

void Box::draw_side(wxDC& dc) {
	dc.SetPen(wxPen(_color));
	dc.SetBrush(*wxTRANSPARENT_BRUSH);

	std::vector<wxPoint> projectedCorners;
	for (const auto& corner : _corners) {
		projectedCorners.push_back(Camera::projectSide(corner));
	}

	// Draw lines connecting the points to form the box
	dc.DrawLine(projectedCorners[0].x, projectedCorners[0].y, projectedCorners[1].x, projectedCorners[1].y);
	dc.DrawLine(projectedCorners[1].x, projectedCorners[1].y, projectedCorners[2].x, projectedCorners[2].y);
	dc.DrawLine(projectedCorners[2].x, projectedCorners[2].y, projectedCorners[3].x, projectedCorners[3].y);
	dc.DrawLine(projectedCorners[3].x, projectedCorners[3].y, projectedCorners[0].x, projectedCorners[0].y);
	dc.DrawLine(projectedCorners[4].x, projectedCorners[4].y, projectedCorners[5].x, projectedCorners[5].y);
	dc.DrawLine(projectedCorners[5].x, projectedCorners[5].y, projectedCorners[6].x, projectedCorners[6].y);
	dc.DrawLine(projectedCorners[6].x, projectedCorners[6].y, projectedCorners[7].x, projectedCorners[7].y);
	dc.DrawLine(projectedCorners[7].x, projectedCorners[7].y, projectedCorners[4].x, projectedCorners[4].y);
	dc.DrawLine(projectedCorners[0].x, projectedCorners[0].y, projectedCorners[4].x, projectedCorners[4].y);
	dc.DrawLine(projectedCorners[1].x, projectedCorners[1].y, projectedCorners[5].x, projectedCorners[5].y);
	dc.DrawLine(projectedCorners[2].x, projectedCorners[2].y, projectedCorners[6].x, projectedCorners[6].y);
	dc.DrawLine(projectedCorners[3].x, projectedCorners[3].y, projectedCorners[7].x, projectedCorners[7].y);
}

void Box::draw_perspective(wxDC& dc) {
	dc.SetPen(wxPen(_color));
	dc.SetBrush(*wxTRANSPARENT_BRUSH);

	// Project and draw all corners
	std::vector<wxPoint> projected_corners;
	for (const auto& corner : _corners) {
		projected_corners.push_back(Camera::projectPerspective(corner));
	}

	// Draw lines
	dc.DrawLine(projected_corners[0], projected_corners[1]);
	dc.DrawLine(projected_corners[1], projected_corners[2]);
	dc.DrawLine(projected_corners[2], projected_corners[3]);
	dc.DrawLine(projected_corners[3], projected_corners[0]);
	dc.DrawLine(projected_corners[4], projected_corners[5]);
	dc.DrawLine(projected_corners[5], projected_corners[6]);
	dc.DrawLine(projected_corners[6], projected_corners[7]);
	dc.DrawLine(projected_corners[7], projected_corners[4]);
	dc.DrawLine(projected_corners[0], projected_corners[4]);
	dc.DrawLine(projected_corners[1], projected_corners[5]);
	dc.DrawLine(projected_corners[2], projected_corners[6]);
	dc.DrawLine(projected_corners[3], projected_corners[7]);
}

void Box::draw(wxDC& dc1, wxDC& dc2, wxDC& dc3, wxDC& dc4)
{
	draw_front(dc1);
	draw_top(dc2);
	draw_side(dc3);
	draw_perspective(dc4);
}

std::string Box::save() const
{
	std::string result = "Box "
		+ std::to_string(_corners[0].x) + " " + std::to_string(_corners[0].y) + " " + std::to_string(_corners[0].z) + " "
		+ std::to_string(_corners[6].x) + " " + std::to_string(_corners[6].y) + " " + std::to_string(_corners[6].z) + " "
		+ std::to_string(_color.GetRGB()) + "\n";
	return result;
}