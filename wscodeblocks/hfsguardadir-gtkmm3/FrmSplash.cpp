#include "FrmSplash.h"
#include "resource.h"
#include <gtkmm/main.h>

// ---------------------------------------------------------------------------
FrmSplash *frmSplash = (FrmSplash*) NULL;
// ---------------------------------------------------------------------------
FrmSplash::FrmSplash()
	: Gtk::Window(Gtk::WINDOW_TOPLEVEL) {

	pb1 = manage(new class Gtk::ProgressBar());
	pb1->set_name("pb1");
	pb1->set_visible(true);
	pb1->set_can_focus(false);
	pb1->set_show_text(true);
/*
	label5 = manage(new class Gtk::Label());
	label5->set_name("label5");
	label5->set_visible(true);
	label5->set_can_focus(false);
	label5->set_label(Rotinas::retUTF8("Catalogador de Diretórios"));

	label4 = manage(new class Gtk::Label());
	label4->set_name("label4");
	label4->set_visible(true);
	label4->set_can_focus(false);
	label4->set_label("HFSGuardaDiretorio 2.0");
*/
	vbox2 = manage(new class Gtk::VBox(false, 0));
	vbox2->set_name("vbox2");
	vbox2->set_visible(true);
	vbox2->set_can_focus(false);
	vbox2->set_spacing(6);
	vbox2->set_border_width(1);
/*
	vbox2->add(*label4);
	vbox2->pack_start(*label4, false, true, 0);
	vbox2->add(*label5);
	vbox2->pack_start(*label5, false, true, 0);
*/

#ifdef __GNUC__
    splashImagem = manage(new class Gtk::Image(Rotinas::XPMToPixbuf(XPM_SPLASH)));
#else
    splashImagem = manage(new class Gtk::Image(Rotinas::imagemToPixbuf("splash.gif")));
#endif

	vbox2->add(*splashImagem);
	vbox2->pack_start(*splashImagem, false, true, 0);

	vbox2->add(*pb1);
	vbox2->pack_end(*pb1, true, true, 0);

	this->set_name("frmSplash");
	this->set_size_request(375, 113);
	this->set_visible(true);
	this->set_can_focus(false);
	this->set_modal(true);
	this->set_resizable(false);
	this->set_position(Gtk::WIN_POS_CENTER_ALWAYS);
	this->set_default_size(375, 113);
	this->set_decorated(false);
	this->add(*vbox2);
}
// ---------------------------------------------------------------------------
FrmSplash::~FrmSplash(){

}
// ---------------------------------------------------------------------------
void FrmSplash::Mostrar()
{
    frmSplash = new FrmSplash();
	frmSplash->set_position(Gtk::WIN_POS_CENTER_ALWAYS);
	frmSplash->show_all();
}

void FrmSplash::Fechar()
{
	frmSplash->hide();
}

void FrmSplash::ProgressoLog(Progresso progresso)
{
	if (frmSplash != NULL) {
		if (progresso.posicao == 0) {
			frmSplash->pb1->set_fraction(progresso.minimo);
			frmSplash->pb1->set_pulse_step(0.1); //progresso.passo
		}
		frmSplash->pb1->set_fraction(
			Rotinas::calculaProgresso(progresso.maximo, progresso.posicao));

		while (Gtk::Main::events_pending()) {
			Gtk::Main::iteration();
		}
	}

}


