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
    Glib::ustring caminho;
    Glib::ustring nomePai;
    Glib::ustring caminhoPai;
    Glib::ustring tamanhoFormatado;
    Glib::ustring modificadoFormatado;
    Glib::ustring caminhoOriginal;

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
    Glib::ustring getCaminho();
    void setCaminho(const Glib::ustring caminho);
    Glib::ustring getNomePai();
    void setNomePai(const Glib::ustring nomePai);
    Glib::ustring getCaminhoPai();
    void setCaminhoPai(const Glib::ustring caminhoPai);
    Glib::ustring getTamanhoFormatado();
    void setTamanhoFormatado(const Glib::ustring tamanhoFormatado);
    Glib::ustring getModificadoFormatado();
    void setModificadoFormatado(const Glib::ustring modificadoFormatado);
    Glib::ustring getCaminhoOriginal();
    void setCaminhoOriginal(const Glib::ustring caminhoOriginal);
    void limparDados();
    bool equals(Diretorio *obj);
    Glib::ustring toString();

};

}
}

#endif // DIRETORIO_H
