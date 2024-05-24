#pragma once
#include <vector>
#include "GUIMyFrame1.h"
#include "Drawable.h"
class Sphere : public Drawable
{
public:
	/// @brief Konstruktor sfery
	/// @param x - wsp�rz�dna X �rodka sfery
	/// @param y - wsp�rz�dna Y �rodka sfery
	/// @param z - wsp�rz�dna Z �rodka sfery
	/// @param radius - promie� sfery
	/// @param meridians - liczba podzia��w na po�udniki
	/// @param parallels - liczba podzia��w na r�wnole�niki
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
	Position _center;   /// @brief �rodek sfery
	double _radius;     /// @brief Promie� sfery
	int _meridians;     /// @brief Liczba podzia��w na po�udniki
	int _parallels;     /// @brief Liczba podzia��w na r�wnole�niki
	wxColour _color;    /// @brief Kolor sfery
};
