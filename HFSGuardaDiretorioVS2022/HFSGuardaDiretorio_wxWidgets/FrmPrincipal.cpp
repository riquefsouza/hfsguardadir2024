#include "FrmPrincipal.h"
#include "FrmSobre.h"
#include "FrmCadExtensao.h"
#include "FrmSplash.h"
#include "FrmEscolherDir.h"
#include "FrmImportarDiretorio.h"
#include "FrmCompararDiretorio.h"
#include "FrmInfoDiretorio.h"

// ---------------------------------------------------------------------------
FrmPrincipal *frmPrincipal;

// ---------------------------------------------------------------------------
FrmPrincipal::FrmPrincipal( wxWindow* parent ):
    wxFrame( parent, wxID_ANY, wxT("HFSGuardaDiretorio 2.0 - Catalogador de Diret\u00f3rios"),
               wxDefaultPosition, wxSize( 924,546 ), wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

    imageList16 = new wxImageList(16, 16, true);
	imageList32 = new wxImageList(32, 32, true);
    imageListTabs = new wxImageList(16, 16, true);

    imageList16->Add( wxBitmap(wxT("DIRETORIO"), wxBITMAP_TYPE_BMP_RESOURCE) );
	imageList16->Add( wxBitmap(wxT("ARQUIVO"), wxBITMAP_TYPE_BMP_RESOURCE));
    imageList16->Add( wxBitmap(wxT("DIRABERTO"), wxBITMAP_TYPE_BMP_RESOURCE) );

    imageList32->Add( wxBitmap(wxT("DIRETORIO32"), wxBITMAP_TYPE_BMP_RESOURCE) );
	imageList32->Add( wxBitmap(wxT("ARQUIVO32"), wxBITMAP_TYPE_BMP_RESOURCE));
    imageList32->Add( wxBitmap(wxT("DIRABERTO32"), wxBITMAP_TYPE_BMP_RESOURCE) );

    wxColour* corTransparente = new wxColour(255, 0, 255);
    imageListTabs->Add( wxBitmap(wxT("CDOURO"), wxBITMAP_TYPE_BMP_RESOURCE), *corTransparente );
    imageListTabs->Add( wxBitmap(wxT("CDPRATA"), wxBITMAP_TYPE_BMP_RESOURCE), *corTransparente );

	barraMenu = new wxMenuBar( 0 );
	menuAba = new wxMenu();
	wxMenuItem* menuIncluirNovaAba;
	menuIncluirNovaAba = new wxMenuItem( menuAba, wxID_ANY, wxString( wxT("Incluir Nova Aba") ) , wxEmptyString, wxITEM_NORMAL );
	menuAba->Append( menuIncluirNovaAba );

	wxMenuItem* menuAlterarNomeAbaAtiva;
	menuAlterarNomeAbaAtiva = new wxMenuItem( menuAba, wxID_ANY, wxString( wxT("Alterar Nome da Aba Ativa") ) , wxEmptyString, wxITEM_NORMAL );
	menuAba->Append( menuAlterarNomeAbaAtiva );

	wxMenuItem* menuExcluirAbaAtiva;
	menuExcluirAbaAtiva = new wxMenuItem( menuAba, wxID_ANY, wxString( wxT("Excluir Aba Ativa") ) , wxEmptyString, wxITEM_NORMAL );
	menuAba->Append( menuExcluirAbaAtiva );

	barraMenu->Append( menuAba, wxT("Aba") );

	menuDiretorio = new wxMenu();
	wxMenuItem* menuImportarDiretorio;
	menuImportarDiretorio = new wxMenuItem( menuDiretorio, wxID_ANY, wxString( wxT("Importar Diret\u00f3rio") ) , wxEmptyString, wxITEM_NORMAL );
	menuDiretorio->Append( menuImportarDiretorio );

	wxMenuItem* menuImportarSubDiretorios;
	menuImportarSubDiretorios = new wxMenuItem( menuDiretorio, wxID_ANY, wxString( wxT("Importar SubDiret\u00f3rios") ) , wxEmptyString, wxITEM_NORMAL );
	menuDiretorio->Append( menuImportarSubDiretorios );

	wxMenuItem* menuCompararDiretorios;
	menuCompararDiretorios = new wxMenuItem( menuDiretorio, wxID_ANY, wxString( wxT("Comparar Diret\u00f3rios") ) , wxEmptyString, wxITEM_NORMAL );
	menuDiretorio->Append( menuCompararDiretorios );

	wxMenuItem* menuCadastrarExtensaoArquivo;
	menuCadastrarExtensaoArquivo = new wxMenuItem( menuDiretorio, wxID_ANY, wxString( wxT("Cadastrar Extens\u00e3o de Arquivo") ) , wxEmptyString, wxITEM_NORMAL );
	menuDiretorio->Append( menuCadastrarExtensaoArquivo );

	menuDiretorio->AppendSeparator();

	wxMenuItem* menuExpandirDiretorios;
	menuExpandirDiretorios = new wxMenuItem( menuDiretorio, wxID_ANY, wxString( wxT("Expandir Diret\u00f3rios") ) , wxEmptyString, wxITEM_NORMAL );
	menuDiretorio->Append( menuExpandirDiretorios );

	wxMenuItem* menuColapsarDiretorios;
	menuColapsarDiretorios = new wxMenuItem( menuDiretorio, wxID_ANY, wxString( wxT("Colapsar Diret\u00f3rios") ) , wxEmptyString, wxITEM_NORMAL );
	menuDiretorio->Append( menuColapsarDiretorios );

	menuExportarDiretoriosAbaAtiva = new wxMenu();
	wxMenuItem* menuExportarDiretoriosAbaAtivaItem = new wxMenuItem( menuDiretorio, wxID_ANY, wxT("Exportar Diret\u00f3rios da Aba Ativa"), wxEmptyString, wxITEM_NORMAL, menuExportarDiretoriosAbaAtiva );
	wxMenuItem* menuTXT;
	menuTXT = new wxMenuItem( menuExportarDiretoriosAbaAtiva, wxID_ANY, wxString( wxT("TXT") ) , wxEmptyString, wxITEM_NORMAL );
	menuExportarDiretoriosAbaAtiva->Append( menuTXT );

	wxMenuItem* menuCSV;
	menuCSV = new wxMenuItem( menuExportarDiretoriosAbaAtiva, wxID_ANY, wxString( wxT("CSV") ) , wxEmptyString, wxITEM_NORMAL );
	menuExportarDiretoriosAbaAtiva->Append( menuCSV );

	wxMenuItem* menuHTML;
	menuHTML = new wxMenuItem( menuExportarDiretoriosAbaAtiva, wxID_ANY, wxString( wxT("HTML") ) , wxEmptyString, wxITEM_NORMAL );
	menuExportarDiretoriosAbaAtiva->Append( menuHTML );

	wxMenuItem* menuXML;
	menuXML = new wxMenuItem( menuExportarDiretoriosAbaAtiva, wxID_ANY, wxString( wxT("XML") ) , wxEmptyString, wxITEM_NORMAL );
	menuExportarDiretoriosAbaAtiva->Append( menuXML );

	wxMenuItem* menuSQL;
	menuSQL = new wxMenuItem( menuExportarDiretoriosAbaAtiva, wxID_ANY, wxString( wxT("SQL") ) , wxEmptyString, wxITEM_NORMAL );
	menuExportarDiretoriosAbaAtiva->Append( menuSQL );

	menuDiretorio->Append( menuExportarDiretoriosAbaAtivaItem );

	wxMenuItem* menuImportarDiretoriosViaXML;
	menuImportarDiretoriosViaXML = new wxMenuItem( menuDiretorio, wxID_ANY, wxString( wxT("Importar Diret\u00f3rios via XML") ) , wxEmptyString, wxITEM_NORMAL );
	menuDiretorio->Append( menuImportarDiretoriosViaXML );

	menuGravarLogImportacao = new wxMenuItem( menuDiretorio, wxID_ANY, wxString( wxT("Gravar Log da Importa\u00e7\u00e3o") ) , wxEmptyString, wxITEM_NORMAL );
	menuDiretorio->Append( menuGravarLogImportacao );

	barraMenu->Append( menuDiretorio, wxT("Diret\u00f3rio") );

	menuVisao = new wxMenu();
	wxMenuItem* menuMostrarOcultarArvoreDirAbaAtiva;
	menuMostrarOcultarArvoreDirAbaAtiva = new wxMenuItem( menuVisao, wxID_ANY, wxString( wxT("Mostrar/Ocultar \u00c1rvore de diret\u00f3rios da Aba Ativa") ) , wxEmptyString, wxITEM_NORMAL );
	menuVisao->Append( menuMostrarOcultarArvoreDirAbaAtiva );

	wxMenuItem* menuMostrarOcultarListaItensPesquisados;
	menuMostrarOcultarListaItensPesquisados = new wxMenuItem( menuVisao, wxID_ANY, wxString( wxT("Mostrar/Ocultar lista de itens pesquisados") ) , wxEmptyString, wxITEM_NORMAL );
	menuVisao->Append( menuMostrarOcultarListaItensPesquisados );

	barraMenu->Append( menuVisao, wxT("Vis\u00e3o") );

	menuSobre = new wxMenu();
	wxMenuItem* menuSobreCatalogador;
	menuSobreCatalogador = new wxMenuItem( menuSobre, wxID_ANY, wxString( wxT("Sobre o Catalogador") ) , wxEmptyString, wxITEM_NORMAL );
	menuSobre->Append( menuSobreCatalogador );

	barraMenu->Append( menuSobre, wxT("Sobre") );

	this->SetMenuBar( barraMenu );

	menuPopup = new wxMenu();
	wxMenuItem* menuInformacoesDiretorioArquivo = new wxMenuItem(menuPopup, wxID_ANY, Rotinas::getRecurso("FrmPrincipal.menuInformacoesDiretorioArquivo"), wxEmptyString, wxITEM_NORMAL);
	wxMenuItem* menuExcluirDiretorioSelecionado = new wxMenuItem(menuPopup, wxID_ANY, Rotinas::getRecurso("FrmPrincipal.menuExcluirDiretorioSelecionado"), wxEmptyString, wxITEM_NORMAL);
	wxMenuItem* menuExpandirDiretorios2 = new wxMenuItem(menuPopup, wxID_ANY, wxString(wxT("Expandir Diret\u00f3rios")), wxEmptyString, wxITEM_NORMAL);
	wxMenuItem* menuColapsarDiretorios2 = new wxMenuItem(menuPopup, wxID_ANY, wxString(wxT("Colapsar Diret\u00f3rios")), wxEmptyString, wxITEM_NORMAL);
	wxMenuItem* menuIncluirNovaAba2 = new wxMenuItem(menuPopup, wxID_ANY, wxString(wxT("Incluir Nova Aba")), wxEmptyString, wxITEM_NORMAL);
	wxMenuItem* menuAlterarNomeAbaAtiva2 = new wxMenuItem(menuPopup, wxID_ANY, wxString(wxT("Alterar Nome da Aba Ativa")), wxEmptyString, wxITEM_NORMAL);
	wxMenuItem* menuExcluirAbaAtiva2 = new wxMenuItem(menuPopup, wxID_ANY, wxString(wxT("Excluir Aba Ativa")), wxEmptyString, wxITEM_NORMAL);

	menuPopup->Append(menuInformacoesDiretorioArquivo);
	menuPopup->Append(menuExcluirDiretorioSelecionado);
	menuPopup->Append(menuExpandirDiretorios2);
	menuPopup->Append(menuColapsarDiretorios2);
	menuPopup->AppendSeparator();
	menuPopup->Append(menuIncluirNovaAba2);
	menuPopup->Append(menuAlterarNomeAbaAtiva2);
	menuPopup->Append(menuExcluirAbaAtiva2);
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( -1,33 ), wxTAB_TRAVERSAL );
	m_panel1->SetMinSize( wxSize( -1,33 ) );
	m_panel1->SetMaxSize( wxSize( -1,33 ) );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );

	btnImportarDiretorio = new wxButton( m_panel1, wxID_ANY, wxT("&Importar Diret\u00f3rio"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( btnImportarDiretorio, 0, wxALL, 5 );

	pb = new wxGauge( m_panel1, wxID_ANY, 100, wxDefaultPosition, wxSize( 385,17 ), wxGA_HORIZONTAL );
	pb->SetValue( 0 );
	pb->SetMinSize( wxSize( 385,17 ) );
	pb->SetMaxSize( wxSize( 385,17 ) );

	bSizer2->Add( pb, 0, wxALL, 5 );

	edtPesquisa = new wxTextCtrl( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	edtPesquisa->SetMaxLength( 255 );
	edtPesquisa->SetToolTip( wxT("Digite aqui para pesquisar") );
	edtPesquisa->SetMinSize( wxSize( 288,-1 ) );

	bSizer2->Add( edtPesquisa, 1, wxALL, 5 );

	btnPesquisa = new wxButton( m_panel1, wxID_ANY, wxT("&Pesquisar"), wxDefaultPosition, wxDefaultSize, 0 );
	btnPesquisa->SetDefault();
	bSizer2->Add( btnPesquisa, 0, wxALL, 5 );
	
	m_panel1->SetSizer( bSizer2 );
	m_panel1->Layout();
	bSizer1->Add( m_panel1, 0, wxEXPAND, 5 );

	spPesquisa = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	spPesquisa->Connect( wxEVT_IDLE, wxIdleEventHandler( FrmPrincipal::spPesquisaOnIdle ), NULL, this );

	m_panel2 = new wxPanel(spPesquisa, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	notebook = new wxNotebook(m_panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, "notebook" );
	notebook->SetImageList(imageListTabs);

	bSizer3->Add( notebook, 1, wxEXPAND | wxALL, 5 );

	m_panel2->SetSizer( bSizer3 );
	m_panel2->Layout();
	bSizer3->Fit( m_panel2 );
	m_panel3 = new wxPanel(spPesquisa, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	tabelaPesquisa = new Tabela(m_panel3, false, imageList16, imageList32);

	bSizer4->Add( tabelaPesquisa, 1, wxALL|wxEXPAND, 5 );

	m_panel3->SetSizer( bSizer4 );
	m_panel3->Layout();
	bSizer4->Fit( m_panel3 );
	spPesquisa->SplitHorizontally( m_panel2, m_panel3, 0 );
	bSizer1->Add(spPesquisa, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();
	barraStatus = this->CreateStatusBar( 2, wxST_SIZEGRIP, wxID_ANY );

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_ACTIVATE, wxActivateEventHandler( FrmPrincipal::FrmPrincipalActivate ) );
	this->Connect( wxEVT_ACTIVATE_APP, wxActivateEventHandler( FrmPrincipal::FrmPrincipalActivateApp ) );
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( FrmPrincipal::FrmPrincipalClose ) );
	this->Connect( menuIncluirNovaAba->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuIncluirNovaAbaSelection ) );
	this->Connect( menuAlterarNomeAbaAtiva->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuAlterarNomeAbaAtivaSelection ) );
	this->Connect( menuExcluirAbaAtiva->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuExcluirAbaAtivaSelection ) );
	this->Connect( menuImportarDiretorio->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuImportarDiretorioSelection ) );
	this->Connect( menuImportarSubDiretorios->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuImportarSubDiretoriosSelection ) );
	this->Connect( menuCompararDiretorios->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuCompararDiretoriosSelection ) );
	this->Connect( menuCadastrarExtensaoArquivo->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuCadastrarExtensaoArquivoSelection ) );
	this->Connect( menuExpandirDiretorios->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuExpandirDiretoriosSelection ) );
	this->Connect( menuColapsarDiretorios->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuColapsarDiretoriosSelection ) );
	this->Connect( menuTXT->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuTXTSelection ) );
	this->Connect( menuCSV->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuCSVSelection ) );
	this->Connect( menuHTML->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuHTMLSelection ) );
	this->Connect( menuXML->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuXMLSelection ) );
	this->Connect( menuSQL->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuSQLSelection ) );
	this->Connect( menuImportarDiretoriosViaXML->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuImportarDiretoriosViaXMLSelection ) );
	this->Connect( menuGravarLogImportacao->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuGravarLogImportacaoSelection ) );
	this->Connect( menuMostrarOcultarArvoreDirAbaAtiva->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuMostrarOcultarArvoreDirAbaAtivaSelection ) );
	this->Connect( menuMostrarOcultarListaItensPesquisados->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuMostrarOcultarListaItensPesquisadosSelection ) );
	this->Connect( menuSobreCatalogador->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuSobreCatalogadorSelection ) );

	this->Connect(menuInformacoesDiretorioArquivo->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(FrmPrincipal::menuInformacoesDiretorioArquivoSelection));
	this->Connect(menuExcluirDiretorioSelecionado->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(FrmPrincipal::menuExcluirDiretorioSelecionadoSelection));
	this->Connect(menuExpandirDiretorios2->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(FrmPrincipal::menuExpandirDiretoriosSelection));
	this->Connect(menuColapsarDiretorios2->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(FrmPrincipal::menuColapsarDiretoriosSelection));
	this->Connect(menuIncluirNovaAba2->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(FrmPrincipal::menuIncluirNovaAbaSelection));
	this->Connect(menuAlterarNomeAbaAtiva2->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(FrmPrincipal::menuAlterarNomeAbaAtivaSelection));
	this->Connect(menuExcluirAbaAtiva2->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(FrmPrincipal::menuExcluirAbaAtivaSelection));

	btnImportarDiretorio->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FrmPrincipal::btnImportarDiretorioClick ), NULL, this );
	btnPesquisa->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FrmPrincipal::btnPesquisaClick ), NULL, this );
	notebook->Connect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( FrmPrincipal::notebookPageChanged ), NULL, this );
	/*
	tvFixa->Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( FrmPrincipal::arvoreSelChanged ), NULL, this );
	lcFixa->Connect( wxEVT_COMMAND_LIST_COL_CLICK, wxListEventHandler( FrmPrincipal::tabelaListColClick ), NULL, this );
	lcFixa->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( FrmPrincipal::tabelaListItemSelected ), NULL, this );
	*/
	tabelaPesquisa->Connect( wxEVT_COMMAND_LIST_COL_CLICK, wxListEventHandler( FrmPrincipal::tabelaPesquisaListColClick ), NULL, this );
	tabelaPesquisa->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( FrmPrincipal::tabelaPesquisaListItemSelected ), NULL, this );
	
#if USE_CONTEXT_MENU
	this->Connect(wxEVT_CONTEXT_MENU, wxContextMenuEventHandler(FrmPrincipal::FrmPrincipalOnContextMenu));
#else
	this->Connect(wxEVT_RIGHT_UP, wxMouseEventHandler(FrmPrincipal::FrmPrincipalOnRightUp));
#endif


}

FrmPrincipal::~FrmPrincipal()
{
	// Disconnect Events
	this->Disconnect( wxEVT_ACTIVATE, wxActivateEventHandler( FrmPrincipal::FrmPrincipalActivate ) );
	this->Disconnect( wxEVT_ACTIVATE_APP, wxActivateEventHandler( FrmPrincipal::FrmPrincipalActivateApp ) );
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( FrmPrincipal::FrmPrincipalClose ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuIncluirNovaAbaSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuAlterarNomeAbaAtivaSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuExcluirAbaAtivaSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuImportarDiretorioSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuImportarSubDiretoriosSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuCompararDiretoriosSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuCadastrarExtensaoArquivoSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuExpandirDiretoriosSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuColapsarDiretoriosSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuTXTSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuCSVSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuHTMLSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuXMLSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuSQLSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuImportarDiretoriosViaXMLSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuGravarLogImportacaoSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuMostrarOcultarArvoreDirAbaAtivaSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuMostrarOcultarListaItensPesquisadosSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrmPrincipal::menuSobreCatalogadorSelection ) );

	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(FrmPrincipal::menuInformacoesDiretorioArquivoSelection));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(FrmPrincipal::menuExcluirDiretorioSelecionadoSelection));

	btnImportarDiretorio->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FrmPrincipal::btnImportarDiretorioClick ), NULL, this );
	btnPesquisa->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FrmPrincipal::btnPesquisaClick ), NULL, this );
	notebook->Disconnect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( FrmPrincipal::notebookPageChanged ), NULL, this );

	/*
	tvFixa->Disconnect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( FrmPrincipal::arvoreSelChanged ), NULL, this );
	lcFixa->Disconnect( wxEVT_COMMAND_LIST_COL_CLICK, wxListEventHandler( FrmPrincipal::tabelaListColClick ), NULL, this );
	lcFixa->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( FrmPrincipal::tabelaListItemSelected ), NULL, this );
	*/
	tabelaPesquisa->Disconnect( wxEVT_COMMAND_LIST_COL_CLICK, wxListEventHandler( FrmPrincipal::tabelaPesquisaListColClick ), NULL, this );
	tabelaPesquisa->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( FrmPrincipal::tabelaPesquisaListItemSelected ), NULL, this );
	
#if USE_CONTEXT_MENU
	this->Disconnect(wxEVT_CONTEXT_MENU, wxContextMenuEventHandler(FrmPrincipal::FrmPrincipalOnContextMenu));
#else
	this->Disconnect(wxEVT_RIGHT_UP, wxMouseEventHandler(FrmPrincipal::FrmPrincipalOnRightUp));
#endif

	imageListTabs->RemoveAll();
	imageList16->RemoveAll();
	imageList32->RemoveAll();

    delete imageList16;
    delete imageList32;
    delete imageListTabs;

    delete catalogador;
}

void FrmPrincipal::ProgressoLog(Progresso progresso)
{
  if (frmPrincipal!=NULL) {
	  if (progresso.posicao == 0) {
         frmPrincipal->pb->SetValue(progresso.minimo);
		 frmPrincipal->pb->SetRange(progresso.maximo);
	  }

	  frmPrincipal->pb->SetValue( progresso.posicao );
  }
}

void FrmPrincipal::FrmPrincipalActivate( wxActivateEvent& event ) {
    event.Skip();

    spPesquisa->Unsplit();
}

void FrmPrincipal::FrmPrincipalActivateApp( wxActivateEvent& event ) {
    event.Skip();

}

void FrmPrincipal::FrmPrincipalClose( wxCloseEvent& event ) {
    event.Skip();

	Rotinas::getInstancia()->Desconectar();
}

void FrmPrincipal::menuIncluirNovaAbaSelection( wxCommandEvent& event ) {
    event.Skip();

    catalogador->IncluirNovaAba();
}

void FrmPrincipal::menuAlterarNomeAbaAtivaSelection( wxCommandEvent& event ) {
    event.Skip();

    catalogador->AlterarNomeAbaAtiva(ProgressoLog);
}

void FrmPrincipal::menuExcluirAbaAtivaSelection( wxCommandEvent& event ) {
    event.Skip();

    catalogador->ExcluirAbaAtiva(ProgressoLog);
}

void FrmPrincipal::menuImportarDiretorioSelection( wxCommandEvent& event ) {
    event.Skip();

	catalogador->ComecaImportacao(false, ProgressoLog);
}

void FrmPrincipal::menuImportarSubDiretoriosSelection( wxCommandEvent& event ) {
    event.Skip();

	catalogador->ComecaImportacao(true, ProgressoLog);
}

void FrmPrincipal::menuCompararDiretoriosSelection( wxCommandEvent& event ) {
    event.Skip();

    frmCompararDiretorio = new FrmCompararDiretorio(this);
    frmCompararDiretorio->Show();
}

void FrmPrincipal::menuCadastrarExtensaoArquivoSelection( wxCommandEvent& event ) {
    event.Skip();

	frmCadExtensao = new FrmCadExtensao(this);
	frmCadExtensao->Show();
}

void FrmPrincipal::menuExpandirDiretoriosSelection( wxCommandEvent& event ) {
    event.Skip();

	catalogador->getArvoreAtual()->ExpandAll();
}

void FrmPrincipal::menuColapsarDiretoriosSelection( wxCommandEvent& event ) {
    event.Skip();

	catalogador->getArvoreAtual()->CollapseAll();
}

void FrmPrincipal::menuTXTSelection( wxCommandEvent& event ) {
    event.Skip();

    catalogador->ExportarArquivo(teTXT, ProgressoLog);
}

void FrmPrincipal::menuCSVSelection( wxCommandEvent& event ) {
    event.Skip();

    catalogador->ExportarArquivo(teCSV, ProgressoLog);
}

void FrmPrincipal::menuHTMLSelection( wxCommandEvent& event ) {
    event.Skip();

    catalogador->ExportarArquivo(teHTML, ProgressoLog);
}

void FrmPrincipal::menuXMLSelection( wxCommandEvent& event ) {
    event.Skip();

    catalogador->ExportarArquivo(teXML, ProgressoLog);
}

void FrmPrincipal::menuSQLSelection( wxCommandEvent& event ) {
    event.Skip();

    catalogador->ExportarArquivo(teSQL, ProgressoLog);
}

void FrmPrincipal::menuImportarDiretoriosViaXMLSelection( wxCommandEvent& event ) {
    event.Skip();

	wxArrayString log;
	catalogador->ImportarArquivo(log, ProgressoLog);
}

void FrmPrincipal::menuGravarLogImportacaoSelection( wxCommandEvent& event ) {
    event.Skip();

	//event.IsChecked()
	catalogador->bGravarLogImportacao = menuGravarLogImportacao->IsChecked();
}

void FrmPrincipal::menuMostrarOcultarArvoreDirAbaAtivaSelection( wxCommandEvent& event ) {
    event.Skip();
	catalogador->mostrarOcultarArvore();
}

void FrmPrincipal::menuMostrarOcultarListaItensPesquisadosSelection( wxCommandEvent& event ) {
    event.Skip();

	catalogador->mostrarListaItensPesquisados(!spPesquisa->IsSplit());
}

void FrmPrincipal::menuSobreCatalogadorSelection( wxCommandEvent& event ) {
    event.Skip();

	FrmSobre frmSobre(this);
	frmSobre.ShowModal();
}

void FrmPrincipal::btnImportarDiretorioClick( wxCommandEvent& event ) {
    event.Skip();

	catalogador->ComecaImportacao(false, ProgressoLog);
}

void FrmPrincipal::btnPesquisaClick( wxCommandEvent& event ) {
    event.Skip();

    catalogador->Pesquisar();
}

void FrmPrincipal::notebookPageChanged( wxNotebookEvent& event ) {    
    event.Skip();
	catalogador->tabPanelMudou();
}

void FrmPrincipal::arvoreSelChanged( wxTreeEvent& event ) {
    Arvore *arvore = (Arvore*)event.GetEventObject();

    if (arvore->IsSelected(event.GetItem())){
       catalogador->arvoreValorMudou(arvore, event.GetItem());
    }
}

int wxCALLBACK
listaComparaASC(wxIntPtr item1, wxIntPtr item2, wxIntPtr WXUNUSED(sortData))
{
    if (item1 > item2)
        return 1;
    if (item1 < item2)
        return -1;

    return 0;
}

int wxCALLBACK
listaComparaDESC(wxIntPtr item1, wxIntPtr item2, wxIntPtr WXUNUSED(sortData))
{
    if (item1 < item2)
        return 1;
    if (item1 > item2)
        return -1;

    return 0;
}

void FrmPrincipal::tabelaListColClick( wxListEvent& event ){
    Tabela *lcLista = (Tabela*)event.GetEventObject();

    //int col = event.GetColumn();
    static bool bOrdemColuna = true;
    bOrdemColuna = !bOrdemColuna;
//    SetColumnImage(col, x ? 0 : 1);

    if (bOrdemColuna)
        lcLista->SortItems(listaComparaASC, 0);
    else
        lcLista->SortItems(listaComparaDESC, 0);
}

void FrmPrincipal::tabelaListItemSelected( wxListEvent& event ){
	Tabela *tabela = (Tabela*)event.GetEventObject();

	wxString nome = tabela->GetItemText(event.GetIndex(), 0);
	wxString tipo = tabela->GetItemText(event.GetIndex(), 2);

	catalogador->DuploCliqueLista(nome, tipo);
}

void FrmPrincipal::tabelaPesquisaListColClick( wxListEvent& event ){
    event.Skip();
}

void FrmPrincipal::tabelaPesquisaListItemSelected( wxListEvent& event ){
	Tabela *tabela = (Tabela*)event.GetEventObject();

	wxString nome = tabela->GetItemText(event.GetIndex(), 0);
	wxString nomeAba = tabela->GetItemText(event.GetIndex(), 6);
	wxString caminho = tabela->GetItemText(event.GetIndex(), 5);
	catalogador->EncontrarItemLista(nomeAba, nome, caminho);

}

void FrmPrincipal::spOnIdle( wxIdleEvent& )
{
    sp->SetSashPosition( 0 );
    sp->Disconnect( wxEVT_IDLE, wxIdleEventHandler( FrmPrincipal::spOnIdle ), NULL, this );
}

void FrmPrincipal::spPesquisaOnIdle( wxIdleEvent& )
{
    spPesquisa->SetSashPosition( 0 );
    spPesquisa->Disconnect( wxEVT_IDLE, wxIdleEventHandler( FrmPrincipal::spPesquisaOnIdle ), NULL, this );
}

void FrmPrincipal::menuInformacoesDiretorioArquivoSelection(wxCommandEvent& event) {
	event.Skip();

	FrmInfoDiretorio *frmInfo;

	Tabela *tabela = catalogador->getTabelaAtual();

	if (tabela->GetSelectedItemCount() > 0) {
		frmInfo = new FrmInfoDiretorio(this);
		Aba aba = catalogador->getAbaAtual();
		Diretorio *dir = tabela->getLinhaSelecionada();
		dir->setAba(aba);
		frmInfo->setDiretorio(*dir);
		frmInfo->ShowModal();
	}
}

void FrmPrincipal::menuExcluirDiretorioSelecionadoSelection(wxCommandEvent& event) {
	event.Skip();

	catalogador->ExcluirDiretorioSelecionado(ProgressoLog);
}

void FrmPrincipal::ShowContextMenu(const wxPoint& pos)
{
	PopupMenu(menuPopup, pos);
}

#if USE_CONTEXT_MENU
void FrmPrincipal::FrmPrincipalOnContextMenu(wxContextMenuEvent& event)
{
	wxPoint point = event.GetPosition();

	if (point.x == -1 && point.y == -1) {
		wxSize size = GetSize();
		point.x = size.x / 2;
		point.y = size.y / 2;
	}
	else {
		point = ScreenToClient(point);
	}
	ShowContextMenu(point);
}
#endif

