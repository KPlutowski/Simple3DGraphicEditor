#pragma once
#include <vector>
#include "GUIMyFrame1.h"
#include "Drawable.h"

/**
 * @brief A class representing a sphere object that can be drawn on a 2D canvas from different perspectives.
 */
class Sphere : public Drawable {
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
	Sphere(double x, double y, double z, double radius, int numMeridians, int numParallels, const wxColour& color = Drawable::penColor);

	/**
	 * @brief Constructs a sphere object.
	 * @param center - The coordinates of the center of the sphere.
	 * @param radius - The radius of the sphere.
	 * @param numMeridians - The number of meridians (longitudes) used to divide the sphere.
	 * @param numParallels - The number of parallels (latitudes) used to divide the sphere.
	 * @param color - The color of the sphere.
	 */
	Sphere(const Position& center, double radius, int numMeridians, int numParallels, const wxColour& color = Drawable::penColor);

	/**
	 * @brief Draws the sphere on four different 2D canvases representing different perspectives.
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
	double _radius;        ///< The radius of the sphere.
	int _numMeridians;     ///< The number of meridians (longitudes).
	int _numParallels;     ///< The number of parallels (latitudes).

	// Rotation angles
	double _alpha = 0;
	double _beta = 0;
	double _gamma = 0;

	Position _center;      ///< The center position of the sphere.

	/**
	 * @brief Rotates a point around a given center by specified Euler angles.
	 * @param point - The point to rotate.
	 * @param center - The center of rotation.
	 * @param alpha - The rotation angle around the X-axis in degrees.
	 * @param beta - The rotation angle around the Y-axis in degrees.
	 * @param gamma - The rotation angle around the Z-axis in degrees.
	 * @return The rotated position.
	 */
	Position rotatePoint(const Position& point, const Position& center, double alpha, double beta, double gamma) const;

	/**
	 * @brief Computes the vertex position for given spherical coordinates.
	 * @param phi - The angle of the parallel (latitude) in radians.
	 * @param lambda - The angle of the meridian (longitude) in radians.
	 * @return The computed vertex position.
	 */
	Position computeVertex(double phi, double lambda) const;

	/**
	 * @brief Rotates a vertex based on the sphere's current rotation angles.
	 * @param vertex - The vertex to rotate.
	 * @return The rotated vertex position.
	 */
	Position rotateVertex(const Position& vertex) const;

	/**
	 * @brief Draws the sphere on a 2D canvas using the provided projection function.
	 * @param dc - The device context for drawing.
	 * @param projectionFunc - The function to project 3D points to 2D points.
	 */
	void renderSphere(wxDC& dc, wxPoint(*projectionFunc)(const Position&)) const;
};
