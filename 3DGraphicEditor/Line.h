#pragma once

#include <vector>
#include "GUIMyFrame1.h"
#include "DrawableObject.h"

/**
 * @brief A class representing a line object that can be drawn on a 2D canvas from different perspectives.
 */
class Line : public DrawableObject {
public:
	/**
	 * @brief Constructs a line object with specified coordinates for its start and end points.
	 * @param x1 - The X-coordinate of the start point.
	 * @param y1 - The Y-coordinate of the start point.
	 * @param z1 - The Z-coordinate of the start point.
	 * @param x2 - The X-coordinate of the end point.
	 * @param y2 - The Y-coordinate of the end point.
	 * @param z2 - The Z-coordinate of the end point.
	 * @param color - The color of the line. Defaults to Drawable::penColor.
	 */
	Line(double x1, double y1, double z1, double x2, double y2, double z2, wxColour color = DrawableObject::penColor, const std::vector<Position>& vertices = {});

	/**
	 * @brief Constructs a line object with specified start and end positions.
	 * @param start - The start position of the line.
	 * @param end - The end position of the line.
	 * @param color - The color of the line. Defaults to Drawable::penColor.
	 */
	Line(Position start, Position end, wxColour color = DrawableObject::penColor, const std::vector<Position>& vertices = {});

	/**
	 * @brief Provides information about the line object.
	 * @return A string containing the line's start and end positions.
	 */
	std::string getInfo() const override;

	/**
	 * @brief Saves the line's data to a string.
	 * @return A string representation of the line's data.
	 */
	std::string save() const override;
protected:
	/**
	 * @brief Renders the line on a given device context using a projection function.
	 * @param dc - The device context to draw on.
	 * @param projectionFunc - The function to project 3D coordinates to 2D points.
	 */
	void render(wxDC& dc, wxPoint(*projectionFunc)(const Position&)) const override;

private:
	Position _start; ///< The start position of the line.
	Position _end; ///< The end position of the line.

	/**
	 * @brief Computes the vertices of the line.
	 */
	void computeVertices() override;
};
