#include "Dialogo.h"
#include "hfsguardadir/comum/Rotinas.h"

gint Dialogo_MsgDlg(GtkWidget *pai, const gchar *sTitulo, 
	const gchar *sMensagem, GtkMessageType tipo, GtkButtonsType botoes) {
	GtkAlertDialog *dialog;
	dialog = gtk_alert_dialog_new("%s", Rotinas_retUTF8(sMensagem));
	//dialog = gtk_message_dialog_new(GTK_WINDOW(pai),
	//	GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT | GTK_DIALOG_MODAL, tipo, botoes,
	//	"%s", Rotinas_retUTF8(sMensagem));
	gtk_window_set_title(GTK_WINDOW(dialog), sTitulo);
	//gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
	
	//gtk_message_dialog_format_secondary_text();
	//gtk_message_dialog_format_secondary_markup():

	gint ret = 0;
	//gint ret = gtk_dialog_run(GTK_DIALOG(dialog));
	//gtk_widget_destroy(dialog);

	return ret;
}

void Dialogo_mensagemErro2(GtkWidget *pai, const char* recurso, const GString* texto) {
	//GString *log = g_string_new("");
	GString *msg, *titulo;

	msg = Rotinas_getRecurso(recurso);
	msg = Rotinas_concatenar1(msg, " ", texto->str);

	titulo = Rotinas_getRecurso("Dialogo.erro");
	
	Dialogo_MsgDlg(pai, titulo->str, msg->str, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK);

	//g_string_printf(log, "warning: %s\n", msg->str); 
	//OutputDebugString(log->str);
}

void Dialogo_mensagemErro(GtkWidget *pai, const char* recurso) {
	Dialogo_mensagemErro2(pai, recurso, g_string_new(""));
}

void Dialogo_mensagemInfo(GtkWidget *pai, const char* recurso) {
	//GString *log = g_string_new("");
	GString *msg, *titulo;

	msg = Rotinas_getRecurso(recurso);
	titulo = Rotinas_getRecurso("Dialogo.info");

	Dialogo_MsgDlg(pai, titulo->str, msg->str, GTK_MESSAGE_INFO, GTK_BUTTONS_OK);

	//g_string_printf(log, "info: %s\n", msg->str);
	//OutputDebugString(log->str);
}

gboolean Dialogo_confirma(GtkWidget *pai, const char* recurso) {
	GString *msg, *titulo;

	msg = Rotinas_getRecurso(recurso);
	titulo = Rotinas_getRecurso("Dialogo.confirma");

	return (Dialogo_MsgDlg(pai, titulo->str, msg->str,
		GTK_MESSAGE_QUESTION, GTK_BUTTONS_YES_NO) == GTK_RESPONSE_YES);
}

GString* Dialogo_entrada2(GtkWidget *pai, const char* recurso,
	const GString* valorInicial) {
	GString *titulo, *rotulo, *texto;

	GtkWidget *dialog;
	GtkWidget* btnOk;
	GtkWidget* btnCancel;
	GtkWidget* vbox;
	GtkWidget *hbox1;
	GtkWidget* hbox2;
	GtkWidget *imagem1;
	GtkWidget *local_entry1;
	GtkWidget *label;
	//gint response;

	texto = g_string_new("");
	titulo = Rotinas_getRecurso("Dialogo.entrada");
	rotulo = Rotinas_getRecurso(recurso);
	
	/*
	dialog = gtk_dialog_new_with_buttons(titulo->str,
		GTK_WINDOW(pai),
		GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
		"_OK",
		GTK_RESPONSE_OK,
		"_Cancelar",
		GTK_RESPONSE_CANCEL,
		NULL);
	*/
	dialog = gtk_window_new();
	gtk_widget_set_parent(GTK_WIDGET(dialog), pai);
	gtk_window_set_title(GTK_WINDOW(dialog), titulo->str);
	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
	gtk_window_set_destroy_with_parent(GTK_WINDOW(dialog), TRUE);
	gtk_window_set_default_size(GTK_WINDOW(dialog), 420, 80);
	//gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);

	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);

	hbox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 8);
	//gtk_container_set_border_width(GTK_CONTAINER(hbox1), 8);

	imagem1 = gtk_image_new_from_icon_name("dialog-question");
	//gtk_box_pack_start(GTK_BOX(hbox), imagem1, FALSE, FALSE, 0);
	gtk_box_append(GTK_BOX(hbox1), imagem1);

	label = gtk_label_new_with_mnemonic(rotulo->str);
	//gtk_box_pack_start(GTK_BOX(hbox), label, TRUE, TRUE, 0);
	gtk_box_append(GTK_BOX(hbox1), label);

	local_entry1 = gtk_entry_new();	
	//gtk_entry_set_text(GTK_ENTRY(local_entry1), valorInicial->str);
	//gtk_entry_set_max_width_chars(GTK_ENTRY(local_entry1), 30);
	gtk_entry_set_placeholder_text(GTK_ENTRY(local_entry1), "Informe um valor!");
	gtk_label_set_mnemonic_widget(GTK_LABEL(label), local_entry1);
	//gtk_box_pack_start(GTK_BOX(hbox), local_entry1, TRUE, TRUE, 0);
	gtk_box_append(GTK_BOX(hbox1), local_entry1);

	//GtkWidget* content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
	//gtk_container_add(GTK_CONTAINER(content_area), GTK_WIDGET(hbox));

	hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 8);
	//gtk_container_set_border_width(GTK_CONTAINER(hbox2), 8);

	btnOk = gtk_button_new_with_label("_OK");
	gtk_box_append(GTK_BOX(hbox2), GTK_WIDGET(btnOk));

	btnCancel = gtk_button_new_with_label("_Cancelar");
	gtk_box_append(GTK_BOX(hbox2), GTK_WIDGET(btnCancel));
	
	gtk_box_append(GTK_BOX(vbox), hbox1);
	gtk_box_append(GTK_BOX(vbox), hbox2);

	//gtk_widget_show(hbox1);
	//response = gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_window_present(GTK_WINDOW(dialog));

	/*
	if (response == GTK_RESPONSE_OK)
	{
		texto = g_string_new(gtk_entry_get_text(GTK_ENTRY(local_entry1)));
	}
	*/
	//gtk_widget_destroy(dialog);
	gtk_window_destroy(GTK_WINDOW(dialog));

	return texto;
}

GString* Dialogo_entrada(GtkWidget *pai, const char* recurso) {
	return Dialogo_entrada2(pai, recurso, g_string_new(""));
}
