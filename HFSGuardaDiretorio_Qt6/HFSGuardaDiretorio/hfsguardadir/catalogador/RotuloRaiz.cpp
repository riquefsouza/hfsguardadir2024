#include "RotuloRaiz.h"

namespace hfsguardadir {

namespace catalogador {

RotuloRaiz::RotuloRaiz()
{

}

QString RotuloRaiz::getRotulo() {
    return rotulo;
}

void RotuloRaiz::setRotulo(const QString &rotulo) {
    this->rotulo = rotulo;
}

}
}
