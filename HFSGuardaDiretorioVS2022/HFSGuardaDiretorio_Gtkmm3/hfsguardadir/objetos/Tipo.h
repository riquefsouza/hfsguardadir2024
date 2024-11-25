#ifndef TIPO_H
#define TIPO_H

#ifndef PTRDIFF_MAX
#define PTRDIFF_MAX (std::numeric_limits<ptrdiff_t>::max())
#endif

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
    Tipo(const char &codigo, const Glib::ustring &nome);
	char &getCodigo();
    void setCodigo(const char &codigo);
    Glib::ustring &getNome();
    void setNome(const Glib::ustring &nome);
    void limparDados();
    bool equals(Tipo *obj);
    Glib::ustring &toString();

};

}
}

#endif // TIPO_H
