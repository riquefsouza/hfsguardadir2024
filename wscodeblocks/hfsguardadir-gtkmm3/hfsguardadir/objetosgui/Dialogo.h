#ifndef DIALOGO_H
#define DIALOGO_H

#include "../comum/Rotinas.h"

#include <gtkmm/window.h>
#include <gtkmm/messagedialog.h>

using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosgui {

class Dialogo
{
private:
	static gint MsgDlg(Gtk::Window* pai, const gchar *sTitulo,
		const gchar *sMensagem, Gtk::MessageType tipo, Gtk::ButtonsType botoes);

public:
	Dialogo();
	virtual ~Dialogo();

	static void mensagemErro2(Gtk::Window* pai, const char* recurso, const Glib::ustring &texto);
	static void mensagemErro(Gtk::Window* pai, const char* recurso);
	static void mensagemInfo(Gtk::Window* pai, const char* recurso);
	static bool confirma(Gtk::Window* pai, const char* recurso);
	static Glib::ustring entrada(Gtk::Window* pai, const char* recurso);
	static Glib::ustring entrada2(Gtk::Window* pai, const char* recurso,
		const Glib::ustring &valorInicial);
};

}
}

#endif
