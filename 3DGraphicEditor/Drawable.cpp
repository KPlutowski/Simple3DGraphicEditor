#include <vector>
#include "GUIMyFrame1.h"
#include "Drawable.h"
#include "Line.h"
#include "Sphere.h"
#include "Box.h"
#include "Cone.h"
#include "Cylinder.h"
#include "DrawableObject.h"

std::vector<DrawableObject*> Drawable::figures;

wxColour Drawable::penColor = wxColour(0, 0, 0);;
bool Drawable::fill_style = false;
wxColour Drawable::fill_color = wxColour(255, 255, 255);
view Drawable::view_style = view::lines;
int Drawable::penWidth = 1;
int Drawable::highlight_duration_ms = 1000;
double Drawable::highlight_factor = 0.6;

void Drawable::addObj(DrawableObject* fig) {
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
	if (index < 1 || index > figures.size()) {
		return;
	}

	auto figure_to_move = figures[index - 1];
	figure_to_move->move(x_shift, y_shift, z_shift);
}

void Drawable::moveGroup(int group_id, double x_shift, double y_shift, double z_shift) 
{
	for (auto& figure : figures) {
		if (figure->getGroupId() == group_id) {
			figure->move(x_shift, y_shift, z_shift);
		}
	}
}

void Drawable::rotateObj(int index, double x_cord, double y_cord, double z_cord, double alpha, double beta, double gamma) {
	if (index < 1 || index > figures.size()) {
		return;
	}

	auto figure_to_move = figures[index - 1];
	figure_to_move->rotate(x_cord, y_cord, z_cord, alpha, beta, gamma);
}

void Drawable::rotateGroup(int group_id, double x_cord, double y_cord, double z_cord, double alpha, double beta, double gamma)
{
	for (auto& fig : figures) {
		if (fig->getGroupId() == group_id) {
			fig->rotate(x_cord, y_cord, z_cord, alpha, beta, gamma);
		}
	}
}

void Drawable::touchObj(int index) {
	if (index < 1 || index > figures.size()) {
		return;
	}

	auto figure_to_move = figures[index - 1];
	int group_id = figure_to_move->getGroupId();

	for (auto& figure : figures) {
		if (figure->getGroupId() == group_id) {
			figure->highlightObject();
		}
	}
}

void Drawable::DrawAll(wxDC& dcFront, wxDC& dcTop, wxDC& dcSide, wxDC& dcPerspective) {
	for (const auto* figure : figures)
	{
		wxPen pen(figure->getColor(), figure->getLineWidth());
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

DrawableObject* Drawable::getObj(int index) {
	if (index < 1 || index > figures.size())
		return nullptr;

	return figures[index - 1];
}

std::vector<DrawableObject*> Drawable::getAllObjs() {
	return figures;
}

void Drawable::SetLineColor(const wxColour& newColour) {
	penColor = newColour;
}

std::vector<std::string> Drawable::getFiguresInfo()
{
	std::vector<std::string> result;
	int i = 0;
	for (const auto figure : figures)
	{
		i++;
		result.push_back("id: " + std::to_string(i) + ", group id: " + std::to_string(figure->getGroupId()) + " " + figure->getInfo());
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
	oss << std::to_string(penWidth) << " ";
	oss << std::to_string(highlight_duration_ms) << " ";
	oss << std::to_string(highlight_factor) << " ";

	oss << Camera::getFrontDistance() << " ";
	oss << Camera::getTopDistance() << " ";
	oss << Camera::getRightDistance() << " ";
	oss << Camera::getPosition().toString() << " ";
	oss << Camera::getLookAt().toString() << " ";
	oss << Camera::getFov() << " ";

	outFile << oss.str() << std::endl;

	for (const auto* obj : figures)
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

		int width;
		if (!(iss >> width)) {
			std::cerr << "Error: Failed to read PenWidth." << std::endl;
			return;
		}
		penWidth = width;

		int highlightDuration;
		if (!(iss >> highlightDuration)) {
			std::cerr << "Error: Failed to read highlightDuration." << std::endl;
			return;
		}
		highlight_duration_ms = highlightDuration;

		double highlightFactor;
		if (!(iss >> highlightFactor)) {
			std::cerr << "Error: Failed to read highlightFactor." << std::endl;
			return;
		}
		highlight_factor = highlightFactor;

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
		int groupId;
		int lineWidth;

		iss >> type >> groupId >> color >> lineWidth >> verticesSize;

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

	for (auto* figure : figures)
	{
		memDC.SetPen(wxPen(figure->getColor()));
		memDC.SetBrush(*wxTRANSPARENT_BRUSH);
		figure->render(memDC, Camera::projectPerspective);
	}

	wxImage image = bitmap.ConvertToImage();
	image.SaveFile(filename, wxBITMAP_TYPE_PNG);
}

void Drawable::add_to_group(int group_id, int element_id)
{
	if (element_id >= 1 && element_id <= figures.size())
		figures[element_id - 1]->setGroupId(group_id);
}