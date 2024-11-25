#ifndef ABA_H
#define ABA_H

#include <QString>

namespace hfsguardadir {

namespace objetos {

class Aba
{
private:
    int codigo;
    QString nome;
    int ordem;

public:
    Aba();
    Aba(int codigo, const QString &nome, int ordem);
    int getCodigo();
    void setCodigo(int codigo);
    QString &getNome();
    void setNome(const QString &nome);
    int getOrdem();
    void setOrdem(int ordem);
    void limparDados();
    bool equals(Aba obj);
    QString &toString();
};

}

}

#endif // ABA_H
