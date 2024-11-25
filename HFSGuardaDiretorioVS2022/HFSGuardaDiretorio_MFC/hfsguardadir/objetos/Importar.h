#ifndef IMPORTAR_H
#define IMPORTAR_H

#pragma once

namespace hfsguardadir {

namespace objetos {

class Importar
{
private:
    int aba;
    int codDirRaiz;
    CString rotuloRaiz;
    CString nomeDirRaiz;
    CString caminho;

public:
    Importar();
    int getAba();
    void setAba(int aba);
    int getCodDirRaiz();
    void setCodDirRaiz(int codDirRaiz);
    CString &getRotuloRaiz();
    void setRotuloRaiz(const CString &rotuloRaiz);
    CString getNomeDirRaiz();
    void setNomeDirRaiz(const CString &nomeDirRaiz);
    CString &getCaminho();
    void setCaminho(const CString &caminho);

};

}
}

#endif // IMPORTAR_H
