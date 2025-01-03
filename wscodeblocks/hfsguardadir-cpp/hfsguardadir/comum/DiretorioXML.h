#ifndef DIRETORIOXML_H
#define DIRETORIOXML_H

#include "../objetos/Diretorio.h"

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
