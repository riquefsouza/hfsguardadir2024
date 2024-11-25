#include "FrmSobre.h"
#include "resource.h"
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::comum;
// ---------------------------------------------------------------------------
FrmSobre *frmSobre = (FrmSobre*) NULL;
// ---------------------------------------------------------------------------
FrmSobre::FrmSobre()
    : Gtk::AboutDialog() {
/*
	: Gtk::Dialog() {

	btbOk = manage(new class Gtk::Button());
	btbOk->set_name("btbOk");
	btbOk->set_label("_Ok");
	btbOk->set_visible(true);
	btbOk->set_can_focus(true);
	btbOk->set_receives_default(true);
	btbOk->set_use_underline(true);
	btbOk->set_margin_top(10);

	dialog_action_area1 = manage(new class Gtk::HButtonBox());
	dialog_action_area1->set_name("dialog_action_area1");
	dialog_action_area1->set_visible(true);
	dialog_action_area1->set_can_focus(false);
	dialog_action_area1->set_layout(Gtk::BUTTONBOX_CENTER);
	dialog_action_area1->add(*btbOk);
	dialog_action_area1->pack_start(*btbOk, false, false, 0);

	label10 = manage(new class Gtk::Label());
	label10->set_name("label10");
	label10->set_visible(true);
	label10->set_can_focus(false);
	label10->set_label("Todos os direitos reservados, 2024");

	label9 = manage(new class Gtk::Label());
	label9->set_name("label9");
	label9->set_visible(true);
	label9->set_can_focus(false);
	label9->set_label("Por Henrique Figueiredo de Souza");

	label8 = manage(new class Gtk::Label());
	label8->set_name("label8");
	label8->set_visible(true);
	label8->set_can_focus(false);
	label8->set_label(Rotinas::retUTF8("Desenvolvido em C++ com GTKMM 3.0"));

	label = manage(new class Gtk::Label());
	label->set_name("label");
	label->set_visible(true);
	label->set_can_focus(false);
	label->set_label(Rotinas::retUTF8("HFSGuardaDir 2.0 - Catalogador de Diretórios"));

	vbox4 = manage(new class Gtk::VBox(false, 0));
	vbox4->set_name("vbox4");
	vbox4->set_visible(true);
	vbox4->set_can_focus(false);
	vbox4->pack_start(*label, false, true, 0);
	vbox4->pack_start(*label8, false, true, 0);
	vbox4->pack_start(*label9, false, true, 0);
	vbox4->pack_start(*label10, false, true, 0);

	dialog_vbox1 = manage(new class Gtk::VBox(false, 0));
	dialog_vbox1->set_name("dialog_vbox1");
	dialog_vbox1->set_visible(true);
	dialog_vbox1->set_can_focus(false);
	dialog_vbox1->set_spacing(2);
	dialog_vbox1->pack_start(*vbox4, true, true, 0);
	dialog_vbox1->pack_start(*dialog_action_area1, false, true, 0);

	this->set_name("frmSobre");
	this->set_can_focus(false);
	this->set_border_width(5);
	this->set_title("Sobre o Catalogador");
	this->set_resizable(false);
	this->set_modal(true);
	this->property_destroy_with_parent() = true;
	this->set_position(Gtk::WIN_POS_CENTER);
	this->set_default_size(300, 150);
	this->set_type_hint(Gdk::WINDOW_TYPE_HINT_DIALOG);
	this->get_vbox()->add(*dialog_vbox1);
*/

	#ifdef __GNUC__
        splashImagem = Rotinas::XPMToPixbuf(XPM_SPLASH);
    #else
        splashImagem = Rotinas::imagemToPixbuf("splash.gif");
	#endif

	this->set_name("frmSobre");
	this->set_can_focus(false);
	this->set_border_width(5);
	this->set_title("Sobre o Catalogador");
	this->set_resizable(false);
	this->set_modal(true);
	this->property_destroy_with_parent() = true;
	this->set_position(Gtk::WIN_POS_CENTER);
	this->set_default_size(300, 150);
	this->set_type_hint(Gdk::WINDOW_TYPE_HINT_DIALOG);

	this->set_program_name(Rotinas::retUTF8("HFSGuardaDir 2.0 - Catalogador de Diretórios"));
	this->set_version(Rotinas::retUTF8("Desenvolvido em C com GTK 3"));
	this->set_copyright("Todos os direitos reservados, 2024");

	autores.push_back("Henrique Figueiredo de Souza");

	this->set_authors(autores);
	this->set_logo(splashImagem);
	this->set_license_type(Gtk::LICENSE_AGPL_3_0);

	//btbOk->signal_clicked().connect(sigc::mem_fun(*this, &FrmSobre::on_btbOk_clicked));

}
// ---------------------------------------------------------------------------
FrmSobre::~FrmSobre(){

}
// ---------------------------------------------------------------------------
void FrmSobre::mostrar()
{
    frmSobre = new FrmSobre();
	frmSobre->set_position(Gtk::WIN_POS_CENTER_ALWAYS);
	frmSobre->run();
	frmSobre->hide();
}
// ---------------------------------------------------------------------------
//void FrmSobre::on_btbOk_clicked(){
//	this->hide();
//}


// ---------------------------------------------------------------------------
