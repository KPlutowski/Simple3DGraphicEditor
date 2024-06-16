#include "GUIMyFrame1.h"
#include "CommandParser.h"
#include "Line.h"
#include "Sphere.h"
#include "Box.h"
#include "Cone.h"
#include "Cylinder.h"

GUIMyFrame1::GUIMyFrame1(wxWindow* parent)
	:
	MyFrame1(parent)
{
	SetTitle("Projekt nr 045");
	Drawable::Camera::update();
	wxInitAllImageHandlers();
}

void GUIMyFrame1::Update(wxCommandEvent& event)
{
	// TODO: Implement Update

	std::vector<std::string> command_prompt;

	command_prompt = CommandParser::parse_to_vector(Command_panel->GetValue());

	bool error = false;
	//Wybór odpowiedniej komendy
	if (CommandParser::command_length_check(command_prompt, 0)) {
		m_error_message_box->SetLabelText("Error: No command given");
	}
	else if (command_prompt[0] == "set_line_color") {
		if (CommandParser::command_length_check(command_prompt, 2)) {
			try {
				Drawable::SetLineColor(CommandParser::get_a_color(command_prompt[1]));
				m_error_message_box->SetLabelText("");
			}
			catch (const std::exception& e) {
				if (m_error_message_box) {
					m_error_message_box->SetLabelText("Error: Invalid command arguments");
				}
			}
		}
		else {
			m_error_message_box->SetLabelText("Error: Not enough arguments");
		}
	}

	else if (command_prompt[0] == "line") {
		if (CommandParser::command_length_check(command_prompt, 3)) {
			try {
				Position start = CommandParser::get_a_point(command_prompt[1]);
				Position end = CommandParser::get_a_point(command_prompt[2]);

				Drawable::addObj(new Line(start, end));
				m_error_message_box->SetLabelText("");
			}
			catch (const std::exception& e) {
				if (m_error_message_box) {
					m_error_message_box->SetLabelText("Error: Invalid command arguments");
				}
			}
		}
		else {
			m_error_message_box->SetLabelText("Error: Not enough arguments");
		}
	}

	else if (command_prompt[0] == "box") {
		if (CommandParser::command_length_check(command_prompt, 3)) {
			try {
				Position start = CommandParser::get_a_point(command_prompt[1]);
				Position end = CommandParser::get_a_point(command_prompt[2]);
				Drawable::addObj(new Box(start, end));
				m_error_message_box->SetLabelText("");
			}
			catch (const std::exception& e) {
				if (m_error_message_box) {
					m_error_message_box->SetLabelText("Error: Invalid command arguments");
				}
			}
		}
		else {
			m_error_message_box->SetLabelText("Error: Not enough arguments");
		}
	}

	else if (command_prompt[0] == "sphere") {
		if (CommandParser::command_length_check(command_prompt, 4)) {
			try {
				Position point = CommandParser::get_a_point(command_prompt[1]);
				double r = std::stod(command_prompt[2]);
				std::vector<int> sphere_lines = CommandParser::get_a_sphere_lines(command_prompt[3]);
				int meridians = sphere_lines[0];
				int parallels = sphere_lines[1];

				Drawable::addObj(new Sphere(point, r, meridians, parallels));
				m_error_message_box->SetLabelText("");
			}
			catch (const std::exception& e) {
				if (m_error_message_box) {
					m_error_message_box->SetLabelText("Error: Invalid command arguments");
				}
			}
		}
		else {
			m_error_message_box->SetLabelText("Error: Not enough arguments");
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
				Drawable::addObj(new Cone(begin_base, r1, end_base, r2, n));
				m_error_message_box->SetLabelText("");
			}
			catch (const std::exception& e) {
				if (m_error_message_box) {
					m_error_message_box->SetLabelText("Error: Invalid command arguments");
				}
			}
		}
		else {
			m_error_message_box->SetLabelText("Error: Not enough arguments");
		}
	}

	else if (command_prompt[0] == "cylinder") {
		if (CommandParser::command_length_check(command_prompt, 5)) {
			try {
				Position begin_base = CommandParser::get_a_point(command_prompt[1]);
				Position end_base = CommandParser::get_a_point(command_prompt[2]);
				double r = std::stod(command_prompt[3]);
				int n = std::stoi(command_prompt[4]);
				Drawable::addObj(new Cylinder(begin_base, r, end_base, r, n));
				m_error_message_box->SetLabelText("");
			}
			catch (const std::exception& e) {
				if (m_error_message_box) {
					m_error_message_box->SetLabelText("Error: Invalid command arguments");
				}
			}
		}
		else {
			m_error_message_box->SetLabelText("Error: Not enough arguments");
		}
	}

	else if (command_prompt[0] == "delete") {
		if (CommandParser::command_length_check(command_prompt, 2)) {
			try {
				int id = std::stoi(command_prompt[1]);
				Drawable::deleteObj(id);
				m_error_message_box->SetLabelText("");
			}

			catch (const std::exception& e) {
				if (m_error_message_box) {
					m_error_message_box->SetLabelText("Error: Invalid command arguments");
				}
			}
		}
		else {
			m_error_message_box->SetLabelText("Error: Not enough arguments");
		}
	}

	else if (command_prompt[0] == "clear_all") {
		if (CommandParser::command_length_check(command_prompt, 1))
		{
			try
			{
				Drawable::clearAll();
				m_error_message_box->SetLabelText("");
			}
			catch (const std::exception& e) {
				if (m_error_message_box) {
					m_error_message_box->SetLabelText("Error: Invalid command arguments");
				}
			}
		}
		else {
			m_error_message_box->SetLabelText("Error: Not enough arguments");
		}
	}

	else if (command_prompt[0] == "move") {
		if (CommandParser::command_length_check(command_prompt, 3)) {
			try {
				int id = std::stoi(command_prompt[1]);
				Position shift = CommandParser::get_a_point(command_prompt[2]);
				Drawable::moveObj(id, shift.x, shift.y, shift.z);
				m_error_message_box->SetLabelText("");
			}
			catch (const std::exception& e) {
				if (m_error_message_box) {
					m_error_message_box->SetLabelText("Error: Invalid command arguments");
				}
			}
		}
		else {
			m_error_message_box->SetLabelText("Error: Not enough arguments");
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
				m_error_message_box->SetLabelText("");
			}
			catch (const std::exception& e) {
				if (m_error_message_box) {
					m_error_message_box->SetLabelText("Error: Invalid command arguments");
				}
			}
		}
		else {
			m_error_message_box->SetLabelText("Error: Not enough arguments");
		}
	}

	else if (command_prompt[0] == "save") {
		if (CommandParser::command_length_check(command_prompt, 2)) {
			try {
				std::string name = command_prompt[1];
				Drawable::saveToFile(name);
				m_error_message_box->SetLabelText("");
			}
			catch (const std::exception& e) {
				if (m_error_message_box) {
					m_error_message_box->SetLabelText("Error: Invalid command arguments");
				}
			}
		}
		else {
			m_error_message_box->SetLabelText("Error: Not enough arguments");
		}
	}

	else if (command_prompt[0] == "load") {
		if (CommandParser::command_length_check(command_prompt, 2)) {
			try {
				std::string name = command_prompt[1];
				Drawable::loadFromFile(name);
				m_error_message_box->SetLabelText("");
			}
			catch (const std::exception& e) {
				if (m_error_message_box) {
					m_error_message_box->SetLabelText("Error: Invalid command arguments");
				}
			}
		}
		else {
			m_error_message_box->SetLabelText("Error: Not enough arguments");
		}
	}

	else if (command_prompt[0] == "camera_look_at") {
		if (CommandParser::command_length_check(command_prompt, 2)) {
			try {
				Position newLook = CommandParser::get_a_point(command_prompt[1]);
				Drawable::Camera::setLookAt(newLook.x, newLook.y, newLook.z);
				m_error_message_box->SetLabelText("");
			}
			catch (const std::exception& e) {
				if (m_error_message_box) {
					m_error_message_box->SetLabelText("Error: Invalid command arguments");
				}
			}
		}
	}

	else if (command_prompt[0] == "camera_at") {
		if (CommandParser::command_length_check(command_prompt, 2)) {
			try {
				Position newPosition = CommandParser::get_a_point(command_prompt[1]);
				Drawable::Camera::setPosition(newPosition.x, newPosition.y, newPosition.z);
				m_error_message_box->SetLabelText("");
			}
			catch (const std::exception& e) {
				if (m_error_message_box) {
					m_error_message_box->SetLabelText("Error: Invalid command arguments");
				}
			}
		}
		else {
			m_error_message_box->SetLabelText("Error: Not enough arguments");
		}
	}

	else if (command_prompt[0] == "camera_fov") {
		if (CommandParser::command_length_check(command_prompt, 2)) {
			try {
				double newFov = std::stod(command_prompt[1]);
				Drawable::Camera::setFov(newFov);
				m_error_message_box->SetLabelText("");
			}
			catch (const std::exception& e) {
				if (m_error_message_box) {
					m_error_message_box->SetLabelText("Error: Invalid command arguments");
				}
			}
		}
		else {
			m_error_message_box->SetLabelText("Error: Not enough arguments");
		}
	}

	else if (command_prompt[0] == "touch") {
		if (CommandParser::command_length_check(command_prompt, 2)) {
			try {
				int id = std::stoi(command_prompt[1]);
				Drawable::touchObj(id);
				m_error_message_box->SetLabelText("");
			}
			catch (const std::exception& e) {
				if (m_error_message_box) {
					m_error_message_box->SetLabelText("Error: Invalid command arguments");
				}
			}
		}
		else {
			m_error_message_box->SetLabelText("Error: Not enough arguments");
		}
	}

	else if (command_prompt[0] == "set_view_range") {
		if (CommandParser::command_length_check(command_prompt, 3)) {
			try {
				double r = std::stod(command_prompt[2]);
				std::string name = command_prompt[1];

				if (name == "right")
				{
					Drawable::Camera::setRightDistance(r);
				}
				else if (name == "front")
				{
					Drawable::Camera::setFrontDistance(r);
				}
				else if (name == "top")
				{
					Drawable::Camera::setTopDistance(r);
				}
				m_error_message_box->SetLabelText("");
			}
			catch (const std::exception& e) {
				if (m_error_message_box) {
					m_error_message_box->SetLabelText("Error: Invalid command arguments");
				}
			}
		}
		else {
			m_error_message_box->SetLabelText("Error: Not enough arguments");
		}
	}

	else if (command_prompt[0] == "render_to_file") {
		if (CommandParser::command_length_check(command_prompt, 4)) {
			try {
				double w = std::stoi(command_prompt[1]);
				double h = std::stoi(command_prompt[2]);

				std::string name = command_prompt[3];

				Drawable::render_panel_to_bitmap(name, w, h, perspective_panel);
				m_error_message_box->SetLabelText("");
			}
			catch (const std::exception& e) {
				if (m_error_message_box) {
					m_error_message_box->SetLabelText("Error: Invalid command arguments");
				}
			}
		}
		else {
			m_error_message_box->SetLabelText("Error: Not enough arguments");
		}
	}

	else if (command_prompt[0] == "rotate_group") {
		if (CommandParser::command_length_check(command_prompt, 4)) {
			try {
				int id_group = std::stoi(command_prompt[1]);
				Position rotate_point = CommandParser::get_a_point(command_prompt[2]);
				Position rotate_angle = CommandParser::get_a_point(command_prompt[3]);
				Drawable::rotateGroup(id_group, rotate_point.x, rotate_point.y, rotate_point.z,
					rotate_angle.x, rotate_angle.y, rotate_angle.z);
				m_error_message_box->SetLabelText("");
			}
			catch (const std::exception& e) {
				if (m_error_message_box) {
					m_error_message_box->SetLabelText("Error: Invalid command arguments");
				}
			}
		}
	}

	else if (command_prompt[0] == "touch_group") {
		if (CommandParser::command_length_check(command_prompt, 2)) {
			try {
				int id = std::stoi(command_prompt[1]);
				Drawable::touchGroup(id);
				m_error_message_box->SetLabelText("");
			}
			catch (const std::exception& e) {
				if (m_error_message_box) {
					m_error_message_box->SetLabelText("Error: Invalid command arguments");
				}
			}
		}
		else {
			m_error_message_box->SetLabelText("Error: Not enough arguments");
		}
	}

	else if (command_prompt[0] == "move_group") {
		if (CommandParser::command_length_check(command_prompt, 3)) {
			try {
				int id_group = std::stoi(command_prompt[1]);
				Position shift = CommandParser::get_a_point(command_prompt[2]);
				Drawable::moveGroup(id_group, shift.x, shift.y, shift.z);
				m_error_message_box->SetLabelText("");
			}
			catch (const std::exception& e) {
				if (m_error_message_box) {
					m_error_message_box->SetLabelText("Error: Invalid command arguments");
				}
			}
		}
		else {
			m_error_message_box->SetLabelText("Error: Not enough arguments");
		}
	}

	else if (command_prompt[0] == "add_to_group") {
		if (CommandParser::command_length_check(command_prompt, 3)) {
			try {
				int group_id = std::stoi(command_prompt[1]);
				if (group_id > 0) {
				int element_id = std::stoi(command_prompt[2]);
				Drawable::add_to_group(group_id, element_id);
				m_error_message_box->SetLabelText("");

				}
				else {
					m_error_message_box->SetLabelText("Error: Group_id must be greater than 0!");
				}
			}
			catch (const std::exception& e) {
				if (m_error_message_box) {
					m_error_message_box->SetLabelText("Error: Invalid command arguments");
				}
			}
		}
		else {
			m_error_message_box->SetLabelText("Error: Not enough arguments");
		}
	}

	else {
		m_error_message_box->SetLabelText("Error: Unrecognized command");
	}

	// wxClients moved to Redraw()
	Redraw();

	// Update List
	Elements_ListBox->Clear();
	for (const auto& t : Drawable::getFiguresInfo())
	{
		Elements_ListBox->Append(t);
	}

	Command_panel->SetValue(wxT(">>"));
	Command_panel->SetInsertionPointEnd();
}

void GUIMyFrame1::OnSize(wxSizeEvent& event) {
	Redraw();
}

void GUIMyFrame1::Redraw() {
	wxClientDC dc1(vertical_side_panel);
	wxBufferedDC topView(&dc1);
	topView.Clear();

	wxClientDC dc2(side_panel);
	wxBufferedDC sideView(&dc2);
	sideView.Clear();

	wxClientDC dc3(horizontal_side_panel);
	wxBufferedDC frontView(&dc3);
	frontView.Clear();

	wxClientDC dc4(perspective_panel);
	wxBufferedDC perspectiveView(&dc4);
	perspectiveView.Clear();

	// Update when changing window size // size of drawable area
	Drawable::Camera::SetViewSize(vertical_side_panel->GetSize().x, vertical_side_panel->GetSize().y);

	Drawable::DrawAll(frontView, topView, sideView, perspectiveView);
}