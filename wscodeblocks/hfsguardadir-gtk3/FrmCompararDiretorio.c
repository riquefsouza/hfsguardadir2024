#include "FrmCompararDiretorio.h"
#include "hfsguardadir/catalogador/Catalogador.h"
#include "hfsguardadir/objetosbo/AbaBO.h"
#include "hfsguardadir/objetosbo/DiretorioBO.h"
#include "hfsguardadir/objetosgui/Dialogo.h"

struct SFrmCompararDiretorio FrmCompararDiretorio;
// ---------------------------------------------------------------------------
GtkWidget *FrmCompararDiretorio_Criar()
{
	FrmCompararDiretorio.frmCompararDiretorio = gtk_window_new(GTK_WINDOW_TOPLEVEL);;

	FrmCompararDiretorio.barraStatus21 = gtk_statusbar_new();
	gtk_widget_set_name(GTK_WIDGET(FrmCompararDiretorio.barraStatus21), "barraStatus21");
	gtk_widget_set_visible(FrmCompararDiretorio.barraStatus21, TRUE);
	gtk_widget_set_can_focus(FrmCompararDiretorio.barraStatus21, FALSE);
	gtk_box_set_spacing(GTK_BOX(FrmCompararDiretorio.barraStatus21), 2);

	FrmCompararDiretorio.barraStatus11 = gtk_statusbar_new();
	gtk_widget_set_name(GTK_WIDGET(FrmCompararDiretorio.barraStatus11), "barraStatus11");
	gtk_widget_set_size_request(FrmCompararDiretorio.barraStatus11, 200, -1);
	gtk_widget_set_visible(FrmCompararDiretorio.barraStatus11, TRUE);
	gtk_widget_set_can_focus(FrmCompararDiretorio.barraStatus11, FALSE);
	gtk_box_set_spacing(GTK_BOX(FrmCompararDiretorio.barraStatus11), 2);

	FrmCompararDiretorio.hbox5 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_widget_set_name(GTK_WIDGET(FrmCompararDiretorio.hbox5), "hbox5");
	gtk_widget_set_visible(FrmCompararDiretorio.hbox5, TRUE);
	gtk_widget_set_can_focus(FrmCompararDiretorio.hbox5, FALSE);
	gtk_container_add(GTK_CONTAINER(FrmCompararDiretorio.hbox5), FrmCompararDiretorio.barraStatus11);
	gtk_box_set_child_packing(GTK_BOX(FrmCompararDiretorio.hbox5), FrmCompararDiretorio.barraStatus11, FALSE, TRUE, 0, GTK_PACK_START);
	gtk_container_add(GTK_CONTAINER(FrmCompararDiretorio.hbox5), FrmCompararDiretorio.barraStatus21);
	gtk_box_set_child_packing(GTK_BOX(FrmCompararDiretorio.hbox5), FrmCompararDiretorio.barraStatus21, TRUE, TRUE, 0, GTK_PACK_START);

	FrmCompararDiretorio.tabelaCompara = gtk_tree_view_new();
	gtk_widget_set_name(GTK_WIDGET(FrmCompararDiretorio.tabelaCompara), "tabelaCompara");
	gtk_widget_set_visible(FrmCompararDiretorio.tabelaCompara, TRUE);
	gtk_widget_set_can_focus(FrmCompararDiretorio.tabelaCompara, TRUE);

	FrmCompararDiretorio.scrollCompara = gtk_scrolled_window_new(NULL, NULL);
	gtk_widget_set_name(GTK_WIDGET(FrmCompararDiretorio.scrollCompara), "scrollTabelaCompara");
	gtk_widget_set_visible(FrmCompararDiretorio.scrollCompara, TRUE);
	gtk_widget_set_can_focus(FrmCompararDiretorio.scrollCompara, TRUE);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(FrmCompararDiretorio.scrollCompara), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(FrmCompararDiretorio.scrollCompara), GTK_SHADOW_ETCHED_OUT);
	gtk_container_add(GTK_CONTAINER(FrmCompararDiretorio.scrollCompara), FrmCompararDiretorio.tabelaCompara);

	Tabela_cria(TRUE, GTK_TREE_VIEW(FrmCompararDiretorio.tabelaCompara));

	FrmCompararDiretorio.labDiferencasEncontradas = gtk_label_new(Rotinas_retUTF8("Diferenças Encontradas"));
	gtk_widget_set_name(GTK_WIDGET(FrmCompararDiretorio.labDiferencasEncontradas), "labDiferencasEncontradas");
	gtk_widget_set_visible(FrmCompararDiretorio.labDiferencasEncontradas, TRUE);
	gtk_widget_set_can_focus(FrmCompararDiretorio.labDiferencasEncontradas, FALSE);
	gtk_label_set_label(GTK_LABEL(FrmCompararDiretorio.labDiferencasEncontradas), Rotinas_retUTF8("Diferenças Encontradas"));

	FrmCompararDiretorio.hbox4 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_widget_set_name(GTK_WIDGET(FrmCompararDiretorio.hbox4), "hbox4");
	gtk_widget_set_visible(FrmCompararDiretorio.hbox4, TRUE);
	gtk_widget_set_can_focus(FrmCompararDiretorio.hbox4, FALSE);
	gtk_container_add(GTK_CONTAINER(FrmCompararDiretorio.hbox4), FrmCompararDiretorio.labDiferencasEncontradas);
	gtk_box_set_child_packing(GTK_BOX(FrmCompararDiretorio.hbox4), FrmCompararDiretorio.labDiferencasEncontradas, FALSE, TRUE, 0, GTK_PACK_START);

	FrmCompararDiretorio.label6 = gtk_label_new(Rotinas_retUTF8("<b>Diretório 2</b>"));
	gtk_widget_set_name(GTK_WIDGET(FrmCompararDiretorio.label6), "label6");
	gtk_widget_set_visible(FrmCompararDiretorio.label6, TRUE);
	gtk_widget_set_can_focus(FrmCompararDiretorio.label6, FALSE);
	gtk_label_set_label(GTK_LABEL(FrmCompararDiretorio.label6), Rotinas_retUTF8("<b>Diretório 2</b>"));
	gtk_label_set_use_markup(GTK_LABEL(FrmCompararDiretorio.label6), TRUE);

	FrmCompararDiretorio.tvDiretorio2 = gtk_tree_view_new();
	gtk_widget_set_name(FrmCompararDiretorio.tvDiretorio2, "arvore2");
	gtk_widget_set_visible(FrmCompararDiretorio.tvDiretorio2, TRUE);
	gtk_widget_set_can_focus(FrmCompararDiretorio.tvDiretorio2, TRUE);

	FrmCompararDiretorio.scrollArvore2 = gtk_scrolled_window_new(NULL, NULL);
	gtk_widget_set_name(GTK_WIDGET(FrmCompararDiretorio.scrollArvore2), "scrollArvore2");
	gtk_widget_set_visible(FrmCompararDiretorio.scrollArvore2, TRUE);
	gtk_widget_set_can_focus(FrmCompararDiretorio.scrollArvore2, TRUE);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(FrmCompararDiretorio.scrollArvore2), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(FrmCompararDiretorio.scrollArvore2), GTK_SHADOW_IN);
	gtk_container_add(GTK_CONTAINER(FrmCompararDiretorio.scrollArvore2), FrmCompararDiretorio.tvDiretorio2);

	Arvore_cria(GTK_TREE_VIEW(FrmCompararDiretorio.tvDiretorio2));

	FrmCompararDiretorio.cmbAba2 = gtk_combo_box_text_new();
	gtk_widget_set_name(GTK_WIDGET(FrmCompararDiretorio.cmbAba2), "cmbAba2");
	gtk_widget_set_visible(FrmCompararDiretorio.cmbAba2, TRUE);
	gtk_widget_set_can_focus(FrmCompararDiretorio.cmbAba2, FALSE);

	FrmCompararDiretorio.vbox7 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_name(GTK_WIDGET(FrmCompararDiretorio.vbox7), "vbox7");
	gtk_widget_set_visible(FrmCompararDiretorio.vbox7, TRUE);
	gtk_widget_set_can_focus(FrmCompararDiretorio.vbox7, FALSE);
	gtk_container_add(GTK_CONTAINER(FrmCompararDiretorio.vbox7), FrmCompararDiretorio.cmbAba2);
	gtk_box_set_child_packing(GTK_BOX(FrmCompararDiretorio.vbox7), FrmCompararDiretorio.cmbAba2, FALSE, TRUE, 0, GTK_PACK_START);
	gtk_container_add(GTK_CONTAINER(FrmCompararDiretorio.vbox7), FrmCompararDiretorio.scrollArvore2);
	gtk_box_set_child_packing(GTK_BOX(FrmCompararDiretorio.vbox7), FrmCompararDiretorio.scrollArvore2, TRUE, TRUE, 0, GTK_PACK_START);

	FrmCompararDiretorio.frame3 = gtk_frame_new("");
	gtk_widget_set_name(GTK_WIDGET(FrmCompararDiretorio.frame3), "frame3");
	gtk_widget_set_visible(FrmCompararDiretorio.frame3, TRUE);
	gtk_widget_set_can_focus(FrmCompararDiretorio.frame3, FALSE);
	gtk_frame_set_label_align(GTK_FRAME(FrmCompararDiretorio.frame3), 0, 0);
	gtk_frame_set_shadow_type(GTK_FRAME(FrmCompararDiretorio.frame3), GTK_SHADOW_NONE);
	gtk_container_add(GTK_CONTAINER(FrmCompararDiretorio.frame3), FrmCompararDiretorio.vbox7);
	gtk_frame_set_label_widget(GTK_FRAME(FrmCompararDiretorio.frame3), FrmCompararDiretorio.label6);

	FrmCompararDiretorio.labDiretorio1 = gtk_label_new(Rotinas_retUTF8("<b>Diretório 1</b>"));
	gtk_widget_set_name(GTK_WIDGET(FrmCompararDiretorio.labDiretorio1), "labDiretorio1");
	gtk_widget_set_visible(FrmCompararDiretorio.labDiretorio1, TRUE);
	gtk_widget_set_can_focus(FrmCompararDiretorio.labDiretorio1, FALSE);
	gtk_label_set_label(GTK_LABEL(FrmCompararDiretorio.labDiretorio1), Rotinas_retUTF8("<b>Diretório 1</b>"));
	gtk_label_set_use_markup(GTK_LABEL(FrmCompararDiretorio.labDiretorio1), TRUE);

	FrmCompararDiretorio.tvDiretorio1 = gtk_tree_view_new();
	gtk_widget_set_name(FrmCompararDiretorio.tvDiretorio1, "arvore1");
	gtk_widget_set_visible(FrmCompararDiretorio.tvDiretorio1, TRUE);
	gtk_widget_set_can_focus(FrmCompararDiretorio.tvDiretorio1, TRUE);

	FrmCompararDiretorio.scrollArvore1 = gtk_scrolled_window_new(NULL, NULL);
	gtk_widget_set_name(GTK_WIDGET(FrmCompararDiretorio.scrollArvore1), "scrollArvore1");
	gtk_widget_set_visible(FrmCompararDiretorio.scrollArvore1, TRUE);
	gtk_widget_set_can_focus(FrmCompararDiretorio.scrollArvore1, TRUE);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(FrmCompararDiretorio.scrollArvore1), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(FrmCompararDiretorio.scrollArvore1), GTK_SHADOW_IN);
	gtk_container_add(GTK_CONTAINER(FrmCompararDiretorio.scrollArvore1), FrmCompararDiretorio.tvDiretorio1);

	Arvore_cria(GTK_TREE_VIEW(FrmCompararDiretorio.tvDiretorio1));

	FrmCompararDiretorio.cmbAba1 = gtk_combo_box_text_new();
	gtk_widget_set_name(GTK_WIDGET(FrmCompararDiretorio.cmbAba1), "cmbAba1");
	gtk_widget_set_visible(FrmCompararDiretorio.cmbAba1, TRUE);
	gtk_widget_set_can_focus(FrmCompararDiretorio.cmbAba1, FALSE);

	FrmCompararDiretorio.vbox6 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_name(GTK_WIDGET(FrmCompararDiretorio.vbox6), "vbox6");
	gtk_widget_set_visible(FrmCompararDiretorio.vbox6, TRUE);
	gtk_widget_set_can_focus(FrmCompararDiretorio.vbox6, FALSE);
	gtk_container_add(GTK_CONTAINER(FrmCompararDiretorio.vbox6), FrmCompararDiretorio.cmbAba1);
	gtk_box_set_child_packing(GTK_BOX(FrmCompararDiretorio.vbox6), FrmCompararDiretorio.cmbAba1, FALSE, TRUE, 0, GTK_PACK_START);
	gtk_container_add(GTK_CONTAINER(FrmCompararDiretorio.vbox6), FrmCompararDiretorio.scrollArvore1);
	gtk_box_set_child_packing(GTK_BOX(FrmCompararDiretorio.vbox6), FrmCompararDiretorio.scrollArvore1, TRUE, TRUE, 0, GTK_PACK_START);

	FrmCompararDiretorio.frame2 = gtk_frame_new("");
	gtk_widget_set_name(GTK_WIDGET(FrmCompararDiretorio.frame2), "frame2");
	gtk_widget_set_visible(FrmCompararDiretorio.frame2, TRUE);
	gtk_widget_set_can_focus(FrmCompararDiretorio.frame2, FALSE);
	gtk_frame_set_label_align(GTK_FRAME(FrmCompararDiretorio.frame2), 0, 0);
	gtk_frame_set_shadow_type(GTK_FRAME(FrmCompararDiretorio.frame2), GTK_SHADOW_NONE);
	gtk_container_add(GTK_CONTAINER(FrmCompararDiretorio.frame2), FrmCompararDiretorio.vbox6);
	gtk_frame_set_label_widget(GTK_FRAME(FrmCompararDiretorio.frame2), FrmCompararDiretorio.labDiretorio1);

	FrmCompararDiretorio.hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_widget_set_name(GTK_WIDGET(FrmCompararDiretorio.hbox2), "hbox2");
	gtk_widget_set_visible(FrmCompararDiretorio.hbox2, TRUE);
	gtk_widget_set_can_focus(FrmCompararDiretorio.hbox2, FALSE);
	gtk_container_add(GTK_CONTAINER(FrmCompararDiretorio.hbox2), FrmCompararDiretorio.frame2);
	gtk_box_set_child_packing(GTK_BOX(FrmCompararDiretorio.hbox2), FrmCompararDiretorio.frame2, TRUE, TRUE, 0, GTK_PACK_START);
	gtk_container_add(GTK_CONTAINER(FrmCompararDiretorio.hbox2), FrmCompararDiretorio.frame3);
	gtk_box_set_child_packing(GTK_BOX(FrmCompararDiretorio.hbox2), FrmCompararDiretorio.frame3, TRUE, TRUE, 0, GTK_PACK_START);

	FrmCompararDiretorio.btnSalvarLog = gtk_button_new();
	gtk_widget_set_name(GTK_WIDGET(FrmCompararDiretorio.btnSalvarLog), "btnSalvarLog");
	gtk_button_set_label(GTK_BUTTON(FrmCompararDiretorio.btnSalvarLog), "Salvar Log");
	gtk_widget_set_visible(FrmCompararDiretorio.btnSalvarLog, TRUE);
	gtk_widget_set_can_focus(FrmCompararDiretorio.btnSalvarLog, TRUE);
	gtk_widget_set_receives_default(FrmCompararDiretorio.btnSalvarLog, TRUE);

	FrmCompararDiretorio.pb2 = gtk_progress_bar_new();
	gtk_widget_set_name(GTK_WIDGET(FrmCompararDiretorio.pb2), "pb2");
	gtk_widget_set_visible(FrmCompararDiretorio.pb2, TRUE);
	gtk_widget_set_can_focus(FrmCompararDiretorio.pb2, FALSE);

	FrmCompararDiretorio.btnCompararDiretorios = gtk_button_new();
	gtk_widget_set_name(GTK_WIDGET(FrmCompararDiretorio.btnCompararDiretorios), "btnCompararDiretorios");
	gtk_button_set_label(GTK_BUTTON(FrmCompararDiretorio.btnCompararDiretorios), Rotinas_retUTF8("Comparar Diretórios"));
	gtk_widget_set_visible(FrmCompararDiretorio.btnCompararDiretorios, TRUE);
	gtk_widget_set_can_focus(FrmCompararDiretorio.btnCompararDiretorios, TRUE);
	gtk_widget_set_receives_default(FrmCompararDiretorio.btnCompararDiretorios, TRUE);

	FrmCompararDiretorio.hbox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_widget_set_name(GTK_WIDGET(FrmCompararDiretorio.hbox1), "hbox1");
	gtk_widget_set_visible(FrmCompararDiretorio.hbox1, TRUE);
	gtk_widget_set_can_focus(FrmCompararDiretorio.hbox1, FALSE);
	gtk_container_add(GTK_CONTAINER(FrmCompararDiretorio.hbox1), FrmCompararDiretorio.btnCompararDiretorios);
	gtk_box_set_child_packing(GTK_BOX(FrmCompararDiretorio.hbox1), FrmCompararDiretorio.btnCompararDiretorios, FALSE, TRUE, 0, GTK_PACK_START);
	gtk_container_add(GTK_CONTAINER(FrmCompararDiretorio.hbox1), FrmCompararDiretorio.pb2);
	gtk_box_set_child_packing(GTK_BOX(FrmCompararDiretorio.hbox1), FrmCompararDiretorio.pb2, TRUE, TRUE, 0, GTK_PACK_START);
	gtk_container_add(GTK_CONTAINER(FrmCompararDiretorio.hbox1), FrmCompararDiretorio.btnSalvarLog);
	gtk_box_set_child_packing(GTK_BOX(FrmCompararDiretorio.hbox1), FrmCompararDiretorio.btnSalvarLog, FALSE, TRUE, 0, GTK_PACK_START);

	FrmCompararDiretorio.vbox5 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_name(GTK_WIDGET(FrmCompararDiretorio.vbox5), "vbox5");
	gtk_widget_set_visible(FrmCompararDiretorio.vbox5, TRUE);
	gtk_widget_set_can_focus(FrmCompararDiretorio.vbox5, FALSE);
	gtk_container_add(GTK_CONTAINER(FrmCompararDiretorio.vbox5), FrmCompararDiretorio.hbox1);
	gtk_box_set_child_packing(GTK_BOX(FrmCompararDiretorio.vbox5), FrmCompararDiretorio.hbox1, FALSE, FALSE, 0, GTK_PACK_START);
	gtk_container_add(GTK_CONTAINER(FrmCompararDiretorio.vbox5), FrmCompararDiretorio.hbox2);
	gtk_box_set_child_packing(GTK_BOX(FrmCompararDiretorio.vbox5), FrmCompararDiretorio.hbox2, TRUE, TRUE, 0, GTK_PACK_START);
	gtk_container_add(GTK_CONTAINER(FrmCompararDiretorio.vbox5), FrmCompararDiretorio.hbox4);
	gtk_box_set_child_packing(GTK_BOX(FrmCompararDiretorio.vbox5), FrmCompararDiretorio.hbox4, FALSE, TRUE, 0, GTK_PACK_START);
	gtk_container_add(GTK_CONTAINER(FrmCompararDiretorio.vbox5), FrmCompararDiretorio.scrollCompara);
	gtk_box_set_child_packing(GTK_BOX(FrmCompararDiretorio.vbox5), FrmCompararDiretorio.scrollCompara, TRUE, TRUE, 0, GTK_PACK_START);
	gtk_container_add(GTK_CONTAINER(FrmCompararDiretorio.vbox5), FrmCompararDiretorio.hbox5);
	gtk_box_set_child_packing(GTK_BOX(FrmCompararDiretorio.vbox5), FrmCompararDiretorio.hbox5, FALSE, TRUE, 0, GTK_PACK_START);

	gtk_widget_set_name(FrmCompararDiretorio.frmCompararDiretorio, "frmCompararDiretorio");
	gtk_widget_set_size_request(FrmCompararDiretorio.frmCompararDiretorio, 700, 600);
	gtk_widget_set_visible(FrmCompararDiretorio.frmCompararDiretorio, TRUE);
	gtk_widget_set_can_focus(FrmCompararDiretorio.frmCompararDiretorio, FALSE);
	gtk_window_set_title(GTK_WINDOW(FrmCompararDiretorio.frmCompararDiretorio), Rotinas_retUTF8("Comparar Diretórios"));
	gtk_window_set_resizable(GTK_WINDOW(FrmCompararDiretorio.frmCompararDiretorio), FALSE);
	gtk_window_set_modal(GTK_WINDOW(FrmCompararDiretorio.frmCompararDiretorio), TRUE);
	gtk_window_set_position(GTK_WINDOW(FrmCompararDiretorio.frmCompararDiretorio), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(FrmCompararDiretorio.frmCompararDiretorio), 700, 600);
	gtk_container_add(GTK_CONTAINER(FrmCompararDiretorio.frmCompararDiretorio), GTK_WIDGET(FrmCompararDiretorio.vbox5));


	g_signal_connect(FrmCompararDiretorio.btnCompararDiretorios, "clicked", G_CALLBACK(on_btnCompararDiretorios_clicked), NULL);
	g_signal_connect(FrmCompararDiretorio.btnSalvarLog, "clicked", G_CALLBACK(btnSalvarLog_clicked_cb), NULL);
	g_signal_connect(FrmCompararDiretorio.cmbAba1, "changed", G_CALLBACK(on_cmbAba1_changed), NULL);
	g_signal_connect(FrmCompararDiretorio.tvDiretorio1, "row_collapsed", G_CALLBACK(on_tvDiretorio1_row_collapsed), NULL);
	g_signal_connect(FrmCompararDiretorio.tvDiretorio1, "row_expanded", G_CALLBACK(on_tvDiretorio1_row_expanded), NULL);
	g_signal_connect(FrmCompararDiretorio.tvDiretorio1, "button_release_event", G_CALLBACK(on_tvDiretorio1_button_release_event), NULL);
	g_signal_connect(FrmCompararDiretorio.tvDiretorio1, "button_press_event", G_CALLBACK(on_tvDiretorio1_button_press_event), NULL);

	g_signal_connect(FrmCompararDiretorio.cmbAba2, "changed", G_CALLBACK(on_cmbAba2_changed), NULL);
	g_signal_connect(FrmCompararDiretorio.tvDiretorio2, "row_collapsed", G_CALLBACK(on_tvDiretorio2_row_collapsed), NULL);
	g_signal_connect(FrmCompararDiretorio.tvDiretorio2, "row_expanded", G_CALLBACK(on_tvDiretorio2_row_expanded), NULL);
	g_signal_connect(FrmCompararDiretorio.tvDiretorio2, "button_release_event", G_CALLBACK(on_tvDiretorio2_button_release_event), NULL);
	g_signal_connect(FrmCompararDiretorio.tvDiretorio2, "button_press_event", G_CALLBACK(on_tvDiretorio2_button_press_event), NULL);

	g_signal_connect(FrmCompararDiretorio.tabelaCompara, "row_activated", G_CALLBACK(on_tabelaCompara_row_activated), NULL);
	g_signal_connect(FrmCompararDiretorio.tabelaCompara, "button_release_event", G_CALLBACK(on_tabelaCompara_button_release_event), NULL);

	g_signal_connect (FrmCompararDiretorio.frmCompararDiretorio, "destroy",
		G_CALLBACK (on_FrmCompararDiretorio_destroy), NULL);

	gtk_label_set_text(FrmCompararDiretorio_getLabStatus1(), Rotinas_retUTF8("Total de diferenças encontradas:"));

	FrmCompararDiretorio_CarregarDados();
	FrmCompararDiretorio_LimparComparacao();

	return FrmCompararDiretorio.frmCompararDiretorio;
}
// ---------------------------------------------------------------------------
void FrmCompararDiretorio_Mostrar()
{
    FrmCompararDiretorio.frmCompararDiretorio = FrmCompararDiretorio_Criar();
	gtk_window_set_position (GTK_WINDOW(FrmCompararDiretorio.frmCompararDiretorio), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_widget_show(FrmCompararDiretorio.frmCompararDiretorio);
}
// ---------------------------------------------------------------------------
void on_FrmCompararDiretorio_destroy(GtkWidget* widget, gpointer user_data) {

}
// ---------------------------------------------------------------------------

void FrmCompararDiretorio_ProgressoLog(Progresso progresso)
{
	if (FrmCompararDiretorio.frmCompararDiretorio != NULL) {
		if (progresso.posicao == 0) {
			gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(FrmCompararDiretorio.pb2), progresso.minimo);
			gtk_progress_bar_set_pulse_step(GTK_PROGRESS_BAR(FrmCompararDiretorio.pb2), 0.1); //progresso.passo
		}
		gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(FrmCompararDiretorio.pb2),
			Rotinas_calculaProgresso(progresso.maximo, progresso.posicao));
	}
}

GtkLabel* FrmCompararDiretorio_getLabStatus1() {
	GList* lista = gtk_container_get_children(GTK_CONTAINER(FrmCompararDiretorio.barraStatus11));
	GtkFrame* frameStatus1 = g_list_nth_data(lista, 0);

	lista = gtk_container_get_children(GTK_CONTAINER(frameStatus1));
	GtkHBox* hboxStatus1 = g_list_nth_data(lista, 0);

	lista = gtk_container_get_children(GTK_CONTAINER(hboxStatus1));
	GtkLabel* labStatus1 = g_list_nth_data(lista, 0);

	return labStatus1;
}

GtkLabel* FrmCompararDiretorio_getLabStatus2() {
	GList* lista = gtk_container_get_children(GTK_CONTAINER(FrmCompararDiretorio.barraStatus21));
	GtkFrame* frameStatus2 = g_list_nth_data(lista, 0);

	lista = gtk_container_get_children(GTK_CONTAINER(frameStatus2));
	GtkHBox* hboxStatus2 = g_list_nth_data(lista, 0);

	lista = gtk_container_get_children(GTK_CONTAINER(hboxStatus2));
	GtkLabel* labStatus2 = g_list_nth_data(lista, 0);

	return labStatus2;
}


void on_btnCompararDiretorios_clicked(GtkWidget* widget, gpointer user_data){
	GString *sCaminhoDir1, *sCaminhoDir2;
	gboolean bSelecionado;
	GtkTreeIter iter1, iter2;
	GtkTreeModel *modelo1, *modelo2;
	//GtkTreeStore *store1, *store2;
	GtkTreeSelection *selecao1, *selecao2;
	const gchar* texto;

	sCaminhoDir1 = g_string_new("");
	sCaminhoDir2 = g_string_new("");
	bSelecionado = FALSE;
	modelo1 = gtk_tree_view_get_model(GTK_TREE_VIEW(FrmCompararDiretorio.tvDiretorio1));
	selecao1 = gtk_tree_view_get_selection(GTK_TREE_VIEW(FrmCompararDiretorio.tvDiretorio1));
	//store1 = GTK_TREE_STORE(modelo1);

	if (gtk_tree_selection_get_selected(selecao1, &modelo1, &iter1)) {
		if (gtk_tree_selection_iter_is_selected(selecao1, &iter1)) {
			Catalogador_LerArvoreDiretorio(modelo1, iter1, FrmCompararDiretorio_getLabStatus2());
			texto = gtk_label_get_text(FrmCompararDiretorio_getLabStatus2());
			sCaminhoDir1 = g_string_new(texto);

			modelo2 = gtk_tree_view_get_model(GTK_TREE_VIEW(FrmCompararDiretorio.tvDiretorio2));
			selecao2 = gtk_tree_view_get_selection(GTK_TREE_VIEW(FrmCompararDiretorio.tvDiretorio2));
			//store2 = GTK_TREE_STORE(modelo2);

			if (gtk_tree_selection_get_selected(selecao2, &modelo2, &iter2)) {
				if (gtk_tree_selection_iter_is_selected(selecao2, &iter2)) {
					Catalogador_LerArvoreDiretorio(modelo2, iter2, FrmCompararDiretorio_getLabStatus2());
					texto = gtk_label_get_text(FrmCompararDiretorio_getLabStatus2());
					sCaminhoDir2 = g_string_new(texto);
					bSelecionado = TRUE;
				}
			}
		}
	}

	FrmCompararDiretorio_LimparComparacao();

	if (bSelecionado) {
		FrmCompararDiretorio_Comparar(sCaminhoDir1, sCaminhoDir2);
	}
	else {
		Dialogo_mensagemInfo(FrmCompararDiretorio.frmCompararDiretorio,
			"FrmCompararDiretorio.DiretoriosNaoSelecionados");
	}

}

void btnSalvarLog_clicked_cb(GtkWidget* widget, gpointer user_data){
	GString* sLog;
	Diretorio diretorio = Diretorio_new();
	ListaString listaLocal = ListaString_inicia();
	guint tamlista = ListaDiretorio_conta(FrmCompararDiretorio.listaCompara);

	if (tamlista > 0) {
		listaLocal = ListaString_inicia();
		sLog = Rotinas_concatenar2(Rotinas_AppDirPath(),
			Rotinas_formataDate(Rotinas_FORMATO_DHARQUIVO, Rotinas_DataHoraNow()),
			"_Comparacao.log");

		for (unsigned int i = 0; i < tamlista; i++) {
			diretorio = ListaDiretorio_pesquisaItemOrd(FrmCompararDiretorio.listaCompara, i);

			listaLocal = ListaString_insere(listaLocal, diretorio->caminho, i);
		}

		Rotinas_SListSaveToFile(listaLocal, sLog);

		Dialogo_mensagemInfo(FrmCompararDiretorio.frmCompararDiretorio,
			"FrmCompararDiretorio.LogSalvoMemoDirSistema");
	}

}

void on_cmbAba1_changed(GtkWidget* widget, gpointer user_data){
	Aba aba = Aba_new();

	Catalogador_SetCursor(GDK_WATCH);

	Arvore_limpar(GTK_TREE_VIEW(FrmCompararDiretorio.tvDiretorio1));

	gint indice = gtk_combo_box_get_active(GTK_COMBO_BOX(FrmCompararDiretorio.cmbAba1));

	aba = AbaBO_pegaAbaPorOrdem(Catalogador.listaAbas, indice + 1);
	Catalogador_CarregarArvore(GTK_TREE_VIEW(FrmCompararDiretorio.tvDiretorio1), aba);

	gtk_widget_grab_focus(FrmCompararDiretorio.tvDiretorio1);
	FrmCompararDiretorio_LimparComparacao();

	Catalogador_SetCursor(GDK_ARROW);

}

void on_tvDiretorio1_row_collapsed(GtkTreeView *tree_view, GtkTreeIter *iter, GtkTreePath *path, gpointer user_data){

}

void on_tvDiretorio1_row_expanded(GtkTreeView *tree_view, GtkTreeIter *iter, GtkTreePath *path, gpointer user_data){

}

gboolean on_tvDiretorio1_button_release_event(GtkWidget *widget, GdkEvent *event, gpointer user_data){
		return FALSE;
}

gboolean on_tvDiretorio1_button_press_event(GtkWidget *widget, GdkEvent *event, gpointer user_data) {
	GtkTreeView* arvore;

	if (event->button.button == 1) {
		if (event->button.type == GDK_2BUTTON_PRESS) {
			arvore = (GtkTreeView*)widget;
			Arvore_expandirSelecionado(arvore);
		}
	}
	return FALSE;
}

void on_cmbAba2_changed(GtkWidget* widget, gpointer user_data){
	Aba aba = Aba_new();

	Catalogador_SetCursor(GDK_WATCH);

	Arvore_limpar(GTK_TREE_VIEW(FrmCompararDiretorio.tvDiretorio2));

	gint indice = gtk_combo_box_get_active(GTK_COMBO_BOX(FrmCompararDiretorio.cmbAba2));

	aba = AbaBO_pegaAbaPorOrdem(Catalogador.listaAbas, indice + 1);
	Catalogador_CarregarArvore(GTK_TREE_VIEW(FrmCompararDiretorio.tvDiretorio2), aba);

	gtk_widget_grab_focus(FrmCompararDiretorio.tvDiretorio2);
	FrmCompararDiretorio_LimparComparacao();

	Catalogador_SetCursor(GDK_ARROW);
}

void on_tvDiretorio2_row_collapsed(GtkTreeView *tree_view, GtkTreeIter *iter, GtkTreePath *path, gpointer user_data){

}

void on_tvDiretorio2_row_expanded(GtkTreeView *tree_view, GtkTreeIter *iter, GtkTreePath *path, gpointer user_data){

}

gboolean on_tvDiretorio2_button_release_event(GtkWidget *widget, GdkEvent *event, gpointer user_data){
		return FALSE;
}

gboolean on_tvDiretorio2_button_press_event(GtkWidget *widget, GdkEvent *event, gpointer user_data) {
	GtkTreeView* arvore;

	if (event->button.button == 1) {
		if (event->button.type == GDK_2BUTTON_PRESS) {
			arvore = (GtkTreeView*)widget;
			Arvore_expandirSelecionado(arvore);
		}
	}
	return FALSE;
}

void on_tabelaCompara_row_activated(GtkTreeView *tree_view, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data){

}

gboolean on_tabelaCompara_button_release_event(GtkWidget *widget, GdkEvent *event, gpointer user_data){
		return FALSE;
}


// ---------------------------------------------------------------------------
void FrmCompararDiretorio_CarregarDados() {
	GtkTreeIter iter;
	GtkTreeModel *modelo1, *modelo2;
	guint tamlista = ListaAba_conta(Catalogador.listaAbas);
	Aba aba = Aba_new();

	for (unsigned int i = 0; i < tamlista; i++) {
		aba = ListaAba_pesquisaItemOrd(Catalogador.listaAbas, i);

		GString* codigo = Rotinas_IntToStr(aba->codigo);
		gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(FrmCompararDiretorio.cmbAba1), codigo->str, aba->nome->str);
		gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(FrmCompararDiretorio.cmbAba2), codigo->str, aba->nome->str);
	}

	modelo1 = gtk_combo_box_get_model(GTK_COMBO_BOX(FrmCompararDiretorio.cmbAba1));
	modelo2 = gtk_combo_box_get_model(GTK_COMBO_BOX(FrmCompararDiretorio.cmbAba2));

	if (gtk_tree_model_get_iter_first(modelo1, &iter)) {
		gtk_combo_box_set_active_iter(GTK_COMBO_BOX(FrmCompararDiretorio.cmbAba1), &iter);
	}

	if (gtk_tree_model_get_iter_first(modelo2, &iter)) {
		gtk_combo_box_set_active_iter(GTK_COMBO_BOX(FrmCompararDiretorio.cmbAba2), &iter);
	}
}

void FrmCompararDiretorio_LimparComparacao() {
	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(FrmCompararDiretorio.pb2), 0);
	Tabela_limpar(GTK_TREE_VIEW(FrmCompararDiretorio.tabelaCompara));
	gtk_widget_set_sensitive(FrmCompararDiretorio.btnSalvarLog, FALSE);
	gtk_label_set_text(FrmCompararDiretorio_getLabStatus2(), "");
}

GString* FrmCompararDiretorio_SQLCompara(Aba aba1, Aba aba2, const GString* caminho1,
	const GString* caminho2) {
	GString* scaminho1 = g_string_new(caminho1->str);
	GString* scaminho2 = g_string_new(caminho2->str);
	GString* sSQL = DiretorioBO_sqlConsultaArquivo();

	g_string_append_printf(sSQL, " WHERE aba=%d AND caminho LIKE %s AND nome NOT IN " \
		"(SELECT nome FROM Diretorios WHERE aba=%d AND caminho LIKE %s) ORDER BY 1, 2, 3",
		aba1->codigo, Rotinas_QuotedStr(g_string_append_c_inline(scaminho1, '%'))->str,
		aba2->codigo, Rotinas_QuotedStr(g_string_append_c_inline(scaminho2, '%'))->str);
	return sSQL;
}

void FrmCompararDiretorio_Comparar(const GString* sCaminhoDir1, const GString* sCaminhoDir2) {
	GString* sSQL;
	Aba aba1 = Aba_new(), aba2 = Aba_new();
	guint tamlista;

	gint indice = gtk_combo_box_get_active(GTK_COMBO_BOX(FrmCompararDiretorio.cmbAba1));
	aba1 = AbaBO_pegaAbaPorOrdem(Catalogador.listaAbas, indice + 1);

	indice = gtk_combo_box_get_active(GTK_COMBO_BOX(FrmCompararDiretorio.cmbAba2));
	aba2 = AbaBO_pegaAbaPorOrdem(Catalogador.listaAbas, indice + 1);

	sSQL = FrmCompararDiretorio_SQLCompara(aba1, aba2, sCaminhoDir1, sCaminhoDir2);
	FrmCompararDiretorio.listaCompara = DiretorioBO_carregarDiretorio(sSQL,
		g_string_new("consultaarquivo"), FrmCompararDiretorio_ProgressoLog);
	tamlista = ListaDiretorio_conta(FrmCompararDiretorio.listaCompara);

	if (tamlista > 0) {
		Tabela_carregar(GTK_TREE_VIEW(FrmCompararDiretorio.tabelaCompara), TRUE,
			FrmCompararDiretorio.listaCompara, Catalogador.listaExtensoes,
			GTK_PROGRESS_BAR(FrmCompararDiretorio.pb2));

		gtk_label_set_text(FrmCompararDiretorio_getLabStatus2(), Rotinas_IntToStr(tamlista)->str);
		gtk_widget_set_sensitive(FrmCompararDiretorio.btnSalvarLog, TRUE);
	}
	else {
		Dialogo_mensagemInfo(FrmCompararDiretorio.frmCompararDiretorio,
			"FrmCompararDiretorio.NenhumaDiferencaEncontrada");
	}
}
