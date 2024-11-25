#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <string>
#include "hfsguardadir/comum/DateTime.h"

using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetos {

class Arquivo
{
private:
    std::string nome;
	unsigned long long tamanho;
    DateTime modificado;
    std::string atributos;

public:
    Arquivo();
    Arquivo(const std::string &nome, const unsigned long long &tamanho, 
		DateTime modificado, const std::string &atributos);
    std::string &getNome();
    void setNome(const std::string &nome);
	unsigned long long &getTamanho();
    void setTamanho(const unsigned long long &tamanho);
	DateTime getModificado();
    void setModificado(DateTime modificado);
    std::string &getAtributos();
    void setAtributos(const std::string &atributos);
    void limparDados();
    bool equals(Arquivo *obj);
    std::string &toString();
};

}

}

#endif // ARQUIVO_H
