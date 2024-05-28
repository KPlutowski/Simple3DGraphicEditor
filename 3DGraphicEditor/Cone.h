#pragma once
#include "Drawable.h"

/**
 * @brief A class representing a cone object that can be drawn on a 2D canvas.
 */
class Cone :public Drawable
{
public:
	/**
	 * @brief Constructs a cone object with specified parameters.
	 * @param base1 The position of the first base.
	 * @param radius1 The radius of the first base.
	 * @param base2 The position of the second base.
	 * @param radius2 The radius of the second base.
	 * @param sides The number of sides.
	 * @param color The color of the cone.
	 */
	Cone(const Position& base1, double radius1, const Position& base2, double radius2, int sides, const wxColour& color = Drawable::penColor, const std::vector<Position>& vertices = {});

	/**
	 * @brief Constructs a cone object with specified parameters.
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
	Cone(double x1, double y1, double z1, double radius1, double x2, double y2, double z2, double radius2, int sides, wxColour color = Drawable::penColor, const std::vector<Position>& vertices = {});

	/**
	 * @brief Saves the cone's data to a string.
	 * @return A string representation of the cone's data.
	 */
	std::string save() const override;

	/**
	 * @brief Returns information about the cone.
	 * @return A string containing the type of the object.
	 */
	std::string getInfo() const override;

protected:

	/**
	 * @brief Draws the cone on a 2D canvas using the provided projection function.
	 * @param dc The device context for drawing.
	 * @param projectionFunc The function to project 3D points to 2D points.
	 */
	void render(wxDC& dc, wxPoint(*projectionFunc)(const Position&)) const override;

	/**
	 * @brief Rotates the sphere around the specified pivot point.
	 * @details This method rotates the sphere around the specified pivot point by the specified angles.
	 *
	 * @param xPivot The X-coordinate of the pivot point.
	 * @param yPivot The Y-coordinate of the pivot point.
	 * @param zPivot The Z-coordinate of the pivot point.
	 * @param alpha The rotation angle around the X-axis, in degrees.
	 * @param beta The rotation angle around the Y-axis, in degrees.
	 * @param gamma The rotation angle around the Z-axis, in degrees.
	 */
	void rotate(double xPivot, double yPivot, double zPivot, double alpha, double beta, double gamma) override;
	
	Position _base1;        ///< The position of the first base.
	double _baseRadius1;    ///< The radius of the first base.
	Position _base2;        ///< The position of the second base.
	double _baseRadius2;    ///< The radius of the second base.
	int _sides;             ///< The number of sides.

	/**
	 * @brief Computes the vertices of the cone.
	 */
	void computeVertices() override;

};
