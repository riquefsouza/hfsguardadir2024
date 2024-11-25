#include "FrmCompararDiretorio.h"
#include "FrmPrincipal.h"

#include "hfsguardadir\comum\Rotinas.h"
#include "hfsguardadir\objetosgui\Dialogo.h"
#include "hfsguardadir\catalogador\Catalogador.h"
#include "hfsguardadir\objetosbo\AbaBO.h"
#include "hfsguardadir\objetosbo\DiretorioBO.h"

using namespace hfsguardadir::comum;
using namespace hfsguardadir::objetosgui;
using namespace hfsguardadir::objetosbo;
using namespace hfsguardadir::catalogador;

// ---------------------------------------------------------------------------
FrmCompararDiretorio *frmCompararDiretorio;

// ---------------------------------------------------------------------------
FrmCompararDiretorio::FrmCompararDiretorio( wxWindow* parent ):
    wxFrame( parent, wxID_ANY, wxT("Comparar Diret\u00f3rios"), wxDefaultPosition, wxSize( 688,572 ), wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	panelSuperior = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );

	btnCompararDiretorios = new wxButton( panelSuperior, wxID_ANY, wxT("Comparar Diret\u00f3rios"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( btnCompararDiretorios, 0, wxALL, 5 );

	pb = new wxGauge( panelSuperior, wxID_ANY, 100, wxDefaultPosition, wxSize( -1,21 ), wxGA_HORIZONTAL );
	pb->SetValue( 0 );
	bSizer2->Add( pb, 1, wxALL, 5 );

	btnSalvarLog = new wxButton( panelSuperior, wxID_ANY, wxT("Salvar Log"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( btnSalvarLog, 0, wxALL, 5 );


	panelSuperior->SetSizer( bSizer2 );
	panelSuperior->Layout();
	bSizer2->Fit( panelSuperior );
	bSizer1->Add( panelSuperior, 0, wxEXPAND | wxALL, 5 );

	panelDiretorio = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );

	panelDiretorio1 = new wxPanel( panelDiretorio, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );

	wxArrayString cmbAba1Choices;
	cmbAba1 = new wxChoice( panelDiretorio1, wxID_ANY, wxDefaultPosition, wxDefaultSize, cmbAba1Choices, 0 );
	cmbAba1->SetSelection( 0 );
	bSizer5->Add( cmbAba1, 0, wxALL|wxEXPAND, 5 );

	arvoreDiretorio1 = new Arvore(panelDiretorio1, frmPrincipal->imageList16);
	bSizer5->Add( arvoreDiretorio1, 1, wxALL|wxEXPAND, 5 );
	
	panelDiretorio1->SetSizer( bSizer5 );
	panelDiretorio1->Layout();
	bSizer5->Fit( panelDiretorio1 );
	bSizer4->Add( panelDiretorio1, 1, wxEXPAND | wxALL, 5 );

	panelDiretorio2 = new wxPanel( panelDiretorio, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );

	wxArrayString cmbAba2Choices;
	cmbAba2 = new wxChoice( panelDiretorio2, wxID_ANY, wxDefaultPosition, wxDefaultSize, cmbAba2Choices, 0 );
	cmbAba2->SetSelection( 0 );
	bSizer6->Add( cmbAba2, 0, wxALL|wxEXPAND, 5 );

	arvoreDiretorio2 = new Arvore( panelDiretorio2, frmPrincipal->imageList16 );
	bSizer6->Add( arvoreDiretorio2, 1, wxALL|wxEXPAND, 5 );
	
	panelDiretorio2->SetSizer( bSizer6 );
	panelDiretorio2->Layout();
	bSizer6->Fit( panelDiretorio2 );
	bSizer4->Add( panelDiretorio2, 1, wxEXPAND | wxALL, 5 );


	panelDiretorio->SetSizer( bSizer4 );
	panelDiretorio->Layout();
	bSizer4->Fit( panelDiretorio );
	bSizer1->Add( panelDiretorio, 1, wxEXPAND | wxALL, 5 );

	labDiferencasEncontradas = new wxStaticText( this, wxID_ANY, wxT("Diferen\u00e7as Encontradas"), wxDefaultPosition, wxDefaultSize, 0 );
	labDiferencasEncontradas->Wrap( -1 );
	bSizer1->Add( labDiferencasEncontradas, 0, wxALL|wxEXPAND, 5 );

	tabelaComparador = new Tabela( this, true, frmPrincipal->imageList16, frmPrincipal->imageList32);
    tabelaComparador->AppendColumn(wxT("Nome"), wxLIST_FORMAT_LEFT, 300);
    tabelaComparador->AppendColumn(wxT("Tamanho"), wxLIST_FORMAT_LEFT, 100);
    tabelaComparador->AppendColumn(wxT("Tipo"), wxLIST_FORMAT_LEFT, 70);
    tabelaComparador->AppendColumn(wxT("Modificado"), wxLIST_FORMAT_LEFT, 120);
    tabelaComparador->AppendColumn(wxT("Atributos"), wxLIST_FORMAT_LEFT, 90);
    tabelaComparador->AppendColumn(wxT("Caminho"), wxLIST_FORMAT_LEFT, 300);

    tabelaComparador->SetImageList(frmPrincipal->imageList32, wxIMAGE_LIST_NORMAL);
    tabelaComparador->SetImageList(frmPrincipal->imageList16, wxIMAGE_LIST_SMALL);

	bSizer1->Add( tabelaComparador, 1, wxALL|wxEXPAND, 5 );

	this->SetSizer( bSizer1 );
	this->Layout();
	barraStatus = this->CreateStatusBar( 2, wxST_SIZEGRIP, wxID_ANY );
	barraStatus->SetStatusText("Total de diferenças encontradas:");

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_ACTIVATE, wxActivateEventHandler( FrmCompararDiretorio::FrmCompararDiretorioActivate ) );
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( FrmCompararDiretorio::FrmCompararDiretorioClose ) );
	btnCompararDiretorios->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FrmCompararDiretorio::btnCompararDiretoriosClick ), NULL, this );
	btnSalvarLog->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FrmCompararDiretorio::btnSalvarLogClick ), NULL, this );
	cmbAba1->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( FrmCompararDiretorio::cmbAba1Choice ), NULL, this );
	arvoreDiretorio1->Connect( wxEVT_COMMAND_TREE_GET_INFO, wxTreeEventHandler( FrmCompararDiretorio::arvoreDiretorio1GetInfo ), NULL, this );
	arvoreDiretorio1->Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( FrmCompararDiretorio::arvoreDiretorio1SelChanged ), NULL, this );
	cmbAba2->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( FrmCompararDiretorio::cmbAba2Choice ), NULL, this );
	arvoreDiretorio2->Connect( wxEVT_COMMAND_TREE_GET_INFO, wxTreeEventHandler( FrmCompararDiretorio::arvoreDiretorio2GetInfo ), NULL, this );
	arvoreDiretorio2->Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( FrmCompararDiretorio::arvoreDiretorio2SelChanged ), NULL, this );
	tabelaComparador->Connect( wxEVT_COMMAND_LIST_COL_CLICK, wxListEventHandler( FrmCompararDiretorio::tabelaComparadorListColClick ), NULL, this );
	tabelaComparador->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( FrmCompararDiretorio::tabelaComparadorListItemSelected ), NULL, this );

	montarArvores();
	LimparComparacao();

}

FrmCompararDiretorio::~FrmCompararDiretorio()
{
	// Disconnect Events
	this->Disconnect( wxEVT_ACTIVATE, wxActivateEventHandler( FrmCompararDiretorio::FrmCompararDiretorioActivate ) );
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( FrmCompararDiretorio::FrmCompararDiretorioClose ) );
	btnCompararDiretorios->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FrmCompararDiretorio::btnCompararDiretoriosClick ), NULL, this );
	btnSalvarLog->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FrmCompararDiretorio::btnSalvarLogClick ), NULL, this );
	cmbAba1->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( FrmCompararDiretorio::cmbAba1Choice ), NULL, this );
	arvoreDiretorio1->Disconnect( wxEVT_COMMAND_TREE_GET_INFO, wxTreeEventHandler( FrmCompararDiretorio::arvoreDiretorio1GetInfo ), NULL, this );
	arvoreDiretorio1->Disconnect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( FrmCompararDiretorio::arvoreDiretorio1SelChanged ), NULL, this );
	cmbAba2->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( FrmCompararDiretorio::cmbAba2Choice ), NULL, this );
	arvoreDiretorio2->Disconnect( wxEVT_COMMAND_TREE_GET_INFO, wxTreeEventHandler( FrmCompararDiretorio::arvoreDiretorio2GetInfo ), NULL, this );
	arvoreDiretorio2->Disconnect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( FrmCompararDiretorio::arvoreDiretorio2SelChanged ), NULL, this );
	tabelaComparador->Disconnect( wxEVT_COMMAND_LIST_COL_CLICK, wxListEventHandler( FrmCompararDiretorio::tabelaComparadorListColClick ), NULL, this );
	tabelaComparador->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( FrmCompararDiretorio::tabelaComparadorListItemSelected ), NULL, this );

}

void FrmCompararDiretorio::ProgressoLog(Progresso progresso)
{
  if (frmCompararDiretorio!=NULL) {
	  if (progresso.posicao == 0) {
         frmCompararDiretorio->pb->SetValue(progresso.minimo);
		 frmCompararDiretorio->pb->SetRange(progresso.maximo);
	  }

	  frmCompararDiretorio->pb->SetValue( progresso.posicao );
  }
}

void FrmCompararDiretorio::LimparComparacao() {
	pb->SetValue(0);
	tabelaComparador->limpar();
	tabelaComparador->selecionaLinha(0);
	//tabelaComparador->setSombrearLinhas(true);
	btnSalvarLog->Enable(false);
	barraStatus->SetStatusText("",1);
}


void FrmCompararDiretorio::FrmCompararDiretorioActivate( wxActivateEvent& event ) {
	 event.Skip();
}

void FrmCompararDiretorio::FrmCompararDiretorioClose( wxCloseEvent& event ) {
	 event.Skip();
}

void FrmCompararDiretorio::btnCompararDiretoriosClick( wxCommandEvent& event ) {
	 event.Skip();

	 wxString sCaminhoDir1 = "", sCaminhoDir2 = "";
	 bool bSelecionado;

	 bSelecionado = false;
	 if (arvoreDiretorio1->GetSelection().IsOk()) {
		 catalogador->LerArvoreDiretorio(arvoreDiretorio1, arvoreDiretorio1->GetSelection(),
			 barraStatus);
		 sCaminhoDir1 = barraStatus->GetStatusText(1);

		 if (arvoreDiretorio2->GetSelection().IsOk()) {
			 catalogador->LerArvoreDiretorio(arvoreDiretorio2,
				 arvoreDiretorio2->GetSelection(), barraStatus);
			 sCaminhoDir2 = barraStatus->GetStatusText(1);
			 bSelecionado = true;
		 }
	 }

	 LimparComparacao();

	 if (bSelecionado) {
		 Comparar(sCaminhoDir1, sCaminhoDir2);
	 }
	 else {
		 Dialogo::mensagemInfo(this,
			 "FrmCompararDiretorio.DiretoriosNaoSelecionados");
	 }
}

void FrmCompararDiretorio::btnSalvarLogClick( wxCommandEvent& event ) {
	 event.Skip();

	 wxString sLog;
	 wxArrayString listaLocal;

	 if (listaCompara.size() > 0) {
		 sLog = Rotinas::AppDirPath() + Rotinas::BARRA_INVERTIDA
			 + Rotinas::formataDate(Rotinas::FORMATO_DHARQUIVO, wxDateTime::Now())
			 + "_Comparacao.log";

		 for each(Diretorio diretorio in listaCompara) {
			 listaLocal.Add(diretorio.getCaminho());
		 }

		 Rotinas::SListSaveToFile(listaLocal, sLog);

		 Dialogo::mensagemInfo(this,
			 "FrmCompararDiretorio.LogSalvoMemoDirSistema");
	 }
}

void FrmCompararDiretorio::cmbAba1Choice( wxCommandEvent& event ) {
	 event.Skip();

	 Aba *aba;

	 SetCursor(wxCURSOR_WAIT);

	 arvoreDiretorio1->limpar();
	 aba = AbaBO::getInstancia()->pegaAbaPorOrdem(catalogador->listaAbas,
		 cmbAba1->GetSelection() + 1);
	 catalogador->CarregarArvore(arvoreDiretorio1, *aba);

	 if (arvoreDiretorio1->GetCount() > 0) {
		 arvoreDiretorio1->SelectItem(arvoreDiretorio1->GetFirstVisibleItem(), true);
	 }
	 LimparComparacao();

	 SetCursor(wxCURSOR_ARROW);
}

void FrmCompararDiretorio::arvoreDiretorio1GetInfo( wxTreeEvent& event ) {
	 event.Skip();
}

void FrmCompararDiretorio::arvoreDiretorio1SelChanged( wxTreeEvent& event ) {
	 event.Skip();
}

void FrmCompararDiretorio::cmbAba2Choice( wxCommandEvent& event ) {
	 event.Skip();

	 Aba *aba;

	 SetCursor(wxCURSOR_WAIT);

	 arvoreDiretorio2->limpar();
	 aba = AbaBO::getInstancia()->pegaAbaPorOrdem(catalogador->listaAbas,
		 cmbAba2->GetSelection() + 1);
	 catalogador->CarregarArvore(arvoreDiretorio2, *aba);
	 if (arvoreDiretorio2->GetCount() > 0) {
		 arvoreDiretorio2->SelectItem(arvoreDiretorio1->GetFirstVisibleItem(), true);
	 }
	 LimparComparacao();

	 SetCursor(wxCURSOR_ARROW);
}

void FrmCompararDiretorio::arvoreDiretorio2GetInfo( wxTreeEvent& event ) {
	 event.Skip();
}

void FrmCompararDiretorio::arvoreDiretorio2SelChanged( wxTreeEvent& event ) {
	 event.Skip();
}

void FrmCompararDiretorio::tabelaComparadorListColClick( wxListEvent& event ) {
    event.Skip();
}

void FrmCompararDiretorio::tabelaComparadorListItemSelected( wxListEvent& event ) {
    event.Skip();
}

void FrmCompararDiretorio::montarArvores()
{
	Aba *aba1;

	for each(Aba aba in catalogador->listaAbas) {
		cmbAba1->AppendString(aba.getNome());
		cmbAba2->AppendString(aba.getNome());
	}
	cmbAba1->SetSelection(0);
	cmbAba2->SetSelection(0);

	aba1 = AbaBO::getInstancia()->pegaAbaPorOrdem(catalogador->listaAbas,
		cmbAba1->GetSelection() + 1);
	catalogador->CarregarArvore(arvoreDiretorio1, *aba1);

	aba1 = AbaBO::getInstancia()->pegaAbaPorOrdem(catalogador->listaAbas,
		cmbAba2->GetSelection() + 1);
	catalogador->CarregarArvore(arvoreDiretorio2, *aba1);
}

wxString FrmCompararDiretorio::SQLCompara(Aba aba1, Aba aba2, const wxString &caminho1,
	const wxString &caminho2) {
	wxString sSQL;

	sSQL = DiretorioBO::SQL_CONSULTA_ARQUIVO + " WHERE aba=" + Rotinas::IntToStr(aba1.getCodigo())
		+ " AND caminho LIKE " + Rotinas::QuotedStr(caminho1 + "%")
		+ " AND nome NOT IN (SELECT nome FROM Diretorios "
		+ " WHERE aba=" + Rotinas::IntToStr(aba2.getCodigo()) + " AND caminho LIKE "
		+ Rotinas::QuotedStr(caminho2 + "%") + ")" + " ORDER BY 1, 2, 3";
	return sSQL;
}

void FrmCompararDiretorio::Comparar(const wxString &sCaminhoDir1, const wxString &sCaminhoDir2)
{
	wxString sSQL;
	Aba *aba1, *aba2;
	int tamLista;

	aba1 = AbaBO::getInstancia()->pegaAbaPorOrdem(catalogador->listaAbas,
		cmbAba1->GetSelection() + 1);
	aba2 = AbaBO::getInstancia()->pegaAbaPorOrdem(catalogador->listaAbas,
		cmbAba2->GetSelection() + 1);

	sSQL = SQLCompara(*aba1, *aba2, sCaminhoDir1, sCaminhoDir2);
	listaCompara = DiretorioBO::getInstancia()->carregarDiretorio(sSQL,
		"consultaarquivo", ProgressoLog);

	if (listaCompara.size() > 0) {
		tabelaComparador->modeloTabela(listaCompara, catalogador->listaExtensoes, pb);
		tabelaComparador->selecionaLinha(0);
		//tabelaCompara.setSombrearLinhas(true);

		tamLista = listaCompara.size();
		barraStatus->SetStatusText(Rotinas::IntToStr(tamLista), 1);
		btnSalvarLog->Enable(true);
	}
	else {
		Dialogo::mensagemInfo(this,
			"FrmCompararDiretorio.NenhumaDiferencaEncontrada");
	}
}
