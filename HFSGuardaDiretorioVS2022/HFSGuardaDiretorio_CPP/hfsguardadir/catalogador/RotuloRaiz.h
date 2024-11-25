#ifndef ROTULORAIZ_H
#define ROTULORAIZ_H

#include <string>

namespace hfsguardadir {

namespace catalogador {

class RotuloRaiz
{
private:
    std::string rotulo;

public:
    RotuloRaiz();
    std::string getRotulo();
    void setRotulo(const std::string &rotulo);
};

}
}

#endif // ROTULORAIZ_H
