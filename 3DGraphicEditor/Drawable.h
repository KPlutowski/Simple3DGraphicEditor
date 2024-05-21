#pragma once

#include <vector>
#include "GUI.h"

/// <summary>
/// Enum dla roznych rodzajow widoku
/// </summary>
enum class view {
	wire, lines, solid
};

/// <summary>
/// Pozycja w przestrzeni 3D
/// </summary>
struct Position {
	double x, y, z;
};

/// <summary>
/// Klasa bazowa dla figur
/// Managment figur w wektorze polega na wywolaniu Drawable::metoda()
/// Jezeli sie nie podoba to moge zrobic osobna klase ObjectManager jak Maciek proponowal : p
/// wowczas managment bedzie polegal na mgr.metoda()
/// </summary>
class Drawable {
public:
	/// <summary>
	/// Dodanie figury do wektora (na zasadzie addObj(new ...))
	/// </summary>
	/// <param name="obj">Wskaznik na dodawany obiekt</param>
	static void addObj(Drawable* obj);

	/// <summary>
	/// Usuniecie figury z wektora
	/// </summary>
	/// <param name="index"></param>
	static void deleteObj(int index);

	/// <summary>
	/// Usuniecie wszystkich figur
	/// </summary>
	static void clearAll();

	/// <summary>
	/// Przesuniecie figury o wektor
	/// </summary>
	/// <param name="index"></param>
	/// <param name="x_shift"></param>
	/// <param name="y_shift"></param>
	/// <param name="z_shift"></param>
	static void moveObj(int index, double x_shift, double y_shift, double z_shift);

	/// <summary>
	/// Obrot figury wokol punktu o zadane katy
	/// </summary>
	/// <param name="index"></param>
	/// <param name="x_cord"></param>
	/// <param name="y_cord"></param>
	/// <param name="z_cord"></param>
	/// <param name="alpha"></param>
	/// <param name="beta"></param>
	/// <param name="gamma"></param>
	static void rotateObj(int index, double x_cord, double y_cord, double z_cord, double alpha, double beta, double gamma);
	
	/// <summary>
	/// Podswietlenie obiektu
	/// </summary>
	/// <param name="index"></param>
	static void touchObj(int index);

	/// <summary>
	/// Getter jednego obiektu z wektora (moze sie przyda)
	/// </summary>
	/// <param name="index"></param>
	/// <returns>Wskaznik na figure o podanym indeksie</returns>
	static Drawable* getObj(int index);

	/// <summary>
	/// Getter wektora figur (moze sie przyda)
	/// </summary>
	/// <returns>Wektor wskaznikow na figury</returns>
	static std::vector<Drawable*> getAllObjs();
protected:
	virtual void move(double x_shift, double y_shift, double z_shift) = 0;
	virtual void rotate(double x_cord, double y_cord, double z_cord, double alpha, double beta, double gamma) = 0;
	virtual void draw() = 0;
private:
	static std::vector<Drawable*> objs;

	static bool fill_style;
	static wxColour fill_color;
	static view view_style;
	static double front_distance;
	static double top_distance;
	static double right_distance;
	static Position camera_pos;
	static Position camera_look;
	static double camera_fov;

	//TODO: opisy zmiennych statycznych
};
