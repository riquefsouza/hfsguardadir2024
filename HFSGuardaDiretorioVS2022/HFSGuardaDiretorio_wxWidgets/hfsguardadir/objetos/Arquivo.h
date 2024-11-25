#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <wx/string.h>
#include <wx/datetime.h>

namespace hfsguardadir {

namespace objetos {

class Arquivo
{
private:
    wxString nome;
	wxULongLong tamanho;
    wxDateTime modificado;
    wxString atributos;

public:
    Arquivo();
    Arquivo(const wxString &nome, const wxULongLong &tamanho, const wxDateTime &modificado, const wxString &atributos);
    wxString &getNome();
    void setNome(const wxString &nome);
	wxULongLong &getTamanho();
    void setTamanho(const wxULongLong &tamanho);
    wxDateTime &getModificado();
    void setModificado(const wxDateTime &modificado);
    wxString &getAtributos();
    void setAtributos(const wxString &atributos);
    void limparDados();
    bool equals(Arquivo *obj);
    wxString &toString();
};

}

}

#endif // ARQUIVO_H
