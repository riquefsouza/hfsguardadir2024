#include "FrmCompararDiretorio.h"

#include <gdkmm/cursor.h>

#include "hfsguardadir/catalogador/Catalogador.h"
#include "hfsguardadir/objetosbo/AbaBO.h"
#include "hfsguardadir/objetosbo/DiretorioBO.h"
#include "hfsguardadir/objetosgui/Dialogo.h"

using namespace hfsguardadir::catalogador;
using namespace hfsguardadir::objetosgui;
using namespace hfsguardadir::objetosbo;

// ---------------------------------------------------------------------------
FrmCompararDiretorio *frmCompararDiretorio = (FrmCompararDiretorio*) NULL;
// ---------------------------------------------------------------------------
FrmCompararDiretorio::FrmCompararDiretorio()
	: Gtk::Window(Gtk::WINDOW_TOPLEVEL) {

	barraStatus21 = manage(new class Gtk::Statusbar());
	barraStatus21->set_name("barraStatus21");
	barraStatus21->set_visible(true);
	barraStatus21->set_can_focus(false);
	barraStatus21->set_spacing(2);

	barraStatus11 = manage(new class Gtk::Statusbar());
	barraStatus11->set_name("barraStatus11");
	barraStatus11->set_size_request(200, -1);
	barraStatus11->set_visible(true);
	barraStatus11->set_can_focus(false);
	barraStatus11->set_spacing(2);

	hbox5 = manage(new class Gtk::HBox(false, 0));
	hbox5->set_name("hbox5");
	hbox5->set_visible(true);
	hbox5->set_can_focus(false);
	hbox5->pack_start(*barraStatus11, false, true, 0);
	hbox5->pack_start(*barraStatus21, true, true, 0);

	tabelaCompara = manage(new class Tabela(true));
	tabelaCompara->set_name("tabelaCompara");
	tabelaCompara->set_visible(true);
	tabelaCompara->set_can_focus(true);

	scrollTabela12 = manage(new class Gtk::ScrolledWindow());
	scrollTabela12->set_name("scrollTabela12");
	scrollTabela12->set_visible(true);
	scrollTabela12->set_can_focus(true);
	scrollTabela12->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	scrollTabela12->add(*tabelaCompara);

	labDiferencasEncontradas = manage(new class Gtk::Label());
	labDiferencasEncontradas->set_name("labDiferencasEncontradas");
	labDiferencasEncontradas->set_visible(true);
	labDiferencasEncontradas->set_can_focus(false);
	labDiferencasEncontradas->set_label(Rotinas::retUTF8("Diferenças Encontradas"));

	hbox4 = manage(new class Gtk::HBox(false, 0));
	hbox4->set_name("hbox4");
	hbox4->set_visible(true);
	hbox4->set_can_focus(false);
	hbox4->pack_start(*labDiferencasEncontradas, false, true, 0);

	label6 = manage(new class Gtk::Label());
	label6->set_name("label6");
	label6->set_visible(true);
	label6->set_can_focus(false);
	label6->set_label(Rotinas::retUTF8("<b>Diretório 2</b>"));
	label6->set_use_markup(true);

	tvDiretorio2 = manage(new class Arvore());
	tvDiretorio2->set_name("tvDiretorio2");
	tvDiretorio2->set_visible(true);
	tvDiretorio2->set_can_focus(true);

	scrolledwindow4 = manage(new class Gtk::ScrolledWindow());
	scrolledwindow4->set_name("scrolledwindow4");
	scrolledwindow4->set_visible(true);
	scrolledwindow4->set_can_focus(true);
	scrolledwindow4->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	scrolledwindow4->add(*tvDiretorio2);

	cmbAba2 = manage(new class Gtk::ComboBoxText());
	cmbAba2->set_name("cmbAba2");
	cmbAba2->set_visible(true);
	cmbAba2->set_can_focus(false);

	vbox7 = manage(new class Gtk::VBox(false, 0));
	vbox7->set_name("vbox7");
	vbox7->set_visible(true);
	vbox7->set_can_focus(false);
	vbox7->pack_start(*cmbAba2, false, true, 0);
	vbox7->pack_start(*scrolledwindow4, true, true, 0);

	alignment2 = manage(new class Gtk::Alignment());
	alignment2->set_name("alignment2");
	alignment2->set_visible(true);
	alignment2->set_can_focus(false);
	alignment2->set_padding(0, 0, 12, 0);
	alignment2->add(*vbox7);

	frame3 = manage(new class Gtk::Frame());
	frame3->set_name("frame3");
	frame3->set_visible(true);
	frame3->set_can_focus(false);
	frame3->set_label_align(0, 0);
	frame3->set_shadow_type(Gtk::SHADOW_NONE);
	frame3->add(*alignment2);
	frame3->add(*label6);

	labDiretorio1 = manage(new class Gtk::Label());
	labDiretorio1->set_name("labDiretorio1");
	labDiretorio1->set_visible(true);
	labDiretorio1->set_can_focus(false);
	labDiretorio1->set_label(Rotinas::retUTF8("<b>Diretório 1</b>"));
	labDiretorio1->set_use_markup(true);

	tvDiretorio1 = manage(new class Arvore());
	tvDiretorio1->set_name("tvDiretorio1");
	tvDiretorio1->set_visible(true);
	tvDiretorio1->set_can_focus(true);

	scrolledwindow3 = manage(new class Gtk::ScrolledWindow());
	scrolledwindow3->set_name("scrolledwindow3");
	scrolledwindow3->set_visible(true);
	scrolledwindow3->set_can_focus(true);
	scrolledwindow3->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	scrolledwindow3->add(*tvDiretorio1);

	cmbAba1 = manage(new class Gtk::ComboBoxText());
	cmbAba1->set_name("cmbAba1");
	cmbAba1->set_visible(true);
	cmbAba1->set_can_focus(false);

	vbox6 = manage(new class Gtk::VBox(false, 0));
	vbox6->set_name("vbox6");
	vbox6->set_visible(true);
	vbox6->set_can_focus(false);
	vbox6->pack_start(*cmbAba1, false, true, 0);
	vbox6->pack_start(*scrolledwindow3, true, true, 0);

	alignment1 = manage(new class Gtk::Alignment());
	alignment1->set_name("alignment1");
	alignment1->set_visible(true);
	alignment1->set_can_focus(false);
	alignment1->set_padding(0, 0, 12, 0);
	alignment1->add(*vbox6);

	frame2 = manage(new class Gtk::Frame());
	frame2->set_name("frame2");
	frame2->set_visible(true);
	frame2->set_can_focus(false);
	frame2->set_label_align(0, 0);
	frame2->set_shadow_type(Gtk::SHADOW_NONE);
	frame2->add(*alignment1);
	frame2->add(*labDiretorio1);

	hbox2 = manage(new class Gtk::HBox(false, 0));
	hbox2->set_name("hbox2");
	hbox2->set_visible(true);
	hbox2->set_can_focus(false);
	hbox2->pack_start(*frame2, true, true, 0);
	hbox2->pack_start(*frame3, true, true, 0);

	btnSalvarLog = manage(new class Gtk::Button());
	btnSalvarLog->set_name("btnSalvarLog");
	btnSalvarLog->set_label("Salvar Log");
	btnSalvarLog->set_visible(true);
	btnSalvarLog->set_can_focus(true);
	btnSalvarLog->set_receives_default(true);

	pb2 = manage(new class Gtk::ProgressBar());
	pb2->set_name("pb2");
	pb2->set_visible(true);
	pb2->set_can_focus(false);

	btnCompararDiretorios = manage(new class Gtk::Button());
	btnCompararDiretorios->set_name("btnCompararDiretorios");
	btnCompararDiretorios->set_label(Rotinas::retUTF8("Comparar Diretórios"));
	btnCompararDiretorios->set_visible(true);
	btnCompararDiretorios->set_can_focus(true);
	btnCompararDiretorios->set_receives_default(true);

	hbox1 = manage(new class Gtk::HBox(false, 0));
	hbox1->set_name("hbox1");
	hbox1->set_visible(true);
	hbox1->set_can_focus(false);
	hbox1->pack_start(*btnCompararDiretorios, false, true, 0);
	hbox1->pack_start(*pb2, true, true, 0);
	hbox1->pack_start(*btnSalvarLog, false, true, 0);

	vbox5 = manage(new class Gtk::VBox(false, 0));
	vbox5->set_name("vbox5");
	vbox5->set_visible(true);
	vbox5->set_can_focus(false);
	vbox5->pack_start(*hbox1, false, false, 0);
	vbox5->pack_start(*hbox2, true, true, 0);
	vbox5->pack_start(*hbox4, false, true, 0);
	vbox5->pack_start(*scrollTabela12, true, true, 0);
	vbox5->pack_start(*hbox5, false, true, 0);

	this->set_name("frmCompararDiretorio");
	this->set_size_request(700, 600);
	this->set_visible(true);
	this->set_can_focus(false);
	this->set_title(Rotinas::retUTF8("Comparar Diretórios"));
	this->set_resizable(false);
	this->set_modal(true);
	this->set_position(Gtk::WIN_POS_CENTER);
	this->set_default_size(700, 600);
	this->add(*vbox5);


	btnCompararDiretorios->signal_clicked().connect(sigc::mem_fun(*this, &FrmCompararDiretorio::on_btnCompararDiretorios_clicked));
	btnSalvarLog->signal_clicked().connect(sigc::mem_fun(*this, &FrmCompararDiretorio::btnSalvarLog_clicked_cb));
	cmbAba1->signal_changed().connect(sigc::mem_fun(*this, &FrmCompararDiretorio::on_cmbAba1_changed));
	tvDiretorio1->signal_row_collapsed().connect(sigc::mem_fun(*this, &FrmCompararDiretorio::on_tvDiretorio1_row_collapsed));
	tvDiretorio1->signal_row_expanded().connect(sigc::mem_fun(*this, &FrmCompararDiretorio::on_tvDiretorio1_row_expanded));
	tvDiretorio1->signal_button_press_event().connect(sigc::mem_fun(*this, &FrmCompararDiretorio::on_tvDiretorio1_button_press_event));
	cmbAba2->signal_changed().connect(sigc::mem_fun(*this, &FrmCompararDiretorio::on_cmbAba2_changed));
	tvDiretorio2->signal_row_collapsed().connect(sigc::mem_fun(*this, &FrmCompararDiretorio::on_tvDiretorio2_row_collapsed));
	tvDiretorio2->signal_row_expanded().connect(sigc::mem_fun(*this, &FrmCompararDiretorio::on_tvDiretorio2_row_expanded));
	tvDiretorio2->signal_button_press_event().connect(sigc::mem_fun(*this, &FrmCompararDiretorio::on_tvDiretorio2_button_press_event));
	tabelaCompara->signal_row_activated().connect(sigc::mem_fun(*this, &FrmCompararDiretorio::on_tabelaCompara_row_activated));
	tabelaCompara->signal_button_release_event().connect(sigc::mem_fun(*this, &FrmCompararDiretorio::on_tabelaCompara_button_release_event));

	getLabStatus1()->set_text(Rotinas::retUTF8("Total de diferenças encontradas:"));

	CarregarDados();
	LimparComparacao();
}
// ---------------------------------------------------------------------------
FrmCompararDiretorio::~FrmCompararDiretorio(){

}
// ---------------------------------------------------------------------------
void FrmCompararDiretorio::mostrar()
{
    frmCompararDiretorio = new FrmCompararDiretorio();
	frmCompararDiretorio->set_position(Gtk::WIN_POS_CENTER_ALWAYS);
	frmCompararDiretorio->show_all();
}

void FrmCompararDiretorio::ProgressoLog(Progresso progresso)
{
	if (frmCompararDiretorio != NULL) {
		if (progresso.posicao == 0) {
			frmCompararDiretorio->pb2->set_fraction(progresso.minimo);
			frmCompararDiretorio->pb2->set_pulse_step(0.1); //progresso.passo
		}
		frmCompararDiretorio->pb2->set_fraction(
			Rotinas::calculaProgresso(progresso.maximo, progresso.posicao));
	}
}

Gtk::Label* FrmCompararDiretorio::getLabStatus1() {
	Glib::ListHandle<Gtk::Widget*> hlista = barraStatus11->get_children();
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

Gtk::Label* FrmCompararDiretorio::getLabStatus2() {
	Glib::ListHandle<Gtk::Widget*> hlista = barraStatus21->get_children();
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

// ---------------------------------------------------------------------------
void FrmCompararDiretorio::on_btnCompararDiretorios_clicked(){
	Glib::ustring sCaminhoDir1, sCaminhoDir2;
	bool bSelecionado;
	Gtk::TreeIter iter1, iter2;

	bSelecionado = false;
	iter1 = tvDiretorio1->get_selection()->get_selected();

	if (iter1) {
		if (tvDiretorio1->get_selection()->is_selected(iter1)) {
			catalogador->LerArvoreDiretorio(tvDiretorio1, iter1, getLabStatus2());
			sCaminhoDir1 = getLabStatus2()->get_text();

			iter2 = tvDiretorio2->get_selection()->get_selected();
			if (iter2) {
				if (tvDiretorio2->get_selection()->is_selected(iter2)) {
					catalogador->LerArvoreDiretorio(tvDiretorio2, iter2, getLabStatus2());
					sCaminhoDir2 = getLabStatus2()->get_text();
					bSelecionado = true;
				}
			}
		}
	}

	LimparComparacao();

	if (bSelecionado) {
		Comparar(sCaminhoDir1, sCaminhoDir2);
	}
	else {
		Dialogo::mensagemInfo(frmCompararDiretorio,
			"DiretoriosNaoSelecionados");
	}
}

void FrmCompararDiretorio::btnSalvarLog_clicked_cb(){
	Glib::ustring sLog;
	Diretorio diretorio;
	std::vector<Glib::ustring> listaLocal;
	guint tamlista = listaCompara.size();

	if (tamlista > 0) {

		sLog = Rotinas::AppDirPath() +
			Rotinas::formataDate(Rotinas::FORMATO_DHARQUIVO, Rotinas::DataHoraNow()) +
			"_Comparacao.log";

		for (unsigned int i = 0; i < tamlista; i++) {
			diretorio = listaCompara.at(i);

			listaLocal.push_back(diretorio.getCaminho());
		}

		Rotinas::SListSaveToFile(listaLocal, sLog);

		Dialogo::mensagemInfo(frmCompararDiretorio,
			"LogSalvoMemoDirSistema");
	}
}

void FrmCompararDiretorio::on_cmbAba1_changed(){
	Aba aba;

	get_window()->set_cursor(Gdk::Cursor::create(Gdk::WATCH));

	tvDiretorio1->limpar();

	gint indice = cmbAba1->get_active_row_number();

	aba = *AbaBO::getInstancia()->pegaAbaPorOrdem(catalogador->listaAbas, indice + 1);
	catalogador->CarregarArvore(tvDiretorio1, aba);

	tvDiretorio1->grab_focus();
	LimparComparacao();

	get_window()->set_cursor(Gdk::Cursor::create(Gdk::ARROW));
}

void FrmCompararDiretorio::on_tvDiretorio1_row_collapsed(const Gtk::TreeModel::iterator& iter, const Gtk::TreeModel::Path& path){

}

void FrmCompararDiretorio::on_tvDiretorio1_row_expanded(const Gtk::TreeModel::iterator& iter, const Gtk::TreeModel::Path& path){

}

bool FrmCompararDiretorio::on_tvDiretorio1_button_press_event(GdkEventButton *event){
	if (event->button == 1) {
		if (event->type == GDK_2BUTTON_PRESS) {
			tvDiretorio1->expandirSelecionado();
		}
	}
	return false;
}

void FrmCompararDiretorio::on_cmbAba2_changed(){
	Aba aba;

	get_window()->set_cursor(Gdk::Cursor::create(Gdk::WATCH));

	tvDiretorio2->limpar();

	gint indice = cmbAba2->get_active_row_number();

	aba = *AbaBO::getInstancia()->pegaAbaPorOrdem(catalogador->listaAbas, indice + 1);
	catalogador->CarregarArvore(tvDiretorio2, aba);

	tvDiretorio2->grab_focus();
	LimparComparacao();

	get_window()->set_cursor(Gdk::Cursor::create(Gdk::ARROW));
}

void FrmCompararDiretorio::on_tvDiretorio2_row_collapsed(const Gtk::TreeModel::iterator& iter, const Gtk::TreeModel::Path& path){

}

void FrmCompararDiretorio::on_tvDiretorio2_row_expanded(const Gtk::TreeModel::iterator& iter, const Gtk::TreeModel::Path& path){

}

bool FrmCompararDiretorio::on_tvDiretorio2_button_press_event(GdkEventButton *event){
	if (event->button == 1) {
		if (event->type == GDK_2BUTTON_PRESS) {
			tvDiretorio2->expandirSelecionado();
		}
	}
	return false;
}

void FrmCompararDiretorio::on_tabelaCompara_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column){

}

bool FrmCompararDiretorio::on_tabelaCompara_button_release_event(GdkEventButton *event){
		return false;
}

void FrmCompararDiretorio::CarregarDados() {
	Gtk::TreeIter iter;
	Aba aba;

	for (unsigned int i = 0; i < catalogador->listaAbas.size(); i++) {
		aba = catalogador->listaAbas.at(i);

		cmbAba1->append(aba.getNome());
		cmbAba2->append(aba.getNome());
	}

	iter = cmbAba1->get_model()->children().begin();
	if (iter) {
		cmbAba1->set_active(iter);
	}

	iter = cmbAba2->get_model()->children().begin();
	if (iter) {
		cmbAba2->set_active(iter);
	}
}

void FrmCompararDiretorio::LimparComparacao() {
	pb2->set_fraction(0);
	tabelaCompara->limpar();
	btnSalvarLog->set_sensitive(false);
	getLabStatus2()->set_text("");
}

Glib::ustring FrmCompararDiretorio::SQLCompara(Aba aba1, Aba aba2, const Glib::ustring caminho1,
	const Glib::ustring caminho2) {
	//Glib::ustring scaminho1 = g_string_new(caminho1->str);
	//Glib::ustring scaminho2 = g_string_new(caminho2->str);
	char* sSQL = (char*)DiretorioBO::SQL_CONSULTA_ARQUIVO.c_str();

	std::snprintf(sSQL, TAM_MAX_STR, " WHERE aba=%d AND caminho LIKE %s AND nome NOT IN " \
		"(SELECT nome FROM Diretorios WHERE aba=%d AND caminho LIKE %s) ORDER BY 1, 2, 3",
		aba1.getCodigo(), Rotinas::QuotedStr(caminho1 + "%").c_str(),
		aba2.getCodigo(), Rotinas::QuotedStr(caminho2 + "%").c_str());
	return sSQL;
}

void FrmCompararDiretorio::Comparar(const Glib::ustring sCaminhoDir1, const Glib::ustring sCaminhoDir2) {
	Glib::ustring sSQL;
	Aba aba1, aba2;
	guint tamlista;

	//gint indice = cmbAba1->get_active();
	gint indice = cmbAba1->get_active_row_number();
	aba1 = *AbaBO::getInstancia()->pegaAbaPorOrdem(catalogador->listaAbas, indice + 1);

	//indice = cmbAba2->get_active();
	indice = cmbAba2->get_active_row_number();
	aba2 = *AbaBO::getInstancia()->pegaAbaPorOrdem(catalogador->listaAbas, indice + 1);

	sSQL = SQLCompara(aba1, aba2, sCaminhoDir1, sCaminhoDir2);
	listaCompara = DiretorioBO::getInstancia()->carregarDiretorio(sSQL,
		"consultaarquivo", ProgressoLog);
	tamlista = listaCompara.size();

	if (tamlista > 0) {
		tabelaCompara->carregar(listaCompara, catalogador->listaExtensoes, pb2);

		getLabStatus2()->set_text(Rotinas::IntToStr(tamlista));
		btnSalvarLog->set_sensitive(true);
	}
	else {
		Dialogo::mensagemInfo(frmCompararDiretorio,
			"NenhumaDiferencaEncontrada");
	}
}

