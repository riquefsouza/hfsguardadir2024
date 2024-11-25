#include "FrmSobre.h"
#include "hfsguardadir/comum/Rotinas.h"

struct SFrmSobre FrmSobre;
// ---------------------------------------------------------------------------
GtkWidget *FrmSobre_Criar()
{
	/*
	FrmSobre.frmSobre = gtk_dialog_new();

	FrmSobre.btbOk = gtk_button_new();
	gtk_widget_set_name(GTK_WIDGET(FrmSobre.btbOk), "btbOk");
	gtk_button_set_label(GTK_BUTTON(FrmSobre.btbOk), "_Ok");
	gtk_widget_set_visible(FrmSobre.btbOk, TRUE);
	gtk_widget_set_can_focus(FrmSobre.btbOk, TRUE);
	gtk_widget_set_receives_default(FrmSobre.btbOk, TRUE);
	gtk_button_set_use_underline(GTK_BUTTON(FrmSobre.btbOk), TRUE);
	gtk_widget_set_margin_top(GTK_BUTTON(FrmSobre.btbOk), 10);
	
	FrmSobre.dialog_action_area1 = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_widget_set_name(GTK_WIDGET(FrmSobre.dialog_action_area1), "dialog_action_area1");
	gtk_widget_set_visible(FrmSobre.dialog_action_area1, TRUE);
	gtk_widget_set_can_focus(FrmSobre.dialog_action_area1, FALSE);
	gtk_button_box_set_layout(GTK_BUTTON_BOX(FrmSobre.dialog_action_area1), GTK_BUTTONBOX_CENTER);
	gtk_container_add(GTK_CONTAINER(FrmSobre.dialog_action_area1), FrmSobre.btbOk);
	gtk_box_set_child_packing(GTK_BOX(FrmSobre.dialog_action_area1), FrmSobre.btbOk, FALSE, FALSE, 0, GTK_PACK_START);
	
	FrmSobre.label10 = gtk_label_new("Todos os direitos reservados, 2024");
	gtk_widget_set_name(GTK_WIDGET(FrmSobre.label10), "label10");
	gtk_widget_set_visible(FrmSobre.label10, TRUE);
	gtk_widget_set_can_focus(FrmSobre.label10, FALSE);
	gtk_label_set_label(GTK_LABEL(FrmSobre.label10), "Todos os direitos reservados, 2024");
	
	FrmSobre.label9 = gtk_label_new("Por Henrique Figueiredo de Souza");
	gtk_widget_set_name(GTK_WIDGET(FrmSobre.label9), "label9");
	gtk_widget_set_visible(FrmSobre.label9, TRUE);
	gtk_widget_set_can_focus(FrmSobre.label9, FALSE);
	gtk_label_set_label(GTK_LABEL(FrmSobre.label9), "Por Henrique Figueiredo de Souza");
	
	FrmSobre.label8 = gtk_label_new("Desenvolvido em C com GTK, Versão: 2.0");
	gtk_widget_set_name(GTK_WIDGET(FrmSobre.label8), "label8");
	gtk_widget_set_visible(FrmSobre.label8, TRUE);
	gtk_widget_set_can_focus(FrmSobre.label8, FALSE);
	gtk_label_set_label(GTK_LABEL(FrmSobre.label8), Rotinas_retUTF8("Desenvolvido em C com GTK, Versão: 3.0"));
	
	FrmSobre.label = gtk_label_new("HFSGuardaDir 2.0 - Catalogador de Diretórios");
	gtk_widget_set_name(GTK_WIDGET(FrmSobre.label), "label");
	gtk_widget_set_visible(FrmSobre.label, TRUE);
	gtk_widget_set_can_focus(FrmSobre.label, FALSE);
	gtk_label_set_label(GTK_LABEL(FrmSobre.label), Rotinas_retUTF8("HFSGuardaDir 2.0 - Catalogador de Diretórios"));
	
	FrmSobre.vbox4 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_name(GTK_WIDGET(FrmSobre.vbox4), "vbox4");
	gtk_widget_set_visible(FrmSobre.vbox4, TRUE);
	gtk_widget_set_can_focus(FrmSobre.vbox4, FALSE);
	gtk_container_add(GTK_CONTAINER(FrmSobre.vbox4), FrmSobre.label);
	gtk_box_set_child_packing(GTK_BOX(FrmSobre.vbox4), FrmSobre.label, FALSE, TRUE, 0, GTK_PACK_START);
	gtk_container_add(GTK_CONTAINER(FrmSobre.vbox4), FrmSobre.label8);
	gtk_box_set_child_packing(GTK_BOX(FrmSobre.vbox4), FrmSobre.label8, FALSE, TRUE, 0, GTK_PACK_START);
	gtk_container_add(GTK_CONTAINER(FrmSobre.vbox4), FrmSobre.label9);
	gtk_box_set_child_packing(GTK_BOX(FrmSobre.vbox4), FrmSobre.label9, FALSE, TRUE, 0, GTK_PACK_START);
	gtk_container_add(GTK_CONTAINER(FrmSobre.vbox4), FrmSobre.label10);
	gtk_box_set_child_packing(GTK_BOX(FrmSobre.vbox4), FrmSobre.label10, FALSE, TRUE, 0, GTK_PACK_START);
	
	FrmSobre.dialog_vbox1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
	gtk_widget_set_name(GTK_WIDGET(FrmSobre.dialog_vbox1), "dialog_vbox1");
	gtk_widget_set_visible(FrmSobre.dialog_vbox1, TRUE);
	gtk_widget_set_can_focus(FrmSobre.dialog_vbox1, FALSE);
	gtk_box_set_spacing(GTK_BOX(FrmSobre.dialog_vbox1), 2);
	gtk_container_add(GTK_CONTAINER(FrmSobre.dialog_vbox1), FrmSobre.vbox4);
	gtk_box_set_child_packing(GTK_BOX(FrmSobre.dialog_vbox1), FrmSobre.vbox4, TRUE, TRUE, 0, GTK_PACK_START);
	gtk_container_add(GTK_CONTAINER(FrmSobre.dialog_vbox1), FrmSobre.dialog_action_area1);
	gtk_box_set_child_packing(GTK_BOX(FrmSobre.dialog_vbox1), FrmSobre.dialog_action_area1, FALSE, TRUE, 0, GTK_PACK_START);
	
	gtk_widget_set_name(FrmSobre.frmSobre, "frmSobre");
	gtk_widget_set_can_focus(FrmSobre.frmSobre, FALSE);
	gtk_container_set_border_width(GTK_CONTAINER(FrmSobre.frmSobre), 5);
	gtk_window_set_title(GTK_WINDOW(FrmSobre.frmSobre), "Sobre o Catalogador");
	gtk_window_set_resizable(GTK_WINDOW(FrmSobre.frmSobre), FALSE);
	gtk_window_set_modal(GTK_WINDOW(FrmSobre.frmSobre), TRUE);
	gtk_window_set_position(GTK_WINDOW(FrmSobre.frmSobre), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(FrmSobre.frmSobre), 300, 150);
	gtk_window_set_type_hint(GTK_WINDOW(FrmSobre.frmSobre), GDK_WINDOW_TYPE_HINT_DIALOG);
	GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(FrmSobre.frmSobre));
	gtk_container_add(GTK_CONTAINER(content_area), GTK_WIDGET(FrmSobre.dialog_vbox1));
	*/

	#ifdef __GNUC__
		FrmSobre.splashImagem = Rotinas_XPMToPixbuf(XPM_SPLASH);
	#else
		FrmSobre.splashImagem = Rotinas_imagemToPixbuf("splash.gif");
	#endif // __GNUC__	

	FrmSobre.frmSobre = gtk_about_dialog_new();
	gtk_widget_set_name(FrmSobre.frmSobre, "frmSobre");
	gtk_widget_set_can_focus(FrmSobre.frmSobre, FALSE);
	gtk_window_set_title(GTK_WINDOW(FrmSobre.frmSobre), "Sobre o Catalogador");
	//gtk_window_set_resizable(GTK_WINDOW(FrmSobre.frmSobre), FALSE);
	gtk_window_set_modal(GTK_WINDOW(FrmSobre.frmSobre), TRUE);
	gtk_window_set_position(GTK_WINDOW(FrmSobre.frmSobre), GTK_WIN_POS_CENTER);
	gtk_window_set_destroy_with_parent(GTK_WINDOW(FrmSobre.frmSobre), TRUE);
	gtk_window_set_type_hint(GTK_WINDOW(FrmSobre.frmSobre), GDK_WINDOW_TYPE_HINT_DIALOG);
	gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(FrmSobre.frmSobre), 
		Rotinas_retUTF8("HFSGuardaDir 2.0 - Catalogador de Diretórios"));
	gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(FrmSobre.frmSobre), Rotinas_retUTF8("Desenvolvido em C com GTK 3"));
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(FrmSobre.frmSobre), "Todos os direitos reservados, 2024");
	
	const char* autores[] = {
		"Henrique Figueiredo de Souza",
		NULL
	};

	gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(FrmSobre.frmSobre), autores);
	gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(FrmSobre.frmSobre), FrmSobre.splashImagem);
	gtk_about_dialog_set_license_type(GTK_ABOUT_DIALOG(FrmSobre.frmSobre), GTK_LICENSE_GPL_3_0);

	GtkWidget* action_area = gtk_dialog_get_action_area(GTK_DIALOG(FrmSobre.frmSobre));
	GList* lista = gtk_container_get_children(GTK_CONTAINER(action_area));
	GtkButtonBox* bbox = g_list_nth_data(lista, 0);
	
	GList* lista2 = gtk_container_get_children(GTK_CONTAINER(bbox));
	FrmSobre.btbOk = g_list_nth_data(lista2, 0);

	g_signal_connect(FrmSobre.btbOk, "clicked", G_CALLBACK(on_btbOk_clicked), NULL); 
			
	g_signal_connect(FrmSobre.frmSobre, "destroy", G_CALLBACK (on_FrmSobre_destroy), NULL);

	return FrmSobre.frmSobre;
}
// ---------------------------------------------------------------------------
void FrmSobre_Mostrar() 
{
    FrmSobre.frmSobre = FrmSobre_Criar();
	gtk_window_set_position (GTK_WINDOW(FrmSobre.frmSobre), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_dialog_run(GTK_DIALOG (FrmSobre.frmSobre));
	gtk_widget_destroy(FrmSobre.frmSobre);
}
// ---------------------------------------------------------------------------
void on_FrmSobre_destroy(GtkWidget* widget, gpointer user_data) {
	
}
// ---------------------------------------------------------------------------
void on_btbOk_clicked(GtkWidget* widget, gpointer user_data){
	gtk_widget_destroy(FrmSobre.frmSobre);
}


// ---------------------------------------------------------------------------
