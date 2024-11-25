#ifndef TIPO_H
#define TIPO_H

#pragma once

namespace hfsguardadir {

namespace objetos {

class Tipo
{
private:
    char codigo;
    CString nome;

public:
    Tipo();
    Tipo(char codigo, const CString &nome);
    char getCodigo();
    void setCodigo(char codigo);
    CString &getNome();
    void setNome(const CString &nome);
    void limparDados();
    bool equals(Tipo *obj);
    CString &toString();

};

}
}

#endif // TIPO_H
