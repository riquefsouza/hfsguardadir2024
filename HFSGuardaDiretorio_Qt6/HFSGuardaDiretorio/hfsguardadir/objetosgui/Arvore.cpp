#include "Arvore.h"

#include <QStandardItemModel>
#include <QStandardItem>
#include <QHeaderView>
#include <QMessageBox>
#include "hfsguardadir/catalogador/Catalogador.h"

using namespace hfsguardadir::catalogador;

namespace hfsguardadir {

namespace objetosgui {

Arvore::Arvore(QWidget *parent) :
    QTreeView(parent)
{
   this->setEditTriggers(QAbstractItemView::NoEditTriggers);
   this->header()->setVisible(false);
}

Arvore::~Arvore()
{

}

QStandardItem* Arvore::encontrarCaminho(QStringList nomes, int Nivel, QStandardItem *item) {
	QStandardItem *item2, *item3;
	QString nome;

	if (Nivel == (nomes.length() - 1)) {
		return item;
	}

	Nivel++;

	for (int linha = 0; linha < item->rowCount(); linha++)
	{
		if (item->hasChildren()) {
			item2 = item->child(linha);
			nome = nomes.at(Nivel);

			if (nome == item2->text()) {
				item3 = encontrarCaminho(nomes, Nivel, item2);

				if (item3 != NULL) {
					return item3;
				}
			}
		}
	}
	
	return NULL;
}

void Arvore::encontrarCaminhoPorNome(QStringList nomes){
    QStandardItemModel *modelo = (QStandardItemModel*) this->model();
	QStandardItem *item;
	int Nivel = 0;
	QString nome;

	for (int linha = 0; linha < modelo->rowCount(); linha++)
	{
		item = modelo->item(linha);
		nome = nomes.at(Nivel);

		if (nome == item->text()) {
			item = encontrarCaminho(nomes, Nivel, item);
			if (item != NULL) {
				this->setCurrentIndex(item->index());
				break;
			}
		}
	}
}

bool Arvore::isSelecionado() {
	QStandardItemModel *modelo = (QStandardItemModel*)this->model();
	QItemSelectionModel *selecao = (QItemSelectionModel*)this->selectionModel();

	if (modelo->rowCount() > 1) {
		return (selecao->hasSelection());
	}

	return false;
}

void Arvore::selecioneLinha(int linha) {
	QStandardItemModel *modelo = (QStandardItemModel*)this->model();

	if (isSelecionado()) {
		setCurrentIndex(modelo->item(linha)->index());
	}
}

void Arvore::limpar() {
	QStandardItemModel *modelo = (QStandardItemModel*)this->model();
	modelo->clear();
}

}
}
