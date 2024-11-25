#include "RotuloRaiz.h"

namespace hfsguardadir {

namespace catalogador {

RotuloRaiz::RotuloRaiz()
{

}

Glib::ustring RotuloRaiz::getRotulo() {
    return rotulo;
}

void RotuloRaiz::setRotulo(const Glib::ustring rotulo) {
    this->rotulo = rotulo;
}

}
}
