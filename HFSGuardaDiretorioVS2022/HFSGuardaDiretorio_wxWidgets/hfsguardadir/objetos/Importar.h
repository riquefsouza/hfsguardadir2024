#ifndef IMPORTAR_H
#define IMPORTAR_H

#include <wx/string.h>

namespace hfsguardadir {

namespace objetos {

class Importar
{
private:
    int aba;
    int codDirRaiz;
    wxString rotuloRaiz;
    wxString nomeDirRaiz;
    wxString caminho;

public:
    Importar();
    int getAba();
    void setAba(int aba);
    int getCodDirRaiz();
    void setCodDirRaiz(int codDirRaiz);
    wxString &getRotuloRaiz();
    void setRotuloRaiz(const wxString &rotuloRaiz);
    wxString getNomeDirRaiz();
    void setNomeDirRaiz(const wxString &nomeDirRaiz);
    wxString &getCaminho();
    void setCaminho(const wxString &caminho);

};

}
}

#endif // IMPORTAR_H
