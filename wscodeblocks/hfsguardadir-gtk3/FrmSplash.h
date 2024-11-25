#ifndef FrmSplash_H
#define FrmSplash_H
// ---------------------------------------------------------------------------
#include "hfsguardadir/comum/Rotinas.h"
// ---------------------------------------------------------------------------
struct SFrmSplash {
	GtkWidget *vbox2;
	//GtkWidget *label4;
	//GtkWidget *label5;
	GtkWidget *pb1;
	GtkWidget *splashImagem;
	GtkWidget *frmSplash;
};
extern struct SFrmSplash FrmSplash;
// ---------------------------------------------------------------------------
	GtkWidget *FrmSplash_Criar();
	void FrmSplash_Mostrar();
	void FrmSplash_Fechar();
	void on_FrmSplash_destroy(GtkWidget* widget, gpointer user_data);
	void FrmSplash_ProgressoLog(Progresso progresso);

// ---------------------------------------------------------------------------
#endif
// ---------------------------------------------------------------------------
