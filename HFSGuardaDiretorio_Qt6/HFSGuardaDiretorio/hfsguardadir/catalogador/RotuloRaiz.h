#ifndef ROTULORAIZ_H
#define ROTULORAIZ_H

#include <QString>

namespace hfsguardadir {

namespace catalogador {

class RotuloRaiz
{
private:
    QString rotulo;

public:
    RotuloRaiz();
    QString getRotulo();
    void setRotulo(const QString &rotulo);
};

}
}

#endif // ROTULORAIZ_H
