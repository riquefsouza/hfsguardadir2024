#ifndef TIPO_H
#define TIPO_H

#include <glibmm/ustring.h>

namespace hfsguardadir {

namespace objetos {

class Tipo
{
private:
	char codigo;
    Glib::ustring nome;

public:
    Tipo();
    Tipo(const char codigo, const Glib::ustring nome);
	char getCodigo();
    void setCodigo(const char codigo);
    Glib::ustring getNome();
    void setNome(const Glib::ustring nome);
    void limparDados();
    bool equals(Tipo obj);
    Glib::ustring toString();

};

}
}

#endif // TIPO_H
