#ifndef FrmSobre_H
#define FrmSobre_H
// ---------------------------------------------------------------------------
#include "resource.h"
// ---------------------------------------------------------------------------
struct SFrmSobre {
	GtkWidget *dialog_vbox1; 
	GtkWidget *vbox4; 
	GtkWidget *label; 
	GtkWidget *label8; 
	GtkWidget *label9; 
	GtkWidget *label10; 
	GtkWidget *dialog_action_area1; 
	GtkWidget *btbOk; 
	GdkTexture* splashImagem;

	GtkAboutDialog *frmSobre;
};
extern struct SFrmSobre FrmSobre;
// ---------------------------------------------------------------------------
	GtkAboutDialog* FrmSobre_Criar();
	void FrmSobre_Mostrar();

// ---------------------------------------------------------------------------
#endif
// ---------------------------------------------------------------------------
