#ifndef EXTENSAO_H
#define EXTENSAO_H

#include <QString>
#include <QByteArray>

namespace hfsguardadir {

namespace objetos {

class Extensao
{
private:
    int codigo;
    QString nome;
    int ordem;
    QByteArray bmp16;
    QByteArray bmp32;
    QByteArray gif16;
    QByteArray gif32;

public:
    Extensao();
    Extensao(int codigo, const QString &nome, int ordem,
		const QByteArray &bmp16, const QByteArray &bmp32);
    int getCodigo();
    void setCodigo(int codigo);
    QString &getNome();
    void setNome(const QString &nome);
    int getOrdem();
    void setOrdem(int ordem);
    QByteArray getBmp16();
    void setBmp16(const QByteArray &bmp16);
    QByteArray getBmp32();
    void setBmp32(const QByteArray &bmp32);
    QByteArray getGif16();
    void setGif16(const QByteArray &gif16);
    QByteArray getGif32();
    void setGif32(const QByteArray &gif32);
    void limparDados();
    bool equals(Extensao *obj);
    QString &toString();

};

}
}

#endif // EXTENSAO_H
