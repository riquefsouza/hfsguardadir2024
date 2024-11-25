#include "Extensao.h"

namespace hfsguardadir {

namespace objetos {

Extensao::Extensao()
{
    this->limparDados();
}

Extensao::Extensao(int codigo, const wxString &nome, int ordem,
	const wxMemoryBuffer &bmp16, const wxMemoryBuffer &bmp32) {
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

wxString &Extensao::getNome() {
    return nome;
}

void Extensao::setNome(const wxString &nome) {
    this->nome = nome;
}

int Extensao::getOrdem() {
    return ordem;
}

void Extensao::setOrdem(int ordem) {
    this->ordem = ordem;
}

wxMemoryBuffer &Extensao::getBmp16() {
    return bmp16;
}

void Extensao::setBmp16(const wxMemoryBuffer &bmp16) {
    this->bmp16 = bmp16;
}

wxMemoryBuffer &Extensao::getBmp32() {
    return bmp32;
}

void Extensao::setBmp32(const wxMemoryBuffer &bmp32) {
    this->bmp32 = bmp32;
}

wxMemoryBuffer &Extensao::getGif16() {
    return gif16;
}

void Extensao::setGif16(const wxMemoryBuffer &gif16) {
    this->gif16 = gif16;
}

wxMemoryBuffer &Extensao::getGif32() {
    return gif32;
}

void Extensao::setGif32(const wxMemoryBuffer &gif32) {
    this->gif32 = gif32;
}

void Extensao::limparDados() {
    this->codigo = 0;
    this->nome = "";
    this->ordem = 0;
	this->bmp16.Clear();
    this->bmp32.Clear();
    this->gif16.Clear();
    this->gif32.Clear();
}

bool Extensao::equals(Extensao *obj) {
    return (obj->getCodigo() == this->getCodigo()
            && obj->getNome() == this->getNome()
            && obj->getOrdem() == this->getOrdem());
}

wxString &Extensao::toString() {
    return this->getNome();
}

}
}
