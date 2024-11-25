#include "FrmCadExtensao.h"

#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/catalogador/Catalogador.h"
#include "hfsguardadir/objetos/Extensao.h"
#include "hfsguardadir/objetosbo/ExtensaoBO.h"
#include "hfsguardadir/objetosgui/EscolhaArquivo.h"
#include "hfsguardadir/objetosgui/Dialogo.h"

struct SFrmCadExtensao FrmCadExtensao;
// ---------------------------------------------------------------------------
GtkWidget *FrmCadExtensao_Criar()
{
	FrmCadExtensao.frmCadExtensao = gtk_dialog_new();

	FrmCadExtensao.btnExcluir = gtk_button_new();
	gtk_widget_set_name(GTK_WIDGET(FrmCadExtensao.btnExcluir), "btnExcluir");
	gtk_button_set_label(GTK_BUTTON(FrmCadExtensao.btnExcluir), "Excluir");
	gtk_widget_set_visible(FrmCadExtensao.btnExcluir, TRUE);
	gtk_widget_set_can_focus(FrmCadExtensao.btnExcluir, TRUE);
	gtk_widget_set_receives_default(FrmCadExtensao.btnExcluir, TRUE);
	gtk_widget_set_margin_top(GTK_WIDGET(FrmCadExtensao.btnExcluir), 10);
	gtk_widget_set_margin_bottom(GTK_WIDGET(FrmCadExtensao.btnExcluir), 10);
	gtk_widget_set_margin_start(GTK_WIDGET(FrmCadExtensao.btnExcluir), 2);

	FrmCadExtensao.btnIncluir = gtk_button_new();
	gtk_widget_set_name(GTK_WIDGET(FrmCadExtensao.btnIncluir), "btnIncluir");
	gtk_button_set_label(GTK_BUTTON(FrmCadExtensao.btnIncluir), "Incluir");
	gtk_widget_set_visible(FrmCadExtensao.btnIncluir, TRUE);
	gtk_widget_set_can_focus(FrmCadExtensao.btnIncluir, TRUE);
	gtk_widget_set_receives_default(FrmCadExtensao.btnIncluir, TRUE);
	gtk_widget_set_margin_top(GTK_WIDGET(FrmCadExtensao.btnIncluir), 10);
	gtk_widget_set_margin_bottom(GTK_WIDGET(FrmCadExtensao.btnIncluir), 10);
	gtk_widget_set_margin_end(GTK_WIDGET(FrmCadExtensao.btnIncluir), 2);

	FrmCadExtensao.form_area = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_widget_set_name(GTK_WIDGET(FrmCadExtensao.form_area), "form_area");
	gtk_widget_set_visible(FrmCadExtensao.form_area, TRUE);
	gtk_widget_set_can_focus(FrmCadExtensao.form_area, FALSE);
	gtk_button_box_set_layout(GTK_BUTTON_BOX(FrmCadExtensao.form_area), GTK_BUTTONBOX_CENTER);
	gtk_container_add(GTK_CONTAINER(FrmCadExtensao.form_area), FrmCadExtensao.btnIncluir);
	gtk_box_set_child_packing(GTK_BOX(FrmCadExtensao.form_area), FrmCadExtensao.btnIncluir, FALSE, FALSE, 0, GTK_PACK_START);
	gtk_container_add(GTK_CONTAINER(FrmCadExtensao.form_area), FrmCadExtensao.btnExcluir);
	gtk_box_set_child_packing(GTK_BOX(FrmCadExtensao.form_area), FrmCadExtensao.btnExcluir, FALSE, FALSE, 0, GTK_PACK_START);

	FrmCadExtensao.colunaCadExtIcone = gtk_tree_view_column_new_with_attributes(Rotinas_retUTF8("Ícone"), gtk_cell_renderer_pixbuf_new(), "pixbuf", 1, NULL);
	gtk_tree_view_column_set_min_width(FrmCadExtensao.colunaCadExtIcone, 100);
	gtk_tree_view_column_set_title(FrmCadExtensao.colunaCadExtIcone, Rotinas_retUTF8("Ícone"));

	FrmCadExtensao.colunaCadExtExtensao = gtk_tree_view_column_new_with_attributes(Rotinas_retUTF8("Extensão"), gtk_cell_renderer_text_new(), "text", 0, NULL);
	gtk_tree_view_column_set_min_width(FrmCadExtensao.colunaCadExtExtensao, 150);
	gtk_tree_view_column_set_title(FrmCadExtensao.colunaCadExtExtensao, Rotinas_retUTF8("Extensão"));

	FrmCadExtensao.tabelaExtensao = gtk_tree_view_new();
	gtk_widget_set_name(GTK_WIDGET(FrmCadExtensao.tabelaExtensao), "tabelaExtensao");
	gtk_widget_set_visible(FrmCadExtensao.tabelaExtensao, TRUE);
	gtk_widget_set_can_focus(FrmCadExtensao.tabelaExtensao, TRUE);

	gtk_tree_view_append_column(GTK_TREE_VIEW(FrmCadExtensao.tabelaExtensao), FrmCadExtensao.colunaCadExtExtensao);
	gtk_tree_view_append_column(GTK_TREE_VIEW(FrmCadExtensao.tabelaExtensao), FrmCadExtensao.colunaCadExtIcone);

	FrmCadExtensao.store = gtk_list_store_new(2, G_TYPE_STRING, GDK_TYPE_PIXBUF);
	FrmCadExtensao.modelo = GTK_TREE_MODEL(FrmCadExtensao.store);
	gtk_tree_view_set_model(GTK_TREE_VIEW(FrmCadExtensao.tabelaExtensao), FrmCadExtensao.modelo);

	FrmCadExtensao.selecao = gtk_tree_view_get_selection(GTK_TREE_VIEW(FrmCadExtensao.tabelaExtensao));
	gtk_tree_selection_set_mode(FrmCadExtensao.selecao, GTK_SELECTION_SINGLE);

	FrmCadExtensao.scrollTabela = gtk_scrolled_window_new(NULL, NULL);
	gtk_widget_set_name(GTK_WIDGET(FrmCadExtensao.scrollTabela), "scrollTabela");
	gtk_widget_set_visible(FrmCadExtensao.scrollTabela, TRUE);
	gtk_widget_set_can_focus(FrmCadExtensao.scrollTabela, TRUE);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(FrmCadExtensao.scrollTabela), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_widget_set_vexpand(FrmCadExtensao.scrollTabela, TRUE);
	gtk_container_add(GTK_CONTAINER(FrmCadExtensao.scrollTabela), FrmCadExtensao.tabelaExtensao);

	FrmCadExtensao.menuExtrairIconesArquivos = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmCadExtensao.menuExtrairIconesArquivos), "menuExtrairIconesArquivos");
	gtk_widget_set_visible(FrmCadExtensao.menuExtrairIconesArquivos, TRUE);
	gtk_widget_set_can_focus(FrmCadExtensao.menuExtrairIconesArquivos, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmCadExtensao.menuExtrairIconesArquivos), Rotinas_retUTF8("Extrair Ícones dos Arquivos"));
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmCadExtensao.menuExtrairIconesArquivos), TRUE);

	FrmCadExtensao.menuImportarIconesArquivos = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmCadExtensao.menuImportarIconesArquivos), "menuImportarIconesArquivos");
	gtk_widget_set_visible(FrmCadExtensao.menuImportarIconesArquivos, TRUE);
	gtk_widget_set_can_focus(FrmCadExtensao.menuImportarIconesArquivos, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmCadExtensao.menuImportarIconesArquivos), Rotinas_retUTF8("Importar Ícones dos Arquivos"));
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmCadExtensao.menuImportarIconesArquivos), TRUE);

	FrmCadExtensao.submenuImportarTodos = gtk_menu_new();
	gtk_widget_set_name(GTK_WIDGET(FrmCadExtensao.submenuImportarTodos), "submenuImportarTodos");
	gtk_widget_set_visible(FrmCadExtensao.submenuImportarTodos, TRUE);
	gtk_widget_set_can_focus(FrmCadExtensao.submenuImportarTodos, FALSE);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmCadExtensao.submenuImportarTodos), FrmCadExtensao.menuImportarIconesArquivos);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmCadExtensao.submenuImportarTodos), FrmCadExtensao.menuExtrairIconesArquivos);

	FrmCadExtensao.menuImportarTodos = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmCadExtensao.menuImportarTodos), "menuImportarTodos");
	gtk_widget_set_visible(FrmCadExtensao.menuImportarTodos, TRUE);
	gtk_widget_set_can_focus(FrmCadExtensao.menuImportarTodos, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmCadExtensao.menuImportarTodos), "Importar Todos");
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmCadExtensao.menuImportarTodos), TRUE);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(FrmCadExtensao.menuImportarTodos), FrmCadExtensao.submenuImportarTodos);

	FrmCadExtensao.menuExportarTIFF = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmCadExtensao.menuExportarTIFF), "menuExportarTIFF");
	gtk_widget_set_visible(FrmCadExtensao.menuExportarTIFF, TRUE);
	gtk_widget_set_can_focus(FrmCadExtensao.menuExportarTIFF, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmCadExtensao.menuExportarTIFF), "Exportar para TIFF");
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmCadExtensao.menuExportarTIFF), TRUE);

	FrmCadExtensao.menuExportarPNG = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmCadExtensao.menuExportarPNG), "menuExportarPNG");
	gtk_widget_set_visible(FrmCadExtensao.menuExportarPNG, TRUE);
	gtk_widget_set_can_focus(FrmCadExtensao.menuExportarPNG, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmCadExtensao.menuExportarPNG), "Exportar para PNG");
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmCadExtensao.menuExportarPNG), TRUE);

	FrmCadExtensao.menuExportarJPEG = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmCadExtensao.menuExportarJPEG), "menuExportarJPEG");
	gtk_widget_set_visible(FrmCadExtensao.menuExportarJPEG, TRUE);
	gtk_widget_set_can_focus(FrmCadExtensao.menuExportarJPEG, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmCadExtensao.menuExportarJPEG), "Exportar para JPEG");
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmCadExtensao.menuExportarJPEG), TRUE);

	FrmCadExtensao.menuExportarGIF = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmCadExtensao.menuExportarGIF), "menuExportarGIF");
	gtk_widget_set_visible(FrmCadExtensao.menuExportarGIF, TRUE);
	gtk_widget_set_can_focus(FrmCadExtensao.menuExportarGIF, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmCadExtensao.menuExportarGIF), "Exportar para GIF");
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmCadExtensao.menuExportarGIF), TRUE);

	FrmCadExtensao.menuExportarIcone = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmCadExtensao.menuExportarIcone), "menuExportarIcone");
	gtk_widget_set_visible(FrmCadExtensao.menuExportarIcone, TRUE);
	gtk_widget_set_can_focus(FrmCadExtensao.menuExportarIcone, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmCadExtensao.menuExportarIcone), Rotinas_retUTF8("Exportar para Ícone"));
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmCadExtensao.menuExportarIcone), TRUE);

	FrmCadExtensao.menuExportarBitmap = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmCadExtensao.menuExportarBitmap), "menuExportarBitmap");
	gtk_widget_set_visible(FrmCadExtensao.menuExportarBitmap, TRUE);
	gtk_widget_set_can_focus(FrmCadExtensao.menuExportarBitmap, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmCadExtensao.menuExportarBitmap), "Exportar para Bitmap");
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmCadExtensao.menuExportarBitmap), TRUE);

	FrmCadExtensao.submenuExportarTodos = gtk_menu_new();
	gtk_widget_set_name(GTK_WIDGET(FrmCadExtensao.submenuExportarTodos), "submenuExportarTodos");
	gtk_widget_set_visible(FrmCadExtensao.submenuExportarTodos, TRUE);
	gtk_widget_set_can_focus(FrmCadExtensao.submenuExportarTodos, FALSE);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmCadExtensao.submenuExportarTodos), FrmCadExtensao.menuExportarBitmap);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmCadExtensao.submenuExportarTodos), FrmCadExtensao.menuExportarIcone);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmCadExtensao.submenuExportarTodos), FrmCadExtensao.menuExportarGIF);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmCadExtensao.submenuExportarTodos), FrmCadExtensao.menuExportarJPEG);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmCadExtensao.submenuExportarTodos), FrmCadExtensao.menuExportarPNG);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmCadExtensao.submenuExportarTodos), FrmCadExtensao.menuExportarTIFF);

	FrmCadExtensao.menuExportarTodos = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmCadExtensao.menuExportarTodos), "menuExportarTodos");
	gtk_widget_set_visible(FrmCadExtensao.menuExportarTodos, TRUE);
	gtk_widget_set_can_focus(FrmCadExtensao.menuExportarTodos, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmCadExtensao.menuExportarTodos), "Exportar Todos");
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmCadExtensao.menuExportarTodos), TRUE);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(FrmCadExtensao.menuExportarTodos), FrmCadExtensao.submenuExportarTodos);

	FrmCadExtensao.menuExcluirTodasExtensoes = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmCadExtensao.menuExcluirTodasExtensoes), "menuExcluirTodasExtensoes");
	gtk_widget_set_visible(FrmCadExtensao.menuExcluirTodasExtensoes, TRUE);
	gtk_widget_set_can_focus(FrmCadExtensao.menuExcluirTodasExtensoes, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmCadExtensao.menuExcluirTodasExtensoes), Rotinas_retUTF8("Excluir Todas Extensões"));
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmCadExtensao.menuExcluirTodasExtensoes), TRUE);

	FrmCadExtensao.menuExcluirExtensao = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmCadExtensao.menuExcluirExtensao), "menuExcluirExtensao");
	gtk_widget_set_visible(FrmCadExtensao.menuExcluirExtensao, TRUE);
	gtk_widget_set_can_focus(FrmCadExtensao.menuExcluirExtensao, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmCadExtensao.menuExcluirExtensao), Rotinas_retUTF8("Excluir Extensão"));
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmCadExtensao.menuExcluirExtensao), TRUE);

	FrmCadExtensao.menuIncluirExtensao = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmCadExtensao.menuIncluirExtensao), "menuIncluirExtensao");
	gtk_widget_set_visible(FrmCadExtensao.menuIncluirExtensao, TRUE);
	gtk_widget_set_can_focus(FrmCadExtensao.menuIncluirExtensao, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmCadExtensao.menuIncluirExtensao), Rotinas_retUTF8("Incluir Extensão"));
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmCadExtensao.menuIncluirExtensao), TRUE);

	FrmCadExtensao.submenuExtensao = gtk_menu_new();
	gtk_widget_set_name(GTK_WIDGET(FrmCadExtensao.submenuExtensao), "submenuExtensao");
	gtk_widget_set_visible(FrmCadExtensao.submenuExtensao, TRUE);
	gtk_widget_set_can_focus(FrmCadExtensao.submenuExtensao, FALSE);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmCadExtensao.submenuExtensao), FrmCadExtensao.menuIncluirExtensao);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmCadExtensao.submenuExtensao), FrmCadExtensao.menuExcluirExtensao);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmCadExtensao.submenuExtensao), FrmCadExtensao.menuExcluirTodasExtensoes);

	FrmCadExtensao.menuExtensao = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmCadExtensao.menuExtensao), "menuExtensao");
	gtk_widget_set_visible(FrmCadExtensao.menuExtensao, TRUE);
	gtk_widget_set_can_focus(FrmCadExtensao.menuExtensao, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmCadExtensao.menuExtensao), Rotinas_retUTF8("_Extensão"));
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmCadExtensao.menuExtensao), TRUE);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(FrmCadExtensao.menuExtensao), FrmCadExtensao.submenuExtensao);

	FrmCadExtensao.barraMenu = gtk_menu_bar_new();
	gtk_widget_set_name(GTK_WIDGET(FrmCadExtensao.barraMenu), "barraMenu");
	gtk_widget_set_visible(FrmCadExtensao.barraMenu, TRUE);
	gtk_widget_set_can_focus(FrmCadExtensao.barraMenu, FALSE);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmCadExtensao.barraMenu), FrmCadExtensao.menuExtensao);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmCadExtensao.barraMenu), FrmCadExtensao.menuExportarTodos);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmCadExtensao.barraMenu), FrmCadExtensao.menuImportarTodos);

	FrmCadExtensao.vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_name(GTK_WIDGET(FrmCadExtensao.vbox), "vbox");
	gtk_widget_set_visible(FrmCadExtensao.vbox, TRUE);
	gtk_widget_set_can_focus(FrmCadExtensao.vbox, FALSE);
	gtk_container_add(GTK_CONTAINER(FrmCadExtensao.vbox), FrmCadExtensao.barraMenu);
	gtk_box_set_child_packing(GTK_BOX(FrmCadExtensao.vbox), FrmCadExtensao.barraMenu, FALSE, TRUE, 0, GTK_PACK_START);
	gtk_container_add(GTK_CONTAINER(FrmCadExtensao.vbox), FrmCadExtensao.scrollTabela);
	gtk_box_set_child_packing(GTK_BOX(FrmCadExtensao.vbox), FrmCadExtensao.scrollTabela, TRUE, TRUE, 0, GTK_PACK_START);

	FrmCadExtensao.form_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
	gtk_widget_set_name(GTK_WIDGET(FrmCadExtensao.form_vbox), "form_vbox");
	gtk_widget_set_visible(FrmCadExtensao.form_vbox, TRUE);
	gtk_widget_set_can_focus(FrmCadExtensao.form_vbox, FALSE);
	gtk_box_set_spacing(GTK_BOX(FrmCadExtensao.form_vbox), 2);
	gtk_container_add(GTK_CONTAINER(FrmCadExtensao.form_vbox), FrmCadExtensao.vbox);
	gtk_box_set_child_packing(GTK_BOX(FrmCadExtensao.form_vbox), FrmCadExtensao.vbox, TRUE, TRUE, 0, GTK_PACK_START);
	gtk_container_add(GTK_CONTAINER(FrmCadExtensao.form_vbox), FrmCadExtensao.form_area);
	gtk_box_set_child_packing(GTK_BOX(FrmCadExtensao.form_vbox), FrmCadExtensao.form_area, FALSE, TRUE, 0, GTK_PACK_START);

	gtk_widget_set_name(FrmCadExtensao.frmCadExtensao, "frmCadExtensao");
	gtk_widget_set_size_request(FrmCadExtensao.frmCadExtensao, 286, 418);
	gtk_widget_set_can_focus(FrmCadExtensao.frmCadExtensao, FALSE);
	gtk_container_set_border_width(GTK_CONTAINER(FrmCadExtensao.frmCadExtensao), 5);
	gtk_window_set_title(GTK_WINDOW(FrmCadExtensao.frmCadExtensao), Rotinas_retUTF8("Cadastro de Extensão de Arquivo"));
	gtk_window_set_resizable(GTK_WINDOW(FrmCadExtensao.frmCadExtensao), FALSE);
	gtk_window_set_modal(GTK_WINDOW(FrmCadExtensao.frmCadExtensao), TRUE);
	gtk_window_set_position(GTK_WINDOW(FrmCadExtensao.frmCadExtensao), GTK_WIN_POS_CENTER);
	gtk_window_set_type_hint(GTK_WINDOW(FrmCadExtensao.frmCadExtensao), GDK_WINDOW_TYPE_HINT_DIALOG);
	GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(FrmCadExtensao.frmCadExtensao));
	gtk_container_add(GTK_CONTAINER(content_area), GTK_WIDGET(FrmCadExtensao.form_vbox));

	g_signal_connect(FrmCadExtensao.menuIncluirExtensao, "activate", G_CALLBACK(on_menuIncluirExtensao_activate), NULL);
	g_signal_connect(FrmCadExtensao.menuExcluirExtensao, "activate", G_CALLBACK(on_menuExcluirExtensao_activate), NULL);
	g_signal_connect(FrmCadExtensao.menuExcluirTodasExtensoes, "activate", G_CALLBACK(on_menuExcluirTodasExtensoes_activate), NULL);
	g_signal_connect(FrmCadExtensao.menuExportarBitmap, "activate", G_CALLBACK(on_menuExportarBitmap_activate), NULL);
	g_signal_connect(FrmCadExtensao.menuExportarIcone, "activate", G_CALLBACK(on_menuExportarIcone_activate), NULL);
	g_signal_connect(FrmCadExtensao.menuExportarGIF, "activate", G_CALLBACK(on_menuExportarGIF_activate), NULL);
	g_signal_connect(FrmCadExtensao.menuExportarJPEG, "activate", G_CALLBACK(on_menuExportarJPEG_activate), NULL);
	g_signal_connect(FrmCadExtensao.menuExportarPNG, "activate", G_CALLBACK(on_menuExportarPNG_activate), NULL);
	g_signal_connect(FrmCadExtensao.menuExportarTIFF, "activate", G_CALLBACK(on_menuExportarTIFF_activate), NULL);
	g_signal_connect(FrmCadExtensao.menuImportarIconesArquivos, "activate", G_CALLBACK(on_menuImportarIconesArquivos_activate), NULL);
	g_signal_connect(FrmCadExtensao.menuExtrairIconesArquivos, "activate", G_CALLBACK(on_menuExtrairIconesArquivos_activate), NULL);
	g_signal_connect(FrmCadExtensao.btnIncluir, "clicked", G_CALLBACK(on_btnIncluir_clicked), NULL);
	g_signal_connect(FrmCadExtensao.btnExcluir, "clicked", G_CALLBACK(on_btnExcluir_clicked), NULL);


	g_signal_connect (FrmCadExtensao.frmCadExtensao, "destroy",
		G_CALLBACK (on_FrmCadExtensao_destroy), NULL);

	FrmCadExtensao_CarregarExtensoesNaGrid();

	return FrmCadExtensao.frmCadExtensao;
}
// ---------------------------------------------------------------------------
void FrmCadExtensao_Mostrar()
{
    FrmCadExtensao.frmCadExtensao = FrmCadExtensao_Criar();
	gtk_window_set_position (GTK_WINDOW(FrmCadExtensao.frmCadExtensao), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_dialog_run(GTK_DIALOG (FrmCadExtensao.frmCadExtensao));
	gtk_widget_destroy(FrmCadExtensao.frmCadExtensao);
}
// ---------------------------------------------------------------------------
void on_FrmCadExtensao_destroy(GtkWidget* widget, gpointer user_data) {

}
// ---------------------------------------------------------------------------

void FrmCadExtensao_CarregarExtensoesNaGrid() {
	GtkTreeModel* tabela_modelo = gtk_tree_view_get_model(GTK_TREE_VIEW(FrmCadExtensao.tabelaExtensao));
	GtkListStore* tabela_store = GTK_LIST_STORE(tabela_modelo);
	guint tamlista = ListaExtensao_conta(Catalogador.listaExtensoes);
	Extensao extensao = Extensao_new();
	GtkTreeIter iter;

	gtk_list_store_clear(tabela_store);

	for (unsigned int i = 0; i < tamlista; i++) {
		extensao = ListaExtensao_pesquisaItemOrd(Catalogador.listaExtensoes, i);

		gtk_list_store_append(tabela_store, &iter);
		gtk_list_store_set(tabela_store, &iter, 0, extensao->nome->str, 1, extensao->bmp16, -1);
		//gtk_list_store_set(tabela_store, &iter, 0, extensao->nome->str, 1, ExtensaoBO_ArquivoXPM, -1);
	}

}

void on_menuIncluirExtensao_activate(GtkWidget* widget, gpointer user_data){
	ListaString log;

	GString* arquivo = EscolhaArquivo_abrirArquivo(
		FrmCadExtensao.frmCadExtensao, EscolhaArquivo_FILTRO_IMAGEM);

	if (arquivo->len > 0) {
		//FileInfo arquivo = new FileInfo(EscolhaArquivo.NomeArquivo);
		if (Rotinas_FileExists(arquivo)) {
			log = ListaString_inicia();

			if (ExtensaoBO_SalvarExtensao(
				Catalogador.listaExtensoes, arquivo, arquivo, log)) {

				FrmCadExtensao_CarregarExtensoesNaGrid();

				Dialogo_mensagemInfo(FrmCadExtensao.frmCadExtensao,
					"FrmCadExtensao.ExtensaoSalvaSucesso");
			}
			else {
				Dialogo_mensagemInfo(FrmCadExtensao.frmCadExtensao,
					"FrmCadExtensao.ExtensaoJaCadastrada");
			}
		}
	}
}

void on_menuExcluirExtensao_activate(GtkWidget* widget, gpointer user_data){
	Extensao extensao = Extensao_new();
	guint tamlista = ListaExtensao_conta(Catalogador.listaExtensoes);
	GtkTreeModel* tabela_modelo = gtk_tree_view_get_model(GTK_TREE_VIEW(FrmCadExtensao.tabelaExtensao));
	GtkTreeSelection *tabela_selecao = gtk_tree_view_get_selection(
		GTK_TREE_VIEW(FrmCadExtensao.tabelaExtensao));

	if (tamlista > 0) {
		gboolean res = Dialogo_confirma(FrmCadExtensao.frmCadExtensao,
			"FrmCadExtensao.ExtensaoCertezaExcluir");
		if (res) {
			GList* linhas = gtk_tree_selection_get_selected_rows(tabela_selecao, &tabela_modelo);
			GtkTreePath* path = g_list_nth_data(linhas, 0);
			gint* indices = gtk_tree_path_get_indices(path);

			extensao = ExtensaoBO_pegaExtensaoPorOrdem(
				Catalogador.listaExtensoes, indices[0] + 1);

			if (ExtensaoBO_excluirExtensao(
				Catalogador.listaExtensoes, extensao->codigo)) {
				FrmCadExtensao_CarregarExtensoesNaGrid();
				Dialogo_mensagemInfo(FrmCadExtensao.frmCadExtensao,
					"FrmCadExtensao.ExtensaoExcluidaSucesso");
			}
		}
	}
}

void on_menuExcluirTodasExtensoes_activate(GtkWidget* widget, gpointer user_data){
	gboolean res = Dialogo_confirma(FrmCadExtensao.frmCadExtensao,
		"FrmCadExtensao.ExtensaoCertezaTodosExcluir");
	if (res) {
		if (ExtensaoBO_excluirTodasExtensoes(Catalogador.listaExtensoes)) {
			FrmCadExtensao_CarregarExtensoesNaGrid();
			Dialogo_mensagemInfo(FrmCadExtensao.frmCadExtensao,
				"FrmCadExtensao.ExtensoesExcluidasSucesso");
		}
	}
}

void on_menuExportarBitmap_activate(GtkWidget* widget, gpointer user_data){
	ExtensaoBO_ExportarExtensao(teBMP, Catalogador.listaExtensoes);
}

void on_menuExportarIcone_activate(GtkWidget* widget, gpointer user_data){
	ExtensaoBO_ExportarExtensao(teICO, Catalogador.listaExtensoes);
}

void on_menuExportarGIF_activate(GtkWidget* widget, gpointer user_data){
	ExtensaoBO_ExportarExtensao(teGIF, Catalogador.listaExtensoes);
}

void on_menuExportarJPEG_activate(GtkWidget* widget, gpointer user_data){
	ExtensaoBO_ExportarExtensao(teJPG, Catalogador.listaExtensoes);
}

void on_menuExportarPNG_activate(GtkWidget* widget, gpointer user_data){
	ExtensaoBO_ExportarExtensao(tePNG, Catalogador.listaExtensoes);
}

void on_menuExportarTIFF_activate(GtkWidget* widget, gpointer user_data){
	ExtensaoBO_ExportarExtensao(teTIF, Catalogador.listaExtensoes);
}

void on_menuImportarIconesArquivos_activate(GtkWidget* widget, gpointer user_data){
	GString* arquivo = EscolhaArquivo_abrirArquivo(FrmCadExtensao.frmCadExtensao,
		EscolhaArquivo_FILTRO_IMAGEM);

	if (arquivo->len > 0) {
		//FileInfo arquivo = new FileInfo(EscolhaArquivo.NomeArquivo);
		if (Rotinas_FileExists(arquivo)) {
			ExtensaoBO_ImportarExtensao(arquivo, Catalogador.listaExtensoes);
			FrmCadExtensao_CarregarExtensoesNaGrid();
		}
	}
}

void on_menuExtrairIconesArquivos_activate(GtkWidget* widget, gpointer user_data){
	GString* arquivo = EscolhaArquivo_abrirArquivo(FrmCadExtensao.frmCadExtensao,
		EscolhaArquivo_FILTRO_IMAGEM);

	if (arquivo->len > 0) {
		//FileInfo arquivo = new FileInfo(EscolhaArquivo.NomeArquivo);
		if (Rotinas_FileExists(arquivo)) {
			ExtensaoBO_ExtrairExtensao(arquivo, Catalogador.listaExtensoes);
			FrmCadExtensao_CarregarExtensoesNaGrid();
		}
	}
}

void on_btnIncluir_clicked(GtkWidget* widget, gpointer user_data){
	on_menuIncluirExtensao_activate(widget, user_data);
}

void on_btnExcluir_clicked(GtkWidget* widget, gpointer user_data){
	on_menuExcluirExtensao_activate(widget, user_data);
}


// ---------------------------------------------------------------------------
