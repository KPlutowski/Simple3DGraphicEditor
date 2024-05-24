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
Position Drawable::camera_pos = Position(1, 1, 1);
Position Drawable::camera_look = Position(0, 0, 0);
double Drawable::camera_fov = 45.0;

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
		figures[index]->move(x_shift, y_shift, z_shift);
}

void Drawable::rotateObj(int index, double x_cord, double y_cord, double z_cord, double alpha, double beta, double gamma) {
	if (index >= 1 && index <= figures.size())
		figures[index]->rotate(x_cord, y_cord, z_cord, alpha, beta, gamma);
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
		return figures[index];
	return nullptr;
}

std::vector<Drawable*> Drawable::getAllObjs() {
	return figures;
}

void Drawable::SetLineColor(const wxColour& newColour){
	line_color = newColour;
}