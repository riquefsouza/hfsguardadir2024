#ifndef IMPORTARBO_H
#define IMPORTARBO_H

#include "../objetos/Importar.h"
#include "../objetos/Extensao.h"
#include "../objetos/Diretorio.h"
#include "../objetos/DiretorioOrdem.h"
#include "../comum/Rotinas.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosbo {

class ImportarBO
{
private:
	ImportarBO();
	ImportarBO(ImportarBO const&);
	ImportarBO& operator=(ImportarBO const&);
	static ImportarBO* instancia;

public:
	static ImportarBO* getInstancia();

	void CarregarListaDiretorios(Importar importar,
			DiretorioOrdem *dirOrdem, std::vector<Diretorio> *listaDiretorio,
			IProgressoLog progressoLog);
	void ImportacaoCompleta(Importar importar, DiretorioOrdem *dirOrdem,
		std::vector<Extensao>  &listaExtensao, IProgressoLog progressoLog);

};

}
}

#endif
