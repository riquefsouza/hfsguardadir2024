#ifndef IMPORTAR_H
#define IMPORTAR_H

#include <QString>

namespace hfsguardadir {

namespace objetos {

class Importar
{
private:
    int aba;
    int codDirRaiz;
    QString rotuloRaiz;
    QString nomeDirRaiz;
    QString caminho;

public:
    Importar();
    int getAba();
    void setAba(int aba);
    int getCodDirRaiz();
    void setCodDirRaiz(int codDirRaiz);
    QString &getRotuloRaiz();
    void setRotuloRaiz(const QString &rotuloRaiz);
    QString getNomeDirRaiz();
    void setNomeDirRaiz(const QString &nomeDirRaiz);
    QString &getCaminho();
    void setCaminho(const QString &caminho);

};

}
}

#endif // IMPORTAR_H
