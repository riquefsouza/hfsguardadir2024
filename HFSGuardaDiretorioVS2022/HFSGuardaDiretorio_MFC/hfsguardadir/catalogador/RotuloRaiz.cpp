#include "stdafx.h"
#include "RotuloRaiz.h"

namespace hfsguardadir {

namespace catalogador {

RotuloRaiz::RotuloRaiz()
{

}

CString RotuloRaiz::getRotulo() {
    return rotulo;
}

void RotuloRaiz::setRotulo(const CString &rotulo) {
    this->rotulo = rotulo;
}

}
}
