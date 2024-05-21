#include <vector>
#include "GUI.h"
#include "Drawable.h"

std::vector<Drawable*> Drawable::objs;
bool Drawable::fill_style = false;
wxColour Drawable::fill_color = wxColour(255, 255, 255);
view Drawable::view_style = view::lines;
double Drawable::front_distance = 1;
double Drawable::top_distance = 1;
double Drawable::right_distance = 1;
Position Drawable::camera_pos = {1, 1, 1};
Position Drawable::camera_look = {0, 0, 0};
double Drawable::camera_fov = 45.0;

void Drawable::addObj(Drawable* obj) {
	objs.push_back(obj);
}

void Drawable::deleteObj(int index) {
	if (index >= 1 && index <= objs.size()) 
		objs.erase(objs.begin() + index - 1);
}

void Drawable::clearAll() {
	for (auto&& obj : objs)
		delete obj;
	objs.clear();
}

void Drawable::moveObj(int index, double x_shift, double y_shift, double z_shift) {
	if (index >= 1 && index <= objs.size())
		objs[index]->move(x_shift, y_shift, z_shift);
}

void Drawable::rotateObj(int index, double x_cord, double y_cord, double z_cord, double alpha, double beta, double gamma) {
	if (index >= 1 && index <= objs.size())
		objs[index]->rotate(x_cord, y_cord, z_cord, alpha, beta, gamma);
}

void Drawable::touchObj(int index) {
	//TODO
}

Drawable* Drawable::getObj(int index) {
	if (index >= 1 && index <= objs.size())
		return objs[index];
}

std::vector<Drawable*> Drawable::getAllObjs() {
	return objs;
}