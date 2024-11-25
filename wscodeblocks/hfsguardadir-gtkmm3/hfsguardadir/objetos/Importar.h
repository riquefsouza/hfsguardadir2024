#ifndef IMPORTAR_H
#define IMPORTAR_H

#include <glibmm/ustring.h>

namespace hfsguardadir {

namespace objetos {

class Importar
{
private:
    int aba;
    int codDirRaiz;
    Glib::ustring rotuloRaiz;
    Glib::ustring nomeDirRaiz;
    Glib::ustring caminho;

public:
    Importar();
    int getAba();
    void setAba(int aba);
    int getCodDirRaiz();
    void setCodDirRaiz(int codDirRaiz);
    Glib::ustring getRotuloRaiz();
    void setRotuloRaiz(const Glib::ustring rotuloRaiz);
    Glib::ustring getNomeDirRaiz();
    void setNomeDirRaiz(const Glib::ustring nomeDirRaiz);
    Glib::ustring getCaminho();
    void setCaminho(const Glib::ustring caminho);

};

}
}

#endif // IMPORTAR_H
