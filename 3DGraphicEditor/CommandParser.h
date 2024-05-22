#pragma once
#include <string>
#include <vector>
#include "GUI.h"
#include "Drawable.h"

class CommandParser {
public:
	std::vector<std::string> parse_to_vector(wxString command);
	Position get_a_point(std::string command);
	wxColour get_a_color(std::string command);
	std::vector<int> get_a_sphere_lines(std::string command);
	bool command_length_check(std::vector<std::string> command, int length);
	
};




 