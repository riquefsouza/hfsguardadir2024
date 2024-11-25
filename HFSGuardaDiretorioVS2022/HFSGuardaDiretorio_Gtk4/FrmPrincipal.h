#ifndef FrmPrincipal_H
#define FrmPrincipal_H
// ---------------------------------------------------------------------------
#include "resource.h"
#include "hfsguardadir/objetosgui/Arvore.h"
#include "hfsguardadir/objetosgui/Tabela.h"
// ---------------------------------------------------------------------------
struct SFrmPrincipal {
	GtkWidget *vbox1; 	
	GtkWidget* barraMenu1;	
	GSimpleActionGroup* actions;

	GtkMenuButton* menuAba;
	GMenu* submenuAba;
	GMenuItem* menuIncluirNovaAba;
	GSimpleAction* actionIncluirNovaAba;
	GMenuItem* menuAlterarNomeAbaAtiva;
	GSimpleAction* actionAlterarNomeAbaAtiva;
	GMenuItem* menuExcluirAbaAtiva;
	GSimpleAction* actionExcluirAbaAtiva;

	GtkMenuButton* menuDiretorio;
	GMenu* submenuDiretorio;
	GMenuItem* menuImportarDiretorio;
	GSimpleAction* actionImportarDiretorio;
	GMenuItem* menuImportarSubDiretorios;
	GSimpleAction* actionImportarSubDiretorios;
	GMenuItem* menuCompararDiretorios;
	GSimpleAction* actionCompararDiretorios;
	GMenuItem* menuCadastrarExtensaoArquivo;
	GSimpleAction* actionCadastrarExtensaoArquivo;
	//GMenuItem* menuseparador1; gtk_separator_menu_item_new
	GMenuItem* menuExpandirDiretorios;
	GSimpleAction* actionExpandirDiretorios;
	GMenuItem* menuColapsarDiretorios;
	GSimpleAction* actionColapsarDiretorios;
	//GMenuItem* menuExportarDiretoriosAbaAtiva;
	//GSimpleAction* actionExportarDiretoriosAbaAtiva;
	//GMenu* submenu2;
	GMenuItem* menuTXT;
	GSimpleAction* actionTXT;
	GMenuItem* menuCSV;
	GSimpleAction* actionCSV;
	GMenuItem* menuHTML;
	GSimpleAction* actionHTML;
	GMenuItem* menuXML;
	GSimpleAction* actionXML;
	GMenuItem* menuSQL;
	GSimpleAction* actionSQL;
	GMenuItem* menuImportarDiretoriosViaXML;
	GSimpleAction* actionImportarDiretoriosViaXML;
	GMenuItem* menuGravarLogImportacao;
	GSimpleAction* actionGravarLogImportacao;

	GtkMenuButton* menuVisao;
	GMenu* submenuVisao;
	GMenuItem* menuMostrarOcultarArvoreDirAbaAtiva;
	GSimpleAction* actionMostrarOcultarArvoreDirAbaAtiva;
	GMenuItem* menuMostrarOcultarListaItensPesquisados;
	GSimpleAction* actionMostrarOcultarListaItensPesquisados;

	GtkMenuButton* menuSobre;
	GMenu* submenuSobre;
	GMenuItem* menuSobreCatalogador;
	GSimpleAction* actionSobreCatalogador;

	GtkWidget* toolbar1;
	GtkWidget* btnImportarDiretorio;
	GtkWidget* pbImportarDiretorio;	
	GtkWidget* edtPesquisa;
	GtkWidget* btnPesquisa;

	GtkWidget* spPesquisa;
	GtkWidget* hbox6;
	GtkWidget* notebook1;					
	
	GtkWidget *spPrincipal; 
	GtkWidget *labAbaFixa;
	GtkWidget *arvoreFixa;
	GtkWidget *scrollArvore;
	GtkWidget *tabelaFixa;
	GtkWidget *tabelaPesquisa;
	GtkWidget *scrollTabelaFixa;
	GtkWidget *scrollPesquisa;
	GtkWidget *barraStatus111; 
	GtkWidget *barraStatus211; 
	/*
	GtkWidget *popupMenu;
	gint nLargura;
	gint nAltura;
	
	GtkWidget *menuInformacoesDiretorioArquivo;
	GtkWidget *menuExcluirDiretorioSelecionado;	
	GtkWidget *menuIncluirNovaAba2;
	GtkWidget *menuAlterarNomeAbaAtiva2;
	GtkWidget *menuExcluirAbaAtiva2;
	GtkWidget *menuseparador2;
	GtkWidget *menuExpandirDiretorios2;
	GtkWidget *menuColapsarDiretorios2;
	*/
	GtkWidget *frmPrincipal;
};
extern struct SFrmPrincipal FrmPrincipal;
// ---------------------------------------------------------------------------
	GtkWidget *FrmPrincipal_Criar(GtkApplication* app);
	void FrmPrincipal_Mostrar(GtkApplication* app);
	void FrmPrincipal_ProgressoLog(Progresso progresso);

	void on_menuIncluirNovaAba_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data);
	void on_menuAlterarNomeAbaAtiva_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data);
	void on_menuExcluirAbaAtiva_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data);
	void on_menuImportarDiretorio_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data);
	void on_menuImportarSubDiretorios_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data);
	void on_menuCompararDiretorios_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data);
	void on_menuCadastrarExtensaoArquivo_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data);
	void on_menuExpandirDiretorios_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data);
	void on_menuColapsarDiretorios_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data);
	//void on_menuExportarDiretoriosAbaAtiva_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data);
	void on_menuTXT_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data);
	void on_menuCSV_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data);
	void on_menuHTML_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data);
	void on_menuXML_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data);
	void on_menuSQL_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data);
	void on_menuImportarDiretoriosViaXML_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data);
	void on_menuMostrarOcultarArvoreDirAbaAtiva_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data);
	void on_menuMostrarOcultarListaItensPesquisados_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data);
	void on_menuSobreCatalogador_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data);

	void FrmPrincipal_adicionaTabPage(GtkNotebook* noteBook, GtkPaned* spPanel, const GString* nomeAba);
	void on_FrmPrincipal_destroy(GtkWidget* widget, gpointer user_data);
	/*
	GtkLabel* FrmPrincipal_getLabStatus1();
	GtkLabel* FrmPrincipal_getLabStatus2();
	*/
	void on_btnImportarDiretorio_clicked(GtkWidget* widget, gpointer user_data);
	void on_btnPesquisa_clicked(GtkWidget* widget, gpointer user_data);
	void on_notebook1_select_page(GtkNotebook *notebook, gboolean arg1, gpointer user_data);
	void on_arvoreFixa_selection_changed(GtkTreeSelection *treeselection, gpointer user_data);
	void on_arvoreFixa_row_collapsed(GtkTreeView *tree_view, GtkTreeIter *iter, GtkTreePath *path, gpointer user_data);
	gboolean on_arvoreFixa_button_release_event(GtkWidget *widget, GdkEvent *event, gpointer user_data);
	gboolean on_arvoreFixa_button_press_event(GtkWidget *widget, GdkEvent *event, gpointer user_data);
	void on_arvoreFixa_row_expanded(GtkTreeView *tree_view, GtkTreeIter *iter, GtkTreePath *path, gpointer user_data);
	gboolean on_tabelaFixa_button_release_event(GtkWidget *widget, GdkEvent *event, gpointer user_data);
	void on_tabelaFixa_row_activated(GtkTreeView *tree_view, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);
	gboolean on_tabelaPesquisa_button_release_event(GtkWidget *widget, GdkEvent *event, gpointer user_data);

	//void FrmPrincipal_ConstruirPopupMenu();
	void FrmPrincipal_menuInformacoesDiretorioArquivo_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data);
	void FrmPrincipal_menuExcluirDiretorioSelecionado_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data);
	void FrmPrincipal_menuIncluirNovaAba2_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data);
	void FrmPrincipal_menuAlterarNomeAbaAtiva2_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data);
	void FrmPrincipal_menuExcluirAbaAtiva2_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data);
	void FrmPrincipal_menuExpandirDiretorios2_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data);
	void FrmPrincipal_menuColapsarDiretorios2_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data);
	
// ---------------------------------------------------------------------------
#endif
// ---------------------------------------------------------------------------
