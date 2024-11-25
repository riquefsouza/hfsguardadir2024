#ifndef MenuPopup_H
#define MenuPopup_H
// ---------------------------------------------------------------------------
#include <gtkmm/menu.h>
#include <gtkmm/menuitem.h>
#include <gtkmm/separatormenuitem.h>
// ---------------------------------------------------------------------------
	class MenuPopup : public Gtk::Menu {
	public:
		MenuPopup();
		~MenuPopup();
		static void mostrar();
	protected:
		Gtk::MenuItem *menuInformacoesDiretorioArquivo;
		Gtk::MenuItem *menuExcluirDiretorioSelecionado;
		Gtk::MenuItem *menuExpandirDiretorios2;
		Gtk::MenuItem *menuColapsarDiretorios2;
		Gtk::SeparatorMenuItem *separador2;
		Gtk::MenuItem *menuIncluirNovaAba2;
		Gtk::MenuItem *menuAlterarNomeAbaAtiva2;
		Gtk::MenuItem *menuExcluirAbaAtiva2;

	private:
		void on_menuInformacoesDiretorioArquivo_activate();
		void on_menuExcluirDiretorioSelecionado_activate();
		void on_menuExpandirDiretorios2_activate();
		void on_menuColapsarDiretorios2_activate();
		void on_menuIncluirNovaAba2_activate();
		void on_menuAlterarNomeAbaAtiva2_activate();
		void on_menuExcluirAbaAtiva2_activate();

	};
// ---------------------------------------------------------------------------
	extern MenuPopup *menuPopup;
// ---------------------------------------------------------------------------
#endif
