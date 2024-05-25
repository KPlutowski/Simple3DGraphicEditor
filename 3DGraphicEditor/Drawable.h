// TODO: 
// set fill style 
// set fill color
// set view
// set view range

// ~Drawable
#pragma once

#include <vector>
#include <fstream>
#include <sstream>
#include <wx/timer.h>
#include "GUIMyFrame1.h"
#include <algorithm>

/// @brief Enum dla rodzajow widoku
enum class view {
	wire, lines, solid
};

/// @brief Pozycja w przestrzeni 3D
struct Position {
	Position(double a, double b, double c) { x = a, y = b, z = c; }
	double x, y, z;
};

/// @brief Klasa bazowa dla figur
/// - management figur w wektorze polega na wywolaniu Drawable::metoda().
/// Jezeli sie nie podoba to moge zrobic osobna klase ObjectManager jak Maciek proponowal :p
/// wowczas management bedzie polegal na mgr.metoda()
class Drawable {
public:
	Drawable(wxColour color = line_color) :_color(color) {};

	/// @brief Dodanie figury do wektora (na zasadzie addObj(new ...))
	/// @param fig - wskaznik na dodawana figure
	static void addObj(Drawable* fig);

	/// @brief Usuniecie figury z wektora
	/// @param index - indeks figury
	static void deleteObj(int index);

	/// @brief Usuniecie wszytskich figur
	static void clearAll();

	/// @brief Przesuniecie figury o wektor
	/// @param index - indeks figury
	/// @param x_shift - shift w osi X 
	/// @param y_shift - shift w osi Y 
	/// @param z_shift - shift w osi Z 
	static void moveObj(int index, double x_shift, double y_shift, double z_shift);

	/// @brief Obrot figury wokol punktu
	/// @param index - indeks figury
	/// @param x_cord - wspolrzedna w osi X
	/// @param y_cord - wspolrzedna w osi Y
	/// @param z_cord - wspolrzedna w osi Z
	/// @param alpha - kat wokol punktu w osi X
	/// @param beta - kat wokol punktu w osi Y
	/// @param gamma - kat wokol puntku w osi Z
	static void rotateObj(int index, double x_cord, double y_cord, double z_cord, double alpha, double beta, double gamma);

	/// @brief Podswietlenie figury
	/// @param index - indeks figury
	static void touchObj(int index);

	/// @brief Rysowanie wszystkich figur
	/// @param dc1 - panel z widokiem z przodu
	/// @param dc2 - panel z widokiem z gory
	/// @param dc3 - panel z widokiem z boku
	/// @param dc4 - panel z widokiem z perspektywa
	static void DrawAll(wxDC& dc1, wxDC& dc2, wxDC& dc3, wxDC& dc4);

	/// @brief Getter jednej figury z wektora
	/// @param index - indeks figury
	/// @return Wskaznik na figure
	static Drawable* getObj(int index);

	/// @brief Getter wszystkich figur
	/// @return Wektor wskaznikow na figury
	static std::vector<Drawable*> getAllObjs();

	/// @brief Rysowanie figury
	/// @param dc1 - panel z widokiem z przodu
	/// @param dc2 - panel z widokiem z gory
	/// @param dc3 - panel z widokiem z boku
	/// @param dc4 - panel z widokiem z perspektywa
	virtual void draw(wxDC& dc1, wxDC& dc2, wxDC& dc3, wxDC& dc4) = 0;

	/// \param newColour	 
	static void SetLineColor(const wxColour& newColour);

	/// \param newCamerePosition
	static void SetCameraPosition(const Position& newCameraPosition);

	/// \param newCameraLook
	static void SetCameraLook(const Position& newCameraLook);

	/// \param newCameraFov
	static void SetCameraFov(const double newCameraFov);

	/// \param fileName
	static void saveToFile(const std::string& fileName);

	/// \param fileName
	static void loadFromFile(const std::string& fileName);

	/// @brief SetVievSize
	/// @param x - Width
	/// @param y - Height
	static void SetViewSize(const double x, const double y);

	void setColor(const wxColour& newColor);

protected:
	wxColour _color; /// @brief kolor obiektu
	
	virtual void move(double x_shift, double y_shift, double z_shift) = 0;
	virtual void rotate(double x_cord, double y_cord, double z_cord, double alpha, double beta, double gamma) = 0;
	virtual void draw_front(wxDC& dc) = 0;
	virtual void draw_top(wxDC& dc) = 0;
	virtual void draw_side(wxDC& dc) = 0;
	virtual void draw_perspective(wxDC& dc) = 0;
	virtual std::string save() const = 0;

	static std::vector<Drawable*> figures; /// @brief Wektor figur	
	static wxColour line_color; /// @brief Kolor linii
	static bool fill_style; /// @brief Czy wypelnienie (false jesli nie, true jesli tak)
	static wxColour fill_color; /// @brief Kolor wypelnienia
	static view view_style; /// @brief Rodzaj widoku (wire, lines lub solid)
	static double front_distance; /// @brief Odleglosc kamery z przodu
	static double top_distance; /// @brief Odleglosc kamery z gory
	static double right_distance; /// @brief Odleglosc kamery z boku
	static Position camera_pos; /// @brief Pozycja kamery z perspektywa
	static Position camera_look; /// @brief Punkt na ktory patrzy kamera
	static double camera_fov; /// @brief FOV kamery z perspektywa (w stopniach)
    static double panel_height;	/// Vertical panel size
    static double panel_width;	///< Horizontal panel size

	/**
	 * @brief Generates a 3D rotation matrix.
	 *
	 * @param alpha The rotation angle around the X-axis (in degrees).
	 * @param beta The rotation angle around the Y-axis (in degrees).
	 * @param gamma The rotation angle around the Z-axis (in degrees).
	 * @return The rotation matrix representing the combined rotation.
	 */
	static std::vector<std::vector<double>> generate_rotation_matrix(double alpha, double beta, double gamma);

private:
	wxTimer* _highlightTimer = nullptr; // Timer for resetting the highlight
	static int highlight_duration_ms; /// Duration in milliseconds for highlighting
	static double highlight_factor; /// Highlight factor

	/**
	 * @brief Multiplies two 3x3 matrices.
	 *
	 * @param a The first matrix.
	 * @param b The second matrix.
	 * @return The result of matrix multiplication (a * b).
	 */
	static std::vector<std::vector<double>> multiplyMatrix(const std::vector<std::vector<double>>& a, const std::vector<std::vector<double>>& b);

	void highlightObject();
	const wxColour& generateHighlight() const;
};
