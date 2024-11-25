#include "FrmInfoDiretorio.h"

FrmInfoDiretorio *frmInfoDiretorio;

FrmInfoDiretorio::FrmInfoDiretorio( wxWindow* parent ):
    wxDialog( parent, wxID_ANY, wxT("Informa\u00e7\u00f5es do Diret\u00f3rio / Arquivo"), wxDefaultPosition, wxSize( 391,371 ), wxDEFAULT_DIALOG_STYLE  )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	panelLegenda = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxDOUBLE_BORDER|wxTAB_TRAVERSAL );
	wxGridSizer* gSizer4;
	gSizer4 = new wxGridSizer( 3, 2, 0, 0 );

	labArquivoComum = new wxStaticText( panelLegenda, wxID_ANY, wxT("[ARQ] - Arquivo comum"), wxDefaultPosition, wxDefaultSize, 0 );
	labArquivoComum->Wrap( -1 );
	gSizer4->Add( labArquivoComum, 0, wxALL, 5 );

	labArquivoOculto = new wxStaticText( panelLegenda, wxID_ANY, wxT("[HID] - Arquivo Oculto"), wxDefaultPosition, wxDefaultSize, 0 );
	labArquivoOculto->Wrap( -1 );
	gSizer4->Add( labArquivoOculto, 0, wxALL, 5 );

	labArquivoSistema = new wxStaticText( panelLegenda, wxID_ANY, wxT("[SYS] - Arquivo de Sistema"), wxDefaultPosition, wxDefaultSize, 0 );
	labArquivoSistema->Wrap( -1 );
	gSizer4->Add( labArquivoSistema, 0, wxALL, 5 );

	labLegendaDiretorio = new wxStaticText( panelLegenda, wxID_ANY, wxT("[DIR] - Diret\u00f3rio"), wxDefaultPosition, wxDefaultSize, 0 );
	labLegendaDiretorio->Wrap( -1 );
	gSizer4->Add( labLegendaDiretorio, 0, wxALL, 5 );

	labVolumeID = new wxStaticText( panelLegenda, wxID_ANY, wxT("[VOL] - Volume ID"), wxDefaultPosition, wxDefaultSize, 0 );
	labVolumeID->Wrap( -1 );
	gSizer4->Add( labVolumeID, 0, wxALL, 5 );

	labArquivoSomenteLeitura = new wxStaticText( panelLegenda, wxID_ANY, wxT("[ROL] - Arquivo Somente Leitura"), wxDefaultPosition, wxDefaultSize, 0 );
	labArquivoSomenteLeitura->Wrap( -1 );
	gSizer4->Add( labArquivoSomenteLeitura, 0, wxALL, 5 );


	panelLegenda->SetSizer( gSizer4 );
	panelLegenda->Layout();
	gSizer4->Fit( panelLegenda );
	bSizer1->Add( panelLegenda, 0, wxALL|wxEXPAND, 5 );

	lcInfo = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
    lcInfo->AppendColumn(wxT("Item"), wxLIST_FORMAT_LEFT, 100);
    lcInfo->AppendColumn(wxT("Descri\u00e7\u00e3o"), wxLIST_FORMAT_LEFT, 100);
    //lcInfo->SetColumnWidth(0, wxLIST_AUTOSIZE);
    //lcInfo->SetColumnWidth(1, wxLIST_AUTOSIZE);

	bSizer1->Add( lcInfo, 1, wxALL|wxEXPAND, 5 );

	btnOk = new wxButton( this, wxID_ANY, wxT("&Ok"), wxDefaultPosition, wxDefaultSize, 0 );
	btnOk->SetDefault();
	bSizer1->Add( btnOk, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_ACTIVATE, wxActivateEventHandler( FrmInfoDiretorio::FrmInfoDiretorioActivate ) );
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( FrmInfoDiretorio::FrmInfoDiretorioClose ) );
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( FrmInfoDiretorio::FrmInfoDiretorioInitDialog ) );
	btnOk->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FrmInfoDiretorio::btnOkClick ), NULL, this );
	lcInfo->Connect( wxEVT_COMMAND_LIST_COL_CLICK, wxListEventHandler( FrmInfoDiretorio::lcInfoListColClick ), NULL, this );
	lcInfo->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( FrmInfoDiretorio::lcInfoListItemSelected ), NULL, this );
}

FrmInfoDiretorio::~FrmInfoDiretorio()
{
	// Disconnect Events
	this->Disconnect( wxEVT_ACTIVATE, wxActivateEventHandler( FrmInfoDiretorio::FrmInfoDiretorioActivate ) );
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( FrmInfoDiretorio::FrmInfoDiretorioClose ) );
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( FrmInfoDiretorio::FrmInfoDiretorioInitDialog ) );
	btnOk->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FrmInfoDiretorio::btnOkClick ), NULL, this );
	lcInfo->Disconnect( wxEVT_COMMAND_LIST_COL_CLICK, wxListEventHandler( FrmInfoDiretorio::lcInfoListColClick ), NULL, this );
	lcInfo->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( FrmInfoDiretorio::lcInfoListItemSelected ), NULL, this );
}

void FrmInfoDiretorio::FrmInfoDiretorioActivate( wxActivateEvent& event ) {
    event.Skip();
}
void FrmInfoDiretorio::FrmInfoDiretorioClose( wxCloseEvent& event ) {
    event.Skip();
}
void FrmInfoDiretorio::FrmInfoDiretorioInitDialog( wxInitDialogEvent& event ) {
    event.Skip();

}

void FrmInfoDiretorio::btnOkClick( wxCommandEvent& event ) {
    event.Skip();

    this->EndModal(0);
}

void FrmInfoDiretorio::lcInfoListColClick( wxListEvent& event ) {
    event.Skip();
}

void FrmInfoDiretorio::lcInfoListItemSelected( wxListEvent& event ) {
    event.Skip();
}

void FrmInfoDiretorio::setDiretorio(Diretorio diretorio) {

	long nItem;
	unsigned int nLinha = 0;

	nItem = lcInfo->InsertItem(nLinha, "Aba:");
	lcInfo->SetItemData(nItem, nLinha);
	lcInfo->SetItem(nItem, 1, diretorio.getAba().getNome());
	nLinha++;

	nItem = lcInfo->InsertItem(nLinha, "Nome:");
	lcInfo->SetItemData(nItem, nLinha);
	lcInfo->SetItem(nItem, 1, diretorio.getNome());
	nLinha++;

	nItem = lcInfo->InsertItem(nLinha, "Tamanho:");
	lcInfo->SetItemData(nItem, nLinha);
	lcInfo->SetItem(nItem, 1, diretorio.getTamanhoFormatado());
	nLinha++;

	nItem = lcInfo->InsertItem(nLinha, "Tipo:");
	lcInfo->SetItemData(nItem, nLinha);
	lcInfo->SetItem(nItem, 1, diretorio.getTipo().getNome());
	nLinha++;

	nItem = lcInfo->InsertItem(nLinha, "Modificado:");
	lcInfo->SetItemData(nItem, nLinha);
	lcInfo->SetItem(nItem, 1, diretorio.getModificadoFormatado());
	nLinha++;

	nItem = lcInfo->InsertItem(nLinha, "Atributos:");
	lcInfo->SetItemData(nItem, nLinha);
	lcInfo->SetItem(nItem, 1, diretorio.getAtributos());
	nLinha++;

	nItem = lcInfo->InsertItem(nLinha, "Caminho:");
	lcInfo->SetItemData(nItem, nLinha);
	lcInfo->SetItem(nItem, 1, diretorio.getCaminho());
	
	lcInfo->SetColumnWidth(1, diretorio.getCaminho().length() * 8);
}
