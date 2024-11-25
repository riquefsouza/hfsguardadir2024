#ifndef ARVORE_H
#define ARVORE_H

#include "../comum/Rotinas.h"

using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosgui {

class Arvore //: public Gtk::TreeView
{
private:

public:
	Arvore();
	virtual ~Arvore();
/*
	void limpar();
	void expandirTodos();
	void colapsarTodos();
	void selecionarPrimeiroItem();
	Gtk::TreeIter encontrarCaminho(Gtk::TreeIter pai, const std::vector<std::string> &nomes, int nivel);
	Gtk::TreePath encontrarCaminhoPorNome(const std::vector<std::string> &nomes);
	void expandirSelecionado();
	*/
};

}
}

#endif

