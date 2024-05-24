#pragma once

#include <vector>
#include "GUIMyFrame1.h"
#include "Drawable.h"

class Line : public Drawable {
public:
	/// @brief Konstruktor linii
	/// @param x1 - wspolrzedna X poczatku
	/// @param y1 - wspolrzedna Y poczatku
	/// @param z1 - wspolrzedna Z poczatku
	/// @param x2 - wspolrzedna X konca
	/// @param y2 - wspolrzedna Y konca
	/// @param z2 - wspolrzedna Z konca
	Line(double x1, double y1, double z1, double x2, double y2, double z2);

	/// @brief Konstruktor linii
	/// @param start - Poczatek linii
	/// @param end - Kolor linii
	Line(Position start, Position end);


	/// @brief Getter poczatku linii
	/// @return Struktura Point punktu poczatkowego linii
	Position start();

	/// @brief Getter konca linii
	/// @return Struktura Point punktu koncowego linii
	Position end();

	/// @brief draw a line
	void draw(wxDC& dc1, wxDC& dc2, wxDC& dc3, wxDC& dc4) override;


protected:
	void move(double x_shift, double y_shift, double z_shift) override;
	void rotate(double x_cord, double y_cord, double z_cord, double alpha, double beta, double gamma) override;
	void draw_front(wxDC& dc) override;
	void draw_top(wxDC& dc) override;
	void draw_side(wxDC& dc) override;
	void draw_perspective(wxDC& dc) override;

private:
	Position _start; /// @brief Poczatek linii
	Position _end; /// @brief Koniec linii
	wxColour _color; /// @brief Kolor linii
	// Tu zakladam ze kazda figura bedzie miala inny kolor linii, jesli nie to mozna ta zmienna usunac
};