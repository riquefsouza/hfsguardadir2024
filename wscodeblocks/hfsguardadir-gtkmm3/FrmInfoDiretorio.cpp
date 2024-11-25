#include "FrmInfoDiretorio.h"
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::comum;
// ---------------------------------------------------------------------------
FrmInfoDiretorio *frmInfoDiretorio = (FrmInfoDiretorio*) NULL;
// ---------------------------------------------------------------------------
FrmInfoDiretorio::FrmInfoDiretorio()
	: Gtk::Dialog() {

	btnOk = manage(new class Gtk::Button());
	btnOk->set_name("btnOk");
	btnOk->set_label("gtk-ok");
	btnOk->set_visible(true);
	btnOk->set_can_focus(true);
	btnOk->set_receives_default(true);
	btnOk->set_use_stock(true);
	btnOk->set_margin_top(10);
	btnOk->set_margin_bottom(10);

	dialog_action_area3 = manage(new class Gtk::HButtonBox());
	dialog_action_area3->set_name("dialog_action_area3");
	dialog_action_area3->set_visible(true);
	dialog_action_area3->set_can_focus(false);
	dialog_action_area3->set_layout(Gtk::BUTTONBOX_CENTER);
	dialog_action_area3->add(*btnOk);
	dialog_action_area3->pack_start(*btnOk, false, false, 0);

	colunaInfoDescricao = manage(new class Gtk::TreeViewColumn(Rotinas::retUTF8("Descrição"), modeloTabelaInfo.coluna1));
	colunaInfoDescricao->set_resizable(true);
	colunaInfoDescricao->set_sizing(Gtk::TREE_VIEW_COLUMN_AUTOSIZE);
	colunaInfoDescricao->set_title(Rotinas::retUTF8("Descrição"));
	colunaInfoDescricao->set_sort_column(1);

	Gtk::CellRendererText *rtexto = manage(new class Gtk::CellRendererText());
	rtexto->property_weight() = PANGO_WEIGHT_BOLD;

	colunaInfoItem = manage(new class Gtk::TreeViewColumn("Item", *rtexto));
	colunaInfoItem->add_attribute(*rtexto, "text", modeloTabelaInfo.coluna0);
	colunaInfoItem->set_resizable(true);
	colunaInfoItem->set_sizing(Gtk::TREE_VIEW_COLUMN_AUTOSIZE);
	colunaInfoItem->set_title("Item");
	colunaInfoItem->set_sort_column(1);

	tabelaInfo = manage(new class Gtk::TreeView());
	tabelaInfo->set_name("tabelaInfo");
	tabelaInfo->set_visible(true);
	tabelaInfo->set_can_focus(true);
	tabelaInfo->append_column(*colunaInfoItem);
	tabelaInfo->append_column(*colunaInfoDescricao);

	scrollTabela1 = manage(new class Gtk::ScrolledWindow());
	scrollTabela1->set_name("scrollTabela1");
	scrollTabela1->set_visible(true);
	scrollTabela1->set_can_focus(true);
	scrollTabela1->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	scrollTabela1->set_vexpand(true);
	scrollTabela1->add(*tabelaInfo);

	labArquivoSomenteLeitura = manage(new class Gtk::Label());
	labArquivoSomenteLeitura->set_name("labArquivoSomenteLeitura");
	labArquivoSomenteLeitura->set_visible(true);
	labArquivoSomenteLeitura->set_can_focus(false);
	labArquivoSomenteLeitura->set_label("[ROL] - Arquivo Somente Leitura");

	labVolumeID = manage(new class Gtk::Label());
	labVolumeID->set_name("labVolumeID");
	labVolumeID->set_visible(true);
	labVolumeID->set_can_focus(false);
	labVolumeID->set_label("[VOL] - Volume ID");

	labLegendaDiretorio = manage(new class Gtk::Label());
	labLegendaDiretorio->set_name("labLegendaDiretorio");
	labLegendaDiretorio->set_visible(true);
	labLegendaDiretorio->set_can_focus(false);
	labLegendaDiretorio->set_label(Rotinas::retUTF8("[DIR] - Diretório"));

	labArquivoSistema = manage(new class Gtk::Label());
	labArquivoSistema->set_name("labArquivoSistema");
	labArquivoSistema->set_visible(true);
	labArquivoSistema->set_can_focus(false);
	labArquivoSistema->set_label("[SYS] - Arquivo de Sistema");

	labArquivoOculto = manage(new class Gtk::Label());
	labArquivoOculto->set_name("labArquivoOculto");
	labArquivoOculto->set_visible(true);
	labArquivoOculto->set_can_focus(false);
	labArquivoOculto->set_label("[HID] - Arquivo Oculto");

	labArquivoComum = manage(new class Gtk::Label());
	labArquivoComum->set_name("labArquivoComum");
	labArquivoComum->set_visible(true);
	labArquivoComum->set_can_focus(false);
	labArquivoComum->set_label("[ARQ] - Arquivo comum");

	table1 = manage(new class Gtk::Table(3, 2, true));
	table1->set_name("table1");
	table1->set_visible(true);
	table1->set_can_focus(false);
	table1->attach(*labArquivoComum, 0, 1, 0, 1, Gtk::FILL, Gtk::FILL, 5, 5);
	table1->attach(*labArquivoOculto, 1, 2, 0, 1, Gtk::FILL, Gtk::FILL, 5, 5);
	table1->attach(*labArquivoSistema, 0, 1, 1, 2, Gtk::FILL, Gtk::FILL, 5, 5);
	table1->attach(*labLegendaDiretorio, 1, 2, 1, 2, Gtk::FILL, Gtk::FILL, 5, 5);
	table1->attach(*labVolumeID, 0, 1, 2, 3, Gtk::FILL, Gtk::FILL, 5, 5);
	table1->attach(*labArquivoSomenteLeitura, 1, 2, 2, 3, Gtk::FILL, Gtk::FILL, 5, 5);

	frame1 = manage(new class Gtk::Frame());
	frame1->set_name("frame1");
	frame1->set_visible(true);
	frame1->set_can_focus(false);
	frame1->set_label_align(0, 0);
	frame1->add(*table1);

	vbox3 = manage(new class Gtk::VBox(false, 0));
	vbox3->set_name("vbox3");
	vbox3->set_visible(true);
	vbox3->set_can_focus(false);
	vbox3->set_spacing(2);
	vbox3->pack_start(*frame1, false, true, 0);
	vbox3->pack_start(*scrollTabela1, true, true, 0);
	vbox3->pack_start(*dialog_action_area3, false, true, 0);

	this->set_name("frmInfoDiretorio");
	this->set_size_request(385, 400);
	this->set_can_focus(false);
	this->set_border_width(5);
	this->set_title(Rotinas::retUTF8("Informações do Diretório / Arquivo"));
	this->set_resizable(false);
	this->set_modal(true);
	this->set_position(Gtk::WIN_POS_CENTER);
	this->set_type_hint(Gdk::WINDOW_TYPE_HINT_DIALOG);
	this->get_vbox()->add(*vbox3);

	btnOk->signal_clicked().connect(sigc::mem_fun(*this, &FrmInfoDiretorio::on_btnOk_clicked));

	ConstruirGrid();
}
// ---------------------------------------------------------------------------
FrmInfoDiretorio::~FrmInfoDiretorio(){

}
// ---------------------------------------------------------------------------
void FrmInfoDiretorio::Mostrar()
{
	frmInfoDiretorio->set_position(Gtk::WIN_POS_CENTER_ALWAYS);
	frmInfoDiretorio->run();
	frmInfoDiretorio->hide();
}
// ---------------------------------------------------------------------------
void FrmInfoDiretorio::on_btnOk_clicked(){
	frmInfoDiretorio->hide();
}

Glib::RefPtr<Gtk::ListStore> FrmInfoDiretorio::getStore() {
	Glib::RefPtr<Gtk::ListStore> store;
	store = Glib::RefPtr<Gtk::ListStore>::cast_static(tabelaInfo->get_model());
	return store;
}

void FrmInfoDiretorio::ConstruirGrid() {
	tabelaInfo->get_selection()->set_mode(Gtk::SELECTION_SINGLE);
	tabelaInfo->set_model(Gtk::ListStore::create(modeloTabelaInfo));
	tabelaInfo->columns_autosize();
}

void FrmInfoDiretorio::setDiretorio(Diretorio diretorio) {
	Gtk::TreeRow tLinha;

	tLinha = *(getStore()->append());
	tLinha[modeloTabelaInfo.coluna0] = "Aba:";
	tLinha[modeloTabelaInfo.coluna1] = diretorio.getAba().getNome();

	tLinha = *(getStore()->append());
	tLinha[modeloTabelaInfo.coluna0] = "Nome:";
	tLinha[modeloTabelaInfo.coluna1] = diretorio.getNome();

	tLinha = *(getStore()->append());
	tLinha[modeloTabelaInfo.coluna0] = "Tamanho:";
	tLinha[modeloTabelaInfo.coluna1] = diretorio.getTamanhoFormatado();

	tLinha = *(getStore()->append());
	tLinha[modeloTabelaInfo.coluna0] = "Tipo:";
	tLinha[modeloTabelaInfo.coluna1] = diretorio.getTipo().getNome();

	tLinha = *(getStore()->append());
	tLinha[modeloTabelaInfo.coluna0] = "Modificado:";
	tLinha[modeloTabelaInfo.coluna1] = diretorio.getModificadoFormatado();

	tLinha = *(getStore()->append());
	tLinha[modeloTabelaInfo.coluna0] = "Atributos:";
	tLinha[modeloTabelaInfo.coluna1] = diretorio.getAtributos();

	tLinha = *(getStore()->append());
	tLinha[modeloTabelaInfo.coluna0] = "Caminho:";
	tLinha[modeloTabelaInfo.coluna1] = diretorio.getCaminho();

}

