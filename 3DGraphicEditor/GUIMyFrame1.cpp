#include "GUIMyFrame1.h"
#include "CommandParser.h"

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{

}

void GUIMyFrame1::Update(wxCommandEvent& event)
{
	// TODO: Implement Update
	std::vector<std::string> command_prompt = parse_to_vector(Command_panel->GetValue());
	
	//Wybór odpowiedniej komendy
	if (command_prompt[0] == "set_line_color") {
		wxColour line_color = get_a_color(command_prompt[1]);
	}

	else if (command_prompt[0] == "line") {
		Position begin = get_a_point(command_prompt[1]);
		Position end = get_a_point(command_prompt[2]);
	}

	else if (command_prompt[0] == "box") {
		Position begin = get_a_point(command_prompt[1]);
		Position end = get_a_point(command_prompt[2]);

	}

	else if (command_prompt[0] == "sphere") {
		Position point = get_a_point(command_prompt[1]);
		double r = std::stod(command_prompt[2]);
		std::vector<int> sphere_lines = get_a_sphere_lines(command_prompt[3]);
		int n = sphere_lines[0];
		int m = sphere_lines[1];
	}

	else if (command_prompt[0] == "cone") {
		Position begin_base = get_a_point(command_prompt[1]);
		double r1 = std::stod(command_prompt[2]);
		Position end_base = get_a_point(command_prompt[3]);
		double r2 = std::stod(command_prompt[4]);
		int n = std::stoi(command_prompt[5]);
	}

	else if (command_prompt[0] == "cylinder") {
		Position begin_base = get_a_point(command_prompt[1]);
		Position end_base = get_a_point(command_prompt[2]);
		double r = std::stod(command_prompt[3]);
		int n = std::stoi(command_prompt[4]);
	}

	else if (command_prompt[0] == "delete") {
		int id = std::stoi(command_prompt[1]);
	}

	else if (command_prompt[0] == "clear_all") {

	}

	else if (command_prompt[0] == "move") {
		int id = std::stoi(command_prompt[1]);
		Position shift = get_a_point(command_prompt[2]);
	}

	else if (command_prompt[0] == "rotate") {
		int id = std::stoi(command_prompt[1]);
		Position rotate_point = get_a_point(command_prompt[2]);
		Position rotate_angle = get_a_point(command_prompt[3]);

	}

	else if (command_prompt[0] == "save") {
		std::string name = command_prompt[1];
	}

	else if (command_prompt[0] == "load") {
		std::string name = command_prompt[1];
	}

	else {
		std::cout << "Z³a komenda" << std::endl;
	}
	Command_panel->SetValue(wxT(">>"));
	Command_panel->SetInsertionPointEnd();
}