#include <vector>
#include "GUIMyFrame1.h"
#include "Drawable.h"
#include "Line.h"
#include "Sphere.h"
#include "Box.h"
#include "Cone.h"
#include "Cylinder.h"

std::vector<Drawable*> Drawable::figures;
wxColour Drawable::penColor = wxColour(0, 0, 0);;
bool Drawable::fill_style = false;
wxColour Drawable::fill_color = wxColour(255, 255, 255);
view Drawable::view_style = view::lines;
double Drawable::panelHeight = 200.0;
double Drawable::panelWidth = 200.0;
int Drawable::highlight_duration_ms = 1000;
double Drawable::highlight_factor = 0.6;

// Camera initializers moved to Camera.cpp

Drawable::Drawable(wxColour color, const std::string& type) : _color(color), _type(type) {};

void Drawable::addObj(Drawable* fig) {
	figures.push_back(fig);
}

void Drawable::deleteObj(int index) {
	if (index >= 1 && index <= figures.size()) {
		delete figures[index - 1];
		figures.erase(figures.begin() + index - 1);
	}
}

void Drawable::clearAll() {
	for (auto&& fig : figures) delete fig;
	figures.clear();
}

void Drawable::moveObj(int index, double x_shift, double y_shift, double z_shift) 
{

	if (index >= 1 && index <= figures.size())
	{
		auto figuere_to_move = figures[index - 1];

		if (figuere_to_move->_group_id == 0)
		{
			figuere_to_move->move(x_shift, y_shift, z_shift);
		}
		else
		{
			// szukamy reszty z grupy
			for (const auto figure : figures)
			{
				if (figure->_group_id == figuere_to_move->_group_id)
				{
					figure->move(x_shift, y_shift, z_shift);
				}
			}
		}
	}
}

void Drawable::rotateObj(int index, double x_cord, double y_cord, double z_cord, double alpha, double beta, double gamma) {
	if (index >= 1 && index <= figures.size())
	{
		auto figuere_to_move = figures[index - 1];

		if (figuere_to_move->_group_id == 0)
		{
			figuere_to_move->rotate(x_cord, y_cord, z_cord, alpha, beta, gamma);
		}
		else
		{
			// szukamy reszty z grupy
			for (const auto figure : figures)
			{
				if (figure->_group_id == figuere_to_move->_group_id)
				{
					figure->rotate(x_cord, y_cord, z_cord, alpha, beta, gamma);
				}
			}
		}
	}
}

void Drawable::touchObj(int index) {
	if (index >= 1 && index <= figures.size())
	{
		auto figuere_to_move = figures[index - 1];

		if (figuere_to_move->_group_id == 0)
		{
			figuere_to_move->highlightObject();
		}
		else
		{
			// szukamy reszty z grupy
			for (const auto figure : figures)
			{
				if (figure->_group_id == figuere_to_move->_group_id)
				{
					figure->highlightObject();
				}
			}
		}
	}
}

void Drawable::DrawAll(wxDC& dcFront, wxDC& dcTop, wxDC& dcSide, wxDC& dcPerspective) {
	for (Drawable* figure : figures)
	{
		wxPen pen(figure->_color, penWidth);
		dcFront.SetPen(pen);
		dcFront.SetBrush(*wxTRANSPARENT_BRUSH);
		dcTop.SetPen(pen);
		dcTop.SetBrush(*wxTRANSPARENT_BRUSH);
		dcSide.SetPen(pen);
		dcSide.SetBrush(*wxTRANSPARENT_BRUSH);
		dcPerspective.SetPen(pen);
		dcPerspective.SetBrush(*wxTRANSPARENT_BRUSH);

		figure->draw(dcFront, dcTop, dcSide, dcPerspective);
	}
}

Drawable* Drawable::getObj(int index) {
	if (index >= 1 && index <= figures.size())
		// Use zero-based indexing internally, so adjust index by -1
		return figures[index - 1];
	return nullptr;
}

std::vector<Drawable*> Drawable::getAllObjs() {
	return figures;
}

void Drawable::SetLineColor(const wxColour& newColour) {
	penColor = newColour;
}

void Drawable::SetViewSize(const double x, const double y) {
	panelWidth = x;
	panelHeight = y;
}

void Drawable::setColor(const wxColour& newColor) {
	_color = newColor;
}

std::vector<std::string> Drawable::getFiguresInfo()
{
	std::vector<std::string> result;
	int i = 0;
	for (const auto figure : figures)
	{
		i++;
		result.push_back("id: "+std::to_string(i)+", group id: "+ std::to_string(figure->_group_id) + " " + figure->getInfo());
	}
	return result;
}

void Drawable::saveToFile(const std::string& fileName)
{
	std::ofstream outFile(fileName);
	if (!outFile.is_open()) {
		std::cerr << "Error: Could not open file for writing: " << fileName << std::endl;
		return;
	}

	std::ostringstream oss;

	// saving drawable settings
	oss << penColor.GetRGB() << " ";
	oss << fill_style << " ";
	oss << fill_color.GetRGB() << " ";
	oss << std::to_string(static_cast<int>(view_style)) << " ";

	oss << Camera::getFrontDistance() << " ";
	oss << Camera::getTopDistance() << " ";
	oss << Camera::getRightDistance() << " ";

	oss << Camera::getPosition().toString() << " ";
	oss << Camera::getLookAt().toString() << " ";

	oss << Camera::getFov() << "\n";

	outFile << oss.str();

	// saving objects setting
	// type _vertices.size() _color _vertices (optional figure info)
	for (const Drawable* obj : figures)
	{
		outFile << obj->save();
	}

	outFile.close();
	if (outFile.fail()) {
		std::cerr << "Error: Could not properly close the file: " << fileName << std::endl;
	}
}

void Drawable::loadFromFile(const std::string& fileName)
{
	std::ifstream inFile(fileName);
	if (!inFile.is_open()) {
		std::cerr << "Error: Could not open file for reading: " << fileName << std::endl;
		return;
	}
	clearAll();  // Clear existing objects before loading new ones

	std::string line;
	if (std::getline(inFile, line))
	{
		std::istringstream iss(line);

		wxUint32 penColor;
		if (!(iss >> penColor)) {
			std::cerr << "Error: Failed to read pen color." << std::endl;
			return;
		}
		penColor = penColor;

		bool fillStyle;
		wxUint32 fillColor;
		if (!(iss >> fillStyle >> fillColor)) {
			std::cerr << "Error: Failed to read fill settings." << std::endl;
			return;
		}
		fill_style = fillStyle;
		fill_color = fillColor;

		int newView;
		if (!(iss >> newView)) {
			std::cerr << "Error: Failed to read view style." << std::endl;
			return;
		}
		view_style = static_cast<view>(newView);

		double fdist, tdist, rdist;
		if (!(iss >> fdist >> tdist >> rdist)) {
			std::cerr << "Error: Failed to read camera distances." << std::endl;
			return;
		}
		Camera::setFrontDistance(fdist);
		Camera::setTopDistance(tdist);
		Camera::setRightDistance(rdist);

		std::string strCamera;
		Position tmpPoint;
		if (!(iss >> strCamera)) {
			std::cerr << "Error: Failed to read camera position." << std::endl;
			return;
		}
		tmpPoint = Position::fromString(strCamera);
		Camera::setPosition(tmpPoint.x, tmpPoint.y, tmpPoint.z);

		if (!(iss >> strCamera)) {
			std::cerr << "Error: Failed to read camera look direction." << std::endl;
			return;
		}
		tmpPoint = Position::fromString(strCamera);
		Camera::setLookAt(tmpPoint.x, tmpPoint.y, tmpPoint.z);

		double fov;
		if (!(iss >> fov)) {
			std::cerr << "Error: Failed to read camera FOV." << std::endl;
			return;
		}
		Camera::setFov(fov);
	}
	else {
		std::cerr << "Error: Could not read the line from the file." << std::endl;
		return;
	}

	// object loading
	while (std::getline(inFile, line))
	{
		std::istringstream iss(line);
		std::string type;
		size_t verticesSize;
		wxUint32 color;

		iss >> type >> verticesSize >> color;

		std::string strPoint;
		Position Point;
		std::vector<Position> vertices;
		for (size_t i = 0; i < verticesSize; i++)
		{
			iss >> strPoint;
			Point = Position::fromString(strPoint);
			vertices.push_back(Point);
		}

		// aditional info and add objects
		if (type == "Line")
		{
			std::string start, end;
			if (iss >> start >> end)
			{
				addObj(new Line(Position::fromString(start), Position::fromString(end), color, vertices));
			}
		}
		else if (type == "Sphere")
		{
			std::string center;
			double radius;
			int meridians, parallels;
			if (iss >> center >> radius >> meridians >> parallels) {
				addObj(new Sphere(Position::fromString(center), radius, meridians, parallels, color, vertices));
			}
		}
		else if (type == "Box")
		{
			std::string start, end;
			if (iss >> start >> end)
			{
				addObj(new Box(Position::fromString(start), Position::fromString(end), color, vertices));
			}
		}
		else if (type == "Cone")
		{
			std::string base1, base2;

			double r1, r2, sides;
			if (iss >> base1 >> r1 >> base2 >> r2 >> sides)
			{
				addObj(new Cone(Position::fromString(base1), r1, Position::fromString(base2), r2, sides, color, vertices));
			}
		}
		else if (type == "Cylinder")
		{
			std::string base1, base2;

			double r1, r2, sides;
			if (iss >> base1 >> r1 >> base2 >> r2 >> sides)
			{
				addObj(new Cylinder(Position::fromString(base1), r1, Position::fromString(base2), r2, sides, color, vertices));
			}
		}
		else
		{
			std::cerr << "Error: Wrong object type. " << std::endl;
			return;
		}
		// Add more cases for other Drawable types
	}

	inFile.close();
	if (inFile.fail()) {
		std::cerr << "Error: Could not properly close the file: " << fileName << std::endl;
	}
}

void Drawable::highlightObject()
{
	if (!_highlightTimer)
	{
		wxColour colorBeforeHighlight = _color;

		_color = generateHighlight();

		_highlightTimer = new wxTimer();
		_highlightTimer->StartOnce(Drawable::highlight_duration_ms);

		// Bind the timer event
		_highlightTimer->Bind(wxEVT_TIMER, [this, colorBeforeHighlight](wxTimerEvent& event) {
			ResetHighlight(event, colorBeforeHighlight);
			});
	}
}

const wxColour Drawable::generateHighlight() const {
	return wxColour(
		std::min(_color.GetRed() - highlight_factor * 255, 255.0),
		std::min(_color.GetGreen() - highlight_factor * 255, 255.0),
		std::min(_color.GetBlue() - highlight_factor * 255, 255.0)
	);
};

void  Drawable::ResetHighlight(wxTimerEvent& event, wxColour prev)
{
	_color = prev;
	_highlightTimer->Stop(); // Stop the timer
	delete _highlightTimer; // Clean up the timer object
	_highlightTimer = nullptr;
}

void Drawable::draw(wxDC& dcFront, wxDC& dcTop, wxDC& dcSide, wxDC& dcPerspective) const
{
	render(dcFront, Camera::projectFront);
	render(dcTop, Camera::projectTop);
	render(dcSide, Camera::projectSide);
	render(dcPerspective, Camera::projectPerspective);
}

void Drawable::move(double xShift, double yShift, double zShift) {
	for (auto& vertex : _vertices)
	{
		vertex.shift(xShift, yShift, zShift);
	}
}

void Drawable::rotate(double xPivot, double yPivot, double zPivot, double alpha, double beta, double gamma) {
	for (auto& vertex : _vertices)
	{
		vertex.rotate(Position(xPivot, yPivot, zPivot), alpha, beta, gamma);
	}
}

std::string Drawable::save() const {
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

std::string Drawable::getInfo() const {
	return "Drawable";
}

void Drawable::render_panel_to_bitmap(const std::string& filename, int width, int height, wxPanel* panel)
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