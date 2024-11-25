#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <QString>
#include <QDateTime>

namespace hfsguardadir {

namespace objetos {

class Arquivo
{
private:
    QString nome;
    long long tamanho;
    QDateTime modificado;
    QString atributos;

public:
    Arquivo();
    Arquivo(const QString &nome, long long tamanho, const QDateTime &modificado, const QString &atributos);
    QString &getNome();
    void setNome(const QString &nome);
    long long getTamanho();
    void setTamanho(long long tamanho);
    QDateTime &getModificado();
    void setModificado(const QDateTime &modificado);
    QString &getAtributos();
    void setAtributos(const QString &atributos);
    void limparDados();
    bool equals(Arquivo *obj);
    QString &toString();

};

}

}

#endif // ARQUIVO_H
