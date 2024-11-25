#include "stdafx.h"
#include "DiretorioXML.h"

namespace hfsguardadir {

namespace comum {

DiretorioXML::DiretorioXML()
{
    this->diretorio = new Diretorio();
}

Diretorio* DiretorioXML::getDiretorio() {
    return diretorio;
}

void DiretorioXML::setDiretorio(Diretorio *diretorio) {
    this->diretorio = diretorio;
}

}
}
