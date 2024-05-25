#include <vector>
#include "GUIMyFrame1.h"
#include "Drawable.h"
#include "Line.h"
#include "Sphere.h"
#include "Box.h"

std::vector<Drawable*> Drawable::figures;
wxColour Drawable::line_color = wxColour(0, 0, 0);;
bool Drawable::fill_style = false;
wxColour Drawable::fill_color = wxColour(255, 255, 255);
view Drawable::view_style = view::lines;
double Drawable::front_distance = 1.0;
double Drawable::top_distance = 1.0;
double Drawable::right_distance = 1.0;
Position Drawable::camera_pos = Position(200, 200, 200);
Position Drawable::camera_look = Position(0, 0, 0);
double Drawable::camera_fov = 60.0;
double Drawable::panel_height = 200.0;
double Drawable::panel_width = 200.0;

void Drawable::addObj(Drawable* fig) {
	figures.push_back(fig);
}

void Drawable::deleteObj(int index) {
	if (index >= 1 && index <= figures.size()) 
		figures.erase(figures.begin() + index - 1);
}

void Drawable::clearAll() {
	for (auto&& fig : figures) delete fig;
	figures.clear();
}

void Drawable::moveObj(int index, double x_shift, double y_shift, double z_shift) {
	if (index >= 1 && index <= figures.size())
		// Use zero-based indexing internally, so adjust index by -1
		figures[index-1]->move(x_shift, y_shift, z_shift);
}

void Drawable::rotateObj(int index, double x_cord, double y_cord, double z_cord, double alpha, double beta, double gamma) {
	if (index >= 1 && index <= figures.size())
		// Use zero-based indexing internally, so adjust index by -1
		figures[index-1]->rotate(x_cord, y_cord, z_cord, alpha, beta, gamma);
}

void Drawable::touchObj(int index) {
	//TODO
}

void Drawable::DrawAll(wxDC& dc1, wxDC& dc2, wxDC& dc3, wxDC& dc4) {
	for (Drawable* figure : figures)
	{
		figure->draw(dc1,dc2,dc3,dc4);
	}
}

Drawable* Drawable::getObj(int index) {
	if (index >= 1 && index <= figures.size())
		// Use zero-based indexing internally, so adjust index by -1
		return figures[index-1];
	return nullptr;
}

std::vector<Drawable*> Drawable::getAllObjs() {
	return figures;
}

void Drawable::SetLineColor(const wxColour& newColour){
	line_color = newColour;
}

void Drawable::SetCameraPosition(const Position& newCameraPosition){
	camera_pos = newCameraPosition;
}

void Drawable::SetCameraLook(const Position& newCameraLook){
	camera_look = newCameraLook;
}

void Drawable::SetCameraFov(const double newCameraFov) {
	camera_fov = newCameraFov;
}

void Drawable::SetViewSize(const double x, const double y) {
	panel_width = x;
	panel_height = y;
}

std::vector<std::vector<double>> Drawable::multiplyMatrix(const std::vector<std::vector<double>>& a, const std::vector<std::vector<double>>& b) {
	int rows1 = a.size();
	int cols1 = a[0].size();
	int cols2 = b[0].size();

	std::vector<std::vector<double>> result(rows1, std::vector<double>(cols2, 0));

	for (int i = 0; i < rows1; ++i) {
		for (int j = 0; j < cols2; ++j) {
			for (int k = 0; k < cols1; ++k) {
				result[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return result;
}

std::vector<std::vector<double>> Drawable::generate_rotation_matrix(double alpha, double beta, double gamma)
{
	// Convert angles to radians
	double alphaRadian = alpha * M_PI / 180.0;
	double betaRadian = beta * M_PI / 180.0;
	double gammaRadian = gamma * M_PI / 180.0;

	// Precalculate trigonometric values
	double cosAlpha = cos(alphaRadian);
	double sinAlpha = sin(alphaRadian);
	double cosBeta = cos(betaRadian);
	double sinBeta = sin(betaRadian);
	double cosGamma = cos(gammaRadian);
	double sinGamma = sin(gammaRadian);

	// Create rotation matrices
	std::vector<std::vector<double>> alphaRotation = {
		{1, 0, 0},
		{0, cosAlpha, -sinAlpha},
		{0, sinAlpha, cosAlpha}
	};
	std::vector<std::vector<double>> betaRotation = {
		{cosBeta, 0, sinBeta},
		{0, 1, 0},
		{-sinBeta, 0, cosBeta}
	};
	std::vector<std::vector<double>> gammaRotation = {
		{cosGamma, -sinGamma, 0},
		{sinGamma, cosGamma, 0},
		{0, 0, 1}
	};

	return multiplyMatrix(multiplyMatrix(gammaRotation, betaRotation), alphaRotation);
}

void Drawable::saveToFile(const std::string& fileName)
{
	std::ofstream outFile(fileName);
	if (!outFile.is_open()) {
		std::cerr << "Error: Could not open file for writing: " << fileName << std::endl;
		return;
	}

	// saving drawable settings
	outFile << line_color.GetRGB() << " ";
	outFile << fill_style << " ";
	outFile << fill_color.GetRGB() << " ";
	outFile << std::to_string(static_cast<int>(view_style)) << " ";

	outFile << front_distance << " ";
	outFile << top_distance << " ";
	outFile << right_distance << " ";

	outFile << camera_pos.x << " " << camera_pos.y << " " << camera_pos.z << " ";
	outFile << camera_look.x << " " << camera_look.y << " " << camera_look.z << " ";

	outFile << camera_fov << "\n";

	for (Drawable* obj : figures)
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

	// loading drawable settings
	std::string line;

	std::getline(inFile, line);
	std::istringstream iss(line);

	wxUint32 color; iss >> color; line_color = color;
	iss >> fill_style;
	iss >> color; fill_color = color;
	int newView; iss >> newView; view_style = static_cast<view>(newView);
	iss >> front_distance;
	iss >> top_distance;
	iss >> right_distance;

	iss >> camera_pos.x >> camera_pos.y >> camera_pos.z;
	iss >> camera_look.x >> camera_look.y >> camera_look.z;

	iss >> camera_fov;


	while (std::getline(inFile, line)) 
	{
		std::istringstream iss(line);
		std::string type;
		iss >> type;

		if (type == "Line") 
		{
			double x1, y1, z1, x2, y2, z2;
			if (iss >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> color) 
			{
				addObj(new Line(Position(x1, y1, z1), Position(x2, y2, z2),color));
			}
		}
		else if (type == "Sphere") 
		{
			double x, y, z, radius;
			int meridians, parallels;
			if (iss >> x >> y >> z >> radius >> meridians >> parallels>> color) {
				addObj(new Sphere(Position(x, y, z), radius, meridians, parallels,color));
			}
		}
		else if (type == "Box")
		{
			double x1, y1, z1, x2, y2, z2;
			if (iss >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> color)
			{
				addObj(new Box(Position(x1, y1, z1), Position(x2, y2, z2), color));
			}
		}
		else
		{
			// throw error
		}
		// Add more cases for other Drawable types
	}

	inFile.close();
	if (inFile.fail()) {
		std::cerr << "Error: Could not properly close the file: " << fileName << std::endl;
	}
}
