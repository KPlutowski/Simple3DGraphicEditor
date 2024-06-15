#pragma once
#include <vector>
#include "GUIMyFrame1.h"
#include "DrawableObject.h"

/**
 * @brief A class representing a sphere object that can be drawn on a 2D canvas from different perspectives.
 */
class Sphere : public DrawableObject {
public:
	/**
	 * @brief Constructs a sphere object.
	 * @param x - The X-coordinate of the center of the sphere.
	 * @param y - The Y-coordinate of the center of the sphere.
	 * @param z - The Z-coordinate of the center of the sphere.
	 * @param radius - The radius of the sphere.
	 * @param numMeridians - The number of meridians (longitudes) used to divide the sphere.
	 * @param numParallels - The number of parallels (latitudes) used to divide the sphere.
	 * @param color - The color of the sphere.
	 */
	Sphere(double x, double y, double z, double radius, int numMeridians, int numParallels, const wxColour& color = DrawableObject::penColor, const std::vector<Position>& vertices = {});

	/**
	 * @brief Constructs a sphere object.
	 * @param center - The coordinates of the center of the sphere.
	 * @param radius - The radius of the sphere.
	 * @param numMeridians - The number of meridians (longitudes) used to divide the sphere.
	 * @param numParallels - The number of parallels (latitudes) used to divide the sphere.
	 * @param color - The color of the sphere.
	 */
	Sphere(const Position& center, double radius, int numMeridians, int numParallels, const wxColour& color = DrawableObject::penColor, const std::vector<Position>& vertices = {});

	/**
	 * @brief Saves the sphere's data to a string.
	 * @return A string representation of the sphere's data.
	 */
	std::string save() const override;
protected:
	/**
	 * @brief Draws the sphere on a 2D canvas using the provided projection function.
	 * @param dc - The device context for drawing.
	 * @param projectionFunc - The function to project 3D points to 2D points.
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

private:
	double _radius;        ///< The radius of the sphere.
	int _numMeridians;     ///< The number of meridians (longitudes).
	int _numParallels;     ///< The number of parallels (latitudes).
	Position _center;      ///< The center position of the sphere.

	/**
	 * @brief Computes the vertices of the sphere.
	 */
	void computeVertices() override;
};
