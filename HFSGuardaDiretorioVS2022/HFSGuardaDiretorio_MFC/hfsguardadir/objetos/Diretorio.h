#ifndef DIRETORIO_H
#define DIRETORIO_H

#pragma once

#include "Arquivo.h"
#include "Aba.h"
#include "Tipo.h"

namespace hfsguardadir {

namespace objetos {

class Diretorio : public Arquivo
{
private:
    Aba aba;
    int codigo;
    int ordem;
    int codDirPai;
    Tipo tipo;
    CString caminho;
    CString nomePai;
    CString caminhoPai;
    CString tamanhoFormatado;
    CString modificadoFormatado;
    CString caminhoOriginal;

public:
    Diretorio();
    Aba getAba();
    void setAba(Aba aba);
    int getCodigo();
    void setCodigo(int codigo);
    int getOrdem();
    void setOrdem(int ordem);
    int getCodDirPai();
    void setCodDirPai(int codDirPai);
    Tipo getTipo();
    void setTipo(Tipo tipo);
    CString &getCaminho();
    void setCaminho(const CString &caminho);
    CString &getNomePai();
    void setNomePai(const CString &nomePai);
    CString &getCaminhoPai();
    void setCaminhoPai(const CString &caminhoPai);
    CString &getTamanhoFormatado();
    void setTamanhoFormatado(const CString &tamanhoFormatado);
    CString &getModificadoFormatado();
    void setModificadoFormatado(const CString &modificadoFormatado);
    CString &getCaminhoOriginal();
    void setCaminhoOriginal(const CString &caminhoOriginal);
    void limparDados();
    bool equals(Diretorio *obj);
    CString &toString();

};

}
}

#endif // DIRETORIO_H
