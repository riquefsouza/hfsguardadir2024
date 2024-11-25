#ifndef TIPO_H
#define TIPO_H

#include <wx/string.h>

namespace hfsguardadir {

namespace objetos {

class Tipo
{
private:
	wxChar codigo;
    wxString nome;

public:
    Tipo();
    Tipo(const wxChar &codigo, const wxString &nome);
	wxChar &getCodigo();
    void setCodigo(const wxChar &codigo);
    wxString &getNome();
    void setNome(const wxString &nome);
    void limparDados();
    bool equals(Tipo *obj);
    wxString &toString();

};

}
}

#endif // TIPO_H
