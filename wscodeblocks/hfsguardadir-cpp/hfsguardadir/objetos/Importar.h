#ifndef IMPORTAR_H
#define IMPORTAR_H

#include <string>

namespace hfsguardadir {

namespace objetos {

class Importar
{
private:
    int aba;
    int codDirRaiz;
    std::string rotuloRaiz;
    std::string nomeDirRaiz;
    std::string caminho;

public:
    Importar();
    int getAba();
    void setAba(int aba);
    int getCodDirRaiz();
    void setCodDirRaiz(int codDirRaiz);
    std::string &getRotuloRaiz();
    void setRotuloRaiz(const std::string &rotuloRaiz);
    std::string getNomeDirRaiz();
    void setNomeDirRaiz(const std::string &nomeDirRaiz);
    std::string &getCaminho();
    void setCaminho(const std::string &caminho);

};

}
}

#endif // IMPORTAR_H
