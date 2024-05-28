#include "Cylinder.h"

Cylinder::Cylinder(const Position& base1, double radius1, const Position& base2, double radius2, int sides, const wxColour& color, const std::vector<Position>& vertices)
	:Cone(base1, radius1, base2, radius2, sides, color, vertices)
{
	_type = "Cylinder";
}

Cylinder::Cylinder(double x1, double y1, double z1, double radius1, double x2, double y2, double z2, double radius2, int sides, wxColour color, const std::vector<Position>& vertices)
	: Cylinder(Position(x1, y1, z1), radius1, Position(x2, y2, z2), radius2, sides, color, vertices) {}

std::string Cylinder::getInfo() const
{
	return "Cylinder";
}

std::string Cylinder::save() const
{
	std::string toSave;

	toSave += Drawable::save();

	toSave += _base1.toString() + " " + std::to_string(_baseRadius1) + " ";
	toSave += _base2.toString() + " " + std::to_string(_baseRadius2) + " ";
	toSave += std::to_string(_sides) + "\n";

	return  toSave;
}