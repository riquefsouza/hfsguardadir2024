#ifndef FRMIMPORTARDIRETORIO_H
#define FRMIMPORTARDIRETORIO_H

#include <QDialog>
#include <QLabel>
#include <QStatusBar>
#include <QProgressBar>
#include <QListWidget>

#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/objetos/Diretorio.h"
#include "hfsguardadir/objetos/Importar.h"

using namespace hfsguardadir::comum;
using namespace hfsguardadir::objetos;

QT_BEGIN_NAMESPACE
namespace Ui {
class FrmImportarDiretorio;
}
QT_END_NAMESPACE

class FrmImportarDiretorio : public QDialog
{
    Q_OBJECT

public:
    bool bSubDiretorio;
	QList<Importar> listaImportar;
	QList<Diretorio> listaDiretorio;
	
	QListWidget *memoImportaDir;
	QLabel *barraStatus2;

    explicit FrmImportarDiretorio(QWidget *parent = 0);
    ~FrmImportarDiretorio();

private:
    Ui::FrmImportarDiretorio *ui;

    QProgressBar *pbImportar;
    QStatusBar *barraStatus;
    QLabel *barraStatus1;
    
    static void ProgressoLog(Progresso progresso);
	void iniciarImportacao();

protected:
	void changeEvent(QEvent *ev);

};

extern FrmImportarDiretorio *frmImportarDiretorio;

#endif // FRMIMPORTARDIRETORIO_H
