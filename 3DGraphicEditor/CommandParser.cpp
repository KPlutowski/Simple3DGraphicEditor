#include "CommandParser.h"
#include "GUIMyFrame1.h"

std::vector<std::string> CommandParser::parse_to_vector(wxString command) {
	std::string command_str = command.ToStdString();
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

Position CommandParser::get_a_point(std::string command) {
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

wxColour CommandParser::get_a_color(std::string command) {
	std::vector<int> color_val;
	std::string text;
	for (auto i : command) {
		if (i == '(' || i == ' ') {
			continue;
		}
		else if (i == ',' || i == ')') {
			color_val.push_back(std::stoi(text));
			text.clear();
		}

		else {

			text += i;
		}
	}
	wxColour color(color_val[0], color_val[1], color_val[2]);
	return color;
	

}

std::vector<int> CommandParser::get_a_sphere_lines(std::string command) {
	std::vector<int> sphere_lines;
	std::string text;
	for (auto i : command) {
		if (i == '(' || i == ' ') {
			continue;
		}
		else if (i == ',' || i == ')') {
			sphere_lines.push_back(std::stoi(text));
			text.clear();
		}

		else {
			text += i;
		}
	}
	
	return sphere_lines;
}

bool CommandParser::command_length_check(std::vector<std::string> command, int length) {
	return command.size() == length;
}