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

/// @brief Enum dla rodzajow widoku
enum class view {
	wire, lines, solid
};

/// @brief Klasa bazowa dla figur
/// - management figur w wektorze polega na wywolaniu Drawable::metoda().
/// Jezeli sie nie podoba to moge zrobic osobna klase ObjectManager jak Maciek proponowal :p
/// wowczas management bedzie polegal na mgr.metoda()
class Drawable {
public:
	Drawable(wxColour color = penColor, const std::string& type = "Drawable") :_color(color), _type(type) {};

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
	/// @param dcFront - panel z widokiem z przodu
	/// @param dcTop - panel z widokiem z gory
	/// @param dcSide - panel z widokiem z boku
	/// @param dcPerspective - panel z widokiem z perspektywa
	static void DrawAll(wxDC& dcFront, wxDC& dcTop, wxDC& dcSide, wxDC& dcPerspective);

	/// @brief Getter jednej figury z wektora
	/// @param index - indeks figury
	/// @return Wskaznik na figure
	static Drawable* getObj(int index);

	/// @brief Getter wszystkich figur
	/// @return Wektor wskaznikow na figury
	static std::vector<Drawable*> getAllObjs();

	/// \param newColour
	static void SetLineColor(const wxColour& newColour);

	/// \param fileName
	static void saveToFile(const std::string& fileName);

	/// \param fileName
	static void loadFromFile(const std::string& fileName);

	/// @brief SetVievSize
	/// @param x - Width
	/// @param y - Height
	static void SetViewSize(const double x, const double y);

	void setColor(const wxColour& newColor);

	static std::vector<std::string> getFiguresInfo();

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
		
		static void setFrontDistance(const double front);
		
		static void setTopDistance(const double top);
		
		static void setRightDistance(const double right);
	
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
	};

	static void render_panel_to_bitmap(const std::string& filename, int width, int height, wxPanel* panel);

protected:
	std::string _type;
	wxColour _color; /// @brief kolor obiektu
	std::vector<Position> _vertices;

	/// @brief Rysowanie figury
	/// @param dcFront - panel z widokiem z przodu
	/// @param dcTop - panel z widokiem z gory
	/// @param dcSide - panel z widokiem z boku
	/// @param dcPerspective - panel z widokiem z perspektywa
	virtual void draw(wxDC& dcFront, wxDC& dcTop, wxDC& dcSide, wxDC& dcPerspective) const;
	
	virtual void move(double xShift, double yShift, double zShift);
	
	virtual void rotate(double xPivot, double yPivot, double zPivot, double alpha, double beta, double gamma);

	virtual void render(wxDC& dc, wxPoint(*projectionFunc)(const Position&)) const = 0;
	
	virtual void computeVertices() = 0;

	virtual std::string save() const;

	virtual std::string getInfo() const;

	static std::vector<Drawable*> figures; /// @brief Wektor figur
	static wxColour penColor; /// @brief Kolor do rysowania
	static bool fill_style; /// @brief Czy wypelnienie (false jesli nie, true jesli tak)
	static wxColour fill_color; /// @brief Kolor wypelnienia
	static view view_style; /// @brief Rodzaj widoku (wire, lines lub solid)
	static double panelHeight;	/// Vertical panel size
	static double panelWidth;	///< Horizontal panel size

private:
	static constexpr int penWidth = 1;
	wxTimer* _highlightTimer = nullptr; /// Timer for resetting the highlight
	static int highlight_duration_ms; /// Duration in milliseconds for highlighting
	static double highlight_factor; /// Highlight factor

	void highlightObject();
	const wxColour generateHighlight() const;
	void ResetHighlight(wxTimerEvent& event, wxColour prev);
};
