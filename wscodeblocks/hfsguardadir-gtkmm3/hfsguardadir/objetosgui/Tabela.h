#ifndef TABELA_H
#define TABELA_H

#include <gtkmm/treeview.h>
#include <gtkmm/treeiter.h>
#include <gtkmm/treepath.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/treemodelcolumn.h>
#include <gtkmm/liststore.h>
#include <gtkmm/progressbar.h>

#include "../comum/Rotinas.h"
#include "../objetos/Diretorio.h"
#include "../objetos/Extensao.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosgui {

class Tabela : public Gtk::TreeView
{

private:
	struct ColRecTabela : public Gtk::TreeModel::ColumnRecord {
	public:
		Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf>> coluna0;
		Gtk::TreeModelColumn<Glib::ustring> coluna1;
		Gtk::TreeModelColumn<Glib::ustring> coluna2;
		Gtk::TreeModelColumn<Glib::ustring> coluna3;
		Gtk::TreeModelColumn<Glib::ustring> coluna4;
		Gtk::TreeModelColumn<Glib::ustring> coluna5;
		Gtk::TreeModelColumn<Glib::ustring> coluna6;
		Gtk::TreeModelColumn<Glib::ustring> coluna7;

		ColRecTabela() {
			add(coluna0);
			add(coluna1);
			add(coluna2);
			add(coluna3);
			add(coluna4);
			add(coluna5);
			add(coluna6);
			add(coluna7);
		}
	};

	bool bTabelaDir;
	Gtk::TreeViewColumn *colunaTamanho;
	Gtk::TreeViewColumn *colunaTipo;
	Gtk::TreeViewColumn *colunaModificado;
	Gtk::TreeViewColumn *colunaAtributos;
	Gtk::TreeViewColumn *colunaCaminho;
	Gtk::TreeViewColumn *colunaAba;

public:
	Gtk::TreeViewColumn *colunaNome;
	ColRecTabela modeloTabela;
	Glib::RefPtr<Gtk::ListStore> getStore();

	Tabela(bool bTabelaDir);
	virtual ~Tabela();

	void limpar();
	void adicionaItem(Diretorio dir, const std::vector<Extensao> &listaExtensao);
	void carregar(const std::vector<Diretorio> &listaDir,
		const std::vector<Extensao> &listaExtensao, Gtk::ProgressBar* barraProgresso);
	Diretorio getLinhaSelecionada();
	Gtk::TreePath encontrarCaminhoPorNome(const Glib::ustring &nome);

};

}
}

#endif
