#ifndef DIRETORIOXML_H
#define DIRETORIOXML_H

#ifndef PTRDIFF_MAX
#define PTRDIFF_MAX (std::numeric_limits<ptrdiff_t>::max())
#endif

#include "hfsguardadir/objetos/Diretorio.h"

using namespace hfsguardadir::objetos;

namespace hfsguardadir {

namespace comum {

class DiretorioXML
{
private:
    Diretorio *diretorio;

public:
    DiretorioXML();
    Diretorio* getDiretorio();
    void setDiretorio(Diretorio *diretorio);
};

}
}

#endif // DIRETORIOXML_H
