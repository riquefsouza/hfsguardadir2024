#include "RotuloRaiz.h"

namespace hfsguardadir {

namespace catalogador {

RotuloRaiz::RotuloRaiz()
{

}

wxString RotuloRaiz::getRotulo() {
    return rotulo;
}

void RotuloRaiz::setRotulo(const wxString &rotulo) {
    this->rotulo = rotulo;
}

}
}
