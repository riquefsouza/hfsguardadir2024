#ifndef ARVORE_H
#define ARVORE_H

#include <QTreeView>
#include <QStandardItem>
#include <QStandardItemModel>
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosgui {

class Arvore: public QTreeView
{
public:
    Arvore(QWidget *parent);
    ~Arvore();

	QStandardItem* encontrarCaminho(QStringList nomes, int Nivel, QStandardItem *item);
    void encontrarCaminhoPorNome(QStringList nomes);
	bool isSelecionado();
	void selecioneLinha(int linha);
	void limpar();

};

}
}

#endif // ARVORE_H
