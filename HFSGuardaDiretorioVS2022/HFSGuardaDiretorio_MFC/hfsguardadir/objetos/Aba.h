#ifndef ABA_H
#define ABA_H

#pragma once

namespace hfsguardadir {

namespace objetos {

class Aba
{
private:
    int codigo;
    CString nome;
    int ordem;

public:
    Aba();
    Aba(int codigo, const CString &nome, int ordem);
    int getCodigo();
    void setCodigo(int codigo);
    CString &getNome();
    void setNome(const CString &nome);
    int getOrdem();
    void setOrdem(int ordem);
    void limparDados();
    bool equals(Aba *obj);
    CString &toString();
};

}

}

#endif // ABA_H
