#include <gtkmm/main.h>
#include <gdkmm/cursor.h>

#include "FrmImportarDiretorio.h"
#include "hfsguardadir/catalogador/Catalogador.h"
#include "hfsguardadir/objetosbo/ImportarBO.h"
#include "hfsguardadir/objetosbo/DiretorioBO.h"
#include "hfsguardadir/objetosgui/Dialogo.h"

using namespace hfsguardadir::catalogador;
using namespace hfsguardadir::objetosgui;
using namespace hfsguardadir::objetosbo;

// ---------------------------------------------------------------------------
FrmImportarDiretorio *frmImportarDiretorio = (FrmImportarDiretorio*) NULL;
// ---------------------------------------------------------------------------
FrmImportarDiretorio::FrmImportarDiretorio()
	: Gtk::Window(Gtk::WINDOW_TOPLEVEL) {

	barraStatus2 = manage(new class Gtk::Statusbar());
	barraStatus2->set_name("barraStatus2");
	barraStatus2->set_visible(true);
	barraStatus2->set_can_focus(false);
	barraStatus2->set_spacing(2);

	barraStatus1 = manage(new class Gtk::Statusbar());
	barraStatus1->set_name("barraStatus1");
	barraStatus1->set_visible(true);
	barraStatus1->set_can_focus(false);
	barraStatus1->set_spacing(2);
	//barraStatus1->set_has_resize_grip(false);

	hbox3 = manage(new class Gtk::HBox(false, 0));
	hbox3->set_name("hbox3");
	hbox3->set_visible(true);
	hbox3->set_can_focus(false);
	hbox3->pack_start(*barraStatus1, false, true, 0);
	hbox3->pack_start(*barraStatus2, true, true, 0);

	pbImportar = manage(new class Gtk::ProgressBar());
	pbImportar->set_name("pbImportar");
	pbImportar->set_visible(true);
	pbImportar->set_can_focus(false);

	memoImportaDir = manage(new class Gtk::TextView());
	memoImportaDir->set_name("memoImportaDir");
	memoImportaDir->set_visible(true);
	memoImportaDir->set_can_focus(true);

	scrollMemo = manage(new class Gtk::ScrolledWindow());
	scrollMemo->set_name("scrollMemo");
	scrollMemo->set_visible(true);
	scrollMemo->set_can_focus(true);
	scrollMemo->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	scrollMemo->add(*memoImportaDir);

	form_vbox1 = manage(new class Gtk::VBox(false, 0));
	form_vbox1->set_name("form_vbox1");
	form_vbox1->set_visible(true);
	form_vbox1->set_can_focus(false);
	form_vbox1->pack_start(*scrollMemo, true, true, 0);
	form_vbox1->pack_start(*pbImportar, false, true, 0);
	form_vbox1->pack_start(*hbox3, false, true, 0);

	this->set_name("frmImportarDiretorio");
	this->set_size_request(895, 572);
	this->set_visible(true);
	this->set_can_focus(false);
	this->set_title("Importando Diretório");
	this->set_resizable(false);
	this->set_modal(true);
	this->set_position(Gtk::WIN_POS_CENTER);
	this->set_default_size(895, 572);
	this->set_decorated(false);
	this->add(*form_vbox1);

}
// ---------------------------------------------------------------------------
FrmImportarDiretorio::~FrmImportarDiretorio(){

}
// ---------------------------------------------------------------------------
void FrmImportarDiretorio::Mostrar()
{
    //frmImportarDiretorio = new FrmImportarDiretorio();
	frmImportarDiretorio->set_position(Gtk::WIN_POS_CENTER_ALWAYS);
	frmImportarDiretorio->show();
}

void FrmImportarDiretorio::Fechar()
{
	frmImportarDiretorio->hide();
}

Gtk::Label* FrmImportarDiretorio::getLabStatus1() {
	Glib::ListHandle<Gtk::Widget*> hlista = barraStatus1->get_children();
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

Gtk::Label* FrmImportarDiretorio::getLabStatus2() {
	Glib::ListHandle<Gtk::Widget*> hlista = barraStatus2->get_children();
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


void FrmImportarDiretorio::ProgressoLog(Progresso progresso)
{
	Glib::RefPtr<Gtk::TextBuffer> buffer;
	Gtk::TextIter titer;
	gint pos;
	Glib::ustring texto = "";

	if (frmImportarDiretorio != NULL) {
		if (progresso.posicao == 0) {
			frmImportarDiretorio->pbImportar->set_fraction(progresso.minimo);
			frmImportarDiretorio->pbImportar->set_pulse_step(0.1); //progresso.passo
		}
		if (progresso.maximo > 0) {
			frmImportarDiretorio->pbImportar->set_fraction(
				Rotinas::calculaProgresso(progresso.maximo, progresso.posicao));
		}

		if (progresso.log.length() > 0) {
			buffer = frmImportarDiretorio->memoImportaDir->get_buffer();
			pos = buffer->get_line_count();
			titer = buffer->get_iter_at_line(pos);
			texto = progresso.log + "\n";
			buffer->insert(titer, texto);
			frmImportarDiretorio->memoImportaDir->set_buffer(buffer);
			frmImportarDiretorio->memoImportaDir->scroll_to(titer, 0);
			frmImportarDiretorio->getLabStatus2()->set_text(Rotinas::IntToStr(pos));
		}

		while (Gtk::Main::events_pending()) {
			Gtk::Main::iteration();
		}
	}
}

void FrmImportarDiretorio::ImportarDir()
{
	Glib::RefPtr<Gtk::TextBuffer> buffer;
	Gtk::TextIter titer;
	gint nlinhas;
	Glib::ustring sLog, texto;
	Importar importar;
	std::vector<Glib::ustring> log;

	for (unsigned int i = 0; i < listaImportar.size(); i++) {
		importar = listaImportar.at(i);

		catalogador->diretorioOrdem.setOrdem(1);

		if (!bSubDiretorio) {
			get_window()->set_cursor(Gdk::Cursor::create(Gdk::WATCH));

			ImportarBO::getInstancia()->ImportacaoCompleta(importar,
				&catalogador->diretorioOrdem, catalogador->listaExtensoes,
				ProgressoLog);

			get_window()->set_cursor(Gdk::Cursor::create(Gdk::ARROW));
		}
		else {
			if (!DiretorioBO::getInstancia()->verificaCodDir(importar.getAba(),
				importar.getRotuloRaiz(), catalogador->listaDiretorioPai)) {
				get_window()->set_cursor(Gdk::Cursor::create(Gdk::WATCH));

				ImportarBO::getInstancia()->ImportacaoCompleta(importar,
					&catalogador->diretorioOrdem, catalogador->listaExtensoes,
					ProgressoLog);

				get_window()->set_cursor(Gdk::Cursor::create(Gdk::ARROW));
			}
			else {
				Dialogo::mensagemInfo(frmImportarDiretorio,
					"DiretorioExisteCatalogo");
			}
		}
	}
/*
	if (frmPrincipal->menuGravarLogImportacao->get_active()) {
		buffer = memoImportaDir->get_buffer();
		nlinhas = buffer->get_line_count();
		if (nlinhas > 0) {
			sLog = Rotinas::AppDirPath() +
				Rotinas::formataDate(Rotinas::FORMATO_DHARQUIVO, Rotinas::DataHoraNow()) +
				"_Importacao.log";

			for (int nlinha = 0; nlinha < nlinhas; nlinha++) {
				titer = buffer->get_iter_at_line(nlinha);
				texto = buffer->get_text(titer, titer, false);

				log.push_back(texto);
			}

			Rotinas::SListSaveToFile(log, sLog);
		}
	}
*/
}
