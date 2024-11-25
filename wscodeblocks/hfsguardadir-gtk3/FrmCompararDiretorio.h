#ifndef FrmCompararDiretorio_H
#define FrmCompararDiretorio_H
// ---------------------------------------------------------------------------
#include "resource.h"
#include "hfsguardadir/objetosgui/Arvore.h"
#include "hfsguardadir/objetosgui/Tabela.h"
#include "hfsguardadir/comum/Rotinas.h"
// ---------------------------------------------------------------------------
struct SFrmCompararDiretorio {
	GtkWidget *vbox5;
	GtkWidget *hbox1;
	GtkWidget *btnCompararDiretorios;
	GtkWidget *pb2;
	GtkWidget *btnSalvarLog;
	GtkWidget *hbox2;
	GtkWidget *frame2;
	GtkWidget *vbox6;
	GtkWidget *cmbAba1;
	GtkWidget *tvDiretorio1;
	GtkWidget *scrollArvore1;
	GtkWidget *labDiretorio1;
	GtkWidget *frame3;
	GtkWidget *vbox7;
	GtkWidget *cmbAba2;
	GtkWidget *tvDiretorio2;
	GtkWidget *scrollArvore2;
	GtkWidget *label6;
	GtkWidget *hbox4;
	GtkWidget *labDiferencasEncontradas;
	GtkWidget *tabelaCompara;
	GtkWidget *scrollCompara;
	GtkWidget *hbox5;
	GtkWidget *barraStatus11;
	GtkWidget *barraStatus21;

	ListaDiretorio listaCompara;

	GtkWidget *frmCompararDiretorio;
};
extern struct SFrmCompararDiretorio FrmCompararDiretorio;
// ---------------------------------------------------------------------------
	GtkWidget *FrmCompararDiretorio_Criar();
	void FrmCompararDiretorio_Mostrar();
	void on_FrmCompararDiretorio_destroy(GtkWidget* widget, gpointer user_data);
	GtkLabel* FrmCompararDiretorio_getLabStatus1();
	GtkLabel* FrmCompararDiretorio_getLabStatus2();
	void FrmCompararDiretorio_ProgressoLog(Progresso progresso);

	void on_btnCompararDiretorios_clicked(GtkWidget* widget, gpointer user_data);
	void btnSalvarLog_clicked_cb(GtkWidget* widget, gpointer user_data);
	void on_cmbAba1_changed(GtkWidget* widget, gpointer user_data);
	void on_tvDiretorio1_row_collapsed(GtkTreeView *tree_view, GtkTreeIter *iter, GtkTreePath *path, gpointer user_data);
	void on_tvDiretorio1_row_expanded(GtkTreeView *tree_view, GtkTreeIter *iter, GtkTreePath *path, gpointer user_data);
	gboolean on_tvDiretorio1_button_release_event(GtkWidget *widget, GdkEvent *event, gpointer user_data);
	gboolean on_tvDiretorio1_button_press_event(GtkWidget *widget, GdkEvent *event, gpointer user_data);

	void on_cmbAba2_changed(GtkWidget* widget, gpointer user_data);
	void on_tvDiretorio2_row_collapsed(GtkTreeView *tree_view, GtkTreeIter *iter, GtkTreePath *path, gpointer user_data);
	void on_tvDiretorio2_row_expanded(GtkTreeView *tree_view, GtkTreeIter *iter, GtkTreePath *path, gpointer user_data);
	gboolean on_tvDiretorio2_button_release_event(GtkWidget *widget, GdkEvent *event, gpointer user_data);
	gboolean on_tvDiretorio2_button_press_event(GtkWidget *widget, GdkEvent *event, gpointer user_data);

	void on_tabelaCompara_row_activated(GtkTreeView *tree_view, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);
	gboolean on_tabelaCompara_button_release_event(GtkWidget *widget, GdkEvent *event, gpointer user_data);

	void FrmCompararDiretorio_CarregarDados();
	void FrmCompararDiretorio_LimparComparacao();
	GString* FrmCompararDiretorio_SQLCompara(Aba aba1, Aba aba2, const GString* caminho1,
		const GString* caminho2);
	void FrmCompararDiretorio_Comparar(const GString* sCaminhoDir1, const GString* sCaminhoDir2);

// ---------------------------------------------------------------------------
#endif
// ---------------------------------------------------------------------------
