#ifndef FrmCadExtensao_H
#define FrmCadExtensao_H
// ---------------------------------------------------------------------------
#include <gtkmm/dialog.h>
#include <gtkmm/box.h>
#include <gtkmm/menu.h>
#include <gtkmm/menubar.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/treeview.h>
#include <gtkmm/treeviewcolumn.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/liststore.h>
#include <gtkmm/treeselection.h>
#include <gdkmm/pixbuf.h>

// ---------------------------------------------------------------------------
	class FrmCadExtensao : public Gtk::Dialog {
	public:
		FrmCadExtensao();
		~FrmCadExtensao();
		static void mostrar();
	protected:
		Gtk::VBox *form_vbox;
		Gtk::VBox *vbox;
		Gtk::MenuBar *barraMenu;
		Gtk::MenuItem *menuExtensao;
		Gtk::Menu *submenuExtensao;
		Gtk::MenuItem *menuIncluirExtensao;
		Gtk::MenuItem *menuExcluirExtensao;
		Gtk::MenuItem *menuExcluirTodasExtensoes;
		Gtk::MenuItem *menuExportarTodos;
		Gtk::Menu *submenuExportarTodos;
		Gtk::MenuItem *menuExportarBitmap;
		Gtk::MenuItem *menuExportarIcone;
		Gtk::MenuItem *menuExportarGIF;
		Gtk::MenuItem *menuExportarJPEG;
		Gtk::MenuItem *menuExportarPNG;
		Gtk::MenuItem *menuExportarTIFF;
		Gtk::MenuItem *menuImportarTodos;
		Gtk::Menu *submenuImportarTodos;
		Gtk::MenuItem *menuImportarIconesArquivos;
		Gtk::MenuItem *menuExtrairIconesArquivos;
		Gtk::ScrolledWindow *scrollTabela;
		Gtk::TreeView *tabelaExtensao;
		Gtk::TreeViewColumn *colunaCadExtExtensao;
		Gtk::TreeViewColumn *colunaCadExtIcone;
		Gtk::HButtonBox *form_area;
		Gtk::Button *btnIncluir;
		Gtk::Button *btnExcluir;

		Glib::RefPtr<Gtk::ListStore> getStore();

	private:
		struct ColRecTabelaExtensao : public Gtk::TreeModel::ColumnRecord {
		public:
			Gtk::TreeModelColumn<Glib::ustring> coluna0;
			Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf>> coluna1;

			ColRecTabelaExtensao() {
				add(coluna0);
				add(coluna1);

			}
		};
		ColRecTabelaExtensao modeloTabelaExtensao;

		void CarregarExtensoesNaGrid();
		void on_menuIncluirExtensao_activate();
		void on_menuExcluirExtensao_activate();
		void on_menuExcluirTodasExtensoes_activate();
		void on_menuExportarBitmap_activate();
		void on_menuExportarIcone_activate();
		void on_menuExportarGIF_activate();
		void on_menuExportarJPEG_activate();
		void on_menuExportarPNG_activate();
		void on_menuExportarTIFF_activate();
		void on_menuImportarIconesArquivos_activate();
		void on_menuExtrairIconesArquivos_activate();
		void on_btnIncluir_clicked();
		void on_btnExcluir_clicked();

	};
// ---------------------------------------------------------------------------
	extern FrmCadExtensao *frmCadExtensao;
// ---------------------------------------------------------------------------
#endif
