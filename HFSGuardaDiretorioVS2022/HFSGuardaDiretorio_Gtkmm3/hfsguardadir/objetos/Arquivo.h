#ifndef ARQUIVO_H
#define ARQUIVO_H

#ifndef PTRDIFF_MAX
#define PTRDIFF_MAX (std::numeric_limits<ptrdiff_t>::max())
#endif

#include <glibmm/ustring.h>
#include "hfsguardadir/comum/DateTime.h"

using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetos {

class Arquivo
{
private:
    Glib::ustring nome;
	unsigned long long tamanho;
    //DateTime* modificado;
	GDateTime* modificado;
    Glib::ustring atributos;

public:
    Arquivo();
    Arquivo(const Glib::ustring &nome, const unsigned long long &tamanho, 
		GDateTime* modificado, const Glib::ustring &atributos);
    Glib::ustring &getNome();
    void setNome(const Glib::ustring &nome);
	unsigned long long &getTamanho();
    void setTamanho(const unsigned long long &tamanho);
	GDateTime* getModificado();
    void setModificado(GDateTime* modificado);
    Glib::ustring &getAtributos();
    void setAtributos(const Glib::ustring &atributos);
    void limparDados();
    bool equals(Arquivo *obj);
    Glib::ustring &toString();
};

}

}

#endif
