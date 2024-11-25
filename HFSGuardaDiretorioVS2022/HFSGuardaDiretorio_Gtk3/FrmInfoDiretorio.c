#include "FrmInfoDiretorio.h"
#include "hfsguardadir/comum/Rotinas.h"

struct SFrmInfoDiretorio FrmInfoDiretorio;
// ---------------------------------------------------------------------------
GtkWidget *FrmInfoDiretorio_Criar()
{
	FrmInfoDiretorio.frmInfoDiretorio = gtk_dialog_new();

	FrmInfoDiretorio.btnOk = gtk_button_new();
	gtk_widget_set_name(GTK_WIDGET(FrmInfoDiretorio.btnOk), "btnOk");
	gtk_button_set_label(GTK_BUTTON(FrmInfoDiretorio.btnOk), "Ok");
	gtk_widget_set_visible(FrmInfoDiretorio.btnOk, TRUE);
	gtk_widget_set_can_focus(FrmInfoDiretorio.btnOk, TRUE);
	gtk_widget_set_receives_default(FrmInfoDiretorio.btnOk, TRUE);
	gtk_widget_set_margin_top(GTK_WIDGET(FrmInfoDiretorio.btnOk), 10);
	gtk_widget_set_margin_bottom(GTK_WIDGET(FrmInfoDiretorio.btnOk), 10);

	FrmInfoDiretorio.dialog_action_area3 = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_widget_set_name(GTK_WIDGET(FrmInfoDiretorio.dialog_action_area3), "dialog_action_area3");
	gtk_widget_set_visible(FrmInfoDiretorio.dialog_action_area3, TRUE);
	gtk_widget_set_can_focus(FrmInfoDiretorio.dialog_action_area3, FALSE);
	gtk_button_box_set_layout(GTK_BUTTON_BOX(FrmInfoDiretorio.dialog_action_area3), GTK_BUTTONBOX_CENTER);
	gtk_container_add(GTK_CONTAINER(FrmInfoDiretorio.dialog_action_area3), FrmInfoDiretorio.btnOk);
	gtk_box_set_child_packing(GTK_BOX(FrmInfoDiretorio.dialog_action_area3), FrmInfoDiretorio.btnOk, FALSE, FALSE, 0, GTK_PACK_START);
	
	FrmInfoDiretorio.colunaInfoDescricao = gtk_tree_view_column_new_with_attributes(Rotinas_retUTF8("Descrição"), gtk_cell_renderer_text_new(), "text", 1, NULL);
	gtk_tree_view_column_set_resizable(FrmInfoDiretorio.colunaInfoDescricao, TRUE);
	gtk_tree_view_column_set_sizing(FrmInfoDiretorio.colunaInfoDescricao, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
	gtk_tree_view_column_set_title(FrmInfoDiretorio.colunaInfoDescricao, Rotinas_retUTF8("Descrição"));
	gtk_tree_view_column_set_sort_column_id(FrmInfoDiretorio.colunaInfoDescricao, 2);
		
	GtkCellRenderer* rtexto = gtk_cell_renderer_text_new();	
	g_object_set(rtexto, "weight", PANGO_WEIGHT_BOLD, NULL);
	
	FrmInfoDiretorio.colunaInfoItem = gtk_tree_view_column_new_with_attributes("Item", rtexto, "text", 0, NULL);
	gtk_tree_view_column_set_resizable(FrmInfoDiretorio.colunaInfoItem, TRUE);
	gtk_tree_view_column_set_sizing(FrmInfoDiretorio.colunaInfoItem, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
	gtk_tree_view_column_set_title(FrmInfoDiretorio.colunaInfoItem, "Item");
	gtk_tree_view_column_set_sort_column_id(FrmInfoDiretorio.colunaInfoItem, 1);
	
	FrmInfoDiretorio.tabelaInfo = gtk_tree_view_new();
	gtk_widget_set_name(GTK_WIDGET(FrmInfoDiretorio.tabelaInfo), "tabelaInfo");
	gtk_widget_set_visible(FrmInfoDiretorio.tabelaInfo, TRUE);
	gtk_widget_set_can_focus(FrmInfoDiretorio.tabelaInfo, TRUE);

	gtk_tree_view_append_column(GTK_TREE_VIEW(FrmInfoDiretorio.tabelaInfo), FrmInfoDiretorio.colunaInfoItem);
	gtk_tree_view_append_column(GTK_TREE_VIEW(FrmInfoDiretorio.tabelaInfo), FrmInfoDiretorio.colunaInfoDescricao);
	
	FrmInfoDiretorio.scrollTabela1 = gtk_scrolled_window_new(NULL, NULL);
	gtk_widget_set_name(GTK_WIDGET(FrmInfoDiretorio.scrollTabela1), "scrollTabela1");
	gtk_widget_set_visible(FrmInfoDiretorio.scrollTabela1, TRUE);
	gtk_widget_set_can_focus(FrmInfoDiretorio.scrollTabela1, TRUE);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(FrmInfoDiretorio.scrollTabela1), 
		GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_widget_set_vexpand(FrmInfoDiretorio.scrollTabela1, TRUE);
	gtk_container_add(GTK_CONTAINER(FrmInfoDiretorio.scrollTabela1), FrmInfoDiretorio.tabelaInfo);
	
	FrmInfoDiretorio.labArquivoSomenteLeitura = gtk_label_new("[ROL] - Arquivo Somente Leitura");
	gtk_widget_set_name(GTK_WIDGET(FrmInfoDiretorio.labArquivoSomenteLeitura), "labArquivoSomenteLeitura");
	gtk_widget_set_visible(FrmInfoDiretorio.labArquivoSomenteLeitura, TRUE);
	gtk_widget_set_can_focus(FrmInfoDiretorio.labArquivoSomenteLeitura, FALSE);
	gtk_label_set_label(GTK_LABEL(FrmInfoDiretorio.labArquivoSomenteLeitura), "[ROL] - Arquivo Somente Leitura");
	
	FrmInfoDiretorio.labVolumeID = gtk_label_new("[VOL] - Volume ID");
	gtk_widget_set_name(GTK_WIDGET(FrmInfoDiretorio.labVolumeID), "labVolumeID");
	gtk_widget_set_visible(FrmInfoDiretorio.labVolumeID, TRUE);
	gtk_widget_set_can_focus(FrmInfoDiretorio.labVolumeID, FALSE);
	gtk_label_set_label(GTK_LABEL(FrmInfoDiretorio.labVolumeID), "[VOL] - Volume ID");
	
	FrmInfoDiretorio.labLegendaDiretorio = gtk_label_new(Rotinas_retUTF8("[DIR] - Diretório"));
	gtk_widget_set_name(GTK_WIDGET(FrmInfoDiretorio.labLegendaDiretorio), "labLegendaDiretorio");
	gtk_widget_set_visible(FrmInfoDiretorio.labLegendaDiretorio, TRUE);
	gtk_widget_set_can_focus(FrmInfoDiretorio.labLegendaDiretorio, FALSE);
	gtk_label_set_label(GTK_LABEL(FrmInfoDiretorio.labLegendaDiretorio), Rotinas_retUTF8("[DIR] - Diretório"));
	
	FrmInfoDiretorio.labArquivoSistema = gtk_label_new("[SYS] - Arquivo de Sistema");
	gtk_widget_set_name(GTK_WIDGET(FrmInfoDiretorio.labArquivoSistema), "labArquivoSistema");
	gtk_widget_set_visible(FrmInfoDiretorio.labArquivoSistema, TRUE);
	gtk_widget_set_can_focus(FrmInfoDiretorio.labArquivoSistema, FALSE);
	gtk_label_set_label(GTK_LABEL(FrmInfoDiretorio.labArquivoSistema), "[SYS] - Arquivo de Sistema");
	
	FrmInfoDiretorio.labArquivoOculto = gtk_label_new("[HID] - Arquivo Oculto");
	gtk_widget_set_name(GTK_WIDGET(FrmInfoDiretorio.labArquivoOculto), "labArquivoOculto");
	gtk_widget_set_visible(FrmInfoDiretorio.labArquivoOculto, TRUE);
	gtk_widget_set_can_focus(FrmInfoDiretorio.labArquivoOculto, FALSE);
	gtk_label_set_label(GTK_LABEL(FrmInfoDiretorio.labArquivoOculto), "[HID] - Arquivo Oculto");
	gtk_widget_set_margin_bottom(GTK_WIDGET(FrmInfoDiretorio.labArquivoOculto), 5);

	FrmInfoDiretorio.labArquivoComum = gtk_label_new("[ARQ] - Arquivo comum");
	gtk_widget_set_name(GTK_WIDGET(FrmInfoDiretorio.labArquivoComum), "labArquivoComum");
	gtk_widget_set_visible(FrmInfoDiretorio.labArquivoComum, TRUE);
	gtk_widget_set_can_focus(FrmInfoDiretorio.labArquivoComum, FALSE);
	gtk_label_set_label(GTK_LABEL(FrmInfoDiretorio.labArquivoComum), "[ARQ] - Arquivo comum");
	gtk_widget_set_margin_bottom(GTK_WIDGET(FrmInfoDiretorio.labArquivoComum), 5);

	FrmInfoDiretorio.grid1 = gtk_grid_new();
	gtk_widget_set_name(GTK_WIDGET(FrmInfoDiretorio.grid1), "grid1");
	gtk_widget_set_visible(FrmInfoDiretorio.grid1, TRUE);
	gtk_widget_set_can_focus(FrmInfoDiretorio.grid1, FALSE);
	gtk_widget_set_margin_start(FrmInfoDiretorio.grid1, 2);
	gtk_widget_set_margin_bottom(FrmInfoDiretorio.grid1, 2);
	gtk_grid_set_row_spacing(GTK_GRID(FrmInfoDiretorio.grid1), 6);
	gtk_grid_set_column_spacing(GTK_GRID(FrmInfoDiretorio.grid1), 6);
	gtk_grid_set_column_homogeneous(GTK_GRID(FrmInfoDiretorio.grid1), TRUE);
	gtk_grid_set_row_homogeneous(GTK_GRID(FrmInfoDiretorio.grid1), TRUE);

	gtk_grid_attach(GTK_GRID(FrmInfoDiretorio.grid1), FrmInfoDiretorio.labArquivoComum, 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(FrmInfoDiretorio.grid1), FrmInfoDiretorio.labArquivoOculto, 1, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(FrmInfoDiretorio.grid1), FrmInfoDiretorio.labArquivoSistema, 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(FrmInfoDiretorio.grid1), FrmInfoDiretorio.labLegendaDiretorio, 1, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(FrmInfoDiretorio.grid1), FrmInfoDiretorio.labVolumeID, 0, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(FrmInfoDiretorio.grid1), FrmInfoDiretorio.labArquivoSomenteLeitura, 1, 2, 1, 1);

	FrmInfoDiretorio.frame1 = gtk_frame_new("");
	gtk_widget_set_name(GTK_WIDGET(FrmInfoDiretorio.frame1), "frame1");
	gtk_widget_set_visible(FrmInfoDiretorio.frame1, TRUE);
	gtk_widget_set_can_focus(FrmInfoDiretorio.frame1, FALSE);
	gtk_frame_set_label_align(GTK_FRAME(FrmInfoDiretorio.frame1), 0, 0);
	gtk_container_add(GTK_CONTAINER(FrmInfoDiretorio.frame1), FrmInfoDiretorio.grid1);
	
	FrmInfoDiretorio.vbox3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_name(GTK_WIDGET(FrmInfoDiretorio.vbox3), "vbox3");
	gtk_widget_set_visible(FrmInfoDiretorio.vbox3, TRUE);
	gtk_widget_set_can_focus(FrmInfoDiretorio.vbox3, FALSE);
	gtk_container_add(GTK_CONTAINER(FrmInfoDiretorio.vbox3), FrmInfoDiretorio.frame1);
	gtk_box_set_child_packing(GTK_BOX(FrmInfoDiretorio.vbox3), FrmInfoDiretorio.frame1, FALSE, TRUE, 0, GTK_PACK_START);
	gtk_container_add(GTK_CONTAINER(FrmInfoDiretorio.vbox3), FrmInfoDiretorio.scrollTabela1);
	gtk_box_set_child_packing(GTK_BOX(FrmInfoDiretorio.vbox3), FrmInfoDiretorio.scrollTabela1, TRUE, TRUE, 0, GTK_PACK_START);
	
	FrmInfoDiretorio.dialog_vbox3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
	gtk_widget_set_name(GTK_WIDGET(FrmInfoDiretorio.dialog_vbox3), "dialog_vbox3");
	gtk_widget_set_visible(FrmInfoDiretorio.dialog_vbox3, TRUE);
	gtk_widget_set_can_focus(FrmInfoDiretorio.dialog_vbox3, FALSE);
	gtk_box_set_spacing(GTK_BOX(FrmInfoDiretorio.dialog_vbox3), 2);
	gtk_container_add(GTK_CONTAINER(FrmInfoDiretorio.dialog_vbox3), FrmInfoDiretorio.vbox3);
	gtk_box_set_child_packing(GTK_BOX(FrmInfoDiretorio.dialog_vbox3), FrmInfoDiretorio.vbox3, TRUE, TRUE, 0, GTK_PACK_START);
	gtk_container_add(GTK_CONTAINER(FrmInfoDiretorio.dialog_vbox3), FrmInfoDiretorio.dialog_action_area3);
	gtk_box_set_child_packing(GTK_BOX(FrmInfoDiretorio.dialog_vbox3), FrmInfoDiretorio.dialog_action_area3, FALSE, TRUE, 0, GTK_PACK_START);
	
	gtk_widget_set_name(FrmInfoDiretorio.frmInfoDiretorio, "frmInfoDiretorio");
	gtk_widget_set_size_request(FrmInfoDiretorio.frmInfoDiretorio, 385, 490);
	gtk_widget_set_can_focus(FrmInfoDiretorio.frmInfoDiretorio, FALSE);
	gtk_container_set_border_width(GTK_CONTAINER(FrmInfoDiretorio.frmInfoDiretorio), 5);
	gtk_window_set_title(GTK_WINDOW(FrmInfoDiretorio.frmInfoDiretorio), Rotinas_retUTF8("Informações do Diretório / Arquivo"));
	gtk_window_set_resizable(GTK_WINDOW(FrmInfoDiretorio.frmInfoDiretorio), FALSE);
	gtk_window_set_modal(GTK_WINDOW(FrmInfoDiretorio.frmInfoDiretorio), TRUE);
	gtk_window_set_position(GTK_WINDOW(FrmInfoDiretorio.frmInfoDiretorio), GTK_WIN_POS_CENTER);
	gtk_window_set_type_hint(GTK_WINDOW(FrmInfoDiretorio.frmInfoDiretorio), GDK_WINDOW_TYPE_HINT_DIALOG);
	GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(FrmInfoDiretorio.frmInfoDiretorio));
	gtk_container_add(GTK_CONTAINER(content_area), GTK_WIDGET(FrmInfoDiretorio.dialog_vbox3));
	
	g_signal_connect(FrmInfoDiretorio.btnOk, "clicked", G_CALLBACK(on_btnOk_clicked), NULL); 			
	g_signal_connect (FrmInfoDiretorio.frmInfoDiretorio, "destroy", 
		G_CALLBACK (on_FrmInfoDiretorio_destroy), NULL);

	FrmInfoDiretorio_ConstruirGrid();

	return FrmInfoDiretorio.frmInfoDiretorio;
}
// ---------------------------------------------------------------------------
void FrmInfoDiretorio_Mostrar() 
{    
	gtk_window_set_position (GTK_WINDOW(FrmInfoDiretorio.frmInfoDiretorio), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_dialog_run(GTK_DIALOG (FrmInfoDiretorio.frmInfoDiretorio));
	//gtk_widget_destroy(FrmInfoDiretorio.frmInfoDiretorio);
}
// ---------------------------------------------------------------------------
void on_FrmInfoDiretorio_destroy(GtkWidget* widget, gpointer user_data) {
	
}
// ---------------------------------------------------------------------------
void on_btnOk_clicked(GtkWidget* widget, gpointer user_data){
	gtk_widget_destroy(FrmInfoDiretorio.frmInfoDiretorio);
}

void FrmInfoDiretorio_ConstruirGrid() {
	FrmInfoDiretorio.store = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_STRING);
	FrmInfoDiretorio.modelo = GTK_TREE_MODEL(FrmInfoDiretorio.store);
	gtk_tree_view_set_model(GTK_TREE_VIEW(FrmInfoDiretorio.tabelaInfo), FrmInfoDiretorio.modelo);

	FrmInfoDiretorio.selecao = gtk_tree_view_get_selection(GTK_TREE_VIEW(FrmInfoDiretorio.tabelaInfo));
	gtk_tree_selection_set_mode(FrmInfoDiretorio.selecao, GTK_SELECTION_SINGLE);
	gtk_tree_view_columns_autosize(GTK_TREE_VIEW(FrmInfoDiretorio.tabelaInfo));

}

void FrmInfoDiretorio_setDiretorio(Diretorio diretorio) {
	GtkTreeIter iter;

	if (diretorio != NULL) {
		gtk_list_store_append(FrmInfoDiretorio.store, &iter);
		gtk_list_store_set(FrmInfoDiretorio.store, &iter, 0, "Aba:", 1, diretorio->aba->nome->str, -1);
		gtk_list_store_append(FrmInfoDiretorio.store, &iter);
		gtk_list_store_set(FrmInfoDiretorio.store, &iter, 0, "Nome:", 1, diretorio->arquivo->nome->str, -1);
		gtk_list_store_append(FrmInfoDiretorio.store, &iter);
		gtk_list_store_set(FrmInfoDiretorio.store, &iter, 0, "Tamanho:", 1, diretorio->tamanhoFormatado->str, -1);
		gtk_list_store_append(FrmInfoDiretorio.store, &iter);
		gtk_list_store_set(FrmInfoDiretorio.store, &iter, 0, "Tipo:", 1, diretorio->tipo->nome->str, -1);
		gtk_list_store_append(FrmInfoDiretorio.store, &iter);
		gtk_list_store_set(FrmInfoDiretorio.store, &iter, 0, "Modificado:", 1, diretorio->modificadoFormatado->str, -1);
		gtk_list_store_append(FrmInfoDiretorio.store, &iter);
		gtk_list_store_set(FrmInfoDiretorio.store, &iter, 0, "Atributos:", 1, diretorio->arquivo->atributos->str, -1);
		gtk_list_store_append(FrmInfoDiretorio.store, &iter);
		gtk_list_store_set(FrmInfoDiretorio.store, &iter, 0, "Caminho:", 1, diretorio->caminho->str, -1);
	}
}