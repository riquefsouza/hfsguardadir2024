#include "Tabela.h"

#include <QStandardItemModel>
#include <QStandardItem>
#include <QHeaderView>
#include <QMessageBox>

#include "hfsguardadir/objetosbo/ExtensaoBO.h"

using namespace hfsguardadir::objetosbo;

namespace hfsguardadir {

namespace objetosgui {

Tabela::Tabela(QWidget *parent, bool bTabelaDir):
    QTableView(parent)
{
	this->bTabelaDir = bTabelaDir;
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->verticalHeader()->setVisible(false);
    this->verticalHeader()->sectionResizeMode(QHeaderView::Fixed);
    this->verticalHeader()->setDefaultSectionSize(18);
    this->setSortingEnabled(true);
    //this->sortByColumn(0, Qt::AscendingOrder);
    //this->reset();

	modeloColunas(true);

	//connect(this, SIGNAL(doubleClicked(QModelIndex)),
		//parent, SLOT(tabelaDoubleClicked(QModelIndex)));
}

Tabela::~Tabela() 
{
	//disconnect(this, SIGNAL(doubleClicked(QModelIndex)),
		//parent(), SLOT(tabelaDoubleClicked(QModelIndex)));
}

int Tabela::encontrarLinha(const QString &nome) {
	QString slinha;
	int nlinha = 0;
	QStandardItem *item;
	QStandardItemModel *modelo = (QStandardItemModel *) this->model();

	for (int i = 0; i < modelo->rowCount(); i++) {
		item = modelo->item(i);
		slinha = item->text();
		if (slinha == nome) {
			nlinha = i;
			break;
		}
	}
	return nlinha;
}

Diretorio* Tabela::getLinhaSelecionada() {
	Diretorio *dir = NULL;
	Aba aba;
	Tipo tipo;
	QItemSelectionModel *selecao = this->selectionModel();

	if (selecao->hasSelection()) {
		dir = new Diretorio();
		dir->setNome(selecao->selectedRows(0).at(0).data(Qt::DisplayRole).toString());
		dir->setTamanhoFormatado(selecao->selectedRows(1).at(0).data(Qt::DisplayRole).toString());
		tipo.setNome(selecao->selectedRows(2).at(0).data(Qt::DisplayRole).toString());
		dir->setTipo(tipo);
		dir->setModificadoFormatado(selecao->selectedRows(3).at(0).data(Qt::DisplayRole).toString());
		dir->setAtributos(selecao->selectedRows(4).at(0).data(Qt::DisplayRole).toString());
		dir->setCaminho(selecao->selectedRows(5).at(0).data(Qt::DisplayRole).toString());
		if (bTabelaDir) {
			aba.setNome(selecao->selectedRows(6).at(0).data(Qt::DisplayRole).toString());
			dir->setAba(aba);
		}
	}

	return dir;
}

void Tabela::modeloColunas(bool bConstruir) {

	if (bTabelaDir) {
		if (bConstruir) {
			modelo = new QStandardItemModel(0, 6, this);
		}
		modelo->setHorizontalHeaderItem(0, new QStandardItem("Nome"));
		modelo->setHorizontalHeaderItem(1, new QStandardItem("Tamanho"));
		modelo->setHorizontalHeaderItem(2, new QStandardItem("Tipo"));
		modelo->setHorizontalHeaderItem(3, new QStandardItem("Modificado"));
		modelo->setHorizontalHeaderItem(4, new QStandardItem("Atributos"));
		modelo->setHorizontalHeaderItem(5, new QStandardItem("Caminho"));

		this->setModel(modelo);
		this->setColumnWidth(0, 300);
		this->setColumnWidth(1, 100);
		this->setColumnWidth(2, 70);
		this->setColumnWidth(3, 120);
		this->setColumnWidth(4, 90);
		this->setColumnWidth(5, 500);
	}
	else {
		if (bConstruir) {
			modelo = new QStandardItemModel(0, 9, this);
		}
		modelo->setHorizontalHeaderItem(0, new QStandardItem("Nome"));
		modelo->setHorizontalHeaderItem(1, new QStandardItem("Tamanho"));
		modelo->setHorizontalHeaderItem(2, new QStandardItem("Tipo"));
		modelo->setHorizontalHeaderItem(3, new QStandardItem("Modificado"));
		modelo->setHorizontalHeaderItem(4, new QStandardItem("Atributos"));
		modelo->setHorizontalHeaderItem(5, new QStandardItem("Caminho"));
		modelo->setHorizontalHeaderItem(6, new QStandardItem("Aba"));
		modelo->setHorizontalHeaderItem(7, new QStandardItem("Número Aba"));
		modelo->setHorizontalHeaderItem(8, new QStandardItem("Nome do Pai"));

		this->setModel(modelo);
		this->setColumnHidden(7, true);
		this->setColumnHidden(8, true);
		this->setColumnWidth(0, 300);
		this->setColumnWidth(1, 100);
		this->setColumnWidth(2, 70);
		this->setColumnWidth(3, 120);
		this->setColumnWidth(4, 90);
		this->setColumnWidth(5, 500);
		this->setColumnWidth(6, 70);
		this->setColumnWidth(7, 70);
		this->setColumnWidth(8, 70);
	}
}

void Tabela::modeloTabela(QList<Diretorio> diretorios,
	QList<Extensao> extensoes,
	QProgressBar *barraProgresso) {
	QList<QStandardItem *> colunas;
	QIcon icone;

	modelo->clear();
	modeloColunas(false);

	barraProgresso->setMinimum(0);
	barraProgresso->setMaximum(diretorios.size());
	barraProgresso->setValue(0);
	
	foreach (Diretorio dir, diretorios) {		
		icone = getIconePorExtensao(extensoes, dir.getNome(), dir.getTipo().getNome());

		if (dir.getTipo().getCodigo() == 'D') {
			colunas.append(new QStandardItem(icone, dir.getNome()));
			colunas.append(new QStandardItem(("")));
		}
		else {
			colunas.append(new QStandardItem(icone, dir.getNome()));
			colunas.append(new QStandardItem(dir.getTamanhoFormatado()));
		}
		colunas.append(new QStandardItem(dir.getTipo().getNome()));
		colunas.append(new QStandardItem(dir.getModificadoFormatado()));
		colunas.append(new QStandardItem(dir.getAtributos()));
		colunas.append(new QStandardItem(dir.getCaminho()));

		if (!bTabelaDir) {
			colunas.append(new QStandardItem(dir.getAba().getNome()));
		}

		modelo->appendRow(colunas);

		barraProgresso->setValue(barraProgresso->value() + 1);

		colunas.clear();
	}
	barraProgresso->setValue(0);

}

bool Tabela::isSelecionado() {
	QStandardItemModel *modelo = (QStandardItemModel*)this->model();
	QItemSelectionModel *selecao = (QItemSelectionModel*)this->selectionModel();

	if (modelo->rowCount() > 1) {
		return (selecao->hasSelection());
	}

	return false;
}

void Tabela::selecioneLinha(int linha) {
	QStandardItemModel *modelo = (QStandardItemModel*)this->model();

	if (isSelecionado()) {
		setCurrentIndex(modelo->item(linha)->index());
	}
}

void Tabela::limpar() {
	modelo->clear();
	modeloColunas(false);
}

QIcon Tabela::getIconePorExtensao(QList<Extensao> extensoes, 
	const QString &nome, const QString &tipo) {

	QString ext = nome.mid(nome.lastIndexOf('.') + 1);
	Extensao extensao = ExtensaoBO::getInstancia()->
		pegaExtensaoPorNome(extensoes, ext, tipo);
	QPixmap pixmap = Rotinas::QByteArrayToQPixmap(
		extensao.getBmp16(), Rotinas::EXTENSAO_BMP);
	return QIcon(pixmap);
}

}
}
