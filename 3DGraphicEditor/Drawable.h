#pragma once

#include <vector>
#include <fstream>
#include <sstream>
#include <wx/timer.h>
#include "GUIMyFrame1.h"
#include <algorithm>
#include <wx/dcbuffer.h>
#include <wx/init.h>
#include "Position.h"

class DrawableObject;

/// @brief Enum dla rodzajow widoku
enum class view {
	wire, lines, solid
};

/// @brief Klasa bazowa dla figur
class Drawable {
public:
	class Camera
	{
	public:
		/// Projects a 3D position to a 2D screen coordinate.
		/// \param pos The 3D position to project.
		/// \return The projected 2D screen coordinate.
		static wxPoint projectPerspective(const Position& point);

		/// Projects a 3D position to a 2D screen coordinate for front view.
		/// \param pos The 3D position to project.
		/// \return The projected 2D screen coordinate.
		static wxPoint projectFront(const Position& pos);

		/// Projects a 3D position to a 2D screen coordinate for top view.
		/// \param pos The 3D position to project.
		/// \return The projected 2D screen coordinate.
		static wxPoint projectTop(const Position& pos);

		/// Projects a 3D position to a 2D screen coordinate for side view.
		/// \param pos The 3D position to project.
		/// \return The projected 2D screen coordinate.
		static wxPoint projectSide(const Position& pos);

		/// Updates the camera parameters based on current settings.
		static void update();

		/// \param x The x coordinate of the new camera position.
		/// \param y The y coordinate of the new camera position.
		/// \param z The z coordinate of the new camera position.
		static void setPosition(const double x, const double y, const double z);

		static Position getPosition();

		/// \param x The x coordinate of the new look at position.
		/// \param y The y coordinate of the new look at position.
		/// \param z The z coordinate of the new look at position.
		static void setLookAt(const double x, const double y, const double z);

		static Position getLookAt();

		/// \param newFov The new field of view for the camera.
		static void setFov(const double newFov);

		static double getFov();

		static double getFrontDistance();

		static double getTopDistance();

		static double getRightDistance();

		static double getWidth();

		static double getHeight();

		static void setFrontDistance(const double front);

		static void setTopDistance(const double top);

		static void setRightDistance(const double right);

		/// @brief SetVievSize
		/// @param x - Width
		/// @param y - Height
		static void SetViewSize(const double x, const double y);

	private:
		static double frontDistance; ///< Distance to the front clipping plane.
		static double topDistance; ///< Distance to the top clipping plane.
		static double rightDistance; ///< Distance to the right clipping plane.

		static Position cameraPosition; ///< Position of the camera.
		static Position lookAtPosition; ///< The point the camera is looking at.
		static double fieldOfView; ///< Field of view of the camera in degrees.

		static Position cameraDirection;
		static Position rightVector;
		static Position upVector;

		static constexpr double nearPlane = 0.01; ///< Distance to the near clipping plane.
		static constexpr double farPlane = 1000.0; ///< Distance to the far clipping plane.
		static double fovInRadians;
		static double tanFov;
		static double aspectRatio;

		static double panelHeight;	/// Vertical panel size
		static double panelWidth;	/// Horizontal panel size
	};

	/// @brief Dodanie figury do wektora (na zasadzie addObj(new ...))
	/// @param fig - wskaznik na dodawana figure
	static void addObj(DrawableObject* fig);

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

	/// @brief Przesuniecie grupy figur o wektor
	/// @param index - indeks figury
	/// @param x_shift - shift w osi X
	/// @param y_shift - shift w osi Y
	/// @param z_shift - shift w osi Z
	static void moveGroup(int group_id, double x_shift, double y_shift, double z_shift);

	/// @brief Obrot figury wokol punktu
	/// @param index - indeks figury
	/// @param x_cord - wspolrzedna w osi X
	/// @param y_cord - wspolrzedna w osi Y
	/// @param z_cord - wspolrzedna w osi Z
	/// @param alpha - kat wokol punktu w osi X
	/// @param beta - kat wokol punktu w osi Y
	/// @param gamma - kat wokol puntku w osi Z
	static void rotateObj(int index, double x_cord, double y_cord, double z_cord, double alpha, double beta, double gamma);
	
	/// @brief Obrot grupy figur wokol punktu
	/// @param index - indeks figury
	/// @param x_cord - wspolrzedna w osi X
	/// @param y_cord - wspolrzedna w osi Y
	/// @param z_cord - wspolrzedna w osi Z
	/// @param alpha - kat wokol punktu w osi X
	/// @param beta - kat wokol punktu w osi Y
	/// @param gamma - kat wokol puntku w osi Z
	static void rotateGroup(int grouo_id, double x_cord, double y_cord, double z_cord, double alpha, double beta, double gamma);

	/// @brief Podswietlenie figury
	/// @param index - indeks figury
	static void touchObj(int index);

	/// @brief Rysowanie wszystkich figur
	/// @param dcFront - panel z widokiem z przodu
	/// @param dcTop - panel z widokiem z gory
	/// @param dcSide - panel z widokiem z boku
	/// @param dcPerspective - panel z widokiem z perspektywa
	static void DrawAll(wxDC& dcFront, wxDC& dcTop, wxDC& dcSide, wxDC& dcPerspective);

	/// @brief Getter jednej figury z wektora
	/// @param index - indeks figury
	/// @return Wskaznik na figure
	static DrawableObject* getObj(int index);

	/// @brief Getter wszystkich figur
	/// @return Wektor wskaznikow na figury
	static std::vector<DrawableObject*> getAllObjs();

	/// \param newColour
	static void SetLineColor(const wxColour& newColour);

	/// \param fileName
	static void saveToFile(const std::string& fileName);

	/// \param fileName
	static void loadFromFile(const std::string& fileName);

	static std::vector<std::string> getFiguresInfo();

	static void render_panel_to_bitmap(const std::string& filename, int width, int height, wxPanel* panel);

	static void add_to_group(int group_id, int element_id);

	static void touchGroup(int group_id);
protected:
	static std::vector<DrawableObject*> figures; /// @brief Wektor figur
	static wxColour penColor; /// @brief Kolor do rysowania
	static bool fill_style; /// @brief Czy wypelnienie (false jesli nie, true jesli tak)
	static wxColour fill_color; /// @brief Kolor wypelnienia
	static view view_style; /// @brief Rodzaj widoku (wire, lines lub solid)
	static int penWidth;
	static int highlight_duration_ms; /// Duration in milliseconds for highlighting
	static double highlight_factor; /// Highlight factor
};
