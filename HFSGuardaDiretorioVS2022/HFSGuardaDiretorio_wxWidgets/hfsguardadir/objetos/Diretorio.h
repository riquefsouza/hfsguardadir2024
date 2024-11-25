#ifndef DIRETORIO_H
#define DIRETORIO_H

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
    wxString caminho;
    wxString nomePai;
    wxString caminhoPai;
    wxString tamanhoFormatado;
    wxString modificadoFormatado;
    wxString caminhoOriginal;

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
    wxString &getCaminho();
    void setCaminho(const wxString &caminho);
    wxString &getNomePai();
    void setNomePai(const wxString &nomePai);
    wxString &getCaminhoPai();
    void setCaminhoPai(const wxString &caminhoPai);
    wxString &getTamanhoFormatado();
    void setTamanhoFormatado(const wxString &tamanhoFormatado);
    wxString &getModificadoFormatado();
    void setModificadoFormatado(const wxString &modificadoFormatado);
    wxString &getCaminhoOriginal();
    void setCaminhoOriginal(const wxString &caminhoOriginal);
    void limparDados();
    bool equals(Diretorio *obj);
    wxString &toString();

};

}
}

#endif // DIRETORIO_H
