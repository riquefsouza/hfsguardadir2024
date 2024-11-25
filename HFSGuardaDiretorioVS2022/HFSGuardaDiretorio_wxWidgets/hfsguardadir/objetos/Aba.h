#ifndef ABA_H
#define ABA_H

#include <wx/string.h>

namespace hfsguardadir {

namespace objetos {

class Aba
{
private:
    int codigo;
    wxString nome;
    int ordem;

public:
    Aba();
    Aba(int codigo, const wxString &nome, int ordem);
    int getCodigo();
    void setCodigo(int codigo);
    wxString &getNome();
    void setNome(const wxString &nome);
    int getOrdem();
    void setOrdem(int ordem);
    void limparDados();
    bool equals(Aba *obj);
    wxString &toString();
};

}

}

#endif // ABA_H
