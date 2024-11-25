#ifndef ABA_H
#define ABA_H

#include <string>

namespace hfsguardadir {

namespace objetos {

class Aba
{
private:
    int codigo;
    std::string nome;
    int ordem;

public:
    Aba();
    Aba(int codigo, const std::string &nome, int ordem);
    int getCodigo();
    void setCodigo(int codigo);
    std::string &getNome();
    void setNome(const std::string &nome);
    int getOrdem();
    void setOrdem(int ordem);
    void limparDados();
    bool equals(Aba obj);
    std::string &toString();
};

}

}

#endif // ABA_H
