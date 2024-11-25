#ifndef TABELA_H
#define TABELA_H

#include "../comum/Rotinas.h"
#include "../objetos/Diretorio.h"
#include "../objetos/Extensao.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosgui {

class Tabela //: public Gtk::TreeView
{

private:
	bool bTabelaDir;

public:
	Tabela(bool bTabelaDir);
	virtual ~Tabela();
	/*
	void limpar();
	void adicionaItem(Diretorio dir, const std::vector<Extensao> &listaExtensao);
	void carregar(const std::vector<Diretorio> &listaDir,
		const std::vector<Extensao> &listaExtensao, Gtk::ProgressBar* barraProgresso);
	Diretorio getLinhaSelecionada();
	Gtk::TreePath encontrarCaminhoPorNome(const std::string &nome);
	*/
};

}
}

#endif
