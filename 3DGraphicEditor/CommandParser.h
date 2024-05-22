#pragma once
#include <string>
#include <vector>
#include "GUI.h"
#include "Drawable.h"

std::vector<std::string> parse_to_vector(wxString command) {
	std::string command_str = std::string(command.mb_str());
	std::vector<std::string> command_prompt;
	std::string text;
	for (auto i : command_str) {
		if (i == '>') {
			continue;
		}

		else if (i != ' ') {
			text += i;
		}
		else {
			command_prompt.push_back(text);
			text.clear();
		}
	}
	if (!text.empty()) {
		command_prompt.push_back(text);
	}
	return command_prompt;
}

Position get_a_point(std::string command) {
	std::vector<double> pos;
	std::string text;
	for (auto i : command) {
		if (i == '(' || i == ' ') {
			continue;
		}
		else if (i == ',' || i == ')') {
			pos.push_back(std::stod(text));
			text.clear();
		}
		
		else {
			text += i;
		}
	}
	Position p(pos[0], pos[1], pos[2]);
	return p;
}

wxColour get_a_color(std::string command) {
	std::vector<int> color_val;
	std::string text;
	for (auto i : command) {
		if (i == '(' || i == ' ') {
			continue;
		}
		else if (i == ',' || i == ')') {
			color_val.push_back(atoi(text.c_str()));
			text.clear();
		}

		else{
			
			text += i;
		}
	}
	wxColour color(color_val[0],color_val[1],color_val[2]);
	return color;
	
}

std::vector<int> get_a_sphere_lines(std::string command) {
	std::vector<int> sphere_lines;
	std::string text;
	for (auto i : command) {
		if (i == '(' || i == ' ') {
			continue;
		}
		else if (i == ',' || i == ')') {
			sphere_lines.push_back(atoi(text.c_str()));
			text.clear();
		}

		else {
			text += i;
		}
	}
	return sphere_lines;
}