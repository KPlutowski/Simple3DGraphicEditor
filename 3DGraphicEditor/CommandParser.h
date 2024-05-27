#pragma once
#include <string>
#include <vector>
#include "GUI.h"
#include "Drawable.h"

class CommandParser {
public:
	static std::vector<std::string> parse_to_vector(wxString command);
	static Position get_a_point(std::string command);
	static wxColour get_a_color(std::string command);
	static std::vector<int> get_a_sphere_lines(std::string command);
	static bool command_length_check(std::vector<std::string> command, int length);
};
