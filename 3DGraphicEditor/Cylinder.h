#pragma once
#include "DrawableObject.h"
#include "Cone.h"

class Cylinder : public Cone
{
public:
	/**
	 * @brief Constructs a Cylinder object with specified parameters.
	 * @param base1 The position of the first base.
	 * @param radius1 The radius of the first base.
	 * @param base2 The position of the second base.
	 * @param radius2 The radius of the second base.
	 * @param sides The number of sides.
	 * @param color The color of the cone.
	 */
	Cylinder(const Position& base1, double radius1, const Position& base2, double radius2, int sides, const wxColour& color = DrawableObject::penColor, const std::vector<Position>& vertices = {});

	/**
	 * @brief Constructs a Cylinder object with specified parameters.
	 * @param x1 The X-coordinate of the first base.
	 * @param y1 The Y-coordinate of the first base.
	 * @param z1 The Z-coordinate of the first base.
	 * @param radius1 The radius of the first base.
	 * @param x2 The X-coordinate of the second base.
	 * @param y2 The Y-coordinate of the second base.
	 * @param z2 The Z-coordinate of the second base.
	 * @param radius2 The radius of the second base.
	 * @param sides The number of sides.
	 * @param color The color of the cone.
	 */
	Cylinder(double x1, double y1, double z1, double radius1, double x2, double y2, double z2, double radius2, int sides, wxColour color = DrawableObject::penColor, const std::vector<Position>& vertices = {});

	/**
	 * @brief Saves the cylinder's data to a string.
	 * @return A string representation of the cylinder's data.
	 */
	std::string save() const override;
};
