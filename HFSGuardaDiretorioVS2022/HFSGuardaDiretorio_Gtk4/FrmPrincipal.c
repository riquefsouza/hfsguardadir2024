#include "FrmPrincipal.h"
#include "hfsguardadir/comum/Rotinas.h"

//#include "FrmCadExtensao.h"
//#include "FrmCompararDiretorio.h"
//#include "FrmImportarDiretorio.h"
//#include "FrmInfoDiretorio.h"
#include "FrmSobre.h"
#include "hfsguardadir/catalogador/Catalogador.h"
#include "hfsguardadir/objetosbo/ExtensaoBO.h"

G_GNUC_BEGIN_IGNORE_DEPRECATIONS

struct SFrmPrincipal FrmPrincipal;
// ---------------------------------------------------------------------------
GtkWidget *FrmPrincipal_Criar(GtkApplication* app)
{
	FrmPrincipal.frmPrincipal = gtk_application_window_new(app);
	gtk_widget_set_name(FrmPrincipal.frmPrincipal, "frmPrincipal");
	gtk_widget_set_size_request(FrmPrincipal.frmPrincipal, 1200, 800);
	gtk_widget_set_visible(FrmPrincipal.frmPrincipal, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.frmPrincipal, FALSE);
	gtk_window_set_title(GTK_WINDOW(FrmPrincipal.frmPrincipal),
		Rotinas_retUTF8("HFSGuardaDiretorio 2.0 - Catalogador de Diretórios"));
	gtk_window_set_default_size(GTK_WINDOW(FrmPrincipal.frmPrincipal), 1200, 800);

	FrmPrincipal.barraStatus211 = gtk_label_new("barraStatus2");
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.barraStatus211), "barraStatus211");
	gtk_widget_set_visible(FrmPrincipal.barraStatus211, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.barraStatus211, FALSE);
	
	//GtkWidget* frameStatus2 = gtk_frame_new("status 2");
	//gtk_widget_set_hexpand(GTK_WIDGET(frameStatus2), TRUE);
	GtkWidget* hboxStatus2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_widget_set_hexpand(GTK_WIDGET(hboxStatus2), TRUE);
	//gtk_frame_set_child(GTK_FRAME(frameStatus2), GTK_WIDGET(hboxStatus2));
	gtk_box_append(GTK_BOX(hboxStatus2), GTK_WIDGET(FrmPrincipal.barraStatus211));

	FrmPrincipal.barraStatus111 = gtk_label_new("barraStatus1");
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.barraStatus111), "barraStatus111");
	gtk_widget_set_visible(FrmPrincipal.barraStatus111, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.barraStatus111, FALSE);

	//GtkWidget* frameStatus1 = gtk_frame_new("status 1");
	//gtk_widget_set_size_request(frameStatus1, 300, -1);
	GtkWidget* hboxStatus1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_widget_set_size_request(hboxStatus1, 300, -1);
	//gtk_frame_set_child(GTK_FRAME(frameStatus1), GTK_WIDGET(hboxStatus1));
	gtk_box_append(GTK_BOX(hboxStatus1), GTK_WIDGET(FrmPrincipal.barraStatus111));

	FrmPrincipal.hbox6 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 8);
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.hbox6), "hbox6");
	gtk_widget_set_visible(FrmPrincipal.hbox6, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.hbox6, FALSE);
	gtk_box_append(GTK_BOX(FrmPrincipal.hbox6), GTK_WIDGET(hboxStatus1));
	gtk_box_append(GTK_BOX(FrmPrincipal.hbox6), GTK_WIDGET(hboxStatus2));

	//FrmPrincipal.tabelaPesquisa = gtk_column_view_new(NULL);
	FrmPrincipal.tabelaPesquisa = gtk_tree_view_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.tabelaPesquisa), "tabelaPesquisa");
	gtk_widget_set_visible(FrmPrincipal.tabelaPesquisa, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.tabelaPesquisa, TRUE);

	FrmPrincipal.scrollPesquisa = gtk_scrolled_window_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.scrollPesquisa), "scrollPesquisa");
	gtk_widget_set_visible(FrmPrincipal.scrollPesquisa, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.scrollPesquisa, TRUE);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(FrmPrincipal.scrollPesquisa), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(FrmPrincipal.scrollPesquisa), FrmPrincipal.tabelaPesquisa);
	gtk_scrolled_window_set_has_frame(GTK_SCROLLED_WINDOW(FrmPrincipal.scrollPesquisa), TRUE);

	//FrmPrincipal.tabelaFixa = gtk_column_view_new(NULL);
	FrmPrincipal.tabelaFixa = gtk_tree_view_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.tabelaFixa), "tabelaFixa");
	gtk_widget_set_visible(FrmPrincipal.tabelaFixa, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.tabelaFixa, TRUE);

	FrmPrincipal.scrollTabelaFixa = gtk_scrolled_window_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.scrollTabelaFixa), "scrollTabelaFixa");
	gtk_widget_set_visible(FrmPrincipal.scrollTabelaFixa, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.scrollTabelaFixa, TRUE);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(FrmPrincipal.scrollTabelaFixa), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(FrmPrincipal.scrollTabelaFixa), FrmPrincipal.tabelaFixa);
	gtk_scrolled_window_set_has_frame(GTK_SCROLLED_WINDOW(FrmPrincipal.scrollTabelaFixa), TRUE);

	//FrmPrincipal.arvoreFixa = gtk_list_view_new(NULL, NULL);
	FrmPrincipal.arvoreFixa = gtk_tree_view_new();
	gtk_widget_set_name(FrmPrincipal.arvoreFixa, "arvoreFixa");
	gtk_widget_set_visible(FrmPrincipal.arvoreFixa, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.arvoreFixa, TRUE);

	FrmPrincipal.scrollArvore = gtk_scrolled_window_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.scrollArvore), "scrollArvore");
	gtk_widget_set_visible(FrmPrincipal.scrollArvore, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.scrollArvore, TRUE);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(FrmPrincipal.scrollArvore), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(FrmPrincipal.scrollArvore), FrmPrincipal.arvoreFixa);
	gtk_scrolled_window_set_has_frame(GTK_SCROLLED_WINDOW(FrmPrincipal.scrollArvore), TRUE);

	FrmPrincipal.spPrincipal = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.spPrincipal), "spPrincipal");
	gtk_widget_set_visible(FrmPrincipal.spPrincipal, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.spPrincipal, TRUE);
	gtk_paned_set_position(GTK_PANED(FrmPrincipal.spPrincipal), 250);
	gtk_paned_set_start_child(GTK_PANED(FrmPrincipal.spPrincipal), FrmPrincipal.scrollArvore);
	gtk_paned_set_end_child(GTK_PANED(FrmPrincipal.spPrincipal), FrmPrincipal.scrollTabelaFixa);

	FrmPrincipal.notebook1 = gtk_notebook_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.notebook1), "notebook1");
	gtk_widget_set_visible(FrmPrincipal.notebook1, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.notebook1, TRUE);

	FrmPrincipal.spPesquisa = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.spPesquisa), "spPesquisa");
	gtk_widget_set_visible(FrmPrincipal.spPesquisa, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.spPesquisa, TRUE);
	gtk_paned_set_position(GTK_PANED(FrmPrincipal.spPesquisa), 250);

	gtk_widget_set_hexpand(FrmPrincipal.spPesquisa, TRUE);
	gtk_widget_set_vexpand(FrmPrincipal.spPesquisa, TRUE);

	gtk_paned_set_start_child(GTK_PANED(FrmPrincipal.spPesquisa), FrmPrincipal.notebook1);
	gtk_paned_set_end_child(GTK_PANED(FrmPrincipal.spPesquisa), FrmPrincipal.scrollPesquisa);

	FrmPrincipal.btnPesquisa = gtk_button_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.btnPesquisa), "btnPesquisa");
	gtk_button_set_label(GTK_BUTTON(FrmPrincipal.btnPesquisa), "Pesquisar");
	gtk_widget_set_visible(FrmPrincipal.btnPesquisa, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.btnPesquisa, TRUE);
	gtk_widget_set_receives_default(FrmPrincipal.btnPesquisa, FALSE);
	gtk_button_set_use_underline(GTK_BUTTON(FrmPrincipal.btnPesquisa), TRUE);

	FrmPrincipal.toolbar1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 8);
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.toolbar1), "toolbar1");
	gtk_widget_set_visible(FrmPrincipal.toolbar1, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.toolbar1, TRUE);		

	FrmPrincipal.btnImportarDiretorio = gtk_button_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.btnImportarDiretorio), "btnImportarDiretorio");
	gtk_button_set_label(GTK_BUTTON(FrmPrincipal.btnImportarDiretorio), Rotinas_retUTF8("Importar Diretório"));
	gtk_widget_set_visible(FrmPrincipal.btnImportarDiretorio, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.btnImportarDiretorio, FALSE);
	gtk_widget_set_receives_default(FrmPrincipal.btnImportarDiretorio, FALSE);
	gtk_button_set_use_underline(GTK_BUTTON(FrmPrincipal.btnImportarDiretorio), TRUE);

	FrmPrincipal.pbImportarDiretorio = gtk_progress_bar_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.pbImportarDiretorio), "pbImportarDiretorio");
	gtk_widget_set_size_request(FrmPrincipal.pbImportarDiretorio, 385, 30);	
	gtk_widget_set_visible(FrmPrincipal.pbImportarDiretorio, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.pbImportarDiretorio, FALSE);


	FrmPrincipal.edtPesquisa = gtk_entry_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.edtPesquisa), "edtPesquisa");
	gtk_entry_set_placeholder_text(GTK_ENTRY(FrmPrincipal.edtPesquisa), "digite o valor a ser pesquisado");
	gtk_widget_set_visible(FrmPrincipal.edtPesquisa, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.edtPesquisa, TRUE);
	gtk_widget_set_size_request(FrmPrincipal.edtPesquisa, 325, -1);
	gtk_entry_set_max_length(GTK_ENTRY(FrmPrincipal.edtPesquisa), 255);

	gtk_box_append(GTK_BOX(FrmPrincipal.toolbar1), FrmPrincipal.btnImportarDiretorio);
	gtk_box_append(GTK_BOX(FrmPrincipal.toolbar1), FrmPrincipal.pbImportarDiretorio);
	gtk_box_append(GTK_BOX(FrmPrincipal.toolbar1), FrmPrincipal.edtPesquisa);
	gtk_box_append(GTK_BOX(FrmPrincipal.toolbar1), FrmPrincipal.btnPesquisa);

	FrmPrincipal.actions = g_simple_action_group_new();

	FrmPrincipal.actionIncluirNovaAba = g_simple_action_new("actionIncluirNovaAba", NULL);
	FrmPrincipal.actionAlterarNomeAbaAtiva = g_simple_action_new("actionAlterarNomeAbaAtiva", NULL);
	FrmPrincipal.actionExcluirAbaAtiva = g_simple_action_new("actionExcluirAbaAtiva", NULL);
	g_action_map_add_action(G_ACTION_MAP(FrmPrincipal.actions), G_ACTION(FrmPrincipal.actionIncluirNovaAba));	
	g_action_map_add_action(G_ACTION_MAP(FrmPrincipal.actions), G_ACTION(FrmPrincipal.actionAlterarNomeAbaAtiva));	
	g_action_map_add_action(G_ACTION_MAP(FrmPrincipal.actions), G_ACTION(FrmPrincipal.actionExcluirAbaAtiva));

	FrmPrincipal.actionImportarDiretorio = g_simple_action_new("actionImportarDiretorio", NULL);
	FrmPrincipal.actionImportarSubDiretorios = g_simple_action_new("actionImportarSubDiretorios", NULL);
	FrmPrincipal.actionCompararDiretorios = g_simple_action_new("actionCompararDiretorios", NULL);
	FrmPrincipal.actionCadastrarExtensaoArquivo = g_simple_action_new("actionCadastrarExtensaoArquivo", NULL);
	FrmPrincipal.actionExpandirDiretorios = g_simple_action_new("actionExpandirDiretorios", NULL);
	FrmPrincipal.actionColapsarDiretorios = g_simple_action_new("actionColapsarDiretorios", NULL);
	//FrmPrincipal.actionExportarDiretoriosAbaAtiva = g_simple_action_new("actionExportarDiretoriosAbaAtiva", NULL);
	FrmPrincipal.actionTXT = g_simple_action_new("actionTXT", NULL);
	FrmPrincipal.actionCSV = g_simple_action_new("actionCSV", NULL);
	FrmPrincipal.actionHTML = g_simple_action_new("actionHTML", NULL);
	FrmPrincipal.actionXML = g_simple_action_new("actionXML", NULL);
	FrmPrincipal.actionSQL = g_simple_action_new("actionSQL", NULL);
	FrmPrincipal.actionImportarDiretoriosViaXML = g_simple_action_new("actionImportarDiretoriosViaXML", NULL);
	FrmPrincipal.actionGravarLogImportacao = g_simple_action_new("actionGravarLogImportacao", NULL);
	g_action_map_add_action(G_ACTION_MAP(FrmPrincipal.actions), G_ACTION(FrmPrincipal.actionImportarDiretorio));
	g_action_map_add_action(G_ACTION_MAP(FrmPrincipal.actions), G_ACTION(FrmPrincipal.actionImportarSubDiretorios));
	g_action_map_add_action(G_ACTION_MAP(FrmPrincipal.actions), G_ACTION(FrmPrincipal.actionCompararDiretorios));
	g_action_map_add_action(G_ACTION_MAP(FrmPrincipal.actions), G_ACTION(FrmPrincipal.actionCadastrarExtensaoArquivo));
	g_action_map_add_action(G_ACTION_MAP(FrmPrincipal.actions), G_ACTION(FrmPrincipal.actionExpandirDiretorios));
	g_action_map_add_action(G_ACTION_MAP(FrmPrincipal.actions), G_ACTION(FrmPrincipal.actionColapsarDiretorios));
	//g_action_map_add_action(G_ACTION_MAP(FrmPrincipal.actions), G_ACTION(FrmPrincipal.actionExportarDiretoriosAbaAtiva));
	g_action_map_add_action(G_ACTION_MAP(FrmPrincipal.actions), G_ACTION(FrmPrincipal.actionTXT));
	g_action_map_add_action(G_ACTION_MAP(FrmPrincipal.actions), G_ACTION(FrmPrincipal.actionCSV));
	g_action_map_add_action(G_ACTION_MAP(FrmPrincipal.actions), G_ACTION(FrmPrincipal.actionHTML));
	g_action_map_add_action(G_ACTION_MAP(FrmPrincipal.actions), G_ACTION(FrmPrincipal.actionXML));
	g_action_map_add_action(G_ACTION_MAP(FrmPrincipal.actions), G_ACTION(FrmPrincipal.actionSQL));
	g_action_map_add_action(G_ACTION_MAP(FrmPrincipal.actions), G_ACTION(FrmPrincipal.actionImportarDiretoriosViaXML));
	g_action_map_add_action(G_ACTION_MAP(FrmPrincipal.actions), G_ACTION(FrmPrincipal.actionGravarLogImportacao));

	FrmPrincipal.actionMostrarOcultarListaItensPesquisados = g_simple_action_new("actionMostrarOcultarListaItensPesquisados", NULL);
	FrmPrincipal.actionMostrarOcultarArvoreDirAbaAtiva = g_simple_action_new("actionMostrarOcultarArvoreDirAbaAtiva", NULL);
	g_action_map_add_action(G_ACTION_MAP(FrmPrincipal.actions), G_ACTION(FrmPrincipal.actionMostrarOcultarListaItensPesquisados));
	g_action_map_add_action(G_ACTION_MAP(FrmPrincipal.actions), G_ACTION(FrmPrincipal.actionMostrarOcultarArvoreDirAbaAtiva));
	
	FrmPrincipal.actionSobreCatalogador = g_simple_action_new("actionSobreCatalogador", NULL);
	g_action_map_add_action(G_ACTION_MAP(FrmPrincipal.actions), G_ACTION(FrmPrincipal.actionSobreCatalogador));

	gtk_widget_insert_action_group(GTK_WIDGET(FrmPrincipal.frmPrincipal), "app", G_ACTION_GROUP(FrmPrincipal.actions));

	FrmPrincipal.submenuAba = g_menu_new();
	FrmPrincipal.menuIncluirNovaAba = g_menu_item_new("Incluir Nova Aba", "app.actionIncluirNovaAba");
	FrmPrincipal.menuAlterarNomeAbaAtiva = g_menu_item_new("Alterar Nome da Aba Ativa", "app.actionAlterarNomeAbaAtiva");
	FrmPrincipal.menuExcluirAbaAtiva = g_menu_item_new("Excluir Aba Ativa", "app.actionExcluirAbaAtiva");
	g_menu_append_item(FrmPrincipal.submenuAba, FrmPrincipal.menuIncluirNovaAba);
	g_menu_append_item(FrmPrincipal.submenuAba, FrmPrincipal.menuAlterarNomeAbaAtiva);
	g_menu_append_item(FrmPrincipal.submenuAba, FrmPrincipal.menuExcluirAbaAtiva);

	FrmPrincipal.menuAba = GTK_MENU_BUTTON(gtk_menu_button_new());
	gtk_menu_button_set_label(FrmPrincipal.menuAba, "Aba");
	gtk_menu_button_set_menu_model(GTK_MENU_BUTTON(FrmPrincipal.menuAba), G_MENU_MODEL(FrmPrincipal.submenuAba));

	FrmPrincipal.submenuDiretorio = g_menu_new();
	FrmPrincipal.menuImportarDiretorio = g_menu_item_new(Rotinas_retUTF8("Importar Diretório"), "app.actionImportarDiretorio");
	FrmPrincipal.menuImportarSubDiretorios = g_menu_item_new(Rotinas_retUTF8("Importar SubDiretórios"), "app.actionImportarSubDiretorios");
	FrmPrincipal.menuCompararDiretorios = g_menu_item_new(Rotinas_retUTF8("Comparar Diretórios"), "app.actionCompararDiretorios");
	FrmPrincipal.menuCadastrarExtensaoArquivo = g_menu_item_new(Rotinas_retUTF8("Cadastrar Extensão de Arquivo"), "app.actionCadastrarExtensaoArquivo");
	//FrmPrincipal.menuseparador1
	FrmPrincipal.menuExpandirDiretorios = g_menu_item_new(Rotinas_retUTF8("Expandir Diretórios"), "app.actionExpandirDiretorios");
	FrmPrincipal.menuColapsarDiretorios = g_menu_item_new(Rotinas_retUTF8("Colapsar Diretórios"), "app.actionColapsarDiretorios");
	//FrmPrincipal.menuExportarDiretoriosAbaAtiva = g_menu_item_new(Rotinas_retUTF8("Exportar Diretórios da Aba Ativa"), "app.actionExportarDiretoriosAbaAtiva");
	FrmPrincipal.menuTXT = g_menu_item_new(Rotinas_retUTF8("Exportar Diretórios da Aba Ativa em TXT"), "app.actionTXT");
	FrmPrincipal.menuCSV = g_menu_item_new(Rotinas_retUTF8("Exportar Diretórios da Aba Ativa em CSV"), "app.actionCSV");
	FrmPrincipal.menuHTML = g_menu_item_new(Rotinas_retUTF8("Exportar Diretórios da Aba Ativa em HTML"), "app.actionHTML");
	FrmPrincipal.menuXML = g_menu_item_new(Rotinas_retUTF8("Exportar Diretórios da Aba Ativa em XML"), "app.actionXML");
	FrmPrincipal.menuSQL = g_menu_item_new(Rotinas_retUTF8("Exportar Diretórios da Aba Ativa em SQL"), "app.actionSQL");
	FrmPrincipal.menuImportarDiretoriosViaXML = g_menu_item_new(Rotinas_retUTF8("Importar Diretórios via XML"), "app.actionImportarDiretoriosViaXML");
	FrmPrincipal.menuGravarLogImportacao = g_menu_item_new(Rotinas_retUTF8("Gravar Log da Importação"), "app.actionGravarLogImportacao");
	g_menu_append_item(FrmPrincipal.submenuDiretorio, FrmPrincipal.menuImportarDiretorio);
	g_menu_append_item(FrmPrincipal.submenuDiretorio, FrmPrincipal.menuImportarSubDiretorios);
	g_menu_append_item(FrmPrincipal.submenuDiretorio, FrmPrincipal.menuCompararDiretorios);
	g_menu_append_item(FrmPrincipal.submenuDiretorio, FrmPrincipal.menuCadastrarExtensaoArquivo);
	g_menu_append_item(FrmPrincipal.submenuDiretorio, FrmPrincipal.menuExpandirDiretorios);
	g_menu_append_item(FrmPrincipal.submenuDiretorio, FrmPrincipal.menuColapsarDiretorios);
	g_menu_append_item(FrmPrincipal.submenuDiretorio, FrmPrincipal.menuTXT);
	g_menu_append_item(FrmPrincipal.submenuDiretorio, FrmPrincipal.menuCSV);
	g_menu_append_item(FrmPrincipal.submenuDiretorio, FrmPrincipal.menuHTML);
	g_menu_append_item(FrmPrincipal.submenuDiretorio, FrmPrincipal.menuXML);
	g_menu_append_item(FrmPrincipal.submenuDiretorio, FrmPrincipal.menuSQL);
	g_menu_append_item(FrmPrincipal.submenuDiretorio, FrmPrincipal.menuImportarDiretoriosViaXML);
	g_menu_append_item(FrmPrincipal.submenuDiretorio, FrmPrincipal.menuGravarLogImportacao);

	FrmPrincipal.menuDiretorio = GTK_MENU_BUTTON(gtk_menu_button_new());
	gtk_menu_button_set_label(FrmPrincipal.menuDiretorio, Rotinas_retUTF8("Diretório"));
	gtk_menu_button_set_menu_model(GTK_MENU_BUTTON(FrmPrincipal.menuDiretorio), G_MENU_MODEL(FrmPrincipal.submenuDiretorio));
	
	FrmPrincipal.submenuVisao = g_menu_new();
	FrmPrincipal.menuMostrarOcultarListaItensPesquisados = g_menu_item_new("Mostrar/Ocultar lista de itens pesquisados", "app.actionMostrarOcultarListaItensPesquisados");
	FrmPrincipal.menuMostrarOcultarArvoreDirAbaAtiva = g_menu_item_new(Rotinas_retUTF8("Mostrar/Ocultar árvore de diretórios da Aba Ativa"), "app.actionMostrarOcultarArvoreDirAbaAtiva");
	g_menu_append_item(FrmPrincipal.submenuVisao, FrmPrincipal.menuMostrarOcultarListaItensPesquisados);
	g_menu_append_item(FrmPrincipal.submenuVisao, FrmPrincipal.menuMostrarOcultarArvoreDirAbaAtiva);

	FrmPrincipal.menuVisao = GTK_MENU_BUTTON(gtk_menu_button_new());
	gtk_menu_button_set_label(FrmPrincipal.menuVisao, Rotinas_retUTF8("Visão"));
	gtk_menu_button_set_menu_model(GTK_MENU_BUTTON(FrmPrincipal.menuVisao), G_MENU_MODEL(FrmPrincipal.submenuVisao));

	FrmPrincipal.submenuSobre = g_menu_new();
	FrmPrincipal.menuSobreCatalogador = g_menu_item_new("Sobre o Catalogador", "app.actionSobreCatalogador");
	g_menu_append_item(FrmPrincipal.submenuSobre, FrmPrincipal.menuSobreCatalogador);
	
	FrmPrincipal.menuSobre = GTK_MENU_BUTTON(gtk_menu_button_new());
	gtk_menu_button_set_label(FrmPrincipal.menuSobre, "Sobre");
	gtk_menu_button_set_menu_model(GTK_MENU_BUTTON(FrmPrincipal.menuSobre), G_MENU_MODEL(FrmPrincipal.submenuSobre));

	FrmPrincipal.barraMenu1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 8);	
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.barraMenu1), "barraMenu1");
	gtk_box_append(GTK_BOX(FrmPrincipal.barraMenu1), GTK_WIDGET(FrmPrincipal.menuAba));
	gtk_box_append(GTK_BOX(FrmPrincipal.barraMenu1), GTK_WIDGET(FrmPrincipal.menuDiretorio));
	gtk_box_append(GTK_BOX(FrmPrincipal.barraMenu1), GTK_WIDGET(FrmPrincipal.menuVisao));
	gtk_box_append(GTK_BOX(FrmPrincipal.barraMenu1), GTK_WIDGET(FrmPrincipal.menuSobre));	

	FrmPrincipal.vbox1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.vbox1), "vbox1");
	gtk_widget_set_visible(FrmPrincipal.vbox1, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.vbox1, FALSE);
	gtk_box_append(GTK_BOX(FrmPrincipal.vbox1), FrmPrincipal.barraMenu1);
	gtk_box_append(GTK_BOX(FrmPrincipal.vbox1), FrmPrincipal.toolbar1);
	gtk_box_append(GTK_BOX(FrmPrincipal.vbox1), FrmPrincipal.spPesquisa);
	gtk_box_append(GTK_BOX(FrmPrincipal.vbox1), FrmPrincipal.hbox6);

	gtk_window_set_child(GTK_WINDOW(FrmPrincipal.frmPrincipal), FrmPrincipal.vbox1);	

	g_signal_connect(FrmPrincipal.actionIncluirNovaAba, "activate", G_CALLBACK(on_menuIncluirNovaAba_activate), NULL);
	g_signal_connect(FrmPrincipal.actionAlterarNomeAbaAtiva, "activate", G_CALLBACK(on_menuAlterarNomeAbaAtiva_activate), NULL);
	g_signal_connect(FrmPrincipal.actionExcluirAbaAtiva, "activate", G_CALLBACK(on_menuExcluirAbaAtiva_activate), NULL);
	g_signal_connect(FrmPrincipal.actionImportarDiretorio, "activate", G_CALLBACK(on_menuImportarDiretorio_activate), NULL);
	g_signal_connect(FrmPrincipal.actionImportarSubDiretorios, "activate", G_CALLBACK(on_menuImportarSubDiretorios_activate), NULL);
	g_signal_connect(FrmPrincipal.actionCompararDiretorios, "activate", G_CALLBACK(on_menuCompararDiretorios_activate), NULL);
	g_signal_connect(FrmPrincipal.actionCadastrarExtensaoArquivo, "activate", G_CALLBACK(on_menuCadastrarExtensaoArquivo_activate), NULL);
	g_signal_connect(FrmPrincipal.actionExpandirDiretorios, "activate", G_CALLBACK(on_menuExpandirDiretorios_activate), NULL);
	g_signal_connect(FrmPrincipal.actionColapsarDiretorios, "activate", G_CALLBACK(on_menuColapsarDiretorios_activate), NULL);
	//g_signal_connect(FrmPrincipal.actionExportarDiretoriosAbaAtiva, "activate", G_CALLBACK(on_menuExportarDiretoriosAbaAtiva_activate), NULL);
	g_signal_connect(FrmPrincipal.actionTXT, "activate", G_CALLBACK(on_menuTXT_activate), NULL);
	g_signal_connect(FrmPrincipal.actionCSV, "activate", G_CALLBACK(on_menuCSV_activate), NULL);
	g_signal_connect(FrmPrincipal.actionHTML, "activate", G_CALLBACK(on_menuHTML_activate), NULL);
	g_signal_connect(FrmPrincipal.actionXML, "activate", G_CALLBACK(on_menuXML_activate), NULL);
	g_signal_connect(FrmPrincipal.actionSQL, "activate", G_CALLBACK(on_menuSQL_activate), NULL);
	g_signal_connect(FrmPrincipal.actionImportarDiretoriosViaXML, "activate", G_CALLBACK(on_menuImportarDiretoriosViaXML_activate), NULL);
	g_signal_connect(FrmPrincipal.actionMostrarOcultarArvoreDirAbaAtiva, "activate", G_CALLBACK(on_menuMostrarOcultarArvoreDirAbaAtiva_activate), NULL);
	g_signal_connect(FrmPrincipal.actionMostrarOcultarListaItensPesquisados, "activate", G_CALLBACK(on_menuMostrarOcultarListaItensPesquisados_activate), NULL);
	g_signal_connect(FrmPrincipal.actionSobreCatalogador, "activate", G_CALLBACK(on_menuSobreCatalogador_activate), NULL);

	g_signal_connect(FrmPrincipal.btnImportarDiretorio, "clicked", G_CALLBACK(on_btnImportarDiretorio_clicked), NULL);
	g_signal_connect(FrmPrincipal.btnPesquisa, "clicked", G_CALLBACK(on_btnPesquisa_clicked), NULL);
	g_signal_connect(FrmPrincipal.notebook1, "select_page", G_CALLBACK(on_notebook1_select_page), NULL);

	GtkTreeSelection* selecaoArvore = gtk_tree_view_get_selection(GTK_TREE_VIEW(FrmPrincipal.arvoreFixa));
	GtkTreeModel* modeloArvore = gtk_tree_view_get_model(GTK_TREE_VIEW(FrmPrincipal.arvoreFixa));

		
	g_signal_connect((gpointer)selecaoArvore, "changed", G_CALLBACK(on_arvoreFixa_selection_changed), modeloArvore);
	g_signal_connect((gpointer)FrmPrincipal.arvoreFixa, "row_collapsed", G_CALLBACK(on_arvoreFixa_row_collapsed), NULL);
	//g_signal_connect((gpointer)FrmPrincipal.arvoreFixa, "button_release_event", G_CALLBACK(on_arvoreFixa_button_release_event), NULL);
	g_signal_connect((gpointer)FrmPrincipal.arvoreFixa, "row_expanded", G_CALLBACK(on_arvoreFixa_row_expanded), NULL);
	//g_signal_connect((gpointer)FrmPrincipal.arvoreFixa, "button_press_event", G_CALLBACK(on_arvoreFixa_button_press_event), NULL);

	//g_signal_connect((gpointer)FrmPrincipal.tabelaFixa, "button_release_event", G_CALLBACK(on_tabelaFixa_button_release_event), NULL);
	g_signal_connect((gpointer)FrmPrincipal.tabelaFixa, "row_activated", G_CALLBACK(on_tabelaFixa_row_activated), NULL);

	//g_signal_connect(FrmPrincipal.tabelaPesquisa, "button_release_event", G_CALLBACK(on_tabelaPesquisa_button_release_event), NULL);
	

	//g_signal_connect(FrmPrincipal.frmPrincipal, "delete_event", G_CALLBACK(on_FrmPrincipal_delete_event), NULL);
	g_signal_connect (FrmPrincipal.frmPrincipal, "destroy", G_CALLBACK (on_FrmPrincipal_destroy), NULL);

	ExtensaoBO_iniciar();
	/*
	FrmPrincipal_ConstruirPopupMenu();	
	*/	
	gtk_notebook_remove_page(GTK_NOTEBOOK(FrmPrincipal.notebook1), 0);

	Arvore_cria(GTK_TREE_VIEW(FrmPrincipal.arvoreFixa));
	Tabela_cria(TRUE, GTK_TREE_VIEW(FrmPrincipal.tabelaFixa));
	Tabela_cria(FALSE, GTK_TREE_VIEW(FrmPrincipal.tabelaPesquisa));
	
	FrmPrincipal_adicionaTabPage(GTK_NOTEBOOK(FrmPrincipal.notebook1),
		GTK_PANED(FrmPrincipal.spPrincipal), g_string_new("DISCO1"));

	gtk_paned_set_position(GTK_PANED(FrmPrincipal.spPrincipal), 250);
	gtk_paned_set_position(GTK_PANED(FrmPrincipal.spPesquisa), 400);
	/*
	gtk_widget_get_size_request(FrmPrincipal.barraStatus111, &FrmPrincipal.nLargura, &FrmPrincipal.nAltura);
	gtk_widget_set_size_request(FrmPrincipal.barraStatus111, 300, FrmPrincipal.nAltura);
	*/

	return FrmPrincipal.frmPrincipal;
}
// ---------------------------------------------------------------------------
void FrmPrincipal_Mostrar(GtkApplication* app)
{
    FrmPrincipal.frmPrincipal = FrmPrincipal_Criar(app);

	GtkCssProvider* provider = gtk_css_provider_new();
	GdkDisplay* display = gtk_widget_get_display(FrmPrincipal.frmPrincipal);
	gtk_style_context_add_provider_for_display(display, GTK_STYLE_PROVIDER(provider), 
		GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
	gtk_css_provider_load_from_string(provider, "progress, trough { min-height: 30px; }");


	//gtk_window_set_position(GTK_WINDOW(FrmPrincipal.frmPrincipal), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_present(GTK_WINDOW(FrmPrincipal.frmPrincipal));
	
	Catalogador_New();
	Arvore_selecionarPrimeiroItem(GTK_TREE_VIEW(FrmPrincipal.arvoreFixa));	
}

void FrmPrincipal_ProgressoLog(Progresso progresso)
{
	if (FrmPrincipal.frmPrincipal != NULL) {
		if (progresso.posicao == 0) {
			gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(FrmPrincipal.pbImportarDiretorio), progresso.minimo);
			gtk_progress_bar_set_pulse_step(GTK_PROGRESS_BAR(FrmPrincipal.pbImportarDiretorio), 0.1); //progresso.passo
		}
		gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(FrmPrincipal.pbImportarDiretorio),
			Rotinas_calculaProgresso(progresso.maximo, progresso.posicao));
	}

}

void on_FrmPrincipal_destroy(GtkWidget* widget, gpointer user_data) {
	Rotinas_BancoDesconectar();
}
/*
GtkLabel* FrmPrincipal_getLabStatus1() {
	GList* lista = gtk_container_get_children(GTK_CONTAINER(FrmPrincipal.barraStatus111));
	GtkFrame* frameStatus1 = g_list_nth_data(lista, 0);

	lista = gtk_container_get_children(GTK_CONTAINER(frameStatus1));
	GtkHBox* hboxStatus1 = g_list_nth_data(lista, 0);

	lista = gtk_container_get_children(GTK_CONTAINER(hboxStatus1));
	GtkLabel* labStatus1 = g_list_nth_data(lista, 0);

	return labStatus1;
}

GtkLabel* FrmPrincipal_getLabStatus2() {
	GList* lista = gtk_container_get_children(GTK_CONTAINER(FrmPrincipal.barraStatus211));
	GtkFrame* frameStatus2 = g_list_nth_data(lista, 0);

	lista = gtk_container_get_children(GTK_CONTAINER(frameStatus2));
	GtkHBox* hboxStatus2 = g_list_nth_data(lista, 0);

	lista = gtk_container_get_children(GTK_CONTAINER(hboxStatus2));
	GtkLabel* labStatus2 = g_list_nth_data(lista, 0);

	return labStatus2;
}
*/
 void FrmPrincipal_adicionaTabPage(GtkNotebook* noteBook, GtkPaned* spPanel, const GString* nomeAba) {
	GtkWidget* tabAba;
	GtkWidget* imgAba;
	GtkWidget* labAba;		

	tabAba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_widget_set_name(GTK_WIDGET(tabAba), Rotinas_concatenar("tabAba", nomeAba->str)->str);
	gtk_widget_set_visible(tabAba, TRUE);
	gtk_widget_set_can_focus(tabAba, FALSE);

	GdkTexture* texture = gdk_texture_new_for_pixbuf(ExtensaoBO_CDOuroXPM);
	imgAba = gtk_image_new_from_paintable(GDK_PAINTABLE(texture));
	gtk_widget_set_name(GTK_WIDGET(imgAba), Rotinas_concatenar("imgAba", nomeAba->str)->str);
	gtk_widget_set_visible(imgAba, TRUE);
	gtk_widget_set_can_focus(imgAba, FALSE);

	labAba = gtk_label_new(nomeAba->str);
	gtk_widget_set_name(GTK_WIDGET(labAba), Rotinas_concatenar("labAba", nomeAba->str)->str);
	gtk_widget_set_visible(labAba, TRUE);
	gtk_widget_set_can_focus(labAba, FALSE);
	gtk_label_set_label(GTK_LABEL(labAba), nomeAba->str);
			
	gtk_box_append(GTK_BOX(tabAba), imgAba);
	gtk_box_append(GTK_BOX(tabAba), labAba);

	gtk_notebook_append_page(GTK_NOTEBOOK(FrmPrincipal.notebook1), GTK_WIDGET(spPanel), tabAba);

}
 /*
 void FrmPrincipal_ConstruirPopupMenu() {
	 
	 FrmPrincipal.menuInformacoesDiretorioArquivo = gtk_menu_item_new();
	 gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.menuInformacoesDiretorioArquivo), "menuInformacoesDiretorioArquivo");
	 gtk_widget_set_visible(FrmPrincipal.menuInformacoesDiretorioArquivo, TRUE);
	 gtk_widget_set_can_focus(FrmPrincipal.menuInformacoesDiretorioArquivo, FALSE);
	 gtk_menu_item_set_label(GTK_MENU_ITEM(FrmPrincipal.menuInformacoesDiretorioArquivo), Rotinas_retUTF8("Informações do Diretório / Arquivo"));
	 gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmPrincipal.menuInformacoesDiretorioArquivo), TRUE);	 
	 gtk_widget_show(GTK_WIDGET(FrmPrincipal.menuInformacoesDiretorioArquivo));
	 	 
	 FrmPrincipal.menuExcluirDiretorioSelecionado = gtk_menu_item_new();
	 gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.menuExcluirDiretorioSelecionado), "menuExcluirDiretorioSelecionado");
	 gtk_widget_set_visible(FrmPrincipal.menuExcluirDiretorioSelecionado, TRUE);
	 gtk_widget_set_can_focus(FrmPrincipal.menuExcluirDiretorioSelecionado, FALSE);
	 gtk_menu_item_set_label(GTK_MENU_ITEM(FrmPrincipal.menuExcluirDiretorioSelecionado), Rotinas_retUTF8("Excluir Diretório Selecionado"));
	 gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmPrincipal.menuExcluirDiretorioSelecionado), TRUE);
	 gtk_widget_show(GTK_WIDGET(FrmPrincipal.menuExcluirDiretorioSelecionado));
	 
	 FrmPrincipal.menuExpandirDiretorios2 = gtk_menu_item_new();
	 gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.menuExpandirDiretorios2), "menuExpandirDiretorios2");
	 gtk_widget_set_visible(FrmPrincipal.menuExpandirDiretorios2, TRUE);
	 gtk_widget_set_can_focus(FrmPrincipal.menuExpandirDiretorios2, FALSE);
	 gtk_menu_item_set_label(GTK_MENU_ITEM(FrmPrincipal.menuExpandirDiretorios2), Rotinas_retUTF8("Expandir Diretórios"));
	 gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmPrincipal.menuExpandirDiretorios2), TRUE);	 
	 gtk_widget_show(GTK_WIDGET(FrmPrincipal.menuExpandirDiretorios2));
	 	  
	 FrmPrincipal.menuColapsarDiretorios2 = gtk_menu_item_new();
	 gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.menuColapsarDiretorios2), "menuColapsarDiretorios2");
	 gtk_widget_set_visible(FrmPrincipal.menuColapsarDiretorios2, TRUE);
	 gtk_widget_set_can_focus(FrmPrincipal.menuColapsarDiretorios2, FALSE);
	 gtk_menu_item_set_label(GTK_MENU_ITEM(FrmPrincipal.menuColapsarDiretorios2), Rotinas_retUTF8("Colapsar Diretórios"));
	 gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmPrincipal.menuColapsarDiretorios2), TRUE);	 
	 gtk_widget_show(GTK_WIDGET(FrmPrincipal.menuColapsarDiretorios2));
	 
	 FrmPrincipal.menuseparador2 = gtk_separator_menu_item_new();
	 gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.menuseparador2), "menuseparador2");
	 gtk_widget_set_visible(FrmPrincipal.menuseparador2, TRUE);
	 gtk_widget_set_can_focus(FrmPrincipal.menuseparador2, FALSE);
	 gtk_widget_show(GTK_WIDGET(FrmPrincipal.menuseparador2));
	 
	 FrmPrincipal.menuIncluirNovaAba2 = gtk_menu_item_new();
	 gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.menuIncluirNovaAba2), "menuIncluirNovaAba2");
	 gtk_widget_set_visible(FrmPrincipal.menuIncluirNovaAba2, TRUE);
	 gtk_widget_set_can_focus(FrmPrincipal.menuIncluirNovaAba2, FALSE);
	 gtk_menu_item_set_label(GTK_MENU_ITEM(FrmPrincipal.menuIncluirNovaAba2), "Incluir Nova Aba");
	 gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmPrincipal.menuIncluirNovaAba2), TRUE);
	 gtk_widget_show(GTK_WIDGET(FrmPrincipal.menuIncluirNovaAba2));
	 
	 FrmPrincipal.menuAlterarNomeAbaAtiva2 = gtk_menu_item_new();
	 gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.menuAlterarNomeAbaAtiva2), "menuAlterarNomeAbaAtiva2");
	 gtk_widget_set_visible(FrmPrincipal.menuAlterarNomeAbaAtiva2, TRUE);
	 gtk_widget_set_can_focus(FrmPrincipal.menuAlterarNomeAbaAtiva2, FALSE);
	 gtk_menu_item_set_label(GTK_MENU_ITEM(FrmPrincipal.menuAlterarNomeAbaAtiva2), "Alterar Nome da Aba Ativa");
	 gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmPrincipal.menuAlterarNomeAbaAtiva2), TRUE);
	 gtk_widget_show(GTK_WIDGET(FrmPrincipal.menuAlterarNomeAbaAtiva2));
	 
	 FrmPrincipal.menuExcluirAbaAtiva2 = gtk_menu_item_new();
	 gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.menuExcluirAbaAtiva2), "menuExcluirAbaAtiva2");
	 gtk_widget_set_visible(FrmPrincipal.menuExcluirAbaAtiva2, TRUE);
	 gtk_widget_set_can_focus(FrmPrincipal.menuExcluirAbaAtiva2, FALSE);
	 gtk_menu_item_set_label(GTK_MENU_ITEM(FrmPrincipal.menuExcluirAbaAtiva2), "Excluir Aba Ativa");
	 gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmPrincipal.menuExcluirAbaAtiva2), TRUE);
	 gtk_widget_show(GTK_WIDGET(FrmPrincipal.menuExcluirAbaAtiva2));
	 

	 FrmPrincipal.popupMenu = gtk_menu_new();
	 gtk_menu_shell_append(GTK_MENU_SHELL(FrmPrincipal.popupMenu), FrmPrincipal.menuInformacoesDiretorioArquivo);
	 gtk_menu_shell_append(GTK_MENU_SHELL(FrmPrincipal.popupMenu), FrmPrincipal.menuExcluirDiretorioSelecionado);
	 gtk_menu_shell_append(GTK_MENU_SHELL(FrmPrincipal.popupMenu), FrmPrincipal.menuExpandirDiretorios2);
	 gtk_menu_shell_append(GTK_MENU_SHELL(FrmPrincipal.popupMenu), FrmPrincipal.menuColapsarDiretorios2);
	 gtk_menu_shell_append(GTK_MENU_SHELL(FrmPrincipal.popupMenu), FrmPrincipal.menuseparador2);
	 gtk_menu_shell_append(GTK_MENU_SHELL(FrmPrincipal.popupMenu), FrmPrincipal.menuIncluirNovaAba2);
	 gtk_menu_shell_append(GTK_MENU_SHELL(FrmPrincipal.popupMenu), FrmPrincipal.menuAlterarNomeAbaAtiva2);
	 gtk_menu_shell_append(GTK_MENU_SHELL(FrmPrincipal.popupMenu), FrmPrincipal.menuExcluirAbaAtiva2);

	 g_signal_connect(FrmPrincipal.menuInformacoesDiretorioArquivo, "activate", G_CALLBACK(FrmPrincipal_menuInformacoesDiretorioArquivo_activate), NULL);
	 g_signal_connect(FrmPrincipal.menuExcluirDiretorioSelecionado, "activate", G_CALLBACK(FrmPrincipal_menuExcluirDiretorioSelecionado_activate), NULL);
	 g_signal_connect(FrmPrincipal.menuExpandirDiretorios2, "activate", G_CALLBACK(FrmPrincipal_menuExpandirDiretorios2_activate), NULL);
	 g_signal_connect(FrmPrincipal.menuColapsarDiretorios2, "activate", G_CALLBACK(FrmPrincipal_menuColapsarDiretorios2_activate), NULL);
	 g_signal_connect(FrmPrincipal.menuIncluirNovaAba2, "activate", G_CALLBACK(FrmPrincipal_menuIncluirNovaAba2_activate), NULL);
	 g_signal_connect(FrmPrincipal.menuAlterarNomeAbaAtiva2, "activate", G_CALLBACK(FrmPrincipal_menuAlterarNomeAbaAtiva2_activate), NULL);
	 g_signal_connect(FrmPrincipal.menuExcluirAbaAtiva2, "activate", G_CALLBACK(FrmPrincipal_menuExcluirAbaAtiva2_activate), NULL);

 }
 */

void on_menuIncluirNovaAba_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data){
	//Catalogador_IncluirNovaAba();
}

void on_menuAlterarNomeAbaAtiva_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
	//Catalogador_AlterarNomeAbaAtiva(FrmPrincipal_ProgressoLog);
}

void on_menuExcluirAbaAtiva_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
	//Catalogador_ExcluirAbaAtiva(FrmPrincipal_ProgressoLog);
}

void on_menuImportarDiretorio_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
	//Catalogador_ComecaImportacao(FALSE, FrmPrincipal_ProgressoLog);
}

void on_menuImportarSubDiretorios_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
	//Catalogador_ComecaImportacao(TRUE, FrmPrincipal_ProgressoLog);
}

void on_menuCompararDiretorios_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
    //FrmCompararDiretorio_Mostrar();
}

void on_menuCadastrarExtensaoArquivo_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
    //FrmCadExtensao_Mostrar();
}

void on_menuExpandirDiretorios_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
	//Arvore_expandirTodos(Catalogador_getArvoreAtual());
}

void on_menuColapsarDiretorios_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
	//Arvore_colapsarTodos(Catalogador_getArvoreAtual());
}

//void on_menuExportarDiretoriosAbaAtiva_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data) {}

void on_menuTXT_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
	//Catalogador_ExportarArquivo(teTXT, FrmPrincipal_ProgressoLog);
}

void on_menuCSV_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
	//Catalogador_ExportarArquivo(teCSV, FrmPrincipal_ProgressoLog);
}

void on_menuHTML_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
	//Catalogador_ExportarArquivo(teHTML, FrmPrincipal_ProgressoLog);
}

void on_menuXML_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
	//Catalogador_ExportarArquivo(teXML, FrmPrincipal_ProgressoLog);
}

void on_menuSQL_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
	//Catalogador_ExportarArquivo(teSQL, FrmPrincipal_ProgressoLog);
}

void on_menuImportarDiretoriosViaXML_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
	//ListaString log = ListaString_inicia();
	//Catalogador_ImportarArquivo(log, FrmPrincipal_ProgressoLog);
}

void on_menuMostrarOcultarArvoreDirAbaAtiva_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
	//Catalogador_mostrarOcultarArvore();
}

void on_menuMostrarOcultarListaItensPesquisados_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
	//Catalogador_mostrarOcultarListaItensPesquisados();
}

void on_menuSobreCatalogador_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
    FrmSobre_Mostrar();
}

void on_btnImportarDiretorio_clicked(GtkWidget* widget, gpointer user_data) {
	on_menuImportarDiretorio_activate(NULL, NULL, user_data);
}

void on_btnPesquisa_clicked(GtkWidget* widget, gpointer user_data){
	//Catalogador_Pesquisar();
}

void on_notebook1_select_page(GtkNotebook *notebook, gboolean move_focus, gpointer user_data){
	//Catalogador_tabPanelMudou();
}

void on_arvoreFixa_selection_changed(GtkTreeSelection *treeselection, gpointer user_data) {
	/*
	GtkTreeModel* arvore_modelo;
	GtkTreeIter iter;

	arvore_modelo = GTK_TREE_MODEL(user_data);

	if (gtk_tree_selection_get_selected(treeselection, &arvore_modelo, &iter)) {
		GtkTreeView* tabela = Catalogador_getTabelaAtual();
		GtkTreeView* arvore = Catalogador_getArvoreAtual();
		Catalogador_ListarArquivos(tabela, arvore, iter);
	}
	*/
}

void on_arvoreFixa_row_collapsed(GtkTreeView *tree_view, GtkTreeIter *iter, GtkTreePath *path, gpointer user_data){
	/*
	GtkTreeModel* arvore_modelo;
	GtkTreeStore* arvore_store;
	GValue value = { 0, };
	GString* item;

	arvore_modelo = gtk_tree_view_get_model(tree_view);
	arvore_store = GTK_TREE_STORE(arvore_modelo);

	gtk_tree_model_get_value(arvore_modelo, iter, 1, &value);
	item = g_string_new(g_value_get_string(&value));
	g_value_unset(&value);

	gtk_tree_store_set(arvore_store, iter, 0, ExtensaoBO_DiretorioXPM, 1, item->str, -1);
	*/
}

gboolean on_arvoreFixa_button_release_event(GtkWidget *widget, GdkEvent *event, gpointer user_data){
	/*
	if (event->button.button == 3) {
		//gtk_menu_popup(GTK_MENU(FrmPrincipal.popupMenu), NULL, NULL, NULL, NULL,
		//	event->button.button, gtk_get_current_event_time());
		gtk_menu_popup_at_widget(GTK_MENU(FrmPrincipal.popupMenu), widget, 
			GDK_GRAVITY_NORTH_WEST, GDK_GRAVITY_NORTH_WEST, event);
	}	
	*/
	return FALSE;
}

gboolean on_arvoreFixa_button_press_event(GtkWidget *widget, GdkEvent *event, gpointer user_data) {
	/*
	GtkTreeView* arvore;

	if (event->button.button == 1) {
		if (event->button.type == GDK_2BUTTON_PRESS) {
			arvore = (GtkTreeView*)widget;
			Arvore_expandirSelecionado(arvore);
		}
	}	
	*/
	return FALSE;
}

void on_arvoreFixa_row_expanded(GtkTreeView *tree_view, GtkTreeIter *iter, GtkTreePath *path, gpointer user_data){
	/*
	GtkTreeModel* arvore_modelo;
	GtkTreeStore* arvore_store;
	GValue value = { 0, };
	GString* item;

	arvore_modelo = gtk_tree_view_get_model(tree_view);
	arvore_store = GTK_TREE_STORE(arvore_modelo);

	gtk_tree_model_get_value(arvore_modelo, iter, 1, &value);
	item = g_string_new(g_value_get_string(&value));
	g_value_unset(&value);

	gtk_tree_store_set(arvore_store, iter, 0, ExtensaoBO_DirAbertoXPM, 1, item->str, -1);
	*/
}

gboolean on_tabelaFixa_button_release_event(GtkWidget *widget, GdkEvent *event, gpointer user_data){
	/*
	if (event->button.button == 3) {
		//gtk_menu_popup(GTK_MENU(FrmPrincipal.popupMenu), NULL, NULL, NULL, NULL, 
			//event->button.button, gtk_get_current_event_time());
		gtk_menu_popup_at_widget(GTK_MENU(FrmPrincipal.popupMenu), widget, 
			GDK_GRAVITY_NORTH_WEST, GDK_GRAVITY_NORTH_WEST, event);
	}	
	*/
	return FALSE;
}

void on_tabelaFixa_row_activated(GtkTreeView *tree_view, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data){
	/*
	GValue value = { 0, };
	GtkTreeModel* tabela_modelo;
	GtkTreeIter iter;
	GtkTreeSelection *tabela_selecao;
	GString *nome, *tipo;

	tabela_modelo = gtk_tree_view_get_model(tree_view);
	tabela_selecao = gtk_tree_view_get_selection(tree_view);

	if (gtk_tree_selection_get_selected(tabela_selecao, &tabela_modelo, &iter)) {
		if (gtk_tree_selection_iter_is_selected(tabela_selecao, &iter)) {

			gtk_tree_model_get_value(tabela_modelo, &iter, 1, &value);
			nome = g_string_new(g_value_get_string(&value));
			g_value_unset(&value);

			gtk_tree_model_get_value(tabela_modelo, &iter, 3, &value);
			tipo = g_string_new(g_value_get_string(&value));
			g_value_unset(&value);

			Catalogador_DuploCliqueLista(nome, tipo);
		}
	}
	*/
}

gboolean on_tabelaPesquisa_button_release_event(GtkWidget *widget, GdkEvent *event, gpointer user_data){
	/*
	GValue value = { 0, };
	GtkTreeModel* tabela_modelo;
	GtkTreeIter iter;
	GtkTreeSelection *tabela_selecao;
	GString *nome, *caminho, *nomeAba;

	if (event->button.button == 1) {
		GtkTreeView* tabela = (GtkTreeView*)widget;
		
		tabela_modelo = gtk_tree_view_get_model(tabela);
		tabela_selecao = gtk_tree_view_get_selection(GTK_TREE_VIEW(tabela));

		if (gtk_tree_selection_get_selected(tabela_selecao, &tabela_modelo, &iter)) {
			if (gtk_tree_selection_iter_is_selected(tabela_selecao, &iter)) {

				gtk_tree_model_get_value(tabela_modelo, &iter, 1, &value);
				nome = g_string_new(g_value_get_string(&value));
				g_value_unset(&value);

				gtk_tree_model_get_value(tabela_modelo, &iter, 6, &value);
				caminho = g_string_new(g_value_get_string(&value));
				g_value_unset(&value);

				gtk_tree_model_get_value(tabela_modelo, &iter, 7, &value);
				nomeAba = g_string_new(g_value_get_string(&value));
				g_value_unset(&value);

				Catalogador_EncontrarItemLista(nomeAba, nome, caminho);
			}
		}
	}	
	*/
	return FALSE;
}

void FrmPrincipal_menuInformacoesDiretorioArquivo_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
	//Catalogador_InformacoesDiretorioArquivo();
}

void FrmPrincipal_menuExcluirDiretorioSelecionado_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
	//Catalogador_ExcluirDiretorioSelecionado(FrmPrincipal_ProgressoLog);
}

void FrmPrincipal_menuIncluirNovaAba2_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
	on_menuIncluirNovaAba_activate(action, parameter, user_data);
}

void FrmPrincipal_menuAlterarNomeAbaAtiva2_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
	on_menuAlterarNomeAbaAtiva_activate(action, parameter, user_data);
}

void FrmPrincipal_menuExcluirAbaAtiva2_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
	on_menuExcluirAbaAtiva_activate(action, parameter, user_data);
}

void FrmPrincipal_menuExpandirDiretorios2_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
	on_menuExpandirDiretorios_activate(action, parameter, user_data);
}

void FrmPrincipal_menuColapsarDiretorios2_activate(GSimpleAction* action, GVariant* parameter, gpointer user_data) {
	on_menuColapsarDiretorios_activate(action, parameter, user_data);
}

