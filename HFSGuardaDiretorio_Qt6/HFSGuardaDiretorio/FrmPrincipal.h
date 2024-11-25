#ifndef FRMPRINCIPAL_H
#define FRMPRINCIPAL_H

#include <QMainWindow>
#include <QSplitter>
#include <QTableView>
#include <QTreeView>
#include <QPushButton>
#include <QProgressBar>
#include <QLineEdit>
#include <QLabel>
#include <QStandardItemModel>
#include <QtSql>

#include "hfsguardadir/objetosgui/Arvore.h"
#include "hfsguardadir/objetosgui/Tabela.h"
#include "hfsguardadir/catalogador/Catalogador.h"
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::comum;
using namespace hfsguardadir::objetosgui;
using namespace hfsguardadir::catalogador;

QT_BEGIN_NAMESPACE
namespace Ui {
class FrmPrincipal;
}
QT_END_NAMESPACE

class FrmPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    explicit FrmPrincipal(QWidget *parent = 0);
    ~FrmPrincipal();

    QTabWidget *tabPanel;
    QLabel *barraStatus1;
    QLabel *barraStatus2;
    QProgressBar *pb;
    QSplitter *spPesquisa;
    QLineEdit *edtPesquisa;
    Tabela *tabelaPesquisa;

private:    
	Ui::FrmPrincipal *ui;

	QAction *actionInformacoesDiretorioArquivo;
	QAction *actionExcluirDiretorioSelecionado;

    QWidget *panelCentral;
    QWidget *panelTopo;    
    QPushButton *btnImportarDiretorio;
    QPushButton *btnPesquisa;

    QSqlDatabase dbConexao;

	static void ProgressoLog(Progresso progresso);
		
private slots:
    void actionIncluirNovaAbaTriggered();
    void actionAlterarNomeAbaAtivaTriggered();
    void actionExcluirAbaAtivaTriggered();
    void actionImportarDiretorioTriggered();
    void actionImportarSubDiretoriosTriggered();
    void actionCompararDiretoriosTriggered();
    void actionCadastrarExtensaoArquivoTriggered();
    void actionExpandirDiretoriosTriggered();
    void actionColapsarDiretoriosTriggered();
    void actionTXTTriggered();
    void actionCSVTriggered();
    void actionHTMLTriggered();
    void actionXMLTriggered();
    void actionSQLTriggered();
    void actionImportarDiretoriosViaXMLTriggered();
    void actionGravarLogImportacaoTriggered();
    void actionMostrarOcultarArvoreDirAbaAtivaTriggered();
    void actionMostrarOcultarListaItensPesquisadosTriggered();
    void actionSobreCatalogadorTriggered();
    void btnImportarDiretorioClicked();
    void btnPesquisaClicked();
    void tabTabBarClicked();
	void tabelaPesquisaClicked(const QModelIndex & mi);

	void arvoreExpanded(const QModelIndex & mi);
	void arvoreCollapsed(const QModelIndex & mi);
	void arvorePressed(const QModelIndex & mi);
	void tabelaDoubleClicked(const QModelIndex & mi);

	void contextMenu(const QPoint &pos);

	void actionInformacoesDiretorioArquivoTriggered();
	void actionExcluirDiretorioSelecionadoTriggered();

};

extern FrmPrincipal *frmPrincipal;

#endif // FRMPRINCIPAL_H
