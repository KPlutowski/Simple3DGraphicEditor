///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.1.0-0-g733bf3d)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUI.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );

	vertical_side_panle = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer4->Add( vertical_side_panle, 1, wxEXPAND | wxALL, 5 );

	side_panel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer4->Add( side_panel, 1, wxEXPAND | wxALL, 5 );


	bSizer3->Add( bSizer4, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );

	horizontal_side_panel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer6->Add( horizontal_side_panel, 1, wxEXPAND | wxALL, 5 );

	perspective_panel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer6->Add( perspective_panel, 1, wxEXPAND | wxALL, 5 );


	bSizer3->Add( bSizer6, 1, wxEXPAND, 5 );


	bSizer2->Add( bSizer3, 1, wxEXPAND, 5 );

	Elements_ListBox = new wxListBox( this, wxID_ANY, wxPoint( -1,-1 ), wxSize( 200,-1 ), 0, NULL, wxLB_MULTIPLE );
	bSizer2->Add( Elements_ListBox, 0, wxALL, 5 );


	bSizer1->Add( bSizer2, 1, wxEXPAND, 5 );

	Command_panel = new wxTextCtrl( this, wxID_ANY, wxT(">>"), wxDefaultPosition, wxSize( 400,-1 ), 0 );
	bSizer1->Add( Command_panel, 0, wxALL, 10 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	Command_panel->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( MyFrame1::Update ), NULL, this );
}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	Command_panel->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( MyFrame1::Update ), NULL, this );

}
