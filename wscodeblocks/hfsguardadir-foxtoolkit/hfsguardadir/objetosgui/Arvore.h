#ifndef ARVORE_H
#define ARVORE_H

#include "resource.h"
#include "hfsguardadir\comum\Rotinas.h"

using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosgui {

class Arvore: public FXTreeList
{		
private:

public:
	Arvore(FXComposite* p);
	Arvore(FXComposite* p, FXObject* tgt, FXSelector sel, FXuint opts);
	virtual ~Arvore();

	void limpar();
	void expandirTodos();
	void colapsarTodos();
	void selecionarPrimeiroItem();
	FXTreeItem* encontrarCaminho(FXTreeItem* pai, const std::vector<std::string>& nomes, int nivel);
	FXTreeItem* encontrarCaminhoPorNome(const std::vector<std::string>& nomes);
	void expandirSelecionado();
	
};

}
}

#endif

