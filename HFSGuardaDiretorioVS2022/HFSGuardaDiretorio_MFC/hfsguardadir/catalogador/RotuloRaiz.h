#ifndef ROTULORAIZ_H
#define ROTULORAIZ_H

#pragma once

namespace hfsguardadir {

namespace catalogador {

class RotuloRaiz
{
private:
    CString rotulo;

public:
    RotuloRaiz();
    CString getRotulo();
    void setRotulo(const CString &rotulo);
};

}
}

#endif // ROTULORAIZ_H
