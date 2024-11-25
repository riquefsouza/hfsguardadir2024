#include "stdafx.h"
#include "DiretorioOrdem.h"

namespace hfsguardadir {

namespace objetos {

DiretorioOrdem::DiretorioOrdem()
{

}

int DiretorioOrdem::getOrdem() {
    return ordem;
}

void DiretorioOrdem::setOrdem(int ordem) {
    this->ordem = ordem;
}

}

}
