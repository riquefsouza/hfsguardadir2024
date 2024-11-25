#ifndef TIPO_H
#define TIPO_H

#include <string>

namespace hfsguardadir {

namespace objetos {

class Tipo
{
private:
	char codigo;
    std::string nome;

public:
    Tipo();
    Tipo(const char &codigo, const std::string &nome);
	char &getCodigo();
    void setCodigo(const char &codigo);
    std::string &getNome();
    void setNome(const std::string &nome);
    void limparDados();
    bool equals(Tipo *obj);
    std::string &toString();

};

}
}

#endif
