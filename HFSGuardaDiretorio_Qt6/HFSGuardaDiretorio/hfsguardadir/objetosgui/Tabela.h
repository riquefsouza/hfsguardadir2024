#ifndef TABELA_H
#define TABELA_H

#include <QStandardItemModel>
#include <QString>
#include <QProgressBar>
#include <QTableView>
#include "hfsguardadir/objetos/Diretorio.h"
#include "hfsguardadir/objetos/Extensao.h"
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::comum;
using namespace hfsguardadir::objetos;

namespace hfsguardadir {

namespace objetosgui {

class Tabela : public QTableView
{
private:
    bool bTabelaDir;
    //bool sombrearLinhas;
    //bool sombrearColunas;
	QStandardItemModel *modelo;
	void modeloColunas(bool bConstruir);
	QIcon getIconePorExtensao(QList<Extensao> extensoes, 
		const QString &nome, const QString &tipo);

public:
    Tabela(QWidget *parent, bool bTabelaDir);
	~Tabela();
	int encontrarLinha(const QString &nome);
	Diretorio* getLinhaSelecionada();
	void modeloTabela(QList<Diretorio> diretorios, 
		QList<Extensao> extensoes,
		QProgressBar *barraProgresso);
	bool isSelecionado();
	void selecioneLinha(int linha);
	void limpar();
/*
private slots:
	void tabelaDoubleClicked(const QModelIndex & mi);
*/
};

}
}

#endif // TABELA_H
