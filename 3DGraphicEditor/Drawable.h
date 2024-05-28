#pragma once

#include <vector>
#include <fstream>
#include <sstream>
#include <wx/timer.h>
#include "GUIMyFrame1.h"
#include <algorithm>
#include <wx/dcbuffer.h>
#include <wx/init.h>

/// @brief Enum dla rodzajow widoku
enum class view {
	wire, lines, solid
};

/// @brief Pozycja w przestrzeni 3D
struct Position {
	Position(double a = 0, double b = 0, double c = 0) { x = a, y = b, z = c; }
	double x, y, z;
	std::string toString() const
	{
		return "(" + std::to_string((int)x) + "," + std::to_string((int)y) + "," + std::to_string((int)z) + ")";
	}
	Position operator-(const Position& other) const {
		return Position(x - other.x, y - other.y, z - other.z);
	}
	Position operator+(const Position& other) const {
		return Position(x + other.x, y + other.y, z + other.z);
	}
	static Position fromString(const std::string& str) {
		std::vector<double> pos_value;
		std::string text;
		for (auto i : str) {
			if (i == '(' || i == ' ') {
				continue;
			}
			else if (i == ',' || i == ')') {
				pos_value.push_back(std::stod(text));
				text.clear();
			}

			else {
				text += i;
			}
		}
		return Position(pos_value[0], pos_value[1], pos_value[2]);
	}
	void shift(double x_shift, double y_shift, double z_shift)
	{
		x += x_shift;
		y += y_shift;
		z += z_shift;
	}
	void rotate(const Position& center, double alpha, double beta, double gamma)
	{
		const double cosAlpha = cos(alpha * M_PI / 180.0);
		const double sinAlpha = sin(alpha * M_PI / 180.0);
		const double cosBeta = cos(beta * M_PI / 180.0);
		const double sinBeta = sin(beta * M_PI / 180.0);
		const double cosGamma = cos(gamma * M_PI / 180.0);
		const double sinGamma = sin(gamma * M_PI / 180.0);

		shift(-center.x, -center.y, -center.z);

		const double xNew = cosBeta * cosGamma * x + (cosAlpha * sinGamma + sinAlpha * sinBeta * cosGamma) * y + (sinAlpha * sinGamma - cosAlpha * sinBeta * cosGamma) * z;
		const double yNew = -cosBeta * sinGamma * x + (cosAlpha * cosGamma - sinAlpha * sinBeta * sinGamma) * y + (sinAlpha * cosGamma + cosAlpha * sinBeta * sinGamma) * z;
		const double zNew = sinBeta * x - sinAlpha * cosBeta * y + cosAlpha * cosBeta * z;
		x = xNew;
		y = yNew;
		z = zNew;

		shift(center.x, center.y, center.z);
	}
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

	static std::vector<std::string> getFiguresInfo()
	{
		std::vector<std::string> result;
		int i = 0;
		for (const auto figure : figures)
		{
			i++;
			result.push_back(std::to_string(i) + " " + figure->getInfo());
		}
		return result;
	}

	class Camera
	{
	public:
		/// Projects a 3D position to a 2D screen coordinate.
		/// \param pos The 3D position to project.
		/// \return The projected 2D screen coordinate.
		static wxPoint projectPerspective(const Position& point) {
			// Transform the point to camera space
			double px = point.x - cameraPosition.x;
			double py = point.y - cameraPosition.y;
			double pz = point.z - cameraPosition.z;

			// Apply rotation (camera orientation)
			double camX = px * rightVector.x + py * rightVector.y + pz * rightVector.z;
			double camY = px * upVector.x + py * upVector.y + pz * upVector.z;
			double camZ = px * cameraDirection.x + py * cameraDirection.y + pz * cameraDirection.z;

			// Ensure camZ is not too close to zero to prevent division by zero
			if (camZ < nearPlane) {
				camZ = nearPlane;
			}

			// Perspective projection
			double screenX = (camX / (camZ * tanFov * aspectRatio)) * (panelWidth / 2) + (panelWidth / 2);
			double screenY = (camY / (camZ * tanFov)) * (panelHeight / 2) + (panelHeight / 2);

			return wxPoint(screenX, panelHeight - screenY); // Flip y-axis for drawing
		}

		/// Projects a 3D position to a 2D screen coordinate for front view.
		/// \param pos The 3D position to project.
		/// \return The projected 2D screen coordinate.
		static wxPoint projectFront(const Position& pos)
		{
			// Project X and Y coordinates for front view, ignoring Z
			double screenX = (pos.x / frontDistance) * (panelWidth / 2) + (panelWidth / 2);
			double screenY = (pos.y / frontDistance) * (panelHeight / 2) + (panelHeight / 2);
			return wxPoint(screenX, panelHeight - screenY); // Flip y-axis for drawing
		}

		/// Projects a 3D position to a 2D screen coordinate for top view.
		/// \param pos The 3D position to project.
		/// \return The projected 2D screen coordinate.
		static wxPoint projectTop(const Position& pos)
		{
			// Project X and Z coordinates for top view, ignoring Y
			double screenX = (pos.x / topDistance) * (panelWidth / 2) + (panelWidth / 2);
			double screenY = (pos.z / topDistance) * (panelHeight / 2) + (panelHeight / 2);
			return wxPoint(screenX, panelHeight - screenY); // Flip y-axis for drawing
		}

		/// Projects a 3D position to a 2D screen coordinate for side view.
		/// \param pos The 3D position to project.
		/// \return The projected 2D screen coordinate.
		static wxPoint projectSide(const Position& pos)
		{
			// Project Y and Z coordinates for side view, ignoring X
			double screenX = (pos.y / rightDistance) * (panelWidth / 2) + (panelWidth / 2);
			double screenY = (pos.z / rightDistance) * (panelHeight / 2) + (panelHeight / 2);
			return wxPoint(screenX, panelHeight - screenY); // Flip y-axis for drawing
		}

		/// Updates the camera parameters based on current settings.
		static void update();

		/// \param x The x coordinate of the new camera position.
		/// \param y The y coordinate of the new camera position.
		/// \param z The z coordinate of the new camera position.
		static void setPosition(const double x, const double y, const double z)
		{
			cameraPosition = { x, y, z };
			Camera::update();
		}
		static Position getPosition() { return cameraPosition; }

		/// \param x The x coordinate of the new look at position.
		/// \param y The y coordinate of the new look at position.
		/// \param z The z coordinate of the new look at position.
		static void setLookAt(const double x, const double y, const double z)
		{
			lookAtPosition = { x, y, z };
			Camera::update();
		}
		static Position getLookAt() { return lookAtPosition; }

		/// \param newFov The new field of view for the camera.
		static void setFov(const double newFov)
		{
			fieldOfView = newFov;
			Camera::update();
		}
		static double getFov() { return fieldOfView; }

		static double getFrontDistance() { return frontDistance; }
		static double getTopDistance() { return topDistance; }
		static double getRightDistance() { return rightDistance; }
		static void setFrontDistance(const double front) { frontDistance = front; }
		static void setTopDistance(const double top) { topDistance = top; }
		static void setRightDistance(const double right) { rightDistance = right; }
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

	static void render_panel_to_bitmap(const std::string& filename, int width, int height, wxPanel* panel)
	{
		wxMemoryDC memDC;

		wxBitmap bitmap(width, height);
		memDC.SelectObject(bitmap);

		memDC.SetBackground(*wxWHITE_BRUSH);
		memDC.Clear();

		panel->Refresh();
		panel->Update();
		panel->GetUpdateRegion().Clear();

		for (Drawable* figure : figures)
		{
			memDC.SetPen(wxPen(figure->_color));
			memDC.SetBrush(*wxTRANSPARENT_BRUSH);
			figure->render(memDC, Camera::projectPerspective);
		}

		wxImage image = bitmap.ConvertToImage();
		image.SaveFile(filename, wxBITMAP_TYPE_PNG);
	}

protected:
	std::string _type;
	wxColour _color; /// @brief kolor obiektu
	std::vector<Position> _vertices;

	/// @brief Rysowanie figury
	/// @param dcFront - panel z widokiem z przodu
	/// @param dcTop - panel z widokiem z gory
	/// @param dcSide - panel z widokiem z boku
	/// @param dcPerspective - panel z widokiem z perspektywa
	virtual void draw(wxDC& dcFront, wxDC& dcTop, wxDC& dcSide, wxDC& dcPerspective) const
	{
		render(dcFront, Camera::projectFront);
		render(dcTop, Camera::projectTop);
		render(dcSide, Camera::projectSide);
		render(dcPerspective, Camera::projectPerspective);
	}
	virtual void move(double xShift, double yShift, double zShift) {
		for (auto& vertex : _vertices)
		{
			vertex.shift(xShift, yShift, zShift);
		}
	}
	virtual void rotate(double xPivot, double yPivot, double zPivot, double alpha, double beta, double gamma) {
		for (auto& vertex : _vertices)
		{
			vertex.rotate(Position(xPivot, yPivot, zPivot), alpha, beta, gamma);
		}
	}

	virtual void render(wxDC& dc, wxPoint(*projectionFunc)(const Position&)) const = 0;
	virtual void computeVertices() = 0;

	virtual std::string save() const
	{
		std::string tmp;

		tmp += _type + " ";
		tmp += std::to_string(_vertices.size()) + " ";
		tmp += std::to_string(_color.GetRGB()) += " ";

		for (const auto& vertex : _vertices)
		{
			tmp += vertex.toString() + " ";
		}

		return tmp;
	}

	virtual std::string getInfo() const
	{
		return "Drawable";
	}

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
