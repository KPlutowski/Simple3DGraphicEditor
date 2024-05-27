#include "Box.h"

Box::Box(double x1, double y1, double z1, double x2, double y2, double z2, const wxColour& color)
	: Box(Position(x1, y1, z1), Position(x2, y2, z2), color) {}

Box::Box(const Position& start, const Position& end, const wxColour& color)
	: Drawable(color) {
	_corners.push_back(start); // 1 (0, 0, 0)
	_corners.push_back(Position(end.x, start.y, start.z)); // 2 (x2, y1, z1)
	_corners.push_back(Position(end.x, start.y, end.z)); // 3 (x2, y1, z2)
	_corners.push_back(Position(start.x, start.y, end.z)); // 4 (x1, y1, z2)
	_corners.push_back(Position(start.x, end.y, start.z)); // 5 (x1, y2, z1)
	_corners.push_back(Position(end.x, end.y, start.z)); // 6 (x2, y2, z1)
	_corners.push_back(end); // 7 (x2, y2, z2)
	_corners.push_back(Position(start.x, end.y, end.z)); // 8 (x1, y2, z2)
}

void Box::move(double xShift, double yShift, double zShift) {
	for (auto& corner : _corners) {
		corner.shift(xShift, yShift, zShift);
	}
}

void Box::rotate(double xPivot, double yPivot, double zPivot, double alpha, double beta, double gamma) {
	// Move box to origin for rotation
	move(-xPivot, -yPivot, -zPivot);

	std::vector<std::vector<double>> rotationMatrix = generateRotationMatrix(alpha, beta, gamma);

	for (auto& corner : _corners) {
		double x = corner.x * rotationMatrix[0][0] + corner.y * rotationMatrix[0][1] + corner.z * rotationMatrix[0][2];
		double y = corner.x * rotationMatrix[1][0] + corner.y * rotationMatrix[1][1] + corner.z * rotationMatrix[1][2];
		double z = corner.x * rotationMatrix[2][0] + corner.y * rotationMatrix[2][1] + corner.z * rotationMatrix[2][2];
		corner.x = x;
		corner.y = y;
		corner.z = z;
	}

	// Move box back to its original position
	move(xPivot, yPivot, zPivot);
}

void Box::draw(wxDC& dcFront, wxDC& dcTop, wxDC& dcSide, wxDC& dcPerspective) {
	// Draw box in different views
	renderBox(dcFront, Camera::projectFront);
	renderBox(dcTop, Camera::projectTop);
	renderBox(dcSide, Camera::projectSide);
	renderBox(dcPerspective, Camera::projectPerspective);
}

void Box::renderBox(wxDC& dc, wxPoint(*projectionFunc)(const Position&)) const {
	std::vector<wxPoint> projectedCorners;
	for (const auto& corner : _corners) {
		projectedCorners.push_back(projectionFunc(corner));
	}

	dc.DrawLine(projectedCorners[0], projectedCorners[1]);
	dc.DrawLine(projectedCorners[1], projectedCorners[2]);
	dc.DrawLine(projectedCorners[2], projectedCorners[3]);
	dc.DrawLine(projectedCorners[3], projectedCorners[0]);
	dc.DrawLine(projectedCorners[4], projectedCorners[5]);
	dc.DrawLine(projectedCorners[5], projectedCorners[6]);
	dc.DrawLine(projectedCorners[6], projectedCorners[7]);
	dc.DrawLine(projectedCorners[7], projectedCorners[4]);
	dc.DrawLine(projectedCorners[0], projectedCorners[4]);
	dc.DrawLine(projectedCorners[1], projectedCorners[5]);
	dc.DrawLine(projectedCorners[2], projectedCorners[6]);
	dc.DrawLine(projectedCorners[3], projectedCorners[7]);
}

std::string Box::save() const {
	std::string result = "Box "
		+ std::to_string(_corners[0].x) + " " + std::to_string(_corners[0].y) + " " + std::to_string(_corners[0].z) + " "
		+ std::to_string(_corners[6].x) + " " + std::to_string(_corners[6].y) + " " + std::to_string(_corners[6].z) + " "
		+ std::to_string(_color.GetRGB()) + "\n";
	return result;
}