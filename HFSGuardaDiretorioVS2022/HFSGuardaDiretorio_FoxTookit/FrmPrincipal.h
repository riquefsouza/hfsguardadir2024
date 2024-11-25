#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include "hfsguardadir/objetosgui/Arvore.h"
#include "hfsguardadir/objetosgui/Tabela.h"

using namespace hfsguardadir::objetosgui;

class FrmPrincipal : public FXMainWindow {
  FXDECLARE(FrmPrincipal)

public:
  enum { MENU_INCLUIRNOVAABA = FXMainWindow::ID_LAST, 
	  MENU_ALTERARNOMEABAATIVA, MENU_EXCLUIRABAATIVA,
	  MENU_IMPORTARDIRETORIO, MENU_IMPORTARSUBDIRETORIOS, MENU_COMPARARDIRETORIOS,
	  MENU_CADASTRAREXTENSAOARQUIVO, MENU_EXPANDIRDIRETORIOS, MENU_COLAPSARDIRETORIOS,
	  MENU_TXT, MENU_CSV, MENU_HTML, MENU_XML, MENU_SQL,
	  MENU_IMPORTARDIRETORIOSVIAXML, MENU_MOSTRAROCULTARARVOREDIRABAATIVA,
	  MENU_GRAVARLOGIMPORTACAO,
	  MENU_MOSTRAROCULTARLISTAITENSPESQUISADOS, MENU_SOBRECATALOGADOR,
	  MENU_INFORMACOESDIRETORIOARQUIVO, MENU_EXCLUIRDIRETORIOSELECIONADO,
	  MENU_EXPANDIRDIRETORIOS2, MENU_COLAPSARDIRETORIOS2, MENU_INCLUIRNOVAABA2,
	  MENU_ALTERARNOMEABAATIVA2, MENU_EXCLUIRABAATIVA2,
	  BTN_IMPORTARDIRETORIO, PB_PRINCIPAL, EDT_PESQUISA, BTN_PESQUISA,
	  BARRA_TAB, ID_ARVORE_FIXA, ID_TABELA_FIXA, ID_TABELA_PESQUISA
  };

  FXTabBar* barraTab;
  FXMenuCheck *menuGravarLogImportacao;
  FXSplitter *spPesquisa;
  FXProgressBar *pb;
  FXTextField *edtPesquisa;
  Tabela *tabelaPesquisa;
  FXStatusBar* barraStatus;
  FXSplitter* spPrincipal;
  FXHorizontalFrame* barraPesquisa;
  FXLabel* labStatus;
  FXPacker* framePrincipal;
  FXObjectListOf<FXSplitter>* listaFrames;

  FrmPrincipal(FXApp* app);
  virtual void create();
  virtual ~FrmPrincipal();

  static void Mostrar(FXApp* app);
  static void ProgressoLog(Progresso progresso);
  void adicionaTabPage(FXTabBar* barraTab, const FXString nomeAba);
  long on_barraTab_change_page(FXObject* obj, FXSelector sel, void* ptr);

  long onCmdOpSair(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuIncluirNovaAba(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuAlterarNomeAbaAtiva(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuExcluirAbaAtiva(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuImportarDiretorio(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuImportarSubDiretorios(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuCompararDiretorios(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuCadastrarExtensaoArquivo(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuExpandirDiretorios(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuColapsarDiretorios(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuExportarDiretoriosAbaAtiva(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuTXT(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuCSV(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuHTML(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuXML(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuSQL(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuImportarDiretoriosViaXML(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuMostrarOcultarArvoreDirAbaAtiva(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuMostrarOcultarListaItensPesquisados(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuSobreCatalogador(FXObject* obj, FXSelector sel, void* ptr);

  long on_btnImportarDiretorio_clicked(FXObject* obj, FXSelector sel, void* ptr);
  long on_btnPesquisa_clicked(FXObject* obj, FXSelector sel, void* ptr);

  long on_menuInformacoesDiretorioArquivo(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuExcluirDiretorioSelecionado(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuExpandirDiretorios2(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuColapsarDiretorios2(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuIncluirNovaAba2(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuAlterarNomeAbaAtiva2(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuExcluirAbaAtiva2(FXObject* obj, FXSelector sel, void* ptr);

  long on_arvoreFixa_RightBtnRelease(FXObject* obj, FXSelector sel, void* ptr);
  long on_arvoreFixa_LeftBtnPress(FXObject* obj, FXSelector sel, void* ptr);
  long on_arvoreFixa_Clicked(FXObject* obj, FXSelector sel, void* ptr);

  long on_tabelaFixa_RightBtnRelease(FXObject* obj, FXSelector sel, void* ptr);
  long on_tabelaFixa_CmdSelectRow(FXObject* obj, FXSelector sel, void* ptr);
  long on_tabelaPesquisa_CmdSelectRow(FXObject* obj, FXSelector sel, void* ptr);

protected:
	FXMenuBar  *barraMenu;
	FXMenuPane *menuAba;
	FXMenuCommand *menuIncluirNovaAba;
	FXMenuCommand *menuAlterarNomeAbaAtiva;
	FXMenuCommand *menuExcluirAbaAtiva;

	FXMenuPane *menuDiretorio;
	FXMenuCommand *menuImportarDiretorio;
	FXMenuCommand *menuImportarSubDiretorios;
	FXMenuCommand *menuCompararDiretorios;
	FXMenuCommand *menuCadastrarExtensaoArquivo;
	FXMenuCommand *menuExpandirDiretorios;
	FXMenuCommand *menuColapsarDiretorios;
	FXMenuSeparator *menuseparador1;

	FXMenuCascade *menuExportarDiretoriosAbaAtiva;
	FXPopup *submenu;
	FXMenuCommand *menuTXT;
	FXMenuCommand *menuCSV;
	FXMenuCommand *menuHTML;
	FXMenuCommand *menuXML;
	FXMenuCommand *menuSQL;
	FXMenuCommand *menuImportarDiretoriosViaXML;
	FXMenuPane *menuVisao;
	FXMenuCommand *menuMostrarOcultarArvoreDirAbaAtiva;
	FXMenuCommand *menuMostrarOcultarListaItensPesquisados;
	FXMenuPane *menuSobre;
	FXMenuCommand *menuSobreCatalogador;
	
	FXButton *btnImportarDiretorio;
	FXButton *btnPesquisa;

	FXHorizontalFrame *frameStatus;
	//FXFont            *fonteSistema;
	FXIcon            *icone;
	FXIcon            *bmpSobre;
  
	FXFrame *tab1;

	FXPopup *popupmenu;
	FXMenuCommand *menuInformacoesDiretorioArquivo;
	FXMenuCommand *menuExcluirDiretorioSelecionado;
	FXMenuCommand *menuExpandirDiretorios2;
	FXMenuCommand *menuColapsarDiretorios2;
	FXMenuSeparator *menuseparador2;
	FXMenuCommand *menuIncluirNovaAba2;
	FXMenuCommand *menuAlterarNomeAbaAtiva2;
	FXMenuCommand *menuExcluirAbaAtiva2;

	Arvore* arvoreFixa;
	Tabela* tabelaFixa;

private:
  FrmPrincipal(){}

  void IniciaControles(FXApp* app);
  void ConstruirPopupMenu();
};

extern FrmPrincipal *frmPrincipal;

#endif
