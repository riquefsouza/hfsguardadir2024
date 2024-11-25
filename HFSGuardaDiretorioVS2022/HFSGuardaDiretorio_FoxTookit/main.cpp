#include "resource.h"
#include "FrmPrincipal.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/catalogador/Catalogador.h"

using namespace hfsguardadir::comum;
using namespace hfsguardadir::catalogador;

int main(int argc, char* argv[]) {
	Rotinas::setArgumentos(argc, argv);

	FXApp HFSGuardaDiretorioApp("HFSGuardaDiretorio",
		"HFSGuardaDiretorio 2.0 - Catalogador de Diretórios");
	HFSGuardaDiretorioApp.init(argc, argv);

	Catalogador::iniciarSistema();
	frmPrincipal = new FrmPrincipal(&HFSGuardaDiretorioApp);

	HFSGuardaDiretorioApp.create();
	
	FrmPrincipal::Mostrar(&HFSGuardaDiretorioApp);

	return HFSGuardaDiretorioApp.run();
}
