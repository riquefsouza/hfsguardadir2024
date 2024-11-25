#ifndef FrmCadExtensao_H
#define FrmCadExtensao_H
// ---------------------------------------------------------------------------
#include "resource.h"
// ---------------------------------------------------------------------------
struct SFrmCadExtensao {
	GtkWidget *form_vbox;
	GtkWidget *vbox;
	GtkWidget *barraMenu;
	GtkWidget *menuExtensao;
	GtkWidget *submenuExtensao;
	GtkWidget *menuIncluirExtensao;
	GtkWidget *menuExcluirExtensao;
	GtkWidget *menuExcluirTodasExtensoes;
	GtkWidget *menuExportarTodos;
	GtkWidget *submenuExportarTodos;
	GtkWidget *menuExportarBitmap;
	GtkWidget *menuExportarIcone;
	GtkWidget *menuExportarGIF;
	GtkWidget *menuExportarJPEG;
	GtkWidget *menuExportarPNG;
	GtkWidget *menuExportarTIFF;
	GtkWidget *menuImportarTodos;
	GtkWidget *submenuImportarTodos;
	GtkWidget *menuImportarIconesArquivos;
	GtkWidget *menuExtrairIconesArquivos;
	GtkWidget *scrollTabela;
	GtkWidget *tabelaExtensao;
	GtkTreeViewColumn *colunaCadExtExtensao;
	GtkTreeViewColumn *colunaCadExtIcone;
	GtkWidget *form_area;
	GtkWidget *btnIncluir;
	GtkWidget *btnExcluir;

	GtkListStore *store;
	GtkTreeModel *modelo;
	GtkTreeSelection *selecao;

	GtkWidget *frmCadExtensao;
};
extern struct SFrmCadExtensao FrmCadExtensao;
// ---------------------------------------------------------------------------
	GtkWidget *FrmCadExtensao_Criar();
	void FrmCadExtensao_Mostrar();
	void on_FrmCadExtensao_destroy(GtkWidget* widget, gpointer user_data);
	void FrmCadExtensao_CarregarExtensoesNaGrid();

	void on_menuIncluirExtensao_activate(GtkWidget* widget, gpointer user_data);
	void on_menuExcluirExtensao_activate(GtkWidget* widget, gpointer user_data);
	void on_menuExcluirTodasExtensoes_activate(GtkWidget* widget, gpointer user_data);
	void on_menuExportarBitmap_activate(GtkWidget* widget, gpointer user_data);
	void on_menuExportarIcone_activate(GtkWidget* widget, gpointer user_data);
	void on_menuExportarGIF_activate(GtkWidget* widget, gpointer user_data);
	void on_menuExportarJPEG_activate(GtkWidget* widget, gpointer user_data);
	void on_menuExportarPNG_activate(GtkWidget* widget, gpointer user_data);
	void on_menuExportarTIFF_activate(GtkWidget* widget, gpointer user_data);
	void on_menuImportarIconesArquivos_activate(GtkWidget* widget, gpointer user_data);
	void on_menuExtrairIconesArquivos_activate(GtkWidget* widget, gpointer user_data);
	void on_btnIncluir_clicked(GtkWidget* widget, gpointer user_data);
	void on_btnExcluir_clicked(GtkWidget* widget, gpointer user_data);

// ---------------------------------------------------------------------------
#endif
// ---------------------------------------------------------------------------
