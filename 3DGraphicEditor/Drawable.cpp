#include <vector>
#include "GUIMyFrame1.h"
#include "Drawable.h"

std::vector<Drawable*> Drawable::figures;
wxColour Drawable::line_color = wxColour(0, 0, 0);;
bool Drawable::fill_style = false;
wxColour Drawable::fill_color = wxColour(255, 255, 255);
view Drawable::view_style = view::lines;
double Drawable::front_distance = 1;
double Drawable::top_distance = 1;
double Drawable::right_distance = 1;
Position Drawable::camera_pos = Position(0, 0, 500);
Position Drawable::camera_look = Position(0, 0, 0);
double Drawable::camera_fov = 60.0;

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

	return multiplyMatrix(multiplyMatrix(alphaRotation, betaRotation), gammaRotation);
}
