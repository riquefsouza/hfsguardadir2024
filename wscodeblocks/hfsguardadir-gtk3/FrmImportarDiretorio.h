#ifndef FrmImportarDiretorio_H
#define FrmImportarDiretorio_H
// ---------------------------------------------------------------------------
#include "resource.h"
#include "hfsguardadir/objetos/Diretorio.h"
#include "hfsguardadir/objetos/Importar.h"
#include "hfsguardadir/comum/Rotinas.h"
// ---------------------------------------------------------------------------
struct SFrmImportarDiretorio {
	GtkWidget *form_vbox1;
	GtkWidget *scrollMemo;
	GtkWidget *memoImportaDir;
	GtkWidget *pbImportar;
	GtkWidget *hbox3;
	GtkWidget *barraStatus1;
	GtkWidget *barraStatus2;

	gboolean bSubDiretorio;
	ListaImportar listaImportar;
	ListaDiretorio listaDiretorio;
	gint nLargura;
	gint nAltura;

	GtkWidget *frmImportarDiretorio;
};
extern struct SFrmImportarDiretorio FrmImportarDiretorio;
// ---------------------------------------------------------------------------
	GtkWidget *FrmImportarDiretorio_Criar();
	void FrmImportarDiretorio_Mostrar();
	void FrmImportarDiretorio_Fechar();
	void on_FrmImportarDiretorio_destroy(GtkWidget* widget, gpointer user_data);

	GtkLabel* FrmImportarDiretorio_getLabStatus1();
	GtkLabel* FrmImportarDiretorio_getLabStatus2();
	void FrmImportarDiretorio_ProgressoLog(Progresso progresso);
	void FrmImportarDiretorio_Importar();
// ---------------------------------------------------------------------------
#endif
// ---------------------------------------------------------------------------
