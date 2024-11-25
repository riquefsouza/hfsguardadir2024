#include "FrmSobre.h"

FrmSobre *frmSobre;

FrmSobre::FrmSobre( wxWindow* parent ) :
    wxDialog( parent, wxID_ANY, wxT("Sobre o Catalogador"), wxDefaultPosition, wxSize( 457,179 ), wxDEFAULT_DIALOG_STYLE )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("HFSGuardaDir 2.0 - Catalogador de Diret\u00f3rios"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticText1->Wrap( -1 );
	m_staticText1->SetFont( wxFont( 14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );

	bSizer1->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Desenvolvido em C++ com WxWindows, Vers\u00e3o: 2.0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer1->Add( m_staticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("Por Henrique Figueiredo de Souza"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	bSizer1->Add( m_staticText3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("Todos os direitos reservados, 2024"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	bSizer1->Add( m_staticText4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	btnOk = new wxButton( this, wxID_ANY, wxT("&Ok"), wxDefaultPosition, wxDefaultSize, 0 );
	btnOk->SetDefault();
	bSizer1->Add( btnOk, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( FrmSobre::FrmSobreClose ) );
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( FrmSobre::FrmSobreInitDialog ) );
	btnOk->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FrmSobre::btnOkClick ), NULL, this );
}

FrmSobre::~FrmSobre()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( FrmSobre::FrmSobreClose ) );
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( FrmSobre::FrmSobreInitDialog ) );
	btnOk->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FrmSobre::btnOkClick ), NULL, this );

}

void FrmSobre::FrmSobreClose( wxCloseEvent& event ) {
    event.Skip();
}

void FrmSobre::FrmSobreInitDialog( wxInitDialogEvent& event ) {
    event.Skip();
}

void FrmSobre::btnOkClick( wxCommandEvent& event ) {
    event.Skip();

    this->EndModal(0);
}
