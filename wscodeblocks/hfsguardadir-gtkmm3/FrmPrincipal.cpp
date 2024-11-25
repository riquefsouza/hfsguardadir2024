#include "FrmPrincipal.h"
#include "hfsguardadir/comum/Rotinas.h"

#include <gtkmm/main.h>

#include "FrmCadExtensao.h"
#include "FrmCompararDiretorio.h"
#include "FrmImportarDiretorio.h"
#include "FrmInfoDiretorio.h"
#include "FrmSobre.h"
#include "hfsguardadir/catalogador/Catalogador.h"
#include "hfsguardadir/objetosbo/ExtensaoBO.h"

using namespace hfsguardadir::comum;
using namespace hfsguardadir::catalogador;
using namespace hfsguardadir::objetosbo;

// ---------------------------------------------------------------------------
FrmPrincipal *frmPrincipal = (FrmPrincipal*) NULL;
// ---------------------------------------------------------------------------
FrmPrincipal::FrmPrincipal()
	: Gtk::Window(Gtk::WINDOW_TOPLEVEL) {

	barraStatus211 = manage(new class Gtk::Statusbar());
	barraStatus211->set_name("barraStatus211");
	barraStatus211->set_visible(true);
	barraStatus211->set_can_focus(false);
	barraStatus211->set_spacing(2);

	barraStatus111 = manage(new class Gtk::Statusbar());
	barraStatus111->set_name("barraStatus111");
	barraStatus111->set_size_request(300, -1);
	barraStatus111->set_visible(true);
	barraStatus111->set_can_focus(false);
	barraStatus111->set_spacing(2);
	//barraStatus111->set_has_resize_grip(false);

	hbox6 = manage(new class Gtk::HBox(false, 0));
	hbox6->set_name("hbox6");
	hbox6->set_visible(true);
	hbox6->set_can_focus(false);
	hbox6->pack_start(*barraStatus111, false, true, 0);
	hbox6->pack_start(*barraStatus211, true, true, 0);

	tabelaPesquisa = manage(new class Tabela(false));
	tabelaPesquisa->set_name("tabelaPesquisa");
	tabelaPesquisa->set_visible(true);
	tabelaPesquisa->set_can_focus(true);

	scrollPesquisa = manage(new class Gtk::ScrolledWindow());
	scrollPesquisa->set_name("scrollPesquisa");
	scrollPesquisa->set_visible(true);
	scrollPesquisa->set_can_focus(true);
	scrollPesquisa->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	scrollPesquisa->add(*tabelaPesquisa);

	tabelaFixa = manage(new class Tabela(true));
	tabelaFixa->set_name("tabelaFixa");
	tabelaFixa->set_visible(true);
	tabelaFixa->set_can_focus(true);

	scrollTabelaFixa = manage(new class Gtk::ScrolledWindow());
	scrollTabelaFixa->set_name("scrollTabelaFixa");
	scrollTabelaFixa->set_visible(true);
	scrollTabelaFixa->set_can_focus(true);
	scrollTabelaFixa->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	scrollTabelaFixa->set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
	scrollTabelaFixa->add(*tabelaFixa);

	arvoreFixa = manage(new class Arvore());
	arvoreFixa->set_name("arvoreFixa");
	arvoreFixa->set_visible(true);
	arvoreFixa->set_can_focus(true);

	scrollArvore = manage(new class Gtk::ScrolledWindow());
	scrollArvore->set_name("scrollArvore");
	scrollArvore->set_visible(true);
	scrollArvore->set_can_focus(true);
	scrollArvore->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	scrollArvore->set_shadow_type(Gtk::SHADOW_IN);
	scrollArvore->add(*arvoreFixa);

	sp = manage(new class Gtk::HPaned());
	sp->set_name("sp");
	sp->set_visible(true);
	sp->set_can_focus(true);
	sp->set_position(250);
	sp->add(*scrollArvore);
	sp->add(*scrollTabelaFixa);

	notebook1 = manage(new class Gtk::Notebook());
	notebook1->set_name("notebook1");
	notebook1->set_visible(true);
	notebook1->set_can_focus(true);

	spPesquisa = manage(new class Gtk::VPaned());
	spPesquisa->set_name("spPesquisa");
	spPesquisa->set_visible(true);
	spPesquisa->set_can_focus(true);
	spPesquisa->set_position(250);
	spPesquisa->add(*notebook1);
	spPesquisa->add(*scrollPesquisa);

	btnPesquisa = manage(new class Gtk::Button());
	btnPesquisa->set_name("btnPesquisa");
	btnPesquisa->set_label("Pesquisar");
	btnPesquisa->set_visible(true);
	btnPesquisa->set_can_focus(false);
	btnPesquisa->set_receives_default(false);
	btnPesquisa->set_use_underline(true);

	toolbutton4 = manage(new class Gtk::ToolItem());
	toolbutton4->set_name("toolbutton4");
	toolbutton4->set_visible(true);
	toolbutton4->set_can_focus(false);
	toolbutton4->add(*btnPesquisa);

	edtPesquisa = manage(new class Gtk::Entry());
	edtPesquisa->set_name("edtPesquisa");
	edtPesquisa->set_size_request(325, -1);
	edtPesquisa->set_visible(true);
	edtPesquisa->set_can_focus(true);
	edtPesquisa->set_max_length(10);
	edtPesquisa->set_icon_activatable(false, Gtk::ENTRY_ICON_PRIMARY);
	edtPesquisa->set_icon_activatable(false, Gtk::ENTRY_ICON_SECONDARY);
	edtPesquisa->set_icon_sensitive(Gtk::ENTRY_ICON_PRIMARY, true);
	edtPesquisa->set_icon_sensitive(Gtk::ENTRY_ICON_SECONDARY, true);

	toolbutton3 = manage(new class Gtk::ToolItem());
	toolbutton3->set_name("toolbutton3");
	toolbutton3->set_visible(true);
	toolbutton3->set_can_focus(false);
	toolbutton3->add(*edtPesquisa);

	pb = manage(new class Gtk::ProgressBar());
	pb->set_name("pb");
	pb->set_size_request(385, -1);
	pb->set_visible(true);
	pb->set_can_focus(false);

	toolbutton2 = manage(new class Gtk::ToolItem());
	toolbutton2->set_name("toolbutton2");
	toolbutton2->set_size_request(222, -1);
	toolbutton2->set_visible(true);
	toolbutton2->set_can_focus(false);
	toolbutton2->add(*pb);

	btnImportarDiretorio = manage(new class Gtk::Button());
	btnImportarDiretorio->set_name("btnImportarDiretorio");
	btnImportarDiretorio->set_label("Importar Diretorio");
	btnImportarDiretorio->set_visible(true);
	btnImportarDiretorio->set_can_focus(false);
	btnImportarDiretorio->set_receives_default(false);
	btnImportarDiretorio->set_use_underline(true);

	toolbutton1 = manage(new class Gtk::ToolItem());
	toolbutton1->set_name("toolbutton1");
	toolbutton1->set_visible(true);
	toolbutton1->set_can_focus(false);
	toolbutton1->add(*btnImportarDiretorio);

	toolbar1 = manage(new class Gtk::Toolbar());
	toolbar1->set_name("toolbar1");
	toolbar1->set_visible(true);
	toolbar1->set_can_focus(false);
	toolbar1->add(*toolbutton1);
	toolbar1->add(*toolbutton2);
	toolbar1->add(*toolbutton3);
	toolbar1->add(*toolbutton4);

	menuSobreCatalogador = manage(new class Gtk::MenuItem());
	menuSobreCatalogador->set_name("menuSobreCatalogador");
	menuSobreCatalogador->set_visible(true);
	menuSobreCatalogador->set_can_focus(false);
	menuSobreCatalogador->set_label("Sobre o Catalogador");
	menuSobreCatalogador->set_use_underline(true);

	submenuSobre = manage(new class Gtk::Menu());
	submenuSobre->set_name("submenuSobre");
	submenuSobre->set_visible(true);
	submenuSobre->set_can_focus(false);
	submenuSobre->append(*menuSobreCatalogador);

	menuSobre = manage(new class Gtk::MenuItem());
	menuSobre->set_name("menuSobre");
	menuSobre->set_visible(true);
	menuSobre->set_can_focus(false);
	menuSobre->set_label("Sobre");
	menuSobre->set_use_underline(true);
	menuSobre->set_submenu(*submenuSobre);

	menuMostrarOcultarListaItensPesquisados = manage(new class Gtk::MenuItem());
	menuMostrarOcultarListaItensPesquisados->set_name("menuMostrarOcultarListaItensPesquisados");
	menuMostrarOcultarListaItensPesquisados->set_visible(true);
	menuMostrarOcultarListaItensPesquisados->set_can_focus(false);
	menuMostrarOcultarListaItensPesquisados->set_label("Mostrar/Ocultar lista de itens pesquisados");
	menuMostrarOcultarListaItensPesquisados->set_use_underline(true);

	menuMostrarOcultarArvoreDirAbaAtiva = manage(new class Gtk::MenuItem());
	menuMostrarOcultarArvoreDirAbaAtiva->set_name("menuMostrarOcultarArvoreDirAbaAtiva");
	menuMostrarOcultarArvoreDirAbaAtiva->set_visible(true);
	menuMostrarOcultarArvoreDirAbaAtiva->set_can_focus(false);
	menuMostrarOcultarArvoreDirAbaAtiva->set_label(Rotinas::retUTF8("Mostrar/Ocultar árvore de diretórios da Aba Ativa"));
	menuMostrarOcultarArvoreDirAbaAtiva->set_use_underline(true);

	submenuVisao = manage(new class Gtk::Menu());
	submenuVisao->set_name("submenuVisao");
	submenuVisao->set_visible(true);
	submenuVisao->set_can_focus(false);
	submenuVisao->append(*menuMostrarOcultarArvoreDirAbaAtiva);
	submenuVisao->append(*menuMostrarOcultarListaItensPesquisados);

	menuVisao = manage(new class Gtk::MenuItem());
	menuVisao->set_name("menuVisao");
	menuVisao->set_visible(true);
	menuVisao->set_can_focus(false);
	menuVisao->set_label(Rotinas::retUTF8("Visão"));
	menuVisao->set_submenu(*submenuVisao);

	menuGravarLogImportacao = manage(new class Gtk::MenuItem());
	menuGravarLogImportacao->set_name("menuGravarLogImportacao");
	menuGravarLogImportacao->set_visible(true);
	menuGravarLogImportacao->set_can_focus(false);
	menuGravarLogImportacao->set_label(Rotinas::retUTF8("Gravar Log da Importação"));
	menuGravarLogImportacao->set_use_underline(true);

	menuImportarDiretoriosViaXML = manage(new class Gtk::MenuItem());
	menuImportarDiretoriosViaXML->set_name("menuImportarDiretoriosViaXML");
	menuImportarDiretoriosViaXML->set_visible(true);
	menuImportarDiretoriosViaXML->set_can_focus(false);
	menuImportarDiretoriosViaXML->set_label(Rotinas::retUTF8("Importar Diretórios via XML"));
	menuImportarDiretoriosViaXML->set_use_underline(true);

	menuSQL = manage(new class Gtk::MenuItem());
	menuSQL->set_name("menuSQL");
	menuSQL->set_visible(true);
	menuSQL->set_can_focus(false);
	menuSQL->set_label("SQL");
	menuSQL->set_use_underline(true);

	menuXML = manage(new class Gtk::MenuItem());
	menuXML->set_name("menuXML");
	menuXML->set_visible(true);
	menuXML->set_can_focus(false);
	menuXML->set_label("XML");
	menuXML->set_use_underline(true);

	menuHTML = manage(new class Gtk::MenuItem());
	menuHTML->set_name("menuHTML");
	menuHTML->set_visible(true);
	menuHTML->set_can_focus(false);
	menuHTML->set_label("HTML");
	menuHTML->set_use_underline(true);

	menuCSV = manage(new class Gtk::MenuItem());
	menuCSV->set_name("menuCSV");
	menuCSV->set_visible(true);
	menuCSV->set_can_focus(false);
	menuCSV->set_label("CSV");
	menuCSV->set_use_underline(true);

	menuTXT = manage(new class Gtk::MenuItem());
	menuTXT->set_name("menuTXT");
	menuTXT->set_visible(true);
	menuTXT->set_can_focus(false);
	menuTXT->set_label("TXT");
	menuTXT->set_use_underline(true);

	menu2 = manage(new class Gtk::Menu());
	menu2->set_name("menu2");
	menu2->set_visible(true);
	menu2->set_can_focus(false);
	menu2->append(*menuTXT);
	menu2->append(*menuCSV);
	menu2->append(*menuHTML);
	menu2->append(*menuXML);
	menu2->append(*menuSQL);

	menuExportarDiretoriosAbaAtiva = manage(new class Gtk::MenuItem());
	menuExportarDiretoriosAbaAtiva->set_name("menuExportarDiretoriosAbaAtiva");
	menuExportarDiretoriosAbaAtiva->set_visible(true);
	menuExportarDiretoriosAbaAtiva->set_can_focus(false);
	menuExportarDiretoriosAbaAtiva->set_label(Rotinas::retUTF8("Exportar Diretórios da Aba Ativa"));
	menuExportarDiretoriosAbaAtiva->set_use_underline(true);
	menuExportarDiretoriosAbaAtiva->set_submenu(*menu2);

	menuColapsarDiretorios = manage(new class Gtk::MenuItem());
	menuColapsarDiretorios->set_name("menuColapsarDiretorios");
	menuColapsarDiretorios->set_visible(true);
	menuColapsarDiretorios->set_can_focus(false);
	menuColapsarDiretorios->set_label(Rotinas::retUTF8("Colapsar Diretórios"));
	menuColapsarDiretorios->set_use_underline(true);

	menuExpandirDiretorios = manage(new class Gtk::MenuItem());
	menuExpandirDiretorios->set_name("menuExpandirDiretorios");
	menuExpandirDiretorios->set_visible(true);
	menuExpandirDiretorios->set_can_focus(false);
	menuExpandirDiretorios->set_label(Rotinas::retUTF8("Expandir Diretórios"));
	menuExpandirDiretorios->set_use_underline(true);

	menuseparador1 = manage(new class Gtk::SeparatorMenuItem());
	menuseparador1->set_name("menuseparador1");
	menuseparador1->set_visible(true);
	menuseparador1->set_can_focus(false);

	menuCadastrarExtensaoArquivo = manage(new class Gtk::MenuItem());
	menuCadastrarExtensaoArquivo->set_name("menuCadastrarExtensaoArquivo");
	menuCadastrarExtensaoArquivo->set_visible(true);
	menuCadastrarExtensaoArquivo->set_can_focus(false);
	menuCadastrarExtensaoArquivo->set_label(Rotinas::retUTF8("Cadastrar Extensão de Arquivo"));
	menuCadastrarExtensaoArquivo->set_use_underline(true);

	menuCompararDiretorios = manage(new class Gtk::MenuItem());
	menuCompararDiretorios->set_name("menuCompararDiretorios");
	menuCompararDiretorios->set_visible(true);
	menuCompararDiretorios->set_can_focus(false);
	menuCompararDiretorios->set_label(Rotinas::retUTF8("Comparar Diretórios"));
	menuCompararDiretorios->set_use_underline(true);

	menuImportarSubDiretorios = manage(new class Gtk::MenuItem());
	menuImportarSubDiretorios->set_name("menuImportarSubDiretorios");
	menuImportarSubDiretorios->set_visible(true);
	menuImportarSubDiretorios->set_can_focus(false);
	menuImportarSubDiretorios->set_label(Rotinas::retUTF8("Importar SubDiretórios"));
	menuImportarSubDiretorios->set_use_underline(true);

	menuImportarDiretorio = manage(new class Gtk::MenuItem());
	menuImportarDiretorio->set_name("menuImportarDiretorio");
	menuImportarDiretorio->set_visible(true);
	menuImportarDiretorio->set_can_focus(false);
	menuImportarDiretorio->set_label(Rotinas::retUTF8("Importar Diretório"));
	menuImportarDiretorio->set_use_underline(true);

	submenuDiretorio = manage(new class Gtk::Menu());
	submenuDiretorio->set_name("submenuDiretorio");
	submenuDiretorio->set_visible(true);
	submenuDiretorio->set_can_focus(false);
	submenuDiretorio->append(*menuImportarDiretorio);
	submenuDiretorio->append(*menuImportarSubDiretorios);
	submenuDiretorio->append(*menuCompararDiretorios);
	submenuDiretorio->append(*menuCadastrarExtensaoArquivo);
	submenuDiretorio->append(*menuseparador1);
	submenuDiretorio->append(*menuExpandirDiretorios);
	submenuDiretorio->append(*menuColapsarDiretorios);
	submenuDiretorio->append(*menuExportarDiretoriosAbaAtiva);
	submenuDiretorio->append(*menuImportarDiretoriosViaXML);
	submenuDiretorio->append(*menuGravarLogImportacao);

	menuDiretorio = manage(new class Gtk::MenuItem());
	menuDiretorio->set_name("menuDiretorio");
	menuDiretorio->set_visible(true);
	menuDiretorio->set_can_focus(false);
	menuDiretorio->set_label(Rotinas::retUTF8("Diretório"));
	menuDiretorio->set_submenu(*submenuDiretorio);

	menuExcluirAbaAtiva = manage(new class Gtk::MenuItem());
	menuExcluirAbaAtiva->set_name("menuExcluirAbaAtiva");
	menuExcluirAbaAtiva->set_visible(true);
	menuExcluirAbaAtiva->set_can_focus(false);
	menuExcluirAbaAtiva->set_label("Excluir Aba Ativa");
	menuExcluirAbaAtiva->set_use_underline(true);

	menuAlterarNomeAbaAtiva = manage(new class Gtk::MenuItem());
	menuAlterarNomeAbaAtiva->set_name("menuAlterarNomeAbaAtiva");
	menuAlterarNomeAbaAtiva->set_visible(true);
	menuAlterarNomeAbaAtiva->set_can_focus(false);
	menuAlterarNomeAbaAtiva->set_label("Alterar Nome da Aba Ativa");
	menuAlterarNomeAbaAtiva->set_use_underline(true);

	menuIncluirNovaAba = manage(new class Gtk::MenuItem());
	menuIncluirNovaAba->set_name("menuIncluirNovaAba");
	menuIncluirNovaAba->set_visible(true);
	menuIncluirNovaAba->set_can_focus(false);
	menuIncluirNovaAba->set_label("Incluir Nova Aba");
	menuIncluirNovaAba->set_use_underline(true);

	submenuAba = manage(new class Gtk::Menu());
	submenuAba->set_name("submenuAba");
	submenuAba->set_visible(true);
	submenuAba->set_can_focus(false);
	submenuAba->append(*menuIncluirNovaAba);
	submenuAba->append(*menuAlterarNomeAbaAtiva);
	submenuAba->append(*menuExcluirAbaAtiva);

	menuAba = manage(new class Gtk::MenuItem());
	menuAba->set_name("menuAba");
	menuAba->set_visible(true);
	menuAba->set_can_focus(false);
	menuAba->set_label("Aba");
	menuAba->set_submenu(*submenuAba);

	barraMenu1 = manage(new class Gtk::MenuBar());
	barraMenu1->set_name("barraMenu1");
	barraMenu1->set_visible(true);
	barraMenu1->set_can_focus(false);
	barraMenu1->append(*menuAba);
	barraMenu1->append(*menuDiretorio);
	barraMenu1->append(*menuVisao);
	barraMenu1->append(*menuSobre);

	vbox1 = manage(new class Gtk::VBox(false, 0));
	vbox1->set_name("vbox1");
	vbox1->set_visible(true);
	vbox1->set_can_focus(false);
	vbox1->pack_start(*barraMenu1, false, true, 0);
	vbox1->pack_start(*toolbar1, false, true, 0);
	vbox1->pack_start(*spPesquisa, true, true, 0);
	vbox1->pack_start(*hbox6, false, true, 0);

	this->set_name("FrmPrincipal");
	this->set_size_request(1200, 800);
	this->set_visible(true);
	this->set_can_focus(false);
	this->set_title(Rotinas::retUTF8("HFSGuardaDiretorio 2.0 - Catalogador de Diretórios"));
	this->set_position(Gtk::WIN_POS_CENTER_ALWAYS);
	this->set_default_size(1200, 800);
	this->add(*vbox1);


	menuIncluirNovaAba->signal_activate().connect(sigc::mem_fun(*this, &FrmPrincipal::on_menuIncluirNovaAba_activate));
	menuAlterarNomeAbaAtiva->signal_activate().connect(sigc::mem_fun(*this, &FrmPrincipal::on_menuAlterarNomeAbaAtiva_activate));
	menuExcluirAbaAtiva->signal_activate().connect(sigc::mem_fun(*this, &FrmPrincipal::on_menuExcluirAbaAtiva_activate));
	menuImportarDiretorio->signal_activate().connect(sigc::mem_fun(*this, &FrmPrincipal::on_menuImportarDiretorio_activate));
	menuImportarSubDiretorios->signal_activate().connect(sigc::mem_fun(*this, &FrmPrincipal::on_menuImportarSubDiretorios_activate));
	menuCompararDiretorios->signal_activate().connect(sigc::mem_fun(*this, &FrmPrincipal::on_menuCompararDiretorios_activate));
	menuCadastrarExtensaoArquivo->signal_activate().connect(sigc::mem_fun(*this, &FrmPrincipal::on_menuCadastrarExtensaoArquivo_activate));
	menuExpandirDiretorios->signal_activate().connect(sigc::mem_fun(*this, &FrmPrincipal::on_menuExpandirDiretorios_activate));
	menuColapsarDiretorios->signal_activate().connect(sigc::mem_fun(*this, &FrmPrincipal::on_menuColapsarDiretorios_activate));
	menuExportarDiretoriosAbaAtiva->signal_activate().connect(sigc::mem_fun(*this, &FrmPrincipal::on_menuExportarDiretoriosAbaAtiva_activate));
	menuTXT->signal_activate().connect(sigc::mem_fun(*this, &FrmPrincipal::on_menuTXT_activate));
	menuCSV->signal_activate().connect(sigc::mem_fun(*this, &FrmPrincipal::on_menuCSV_activate));
	menuHTML->signal_activate().connect(sigc::mem_fun(*this, &FrmPrincipal::on_menuHTML_activate));
	menuXML->signal_activate().connect(sigc::mem_fun(*this, &FrmPrincipal::on_menuXML_activate));
	menuSQL->signal_activate().connect(sigc::mem_fun(*this, &FrmPrincipal::on_menuSQL_activate));
	menuImportarDiretoriosViaXML->signal_activate().connect(sigc::mem_fun(*this, &FrmPrincipal::on_menuImportarDiretoriosViaXML_activate));
	menuMostrarOcultarArvoreDirAbaAtiva->signal_activate().connect(sigc::mem_fun(*this, &FrmPrincipal::on_menuMostrarOcultarArvoreDirAbaAtiva_activate));
	menuMostrarOcultarListaItensPesquisados->signal_activate().connect(sigc::mem_fun(*this, &FrmPrincipal::on_menuMostrarOcultarListaItensPesquisados_activate));
	menuSobreCatalogador->signal_activate().connect(sigc::mem_fun(*this, &FrmPrincipal::on_menuSobreCatalogador_activate));
	btnImportarDiretorio->signal_clicked().connect(sigc::mem_fun(*this, &FrmPrincipal::on_btnImportarDiretorio_clicked));
	btnPesquisa->signal_clicked().connect(sigc::mem_fun(*this, &FrmPrincipal::on_btnPesquisa_clicked));

	notebook1->signal_switch_page().connect(sigc::mem_fun(*this, &FrmPrincipal::on_notebook1_switch_page));

	arvoreFixa->get_selection()->signal_changed().connect(sigc::mem_fun(*this, &FrmPrincipal::on_arvoreFixa_selection_changed));
	arvoreFixa->signal_row_collapsed().connect(sigc::mem_fun(*this, &FrmPrincipal::on_arvoreFixa_row_collapsed));
	arvoreFixa->signal_button_release_event().connect(sigc::mem_fun(*this, &FrmPrincipal::on_arvoreFixa_button_release_event));
	arvoreFixa->signal_button_press_event().connect(sigc::mem_fun(*this, &FrmPrincipal::on_arvoreFixa_button_press_event));
	arvoreFixa->signal_row_expanded().connect(sigc::mem_fun(*this, &FrmPrincipal::on_arvoreFixa_row_expanded));

	tabelaFixa->signal_button_release_event().connect(sigc::mem_fun(*this, &FrmPrincipal::on_tabelaFixa_button_release_event));
	tabelaFixa->signal_row_activated().connect(sigc::mem_fun(*this, &FrmPrincipal::on_tabelaFixa_row_activated));
	tabelaPesquisa->signal_button_release_event().connect(sigc::mem_fun(*this, &FrmPrincipal::on_tabelaPesquisa_button_release_event));

	this->signal_delete_event().connect(sigc::mem_fun(*this, &FrmPrincipal::on_FrmPrincipal_delete_event));


	ExtensaoBO::getInstancia();
	ConstruirPopupMenu();
	notebook1->remove_page(0);

	adicionaTabPage(notebook1, sp, "DISCO1");

	sp->set_position(250);
	spPesquisa->set_position(400);

	barraStatus111->get_size_request(nLargura, nAltura);
	barraStatus111->set_size_request(300, nAltura);

}
// ---------------------------------------------------------------------------
FrmPrincipal::~FrmPrincipal(){

}
// ---------------------------------------------------------------------------
void FrmPrincipal::Mostrar()
{
    frmPrincipal = new FrmPrincipal();
	frmPrincipal->set_position(Gtk::WIN_POS_CENTER_ALWAYS);
	frmPrincipal->show_all();

	catalogador = new Catalogador();
	frmPrincipal->arvoreFixa->selecionarPrimeiroItem();
}

void FrmPrincipal::ProgressoLog(Progresso progresso)
{
	if (frmPrincipal != NULL) {
		if (progresso.posicao == 0) {
			frmPrincipal->pb->set_fraction(progresso.minimo);
			frmPrincipal->pb->set_pulse_step(0.1); //progresso.passo
		}
		frmPrincipal->pb->set_fraction(
			Rotinas::calculaProgresso(progresso.maximo, progresso.posicao));
	}
}

Gtk::Label* FrmPrincipal::getLabStatus1() {
	Glib::ListHandle<Gtk::Widget*> hlista = barraStatus111->get_children();
	std::vector<Gtk::Widget*, std::allocator<Gtk::Widget*>> lista =
		hlista.operator std::vector<Gtk::Widget*, std::allocator<Gtk::Widget*>>();
	Gtk::Frame* frameStatus1 = static_cast<Gtk::Frame*>(lista.at(0));

	Glib::ListHandle<Gtk::Widget*> hlista2 = frameStatus1->get_children();
	std::vector<Gtk::Widget*, std::allocator<Gtk::Widget*>> lista2 =
		hlista2.operator std::vector<Gtk::Widget*, std::allocator<Gtk::Widget*>>();
	Gtk::HBox* hboxStatus1 = static_cast<Gtk::HBox*>(lista2.at(0));

	Glib::ListHandle<Gtk::Widget*> hlista3 = hboxStatus1->get_children();
	std::vector<Gtk::Widget*, std::allocator<Gtk::Widget*>> lista3 =
		hlista3.operator std::vector<Gtk::Widget*, std::allocator<Gtk::Widget*>>();
	Gtk::Label* labStatus1 = static_cast<Gtk::Label*>(lista3.at(0));

	return labStatus1;
}

Gtk::Label* FrmPrincipal::getLabStatus2() {
	Glib::ListHandle<Gtk::Widget*> hlista = barraStatus211->get_children();
	std::vector<Gtk::Widget*, std::allocator<Gtk::Widget*>> lista =
		hlista.operator std::vector<Gtk::Widget*, std::allocator<Gtk::Widget*>>();
	Gtk::Frame* frameStatus2 = static_cast<Gtk::Frame*>(lista.at(0));

	Glib::ListHandle<Gtk::Widget*> hlista2 = frameStatus2->get_children();
	std::vector<Gtk::Widget*, std::allocator<Gtk::Widget*>> lista2 =
		hlista2.operator std::vector<Gtk::Widget*, std::allocator<Gtk::Widget*>>();
	Gtk::HBox* hboxStatus2 = static_cast<Gtk::HBox*>(lista2.at(0));

	Glib::ListHandle<Gtk::Widget*> hlista3 = hboxStatus2->get_children();
	std::vector<Gtk::Widget*, std::allocator<Gtk::Widget*>> lista3 =
		hlista3.operator std::vector<Gtk::Widget*, std::allocator<Gtk::Widget*>>();
	Gtk::Label* labStatus2 = static_cast<Gtk::Label*>(lista3.at(0));

	return labStatus2;
}

void FrmPrincipal::adicionaTabPage(Gtk::Notebook* noteBook, Gtk::HPaned* spPanel, const Glib::ustring nomeAba) {
	Gtk::HBox* tabAba;
	Gtk::Image* imgAba;
	Gtk::Label* labAba;

	notebook1->add(*spPanel);

	tabAba = manage(new class Gtk::HBox(false, 0));
	tabAba->set_name("tabAba" + nomeAba);
	tabAba->set_visible(true);
	tabAba->set_can_focus(false);

	imgAba = manage(new class Gtk::Image(ExtensaoBO::getInstancia()->CDOuroXPM));
	imgAba->set_name("imgAba" + nomeAba);
	imgAba->set_visible(true);
	imgAba->set_can_focus(false);

	labAba = manage(new class Gtk::Label(nomeAba));
	labAba->set_name("labAba" + nomeAba);
	labAba->set_visible(true);
	labAba->set_can_focus(false);
	labAba->set_label(nomeAba);

	tabAba->add(*imgAba);
	tabAba->add(*labAba);

	noteBook->set_tab_label(*spPanel, *tabAba);
	tabAba->show_all();
	noteBook->show_all();
}

void FrmPrincipal::ConstruirPopupMenu() {

	menuInformacoesDiretorioArquivo = manage(new class Gtk::MenuItem());
	menuInformacoesDiretorioArquivo->set_name("menuInformacoesDiretorioArquivo");
	menuInformacoesDiretorioArquivo->set_visible(true);
	menuInformacoesDiretorioArquivo->set_can_focus(false);
	menuInformacoesDiretorioArquivo->set_label(Rotinas::retUTF8("Informações do Diretório / Arquivo"));
	menuInformacoesDiretorioArquivo->set_use_underline(true);
	menuInformacoesDiretorioArquivo->show();

	menuExcluirDiretorioSelecionado = manage(new class Gtk::MenuItem());
	menuExcluirDiretorioSelecionado->set_name("menuExcluirDiretorioSelecionado");
	menuExcluirDiretorioSelecionado->set_visible(true);
	menuExcluirDiretorioSelecionado->set_can_focus(false);
	menuExcluirDiretorioSelecionado->set_label(Rotinas::retUTF8("Excluir Diretório Selecionado"));
	menuExcluirDiretorioSelecionado->set_use_underline(true);
	menuExcluirDiretorioSelecionado->show();

	menuExpandirDiretorios2 = manage(new class Gtk::MenuItem());
	menuExpandirDiretorios2->set_name("menuExpandirDiretorios2");
	menuExpandirDiretorios2->set_visible(true);
	menuExpandirDiretorios2->set_can_focus(false);
	menuExpandirDiretorios2->set_label(Rotinas::retUTF8("Expandir Diretórios"));
	menuExpandirDiretorios2->set_use_underline(true);
	menuExpandirDiretorios2->show();

	menuColapsarDiretorios2 = manage(new class Gtk::MenuItem());
	menuColapsarDiretorios2->set_name("menuColapsarDiretorios2");
	menuColapsarDiretorios2->set_visible(true);
	menuColapsarDiretorios2->set_can_focus(false);
	menuColapsarDiretorios2->set_label(Rotinas::retUTF8("Colapsar Diretórios"));
	menuColapsarDiretorios2->set_use_underline(true);
	menuColapsarDiretorios2->show();

	menuseparador2 = manage(new class Gtk::SeparatorMenuItem());
	menuseparador2->set_name("menuseparador2");
	menuseparador2->set_visible(true);
	menuseparador2->set_can_focus(false);
	menuseparador2->show();

	menuIncluirNovaAba2 = manage(new class Gtk::MenuItem());
	menuIncluirNovaAba2->set_name("menuIncluirNovaAba2");
	menuIncluirNovaAba2->set_visible(true);
	menuIncluirNovaAba2->set_can_focus(false);
	menuIncluirNovaAba2->set_label("Incluir Nova Aba");
	menuIncluirNovaAba2->set_use_underline(true);
	menuIncluirNovaAba2->show();

	menuAlterarNomeAbaAtiva2 = manage(new class Gtk::MenuItem());
	menuAlterarNomeAbaAtiva2->set_name("menuAlterarNomeAbaAtiva2");
	menuAlterarNomeAbaAtiva2->set_visible(true);
	menuAlterarNomeAbaAtiva2->set_can_focus(false);
	menuAlterarNomeAbaAtiva2->set_label("Alterar Nome da Aba Ativa");
	menuAlterarNomeAbaAtiva2->set_use_underline(true);
	menuAlterarNomeAbaAtiva2->show();

	menuExcluirAbaAtiva2 = manage(new class Gtk::MenuItem());
	menuExcluirAbaAtiva2->set_name("menuExcluirAbaAtiva2");
	menuExcluirAbaAtiva2->set_visible(true);
	menuExcluirAbaAtiva2->set_can_focus(false);
	menuExcluirAbaAtiva2->set_label("Excluir Aba Ativa");
	menuExcluirAbaAtiva2->set_use_underline(true);
	menuExcluirAbaAtiva2->show();


	popupMenu = manage(new class Gtk::Menu());
	popupMenu->append(*menuInformacoesDiretorioArquivo);
	popupMenu->append(*menuExcluirDiretorioSelecionado);
	popupMenu->append(*menuExpandirDiretorios2);
	popupMenu->append(*menuColapsarDiretorios2);
	popupMenu->append(*menuseparador2);
	popupMenu->append(*menuIncluirNovaAba2);
	popupMenu->append(*menuAlterarNomeAbaAtiva2);
	popupMenu->append(*menuExcluirAbaAtiva2);

	menuInformacoesDiretorioArquivo->signal_activate().connect(sigc::mem_fun(*this, &FrmPrincipal::on_menuInformacoesDiretorioArquivo_activate));
	menuExcluirDiretorioSelecionado->signal_activate().connect(sigc::mem_fun(*this, &FrmPrincipal::on_menuExcluirDiretorioSelecionado_activate));
	menuExpandirDiretorios2->signal_activate().connect(sigc::mem_fun(*this, &FrmPrincipal::on_menuExpandirDiretorios2_activate));
	menuColapsarDiretorios2->signal_activate().connect(sigc::mem_fun(*this, &FrmPrincipal::on_menuColapsarDiretorios2_activate));
	menuIncluirNovaAba2->signal_activate().connect(sigc::mem_fun(*this, &FrmPrincipal::on_menuIncluirNovaAba2_activate));
	menuAlterarNomeAbaAtiva2->signal_activate().connect(sigc::mem_fun(*this, &FrmPrincipal::on_menuAlterarNomeAbaAtiva2_activate));
	menuExcluirAbaAtiva2->signal_activate().connect(sigc::mem_fun(*this, &FrmPrincipal::on_menuExcluirAbaAtiva2_activate));

}

// ---------------------------------------------------------------------------
void FrmPrincipal::on_menuIncluirNovaAba_activate(){
	catalogador->IncluirNovaAba();
}

void FrmPrincipal::on_menuAlterarNomeAbaAtiva_activate(){
	catalogador->AlterarNomeAbaAtiva(FrmPrincipal::ProgressoLog);
}

void FrmPrincipal::on_menuExcluirAbaAtiva_activate(){
	catalogador->ExcluirAbaAtiva(FrmPrincipal::ProgressoLog);
}

void FrmPrincipal::on_menuImportarDiretorio_activate(){
	catalogador->ComecaImportacao(false, FrmPrincipal::ProgressoLog);
}

void FrmPrincipal::on_menuImportarSubDiretorios_activate(){
	catalogador->ComecaImportacao(true, FrmPrincipal::ProgressoLog);
}

void FrmPrincipal::on_menuCompararDiretorios_activate(){
    FrmCompararDiretorio::mostrar();
}

void FrmPrincipal::on_menuCadastrarExtensaoArquivo_activate(){
   FrmCadExtensao::mostrar();
}

void FrmPrincipal::on_menuExpandirDiretorios_activate(){
	catalogador->getArvoreAtual()->expandirTodos();
}

void FrmPrincipal::on_menuColapsarDiretorios_activate(){
	catalogador->getArvoreAtual()->colapsarTodos();
}

void FrmPrincipal::on_menuExportarDiretoriosAbaAtiva_activate(){

}

void FrmPrincipal::on_menuTXT_activate(){
	catalogador->ExportarArquivo(teTXT, FrmPrincipal::ProgressoLog);
}

void FrmPrincipal::on_menuCSV_activate(){
	catalogador->ExportarArquivo(teCSV, FrmPrincipal::ProgressoLog);
}

void FrmPrincipal::on_menuHTML_activate(){
	catalogador->ExportarArquivo(teHTML, FrmPrincipal::ProgressoLog);
}

void FrmPrincipal::on_menuXML_activate(){
	catalogador->ExportarArquivo(teXML, FrmPrincipal::ProgressoLog);
}

void FrmPrincipal::on_menuSQL_activate(){
	catalogador->ExportarArquivo(teSQL, FrmPrincipal::ProgressoLog);
}

void FrmPrincipal::on_menuImportarDiretoriosViaXML_activate(){
	std::vector<Glib::ustring> log;
	catalogador->ImportarArquivo(log, FrmPrincipal::ProgressoLog);
}

void FrmPrincipal::on_menuMostrarOcultarArvoreDirAbaAtiva_activate(){
	catalogador->mostrarOcultarArvore();
}

void FrmPrincipal::on_menuMostrarOcultarListaItensPesquisados_activate(){
	catalogador->mostrarOcultarListaItensPesquisados();
}

void FrmPrincipal::on_menuSobreCatalogador_activate(){
    FrmSobre::mostrar();
}

void FrmPrincipal::on_btnImportarDiretorio_clicked(){
	on_menuImportarDiretorio_activate();
}

void FrmPrincipal::on_btnPesquisa_clicked(){
	catalogador->Pesquisar();
}

void FrmPrincipal::on_notebook1_switch_page(Gtk::Widget* page, guint page_number) {
	if (frmPrincipal != NULL) {
		catalogador->tabPanelMudou();
	}
}

void FrmPrincipal::on_arvoreFixa_selection_changed() {
	Tabela* tabela = catalogador->getTabelaAtual();
	Arvore* arvore = catalogador->getArvoreAtual();
	Gtk::TreeIter iter;

	iter = arvore->get_selection()->get_selected();
	if (iter) {
		catalogador->ListarArquivos(tabela, arvore, iter);
	}

}

void FrmPrincipal::on_arvoreFixa_row_collapsed(const Gtk::TreeModel::iterator& iter, const Gtk::TreeModel::Path& path){
	Arvore* arvore = catalogador->getArvoreAtual();
	Gtk::TreeRow linha;

	linha = *iter;
	linha[arvore->modeloArvore.coluna0] = ExtensaoBO::getInstancia()->DiretorioXPM;
}

//typedef sigc::slot<void, int&, int&, bool&> Gtk::Menu::SlotPositionCalc
//void on_popup_menu_position(int& x, int& y, bool& push_in) {}
bool FrmPrincipal::on_arvoreFixa_button_release_event(GdkEventButton *event){
	if (event->button == 3) {
		popupMenu->popup(event->button, event->time);
	}
	return false;
}

bool FrmPrincipal::on_arvoreFixa_button_press_event(GdkEventButton *event) {
	Arvore* arvore;

	if (event->button == 1) {
		if (event->type == GDK_2BUTTON_PRESS) {
			arvore = catalogador->getArvoreAtual();
			arvore->expandirSelecionado();
		}
	}
	return false;
}

void FrmPrincipal::on_arvoreFixa_row_expanded(const Gtk::TreeModel::iterator& iter, const Gtk::TreeModel::Path& path){
	Arvore* arvore = catalogador->getArvoreAtual();
	Gtk::TreeRow linha;

	linha = *iter;
	linha[arvore->modeloArvore.coluna0] = ExtensaoBO::getInstancia()->DirAbertoXPM;
}

bool FrmPrincipal::on_tabelaFixa_button_release_event(GdkEventButton *event){
	if (event->button == 3) {
		popupMenu->popup(event->button, event->time);
	}
	return false;
}

void FrmPrincipal::on_tabelaFixa_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column){
	Tabela* tabela = catalogador->getTabelaAtual();
	Gtk::TreeIter iter;
	Gtk::TreeRow linha;
	Glib::ustring nome, tipo;

	iter = tabela->get_selection()->get_selected();
	if (iter) {
		if (tabela->get_selection()->is_selected(iter)) {
			linha = *iter;
			nome = linha[tabela->modeloTabela.coluna1];
			tipo = linha[tabela->modeloTabela.coluna3];

			catalogador->DuploCliqueLista(nome, tipo);
		}
	}
}

bool FrmPrincipal::on_tabelaPesquisa_button_release_event(GdkEventButton *event){
	Gtk::TreeIter iter;
	Gtk::TreeRow linha;
	Glib::ustring nome, caminho, nomeAba;

	if (event->button == 1) {
		iter = tabelaPesquisa->get_selection()->get_selected();
		if (iter) {
			if (tabelaPesquisa->get_selection()->is_selected(iter)) {
				linha = *iter;
				nome = linha[tabelaPesquisa->modeloTabela.coluna1];
				caminho = linha[tabelaPesquisa->modeloTabela.coluna6];
				nomeAba = linha[tabelaPesquisa->modeloTabela.coluna7];

				catalogador->EncontrarItemLista(nomeAba, nome, caminho);
			}
		}
	}
	return false;
}

bool FrmPrincipal::on_FrmPrincipal_delete_event(GdkEventAny *event){
	Rotinas::getInstancia()->BancoDesconectar();

	Gtk::Main::quit();
	return true;
}

void FrmPrincipal::on_menuInformacoesDiretorioArquivo_activate() {
	catalogador->InformacoesDiretorioArquivo();
}

void FrmPrincipal::on_menuExcluirDiretorioSelecionado_activate() {
	catalogador->ExcluirDiretorioSelecionado(FrmPrincipal::ProgressoLog);
}

void FrmPrincipal::on_menuExpandirDiretorios2_activate() {
	on_menuExpandirDiretorios_activate();
}

void FrmPrincipal::on_menuColapsarDiretorios2_activate() {
	on_menuColapsarDiretorios_activate();
}

void FrmPrincipal::on_menuIncluirNovaAba2_activate() {
	on_menuIncluirNovaAba_activate();
}

void FrmPrincipal::on_menuAlterarNomeAbaAtiva2_activate() {
	on_menuAlterarNomeAbaAtiva_activate();
}

void FrmPrincipal::on_menuExcluirAbaAtiva2_activate() {
	on_menuExcluirAbaAtiva_activate();
}
