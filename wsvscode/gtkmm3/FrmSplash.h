#ifndef FrmSplash_H
#define FrmSplash_H
// ---------------------------------------------------------------------------
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/label.h>
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::comum;
// ---------------------------------------------------------------------------
	class FrmSplash : public Gtk::Window {
	public:
		FrmSplash();
		~FrmSplash();
		static void Mostrar();
		static void Fechar();
		static void ProgressoLog(Progresso progresso);
	protected:
		Gtk::VBox *vbox2;
		Gtk::Label *label4;
		Gtk::Label *label5;
		Gtk::ProgressBar *pb1;

	private:
		
	};
// ---------------------------------------------------------------------------
	extern FrmSplash *frmSplash;
// ---------------------------------------------------------------------------
#endif
