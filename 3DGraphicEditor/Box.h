#pragma once
#include "Drawable.h"
#include <vector>

/**
 * @brief A class representing a box object that can be drawn on a 2D canvas from different perspectives.
 */
class Box : public Drawable {
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
	Box(double x1, double y1, double z1, double x2, double y2, double z2, const wxColour& color = Drawable::penColor);

	/**
	 * @brief Constructs a box object with specified coordinates for two opposite corners.
	 * @param start - The position of the first corner.
	 * @param end - The position of the second corner.
	 * @param color - The color of the box.
	 */
	Box(const Position& start, const Position& end, const wxColour& color = Drawable::penColor);

	/**
	 * @brief Draws the box on four different 2D canvases representing different perspectives.
	 * @param dcFront - The device context for the front view.
	 * @param dcTop - The device context for the top view.
	 * @param dcSide - The device context for the side view.
	 * @param dcPerspective - The device context for the perspective view.
	 */
	void draw(wxDC& dcFront, wxDC& dcTop, wxDC& dcSide, wxDC& dcPerspective) override;

	std::string getInfo() const override {
		return "Box ";
	}

protected:
	void move(double xShift, double yShift, double zShift) override;
	void rotate(double xPivot, double yPivot, double zPivot, double alpha, double beta, double gamma) override;
	std::string save() const override;

private:
	std::vector<Position> _corners; ///< The positions of all eight corners of the box.

	/**
	 * @brief Draws the box corners on a 2D canvas using the provided projection function.
	 * @param dc - The device context for drawing.
	 * @param projectionFunc - The function to project 3D points to 2D points.
	 */
	void renderBox(wxDC& dc, wxPoint(*projectionFunc)(const Position&)) const;
};
