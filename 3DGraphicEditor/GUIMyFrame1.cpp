#include "GUIMyFrame1.h"
#include "CommandParser.h"
#include "Line.h"

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{

}

void GUIMyFrame1::Update(wxCommandEvent& event)
{
	std::vector<std::string> command_prompt;

	command_prompt = CommandParser::parse_to_vector(Command_panel->GetValue());

	bool error = false;
	//Wybór odpowiedniej komendy
	if (command_prompt[0] == "set_line_color") {
		if (CommandParser::command_length_check(command_prompt, 2)) {
			try {
				Drawable::SetLineColor(CommandParser::get_a_color(command_prompt[1]));
			}
			catch(const std::exception &e){}
		

		}
	}

	else if (command_prompt[0] == "line") {
		if (CommandParser::command_length_check(command_prompt, 3)) {
			try {
				Position start = CommandParser::get_a_point(command_prompt[1]);
				Position end = CommandParser::get_a_point(command_prompt[2]);

				Drawable::addObj(new Line(start, end));
			}
			catch (const std::exception& e) {
				error = true;
			}
		}
	}

	else if (command_prompt[0] == "box") {
		if (CommandParser::command_length_check(command_prompt, 3)) {
			try {
				Position begin = CommandParser::get_a_point(command_prompt[1]);
				Position end = CommandParser::get_a_point(command_prompt[2]);
			}
			catch (const std::exception& e) {
				if (Command_panel) {
					Command_panel->SetValue("ERROR");
				}
			}
		}

	}

	else if (command_prompt[0] == "sphere") {
		if (CommandParser::command_length_check(command_prompt, 4)) {
			try {
				Position point = CommandParser::get_a_point(command_prompt[1]);
			double r = std::stod(command_prompt[2]);
			std::vector<int> sphere_lines = CommandParser::get_a_sphere_lines(command_prompt[3]);
			int n = sphere_lines[0];
			int m = sphere_lines[1];

			}
			catch (const std::exception& e) {
				if (Command_panel) {
					Command_panel->SetValue("ERROR");
				}
			}
		}
	}

	else if (command_prompt[0] == "cone") {
		if (CommandParser::command_length_check(command_prompt, 6)) {
			try {
				Position begin_base = CommandParser::get_a_point(command_prompt[1]);
				double r1 = std::stod(command_prompt[2]);
				Position end_base = CommandParser::get_a_point(command_prompt[3]);
				double r2 = std::stod(command_prompt[4]);
				int n = std::stoi(command_prompt[5]);
			}
		catch (const std::exception& e) {
			if (Command_panel) {
				Command_panel->SetValue("ERROR");
			}
		}
		}

	}

	else if (command_prompt[0] == "cylinder") {
		if (CommandParser::command_length_check(command_prompt, 5)) {
			try {
				Position begin_base = CommandParser::get_a_point(command_prompt[1]);
				Position end_base = CommandParser::get_a_point(command_prompt[2]);
				double r = std::stod(command_prompt[3]);
				int n = std::stoi(command_prompt[4]);
		}
			catch (const std::exception& e) {
				if (Command_panel) {
					Command_panel->SetValue("ERROR");
				}
			}
		}
	}

	else if (command_prompt[0] == "delete") {
		if (CommandParser::command_length_check(command_prompt, 2)) {
			try {
				int id = std::stoi(command_prompt[1]);
				Drawable::deleteObj(id);
			}

			catch (const std::exception& e) {
				if (Command_panel) {
					Command_panel->SetValue("ERROR");
				}
			}
		}
	}

	else if (command_prompt[0] == "clear_all") {
		if (CommandParser::command_length_check(command_prompt, 1)) 
		{
			try 
			{
				Drawable::clearAll();
			}
			catch (const std::exception& e) {
				if (Command_panel) {
					Command_panel->SetValue("ERROR");
				}
			}
		}

	}

	else if (command_prompt[0] == "move") {
		if (CommandParser::command_length_check(command_prompt, 3)) {
			try {
				int id = std::stoi(command_prompt[1]);
				Position shift = CommandParser::get_a_point(command_prompt[2]);
				Drawable::moveObj(id, shift.x, shift.y, shift.z);
			}
			catch (const std::exception& e) {
				if (Command_panel) {
					Command_panel->SetValue("ERROR");
				}
			}
		}
	}

	else if (command_prompt[0] == "rotate") {
		if (CommandParser::command_length_check(command_prompt, 4)) {
			try {
				int id = std::stoi(command_prompt[1]);
				Position rotate_point = CommandParser::get_a_point(command_prompt[2]);
				Position rotate_angle = CommandParser::get_a_point(command_prompt[3]);
				Drawable::rotateObj(id, rotate_point.x, rotate_point.y, rotate_point.z,
					rotate_angle.x, rotate_angle.y, rotate_angle.z);
			}
			catch (const std::exception& e) {
				if (Command_panel) {
					Command_panel->SetValue("ERROR");
				}
			}
		}

	}

	else if (command_prompt[0] == "save") {
		if (CommandParser::command_length_check(command_prompt, 2)) {
			try {
				std::string name = command_prompt[1];
			}
			catch (const std::exception& e) {
				if (Command_panel) {
					Command_panel->SetValue("ERROR");
				}
			}
		}
	}

	else if (command_prompt[0] == "load") {
		if (CommandParser::command_length_check(command_prompt, 2)) {
			try {
				std::string name = command_prompt[1];
			}
			catch (const std::exception& e) {
				if (Command_panel) {
					Command_panel->SetValue("ERROR");
				}
			}
		}
	}
	else if (error) {
		
	}
	else {
		Command_panel->SetValue("ERROR");
	}

	
	wxClientDC dc1 = wxClientDC(vertical_side_panel);
	wxBufferedDC topView(&dc1);
	topView.Clear();

	wxClientDC dc2 = wxClientDC(side_panel);
	wxBufferedDC sideView(&dc2);
	sideView.Clear();

	wxClientDC dc3 = wxClientDC(horizontal_side_panel);
	wxBufferedDC frontView(&dc3);
	frontView.Clear();

	wxClientDC dc4 = wxClientDC(perspective_panel);
	wxBufferedDC perspectiveView(&dc4);
	perspectiveView.Clear();

	Drawable::DrawAll(frontView, topView, sideView, perspectiveView);
	//Command_panel->SetValue(wxT(">>"));
	Command_panel->SetInsertionPointEnd();
}