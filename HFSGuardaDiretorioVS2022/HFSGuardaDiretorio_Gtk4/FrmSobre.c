#include "FrmSobre.h"
#include "hfsguardadir/comum/Rotinas.h"

struct SFrmSobre FrmSobre;
// ---------------------------------------------------------------------------
GtkAboutDialog* FrmSobre_Criar()
{
	#ifdef __GNUC__
		FrmSobre.splashImagem = Rotinas_XPMToPixbuf(XPM_SPLASH);
	#else
		FrmSobre.splashImagem = Rotinas_imagemToTexture("splash.gif");
	#endif // __GNUC__	

	FrmSobre.frmSobre = GTK_ABOUT_DIALOG(gtk_about_dialog_new());
	gtk_widget_set_name(GTK_WIDGET(FrmSobre.frmSobre), "frmSobre");
	gtk_widget_set_can_focus(GTK_WIDGET(FrmSobre.frmSobre), FALSE);
	gtk_window_set_title(GTK_WINDOW(FrmSobre.frmSobre), "Sobre o Catalogador");
	gtk_window_set_resizable(GTK_WINDOW(FrmSobre.frmSobre), FALSE);
	gtk_window_set_modal(GTK_WINDOW(FrmSobre.frmSobre), TRUE);
	//gtk_window_set_position(GTK_WINDOW(FrmSobre.frmSobre), GTK_WIN_POS_CENTER);
	gtk_window_set_destroy_with_parent(GTK_WINDOW(FrmSobre.frmSobre), TRUE);
	gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(FrmSobre.frmSobre), 
		Rotinas_retUTF8("HFSGuardaDir 2.0 - Catalogador de Diretórios"));
	gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(FrmSobre.frmSobre), Rotinas_retUTF8("Desenvolvido em C com GTK 4"));
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(FrmSobre.frmSobre), "Todos os direitos reservados, 2024");
	
	const char* autores[] = {
		"Henrique Figueiredo de Souza",
		NULL
	};

	gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(FrmSobre.frmSobre), autores);
	gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(FrmSobre.frmSobre), GDK_PAINTABLE(FrmSobre.splashImagem));
	gtk_about_dialog_set_license_type(GTK_ABOUT_DIALOG(FrmSobre.frmSobre), GTK_LICENSE_GPL_3_0);	

	return FrmSobre.frmSobre;
}
// ---------------------------------------------------------------------------
void FrmSobre_Mostrar() 
{
    FrmSobre.frmSobre = FrmSobre_Criar();
	//gtk_window_set_position (GTK_WINDOW(FrmSobre.frmSobre), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_present(GTK_WINDOW(FrmSobre.frmSobre));
}
