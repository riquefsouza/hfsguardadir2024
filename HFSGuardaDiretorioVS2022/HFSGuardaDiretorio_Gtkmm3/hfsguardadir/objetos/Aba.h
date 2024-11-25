#ifndef ABA_H
#define ABA_H

#ifndef PTRDIFF_MAX
#define PTRDIFF_MAX (std::numeric_limits<ptrdiff_t>::max())
#endif

#include <glibmm/ustring.h>

namespace hfsguardadir {

namespace objetos {

class Aba
{
private:
    int codigo;
    Glib::ustring nome;
    int ordem;

public:
    Aba();
    Aba(int codigo, const Glib::ustring &nome, int ordem);
    int getCodigo();
    void setCodigo(int codigo);
    Glib::ustring &getNome();
    void setNome(const Glib::ustring &nome);
    int getOrdem();
    void setOrdem(int ordem);
    void limparDados();
    bool equals(Aba *obj);
    Glib::ustring &toString();
};

}

}

#endif // ABA_H
