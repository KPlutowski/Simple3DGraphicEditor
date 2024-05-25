#pragma once
#include <vector>
#include "GUIMyFrame1.h"
#include "Drawable.h"

/**
 * @brief A class representing a sphere object that can be drawn on a 2D canvas from different perspectives.
 */
class Sphere : public Drawable
{
public:
	/**
	* @brief Constructs a sphere object.
	* @param x - The X-coordinate of the center of the sphere.
	* @param y - The Y-coordinate of the center of the sphere.
	* @param z - The Z-coordinate of the center of the sphere.
	* @param radius - The radius of the sphere.
	* @param meridians - The number of meridians (longitudes) used to divide the sphere.
	* @param parallels - The number of parallels (latitudes) used to divide the sphere.
	* @param color - The color of the sphere.
	*/
	Sphere(double x, double y, double z, double radius, int meridians, int parallels, wxColour color = Drawable::line_color);

	/**
	 * @brief Constructs a sphere object.
	 * @param center - The coordinates of the center of the sphere.
	 * @param radius - The radius of the sphere.
	 * @param meridians - The number of meridians (longitudes) used to divide the sphere.
	 * @param parallels - The number of parallels (latitudes) used to divide the sphere.
	 * @param color - The color of the sphere.
	 */
	Sphere(Position center, double radius, int meridians, int parallels, wxColour color = Drawable::line_color);

	/**
	 * @brief Draws the sphere on four different 2D canvases representing different perspectives.
	 * @param dc1 - The device context for the front view.
	 * @param dc2 - The device context for the top view.
	 * @param dc3 - The device context for the side view.
	 * @param dc4 - The device context for the perspective view.
	 */
	void draw(wxDC& dc1, wxDC& dc2, wxDC& dc3, wxDC& dc4) override;

protected:
	void move(double x_shift, double y_shift, double z_shift) override;
	void rotate(double x_cord, double y_cord, double z_cord, double alpha, double beta, double gamma) override;
	void draw_front(wxDC& dc) override;
	void draw_top(wxDC& dc) override;
	void draw_side(wxDC& dc) override;
	void draw_perspective(wxDC& dc) override;
	std::string save() const override;

private:
	Position _center;   ///< The center of the sphere.
	double _radius;     ///< The radius of the sphere.
	int _meridians;     ///< The number of meridians (longitudes).
	int _parallels;     ///< The number of parallels (latitudes).
};
