#include "FrmPrincipal.h"
#include <QResource>
#include <QRect>
#include <QSplashScreen>
#include <QThread>
#include <QApplication>
#include "hfsguardadir/comum/Rotinas.h"

//Q_IMPORT_PLUGIN(qgif)
//Q_IMPORT_PLUGIN(qtiff)

using namespace hfsguardadir::comum;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QResource::registerResource("resource.qrc");

	frmPrincipal = new FrmPrincipal();
    Rotinas::CentralizaWidget(frmPrincipal->window());

	catalogador = new Catalogador();

	frmPrincipal->show();
	
	//Rotinas::getInstancia()->testar();

    return a.exec();
}

