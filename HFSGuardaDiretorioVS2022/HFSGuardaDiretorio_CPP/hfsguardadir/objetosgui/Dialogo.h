#ifndef DIALOGO_H
#define DIALOGO_H

#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosgui {

class Dialogo
{
private:
	/*
	static int MsgDlg(Gtk::Window* pai, const char *sTitulo,
		const char *sMensagem, Gtk::MessageType tipo, Gtk::ButtonsType botoes);
		*/
public:
	Dialogo();
	virtual ~Dialogo();
	/*
	static void mensagemErro2(Gtk::Window* pai, const char* recurso, const std::string &texto);
	static void mensagemErro(Gtk::Window* pai, const char* recurso);
	static void mensagemInfo(Gtk::Window* pai, const char* recurso);
	static bool confirma(Gtk::Window* pai, const char* recurso);
	static std::string entrada(Gtk::Window* pai, const char* recurso);
	static std::string entrada2(Gtk::Window* pai, const char* recurso,
		const std::string &valorInicial);
		*/
};

}
}

#endif
