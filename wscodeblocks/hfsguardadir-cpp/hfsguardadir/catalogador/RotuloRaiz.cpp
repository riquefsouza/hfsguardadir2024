#include "RotuloRaiz.h"

namespace hfsguardadir {

namespace catalogador {

RotuloRaiz::RotuloRaiz()
{

}

std::string RotuloRaiz::getRotulo() {
    return rotulo;
}

void RotuloRaiz::setRotulo(const std::string &rotulo) {
    this->rotulo = rotulo;
}

}
}
