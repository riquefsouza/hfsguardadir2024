#ifndef ARQUIVO_H
#define ARQUIVO_H

#pragma once

namespace hfsguardadir {

namespace objetos {

class Arquivo
{
private:
    CString nome;
    long long tamanho;
    CTime modificado;
    CString atributos;

public:
    Arquivo();
    Arquivo(const CString &nome, long long tamanho, const CTime &modificado, const CString &atributos);
    CString &getNome();
    void setNome(const CString &nome);
    long long getTamanho();
    void setTamanho(long long tamanho);
    CTime &getModificado();
    void setModificado(const CTime &modificado);
    CString &getAtributos();
    void setAtributos(const CString &atributos);
    void limparDados();
    bool equals(Arquivo *obj);
    CString &toString();

};

}

}

#endif // ARQUIVO_H
