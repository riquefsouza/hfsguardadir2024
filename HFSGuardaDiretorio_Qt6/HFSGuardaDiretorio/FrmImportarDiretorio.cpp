#include "FrmImportarDiretorio.h"
#include "ui_FrmImportarDiretorio.h"

#include <QVBoxLayout>
#include <QMessageBox>

#include "hfsguardadir/objetosdao/AbaDAO.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/catalogador/Catalogador.h"
#include "hfsguardadir/objetosbo/ImportarBO.h"
#include "hfsguardadir/objetosbo/DiretorioBO.h"
#include "hfsguardadir/objetosgui/Dialogo.h"

using namespace hfsguardadir::objetosdao;
using namespace hfsguardadir::comum;
using namespace hfsguardadir::catalogador;
using namespace hfsguardadir::objetosbo;
using namespace hfsguardadir::objetosgui;

FrmImportarDiretorio *frmImportarDiretorio;

FrmImportarDiretorio::FrmImportarDiretorio(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmImportarDiretorio)
{
    ui->setupUi(this);

    setModal(true);
    setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    setMinimumSize(685,462);
    setMaximumSize(minimumSize());
    setWindowFlags(windowFlags() & (~Qt::WindowContextHelpButtonHint));

	setFocusPolicy(Qt::StrongFocus);
	setAttribute(Qt::WA_QuitOnClose, true);

    QVBoxLayout *vbox = new QVBoxLayout();

    memoImportaDir = new QListWidget();
    memoImportaDir->setEditTriggers(QAbstractItemView::NoEditTriggers);
    memoImportaDir->setSelectionBehavior(QAbstractItemView::SelectRows);
    memoImportaDir->setSelectionMode(QAbstractItemView::SingleSelection);
	memoImportaDir->setSelectionRectVisible(true);
	
    pbImportar = new QProgressBar();
    pbImportar->setTextVisible(false);

    barraStatus1 = new QLabel("Total de linhas sendo processadas:");
    barraStatus1->setMinimumSize(200, barraStatus1->minimumHeight());

    barraStatus2 = new QLabel("");

    barraStatus = new QStatusBar();
    barraStatus->setSizeGripEnabled(false);
    barraStatus->addWidget(barraStatus1);
    barraStatus->addWidget(barraStatus2, 1);

    //vbox->setMargin(0);
    vbox->addWidget(memoImportaDir);
    vbox->addWidget(pbImportar);
    vbox->addWidget(barraStatus);

    setLayout(vbox);
}

FrmImportarDiretorio::~FrmImportarDiretorio()
{
    delete ui;
}

void FrmImportarDiretorio::changeEvent(QEvent *ev) {
	if (ev->type() == QEvent::ActivationChange && this->isActiveWindow()) {
		iniciarImportacao();
	}
}

void FrmImportarDiretorio::iniciarImportacao()
{
	QString sLog;
	QStringList log;
	QListWidgetItem *listItem;

	foreach (Importar importar, listaImportar) {
		catalogador->diretorioOrdem.setOrdem(1);

		if (!bSubDiretorio) {
			setCursor(Qt::WaitCursor);

			ImportarBO::getInstancia()->ImportacaoCompleta(importar,
                    &catalogador->diretorioOrdem, ProgressoLog);

			setCursor(Qt::ArrowCursor);
		}
		else {
			if (!DiretorioBO::getInstancia()->verificaCodDir(importar.getAba(),
				importar.getRotuloRaiz(), catalogador->listaDiretorioPai)) {
				setCursor(Qt::WaitCursor);

				ImportarBO::getInstancia()->ImportacaoCompleta(importar,
                        &catalogador->diretorioOrdem, ProgressoLog);

				setCursor(Qt::ArrowCursor);
			}
			else {
				Dialogo::mensagemInfo(this,
					"FrmImportarDiretorio.DiretorioExisteCatalogo");
			}
		}
	}

	if (catalogador->bGravarLogImportacao) {
		if (memoImportaDir->count() > 0) {
			sLog = qApp->applicationDirPath() + Rotinas::BARRA_INVERTIDA
				+ Rotinas::formataDate(Rotinas::FORMATO_DHARQUIVO, QDateTime::currentDateTime())
				+ "_Importacao.log";

			for (int i = 0; i < memoImportaDir->count(); i++)
			{
				listItem = memoImportaDir->item(i);
				log.append(listItem->text());
			}
			Rotinas::SListSaveToFile(log, sLog);
		}
	}

	this->close();
}

void FrmImportarDiretorio::ProgressoLog(Progresso progresso)
{
    if (frmImportarDiretorio!=NULL) {
        if (progresso.posicao == 0) {
           frmImportarDiretorio->pbImportar->setMinimum(progresso.minimo);
           frmImportarDiretorio->pbImportar->setMaximum(progresso.maximo);
        }

        frmImportarDiretorio->pbImportar->setValue(progresso.posicao);
		
		if (!progresso.log.isEmpty()) {			
			int pos = frmImportarDiretorio->memoImportaDir->count();
			frmImportarDiretorio->memoImportaDir->addItem(progresso.log);		
			//frmImportarDiretorio->memoImportaDir->setItemSelected(frmImportarDiretorio->memoImportaDir->item(pos), true);
			frmImportarDiretorio->memoImportaDir->scrollToBottom();
			frmImportarDiretorio->barraStatus2->setText(QString::number(pos));
			qApp->processEvents();
		}

    }

}
