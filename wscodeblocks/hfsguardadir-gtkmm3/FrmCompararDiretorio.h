#ifndef FrmCompararDiretorio_H
#define FrmCompararDiretorio_H
// ---------------------------------------------------------------------------

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/label.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/treeview.h>
#include <gtkmm/frame.h>
#include <gtkmm/alignment.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/statusbar.h>

#include "hfsguardadir/objetosgui/Arvore.h"
#include "hfsguardadir/objetosgui/Tabela.h"
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::comum;
using namespace hfsguardadir::objetosgui;

// ---------------------------------------------------------------------------
	class FrmCompararDiretorio : public Gtk::Window {
	public:
		Gtk::ProgressBar *pb2;

		FrmCompararDiretorio();
		~FrmCompararDiretorio();
		static void mostrar();
		static void ProgressoLog(Progresso progresso);

	protected:
		Gtk::VBox *vbox5;
		Gtk::HBox *hbox1;
		Gtk::Button *btnCompararDiretorios;		
		Gtk::Button *btnSalvarLog;
		Gtk::HBox *hbox2;
		Gtk::Frame *frame2;
		Gtk::Alignment *alignment1;
		Gtk::VBox *vbox6;
		Gtk::ComboBoxText *cmbAba1;
		Gtk::ScrolledWindow *scrolledwindow3;
		Arvore *tvDiretorio1;
		Gtk::Label *labDiretorio1;
		Gtk::Frame *frame3;
		Gtk::Alignment *alignment2;
		Gtk::VBox *vbox7;
		Gtk::ComboBoxText *cmbAba2;
		Gtk::ScrolledWindow *scrolledwindow4;
		Arvore *tvDiretorio2;
		Gtk::Label *label6;
		Gtk::HBox *hbox4;
		Gtk::Label *labDiferencasEncontradas;
		Gtk::ScrolledWindow *scrollTabela12;
		Tabela *tabelaCompara;
		Gtk::HBox *hbox5;
		Gtk::Statusbar *barraStatus11;
		Gtk::Statusbar *barraStatus21;

		std::vector<Diretorio> listaCompara;

	private:
		Gtk::Label* getLabStatus1();
		Gtk::Label* getLabStatus2();
		void CarregarDados();
		void LimparComparacao();
		Glib::ustring SQLCompara(Aba aba1, Aba aba2, const Glib::ustring caminho1, const Glib::ustring caminho2);
		void Comparar(const Glib::ustring sCaminhoDir1, const Glib::ustring sCaminhoDir2);
		void on_btnCompararDiretorios_clicked();
		void btnSalvarLog_clicked_cb();
		void on_cmbAba1_changed();
		void on_tvDiretorio1_row_collapsed(const Gtk::TreeModel::iterator& iter, const Gtk::TreeModel::Path& path);
		void on_tvDiretorio1_row_expanded(const Gtk::TreeModel::iterator& iter, const Gtk::TreeModel::Path& path);
		bool on_tvDiretorio1_button_press_event(GdkEventButton *event);
		void on_cmbAba2_changed();
		void on_tvDiretorio2_row_collapsed(const Gtk::TreeModel::iterator& iter, const Gtk::TreeModel::Path& path);
		void on_tvDiretorio2_row_expanded(const Gtk::TreeModel::iterator& iter, const Gtk::TreeModel::Path& path);
		bool on_tvDiretorio2_button_press_event(GdkEventButton *event);
		void on_tabelaCompara_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);
		bool on_tabelaCompara_button_release_event(GdkEventButton *event);

	};
// ---------------------------------------------------------------------------
	extern FrmCompararDiretorio *frmCompararDiretorio;
// ---------------------------------------------------------------------------
#endif
