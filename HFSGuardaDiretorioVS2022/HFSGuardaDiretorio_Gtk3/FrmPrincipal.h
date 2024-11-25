#ifndef FrmPrincipal_H
#define FrmPrincipal_H
// ---------------------------------------------------------------------------
#include "resource.h"
#include "hfsguardadir/objetosgui/Arvore.h"
#include "hfsguardadir/objetosgui/Tabela.h"
// ---------------------------------------------------------------------------
struct SFrmPrincipal {
	GtkWidget *vbox1; 
	GtkWidget *barraMenu1; 
	GtkWidget *menuAba; 
	GtkWidget *submenuAba; 
	GtkWidget *menuIncluirNovaAba; 
	GtkWidget *menuAlterarNomeAbaAtiva; 
	GtkWidget *menuExcluirAbaAtiva; 
	GtkWidget *menuDiretorio; 
	GtkWidget *submenuDiretorio; 
	GtkWidget *menuImportarDiretorio; 
	GtkWidget *menuImportarSubDiretorios; 
	GtkWidget *menuCompararDiretorios; 
	GtkWidget *menuCadastrarExtensaoArquivo; 
	GtkWidget *menuseparador1; 
	GtkWidget *menuExpandirDiretorios; 
	GtkWidget *menuColapsarDiretorios; 
	GtkWidget *menuExportarDiretoriosAbaAtiva; 
	GtkWidget *menu2; 
	GtkWidget *menuTXT; 
	GtkWidget *menuCSV; 
	GtkWidget *menuHTML; 
	GtkWidget *menuXML; 
	GtkWidget *menuSQL; 
	GtkWidget *menuImportarDiretoriosViaXML; 
	GtkWidget *menuGravarLogImportacao; 
	GtkWidget *menuVisao; 
	GtkWidget *submenuVisao; 
	GtkWidget *menuMostrarOcultarArvoreDirAbaAtiva; 
	GtkWidget *menuMostrarOcultarListaItensPesquisados; 
	GtkWidget *menuSobre; 
	GtkWidget *submenuSobre; 
	GtkWidget *menuSobreCatalogador; 
	GtkWidget *toolbar1; 
	GtkToolItem *toolbutton1; 
	GtkWidget *btnImportarDiretorio; 
	GtkToolItem *toolbutton2; 
	GtkWidget *pb; 
	GtkToolItem *toolbutton3; 
	GtkWidget *edtPesquisa; 
	GtkToolItem *toolbutton4; 
	GtkWidget *btnPesquisa; 
	GtkWidget *spPesquisa; 
	GtkWidget *notebook1; 
	GtkWidget *sp; 

	GtkWidget *labAbaFixa;
	GtkWidget *arvoreFixa;
	GtkWidget *scrollArvore;
	GtkWidget *tabelaFixa;
	GtkWidget *tabelaPesquisa;
	GtkWidget *scrollTabelaFixa;
	GtkWidget *scrollPesquisa;

	GtkWidget *hbox6; 
	GtkWidget *barraStatus111; 
	GtkWidget *barraStatus211; 

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

	GtkWidget *frmPrincipal;
};
extern struct SFrmPrincipal FrmPrincipal;
// ---------------------------------------------------------------------------
	GtkWidget *FrmPrincipal_Criar();
	void FrmPrincipal_Mostrar();
	void FrmPrincipal_ProgressoLog(Progresso progresso);
	void on_FrmPrincipal_destroy(GtkWidget* widget, gpointer user_data);
	GtkLabel* FrmPrincipal_getLabStatus1();
	GtkLabel* FrmPrincipal_getLabStatus2();
	void FrmPrincipal_adicionaTabPage(GtkNotebook* noteBook, GtkPaned* spPanel, const GString* nomeAba);

	void on_menuIncluirNovaAba_activate(GtkWidget* widget, gpointer user_data);
	void on_menuAlterarNomeAbaAtiva_activate(GtkWidget* widget, gpointer user_data);
	void on_menuExcluirAbaAtiva_activate(GtkWidget* widget, gpointer user_data);
	void on_menuImportarDiretorio_activate(GtkWidget* widget, gpointer user_data);
	void on_menuImportarSubDiretorios_activate(GtkWidget* widget, gpointer user_data);
	void on_menuCompararDiretorios_activate(GtkWidget* widget, gpointer user_data);
	void on_menuCadastrarExtensaoArquivo_activate(GtkWidget* widget, gpointer user_data);
	void on_menuExpandirDiretorios_activate(GtkWidget* widget, gpointer user_data);
	void on_menuColapsarDiretorios_activate(GtkWidget* widget, gpointer user_data);
	void on_menuExportarDiretoriosAbaAtiva_activate(GtkWidget* widget, gpointer user_data);
	void on_menuTXT_activate(GtkWidget* widget, gpointer user_data);
	void on_menuCSV_activate(GtkWidget* widget, gpointer user_data);
	void on_menuHTML_activate(GtkWidget* widget, gpointer user_data);
	void on_menuXML_activate(GtkWidget* widget, gpointer user_data);
	void on_menuSQL_activate(GtkWidget* widget, gpointer user_data);
	void on_menuImportarDiretoriosViaXML_activate(GtkWidget* widget, gpointer user_data);
	void on_menuMostrarOcultarArvoreDirAbaAtiva_activate(GtkWidget* widget, gpointer user_data);
	void on_menuMostrarOcultarListaItensPesquisados_activate(GtkWidget* widget, gpointer user_data);
	void on_menuSobreCatalogador_activate(GtkWidget* widget, gpointer user_data);
	
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
	gboolean on_FrmPrincipal_delete_event(GtkWidget *widget, GdkEvent *event, gpointer user_data);

	void FrmPrincipal_ConstruirPopupMenu();
	void FrmPrincipal_menuInformacoesDiretorioArquivo_activate(GtkWidget* widget, gpointer user_data);
	void FrmPrincipal_menuExcluirDiretorioSelecionado_activate(GtkWidget* widget, gpointer user_data);
	void FrmPrincipal_menuIncluirNovaAba2_activate(GtkWidget* widget, gpointer user_data);
	void FrmPrincipal_menuAlterarNomeAbaAtiva2_activate(GtkWidget* widget, gpointer user_data);
	void FrmPrincipal_menuExcluirAbaAtiva2_activate(GtkWidget* widget, gpointer user_data);
	void FrmPrincipal_menuExpandirDiretorios2_activate(GtkWidget* widget, gpointer user_data);
	void FrmPrincipal_menuColapsarDiretorios2_activate(GtkWidget* widget, gpointer user_data);

// ---------------------------------------------------------------------------
#endif
// ---------------------------------------------------------------------------
