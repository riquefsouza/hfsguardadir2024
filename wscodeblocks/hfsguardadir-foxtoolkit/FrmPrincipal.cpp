#include "resource.h"
#include "FrmPrincipal.h"

#include "hfsguardadir/comum/Rotinas.h"

#include "FrmSobre.h"
#include "FrmSplash.h"
#include "FrmCadExtensao.h"
#include "FrmCompararDiretorio.h"
#include "FrmImportarDiretorio.h"
#include "FrmInfoDiretorio.h"

#include "hfsguardadir/catalogador/Catalogador.h"
#include "hfsguardadir/objetosbo/ExtensaoBO.h"

using namespace hfsguardadir::comum;
using namespace hfsguardadir::catalogador;
using namespace hfsguardadir::objetosbo;

// ---------------------------------------------------------------------------
FrmPrincipal* frmPrincipal = (FrmPrincipal*)NULL;
// ---------------------------------------------------------------------------

FXDEFMAP(FrmPrincipal) FrmPrincipalMap[]={
  FXMAPFUNC(SEL_COMMAND, FrmPrincipal::MENU_INCLUIRNOVAABA, FrmPrincipal::on_menuIncluirNovaAba),
  FXMAPFUNC(SEL_COMMAND, FrmPrincipal::MENU_ALTERARNOMEABAATIVA, FrmPrincipal::on_menuAlterarNomeAbaAtiva),
  FXMAPFUNC(SEL_COMMAND, FrmPrincipal::MENU_EXCLUIRABAATIVA, FrmPrincipal::on_menuExcluirAbaAtiva),
  FXMAPFUNC(SEL_COMMAND, FrmPrincipal::MENU_IMPORTARDIRETORIO, FrmPrincipal::on_menuImportarDiretorio),
  FXMAPFUNC(SEL_COMMAND, FrmPrincipal::MENU_IMPORTARSUBDIRETORIOS, FrmPrincipal::on_menuImportarSubDiretorios),
  FXMAPFUNC(SEL_COMMAND, FrmPrincipal::MENU_COMPARARDIRETORIOS, FrmPrincipal::on_menuCompararDiretorios),
  FXMAPFUNC(SEL_COMMAND, FrmPrincipal::MENU_CADASTRAREXTENSAOARQUIVO, FrmPrincipal::on_menuCadastrarExtensaoArquivo),
  FXMAPFUNC(SEL_COMMAND, FrmPrincipal::MENU_EXPANDIRDIRETORIOS, FrmPrincipal::on_menuExpandirDiretorios),
  FXMAPFUNC(SEL_COMMAND, FrmPrincipal::MENU_COLAPSARDIRETORIOS, FrmPrincipal::on_menuColapsarDiretorios),
  FXMAPFUNC(SEL_COMMAND, FrmPrincipal::MENU_TXT, FrmPrincipal::on_menuTXT),
  FXMAPFUNC(SEL_COMMAND, FrmPrincipal::MENU_CSV, FrmPrincipal::on_menuCSV),
  FXMAPFUNC(SEL_COMMAND, FrmPrincipal::MENU_HTML, FrmPrincipal::on_menuHTML),
  FXMAPFUNC(SEL_COMMAND, FrmPrincipal::MENU_XML, FrmPrincipal::on_menuXML),
  FXMAPFUNC(SEL_COMMAND, FrmPrincipal::MENU_SQL, FrmPrincipal::on_menuSQL),
  FXMAPFUNC(SEL_COMMAND, FrmPrincipal::MENU_IMPORTARDIRETORIOSVIAXML, FrmPrincipal::on_menuImportarDiretoriosViaXML),
  FXMAPFUNC(SEL_COMMAND, FrmPrincipal::MENU_MOSTRAROCULTARARVOREDIRABAATIVA, FrmPrincipal::on_menuMostrarOcultarArvoreDirAbaAtiva),
  FXMAPFUNC(SEL_COMMAND, FrmPrincipal::MENU_MOSTRAROCULTARLISTAITENSPESQUISADOS, FrmPrincipal::on_menuMostrarOcultarListaItensPesquisados),
  FXMAPFUNC(SEL_COMMAND, FrmPrincipal::MENU_SOBRECATALOGADOR, FrmPrincipal::on_menuSobreCatalogador),
  FXMAPFUNC(SEL_COMMAND, FrmPrincipal::MENU_INFORMACOESDIRETORIOARQUIVO, FrmPrincipal::on_menuInformacoesDiretorioArquivo),
  FXMAPFUNC(SEL_COMMAND, FrmPrincipal::MENU_EXCLUIRDIRETORIOSELECIONADO, FrmPrincipal::on_menuExcluirDiretorioSelecionado),
  FXMAPFUNC(SEL_COMMAND, FrmPrincipal::MENU_EXPANDIRDIRETORIOS2, FrmPrincipal::on_menuExpandirDiretorios2),
  FXMAPFUNC(SEL_COMMAND, FrmPrincipal::MENU_COLAPSARDIRETORIOS2, FrmPrincipal::on_menuColapsarDiretorios2),
  FXMAPFUNC(SEL_COMMAND, FrmPrincipal::MENU_INCLUIRNOVAABA2, FrmPrincipal::on_menuIncluirNovaAba2),
  FXMAPFUNC(SEL_COMMAND, FrmPrincipal::MENU_ALTERARNOMEABAATIVA2, FrmPrincipal::on_menuAlterarNomeAbaAtiva2),
  FXMAPFUNC(SEL_COMMAND, FrmPrincipal::MENU_EXCLUIRABAATIVA2, FrmPrincipal::on_menuExcluirAbaAtiva2),  
  FXMAPFUNC(SEL_COMMAND, FrmPrincipal::BTN_IMPORTARDIRETORIO, FrmPrincipal::on_btnImportarDiretorio_clicked),
  FXMAPFUNC(SEL_COMMAND, FrmPrincipal::BTN_PESQUISA, FrmPrincipal::on_btnPesquisa_clicked),
  FXMAPFUNC(SEL_COMMAND, FrmPrincipal::BARRA_TAB, FrmPrincipal::on_barraTab_change_page),
  FXMAPFUNC(SEL_RIGHTBUTTONRELEASE, FrmPrincipal::ID_ARVORE_FIXA, FrmPrincipal::on_arvoreFixa_RightBtnRelease),
  FXMAPFUNC(SEL_LEFTBUTTONPRESS, FrmPrincipal::ID_ARVORE_FIXA, FrmPrincipal::on_arvoreFixa_LeftBtnPress),
  FXMAPFUNC(SEL_CLICKED, FrmPrincipal::ID_ARVORE_FIXA, FrmPrincipal::on_arvoreFixa_Clicked),
  FXMAPFUNC(SEL_RIGHTBUTTONRELEASE, FrmPrincipal::ID_TABELA_FIXA, FrmPrincipal::on_tabelaFixa_RightBtnRelease),
  FXMAPFUNC(SEL_COMMAND, FrmPrincipal::ID_TABELA_FIXA, FrmPrincipal::on_tabelaFixa_CmdSelectRow),
  //FXMAPFUNC(SEL_LEFTBUTTONRELEASE, FrmPrincipal::ID_TABELA_PESQUISA, FrmPrincipal::on_tabelaPesquisa_LeftBtnRelease),
  FXMAPFUNC(SEL_COMMAND, FrmPrincipal::ID_TABELA_PESQUISA, FrmPrincipal::on_tabelaPesquisa_CmdSelectRow),

  FXMAPFUNC(SEL_CLOSE, 0, FrmPrincipal::onCmdOpSair),
  };
FXIMPLEMENT(FrmPrincipal,FXMainWindow,FrmPrincipalMap,
            ARRAYNUMBER(FrmPrincipalMap))

FrmPrincipal::FrmPrincipal(FXApp* app):
  FXMainWindow(app, "HFSGuardaDiretorio 2.0 - Catalogador de Diretórios",NULL,NULL,DECOR_ALL,0,0, 950, 718){
  IniciaControles(app);
}

void FrmPrincipal::IniciaControles(FXApp* app) {
  this->setIcon(new FXBMPIcon(app,cdouro));

  //fonteSistema=new FXFont(app,"courier",15);
  barraMenu=new FXMenuBar(this,LAYOUT_SIDE_TOP|LAYOUT_FILL_X);

  frameStatus = new FXHorizontalFrame(this, LAYOUT_SIDE_BOTTOM|LAYOUT_FILL_X);

  labStatus=new FXLabel(frameStatus, "", NULL, FRAME_SUNKEN|
    LAYOUT_FIX_WIDTH, 0, 0, 400, 20);
  labStatus->setJustify(FX::JUSTIFY_LEFT);
  barraStatus=new FXStatusBar(frameStatus,LAYOUT_FILL_X|
    STATUSBAR_WITH_DRAGCORNER);
  barraStatus->getStatusLine()->setNormalText("");

  //icone=new FXBMPIcon(app,cdouro);

  barraPesquisa = new FXHorizontalFrame(this, LAYOUT_SIDE_TOP | LAYOUT_FILL_X);
  btnImportarDiretorio = new FXButton(barraPesquisa, "Importar Diretório", 0,
    this, BTN_IMPORTARDIRETORIO, (FRAME_RAISED | FRAME_THICK |LAYOUT_TOP|LAYOUT_LEFT));
  pb = new FXProgressBar(barraPesquisa, this, PB_PRINCIPAL, FRAME_SUNKEN | LAYOUT_FILL_X | LAYOUT_FILL_Y);
  edtPesquisa = new FXTextField(barraPesquisa, 50, this, EDT_PESQUISA, FRAME_SUNKEN);
  edtPesquisa->setTextStyle(TEXTFIELD_LIMITED);
  btnPesquisa = new FXButton(barraPesquisa, "Pesquisar", 0,
	  this, BTN_PESQUISA, (FRAME_RAISED | FRAME_THICK | LAYOUT_TOP | LAYOUT_LEFT));

  spPesquisa = new FXSplitter(this, LAYOUT_FILL_X | LAYOUT_FILL_Y | SPLITTER_VERTICAL);

  framePrincipal = new FXPacker(spPesquisa, LAYOUT_FILL_X | LAYOUT_FILL_Y);

  barraTab = new FXTabBar(framePrincipal, this, BARRA_TAB);

  listaFrames = new FXObjectListOf<FXSplitter>();

  spPrincipal = new FXSplitter(framePrincipal, LAYOUT_FILL_X | LAYOUT_FILL_Y);
  
  arvoreFixa = new Arvore(spPrincipal, this, ID_ARVORE_FIXA, TREELIST_SINGLESELECT | TREELIST_ROOT_BOXES | 
	  TREELIST_SHOWS_BOXES | TREELIST_SHOWS_LINES);
  tabelaFixa = new Tabela(spPrincipal, this, ID_TABELA_FIXA, TABLE_COL_SIZABLE | TABLE_READONLY, true);
  tabelaFixa->setEditable(false);
  tabelaFixa->setDefRowHeight(20);

  listaFrames->append(spPrincipal);

  tabelaPesquisa = new Tabela(spPesquisa, this, ID_TABELA_PESQUISA, TABLE_COL_SIZABLE | TABLE_READONLY, false);

  spPrincipal->setSplit(0, 300);
  spPesquisa->setSplit(0, 450);

  menuAba = new FXMenuPane(this);
  new FXMenuTitle(barraMenu, "&Aba", NULL, menuAba);
  menuIncluirNovaAba = new FXMenuCommand(menuAba, "Incluir nova Aba", NULL, this, MENU_INCLUIRNOVAABA);
  menuAlterarNomeAbaAtiva = new FXMenuCommand(menuAba, "Alterar Nome da Aba Ativa", NULL, this, MENU_ALTERARNOMEABAATIVA);
  menuExcluirAbaAtiva = new FXMenuCommand(menuAba, "Excluir Aba Ativa", NULL, this, MENU_EXCLUIRABAATIVA);
  
  menuDiretorio = new FXMenuPane(this);
  new FXMenuTitle(barraMenu, "&Diretório", NULL, menuDiretorio);

  menuImportarDiretorio = new FXMenuCommand(menuDiretorio, "Importar Diretório", NULL, this, MENU_IMPORTARDIRETORIO);
  menuImportarSubDiretorios = new FXMenuCommand(menuDiretorio, "Importar SubDiretórios", NULL, this, MENU_IMPORTARSUBDIRETORIOS);
  menuCompararDiretorios = new FXMenuCommand(menuDiretorio, "Comparar Diretórios", NULL, this, MENU_COMPARARDIRETORIOS);
  menuCadastrarExtensaoArquivo = new FXMenuCommand(menuDiretorio, "Cadastrar Extensão de Arquivo", NULL, this, MENU_CADASTRAREXTENSAOARQUIVO);
  menuseparador1 = new FXMenuSeparator(menuDiretorio);
  menuExpandirDiretorios = new FXMenuCommand(menuDiretorio, "Expandir Diretórios", NULL, this, MENU_EXPANDIRDIRETORIOS);
  menuColapsarDiretorios = new FXMenuCommand(menuDiretorio, "Colapsar Diretórios", NULL, this, MENU_COLAPSARDIRETORIOS);

  submenu = new FXPopup(this);
  menuTXT = new FXMenuCommand(submenu, "TXT", NULL, this, MENU_TXT);
  menuCSV = new FXMenuCommand(submenu, "CSV", NULL, this, MENU_CSV);
  menuHTML = new FXMenuCommand(submenu, "HTML", NULL, this, MENU_HTML);
  menuXML = new FXMenuCommand(submenu, "XML", NULL, this, MENU_XML);
  menuSQL = new FXMenuCommand(submenu, "SQL", NULL, this, MENU_SQL);

  menuExportarDiretoriosAbaAtiva = new FXMenuCascade(menuDiretorio, "Exportar Diretórios da Aba Ativa", NULL, submenu);

  menuImportarDiretoriosViaXML = new FXMenuCommand(menuDiretorio, "Importar Diretórios via XML", NULL, this, MENU_IMPORTARDIRETORIOSVIAXML);
  menuGravarLogImportacao = new FXMenuCheck(menuDiretorio, "Gravar Log da Importação", this, MENU_GRAVARLOGIMPORTACAO);

  menuVisao = new FXMenuPane(this);
  new FXMenuTitle(barraMenu, "&Visão", NULL, menuVisao);
  menuMostrarOcultarListaItensPesquisados = new FXMenuCommand(menuVisao, "Mostrar/Ocultar lista de itens pesquisados", 
	  NULL, this, MENU_MOSTRAROCULTARLISTAITENSPESQUISADOS);
  menuMostrarOcultarArvoreDirAbaAtiva = new FXMenuCommand(menuVisao, "Mostrar/Ocultar árvore de diretórios da Aba Ativa", 
	  NULL, this, MENU_MOSTRAROCULTARARVOREDIRABAATIVA);

  menuSobre = new FXMenuPane(this);
  new FXMenuTitle(barraMenu, "&Sobre", NULL, menuSobre);
  menuSobreCatalogador = new FXMenuCommand(menuSobre, "Sobre o Catalogador", NULL, this, MENU_SOBRECATALOGADOR);

  ExtensaoBO::getInstancia();
  ConstruirPopupMenu();
  adicionaTabPage(barraTab, "DISCO1");  
}

void FrmPrincipal::create(){
	catalogador = new Catalogador(frmPrincipal->getApp(), frmPrincipal);
	//frmPrincipal->arvoreFixa->selecionarPrimeiroItem();
	
	FXMainWindow::create();	
}

FrmPrincipal::~FrmPrincipal(){
	
	delete menuGravarLogImportacao;
	delete spPesquisa;
	delete pb;
	delete edtPesquisa;
	delete barraMenu;
	delete menuAba;
	delete labStatus;
	delete barraStatus;
	delete listaFrames;
	delete barraPesquisa;
	delete frameStatus;

	delete menuInformacoesDiretorioArquivo;
	delete menuExcluirDiretorioSelecionado;
	delete menuExpandirDiretorios2;
	delete menuColapsarDiretorios2;
	delete menuseparador2;
	delete menuIncluirNovaAba2;
	delete menuAlterarNomeAbaAtiva2;
	delete menuExcluirAbaAtiva2;	
}

void FrmPrincipal::ConstruirPopupMenu() {

	popupmenu = new FXPopup(this);

	menuInformacoesDiretorioArquivo = new FXMenuCommand(popupmenu, "Informações do Diretório / Arquivo", NULL, this, MENU_INFORMACOESDIRETORIOARQUIVO);
	menuExcluirDiretorioSelecionado = new FXMenuCommand(popupmenu, "Excluir Diretório Selecionado", NULL, this, MENU_EXCLUIRDIRETORIOSELECIONADO);
	menuExpandirDiretorios2 = new FXMenuCommand(popupmenu, "Expandir Diretórios", NULL, this, MENU_EXPANDIRDIRETORIOS2);
	menuColapsarDiretorios2 = new FXMenuCommand(popupmenu, "Colapsar Diretórios", NULL, this, MENU_COLAPSARDIRETORIOS2);
	menuseparador2 = new FXMenuSeparator(popupmenu);
	menuIncluirNovaAba2 = new FXMenuCommand(popupmenu, "Incluir Nova Aba", NULL, this, MENU_INCLUIRNOVAABA2);
	menuAlterarNomeAbaAtiva2 = new FXMenuCommand(popupmenu, "Alterar Nome da Aba Ativa", NULL, this, MENU_ALTERARNOMEABAATIVA2);
	menuExcluirAbaAtiva2 = new FXMenuCommand(popupmenu, "Excluir Aba Ativa", NULL, this, MENU_EXCLUIRABAATIVA2);
}

void FrmPrincipal::Mostrar(FXApp* app)
{
	frmPrincipal->show(PLACEMENT_SCREEN);
}

void FrmPrincipal::ProgressoLog(Progresso progresso)
{
	if (frmPrincipal != NULL) {
		if (progresso.posicao == 0) {
			frmPrincipal->pb->setProgress(progresso.minimo);
		}
		frmPrincipal->pb->setProgress(
			Rotinas::calculaProgresso(progresso.maximo, progresso.posicao));
	}
}

void FrmPrincipal::adicionaTabPage(FXTabBar* barraTab, const FXString nomeAba) {
	FXTabItem* tabAba;

	FXIcon* tabIcone = new FXBMPIcon(getApp(), cdouro);
	tabAba = new FXTabItem(barraTab, nomeAba, tabIcone);
}

long FrmPrincipal::on_barraTab_change_page(FXObject* obj, FXSelector sel, void* ptr){  
	catalogador->tabPanelMudou(this);
	return true;
}

long FrmPrincipal::onCmdOpSair(FXObject* obj, FXSelector sel, void* ptr) {
	/*
  if (FXMessageBox::question(this, MBOX_YES_NO, STR_TITULO,
	  "Deseja sair do sistema?") == MBOX_CLICKED_NO) {
     return true;
  }
  */
	
	Rotinas::getInstancia()->BancoDesconectar();
	getApp()->exit(0);
	return true;
}

long FrmPrincipal::on_menuIncluirNovaAba(FXObject* obj, FXSelector sel, void* ptr) {
	catalogador->IncluirNovaAba();
	return true;
}

long FrmPrincipal::on_menuAlterarNomeAbaAtiva(FXObject* obj, FXSelector sel, void* ptr) {
	catalogador->AlterarNomeAbaAtiva(FrmPrincipal::ProgressoLog);
	return true;
}

long FrmPrincipal::on_menuExcluirAbaAtiva(FXObject* obj, FXSelector sel, void* ptr) {
	catalogador->ExcluirAbaAtiva(FrmPrincipal::ProgressoLog);
	return true;
}

long FrmPrincipal::on_menuImportarDiretorio(FXObject* obj, FXSelector sel, void* ptr) {
	catalogador->ComecaImportacao(this, false, FrmPrincipal::ProgressoLog);
	return true;
}

long FrmPrincipal::on_menuImportarSubDiretorios(FXObject* obj, FXSelector sel, void* ptr) {
	catalogador->ComecaImportacao(this, true, FrmPrincipal::ProgressoLog);
	return true;
}

long FrmPrincipal::on_menuCompararDiretorios(FXObject* obj, FXSelector sel, void* ptr) {	
	FrmCompararDiretorio::mostrar(this);
	return true;
}

long FrmPrincipal::on_menuCadastrarExtensaoArquivo(FXObject* obj, FXSelector sel, void* ptr) {
	FrmCadExtensao::mostrar(this);
	return true;
}

long FrmPrincipal::on_menuExpandirDiretorios(FXObject* obj, FXSelector sel, void* ptr) {
	catalogador->getArvoreAtual(this)->expandirTodos();
	return true;
}

long FrmPrincipal::on_menuColapsarDiretorios(FXObject* obj, FXSelector sel, void* ptr) {
	catalogador->getArvoreAtual(this)->colapsarTodos();
	return true;
}

long FrmPrincipal::on_menuExportarDiretoriosAbaAtiva(FXObject* obj, FXSelector sel, void* ptr) {
	return true;
}

long FrmPrincipal::on_menuTXT(FXObject* obj, FXSelector sel, void* ptr) {
	catalogador->ExportarArquivo(teTXT, FrmPrincipal::ProgressoLog);
	return true;
}

long FrmPrincipal::on_menuCSV(FXObject* obj, FXSelector sel, void* ptr) {
	catalogador->ExportarArquivo(teCSV, FrmPrincipal::ProgressoLog);
	return true;
}

long FrmPrincipal::on_menuHTML(FXObject* obj, FXSelector sel, void* ptr) {
	catalogador->ExportarArquivo(teHTML, FrmPrincipal::ProgressoLog);
	return true;
}

long FrmPrincipal::on_menuXML(FXObject* obj, FXSelector sel, void* ptr) {
	catalogador->ExportarArquivo(teXML, FrmPrincipal::ProgressoLog);
	return true;
}

long FrmPrincipal::on_menuSQL(FXObject* obj, FXSelector sel, void* ptr) {
	catalogador->ExportarArquivo(teSQL, FrmPrincipal::ProgressoLog);
	return true;
}

long FrmPrincipal::on_menuImportarDiretoriosViaXML(FXObject* obj, FXSelector sel, void* ptr) {
	std::vector<std::string> log;
	catalogador->ImportarArquivo(this, log, FrmPrincipal::ProgressoLog);
	return true;
}

long FrmPrincipal::on_menuMostrarOcultarArvoreDirAbaAtiva(FXObject* obj, FXSelector sel, void* ptr) {
	catalogador->mostrarOcultarArvore();
	return true;
}

long FrmPrincipal::on_menuMostrarOcultarListaItensPesquisados(FXObject* obj, FXSelector sel, void* ptr) {
	catalogador->mostrarOcultarListaItensPesquisados(this);
	return true;
}

long FrmPrincipal::on_menuSobreCatalogador(FXObject* obj, FXSelector sel, void* ptr) {
	FrmSobre::mostrar(this);
	return true;
}

long FrmPrincipal::on_btnImportarDiretorio_clicked(FXObject* obj, FXSelector sel, void* ptr) {
	on_menuImportarDiretorio(obj, sel, ptr);
	return true;
}

long FrmPrincipal::on_btnPesquisa_clicked(FXObject* obj, FXSelector sel, void* ptr) {
	catalogador->Pesquisar();
	return true;
}

long FrmPrincipal::on_menuInformacoesDiretorioArquivo(FXObject* obj, FXSelector sel, void* ptr) {
	catalogador->InformacoesDiretorioArquivo();
	return true;
}

long FrmPrincipal::on_menuExcluirDiretorioSelecionado(FXObject* obj, FXSelector sel, void* ptr) {
	catalogador->ExcluirDiretorioSelecionado(FrmPrincipal::ProgressoLog);
	return true;
}

long FrmPrincipal::on_menuExpandirDiretorios2(FXObject* obj, FXSelector sel, void* ptr) {
	on_menuExpandirDiretorios(obj, sel, ptr);
	return true;
}

long FrmPrincipal::on_menuColapsarDiretorios2(FXObject* obj, FXSelector sel, void* ptr) {
	on_menuColapsarDiretorios(obj, sel, ptr);
	return true;
}

long FrmPrincipal::on_menuIncluirNovaAba2(FXObject* obj, FXSelector sel, void* ptr) {
	on_menuIncluirNovaAba(obj, sel, ptr);
	return true;
}

long FrmPrincipal::on_menuAlterarNomeAbaAtiva2(FXObject* obj, FXSelector sel, void* ptr) {
	on_menuAlterarNomeAbaAtiva(obj, sel, ptr);
	return true;
}

long FrmPrincipal::on_menuExcluirAbaAtiva2(FXObject* obj, FXSelector sel, void* ptr) {
	on_menuExcluirAbaAtiva(obj, sel, ptr);
	return true;
}

/*
void FrmPrincipal::on_arvoreFixa_row_collapsed(const Gtk::TreeModel::iterator& iter, const Gtk::TreeModel::Path& path) {
	Arvore* arvore = catalogador->getArvoreAtual();
	Gtk::TreeRow linha;

	linha = *iter;
	linha[arvore->modeloArvore.coluna0] = ExtensaoBO::getInstancia()->DiretorioXPM;
}
*/

long FrmPrincipal::on_arvoreFixa_RightBtnRelease(FXObject* obj, FXSelector sel, void* ptr) {
	FXint x;
	FXint y;
	FXuint buttons;

	if (this->getCursorPosition(x, y, buttons)) {
		popupmenu->popup(this, x, y);
	}	
	return false;
}

long FrmPrincipal::on_arvoreFixa_LeftBtnPress(FXObject* obj, FXSelector sel, void* ptr) {
	//Arvore* arvore = catalogador->getArvoreAtual(this);
	//arvore->expandirSelecionado();
	return false;
}

long FrmPrincipal::on_arvoreFixa_Clicked(FXObject* obj, FXSelector sel, void* ptr) {
	Tabela* tabela = catalogador->getTabelaAtual(this);
	Arvore* arvore = catalogador->getArvoreAtual(this);
	FXTreeItem* item;

	item = arvore->getCurrentItem();
	if (arvore->isItemSelected(item)) {
		catalogador->ListarArquivos(tabela, arvore, item);
	}

	return true;
}

long FrmPrincipal::on_tabelaFixa_RightBtnRelease(FXObject* obj, FXSelector sel, void* ptr) {
	FXint x;
	FXint y;
	FXuint buttons;

	if (this->getCursorPosition(x, y, buttons)) {
		popupmenu->popup(this, x, y);
	}
	return false;
}

long FrmPrincipal::on_tabelaFixa_CmdSelectRow(FXObject* obj, FXSelector sel, void* ptr) {
	Tabela* tabela = catalogador->getTabelaAtual(this);
	std::string nome, tipo;

	int row = tabela->getCurrentRow();
	//if (tabela->isRowSelected(row)) {
	if (row > 0) {
		nome = tabela->getItem(row, 0)->getText().text();
		tipo = tabela->getItem(row, 2)->getText().text();

		catalogador->DuploCliqueLista(nome, tipo);		
	}
	return true;
}

long FrmPrincipal::on_tabelaPesquisa_CmdSelectRow(FXObject* obj, FXSelector sel, void* ptr) {
	std::string nome, caminho, nomeAba;

	int row = tabelaPesquisa->getCurrentRow();
	//if (tabelaPesquisa->isRowSelected(row)) {	
	if (row > 0) {
		nome = tabelaPesquisa->getItem(row, 0)->getText().text();
		caminho = tabelaPesquisa->getItem(row, 5)->getText().text();
		nomeAba = tabelaPesquisa->getItem(row, 6)->getText().text();

		catalogador->EncontrarItemLista(nomeAba, nome, caminho);
	}
	return false;
}
