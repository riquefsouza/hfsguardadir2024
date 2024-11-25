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
    std::string caminho;
    std::string nomePai;
    std::string caminhoPai;
    std::string tamanhoFormatado;
    std::string modificadoFormatado;
    std::string caminhoOriginal;

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
    std::string &getCaminho();
    void setCaminho(const std::string &caminho);
    std::string &getNomePai();
    void setNomePai(const std::string &nomePai);
    std::string &getCaminhoPai();
    void setCaminhoPai(const std::string &caminhoPai);
    std::string &getTamanhoFormatado();
    void setTamanhoFormatado(const std::string &tamanhoFormatado);
    std::string &getModificadoFormatado();
    void setModificadoFormatado(const std::string &modificadoFormatado);
    std::string &getCaminhoOriginal();
    void setCaminhoOriginal(const std::string &caminhoOriginal);
    void limparDados();
    bool equals(Diretorio *obj);
    std::string &toString();

};

}
}

#endif // DIRETORIO_H
