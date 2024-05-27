#pragma once

#include <vector>
#include "GUIMyFrame1.h"
#include "Drawable.h"

/**
 * @brief A class representing a line object that can be drawn on a 2D canvas from different perspectives.
 */
class Line : public Drawable {
public:
	/**
	 * @brief Constructs a line object with specified coordinates for its start and end points.
	 * @param x1 - The X-coordinate of the start point.
	 * @param y1 - The Y-coordinate of the start point.
	 * @param z1 - The Z-coordinate of the start point.
	 * @param x2 - The X-coordinate of the end point.
	 * @param y2 - The Y-coordinate of the end point.
	 * @param z2 - The Z-coordinate of the end point.
	 * @param color - The color of the line.
	 */
	Line(double x1, double y1, double z1, double x2, double y2, double z2, wxColour color = Drawable::penColor);

	/**
	 * @brief Constructs a line object with specified start and end positions.
	 * @param start - The start position of the line.
	 * @param end - The end position of the line.
	 * @param color - The color of the line.
	 */
	Line(Position start, Position end, wxColour color = Drawable::penColor);

	/**
	 * @brief Gets the start position of the line.
	 * @return The start position of the line.
	 */
	Position getStart() const;

	/**
	 * @brief Sets the start position of the line.
	 * @param newStart - The new start position of the line.
	 */
	void setStart(const Position& newStart);

	/**
	 * @brief Gets the end position of the line.
	 * @return The end position of the line.
	 */
	Position getEnd() const;

	/**
	 * @brief Sets the end position of the line.
	 * @param newEnd - The new end position of the line.
	 */
	void setEnd(const Position& newEnd);

	/**
	 * @brief Draws the line on four different 2D canvases representing different perspectives.
	 * @param dcFront - The device context for the front view.
	 * @param dcTop - The device context for the top view.
	 * @param dcSide - The device context for the side view.
	 * @param dcPerspective - The device context for the perspective view.
	 */
	void draw(wxDC& dcFront, wxDC& dcTop, wxDC& dcSide, wxDC& dcPerspective) override;

	std::string getInfo() const override;

protected:
	void move(double xShift, double yShift, double zShift) override;
	void rotate(double xPivot, double yPivot, double zPivot, double alpha, double beta, double gamma) override;
	std::string save() const override;

private:
	Position _start; ///< The start position of the line.
	Position _end; ///< The end position of the line.

	/**
	 * @brief Draws the line on a 2D canvas using the provided projection function.
	 * @param dc - The device context for drawing.
	 * @param projectionFunc - The function to project 3D points to 2D points.
	 */
	void renderLine(wxDC& dc, wxPoint(*projectionFunc)(const Position&)) const;
};