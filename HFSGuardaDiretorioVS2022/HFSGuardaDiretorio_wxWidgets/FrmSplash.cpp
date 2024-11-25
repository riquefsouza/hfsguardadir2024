#include "FrmSplash.h"

FrmSplash *frmSplash;

FrmSplash::FrmSplash(wxWindow* parent):
    wxDialog( parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDIALOG_NO_PARENT  )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("HFSGuardaDiretorio 2.0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	m_staticText1->SetFont( wxFont( 24, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );

	//bSizer1->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	bSizer1->Add(m_staticText1, 0, wxALL | wxEXPAND, 5);

	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Catalogador de Diret\u00f3rios"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	m_staticText2->SetFont( wxFont( 18, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );

	//bSizer1->Add( m_staticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	bSizer1->Add(m_staticText2, 0, wxALL | wxEXPAND, 5);

	gauge1 = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	gauge1->SetValue( 0 );
	//bSizer1->Add( gauge1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	bSizer1->Add(gauge1, 0, wxALL | wxEXPAND, 5);


	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( FrmSplash::FrmSplashClose ) );
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( FrmSplash::FrmSplashInitDialog ) );
}

FrmSplash::~FrmSplash()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( FrmSplash::FrmSplashClose ) );
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( FrmSplash::FrmSplashInitDialog ) );

}

void FrmSplash::FrmSplashClose( wxCloseEvent& event ) {
    event.Skip();
}

void FrmSplash::FrmSplashInitDialog( wxInitDialogEvent& event ) {
    event.Skip();
}

void FrmSplash::ProgressoLog(Progresso progresso)
{
  if (frmSplash!=NULL) {
	  if (progresso.posicao == 0) {
         frmSplash->gauge1->SetValue(progresso.minimo);
		 frmSplash->gauge1->SetRange(progresso.maximo);
	  }

	  frmSplash->gauge1->SetValue( progresso.posicao );
	  //frmSplash->gauge1->Update();
  }

}
