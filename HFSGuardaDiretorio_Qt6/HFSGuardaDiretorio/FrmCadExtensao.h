#ifndef FRMCADEXTENSAO_H
#define FRMCADEXTENSAO_H

#include <QDialog>
#include <QMenuBar>
#include <QMenu>
#include <QAbstractButton>
#include <QTableView>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class FrmCadExtensao;
}
QT_END_NAMESPACE

class FrmCadExtensao : public QDialog
{
    Q_OBJECT

public:
    explicit FrmCadExtensao(QWidget *parent = 0);
    ~FrmCadExtensao();

private:
    Ui::FrmCadExtensao *ui;

    QMenuBar *barraMenu;
    QAction *actionIncluirExtensao;
    QAction *actionExcluirExtensao;
    QAction *actionExcluirTodasExtensoes;
    QAction *actionExportarBitmap;
    QAction *actionExportarIcone;
    QAction *actionExportarGIF;
    QAction *actionExportarJPEG;
    QAction *actionExportarPNG;
    QAction *actionExportarTIFF;
    QAction *actionImportarIconesArquivos;
    QAction *actionExtrairIconesArquivos;
	QStandardItemModel *modeloExtensao;
    QTableView *tabelaExtensao;
    QMenu *menuExtensao;
    QMenu *menuExportarTodos;
    QMenu *menuImportarTodos;

	void modeloColunas(bool bConstruir);
	void CarregarExtensoesNaGrid();

private slots:
    void actionIncluirExtensaoTriggered();
    void actionExcluirExtensaoTriggered();
    void actionExcluirTodasExtensoesTriggered();
    void actionExportarBitmapTriggered();
    void actionExportarIconeTriggered();
    void actionExportarGIFTriggered();
    void actionExportarJPEGTriggered();
    void actionExportarPNGTriggered();
    void actionExportarTIFFTriggered();
    void actionImportarIconesArquivosTriggered();
    void actionExtrairIconesArquivosTriggered();

    //void tabelaExtensaoDoubleClicked(const QModelIndex & mi);
    void grupoBotaoClicked(QAbstractButton* botao);

};

#endif // FRMCADEXTENSAO_H
