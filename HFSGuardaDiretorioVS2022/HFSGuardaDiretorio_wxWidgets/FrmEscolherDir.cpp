#include "FrmEscolherDir.h"
// ---------------------------------------------------------------------------
FrmEscolherDir *frmEscolherDir;

// ---------------------------------------------------------------------------
FrmEscolherDir::FrmEscolherDir( wxWindow* parent ):
     wxDialog( parent, wxID_ANY, wxT("Escolha o Diret\u00f3rio"), wxDefaultPosition, wxSize( 367,392 ), wxDEFAULT_DIALOG_STYLE  )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	arvoreDiretorio = new wxGenericDirCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDIRCTRL_3D_INTERNAL|wxSUNKEN_BORDER, wxEmptyString, 0 );

	arvoreDiretorio->ShowHidden( false );
	bSizer1->Add( arvoreDiretorio, 1, wxEXPAND | wxALL, 5 );

	panelDiretorio = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );

	labDiretorio = new wxStaticText( panelDiretorio, wxID_ANY, wxT("Diret\u00f3rio escolhido:"), wxDefaultPosition, wxDefaultSize, 0 );
	labDiretorio->Wrap( -1 );
	bSizer2->Add( labDiretorio, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	edtDiretorio = new wxTextCtrl( panelDiretorio, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( edtDiretorio, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	panelDiretorio->SetSizer( bSizer2 );
	panelDiretorio->Layout();
	bSizer2->Fit( panelDiretorio );
	bSizer1->Add( panelDiretorio, 0, wxALL|wxEXPAND, 5 );

	panelBotoes = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );


	bSizer3->Add( 0, 0, 1, wxEXPAND, 5 );

	btnOk = new wxButton( panelBotoes, wxID_ANY, wxT("&Ok"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( btnOk, 0, wxALL, 5 );

	btnCancelar = new wxButton( panelBotoes, wxID_ANY, wxT("&Cancelar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( btnCancelar, 0, wxALL, 5 );


	bSizer3->Add( 0, 0, 1, wxEXPAND, 5 );


	panelBotoes->SetSizer( bSizer3 );
	panelBotoes->Layout();
	bSizer3->Fit( panelBotoes );
	bSizer1->Add( panelBotoes, 0, wxALL|wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	arvoreDiretorio->Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( FrmEscolherDir::arvoreDiretorioSelChanged ), NULL, this );
	btnOk->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FrmEscolherDir::btnOkClick ), NULL, this );
	btnCancelar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FrmEscolherDir::btnCancelarClick ), NULL, this );
}

FrmEscolherDir::~FrmEscolherDir()
{
	// Disconnect Events
	arvoreDiretorio->Disconnect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( FrmEscolherDir::arvoreDiretorioSelChanged ), NULL, this );
	btnOk->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FrmEscolherDir::btnOkClick ), NULL, this );
	btnCancelar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FrmEscolherDir::btnCancelarClick ), NULL, this );

}

void FrmEscolherDir::arvoreDiretorioSelChanged( wxTreeEvent& event ) {
    event.Skip();
}

void FrmEscolherDir::btnOkClick( wxCommandEvent& event ) {
    event.Skip();
}

void FrmEscolherDir::btnCancelarClick( wxCommandEvent& event ) {
    event.Skip();
}
