#include "FrmSplash.h"

struct SFrmSplash FrmSplash;
// ---------------------------------------------------------------------------
GtkWidget *FrmSplash_Criar()
{
	FrmSplash.frmSplash = gtk_window_new();

	FrmSplash.pb1 = gtk_progress_bar_new();
	gtk_widget_set_name(GTK_WIDGET(FrmSplash.pb1), "pb1");
	gtk_widget_set_visible(FrmSplash.pb1, TRUE);
	gtk_widget_set_can_focus(FrmSplash.pb1, FALSE);
	gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(FrmSplash.pb1), TRUE);
	
	FrmSplash.vbox2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
	gtk_widget_set_name(GTK_WIDGET(FrmSplash.vbox2), "vbox2");
	gtk_widget_set_visible(FrmSplash.vbox2, TRUE);
	gtk_widget_set_can_focus(FrmSplash.vbox2, FALSE);
	gtk_box_set_spacing(GTK_BOX(FrmSplash.vbox2), 6);
	//gtk_container_set_border_width(GTK_CONTAINER(FrmSplash.vbox2), 1);
	
	#ifdef __GNUC__
		FrmSplash.splashImagem = gtk_image_new_from_paintable(GDK_PAINTABLE(Rotinas_XPMToTexture(XPM_SPLASH)));
	#else
		FrmSplash.splashImagem = gtk_image_new_from_paintable(GDK_PAINTABLE(Rotinas_imagemToTexture("splash.gif")));
	#endif // __GNUC__	

	gtk_box_append(GTK_BOX(FrmSplash.vbox2), FrmSplash.splashImagem);
	gtk_widget_set_hexpand(GTK_WIDGET(FrmSplash.vbox2), TRUE);

	gtk_box_append(GTK_BOX(FrmSplash.vbox2), FrmSplash.pb1);
	gtk_widget_set_hexpand(GTK_WIDGET(FrmSplash.pb1), TRUE);
	gtk_widget_set_vexpand(GTK_WIDGET(FrmSplash.pb1), TRUE);
	
	gtk_widget_set_name(FrmSplash.frmSplash, "frmSplash");
	gtk_widget_set_size_request(FrmSplash.frmSplash, 375, 113);
	gtk_widget_set_visible(FrmSplash.frmSplash, TRUE);
	gtk_widget_set_can_focus(FrmSplash.frmSplash, FALSE);
	gtk_window_set_modal(GTK_WINDOW(FrmSplash.frmSplash), TRUE);
	gtk_window_set_resizable(GTK_WINDOW(FrmSplash.frmSplash), FALSE);
	//gtk_window_set_position(GTK_WINDOW(FrmSplash.frmSplash), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_default_size(GTK_WINDOW(FrmSplash.frmSplash), 375, 113);
	gtk_window_set_decorated(GTK_WINDOW(FrmSplash.frmSplash), FALSE);
	gtk_window_set_child(GTK_WINDOW(FrmSplash.frmSplash), GTK_WIDGET(FrmSplash.vbox2));
	
	g_signal_connect (FrmSplash.frmSplash, "destroy", G_CALLBACK (on_FrmSplash_destroy), NULL);

	return FrmSplash.frmSplash;
}
// ---------------------------------------------------------------------------
void FrmSplash_Mostrar() 
{
    FrmSplash.frmSplash = FrmSplash_Criar();
	//gtk_window_set_position (GTK_WINDOW(FrmSplash.frmSplash), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_present(GTK_WINDOW(FrmSplash.frmSplash));
}

void FrmSplash_Fechar()
{
	gtk_widget_set_visible(FrmSplash.frmSplash, FALSE);
	//gtk_widget_destroy(FrmSplash.frmSplash);
}

void FrmSplash_ProgressoLog(Progresso progresso)
{
	if (FrmSplash.frmSplash != NULL) {
		if (progresso.posicao == 0) {
			gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(FrmSplash.pb1), progresso.minimo);
			gtk_progress_bar_set_pulse_step(GTK_PROGRESS_BAR(FrmSplash.pb1), 0.1); //progresso.passo
		}
		gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(FrmSplash.pb1),
			Rotinas_calculaProgresso(progresso.maximo, progresso.posicao));

		//while (gtk_events_pending()) {gtk_main_iteration();}
	}

}

void on_FrmSplash_destroy(GtkWidget* widget, gpointer user_data) {
	
}

// ---------------------------------------------------------------------------
