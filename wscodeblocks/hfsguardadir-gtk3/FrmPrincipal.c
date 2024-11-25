#include "FrmPrincipal.h"
#include "hfsguardadir/comum/Rotinas.h"

#include "FrmCadExtensao.h"
#include "FrmCompararDiretorio.h"
#include "FrmImportarDiretorio.h"
#include "FrmInfoDiretorio.h"
#include "FrmSobre.h"
#include "hfsguardadir/catalogador/Catalogador.h"
#include "hfsguardadir/objetosbo/ExtensaoBO.h"

struct SFrmPrincipal FrmPrincipal;
// ---------------------------------------------------------------------------
GtkWidget *FrmPrincipal_Criar()
{
	FrmPrincipal.frmPrincipal = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	FrmPrincipal.barraStatus211 = gtk_statusbar_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.barraStatus211), "barraStatus211");
	gtk_widget_set_visible(FrmPrincipal.barraStatus211, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.barraStatus211, FALSE);
	gtk_box_set_spacing(GTK_BOX(FrmPrincipal.barraStatus211), 2);

	FrmPrincipal.barraStatus111 = gtk_statusbar_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.barraStatus111), "barraStatus111");
	gtk_widget_set_visible(FrmPrincipal.barraStatus111, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.barraStatus111, FALSE);
	gtk_box_set_spacing(GTK_BOX(FrmPrincipal.barraStatus111), 2);
	//gtk_statusbar_set_has_resize_grip(GTK_STATUSBAR(FrmPrincipal.barraStatus111), FALSE);

	FrmPrincipal.hbox6 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.hbox6), "hbox6");
	gtk_widget_set_visible(FrmPrincipal.hbox6, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.hbox6, FALSE);
	gtk_container_add(GTK_CONTAINER(FrmPrincipal.hbox6), FrmPrincipal.barraStatus111);
	gtk_box_set_child_packing(GTK_BOX(FrmPrincipal.hbox6), FrmPrincipal.barraStatus111, FALSE, TRUE, 0, GTK_PACK_START);
	gtk_container_add(GTK_CONTAINER(FrmPrincipal.hbox6), FrmPrincipal.barraStatus211);
	gtk_box_set_child_packing(GTK_BOX(FrmPrincipal.hbox6), FrmPrincipal.barraStatus211, TRUE, TRUE, 0, GTK_PACK_START);

	FrmPrincipal.tabelaPesquisa = gtk_tree_view_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.tabelaPesquisa), "tabelaPesquisa");
	gtk_widget_set_visible(FrmPrincipal.tabelaPesquisa, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.tabelaPesquisa, TRUE);

	FrmPrincipal.scrollPesquisa = gtk_scrolled_window_new(NULL, NULL);
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.scrollPesquisa), "scrollPesquisa");
	gtk_widget_set_visible(FrmPrincipal.scrollPesquisa, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.scrollPesquisa, TRUE);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(FrmPrincipal.scrollPesquisa), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_container_add(GTK_CONTAINER(FrmPrincipal.scrollPesquisa), FrmPrincipal.tabelaPesquisa);

	FrmPrincipal.tabelaFixa = gtk_tree_view_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.tabelaFixa), "tabelaFixa");
	gtk_widget_set_visible(FrmPrincipal.tabelaFixa, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.tabelaFixa, TRUE);

	FrmPrincipal.scrollTabelaFixa = gtk_scrolled_window_new(NULL, NULL);
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.scrollTabelaFixa), "scrollTabelaFixa");
	gtk_widget_set_visible(FrmPrincipal.scrollTabelaFixa, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.scrollTabelaFixa, TRUE);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(FrmPrincipal.scrollTabelaFixa), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(FrmPrincipal.scrollTabelaFixa), GTK_SHADOW_ETCHED_OUT);
	gtk_container_add(GTK_CONTAINER(FrmPrincipal.scrollTabelaFixa), FrmPrincipal.tabelaFixa);

	FrmPrincipal.arvoreFixa = gtk_tree_view_new();
	gtk_widget_set_name(FrmPrincipal.arvoreFixa, "arvoreFixa");
	gtk_widget_set_visible(FrmPrincipal.arvoreFixa, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.arvoreFixa, TRUE);

	FrmPrincipal.scrollArvore = gtk_scrolled_window_new(NULL, NULL);
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.scrollArvore), "scrollArvore");
	gtk_widget_set_visible(FrmPrincipal.scrollArvore, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.scrollArvore, TRUE);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(FrmPrincipal.scrollArvore), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(FrmPrincipal.scrollArvore), GTK_SHADOW_IN);
	gtk_container_add(GTK_CONTAINER(FrmPrincipal.scrollArvore), FrmPrincipal.arvoreFixa);

	FrmPrincipal.sp = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.sp), "sp");
	gtk_widget_set_visible(FrmPrincipal.sp, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.sp, TRUE);
	gtk_paned_set_position(GTK_PANED(FrmPrincipal.sp), 250);
	gtk_container_add(GTK_CONTAINER(FrmPrincipal.sp), FrmPrincipal.scrollArvore);
	gtk_container_add(GTK_CONTAINER(FrmPrincipal.sp), FrmPrincipal.scrollTabelaFixa);

	FrmPrincipal.notebook1 = gtk_notebook_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.notebook1), "notebook1");
	gtk_widget_set_visible(FrmPrincipal.notebook1, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.notebook1, TRUE);

	FrmPrincipal.spPesquisa = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.spPesquisa), "spPesquisa");
	gtk_widget_set_visible(FrmPrincipal.spPesquisa, FALSE);
	gtk_widget_set_can_focus(FrmPrincipal.spPesquisa, TRUE);
	gtk_paned_set_position(GTK_PANED(FrmPrincipal.spPesquisa), 250);
	gtk_container_add(GTK_CONTAINER(FrmPrincipal.spPesquisa), FrmPrincipal.notebook1);
	gtk_container_add(GTK_CONTAINER(FrmPrincipal.spPesquisa), FrmPrincipal.scrollPesquisa);

	FrmPrincipal.btnPesquisa = gtk_button_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.btnPesquisa), "btnPesquisa");
	gtk_button_set_label(GTK_BUTTON(FrmPrincipal.btnPesquisa), "Pesquisar");
	gtk_widget_set_visible(FrmPrincipal.btnPesquisa, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.btnPesquisa, FALSE);
	gtk_widget_set_receives_default(FrmPrincipal.btnPesquisa, FALSE);
	gtk_button_set_use_underline(GTK_BUTTON(FrmPrincipal.btnPesquisa), TRUE);

	FrmPrincipal.toolbutton4 = gtk_tool_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.toolbutton4), "toolbutton4");
	gtk_widget_set_visible(GTK_WIDGET(FrmPrincipal.toolbutton4), TRUE);
	gtk_widget_set_can_focus(GTK_WIDGET(FrmPrincipal.toolbutton4), FALSE);
	gtk_container_add(GTK_CONTAINER(FrmPrincipal.toolbutton4), FrmPrincipal.btnPesquisa);

	FrmPrincipal.edtPesquisa = gtk_entry_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.edtPesquisa), "edtPesquisa");
	gtk_widget_set_size_request(FrmPrincipal.edtPesquisa, 325, -1);
	gtk_widget_set_visible(FrmPrincipal.edtPesquisa, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.edtPesquisa, TRUE);
	gtk_entry_set_max_length(GTK_ENTRY(FrmPrincipal.edtPesquisa), 255);
	gtk_entry_set_icon_activatable(GTK_ENTRY(FrmPrincipal.edtPesquisa), FALSE, GTK_ENTRY_ICON_PRIMARY);
	gtk_entry_set_icon_activatable(GTK_ENTRY(FrmPrincipal.edtPesquisa), FALSE, GTK_ENTRY_ICON_SECONDARY);
	gtk_entry_set_icon_sensitive(GTK_ENTRY(FrmPrincipal.edtPesquisa), GTK_ENTRY_ICON_PRIMARY, TRUE);
	gtk_entry_set_icon_sensitive(GTK_ENTRY(FrmPrincipal.edtPesquisa), GTK_ENTRY_ICON_SECONDARY, TRUE);

	FrmPrincipal.toolbutton3 = gtk_tool_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.toolbutton3), "toolbutton3");
	gtk_widget_set_visible(GTK_WIDGET(FrmPrincipal.toolbutton3), TRUE);
	gtk_widget_set_can_focus(GTK_WIDGET(FrmPrincipal.toolbutton3), FALSE);
	gtk_container_add(GTK_CONTAINER(FrmPrincipal.toolbutton3), FrmPrincipal.edtPesquisa);

	FrmPrincipal.pb = gtk_progress_bar_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.pb), "pb");
	gtk_widget_set_size_request(FrmPrincipal.pb, 385, -1);
	gtk_widget_set_visible(FrmPrincipal.pb, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.pb, FALSE);

	FrmPrincipal.toolbutton2 = gtk_tool_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.toolbutton2), "toolbutton2");
	gtk_widget_set_size_request(GTK_WIDGET(FrmPrincipal.toolbutton2), 222, -1);
	gtk_widget_set_visible(GTK_WIDGET(FrmPrincipal.toolbutton2), TRUE);
	gtk_widget_set_can_focus(GTK_WIDGET(FrmPrincipal.toolbutton2), FALSE);
	gtk_container_add(GTK_CONTAINER(FrmPrincipal.toolbutton2), FrmPrincipal.pb);

	FrmPrincipal.btnImportarDiretorio = gtk_button_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.btnImportarDiretorio), "btnImportarDiretorio");
	gtk_button_set_label(GTK_BUTTON(FrmPrincipal.btnImportarDiretorio), Rotinas_retUTF8("Importar Diretório"));
	gtk_widget_set_visible(FrmPrincipal.btnImportarDiretorio, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.btnImportarDiretorio, FALSE);
	gtk_widget_set_receives_default(FrmPrincipal.btnImportarDiretorio, FALSE);
	gtk_button_set_use_underline(GTK_BUTTON(FrmPrincipal.btnImportarDiretorio), TRUE);

	FrmPrincipal.toolbutton1 = gtk_tool_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.toolbutton1), "toolbutton1");
	gtk_widget_set_visible(GTK_WIDGET(FrmPrincipal.toolbutton1), TRUE);
	gtk_widget_set_can_focus(GTK_WIDGET(FrmPrincipal.toolbutton1), FALSE);
	gtk_container_add(GTK_CONTAINER(FrmPrincipal.toolbutton1), FrmPrincipal.btnImportarDiretorio);

	FrmPrincipal.toolbar1 = gtk_toolbar_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.toolbar1), "toolbar1");
	gtk_widget_set_visible(FrmPrincipal.toolbar1, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.toolbar1, FALSE);
	gtk_container_add(GTK_CONTAINER(FrmPrincipal.toolbar1), GTK_WIDGET(FrmPrincipal.toolbutton1));
	gtk_container_add(GTK_CONTAINER(FrmPrincipal.toolbar1), GTK_WIDGET(FrmPrincipal.toolbutton2));
	gtk_container_add(GTK_CONTAINER(FrmPrincipal.toolbar1), GTK_WIDGET(FrmPrincipal.toolbutton3));
	gtk_container_add(GTK_CONTAINER(FrmPrincipal.toolbar1), GTK_WIDGET(FrmPrincipal.toolbutton4));

	FrmPrincipal.menuSobreCatalogador = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.menuSobreCatalogador), "menuSobreCatalogador");
	gtk_widget_set_visible(FrmPrincipal.menuSobreCatalogador, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.menuSobreCatalogador, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmPrincipal.menuSobreCatalogador), "Sobre o Catalogador");
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmPrincipal.menuSobreCatalogador), TRUE);

	FrmPrincipal.submenuSobre = gtk_menu_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.submenuSobre), "submenuSobre");
	gtk_widget_set_visible(FrmPrincipal.submenuSobre, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.submenuSobre, FALSE);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmPrincipal.submenuSobre), FrmPrincipal.menuSobreCatalogador);

	FrmPrincipal.menuSobre = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.menuSobre), "menuSobre");
	gtk_widget_set_visible(FrmPrincipal.menuSobre, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.menuSobre, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmPrincipal.menuSobre), "Sobre");
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmPrincipal.menuSobre), TRUE);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(FrmPrincipal.menuSobre), FrmPrincipal.submenuSobre);

	FrmPrincipal.menuMostrarOcultarListaItensPesquisados = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.menuMostrarOcultarListaItensPesquisados), "menuMostrarOcultarListaItensPesquisados");
	gtk_widget_set_visible(FrmPrincipal.menuMostrarOcultarListaItensPesquisados, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.menuMostrarOcultarListaItensPesquisados, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmPrincipal.menuMostrarOcultarListaItensPesquisados), "Mostrar/Ocultar lista de itens pesquisados");
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmPrincipal.menuMostrarOcultarListaItensPesquisados), TRUE);

	FrmPrincipal.menuMostrarOcultarArvoreDirAbaAtiva = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.menuMostrarOcultarArvoreDirAbaAtiva), "menuMostrarOcultarArvoreDirAbaAtiva");
	gtk_widget_set_visible(FrmPrincipal.menuMostrarOcultarArvoreDirAbaAtiva, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.menuMostrarOcultarArvoreDirAbaAtiva, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmPrincipal.menuMostrarOcultarArvoreDirAbaAtiva), Rotinas_retUTF8("Mostrar/Ocultar árvore de diretórios da Aba Ativa"));
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmPrincipal.menuMostrarOcultarArvoreDirAbaAtiva), TRUE);

	FrmPrincipal.submenuVisao = gtk_menu_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.submenuVisao), "submenuVisao");
	gtk_widget_set_visible(FrmPrincipal.submenuVisao, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.submenuVisao, FALSE);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmPrincipal.submenuVisao), FrmPrincipal.menuMostrarOcultarArvoreDirAbaAtiva);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmPrincipal.submenuVisao), FrmPrincipal.menuMostrarOcultarListaItensPesquisados);

	FrmPrincipal.menuVisao = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.menuVisao), "menuVisao");
	gtk_widget_set_visible(FrmPrincipal.menuVisao, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.menuVisao, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmPrincipal.menuVisao), Rotinas_retUTF8("Visão"));
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(FrmPrincipal.menuVisao), FrmPrincipal.submenuVisao);

	FrmPrincipal.menuGravarLogImportacao = gtk_check_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.menuGravarLogImportacao), "menuGravarLogImportacao");
	gtk_widget_set_visible(FrmPrincipal.menuGravarLogImportacao, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.menuGravarLogImportacao, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmPrincipal.menuGravarLogImportacao), Rotinas_retUTF8("Gravar Log da Importação"));
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmPrincipal.menuGravarLogImportacao), TRUE);

	FrmPrincipal.menuImportarDiretoriosViaXML = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.menuImportarDiretoriosViaXML), "menuImportarDiretoriosViaXML");
	gtk_widget_set_visible(FrmPrincipal.menuImportarDiretoriosViaXML, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.menuImportarDiretoriosViaXML, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmPrincipal.menuImportarDiretoriosViaXML), Rotinas_retUTF8("Importar Diretórios via XML"));
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmPrincipal.menuImportarDiretoriosViaXML), TRUE);

	FrmPrincipal.menuSQL = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.menuSQL), "menuSQL");
	gtk_widget_set_visible(FrmPrincipal.menuSQL, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.menuSQL, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmPrincipal.menuSQL), "SQL");
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmPrincipal.menuSQL), TRUE);

	FrmPrincipal.menuXML = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.menuXML), "menuXML");
	gtk_widget_set_visible(FrmPrincipal.menuXML, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.menuXML, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmPrincipal.menuXML), "XML");
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmPrincipal.menuXML), TRUE);

	FrmPrincipal.menuHTML = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.menuHTML), "menuHTML");
	gtk_widget_set_visible(FrmPrincipal.menuHTML, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.menuHTML, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmPrincipal.menuHTML), "HTML");
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmPrincipal.menuHTML), TRUE);

	FrmPrincipal.menuCSV = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.menuCSV), "menuCSV");
	gtk_widget_set_visible(FrmPrincipal.menuCSV, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.menuCSV, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmPrincipal.menuCSV), "CSV");
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmPrincipal.menuCSV), TRUE);

	FrmPrincipal.menuTXT = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.menuTXT), "menuTXT");
	gtk_widget_set_visible(FrmPrincipal.menuTXT, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.menuTXT, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmPrincipal.menuTXT), "TXT");
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmPrincipal.menuTXT), TRUE);

	FrmPrincipal.menu2 = gtk_menu_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.menu2), "menu2");
	gtk_widget_set_visible(FrmPrincipal.menu2, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.menu2, FALSE);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmPrincipal.menu2), FrmPrincipal.menuTXT);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmPrincipal.menu2), FrmPrincipal.menuCSV);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmPrincipal.menu2), FrmPrincipal.menuHTML);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmPrincipal.menu2), FrmPrincipal.menuXML);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmPrincipal.menu2), FrmPrincipal.menuSQL);

	FrmPrincipal.menuExportarDiretoriosAbaAtiva = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.menuExportarDiretoriosAbaAtiva), "menuExportarDiretoriosAbaAtiva");
	gtk_widget_set_visible(FrmPrincipal.menuExportarDiretoriosAbaAtiva, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.menuExportarDiretoriosAbaAtiva, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmPrincipal.menuExportarDiretoriosAbaAtiva), Rotinas_retUTF8("Exportar Diretórios da Aba Ativa"));
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmPrincipal.menuExportarDiretoriosAbaAtiva), TRUE);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(FrmPrincipal.menuExportarDiretoriosAbaAtiva), FrmPrincipal.menu2);

	FrmPrincipal.menuColapsarDiretorios = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.menuColapsarDiretorios), "menuColapsarDiretorios");
	gtk_widget_set_visible(FrmPrincipal.menuColapsarDiretorios, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.menuColapsarDiretorios, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmPrincipal.menuColapsarDiretorios), Rotinas_retUTF8("Colapsar Diretórios"));
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmPrincipal.menuColapsarDiretorios), TRUE);

	FrmPrincipal.menuExpandirDiretorios = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.menuExpandirDiretorios), "menuExpandirDiretorios");
	gtk_widget_set_visible(FrmPrincipal.menuExpandirDiretorios, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.menuExpandirDiretorios, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmPrincipal.menuExpandirDiretorios), Rotinas_retUTF8("Expandir Diretórios"));
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmPrincipal.menuExpandirDiretorios), TRUE);

	FrmPrincipal.menuseparador1 = gtk_separator_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.menuseparador1), "menuseparador1");
	gtk_widget_set_visible(FrmPrincipal.menuseparador1, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.menuseparador1, FALSE);

	FrmPrincipal.menuCadastrarExtensaoArquivo = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.menuCadastrarExtensaoArquivo), "menuCadastrarExtensaoArquivo");
	gtk_widget_set_visible(FrmPrincipal.menuCadastrarExtensaoArquivo, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.menuCadastrarExtensaoArquivo, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmPrincipal.menuCadastrarExtensaoArquivo), Rotinas_retUTF8("Cadastrar Extensão de Arquivo"));
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmPrincipal.menuCadastrarExtensaoArquivo), TRUE);

	FrmPrincipal.menuCompararDiretorios = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.menuCompararDiretorios), "menuCompararDiretorios");
	gtk_widget_set_visible(FrmPrincipal.menuCompararDiretorios, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.menuCompararDiretorios, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmPrincipal.menuCompararDiretorios), Rotinas_retUTF8("Comparar Diretórios"));
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmPrincipal.menuCompararDiretorios), TRUE);

	FrmPrincipal.menuImportarSubDiretorios = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.menuImportarSubDiretorios), "menuImportarSubDiretorios");
	gtk_widget_set_visible(FrmPrincipal.menuImportarSubDiretorios, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.menuImportarSubDiretorios, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmPrincipal.menuImportarSubDiretorios), Rotinas_retUTF8("Importar SubDiretórios"));
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmPrincipal.menuImportarSubDiretorios), TRUE);

	FrmPrincipal.menuImportarDiretorio = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.menuImportarDiretorio), "menuImportarDiretorio");
	gtk_widget_set_visible(FrmPrincipal.menuImportarDiretorio, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.menuImportarDiretorio, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmPrincipal.menuImportarDiretorio), Rotinas_retUTF8("Importar Diretório"));
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmPrincipal.menuImportarDiretorio), TRUE);

	FrmPrincipal.submenuDiretorio = gtk_menu_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.submenuDiretorio), "submenuDiretorio");
	gtk_widget_set_visible(FrmPrincipal.submenuDiretorio, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.submenuDiretorio, FALSE);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmPrincipal.submenuDiretorio), FrmPrincipal.menuImportarDiretorio);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmPrincipal.submenuDiretorio), FrmPrincipal.menuImportarSubDiretorios);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmPrincipal.submenuDiretorio), FrmPrincipal.menuCompararDiretorios);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmPrincipal.submenuDiretorio), FrmPrincipal.menuCadastrarExtensaoArquivo);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmPrincipal.submenuDiretorio), FrmPrincipal.menuseparador1);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmPrincipal.submenuDiretorio), FrmPrincipal.menuExpandirDiretorios);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmPrincipal.submenuDiretorio), FrmPrincipal.menuColapsarDiretorios);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmPrincipal.submenuDiretorio), FrmPrincipal.menuExportarDiretoriosAbaAtiva);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmPrincipal.submenuDiretorio), FrmPrincipal.menuImportarDiretoriosViaXML);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmPrincipal.submenuDiretorio), FrmPrincipal.menuGravarLogImportacao);

	FrmPrincipal.menuDiretorio = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.menuDiretorio), "menuDiretorio");
	gtk_widget_set_visible(FrmPrincipal.menuDiretorio, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.menuDiretorio, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmPrincipal.menuDiretorio), Rotinas_retUTF8("Diretório"));
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(FrmPrincipal.menuDiretorio), FrmPrincipal.submenuDiretorio);

	FrmPrincipal.menuExcluirAbaAtiva = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.menuExcluirAbaAtiva), "menuExcluirAbaAtiva");
	gtk_widget_set_visible(FrmPrincipal.menuExcluirAbaAtiva, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.menuExcluirAbaAtiva, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmPrincipal.menuExcluirAbaAtiva), "Excluir Aba Ativa");
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmPrincipal.menuExcluirAbaAtiva), TRUE);

	FrmPrincipal.menuAlterarNomeAbaAtiva = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.menuAlterarNomeAbaAtiva), "menuAlterarNomeAbaAtiva");
	gtk_widget_set_visible(FrmPrincipal.menuAlterarNomeAbaAtiva, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.menuAlterarNomeAbaAtiva, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmPrincipal.menuAlterarNomeAbaAtiva), "Alterar Nome da Aba Ativa");
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmPrincipal.menuAlterarNomeAbaAtiva), TRUE);

	FrmPrincipal.menuIncluirNovaAba = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.menuIncluirNovaAba), "menuIncluirNovaAba");
	gtk_widget_set_visible(FrmPrincipal.menuIncluirNovaAba, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.menuIncluirNovaAba, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmPrincipal.menuIncluirNovaAba), "Incluir Nova Aba");
	gtk_menu_item_set_use_underline(GTK_MENU_ITEM(FrmPrincipal.menuIncluirNovaAba), TRUE);

	FrmPrincipal.submenuAba = gtk_menu_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.submenuAba), "submenuAba");
	gtk_widget_set_visible(FrmPrincipal.submenuAba, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.submenuAba, FALSE);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmPrincipal.submenuAba), FrmPrincipal.menuIncluirNovaAba);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmPrincipal.submenuAba), FrmPrincipal.menuAlterarNomeAbaAtiva);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmPrincipal.submenuAba), FrmPrincipal.menuExcluirAbaAtiva);

	FrmPrincipal.menuAba = gtk_menu_item_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.menuAba), "menuAba");
	gtk_widget_set_visible(FrmPrincipal.menuAba, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.menuAba, FALSE);
	gtk_menu_item_set_label(GTK_MENU_ITEM(FrmPrincipal.menuAba), "Aba");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(FrmPrincipal.menuAba), FrmPrincipal.submenuAba);

	FrmPrincipal.barraMenu1 = gtk_menu_bar_new();
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.barraMenu1), "barraMenu1");
	gtk_widget_set_visible(FrmPrincipal.barraMenu1, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.barraMenu1, FALSE);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmPrincipal.barraMenu1), FrmPrincipal.menuAba);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmPrincipal.barraMenu1), FrmPrincipal.menuDiretorio);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmPrincipal.barraMenu1), FrmPrincipal.menuVisao);
	gtk_menu_shell_append(GTK_MENU_SHELL(FrmPrincipal.barraMenu1), FrmPrincipal.menuSobre);

	FrmPrincipal.vbox1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_name(GTK_WIDGET(FrmPrincipal.vbox1), "vbox1");
	gtk_widget_set_visible(FrmPrincipal.vbox1, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.vbox1, FALSE);
	gtk_container_add(GTK_CONTAINER(FrmPrincipal.vbox1), FrmPrincipal.barraMenu1);
	gtk_box_set_child_packing(GTK_BOX(FrmPrincipal.vbox1), FrmPrincipal.barraMenu1, FALSE, TRUE, 0, GTK_PACK_START);
	gtk_container_add(GTK_CONTAINER(FrmPrincipal.vbox1), FrmPrincipal.toolbar1);
	gtk_box_set_child_packing(GTK_BOX(FrmPrincipal.vbox1), FrmPrincipal.toolbar1, FALSE, TRUE, 0, GTK_PACK_START);
	gtk_container_add(GTK_CONTAINER(FrmPrincipal.vbox1), FrmPrincipal.spPesquisa);
	gtk_box_set_child_packing(GTK_BOX(FrmPrincipal.vbox1), FrmPrincipal.spPesquisa, TRUE, TRUE, 0, GTK_PACK_START);
	gtk_container_add(GTK_CONTAINER(FrmPrincipal.vbox1), FrmPrincipal.hbox6);
	gtk_box_set_child_packing(GTK_BOX(FrmPrincipal.vbox1), FrmPrincipal.hbox6, FALSE, TRUE, 0, GTK_PACK_START);

	gtk_widget_set_name(FrmPrincipal.frmPrincipal, "frmPrincipal");
	gtk_widget_set_size_request(FrmPrincipal.frmPrincipal, 1200, 800);
	gtk_widget_set_visible(FrmPrincipal.frmPrincipal, TRUE);
	gtk_widget_set_can_focus(FrmPrincipal.frmPrincipal, FALSE);
	gtk_window_set_title(GTK_WINDOW(FrmPrincipal.frmPrincipal), Rotinas_retUTF8("HFSGuardaDiretorio 2.0 - Catalogador de Diretórios"));
	gtk_window_set_position(GTK_WINDOW(FrmPrincipal.frmPrincipal), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_default_size(GTK_WINDOW(FrmPrincipal.frmPrincipal), 1200, 800);
	gtk_container_add(GTK_CONTAINER(FrmPrincipal.frmPrincipal), GTK_WIDGET(FrmPrincipal.vbox1));

	g_signal_connect((gpointer) FrmPrincipal.menuIncluirNovaAba, "activate", G_CALLBACK(on_menuIncluirNovaAba_activate), NULL);
	g_signal_connect((gpointer) FrmPrincipal.menuAlterarNomeAbaAtiva, "activate", G_CALLBACK(on_menuAlterarNomeAbaAtiva_activate), NULL);
	g_signal_connect((gpointer) FrmPrincipal.menuExcluirAbaAtiva, "activate", G_CALLBACK(on_menuExcluirAbaAtiva_activate), NULL);
	g_signal_connect((gpointer) FrmPrincipal.menuImportarDiretorio, "activate", G_CALLBACK(on_menuImportarDiretorio_activate), NULL);
	g_signal_connect((gpointer) FrmPrincipal.menuImportarSubDiretorios, "activate", G_CALLBACK(on_menuImportarSubDiretorios_activate), NULL);
	g_signal_connect((gpointer) FrmPrincipal.menuCompararDiretorios, "activate", G_CALLBACK(on_menuCompararDiretorios_activate), NULL);
	g_signal_connect((gpointer) FrmPrincipal.menuCadastrarExtensaoArquivo, "activate", G_CALLBACK(on_menuCadastrarExtensaoArquivo_activate), NULL);
	g_signal_connect((gpointer) FrmPrincipal.menuExpandirDiretorios, "activate", G_CALLBACK(on_menuExpandirDiretorios_activate), NULL);
	g_signal_connect((gpointer) FrmPrincipal.menuColapsarDiretorios, "activate", G_CALLBACK(on_menuColapsarDiretorios_activate), NULL);
	g_signal_connect((gpointer) FrmPrincipal.menuExportarDiretoriosAbaAtiva, "activate", G_CALLBACK(on_menuExportarDiretoriosAbaAtiva_activate), NULL);
	g_signal_connect((gpointer) FrmPrincipal.menuTXT, "activate", G_CALLBACK(on_menuTXT_activate), NULL);
	g_signal_connect((gpointer) FrmPrincipal.menuCSV, "activate", G_CALLBACK(on_menuCSV_activate), NULL);
	g_signal_connect((gpointer) FrmPrincipal.menuHTML, "activate", G_CALLBACK(on_menuHTML_activate), NULL);
	g_signal_connect((gpointer) FrmPrincipal.menuXML, "activate", G_CALLBACK(on_menuXML_activate), NULL);
	g_signal_connect((gpointer) FrmPrincipal.menuSQL, "activate", G_CALLBACK(on_menuSQL_activate), NULL);
	g_signal_connect((gpointer) FrmPrincipal.menuImportarDiretoriosViaXML, "activate", G_CALLBACK(on_menuImportarDiretoriosViaXML_activate), NULL);
	g_signal_connect((gpointer) FrmPrincipal.menuMostrarOcultarArvoreDirAbaAtiva, "activate", G_CALLBACK(on_menuMostrarOcultarArvoreDirAbaAtiva_activate), NULL);
	g_signal_connect((gpointer) FrmPrincipal.menuMostrarOcultarListaItensPesquisados, "activate", G_CALLBACK(on_menuMostrarOcultarListaItensPesquisados_activate), NULL);
	g_signal_connect((gpointer) FrmPrincipal.menuSobreCatalogador, "activate", G_CALLBACK(on_menuSobreCatalogador_activate), NULL);
	g_signal_connect((gpointer) FrmPrincipal.btnImportarDiretorio, "clicked", G_CALLBACK(on_btnImportarDiretorio_clicked), NULL);
	g_signal_connect((gpointer) FrmPrincipal.btnPesquisa, "clicked", G_CALLBACK(on_btnPesquisa_clicked), NULL);
	g_signal_connect((gpointer) FrmPrincipal.notebook1, "select_page", G_CALLBACK(on_notebook1_select_page), NULL);

	GtkTreeSelection *selecaoArvore = gtk_tree_view_get_selection(GTK_TREE_VIEW(FrmPrincipal.arvoreFixa));
	GtkTreeModel* modeloArvore = gtk_tree_view_get_model(GTK_TREE_VIEW(FrmPrincipal.arvoreFixa));

	g_signal_connect((gpointer) selecaoArvore, "changed", G_CALLBACK(on_arvoreFixa_selection_changed), modeloArvore);
	g_signal_connect((gpointer) FrmPrincipal.arvoreFixa, "row_collapsed", G_CALLBACK(on_arvoreFixa_row_collapsed), NULL);
	g_signal_connect((gpointer) FrmPrincipal.arvoreFixa, "button_release_event", G_CALLBACK(on_arvoreFixa_button_release_event), NULL);
	g_signal_connect((gpointer) FrmPrincipal.arvoreFixa, "row_expanded", G_CALLBACK(on_arvoreFixa_row_expanded), NULL);
	g_signal_connect((gpointer) FrmPrincipal.arvoreFixa, "button_press_event", G_CALLBACK(on_arvoreFixa_button_press_event), NULL);

	g_signal_connect((gpointer) FrmPrincipal.tabelaFixa, "button_release_event", G_CALLBACK(on_tabelaFixa_button_release_event), NULL);
	g_signal_connect((gpointer) FrmPrincipal.tabelaFixa, "row_activated", G_CALLBACK(on_tabelaFixa_row_activated), NULL);

	g_signal_connect((gpointer) FrmPrincipal.tabelaPesquisa, "button_release_event", G_CALLBACK(on_tabelaPesquisa_button_release_event), NULL);
	g_signal_connect((gpointer) FrmPrincipal.frmPrincipal, "delete_event", G_CALLBACK(on_FrmPrincipal_delete_event), NULL);


	g_signal_connect ((gpointer) FrmPrincipal.frmPrincipal, "destroy",
		G_CALLBACK (on_FrmPrincipal_destroy), NULL);

	ExtensaoBO_iniciar();
	FrmPrincipal_ConstruirPopupMenu();
	gtk_notebook_remove_page(GTK_NOTEBOOK(FrmPrincipal.notebook1), 0);

	Arvore_cria(GTK_TREE_VIEW(FrmPrincipal.arvoreFixa));
	Tabela_cria(TRUE, GTK_TREE_VIEW(FrmPrincipal.tabelaFixa));
	Tabela_cria(FALSE, GTK_TREE_VIEW(FrmPrincipal.tabelaPesquisa));

	FrmPrincipal_adicionaTabPage(GTK_NOTEBOOK(FrmPrincipal.notebook1), GTK_PANED(FrmPrincipal.sp), g_string_new("DISCO1"));

	gtk_paned_set_position(GTK_PANED(FrmPrincipal.sp), 250);
	gtk_paned_set_position(GTK_PANED(FrmPrincipal.spPesquisa), 400);

	gtk_widget_get_size_request(FrmPrincipal.barraStatus111, &FrmPrincipal.nLargura, &FrmPrincipal.nAltura);
	gtk_widget_set_size_request(FrmPrincipal.barraStatus111, 300, FrmPrincipal.nAltura);

	return FrmPrincipal.frmPrincipal;
}
// ---------------------------------------------------------------------------
void FrmPrincipal_Mostrar()
{
    FrmPrincipal.frmPrincipal = FrmPrincipal_Criar();
	gtk_window_set_position(GTK_WINDOW(FrmPrincipal.frmPrincipal), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_widget_show_all(FrmPrincipal.frmPrincipal);

	Catalogador_New();
	Arvore_selecionarPrimeiroItem(GTK_TREE_VIEW(FrmPrincipal.arvoreFixa));
}

void FrmPrincipal_ProgressoLog(Progresso progresso)
{
	if (FrmPrincipal.frmPrincipal != NULL) {
		if (progresso.posicao == 0) {
			gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(FrmPrincipal.pb), progresso.minimo);
			gtk_progress_bar_set_pulse_step(GTK_PROGRESS_BAR(FrmPrincipal.pb), 0.1); //progresso.passo
		}
		gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(FrmPrincipal.pb),
			Rotinas_calculaProgresso(progresso.maximo, progresso.posicao));
	}

}

void on_FrmPrincipal_destroy(GtkWidget* widget, gpointer user_data) {

}

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

 void FrmPrincipal_adicionaTabPage(GtkNotebook* noteBook, GtkPaned* spPanel, const GString* nomeAba) {
	GtkWidget* tabAba;
	GtkWidget* imgAba;
	GtkWidget* labAba;

	gtk_container_add(GTK_CONTAINER(FrmPrincipal.notebook1), GTK_WIDGET(spPanel));

	tabAba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_widget_set_name(GTK_WIDGET(tabAba), Rotinas_concatenar("tabAba", nomeAba->str)->str);
	gtk_widget_set_visible(tabAba, TRUE);
	gtk_widget_set_can_focus(tabAba, FALSE);

	imgAba = gtk_image_new_from_pixbuf(ExtensaoBO_CDOuroXPM);
	gtk_widget_set_name(GTK_WIDGET(imgAba), Rotinas_concatenar("imgAba", nomeAba->str)->str);
	gtk_widget_set_visible(imgAba, TRUE);
	gtk_widget_set_can_focus(imgAba, FALSE);

	labAba = gtk_label_new(nomeAba->str);
	gtk_widget_set_name(GTK_WIDGET(labAba), Rotinas_concatenar("labAba", nomeAba->str)->str);
	gtk_widget_set_visible(labAba, TRUE);
	gtk_widget_set_can_focus(labAba, FALSE);
	gtk_label_set_label(GTK_LABEL(labAba), nomeAba->str);

	gtk_container_add(GTK_CONTAINER(tabAba), imgAba);
	gtk_container_add(GTK_CONTAINER(tabAba), labAba);

	gtk_notebook_set_tab_label(noteBook, GTK_WIDGET(spPanel), tabAba);
	gtk_widget_show_all(tabAba);
	gtk_widget_show_all(GTK_WIDGET(noteBook));
}

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


void on_menuIncluirNovaAba_activate(GtkWidget* widget, gpointer user_data){
	Catalogador_IncluirNovaAba();
}

void on_menuAlterarNomeAbaAtiva_activate(GtkWidget* widget, gpointer user_data){
	Catalogador_AlterarNomeAbaAtiva(FrmPrincipal_ProgressoLog);
}

void on_menuExcluirAbaAtiva_activate(GtkWidget* widget, gpointer user_data){
	Catalogador_ExcluirAbaAtiva(FrmPrincipal_ProgressoLog);
}

void on_menuImportarDiretorio_activate(GtkWidget* widget, gpointer user_data){
	Catalogador_ComecaImportacao(FALSE, FrmPrincipal_ProgressoLog);
}

void on_menuImportarSubDiretorios_activate(GtkWidget* widget, gpointer user_data){
	Catalogador_ComecaImportacao(TRUE, FrmPrincipal_ProgressoLog);
}

void on_menuCompararDiretorios_activate(GtkWidget* widget, gpointer user_data){
    FrmCompararDiretorio_Mostrar();
}

void on_menuCadastrarExtensaoArquivo_activate(GtkWidget* widget, gpointer user_data){
    FrmCadExtensao_Mostrar();
}

void on_menuExpandirDiretorios_activate(GtkWidget* widget, gpointer user_data){
	Arvore_expandirTodos(Catalogador_getArvoreAtual());
}

void on_menuColapsarDiretorios_activate(GtkWidget* widget, gpointer user_data){
	Arvore_colapsarTodos(Catalogador_getArvoreAtual());
}

void on_menuExportarDiretoriosAbaAtiva_activate(GtkWidget* widget, gpointer user_data){

}

void on_menuTXT_activate(GtkWidget* widget, gpointer user_data){
	Catalogador_ExportarArquivo(teTXT, FrmPrincipal_ProgressoLog);
}

void on_menuCSV_activate(GtkWidget* widget, gpointer user_data){
	Catalogador_ExportarArquivo(teCSV, FrmPrincipal_ProgressoLog);
}

void on_menuHTML_activate(GtkWidget* widget, gpointer user_data){
	Catalogador_ExportarArquivo(teHTML, FrmPrincipal_ProgressoLog);
}

void on_menuXML_activate(GtkWidget* widget, gpointer user_data){
	Catalogador_ExportarArquivo(teXML, FrmPrincipal_ProgressoLog);
}

void on_menuSQL_activate(GtkWidget* widget, gpointer user_data){
	Catalogador_ExportarArquivo(teSQL, FrmPrincipal_ProgressoLog);
}

void on_menuImportarDiretoriosViaXML_activate(GtkWidget* widget, gpointer user_data){
	ListaString log = ListaString_inicia();
	Catalogador_ImportarArquivo(log, FrmPrincipal_ProgressoLog);
}

void on_menuMostrarOcultarArvoreDirAbaAtiva_activate(GtkWidget* widget, gpointer user_data){
	Catalogador_mostrarOcultarArvore();
}

void on_menuMostrarOcultarListaItensPesquisados_activate(GtkWidget* widget, gpointer user_data){
	Catalogador_mostrarOcultarListaItensPesquisados();
}

void on_menuSobreCatalogador_activate(GtkWidget* widget, gpointer user_data){
    FrmSobre_Mostrar();
}

void on_btnImportarDiretorio_clicked(GtkWidget* widget, gpointer user_data){
	on_menuImportarDiretorio_activate(widget, user_data);
}

void on_btnPesquisa_clicked(GtkWidget* widget, gpointer user_data){
	Catalogador_Pesquisar();
}

void on_notebook1_select_page(GtkNotebook *notebook, gboolean arg1, gpointer user_data){
	Catalogador_tabPanelMudou();
}

void on_arvoreFixa_selection_changed(GtkTreeSelection *treeselection, gpointer user_data) {
	GtkTreeModel* arvore_modelo;
	GtkTreeIter iter;

	arvore_modelo = GTK_TREE_MODEL(user_data);

	if (gtk_tree_selection_get_selected(treeselection, &arvore_modelo, &iter)) {
		GtkTreeView* tabela = Catalogador_getTabelaAtual();
		GtkTreeView* arvore = Catalogador_getArvoreAtual();
		Catalogador_ListarArquivos(tabela, arvore, iter);
	}
}

void on_arvoreFixa_row_collapsed(GtkTreeView *tree_view, GtkTreeIter *iter, GtkTreePath *path, gpointer user_data){
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
}

gboolean on_arvoreFixa_button_release_event(GtkWidget *widget, GdkEvent *event, gpointer user_data){
	if (event->button.button == 3) {
		//gtk_menu_popup(GTK_MENU(FrmPrincipal.popupMenu), NULL, NULL, NULL, NULL,
		//	event->button.button, gtk_get_current_event_time());
		gtk_menu_popup_at_widget(GTK_MENU(FrmPrincipal.popupMenu), widget,
			GDK_GRAVITY_NORTH_WEST, GDK_GRAVITY_NORTH_WEST, event);
	}
	return FALSE;
}

gboolean on_arvoreFixa_button_press_event(GtkWidget *widget, GdkEvent *event, gpointer user_data) {
	GtkTreeView* arvore;

	if (event->button.button == 1) {
		if (event->button.type == GDK_2BUTTON_PRESS) {
			arvore = (GtkTreeView*)widget;
			Arvore_expandirSelecionado(arvore);
		}
	}
	return FALSE;
}

void on_arvoreFixa_row_expanded(GtkTreeView *tree_view, GtkTreeIter *iter, GtkTreePath *path, gpointer user_data){
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
}

gboolean on_tabelaFixa_button_release_event(GtkWidget *widget, GdkEvent *event, gpointer user_data){

	if (event->button.button == 3) {
		//gtk_menu_popup(GTK_MENU(FrmPrincipal.popupMenu), NULL, NULL, NULL, NULL,
			//event->button.button, gtk_get_current_event_time());
		gtk_menu_popup_at_widget(GTK_MENU(FrmPrincipal.popupMenu), widget,
			GDK_GRAVITY_NORTH_WEST, GDK_GRAVITY_NORTH_WEST, event);
	}
	return FALSE;
}

void on_tabelaFixa_row_activated(GtkTreeView *tree_view, GtkTreePath *path,
	GtkTreeViewColumn *column, gpointer user_data){
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

}

gboolean on_tabelaPesquisa_button_release_event(GtkWidget *widget, GdkEvent *event, gpointer user_data){
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
	return FALSE;
}

gboolean on_FrmPrincipal_delete_event(GtkWidget *widget, GdkEvent *event, gpointer user_data){
	Rotinas_BancoDesconectar();

	gtk_main_quit();
	return TRUE;
}

void FrmPrincipal_menuInformacoesDiretorioArquivo_activate(GtkWidget* widget, gpointer user_data) {
	Catalogador_InformacoesDiretorioArquivo();
}

void FrmPrincipal_menuExcluirDiretorioSelecionado_activate(GtkWidget* widget, gpointer user_data) {
	Catalogador_ExcluirDiretorioSelecionado(FrmPrincipal_ProgressoLog);
}

void FrmPrincipal_menuIncluirNovaAba2_activate(GtkWidget* widget, gpointer user_data) {
	on_menuIncluirNovaAba_activate(widget, user_data);
}

void FrmPrincipal_menuAlterarNomeAbaAtiva2_activate(GtkWidget* widget, gpointer user_data) {
	on_menuAlterarNomeAbaAtiva_activate(widget, user_data);
}

void FrmPrincipal_menuExcluirAbaAtiva2_activate(GtkWidget* widget, gpointer user_data) {
	on_menuExcluirAbaAtiva_activate(widget, user_data);
}

void FrmPrincipal_menuExpandirDiretorios2_activate(GtkWidget* widget, gpointer user_data) {
	on_menuExpandirDiretorios_activate(widget, user_data);
}

void FrmPrincipal_menuColapsarDiretorios2_activate(GtkWidget* widget, gpointer user_data) {
	on_menuColapsarDiretorios_activate(widget, user_data);
}

