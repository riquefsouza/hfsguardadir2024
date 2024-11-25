#include "hfsguardadir/objetosgui/Dialogo.h"
#include "resource.h"

#include <gtkmm/table.h>
#include <gtkmm/entry.h>
#include <gtkmm/stock.h>

namespace hfsguardadir {

namespace objetosgui {

Dialogo::Dialogo()
{
}


Dialogo::~Dialogo()
{
}

gint Dialogo::MsgDlg(Gtk::Window* pai, const gchar *sTitulo,
	const gchar *sMensagem, Gtk::MessageType tipo, Gtk::ButtonsType botoes) {

	Gtk::MessageDialog dialog(*pai, sMensagem, false, tipo, botoes, true);

	dialog.set_title(sTitulo);
	dialog.set_position(Gtk::WIN_POS_CENTER);
	//dialog.set_has_separator(false);
	gint ret = dialog.run();

	return ret;
}

void Dialogo::mensagemErro2(Gtk::Window* pai, const char* recurso, const Glib::ustring &texto) {
	Glib::ustring msg, titulo;

	msg = Rotinas::getRecurso(recurso);
	msg += " " + texto;

	titulo = Rotinas::getRecurso("Dialogo.erro");

	Dialogo::MsgDlg(pai, titulo.c_str(), msg.c_str(), Gtk::MESSAGE_ERROR,
		Gtk::BUTTONS_OK);
}

void Dialogo::mensagemErro(Gtk::Window* pai, const char* recurso) {
	Dialogo::mensagemErro2(pai, recurso, "");
}

void Dialogo::mensagemInfo(Gtk::Window* pai, const char* recurso) {
	Glib::ustring msg, titulo;

	msg = Rotinas::getRecurso(recurso);
	titulo = Rotinas::getRecurso("Dialogo.info");

	Dialogo::MsgDlg(pai, titulo.c_str(), msg.c_str(),
		Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK);
}

bool Dialogo::confirma(Gtk::Window* pai, const char* recurso) {
	Glib::ustring msg, titulo;

	msg = Rotinas::getRecurso(recurso);
	titulo = Rotinas::getRecurso("Dialogo.confirma");

	return (Dialogo::MsgDlg(pai, titulo.c_str(), msg.c_str(),
		Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO) == Gtk::RESPONSE_YES);
}

Glib::ustring Dialogo::entrada2(Gtk::Window* pai, const char* recurso,
	const Glib::ustring &valorInicial) {
	Glib::ustring titulo, rotulo, texto;

	gint response;

	texto = "";
	titulo = Rotinas::getRecurso("Dialogo.entrada");
	rotulo = Rotinas::getRecurso(recurso);

	Gtk::Dialog dialog(titulo, *pai, true);

	dialog.property_destroy_with_parent() = true;
	dialog.add_button(Gtk::Stock::OK, Gtk::ResponseType::RESPONSE_OK);
	dialog.add_button(Gtk::Stock::CANCEL, Gtk::ResponseType::RESPONSE_CANCEL);

	Gtk::HBox hbox(false, 8);
	hbox.set_border_width(8);
	dialog.get_vbox()->pack_start(hbox, false, false, 0);

	Gtk::Image stock(Gtk::Stock::DIALOG_QUESTION, Gtk::ICON_SIZE_DIALOG);
	hbox.pack_start(stock, false, false, 0);

	Gtk::Table table(2, 2, false);
	table.set_row_spacings(4);
	table.set_col_spacings(4);
	hbox.pack_start(table, true, true, 0);
	Gtk::Label label(rotulo);
	table.attach(label, 0, 1, 0, 1);
	Gtk::Entry local_entry1;
	local_entry1.set_text(valorInicial);
	table.attach(local_entry1, 1, 2, 0, 1);
	label.set_mnemonic_widget(local_entry1);

	hbox.show_all();
	response = dialog.run();

	if (response == Gtk::ResponseType::RESPONSE_OK)
	{
		texto = local_entry1.get_text();
	}
	return texto;
}

Glib::ustring Dialogo::entrada(Gtk::Window* pai, const char* recurso) {
	return Dialogo::entrada2(pai, recurso, "");
}

}
}
