#include "EscolhaArquivo.h"
#include "../comum/Rotinas.h"

void EscolhaArquivo_montaFiltro(GtkWidget* fcdialog, const gchar* filtro) {
	ListaString sl = Rotinas_SListSeparador(g_string_new(filtro), '|');
	GtkFileFilter *ffiltro = NULL;
	gboolean bAdiciona = TRUE;
	GString* item = g_string_new("");
	guint tamLista = ListaString_conta(sl);
	for (unsigned int i = 0; i < tamLista; i++) {
		item = ListaString_pesquisaItemOrd(sl, i);

		if (bAdiciona) {
			ffiltro = gtk_file_filter_new();
			gtk_file_filter_set_name(ffiltro, Rotinas_retUTF8(item->str));
			bAdiciona = FALSE;
		}
		else {
			gtk_file_filter_add_pattern(ffiltro, item->str);
			//gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(fcdialog), ffiltro);
			bAdiciona = TRUE;
		}
	}
}

GString* EscolhaArquivo_getTextoExtensao(const GString* extensao) {
	if (Rotinas_comparar(Rotinas_LowerCase(extensao),"txt")) return Rotinas_getRecurso("EscolhaArquivo.filtroTXT");
	if (Rotinas_comparar(Rotinas_LowerCase(extensao),"csv")) return Rotinas_getRecurso("EscolhaArquivo.filtroCSV");
	if (Rotinas_comparar(Rotinas_LowerCase(extensao),"html")) return Rotinas_getRecurso("EscolhaArquivo.filtroHTML");
	if (Rotinas_comparar(Rotinas_LowerCase(extensao),"xml")) return Rotinas_getRecurso("EscolhaArquivo.filtroXML");
	if (Rotinas_comparar(Rotinas_LowerCase(extensao),"sql")) return Rotinas_getRecurso("EscolhaArquivo.filtroSQL");
	if (Rotinas_comparar(Rotinas_LowerCase(extensao),"bmp")) return Rotinas_getRecurso("EscolhaArquivo.filtroBMP");
	if (Rotinas_comparar(Rotinas_LowerCase(extensao),"ico")) return Rotinas_getRecurso("EscolhaArquivo.filtroICO");
	if (Rotinas_comparar(Rotinas_LowerCase(extensao),"jpg")) return Rotinas_getRecurso("EscolhaArquivo.filtroJPG");
	if (Rotinas_comparar(Rotinas_LowerCase(extensao),"gif")) return Rotinas_getRecurso("EscolhaArquivo.filtroGIF");
	if (Rotinas_comparar(Rotinas_LowerCase(extensao),"png")) return Rotinas_getRecurso("EscolhaArquivo.filtroPNG");
	if (Rotinas_comparar(Rotinas_LowerCase(extensao),"tif")) return Rotinas_getRecurso("EscolhaArquivo.filtroTIF");
	return Rotinas_getRecurso("EscolhaArquivo.acceptAllFileFilterText");
}

GString* EscolhaArquivo_escolher(GtkWidget *pai, const gchar *filtro, const GString *titulo,
	GtkFileChooserAction acao, const gchar* textoAcao,
	const GString* diretorio, const GString* arquivo) {

	GString* sretorno = g_string_new("");

	GtkWidget* dialog = GTK_WIDGET(gtk_file_dialog_new());
	/*
	GtkWidget *dialog = gtk_file_dialog_new(Rotinas_retUTF8(titulo->str),
		GTK_WINDOW(pai),
		acao,
		"Cancelar", GTK_RESPONSE_CANCEL,
		textoAcao, GTK_RESPONSE_ACCEPT,
		NULL);
	*/
	//gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
	EscolhaArquivo_montaFiltro(dialog, filtro);
	//gtk_file_set_select_multiple(GTK_FILE_CHOOSER(dialog), FALSE);
	//gtk_file_dialog_set_filename(GTK_FILE_CHOOSER(dialog), arquivo->str);
	//gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), diretorio->str, NULL);
	//gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(dialog), TRUE);
	/*
	if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
	{
		if (acao == GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER)
			sretorno = g_string_new(gtk_file_dialog_get_initial_file(GTK_FILE_CHOOSER(dialog)));
		else
			sretorno = g_string_new(gtk_file_dialog_get_initial_folder(GTK_FILE_CHOOSER(dialog)));
	}
	//gtk_widget_destroy(dialog);
	*/
	return sretorno;
}

GString* EscolhaArquivo_abrirArquivo2(GtkWidget *pai, const gchar* filtro, const GString* diretorio, const GString* arquivo) {
	GString* sarquivo = g_string_new("");
	GString *titulo = Rotinas_getRecurso("EscolhaArquivo.openButtonText");

	sarquivo = EscolhaArquivo_escolher(pai, filtro, titulo, GTK_FILE_CHOOSER_ACTION_OPEN, "Abrir", diretorio, arquivo);

	return sarquivo;
}

GString* EscolhaArquivo_abrirArquivo(GtkWidget *pai, const gchar* filtro) {
	return EscolhaArquivo_abrirArquivo2(pai, filtro, g_string_new(""), g_string_new(""));
}

GString* EscolhaArquivo_salvarArquivo2(GtkWidget *pai, const gchar* filtro, const GString* diretorio, const GString* arquivo) {
	GString* sarquivo = g_string_new("");
	GString *titulo = Rotinas_getRecurso("EscolhaArquivo.saveButtonText");

	sarquivo = EscolhaArquivo_escolher(pai, filtro, titulo, GTK_FILE_CHOOSER_ACTION_SAVE, "Salvar", diretorio, arquivo);

	return sarquivo;
}

GString* EscolhaArquivo_salvarArquivo(GtkWidget *pai, const gchar* filtro) {
	return EscolhaArquivo_salvarArquivo2(pai, filtro, g_string_new(""), g_string_new(""));
}

GString* EscolhaArquivo_abrirDiretorio2(GtkWidget *pai, const GString* diretorio) {
	GString* sdiretorio = g_string_new("");
	GString *titulo = Rotinas_getRecurso("EscolhaArquivo.ApproveButtonText");

	sdiretorio = EscolhaArquivo_escolher(pai, EscolhaArquivo_FILTRO_TODOS_DIRETORIOS, titulo,
		GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER, "Selecionar", diretorio, g_string_new(""));

	return sdiretorio;
}

GString* EscolhaArquivo_abrirDiretorio(GtkWidget *pai) {
	GString* dir = g_string_new(g_get_current_dir());
	return EscolhaArquivo_abrirDiretorio2(pai, dir);
}

