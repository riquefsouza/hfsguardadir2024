#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <glibmm/ustring.h>
#include "../comum/DateTime.h"

using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetos {

class Arquivo
{
private:
    Glib::ustring nome;
	unsigned long long tamanho;
    //DateTime* modificado;
	Glib::DateTime modificado;
    Glib::ustring atributos;

public:
    Arquivo();
    Arquivo(const Glib::ustring nome, const unsigned long long tamanho,
		Glib::DateTime modificado, const Glib::ustring atributos);
    Glib::ustring getNome();
    void setNome(const Glib::ustring nome);
	unsigned long long getTamanho();
    void setTamanho(const unsigned long long tamanho);
	Glib::DateTime getModificado();
    void setModificado(Glib::DateTime modificado);
    Glib::ustring getAtributos();
    void setAtributos(const Glib::ustring atributos);
    void limparDados();
    bool equals(Arquivo obj);
    Glib::ustring toString();
};

}

}

#endif // ARQUIVO_H
