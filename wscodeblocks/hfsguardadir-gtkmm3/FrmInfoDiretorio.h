#ifndef FrmInfoDiretorio_H
#define FrmInfoDiretorio_H
// ---------------------------------------------------------------------------
#include <gtkmm/dialog.h>
#include <gtkmm/frame.h>
#include <gtkmm/table.h>
#include <gtkmm/label.h>
#include <gtkmm/box.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/treeview.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/button.h>
#include <gtkmm/treeviewcolumn.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/liststore.h>
#include <gtkmm/treeselection.h>

#include "hfsguardadir/objetos/Diretorio.h"

using namespace hfsguardadir::objetos;

// ---------------------------------------------------------------------------
	class FrmInfoDiretorio : public Gtk::Dialog {
	public:
		FrmInfoDiretorio();
		~FrmInfoDiretorio();
		static void Mostrar();
		void setDiretorio(Diretorio diretorio);
	protected:
		Gtk::VBox *vbox3;
		Gtk::Frame *frame1;
		Gtk::Table *table1;
		Gtk::Label *labArquivoComum;
		Gtk::Label *labArquivoOculto;
		Gtk::Label *labArquivoSistema;
		Gtk::Label *labLegendaDiretorio;
		Gtk::Label *labVolumeID;
		Gtk::Label *labArquivoSomenteLeitura;
		Gtk::ScrolledWindow *scrollTabela1;
		Gtk::TreeView *tabelaInfo;
		Gtk::TreeViewColumn *colunaInfoItem;
		Gtk::TreeViewColumn *colunaInfoDescricao;
		Gtk::HButtonBox *dialog_action_area3;
		Gtk::Button *btnOk;

		Glib::RefPtr<Gtk::ListStore> getStore();

	private:
		struct ColRecTabelaInfo : public Gtk::TreeModel::ColumnRecord {
		public:
			Gtk::TreeModelColumn<Glib::ustring> coluna0;
			Gtk::TreeModelColumn<Glib::ustring> coluna1;

			ColRecTabelaInfo() {
				add(coluna0);
				add(coluna1);

			}
		};
		ColRecTabelaInfo modeloTabelaInfo;

		void on_btnOk_clicked();
		void ConstruirGrid();

	};
// ---------------------------------------------------------------------------
	extern FrmInfoDiretorio *frmInfoDiretorio;
// ---------------------------------------------------------------------------
#endif
