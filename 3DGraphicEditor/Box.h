#pragma once

#include "DrawableObject.h"
#include <vector>
#include <string>

/**
 * @brief A class representing a box object that can be drawn on a 2D canvas from different perspectives.
 */
class Box : public DrawableObject {
public:
	/**
	 * @brief Constructs a box object with specified coordinates for two opposite corners.
	 * @param x1 - The X-coordinate of the first corner.
	 * @param y1 - The Y-coordinate of the first corner.
	 * @param z1 - The Z-coordinate of the first corner.
	 * @param x2 - The X-coordinate of the second corner.
	 * @param y2 - The Y-coordinate of the second corner.
	 * @param z2 - The Z-coordinate of the second corner.
	 * @param color - The color of the box.
	 */
	Box(double x1, double y1, double z1, double x2, double y2, double z2, const wxColour& color = DrawableObject::penColor, const std::vector<Position>& vertices = {});

	/**
	 * @brief Constructs a box object with specified coordinates for two opposite corners.
	 * @param start - The position of the first corner.
	 * @param end - The position of the second corner.
	 * @param color - The color of the box.
	 */
	Box(const Position& start, const Position& end, const wxColour& color = DrawableObject::penColor, const std::vector<Position>& vertices = {});

	/**
	 * @brief Returns information about the box.
	 * @return A string containing the type of the object.
	 */
	std::string getInfo() const override;

	/**
	 * @brief Saves the box's data to a string.
	 * @return A string representation of the box's data.
	 */
	std::string save() const override;

protected:
	/**
	 * @brief Draws the box on a 2D canvas using the provided projection function.
	 * @param dc - The device context for drawing.
	 * @param projectionFunc - The function to project 3D points to 2D points.
	 */
	void render(wxDC& dc, wxPoint(*projectionFunc)(const Position&)) const override;

private:
	Position _start; ///< The start position of the box (one corner).
	Position _end;   ///< The end position of the box (opposite corner).

	/**
	 * @brief Computes the vertices of the box.
	 */
	void computeVertices() override;
};
