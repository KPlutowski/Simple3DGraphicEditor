#include <vector>
#include <fstream>
#include <sstream>
#include <wx/timer.h>
#include "GUIMyFrame1.h"
#include <algorithm>
#include <wx/dcbuffer.h>
#include <wx/init.h>
#include "Position.h"

Position::Position(double a, double b, double c) { x = a, y = b, z = c; }

std::string Position::toString() const
{
	return "(" + std::to_string((int)x) + "," + std::to_string((int)y) + "," + std::to_string((int)z) + ")";
}

Position Position::operator-(const Position& other) const {
	return Position(x - other.x, y - other.y, z - other.z);
}

Position Position::operator+(const Position& other) const {
	return Position(x + other.x, y + other.y, z + other.z);
}

Position Position::fromString(const std::string& str) {
	std::vector<double> pos_value;
	std::string text;
	for (auto i : str) {
		if (i == '(' || i == ' ') {
			continue;
		}
		else if (i == ',' || i == ')') {
			pos_value.push_back(std::stod(text));
			text.clear();
		}

		else {
			text += i;
		}
	}
	return Position(pos_value[0], pos_value[1], pos_value[2]);
}

void Position::shift(double x_shift, double y_shift, double z_shift)
{
	x += x_shift;
	y += y_shift;
	z += z_shift;
}

void Position::rotate(const Position& center, double alpha, double beta, double gamma)
{
	const double cosAlpha = cos(alpha * M_PI / 180.0);
	const double sinAlpha = sin(alpha * M_PI / 180.0);
	const double cosBeta = cos(beta * M_PI / 180.0);
	const double sinBeta = sin(beta * M_PI / 180.0);
	const double cosGamma = cos(gamma * M_PI / 180.0);
	const double sinGamma = sin(gamma * M_PI / 180.0);

	shift(-center.x, -center.y, -center.z);

	const double xNew = cosBeta * cosGamma * x + (cosAlpha * sinGamma + sinAlpha * sinBeta * cosGamma) * y + (sinAlpha * sinGamma - cosAlpha * sinBeta * cosGamma) * z;
	const double yNew = -cosBeta * sinGamma * x + (cosAlpha * cosGamma - sinAlpha * sinBeta * sinGamma) * y + (sinAlpha * cosGamma + cosAlpha * sinBeta * sinGamma) * z;
	const double zNew = sinBeta * x - sinAlpha * cosBeta * y + cosAlpha * cosBeta * z;
	x = xNew;
	y = yNew;
	z = zNew;

	shift(center.x, center.y, center.z);
}