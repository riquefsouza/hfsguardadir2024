#ifndef IMPORTARBO_H
#define IMPORTARBO_H

#include <QList>
#include "hfsguardadir/objetos/Importar.h"
#include "hfsguardadir/objetos/Extensao.h"
#include "hfsguardadir/objetos/Diretorio.h"
#include "hfsguardadir/objetos/DiretorioOrdem.h"
#include "hfsguardadir/comum/Rotinas.h"

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
            DiretorioOrdem *dirOrdem, QList<Diretorio> *listaDiretorio,
            IProgressoLog progressoLog);
    void ImportacaoCompleta(Importar importar, DiretorioOrdem *dirOrdem,
                            IProgressoLog progressoLog);
};

}
}

#endif // IMPORTARBO_H
