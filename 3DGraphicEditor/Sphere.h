#pragma once
#include <vector>
#include "GUIMyFrame1.h"
#include "Drawable.h"
class Sphere : public Drawable
{
public:
	/// @brief Konstruktor sfery
	/// @param x - wspó³rzêdna X œrodka sfery
	/// @param y - wspó³rzêdna Y œrodka sfery
	/// @param z - wspó³rzêdna Z œrodka sfery
	/// @param radius - promieñ sfery
	/// @param meridians - liczba podzia³ów na po³udniki
	/// @param parallels - liczba podzia³ów na równole¿niki
	/// @param color - kolor sfery
	Sphere(double x, double y, double z, double radius, int meridians, int parallels, wxColour color = Drawable::line_color);
	Sphere(Position center, double radius, int meridians, int parallels, wxColour color = Drawable::line_color);

	/// @brief draw a sphere
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
	Position _center;   /// @brief Œrodek sfery
	double _radius;     /// @brief Promieñ sfery
	int _meridians;     /// @brief Liczba podzia³ów na po³udniki
	int _parallels;     /// @brief Liczba podzia³ów na równole¿niki
	wxColour _color;    /// @brief Kolor sfery
};
