#include "FrmImportarDiretorio.h"
#include "hfsguardadir/catalogador/Catalogador.h"
#include "hfsguardadir/objetosbo/ImportarBO.h"
#include "hfsguardadir/objetosbo/DiretorioBO.h"
#include "hfsguardadir/objetosgui/Dialogo.h"

struct SFrmImportarDiretorio FrmImportarDiretorio;
// ---------------------------------------------------------------------------
GtkWidget *FrmImportarDiretorio_Criar()
{
	FrmImportarDiretorio.frmImportarDiretorio = gtk_window_new(GTK_WINDOW_TOPLEVEL);;

	FrmImportarDiretorio.barraStatus2 = gtk_statusbar_new();
	gtk_widget_set_name(GTK_WIDGET(FrmImportarDiretorio.barraStatus2), "barraStatus2");
	gtk_widget_set_visible(FrmImportarDiretorio.barraStatus2, TRUE);
	gtk_widget_set_can_focus(FrmImportarDiretorio.barraStatus2, FALSE);
	gtk_box_set_spacing(GTK_BOX(FrmImportarDiretorio.barraStatus2), 2);
	
	FrmImportarDiretorio.barraStatus1 = gtk_statusbar_new();
	gtk_widget_set_name(GTK_WIDGET(FrmImportarDiretorio.barraStatus1), "barraStatus1");
	gtk_widget_set_visible(FrmImportarDiretorio.barraStatus1, TRUE);
	gtk_widget_set_can_focus(FrmImportarDiretorio.barraStatus1, FALSE);
	gtk_box_set_spacing(GTK_BOX(FrmImportarDiretorio.barraStatus1), 2);
	//gtk_statusbar_set_has_resize_grip(GTK_STATUSBAR(FrmImportarDiretorio.barraStatus1), FALSE);
	
	FrmImportarDiretorio.hbox3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_widget_set_name(GTK_WIDGET(FrmImportarDiretorio.hbox3), "hbox3");
	gtk_widget_set_visible(FrmImportarDiretorio.hbox3, TRUE);
	gtk_widget_set_can_focus(FrmImportarDiretorio.hbox3, FALSE);
	gtk_container_add(GTK_CONTAINER(FrmImportarDiretorio.hbox3), FrmImportarDiretorio.barraStatus1);
	gtk_box_set_child_packing(GTK_BOX(FrmImportarDiretorio.hbox3), FrmImportarDiretorio.barraStatus1, FALSE, TRUE, 0, GTK_PACK_START);
	gtk_container_add(GTK_CONTAINER(FrmImportarDiretorio.hbox3), FrmImportarDiretorio.barraStatus2);
	gtk_box_set_child_packing(GTK_BOX(FrmImportarDiretorio.hbox3), FrmImportarDiretorio.barraStatus2, TRUE, TRUE, 0, GTK_PACK_START);
	
	FrmImportarDiretorio.pbImportar = gtk_progress_bar_new();
	gtk_widget_set_name(GTK_WIDGET(FrmImportarDiretorio.pbImportar), "pbImportar");
	gtk_widget_set_visible(FrmImportarDiretorio.pbImportar, TRUE);
	gtk_widget_set_can_focus(FrmImportarDiretorio.pbImportar, FALSE);
	
	FrmImportarDiretorio.memoImportaDir = gtk_text_view_new();
	gtk_widget_set_name(GTK_WIDGET(FrmImportarDiretorio.memoImportaDir), "memoImportaDir");
	gtk_widget_set_visible(FrmImportarDiretorio.memoImportaDir, TRUE);
	gtk_widget_set_can_focus(FrmImportarDiretorio.memoImportaDir, TRUE);
	
	FrmImportarDiretorio.scrollMemo = gtk_scrolled_window_new(NULL, NULL);
	gtk_widget_set_name(GTK_WIDGET(FrmImportarDiretorio.scrollMemo), "scrollMemo");
	gtk_widget_set_visible(FrmImportarDiretorio.scrollMemo, TRUE);
	gtk_widget_set_can_focus(FrmImportarDiretorio.scrollMemo, TRUE);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(FrmImportarDiretorio.scrollMemo), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_container_add(GTK_CONTAINER(FrmImportarDiretorio.scrollMemo), FrmImportarDiretorio.memoImportaDir);
	
	FrmImportarDiretorio.form_vbox1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_name(GTK_WIDGET(FrmImportarDiretorio.form_vbox1), "form_vbox1");
	gtk_widget_set_visible(FrmImportarDiretorio.form_vbox1, TRUE);
	gtk_widget_set_can_focus(FrmImportarDiretorio.form_vbox1, FALSE);
	gtk_container_add(GTK_CONTAINER(FrmImportarDiretorio.form_vbox1), FrmImportarDiretorio.scrollMemo);
	gtk_box_set_child_packing(GTK_BOX(FrmImportarDiretorio.form_vbox1), FrmImportarDiretorio.scrollMemo, TRUE, TRUE, 0, GTK_PACK_START);
	gtk_container_add(GTK_CONTAINER(FrmImportarDiretorio.form_vbox1), FrmImportarDiretorio.pbImportar);
	gtk_box_set_child_packing(GTK_BOX(FrmImportarDiretorio.form_vbox1), FrmImportarDiretorio.pbImportar, FALSE, TRUE, 0, GTK_PACK_START);
	gtk_container_add(GTK_CONTAINER(FrmImportarDiretorio.form_vbox1), FrmImportarDiretorio.hbox3);
	gtk_box_set_child_packing(GTK_BOX(FrmImportarDiretorio.form_vbox1), FrmImportarDiretorio.hbox3, FALSE, TRUE, 0, GTK_PACK_START);
	
	gtk_widget_set_name(FrmImportarDiretorio.frmImportarDiretorio, "frmImportarDiretorio");
	gtk_widget_set_size_request(FrmImportarDiretorio.frmImportarDiretorio, 895, 572);
	gtk_widget_set_visible(FrmImportarDiretorio.frmImportarDiretorio, TRUE);
	gtk_widget_set_can_focus(FrmImportarDiretorio.frmImportarDiretorio, FALSE);
	gtk_window_set_title(GTK_WINDOW(FrmImportarDiretorio.frmImportarDiretorio), "Importando Diretório");
	gtk_window_set_resizable(GTK_WINDOW(FrmImportarDiretorio.frmImportarDiretorio), FALSE);
	gtk_window_set_modal(GTK_WINDOW(FrmImportarDiretorio.frmImportarDiretorio), TRUE);
	gtk_window_set_position(GTK_WINDOW(FrmImportarDiretorio.frmImportarDiretorio), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(FrmImportarDiretorio.frmImportarDiretorio), 895, 572);
	gtk_window_set_decorated(GTK_WINDOW(FrmImportarDiretorio.frmImportarDiretorio), FALSE);
	gtk_container_add(GTK_CONTAINER(FrmImportarDiretorio.frmImportarDiretorio), GTK_WIDGET(FrmImportarDiretorio.form_vbox1));
			
	g_signal_connect ((gpointer) FrmImportarDiretorio.frmImportarDiretorio, "destroy", 
		G_CALLBACK (on_FrmImportarDiretorio_destroy), NULL);


	gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(FrmImportarDiretorio.memoImportaDir), FALSE);
	gtk_widget_get_size_request(GTK_WIDGET(FrmImportarDiretorio.barraStatus1), 
		&FrmImportarDiretorio.nLargura, &FrmImportarDiretorio.nAltura);
	gtk_widget_set_size_request(GTK_WIDGET(FrmImportarDiretorio.barraStatus1), 
		180, FrmImportarDiretorio.nAltura);
	gtk_label_set_text(FrmImportarDiretorio_getLabStatus1(), 
		Rotinas_getRecurso("FrmCompararDiretorio.barraStatus1")->str);

	FrmImportarDiretorio.listaImportar = ListaImportar_inicia();
	
	return FrmImportarDiretorio.frmImportarDiretorio;
}
// ---------------------------------------------------------------------------
void FrmImportarDiretorio_Mostrar() 
{    
	gtk_window_set_position (GTK_WINDOW(FrmImportarDiretorio.frmImportarDiretorio), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_widget_show(FrmImportarDiretorio.frmImportarDiretorio);
}

void FrmImportarDiretorio_Fechar()
{
	gtk_widget_hide(FrmImportarDiretorio.frmImportarDiretorio);
	gtk_widget_destroy(FrmImportarDiretorio.frmImportarDiretorio);
}

void on_FrmImportarDiretorio_destroy(GtkWidget* widget, gpointer user_data) {
	
}

GtkLabel* FrmImportarDiretorio_getLabStatus1() {
	GList* lista = gtk_container_get_children(GTK_CONTAINER(FrmImportarDiretorio.barraStatus1));
	GtkFrame* frameStatus1 = g_list_nth_data(lista, 0);

	lista = gtk_container_get_children(GTK_CONTAINER(frameStatus1));
	GtkHBox* hboxStatus1 = g_list_nth_data(lista, 0);

	lista = gtk_container_get_children(GTK_CONTAINER(hboxStatus1));
	GtkLabel* labStatus1 = g_list_nth_data(lista, 0);

	return labStatus1;
}

GtkLabel* FrmImportarDiretorio_getLabStatus2() {
	GList* lista = gtk_container_get_children(GTK_CONTAINER(FrmImportarDiretorio.barraStatus2));
	GtkFrame* frameStatus2 = g_list_nth_data(lista, 0);

	lista = gtk_container_get_children(GTK_CONTAINER(frameStatus2));
	GtkHBox* hboxStatus2 = g_list_nth_data(lista, 0);

	lista = gtk_container_get_children(GTK_CONTAINER(hboxStatus2));
	GtkLabel* labStatus2 = g_list_nth_data(lista, 0);

	return labStatus2;
}

void FrmImportarDiretorio_ProgressoLog(Progresso progresso)
{
	GtkTextBuffer* buffer;
	GtkTextIter titer;
	gint pos;
	GString* texto = g_string_new("");

	if (FrmImportarDiretorio.frmImportarDiretorio != NULL) {
		if (progresso.posicao == 0) {
			gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(FrmImportarDiretorio.pbImportar), progresso.minimo);
			gtk_progress_bar_set_pulse_step(GTK_PROGRESS_BAR(FrmImportarDiretorio.pbImportar), 0.1); //progresso.passo
		}
		if (progresso.maximo > 0) {
			gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(FrmImportarDiretorio.pbImportar),
				Rotinas_calculaProgresso(progresso.maximo, progresso.posicao));
		}

		if (progresso.log->len > 0) {
			buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(FrmImportarDiretorio.memoImportaDir));
			pos = gtk_text_buffer_get_line_count(buffer);
			gtk_text_buffer_get_iter_at_line(buffer, &titer, pos);
			texto = g_string_append(progresso.log, "\n");
			gtk_text_buffer_insert(buffer, &titer, texto->str, (gint)texto->len);
			gtk_text_view_set_buffer(GTK_TEXT_VIEW(FrmImportarDiretorio.memoImportaDir), buffer);		
			gtk_text_view_scroll_to_iter(GTK_TEXT_VIEW(FrmImportarDiretorio.memoImportaDir), &titer, 0, FALSE, 0, 0);
			gtk_label_set_text(FrmImportarDiretorio_getLabStatus2(), Rotinas_IntToStr(pos)->str);
		}

		while (gtk_events_pending()) {
			gtk_main_iteration();
		}

	}
}

void FrmImportarDiretorio_Importar()
{
	GtkTextBuffer* buffer;
	GtkTextIter titer;
	gint nlinhas;
	GString* sLog;
	gchar* texto;
	Importar importar = Importar_new();
	guint tamlista = ListaImportar_conta(FrmImportarDiretorio.listaImportar);
	
	for (unsigned int i = 0; i < tamlista; i++) {
		importar = ListaImportar_pesquisaItemOrd(FrmImportarDiretorio.listaImportar, i);

		Catalogador.diretorioOrdem->ordem = 1;

		if (!FrmImportarDiretorio.bSubDiretorio) {
			Catalogador_SetCursor(GDK_WATCH);

			ImportarBO_ImportacaoCompleta(importar,
				&Catalogador.diretorioOrdem, Catalogador.listaExtensoes,
				FrmImportarDiretorio_ProgressoLog);

			Catalogador_SetCursor(GDK_ARROW);
		}
		else {
			if (!DiretorioBO_verificaCodDir(importar->aba,
				importar->rotuloRaiz, Catalogador.listaDiretorioPai)) {
				Catalogador_SetCursor(GDK_WATCH);

				ImportarBO_ImportacaoCompleta(importar,
					&Catalogador.diretorioOrdem, Catalogador.listaExtensoes,
					FrmImportarDiretorio_ProgressoLog);

				Catalogador_SetCursor(GDK_ARROW);
			}
			else {
				Dialogo_mensagemInfo(FrmImportarDiretorio.frmImportarDiretorio,
					"FrmImportarDiretorio.DiretorioExisteCatalogo");
			}
		}
	}
		
	if (gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(FrmPrincipal.menuGravarLogImportacao))) {
		buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(FrmImportarDiretorio.memoImportaDir));
		nlinhas = gtk_text_buffer_get_line_count(buffer);
		if (nlinhas > 0) {
			sLog = Rotinas_concatenar2(Rotinas_AppDirPath(),
				Rotinas_formataDate(Rotinas_FORMATO_DHARQUIVO, Rotinas_DataHoraNow()),
				"_Importacao.log");

			ListaString log = ListaString_inicia();
			
			for (int nlinha = 0; nlinha < nlinhas; nlinha++) {

				gtk_text_buffer_get_iter_at_line(buffer, &titer, nlinha);
				texto = gtk_text_buffer_get_text(buffer, &titer, &titer, FALSE);

				log = ListaString_insere(log, g_string_new(texto), nlinha);
			}

			Rotinas_SListSaveToFile(log, sLog);
		}
	}

}

	
