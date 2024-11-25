#ifndef TIPO_H
#define TIPO_H

#include <QString>

namespace hfsguardadir {

namespace objetos {

class Tipo
{
private:
    char codigo;
    QString nome;

public:
    Tipo();
    Tipo(char codigo, const QString &nome);
    char getCodigo();
    void setCodigo(char codigo);
    QString &getNome();
    void setNome(const QString &nome);
    void limparDados();
    bool equals(Tipo obj);
    QString &toString();

};

}
}

#endif // TIPO_H
