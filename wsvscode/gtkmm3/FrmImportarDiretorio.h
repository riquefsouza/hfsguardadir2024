#ifndef FrmImportarDiretorio_H
#define FrmImportarDiretorio_H
// ---------------------------------------------------------------------------
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/textview.h>
#include <gtkmm/statusbar.h>
#include <gtkmm/label.h>
#include <gtkmm/frame.h>

#include "hfsguardadir/objetos/Diretorio.h"
#include "hfsguardadir/objetos/Importar.h"
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

// ---------------------------------------------------------------------------
	class FrmImportarDiretorio : public Gtk::Window {
	public:
		bool bSubDiretorio;
		Gtk::TextView *memoImportaDir;
		Gtk::ProgressBar *pbImportar;
		std::vector<Importar> listaImportar;

		FrmImportarDiretorio();
		~FrmImportarDiretorio();

		static void Mostrar();
		static void Fechar();
		static void ProgressoLog(Progresso progresso);
		Gtk::Label* getLabStatus2();
		void ImportarDir();

	protected:
		Gtk::VBox *form_vbox1;
		Gtk::ScrolledWindow *scrollMemo;
		Gtk::HBox *hbox3;
		Gtk::Statusbar *barraStatus1;
		Gtk::Statusbar *barraStatus2;

	private:		
		std::vector<Diretorio> listaDiretorio;
		Gtk::Label* getLabStatus1();				
	};
// ---------------------------------------------------------------------------
	extern FrmImportarDiretorio *frmImportarDiretorio;
// ---------------------------------------------------------------------------
#endif
