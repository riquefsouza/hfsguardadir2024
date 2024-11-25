#include "resource.h"
#include "hfsguardadir\objetosgui\Arvore.h"

#include <iostream>

namespace hfsguardadir {

namespace objetosgui {

Arvore::Arvore(FXComposite* p): FXTreeList(p)
{
}

Arvore::Arvore(FXComposite* p, FXObject* tgt, FXSelector sel, FXuint opts): FXTreeList(p, tgt, sel, opts)
{
}

Arvore::~Arvore()
{
}

void Arvore::limpar() {
	this->clearItems();
}

void Arvore::expandirTodos() {
	/*
	FXTreeItem* item;

	for (item = this->getFirstItem(); item != this->getLastItem(); ++item) {
		//this->expandTree(item);
		std::cerr << item->getText().text() << std::endl;
	}
	
	for (unsigned int i = 0; i < this->getNumItems(); i++) {
		item = this->getItemAt(i, 0);
		
		std::cerr << item->getText().text() << std::endl;
	}
	*/
}

void Arvore::colapsarTodos() {
	this->collapseTree(NULL);
}

void Arvore::selecionarPrimeiroItem() {	
	FXTreeItem* item = this->getFirstItem();

	this->selectItem(item);
	this->openItem(item);
}

FXTreeItem* Arvore::encontrarCaminho(FXTreeItem* pai,
	const std::vector<std::string> &nomes, int nivel) {
	FXTreeItem* filho;
	std::string valor, nome;
	size_t ntamlista = nomes.size();

	//this->findItem

	for (filho = pai->getFirst(); filho != pai->getLast(); ++filho){
		valor = filho->getText().text();

		nome = nomes.at(nivel);

		if (valor == nome) {

			if (nivel == (ntamlista - 1)) {
				return filho;
			}

			if (filho->getNumChildren() > 0) {
				return encontrarCaminho(filho, nomes, nivel + 1);
			}
			else {
				return filho;
			}
		}
	}

	return pai;

}

FXTreeItem* Arvore::encontrarCaminhoPorNome(const std::vector<std::string> &nomes) {
	FXTreeItem* filho;
	int nivel = 0;
	std::string valor, nome;
	size_t ntamlista = nomes.size();

	for (filho = this->getFirstItem(); filho != this->getLastItem(); ++filho) {
		valor = filho->getText().text();

		nome = nomes.at(nivel);

		if (valor == nome) {

			if (nivel == (ntamlista - 1)) {
				break;
			}

			if (filho->getNumChildren() > 0) {
				filho = encontrarCaminho(filho, nomes, nivel + 1);
				break;
			}

		}
	}

	return filho;
}

void Arvore::expandirSelecionado() {
	this->expandTree(this->getCurrentItem());
}

}
}
