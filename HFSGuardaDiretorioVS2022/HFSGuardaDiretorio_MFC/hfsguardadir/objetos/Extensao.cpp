#include "stdafx.h"
#include "Extensao.h"

namespace hfsguardadir {

namespace objetos {

Extensao::Extensao()
{
    this->limparDados();
}

Extensao::Extensao(int codigo, const CString &nome, int ordem,
	CBitmap* bmp16, CBitmap* bmp32) {
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

CString &Extensao::getNome() {
    return nome;
}

void Extensao::setNome(const CString &nome) {
    this->nome = nome;
}

int Extensao::getOrdem() {
    return ordem;
}

void Extensao::setOrdem(int ordem) {
    this->ordem = ordem;
}

CBitmap* Extensao::getBmp16() {
    return bmp16;
}

void Extensao::setBmp16(CBitmap* bmp16) {
    this->bmp16 = bmp16;
}

CBitmap* Extensao::getBmp32() {
    return bmp32;
}

void Extensao::setBmp32(CBitmap* bmp32) {
    this->bmp32 = bmp32;
}

void Extensao::limparDados() {
    this->codigo = 0;
    this->nome = "";
    this->ordem = 0;
	this->bmp16 = NULL;
	this->bmp32 = NULL;
}

bool Extensao::equals(Extensao *obj) {
    return (obj->getCodigo() == this->getCodigo()
            && obj->getNome() == this->getNome()
            && obj->getOrdem() == this->getOrdem());
}

CString &Extensao::toString() {
    return this->getNome();
}

}
}
