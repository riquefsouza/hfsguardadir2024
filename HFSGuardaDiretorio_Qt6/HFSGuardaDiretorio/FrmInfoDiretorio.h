#ifndef FRMINFODIRETORIO_H
#define FRMINFODIRETORIO_H

#include <QDialog>
#include <QLabel>
#include <QTableView>
#include <QGroupBox>
#include <QStandardItemModel>
#include "hfsguardadir/objetos/Diretorio.h"

using namespace hfsguardadir::objetos;

QT_BEGIN_NAMESPACE
namespace Ui {
class FrmInfoDiretorio;
}
QT_END_NAMESPACE

class FrmInfoDiretorio : public QDialog
{
    Q_OBJECT

public:
    explicit FrmInfoDiretorio(QWidget *parent = 0);
    ~FrmInfoDiretorio();

	void setDiretorio(Diretorio diretorio);

private:
    Ui::FrmInfoDiretorio *ui;

	QStandardItemModel *modeloInfo;

    QGroupBox *panelLegenda;
    QLabel *labArquivoComum;
    QLabel *labArquivoOculto;
    QLabel *labArquivoSistema;
    QLabel *labLegendaDiretorio;
    QLabel *labVolumeID;
    QLabel *labArquivoSomenteLeitura;
    QTableView *tabelaInfo;

};

#endif // FRMINFODIRETORIO_H
