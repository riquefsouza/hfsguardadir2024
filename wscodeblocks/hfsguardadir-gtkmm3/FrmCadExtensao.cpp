#include "FrmCadExtensao.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/catalogador/Catalogador.h"
#include "hfsguardadir/objetos/Extensao.h"
#include "hfsguardadir/objetosbo/ExtensaoBO.h"
#include "hfsguardadir/objetosgui/EscolhaArquivo.h"
#include "hfsguardadir/objetosgui/Dialogo.h"

using namespace hfsguardadir::comum;
using namespace hfsguardadir::catalogador;
using namespace hfsguardadir::objetos;
using namespace hfsguardadir::objetosbo;
using namespace hfsguardadir::objetosgui;

// ---------------------------------------------------------------------------
FrmCadExtensao *frmCadExtensao = (FrmCadExtensao*) NULL;
// ---------------------------------------------------------------------------
FrmCadExtensao::FrmCadExtensao()
	: Gtk::Dialog() {

	btnExcluir = manage(new class Gtk::Button());
	btnExcluir->set_name("btnExcluir");
	btnExcluir->set_label("gtk-remove");
	btnExcluir->set_visible(true);
	btnExcluir->set_can_focus(true);
	btnExcluir->set_receives_default(true);
	btnExcluir->set_use_stock(true);
    btnExcluir->set_margin_top(10);
	btnExcluir->set_margin_bottom(10);
	btnExcluir->set_margin_left(2);

	btnIncluir = manage(new class Gtk::Button());
	btnIncluir->set_name("btnIncluir");
	btnIncluir->set_label("gtk-add");
	btnIncluir->set_visible(true);
	btnIncluir->set_can_focus(true);
	btnIncluir->set_receives_default(true);
	btnIncluir->set_use_stock(true);
    btnIncluir->set_margin_top(10);
	btnIncluir->set_margin_bottom(10);
	btnIncluir->set_margin_right(2);

	form_area = manage(new class Gtk::HButtonBox());
	form_area->set_name("form_area");
	form_area->set_visible(true);
	form_area->set_can_focus(false);
	form_area->set_layout(Gtk::BUTTONBOX_CENTER);
	form_area->add(*btnIncluir);
	form_area->pack_start(*btnIncluir, false, false, 0);
	form_area->add(*btnExcluir);
	form_area->pack_start(*btnExcluir, false, false, 0);

	colunaCadExtIcone = manage(new class Gtk::TreeViewColumn(Rotinas::retUTF8("Ícone"), modeloTabelaExtensao.coluna1));
	colunaCadExtIcone->set_min_width(100);
	colunaCadExtIcone->set_title(Rotinas::retUTF8("Ícone"));

	colunaCadExtExtensao = manage(new class Gtk::TreeViewColumn(Rotinas::retUTF8("Extensão"), modeloTabelaExtensao.coluna0));
	colunaCadExtExtensao->set_min_width(150);
	colunaCadExtExtensao->set_title(Rotinas::retUTF8("Extensão"));

	tabelaExtensao = manage(new class Gtk::TreeView());
	tabelaExtensao->set_name("tabelaExtensao");
	tabelaExtensao->set_visible(true);
	tabelaExtensao->set_can_focus(true);

	tabelaExtensao->append_column(*colunaCadExtExtensao);
	tabelaExtensao->append_column(*colunaCadExtIcone);

	tabelaExtensao->get_selection()->set_mode(Gtk::SELECTION_SINGLE);
	tabelaExtensao->set_model(Gtk::ListStore::create(modeloTabelaExtensao));
	tabelaExtensao->columns_autosize();

	scrollTabela = manage(new class Gtk::ScrolledWindow());
	scrollTabela->set_name("scrollTabela");
	scrollTabela->set_visible(true);
	scrollTabela->set_can_focus(true);
	scrollTabela->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	scrollTabela->set_vexpand(true);
	scrollTabela->add(*tabelaExtensao);

	menuExtrairIconesArquivos = manage(new class Gtk::MenuItem());
	menuExtrairIconesArquivos->set_name("menuExtrairIconesArquivos");
	menuExtrairIconesArquivos->set_visible(true);
	menuExtrairIconesArquivos->set_can_focus(false);
	menuExtrairIconesArquivos->set_label(Rotinas::retUTF8("Extrair Ícones dos Arquivos"));
	menuExtrairIconesArquivos->set_use_underline(true);

	menuImportarIconesArquivos = manage(new class Gtk::MenuItem());
	menuImportarIconesArquivos->set_name("menuImportarIconesArquivos");
	menuImportarIconesArquivos->set_visible(true);
	menuImportarIconesArquivos->set_can_focus(false);
	menuImportarIconesArquivos->set_label(Rotinas::retUTF8("Importar Ícones dos Arquivos"));
	menuImportarIconesArquivos->set_use_underline(true);

	submenuImportarTodos = manage(new class Gtk::Menu());
	submenuImportarTodos->set_name("submenuImportarTodos");
	submenuImportarTodos->set_visible(true);
	submenuImportarTodos->set_can_focus(false);
	submenuImportarTodos->append(*menuImportarIconesArquivos);
	submenuImportarTodos->append(*menuExtrairIconesArquivos);

	menuImportarTodos = manage(new class Gtk::MenuItem());
	menuImportarTodos->set_name("menuImportarTodos");
	menuImportarTodos->set_visible(true);
	menuImportarTodos->set_can_focus(false);
	menuImportarTodos->set_label("Importar Todos");
	menuImportarTodos->set_use_underline(true);
	menuImportarTodos->set_submenu(*submenuImportarTodos);

	menuExportarTIFF = manage(new class Gtk::MenuItem());
	menuExportarTIFF->set_name("menuExportarTIFF");
	menuExportarTIFF->set_visible(true);
	menuExportarTIFF->set_can_focus(false);
	menuExportarTIFF->set_label("Exportar para TIFF");
	menuExportarTIFF->set_use_underline(true);

	menuExportarPNG = manage(new class Gtk::MenuItem());
	menuExportarPNG->set_name("menuExportarPNG");
	menuExportarPNG->set_visible(true);
	menuExportarPNG->set_can_focus(false);
	menuExportarPNG->set_label("Exportar para PNG");
	menuExportarPNG->set_use_underline(true);

	menuExportarJPEG = manage(new class Gtk::MenuItem());
	menuExportarJPEG->set_name("menuExportarJPEG");
	menuExportarJPEG->set_visible(true);
	menuExportarJPEG->set_can_focus(false);
	menuExportarJPEG->set_label("Exportar para JPEG");
	menuExportarJPEG->set_use_underline(true);

	menuExportarGIF = manage(new class Gtk::MenuItem());
	menuExportarGIF->set_name("menuExportarGIF");
	menuExportarGIF->set_visible(true);
	menuExportarGIF->set_can_focus(false);
	menuExportarGIF->set_label("Exportar para GIF");
	menuExportarGIF->set_use_underline(true);

	menuExportarIcone = manage(new class Gtk::MenuItem());
	menuExportarIcone->set_name("menuExportarIcone");
	menuExportarIcone->set_visible(true);
	menuExportarIcone->set_can_focus(false);
	menuExportarIcone->set_label(Rotinas::retUTF8("Exportar para Ícone"));
	menuExportarIcone->set_use_underline(true);

	menuExportarBitmap = manage(new class Gtk::MenuItem());
	menuExportarBitmap->set_name("menuExportarBitmap");
	menuExportarBitmap->set_visible(true);
	menuExportarBitmap->set_can_focus(false);
	menuExportarBitmap->set_label("Exportar para Bitmap");
	menuExportarBitmap->set_use_underline(true);

	submenuExportarTodos = manage(new class Gtk::Menu());
	submenuExportarTodos->set_name("submenuExportarTodos");
	submenuExportarTodos->set_visible(true);
	submenuExportarTodos->set_can_focus(false);
	submenuExportarTodos->append(*menuExportarBitmap);
	submenuExportarTodos->append(*menuExportarIcone);
	submenuExportarTodos->append(*menuExportarGIF);
	submenuExportarTodos->append(*menuExportarJPEG);
	submenuExportarTodos->append(*menuExportarPNG);
	submenuExportarTodos->append(*menuExportarTIFF);

	menuExportarTodos = manage(new class Gtk::MenuItem());
	menuExportarTodos->set_name("menuExportarTodos");
	menuExportarTodos->set_visible(true);
	menuExportarTodos->set_can_focus(false);
	menuExportarTodos->set_label("Exportar Todos");
	menuExportarTodos->set_use_underline(true);
	menuExportarTodos->set_submenu(*submenuExportarTodos);

	menuExcluirTodasExtensoes = manage(new class Gtk::MenuItem());
	menuExcluirTodasExtensoes->set_name("menuExcluirTodasExtensoes");
	menuExcluirTodasExtensoes->set_visible(true);
	menuExcluirTodasExtensoes->set_can_focus(false);
	menuExcluirTodasExtensoes->set_label(Rotinas::retUTF8("Excluir Todas Extensões"));
	menuExcluirTodasExtensoes->set_use_underline(true);

	menuExcluirExtensao = manage(new class Gtk::MenuItem());
	menuExcluirExtensao->set_name("menuExcluirExtensao");
	menuExcluirExtensao->set_visible(true);
	menuExcluirExtensao->set_can_focus(false);
	menuExcluirExtensao->set_label(Rotinas::retUTF8("Excluir Extensão"));
	menuExcluirExtensao->set_use_underline(true);

	menuIncluirExtensao = manage(new class Gtk::MenuItem());
	menuIncluirExtensao->set_name("menuIncluirExtensao");
	menuIncluirExtensao->set_visible(true);
	menuIncluirExtensao->set_can_focus(false);
	menuIncluirExtensao->set_label(Rotinas::retUTF8("Incluir Extensão"));
	menuIncluirExtensao->set_use_underline(true);

	submenuExtensao = manage(new class Gtk::Menu());
	submenuExtensao->set_name("submenuExtensao");
	submenuExtensao->set_visible(true);
	submenuExtensao->set_can_focus(false);
	submenuExtensao->append(*menuIncluirExtensao);
	submenuExtensao->append(*menuExcluirExtensao);
	submenuExtensao->append(*menuExcluirTodasExtensoes);

	menuExtensao = manage(new class Gtk::MenuItem());
	menuExtensao->set_name("menuExtensao");
	menuExtensao->set_visible(true);
	menuExtensao->set_can_focus(false);
	menuExtensao->set_label(Rotinas::retUTF8("Extensão"));
	menuExtensao->set_use_underline(true);
	menuExtensao->set_submenu(*submenuExtensao);

	barraMenu = manage(new class Gtk::MenuBar());
	barraMenu->set_name("barraMenu");
	barraMenu->set_visible(true);
	barraMenu->set_can_focus(false);
	barraMenu->append(*menuExtensao);
	barraMenu->append(*menuExportarTodos);
	barraMenu->append(*menuImportarTodos);

	vbox = manage(new class Gtk::VBox(false, 0));
	vbox->set_name("vbox");
	vbox->set_visible(true);
	vbox->set_can_focus(false);
	vbox->pack_start(*barraMenu, false, true, 0);
	vbox->pack_start(*scrollTabela, true, true, 0);

	form_vbox = manage(new class Gtk::VBox(false, 0));
	form_vbox->set_name("form_vbox");
	form_vbox->set_visible(true);
	form_vbox->set_can_focus(false);
	form_vbox->set_spacing(2);
	form_vbox->pack_start(*vbox, true, true, 0);
	form_vbox->pack_start(*form_area, false, true, 0);

	this->set_name("frmCadExtensao");
	this->set_size_request(286, 418);
	this->set_can_focus(false);
	this->set_border_width(5);
	this->set_title(Rotinas::retUTF8("Cadastro de Extensão de Arquivo"));
	this->set_resizable(false);
	this->set_modal(true);
	this->property_destroy_with_parent() = true;
	this->set_position(Gtk::WIN_POS_CENTER);
	this->set_type_hint(Gdk::WINDOW_TYPE_HINT_DIALOG);
	this->get_vbox()->add(*form_vbox);


	menuIncluirExtensao->signal_activate().connect(sigc::mem_fun(*this, &FrmCadExtensao::on_menuIncluirExtensao_activate));
	menuExcluirExtensao->signal_activate().connect(sigc::mem_fun(*this, &FrmCadExtensao::on_menuExcluirExtensao_activate));
	menuExcluirTodasExtensoes->signal_activate().connect(sigc::mem_fun(*this, &FrmCadExtensao::on_menuExcluirTodasExtensoes_activate));
	menuExportarBitmap->signal_activate().connect(sigc::mem_fun(*this, &FrmCadExtensao::on_menuExportarBitmap_activate));
	menuExportarIcone->signal_activate().connect(sigc::mem_fun(*this, &FrmCadExtensao::on_menuExportarIcone_activate));
	menuExportarGIF->signal_activate().connect(sigc::mem_fun(*this, &FrmCadExtensao::on_menuExportarGIF_activate));
	menuExportarJPEG->signal_activate().connect(sigc::mem_fun(*this, &FrmCadExtensao::on_menuExportarJPEG_activate));
	menuExportarPNG->signal_activate().connect(sigc::mem_fun(*this, &FrmCadExtensao::on_menuExportarPNG_activate));
	menuExportarTIFF->signal_activate().connect(sigc::mem_fun(*this, &FrmCadExtensao::on_menuExportarTIFF_activate));
	menuImportarIconesArquivos->signal_activate().connect(sigc::mem_fun(*this, &FrmCadExtensao::on_menuImportarIconesArquivos_activate));
	menuExtrairIconesArquivos->signal_activate().connect(sigc::mem_fun(*this, &FrmCadExtensao::on_menuExtrairIconesArquivos_activate));
	btnIncluir->signal_clicked().connect(sigc::mem_fun(*this, &FrmCadExtensao::on_btnIncluir_clicked));
	btnExcluir->signal_clicked().connect(sigc::mem_fun(*this, &FrmCadExtensao::on_btnExcluir_clicked));


	CarregarExtensoesNaGrid();
}
// ---------------------------------------------------------------------------
FrmCadExtensao::~FrmCadExtensao(){

}
// ---------------------------------------------------------------------------
void FrmCadExtensao::mostrar()
{
    frmCadExtensao = new FrmCadExtensao();
	frmCadExtensao->set_position(Gtk::WIN_POS_CENTER_ALWAYS);
	frmCadExtensao->run();
	frmCadExtensao->hide();
}

Glib::RefPtr<Gtk::ListStore> FrmCadExtensao::getStore() {
	Glib::RefPtr<Gtk::ListStore> store;
	store = Glib::RefPtr<Gtk::ListStore>::cast_static(tabelaExtensao->get_model());
	return store;
}

void FrmCadExtensao::CarregarExtensoesNaGrid() {
	Gtk::TreeRow tLinha;
	Extensao extensao;

	tabelaExtensao->get_model().clear();

	for (unsigned int i = 0; i < catalogador->listaExtensoes.size(); i++) {
		extensao = catalogador->listaExtensoes.at(i);

		tLinha = *(getStore()->append());
		tLinha[modeloTabelaExtensao.coluna0] = extensao.getNome();
		tLinha[modeloTabelaExtensao.coluna1] = extensao.getBmp16();
	}

}

// ---------------------------------------------------------------------------
void FrmCadExtensao::on_menuIncluirExtensao_activate(){
	std::vector<Glib::ustring> log;

	Glib::ustring arquivo = EscolhaArquivo::abrirArquivo(
		frmCadExtensao, EscolhaArquivo::FILTRO_IMAGEM);

	if (arquivo.length() > 0) {
		if (Rotinas::FileExists(arquivo)) {

			if (ExtensaoBO::getInstancia()->SalvarExtensao(
				catalogador->listaExtensoes, arquivo, arquivo, log)) {

				CarregarExtensoesNaGrid();

				Dialogo::mensagemInfo(frmCadExtensao,
					"ExtensaoSalvaSucesso");
			}
			else {
				Dialogo::mensagemInfo(frmCadExtensao,
					"ExtensaoJaCadastrada");
			}
		}
	}
}

void FrmCadExtensao::on_menuExcluirExtensao_activate(){
	Extensao extensao;
	std::vector<int> indices;

	if (catalogador->listaExtensoes.size() > 0) {
		bool res = Dialogo::confirma(frmCadExtensao,
			"ExtensaoCertezaExcluir");
		if (res) {
			Gtk::TreeIter iter = tabelaExtensao->get_selection()->get_selected();
			Gtk::TreePath path(iter);
			//Glib::ArrayHandle<int> aindices = path.get_indices();

			//GList* linhas = gtk_tree_selection_get_selected_rows(tabela_selecao, &tabela_modelo);
			//GtkTreePath* path = g_list_nth_data(linhas, 0);
			//gint* indices = gtk_tree_path_get_indices(path);
/*
			indices = aindices.operator std::vector<int, std::allocator<int>>();

			extensao = *ExtensaoBO::getInstancia()->pegaExtensaoPorOrdem(
				catalogador->listaExtensoes, indices.at(0) + 1);

			if (ExtensaoBO::getInstancia()->excluirExtensao(
				catalogador->listaExtensoes, extensao.getCodigo())) {
				CarregarExtensoesNaGrid();
				Dialogo::mensagemInfo(frmCadExtensao,
					"ExtensaoExcluidaSucesso");
			}
*/
		}
	}
}

void FrmCadExtensao::on_menuExcluirTodasExtensoes_activate(){
	bool res = Dialogo::confirma(frmCadExtensao,
		"ExtensaoCertezaTodosExcluir");
	if (res) {
		if (ExtensaoBO::getInstancia()->excluirTodasExtensoes(catalogador->listaExtensoes)) {
			CarregarExtensoesNaGrid();
			Dialogo::mensagemInfo(frmCadExtensao,
				"ExtensoesExcluidasSucesso");
		}
	}
}

void FrmCadExtensao::on_menuExportarBitmap_activate(){
	ExtensaoBO::getInstancia()->ExportarExtensao(teBMP, catalogador->listaExtensoes);
}

void FrmCadExtensao::on_menuExportarIcone_activate(){
	ExtensaoBO::getInstancia()->ExportarExtensao(teICO, catalogador->listaExtensoes);
}

void FrmCadExtensao::on_menuExportarGIF_activate(){
	ExtensaoBO::getInstancia()->ExportarExtensao(teGIF, catalogador->listaExtensoes);
}

void FrmCadExtensao::on_menuExportarJPEG_activate(){
	ExtensaoBO::getInstancia()->ExportarExtensao(teJPG, catalogador->listaExtensoes);
}

void FrmCadExtensao::on_menuExportarPNG_activate(){
	ExtensaoBO::getInstancia()->ExportarExtensao(tePNG, catalogador->listaExtensoes);
}

void FrmCadExtensao::on_menuExportarTIFF_activate(){
	ExtensaoBO::getInstancia()->ExportarExtensao(teTIF, catalogador->listaExtensoes);
}

void FrmCadExtensao::on_menuImportarIconesArquivos_activate(){
	Glib::ustring arquivo = EscolhaArquivo::abrirArquivo(frmCadExtensao,
		EscolhaArquivo::FILTRO_IMAGEM);

	if (arquivo.length() > 0) {
		if (Rotinas::FileExists(arquivo)) {
			ExtensaoBO::getInstancia()->ImportarExtensao(arquivo, catalogador->listaExtensoes);
			CarregarExtensoesNaGrid();
		}
	}
}

void FrmCadExtensao::on_menuExtrairIconesArquivos_activate(){
	Glib::ustring arquivo = EscolhaArquivo::abrirArquivo(frmCadExtensao,
		EscolhaArquivo::FILTRO_IMAGEM);

	if (arquivo.length() > 0) {
		if (Rotinas::FileExists(arquivo)) {
			ExtensaoBO::getInstancia()->ExtrairExtensao(arquivo, catalogador->listaExtensoes);
			CarregarExtensoesNaGrid();
		}
	}
}

void FrmCadExtensao::on_btnIncluir_clicked(){
	on_menuIncluirExtensao_activate();
}

void FrmCadExtensao::on_btnExcluir_clicked(){
	on_menuExcluirExtensao_activate();
}
