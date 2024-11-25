#ifndef FRMCOMPARARDIRETORIO_H
#define FRMCOMPARARDIRETORIO_H

#include <QDialog>
#include <QTableView>
#include <QPushButton>
#include <QProgressBar>
#include <QLabel>
#include <QGroupBox>
#include <QTreeView>
#include <QComboBox>
#include <QStatusBar>

#include "hfsguardadir/objetos/Diretorio.h"
#include "hfsguardadir/objetosgui/Arvore.h"
#include "hfsguardadir/objetosgui/Tabela.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::objetosgui;

QT_BEGIN_NAMESPACE
namespace Ui {
class FrmCompararDiretorio;
}
QT_END_NAMESPACE

class FrmCompararDiretorio : public QDialog
{
    Q_OBJECT

public:
    explicit FrmCompararDiretorio(QWidget *parent = 0);
    ~FrmCompararDiretorio();

private:
    Ui::FrmCompararDiretorio *ui;

	QList<Diretorio> listaCompara;
	
    QWidget *panelCentral;
    QWidget *panelTopo;
    QPushButton *btnCompararDiretorios;
    QPushButton *btnSalvarLog;
    QProgressBar *pb;
    QGroupBox *panelDiretorio1;
    QComboBox *cmbAba1;
    Arvore *arvoreDiretorio1;
    QGroupBox *panelDiretorio2;
    QComboBox *cmbAba2;
	Arvore *arvoreDiretorio2;
    Tabela *tabelaComparador;
    QLabel *labDiferencasEncontradas;
    QStatusBar *barraStatus;
    QLabel *barraStatus1;
    QLabel *barraStatus2;

	static void ProgressoLog(Progresso progresso);
	void montarArvores();
	void LimparComparacao();
	QString SQLCompara(Aba aba1, Aba aba2, const QString &caminho1,
		const QString &caminho2);
	void Comparar(const QString &sCaminhoDir1, const QString &sCaminhoDir2);

private slots:	
    void btnCompararDiretoriosClicked();
    void btnSalvarLogClicked();
    void cmbAba1CurrentTextChanged();
    void cmbAba2CurrentTextChanged();
    void arvoreDiretorio1Expanded(const QModelIndex & mi);
    void arvoreDiretorio1Collapsed(const QModelIndex & mi);
    void arvoreDiretorio2Expanded(const QModelIndex & mi);
    void arvoreDiretorio2Collapsed(const QModelIndex & mi);
};

extern FrmCompararDiretorio *frmCompararDiretorio;

#endif // FRMCOMPARARDIRETORIO_H
