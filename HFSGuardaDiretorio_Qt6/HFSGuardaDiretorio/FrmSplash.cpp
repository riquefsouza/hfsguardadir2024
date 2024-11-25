#include "FrmSplash.h"
#include "ui_FrmSplash.h"
#include <QThread>

FrmSplash *frmSplash;

FrmSplash::FrmSplash(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmSplash)
{
    ui->setupUi(this);

	//this->setCursor(Qt::BusyCursor);
	//this->setWindowFlags(Qt::FramelessWindowHint);
	this->setWindowFlags(Qt::SplashScreen);
	//this->layout()->setSizeConstraint(QLayout::SetFixedSize);
	//this->setSizeGripEnabled(false);
	//this->setModal(true);

    //connect(ui->pb, SIGNAL(valueChanged(int)), this, SLOT(progressBarUpdated(int)));
}

FrmSplash::~FrmSplash()
{
    //disconnect(ui->pb, SIGNAL(valueChanged(int)), this, SLOT(progressBarUpdated(int)));

    delete ui;
}

/*
void FrmSplash::progressBarUpdated(int value)
{
	//this->repaint();
	//qApp->processEvents();
}
*/

void FrmSplash::ProgressoLog(Progresso progresso)
{
	if (frmSplash != NULL) {
		if (progresso.posicao == 0) {
			frmSplash->ui->pb->setValue(progresso.minimo);
			frmSplash->ui->pb->setMaximum(progresso.maximo);
		}

		frmSplash->ui->pb->setValue(progresso.posicao);
	}

}
