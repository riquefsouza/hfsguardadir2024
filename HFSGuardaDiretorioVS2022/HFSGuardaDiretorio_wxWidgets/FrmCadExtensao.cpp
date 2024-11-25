#include "FrmCadExtensao.h"
#include "FrmPrincipal.h"
#include "FrmEscolherDir.h"

#include "hfsguardadir\objetos\Extensao.h"
#include "hfsguardadir\objetosbo\ExtensaoBO.h"
#include "hfsguardadir\catalogador\Catalogador.h"
#include "hfsguardadir\objetosgui\EscolhaArquivo.h"
#include "hfsguardadir\objetosgui\Dialogo.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::objetosbo;
using namespace hfsguardadir::objetosgui;
using namespace hfsguardadir::catalogador;

// ---------------------------------------------------------------------------
FrmCadExtensao *frmCadExtensao;

// ---------------------------------------------------------------------------
FrmCadExtensao::FrmCadExtensao( wxWindow* parent ):
    wxFrame( parent, wxID_ANY, wxT("Cadastro de Extens\u00e3o de Arquivo"), wxDefaultPosition, wxSize( 289,300 ),
            wxCAPTION|wxCLOSE_BOX|wxFRAME_FLOAT_ON_PARENT|wxSYSTEM_MENU|wxTAB_TRAVERSAL )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	barraMenu = new wxMenuBar( 0 );
	menuExtensao = new wxMenu();
	wxMenuItem* menuIncluirExtensao;
	menuIncluirExtensao = new wxMenuItem( menuExtensao, wxID_ANY, wxString( wxT("Incluir Extens\u00e3o") ) , wxEmptyString, wxITEM_NORMAL );
	menuExtensao->Append( menuIncluirExtensao );

	wxMenuItem* menuExcluirExtensao;
	menuExcluirExtensao = new wxMenuItem( menuExtensao, wxID_ANY, wxString( wxT("Excluir Extens\u00e3o") ) , wxEmptyString, wxITEM_NORMAL );
	menuExtensao->Append( menuExcluirExtensao );

	wxMenuItem* menuExcluirTodasExtensoes;
	menuExcluirTodasExtensoes = new wxMenuItem( menuExtensao, wxID_ANY, wxString( wxT("Excluir Todas Extens\u00f5es") ) , wxEmptyString, wxITEM_NORMAL );
	menuExtensao->Append( menuExcluirTodasExtensoes );

	barraMenu->Append( menuExtensao, wxT("Extens\u00e3o") );

	menuExportarTodos = new wxMenu();

	wxMenuItem* menuExportarBitmap;
	menuExportarBitmap = new wxMenuItem( menuExportarTodos, wxID_ANY, wxString( wxT("Exportar para Bitmap") ) , wxEmptyString, wxITEM_NORMAL );
	menuExportarTodos->Append( menuExportarBitmap );

	wxMenuItem* menuExportarIcone;
	menuExportarIcone = new wxMenuItem( menuExportarTodos, wxID_ANY, wxString( wxT("Exportar para \u00cdcone") ) , wxEmptyString, wxITEM_NORMAL );
	menuExportarTodos->Append( menuExportarIcone );

	wxMenuItem* menuExportarGIF;
	menuExportarGIF = new wxMenuItem( menuExportarTodos, wxID_ANY, wxString( wxT("Exportar para GIF") ) , wxEmptyString, wxITEM_NORMAL );
	menuExportarTodos->Append( menuExportarGIF );

	wxMenuItem* menuExportarJPEG;
	menuExportarJPEG = new wxMenuItem( menuExportarTodos, wxID_ANY, wxString( wxT("Exportar para JPEG") ) , wxEmptyString, wxITEM_NORMAL );
	menuExportarTodos->Append( menuExportarJPEG );

	wxMenuItem* menuExportarPNG;
	menuExportarPNG = new wxMenuItem( menuExportarTodos, wxID_ANY, wxString( wxT("Exportar para PNG") ) , wxEmptyString, wxITEM_NORMAL );
	menuExportarTodos->Append( menuExportarPNG );

	wxMenuItem* menuExportarTIFF;
	menuExportarTIFF = new wxMenuItem( menuExportarTodos, wxID_ANY, wxString( wxT("Exportar para TIFF") ) , wxEmptyString, wxITEM_NORMAL );
	menuExportarTodos->Append( menuExportarTIFF );

	barraMenu->Append( menuExportarTodos, wxT("Exportar Todos") );

	menuImportarTodos = new wxMenu();
	wxMenuItem* menuImportarIconesArquivos;
	menuImportarIconesArquivos = new wxMenuItem( menuImportarTodos, wxID_ANY, wxString( wxT("Importar \u00cdcones dos Arquivos") ) , wxEmptyString, wxITEM_NORMAL );
	menuImportarTodos->Append( menuImportarIconesArquivos );

	wxMenuItem* menuExtrairIconesArquivos;
	menuExtrairIconesArquivos = new wxMenuItem( menuImportarTodos, wxID_ANY, wxString( wxT("Extrair \u00cdcones dos Arquivos") ) , wxEmptyString, wxITEM_NORMAL );
	menuImportarTodos->Append( menuExtrairIconesArquivos );

	barraMenu->Append( menuImportarTodos, wxT("Importar Todos") );

	this->SetMenuBar( barraMenu );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	imageList16 = new wxImageList(16, 16, true);
	imageList32 = new wxImageList(32, 32, true);

	lcExtensao = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
    lcExtensao->AppendColumn(wxT("Extens\u00e3o"), wxLIST_FORMAT_LEFT, 100);
	lcExtensao->AppendColumn(wxT("\u00cdcone"), wxLIST_FORMAT_LEFT, 100);
	lcExtensao->SetImageList(imageList32, wxIMAGE_LIST_NORMAL);
	lcExtensao->SetImageList(imageList16, wxIMAGE_LIST_SMALL);

	bSizer1->Add( lcExtensao, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );


	bSizer2->Add( 0, 0, 1, wxEXPAND, 5 );

	btnIncluir = new wxButton( this, wxID_ANY, wxT("&Incluir"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( btnIncluir, 0, wxALL, 5 );

	btnExcluir = new wxButton( this, wxID_ANY, wxT("&Excluir"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( btnExcluir, 0, wxALL, 5 );


	bSizer2->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer1->Add( bSizer2, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_ACTIVATE, wxActivateEventHandler( FrmCadExtensao::FrmCadExtensaoActivate ) );
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( FrmCadExtensao::FrmCadExtensaoClose ) );
	this->Connect( menuIncluirExtensao->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmCadExtensao::menuIncluirExtensaoSelection ) );
	this->Connect( menuExcluirExtensao->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmCadExtensao::menuExcluirExtensaoSelection ) );
	this->Connect( menuExcluirTodasExtensoes->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmCadExtensao::menuExcluirTodasExtensoesSelection ) );
	this->Connect( menuExportarBitmap->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmCadExtensao::menuExportarBitmapSelection ) );
	this->Connect( menuExportarIcone->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmCadExtensao::menuExportarIconeSelection ) );
	this->Connect( menuExportarGIF->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmCadExtensao::menuExportarGIFSelection ) );
	this->Connect( menuExportarJPEG->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmCadExtensao::menuExportarJPEGSelection ) );
	this->Connect( menuExportarPNG->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmCadExtensao::menuExportarPNGSelection ) );
	this->Connect( menuExportarTIFF->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmCadExtensao::menuExportarTIFFSelection ) );
	this->Connect( menuImportarIconesArquivos->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmCadExtensao::menuImportarIconesArquivosSelection ) );
	this->Connect( menuExtrairIconesArquivos->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmCadExtensao::menuExtrairIconesArquivosSelection ) );
	lcExtensao->Connect( wxEVT_COMMAND_LIST_COL_CLICK, wxListEventHandler( FrmCadExtensao::lcExtensaoListColClick ), NULL, this );
	lcExtensao->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( FrmCadExtensao::lcExtensaoListItemSelected ), NULL, this );
	btnIncluir->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FrmCadExtensao::btnIncluirClick ), NULL, this );
	btnExcluir->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FrmCadExtensao::btnExcluirClick ), NULL, this );
}

FrmCadExtensao::~FrmCadExtensao()
{
	// Disconnect Events
	this->Disconnect( wxEVT_ACTIVATE, wxActivateEventHandler( FrmCadExtensao::FrmCadExtensaoActivate ) );
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( FrmCadExtensao::FrmCadExtensaoClose ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmCadExtensao::menuIncluirExtensaoSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmCadExtensao::menuExcluirExtensaoSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmCadExtensao::menuExcluirTodasExtensoesSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmCadExtensao::menuExportarIconeSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmCadExtensao::menuExportarGIFSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmCadExtensao::menuExportarJPEGSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmCadExtensao::menuExportarPNGSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmCadExtensao::menuExportarTIFFSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmCadExtensao::menuImportarIconesArquivosSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmCadExtensao::menuExtrairIconesArquivosSelection ) );
	lcExtensao->Disconnect( wxEVT_COMMAND_LIST_COL_CLICK, wxListEventHandler( FrmCadExtensao::lcExtensaoListColClick ), NULL, this );
	lcExtensao->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( FrmCadExtensao::lcExtensaoListItemSelected ), NULL, this );
	btnIncluir->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FrmCadExtensao::btnIncluirClick ), NULL, this );
	btnExcluir->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FrmCadExtensao::btnExcluirClick ), NULL, this );

}

void FrmCadExtensao::FrmCadExtensaoActivate( wxActivateEvent& event ) {
	 event.Skip();

	 CarregarExtensoesNaGrid();
}

void FrmCadExtensao::FrmCadExtensaoClose( wxCloseEvent& event ) {
	 event.Skip();
}

void FrmCadExtensao::menuIncluirExtensaoSelection( wxCommandEvent& event ) {
	 event.Skip();

	 wxArrayString log;

	 wxString arqSelecionado = EscolhaArquivo::abrirArquivo(this);
	 if (!arqSelecionado.IsEmpty()) {
		 wxFileName arquivo(arqSelecionado);

		 if (arquivo.Exists()) {
			 if (ExtensaoBO::getInstancia()->SalvarExtensao(
				 catalogador->listaExtensoes, arquivo.GetName(),
				 arquivo.GetFullPath(), log)) {

				 CarregarExtensoesNaGrid();

				 Dialogo::mensagemInfo(this,
					 "FrmCadExtensao.ExtensaoSalvaSucesso");
			 }
			 else {
				 Dialogo::mensagemInfo(this,
					 "FrmCadExtensao.ExtensaoJaCadastrada");
			 }
		 }
	 }

}

void FrmCadExtensao::menuExcluirExtensaoSelection( wxCommandEvent& event ) {
	 event.Skip();
	 wxListView lvExtensao = lcExtensao;
	 Extensao *extensao;

	 if (catalogador->listaExtensoes.size() > 0) {
		 int res = Dialogo::confirma(this, "FrmCadExtensao.ExtensaoCertezaExcluir");
		 if (res == wxYES) {
			 extensao = ExtensaoBO::getInstancia()->pegaExtensaoPorOrdem(
				 catalogador->listaExtensoes, lvExtensao.GetFirstSelected() + 1);

			 if (ExtensaoBO::getInstancia()->excluirExtensao(
				 catalogador->listaExtensoes, extensao->getCodigo())) {
				 CarregarExtensoesNaGrid();
				 Dialogo::mensagemInfo(this,
					 "FrmCadExtensao.ExtensaoExcluidaSucesso");
			 }
		 }
	 }

}

void FrmCadExtensao::menuExcluirTodasExtensoesSelection( wxCommandEvent& event ) {
	 event.Skip();

	 if (catalogador->listaExtensoes.size() > 0) {
		 int res = Dialogo::confirma(this, "FrmCadExtensao.ExtensaoCertezaTodosExcluir");
		 if (res == wxYES) {
			 if (ExtensaoBO::getInstancia()->excluirTodasExtensoes(
				 catalogador->listaExtensoes)) {
				 CarregarExtensoesNaGrid();
				 Dialogo::mensagemInfo(this,
					 "FrmCadExtensao.ExtensoesExcluidasSucesso");
			 }
		 }
	 }
}

void FrmCadExtensao::menuExportarBitmapSelection( wxCommandEvent& event ) {
	 event.Skip();

	 if (ExtensaoBO::getInstancia()->ExportarExtensao(teBMP,
		 catalogador->listaExtensoes)) {
		 Dialogo::mensagemInfo(this, "FrmCadExtensao.ExportarExtensao");
	 }

}

void FrmCadExtensao::menuExportarIconeSelection( wxCommandEvent& event ) {
	 event.Skip();

	 if (ExtensaoBO::getInstancia()->ExportarExtensao(teICO,
		 catalogador->listaExtensoes)) {
		 Dialogo::mensagemInfo(this, "FrmCadExtensao.ExportarExtensao");
	 }

}

void FrmCadExtensao::menuExportarGIFSelection( wxCommandEvent& event ) {
	 event.Skip();

	 if (ExtensaoBO::getInstancia()->ExportarExtensao(teGIF,
		 catalogador->listaExtensoes)) {
		 Dialogo::mensagemInfo(this, "FrmCadExtensao.ExportarExtensao");
	 }

}

void FrmCadExtensao::menuExportarJPEGSelection( wxCommandEvent& event ) {
	 event.Skip();

	 if (ExtensaoBO::getInstancia()->ExportarExtensao(teJPG,
		 catalogador->listaExtensoes)) {
		 Dialogo::mensagemInfo(this, "FrmCadExtensao.ExportarExtensao");
	 }

}

void FrmCadExtensao::menuExportarPNGSelection( wxCommandEvent& event ) {
	 event.Skip();

	 if (ExtensaoBO::getInstancia()->ExportarExtensao(tePNG,
		 catalogador->listaExtensoes)) {
		 Dialogo::mensagemInfo(this, "FrmCadExtensao.ExportarExtensao");
	 }

}

void FrmCadExtensao::menuExportarTIFFSelection( wxCommandEvent& event ) {
	 event.Skip();

	 if (ExtensaoBO::getInstancia()->ExportarExtensao(teTIF,
		 catalogador->listaExtensoes)) {
		 Dialogo::mensagemInfo(this, "FrmCadExtensao.ExportarExtensao");
	 }

}

void FrmCadExtensao::menuImportarIconesArquivosSelection( wxCommandEvent& event ) {
	 event.Skip();

	 wxString sCaminho;

	 wxString dirSelecionado = EscolhaArquivo::abrirDiretorio(this);
	 if (!dirSelecionado.IsEmpty()) {
		 wxFileName diretorio(dirSelecionado);
		 if (diretorio.Exists()) {
			 sCaminho = diretorio.GetFullPath();

			 ExtensaoBO::getInstancia()->ImportarExtensao(sCaminho,
				 catalogador->listaExtensoes);
			 CarregarExtensoesNaGrid();
		 }
	 }
}

void FrmCadExtensao::menuExtrairIconesArquivosSelection( wxCommandEvent& event ) {
	 event.Skip();

	 wxString sCaminho;
	 wxString dirSelecionado = EscolhaArquivo::abrirDiretorio(this);
	 if (!dirSelecionado.IsEmpty()) {
		 wxFileName diretorio(dirSelecionado);
		 if (diretorio.Exists()) {
			 sCaminho = diretorio.GetFullPath();

			 ExtensaoBO::getInstancia()->ExtrairExtensao(sCaminho,
				 catalogador->listaExtensoes);
			 CarregarExtensoesNaGrid();
		 }
	 }
}

void FrmCadExtensao::lcExtensaoListColClick( wxListEvent& event ) {
    event.Skip();
}

void FrmCadExtensao::lcExtensaoListItemSelected( wxListEvent& event ) {
    event.Skip();
}

void FrmCadExtensao::btnIncluirClick( wxCommandEvent& event ) {
	 event.Skip();

	 menuIncluirExtensaoSelection(event);
}

void FrmCadExtensao::btnExcluirClick( wxCommandEvent& event ) {
	 event.Skip();

	 menuExcluirExtensaoSelection(event);
}
// ---------------------------------------------------------------------------

void FrmCadExtensao::CarregarExtensoesNaGrid() {
	long nItem;
	unsigned int nLinha = 0;
	wxImage img;
	wxBitmap *bmp;

	for each(Extensao extensao in catalogador->listaExtensoes) {
		img = Rotinas::MemoryBufferToImage(extensao.getBmp16(), wxBITMAP_TYPE_BMP);
		bmp = new wxBitmap(img);
		imageList16->Add(*bmp);

		nItem = lcExtensao->InsertItem(nLinha, extensao.getNome(), -1);
		lcExtensao->SetItemData(nItem, nLinha);
		lcExtensao->SetItem(nItem, 1, "", nLinha);
		nLinha++;
	}

}

