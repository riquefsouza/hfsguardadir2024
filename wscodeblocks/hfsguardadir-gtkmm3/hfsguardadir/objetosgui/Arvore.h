#ifndef ARVORE_H
#define ARVORE_H

#include "../comum/Rotinas.h"

#include <gtkmm/treeview.h>
#include <gtkmm/treeiter.h>
#include <gtkmm/treepath.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/treemodelcolumn.h>
#include <gtkmm/treestore.h>

using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosgui {

class Arvore : public Gtk::TreeView
{
private:
	struct ColRecArvore : public Gtk::TreeModel::ColumnRecord {
	public:
		Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf>> coluna0;
		Gtk::TreeModelColumn<Glib::ustring> coluna1;

		ColRecArvore() {
			add(coluna0);
			add(coluna1);

		}
	};

public:
	ColRecArvore modeloArvore;
	Glib::RefPtr<Gtk::TreeStore> getStore();
	Gtk::TreeViewColumn coluna;

	Arvore();
	virtual ~Arvore();

	void limpar();
	void expandirTodos();
	void colapsarTodos();
	void selecionarPrimeiroItem();
	Gtk::TreeIter encontrarCaminho(Gtk::TreeIter pai, const std::vector<Glib::ustring> &nomes, int nivel);
	Gtk::TreePath encontrarCaminhoPorNome(const std::vector<Glib::ustring> &nomes);
	void expandirSelecionado();

};

}
}

#endif

