#include "Extensao.h"

namespace hfsguardadir {

namespace objetos {

Extensao::Extensao()
{
    this->limparDados();
}

Extensao::Extensao(int codigo, const std::string &nome, int ordem,
	ImagemBuffer bmp16, ImagemBuffer bmp32) {
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

std::string &Extensao::getNome() {
    return nome;
}

void Extensao::setNome(const std::string &nome) {
    this->nome = nome;
}

int Extensao::getOrdem() {
    return ordem;
}

void Extensao::setOrdem(int ordem) {
    this->ordem = ordem;
}

ImagemBuffer Extensao::getBmp16() {
    return bmp16;
}

void Extensao::setBmp16(ImagemBuffer bmp16) {
    this->bmp16 = bmp16;
}

ImagemBuffer Extensao::getBmp32() {
    return bmp32;
}

void Extensao::setBmp32(ImagemBuffer bmp32) {
    this->bmp32 = bmp32;
}

int Extensao::getTamanhoBmp16() {
	return tamanhoBmp16;
}

void Extensao::setTamanhoBmp16(int tamanhoBmp16) {
	this->tamanhoBmp16 = tamanhoBmp16;
}

int Extensao::getTamanhoBmp32() {
	return tamanhoBmp32;
}

void Extensao::setTamanhoBmp32(int tamanhoBmp32) {
	this->tamanhoBmp32 = tamanhoBmp32;
}
void Extensao::limparDados() {
    this->codigo = 0;
    this->nome = "";
    this->ordem = 0;
	this->tamanhoBmp16 = 0;
	this->tamanhoBmp32 = 0;
}

bool Extensao::equals(Extensao *obj) {
    return (obj->getCodigo() == this->getCodigo()
            && obj->getNome() == this->getNome()
            && obj->getOrdem() == this->getOrdem());
}

std::string &Extensao::toString() {
    return this->getNome();
}

}
}
