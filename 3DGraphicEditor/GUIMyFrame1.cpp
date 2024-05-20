#include "GUIMyFrame1.h"

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{

}

void GUIMyFrame1::Update(wxCommandEvent& event)
{
	// TODO: Implement Update
	Command_panel->SetValue(wxT(">>"));
	Command_panel->SetInsertionPointEnd();
}