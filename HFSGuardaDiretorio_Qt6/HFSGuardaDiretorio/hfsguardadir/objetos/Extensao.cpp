#include "Extensao.h"

namespace hfsguardadir {

namespace objetos {

Extensao::Extensao()
{
    this->limparDados();
}

Extensao::Extensao(int codigo, const QString &nome, int ordem,
	const QByteArray &bmp16, const QByteArray &bmp32) {
    this->codigo = codigo;
    this->nome = nome;
    this->ordem = ordem;
    this->bmp16 = bmp16;
    this->bmp32 = bmp32;
}

int Extensao::getCodigo() {
    return codigo;
}

void Extensao::setCodigo(int codigo) {
    this->codigo = codigo;
}

QString &Extensao::getNome() {
    return nome;
}

void Extensao::setNome(const QString &nome) {
    this->nome = nome;
}

int Extensao::getOrdem() {
    return ordem;
}

void Extensao::setOrdem(int ordem) {
    this->ordem = ordem;
}

QByteArray Extensao::getBmp16() {
    return bmp16;
}

void Extensao::setBmp16(const QByteArray &bmp16) {
    this->bmp16 = bmp16;
}

QByteArray Extensao::getBmp32() {
    return bmp32;
}

void Extensao::setBmp32(const QByteArray &bmp32) {
    this->bmp32 = bmp32;
}

QByteArray Extensao::getGif16() {
    return gif16;
}

void Extensao::setGif16(const QByteArray &gif16) {
    this->gif16 = gif16;
}

QByteArray Extensao::getGif32() {
    return gif32;
}

void Extensao::setGif32(const QByteArray &gif32) {
    this->gif32 = gif32;
}

void Extensao::limparDados() {
    this->codigo = 0;
    this->nome = "";
    this->ordem = 0;
    this->bmp16.clear();
    this->bmp32.clear();
    this->gif16.clear();
    this->gif32.clear();
}

bool Extensao::equals(Extensao *obj) {
    return (obj->getCodigo() == this->getCodigo()
            && obj->getNome() == this->getNome()
            && obj->getOrdem() == this->getOrdem());
}

QString &Extensao::toString() {
    return this->getNome();
}

}
}
