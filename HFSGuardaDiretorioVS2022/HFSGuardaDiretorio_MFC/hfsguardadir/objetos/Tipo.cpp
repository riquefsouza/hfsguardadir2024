#include "stdafx.h"
#include "Tipo.h"

namespace hfsguardadir {

namespace objetos {

Tipo::Tipo()
{
    this->limparDados();
}

Tipo::Tipo(char codigo, const CString &nome) {
    this->codigo = codigo;
    this->nome = nome;
}

char Tipo::getCodigo() {
    return codigo;
}

void Tipo::setCodigo(char codigo) {
    this->codigo = codigo;
}

CString &Tipo::getNome() {
    return nome;
}

void Tipo::setNome(const CString &nome) {
    this->nome = nome;
}

void Tipo::limparDados() {
    this->codigo = ' ';
    this->nome = "";
}

bool Tipo::equals(Tipo *obj) {
    return obj->getCodigo() == this->getCodigo()
            && obj->getNome() == this->getNome();
}

CString &Tipo::toString() {
    return this->nome;
}

}
}
