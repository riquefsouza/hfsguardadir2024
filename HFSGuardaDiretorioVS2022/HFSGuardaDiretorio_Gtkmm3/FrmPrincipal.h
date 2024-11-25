#ifndef FrmPrincipal_H
#define FrmPrincipal_H

#ifndef PTRDIFF_MAX
#define PTRDIFF_MAX (std::numeric_limits<ptrdiff_t>::max())
#endif
// ---------------------------------------------------------------------------

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/menu.h>
#include <gtkmm/menubar.h>
#include <gtkmm/menuitem.h>
#include <gtkmm/separatormenuitem.h>
#include <gtkmm/toolbar.h>
#include <gtkmm/toolitem.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/button.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/treeview.h>
#include <gtkmm/notebook.h>
#include <gtkmm/paned.h>
#include <gtkmm/statusbar.h>
#include <gtkmm/selectiondata.h>

//#include "hfsguardadir/objetosgui/Arvore.h"
#include "hfsguardadir/objetosgui/Tabela.h"

using namespace hfsguardadir::objetosgui;

// ---------------------------------------------------------------------------
	class FrmPrincipal : public Gtk::Window {
	public:
		GtkCheckMenuItem *menuGravarLogImportacao;
		Gtk::Notebook *notebook1;
		Gtk::VPaned *spPesquisa;
		Gtk::ProgressBar *pb;
		Gtk::Entry *edtPesquisa;
		Tabela *tabelaPesquisa;

		FrmPrincipal();
		~FrmPrincipal();

		static void Mostrar();
		static void ProgressoLog(Progresso progresso);
		//Gtk::Label* getLabStatus1();
		//Gtk::Label* getLabStatus2();
		void adicionaTabPage(Gtk::Notebook* noteBook, Gtk::HPaned* spPanel, const Glib::ustring nomeAba);

		void on_arvoreFixa_selection_changed();
		void on_arvoreFixa_row_collapsed(const Gtk::TreeModel::iterator& iter, const Gtk::TreeModel::Path& path);
		bool on_arvoreFixa_button_release_event(GdkEventButton *event);
		bool on_arvoreFixa_button_press_event(GdkEventButton *event);
		void on_arvoreFixa_row_expanded(const Gtk::TreeModel::iterator& iter, const Gtk::TreeModel::Path& path);

		bool on_tabelaFixa_button_release_event(GdkEventButton *event);
		void on_tabelaFixa_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);

	protected:
		Gtk::VBox *vbox1;
		Gtk::MenuBar *barraMenu1;
		Gtk::MenuItem *menuAba;
		Gtk::Menu *submenuAba;
		Gtk::MenuItem *menuIncluirNovaAba;
		Gtk::MenuItem *menuAlterarNomeAbaAtiva;
		Gtk::MenuItem *menuExcluirAbaAtiva;
		Gtk::MenuItem *menuDiretorio;
		Gtk::Menu *submenuDiretorio;
		Gtk::MenuItem *menuImportarDiretorio;
		Gtk::MenuItem *menuImportarSubDiretorios;
		Gtk::MenuItem *menuCompararDiretorios;
		Gtk::MenuItem *menuCadastrarExtensaoArquivo;
		Gtk::SeparatorMenuItem *menuseparador1;
		Gtk::MenuItem *menuExpandirDiretorios;
		Gtk::MenuItem *menuColapsarDiretorios;
		Gtk::MenuItem *menuExportarDiretoriosAbaAtiva;
		Gtk::Menu *menu2;
		Gtk::MenuItem *menuTXT;
		Gtk::MenuItem *menuCSV;
		Gtk::MenuItem *menuHTML;
		Gtk::MenuItem *menuXML;
		Gtk::MenuItem *menuSQL;
		Gtk::MenuItem *menuImportarDiretoriosViaXML;		
		Gtk::MenuItem *menuVisao;
		Gtk::Menu *submenuVisao;
		Gtk::MenuItem *menuMostrarOcultarArvoreDirAbaAtiva;
		Gtk::MenuItem *menuMostrarOcultarListaItensPesquisados;
		Gtk::MenuItem *menuSobre;
		Gtk::Menu *submenuSobre;
		Gtk::MenuItem *menuSobreCatalogador;
		Gtk::Toolbar *toolbar1;
		Gtk::ToolItem *toolbutton1;
		Gtk::Button *btnImportarDiretorio;
		Gtk::ToolItem *toolbutton2;		
		Gtk::ToolItem *toolbutton3;		
		Gtk::ToolItem *toolbutton4;
		Gtk::Button *btnPesquisa;		
		Gtk::HPaned *sp;
		Gtk::ScrolledWindow *scrollArvore;
		//Arvore *arvoreFixa;
		Gtk::ScrolledWindow *scrollTabelaFixa;
		Tabela *tabelaFixa;
		Gtk::ScrolledWindow *scrollPesquisa;		
		Gtk::HBox *hbox6;
		Gtk::Statusbar *barraStatus111;
		Gtk::Statusbar *barraStatus211;

		Gtk::Menu *popupMenu;
		gint nLargura;
		gint nAltura;

		Gtk::MenuItem *menuInformacoesDiretorioArquivo;
		Gtk::MenuItem *menuExcluirDiretorioSelecionado;
		Gtk::MenuItem *menuExpandirDiretorios2;
		Gtk::MenuItem *menuColapsarDiretorios2;
		Gtk::SeparatorMenuItem *menuseparador2;
		Gtk::MenuItem *menuIncluirNovaAba2;
		Gtk::MenuItem *menuAlterarNomeAbaAtiva2;
		Gtk::MenuItem *menuExcluirAbaAtiva2;

	private:
		void on_menuIncluirNovaAba_activate();
		void on_menuAlterarNomeAbaAtiva_activate();
		void on_menuExcluirAbaAtiva_activate();
		void on_menuImportarDiretorio_activate();
		void on_menuImportarSubDiretorios_activate();
		void on_menuCompararDiretorios_activate();
		void on_menuCadastrarExtensaoArquivo_activate();
		void on_menuExpandirDiretorios_activate();
		void on_menuColapsarDiretorios_activate();
		void on_menuExportarDiretoriosAbaAtiva_activate();
		void on_menuTXT_activate();
		void on_menuCSV_activate();
		void on_menuHTML_activate();
		void on_menuXML_activate();
		void on_menuSQL_activate();
		void on_menuImportarDiretoriosViaXML_activate();
		void on_menuMostrarOcultarArvoreDirAbaAtiva_activate();
		void on_menuMostrarOcultarListaItensPesquisados_activate();
		void on_menuSobreCatalogador_activate();
		void on_btnImportarDiretorio_clicked();
		void on_btnPesquisa_clicked();

		void on_notebook1_switch_page(GtkNotebook* page, guint page_num);

		bool on_tabelaPesquisa_button_release_event(GdkEventButton *event);
		
		bool on_FrmPrincipal_delete_event(GdkEventAny *event);
				
		void ConstruirPopupMenu();
		void on_menuInformacoesDiretorioArquivo_activate();
		void on_menuExcluirDiretorioSelecionado_activate();
		void on_menuExpandirDiretorios2_activate();
		void on_menuColapsarDiretorios2_activate();
		void on_menuIncluirNovaAba2_activate();
		void on_menuAlterarNomeAbaAtiva2_activate();
		void on_menuExcluirAbaAtiva2_activate();

	};
// ---------------------------------------------------------------------------
	extern FrmPrincipal *frmPrincipal;
// ---------------------------------------------------------------------------
#endif
