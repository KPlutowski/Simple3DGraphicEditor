#pragma once

#include <vector>
#include <fstream>
#include <sstream>
#include <wx/timer.h>
#include "GUIMyFrame1.h"
#include <algorithm>
#include <wx/dcbuffer.h>
#include <wx/init.h>

/// @brief Pozycja w przestrzeni 3D
struct Position {
	/// @brief Konstruktor Position
	/// @param a - koord. w osi X
	/// @param b - koord. w osi Y
	/// @param c - koord. w osi Z
	Position(double a = 0, double b = 0, double c = 0);

	double x, y, z;

	/// @brief Konwersja pozycji na string
	/// @return - string z koordynatami
	std::string toString() const;

	/// @brief Operator odejmowania wektorowego dwoch pozycji
	/// @param other - odejmowana pozycja
	/// @return - pozycja bedaca wynikiem operacji
	Position operator-(const Position& other) const;

	/// @brief Operator dodawania wektorowego dwoch pozycji
	/// @param other - dodawana pozycja
	/// @return - pozycja bedaca wynikiem operacji
	Position operator+(const Position& other) const;

	/// @brief Konwersja stringu na obiekt Posiiton
	/// @param str - string z danymi
	/// @return - utworzony obiekt pozycji
	static Position fromString(const std::string& str);

	/// @brief Przesuniecie pozycji o wektor
	/// @param x_shift - shift w osi X
	/// @param y_shift - shift w osi Y
	/// @param z_shift - shift w osi Z
	void shift(double x_shift, double y_shift, double z_shift);

	/// @brief Obrocenie pozycji wokol punktu
	/// @param center - punkt obrotu
	/// @param alpha - kat wokol punktu w osi X
	/// @param beta - kat wokol punktu w osi Y
	/// @param gamma - kat wokol puntku w osi Z
	void rotate(const Position& center, double alpha, double beta, double gamma);
};