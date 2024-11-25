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
    QString caminho;
    QString nomePai;
    QString caminhoPai;
    QString tamanhoFormatado;
    QString modificadoFormatado;
    QString caminhoOriginal;

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
    QString &getCaminho();
    void setCaminho(const QString &caminho);
    QString &getNomePai();
    void setNomePai(const QString &nomePai);
    QString &getCaminhoPai();
    void setCaminhoPai(const QString &caminhoPai);
    QString &getTamanhoFormatado();
    void setTamanhoFormatado(const QString &tamanhoFormatado);
    QString &getModificadoFormatado();
    void setModificadoFormatado(const QString &modificadoFormatado);
    QString &getCaminhoOriginal();
    void setCaminhoOriginal(const QString &caminhoOriginal);
    void limparDados();
    bool equals(Diretorio *obj);
    QString &toString();

};

}
}

#endif // DIRETORIO_H
