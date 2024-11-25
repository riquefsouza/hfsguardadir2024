#include <iostream>
#include <fstream>

//#include "FrmPrincipal.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/catalogador/Catalogador.h"
#include "hfsguardadir/objetosdao/AbaDAO.h"

using namespace hfsguardadir::comum;
using namespace hfsguardadir::catalogador;
using namespace hfsguardadir::objetosdao;

void testarDAO() {
	std::string sApp = Rotinas::AppDirName();
	sApp += "GuardaDir.db";
	Rotinas::getInstancia()->BancoConectar(sApp);

	std::vector<Aba> lista = AbaDAO::getInstancia()->consultarTudo(NULL);

	size_t tamlista = lista.size();
	Aba aba1;
	char* saida = Rotinas::NewStr();
	if (tamlista > 0) {
		for (unsigned int i = 0; i < tamlista; i++) {
			aba1 = lista.at(i);

			std::snprintf(saida, TAM_MAX_STR, "sDir: [%s]\n", aba1.getNome().c_str());
			//OutputDebugString(Rotinas::CharToWChar(saida));
			std::cout << saida << std::endl;
		}
	}

	lista.clear();

	Aba aba;
	aba.setCodigo(3);
	aba.setNome("DISCO3");
	aba.setOrdem(3);
	AbaDAO::getInstancia()->incluir(aba);

	Rotinas::getInstancia()->BancoDesconectar();
}

int main(int argc, char* argv[]) {
	Rotinas::setArgumentos(argc, argv);

	testarDAO();
	//Rotinas::testar();

	//Catalogador::iniciarSistema();
	//FrmPrincipal::Mostrar();

	return 0;
}
