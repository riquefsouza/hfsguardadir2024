#include "Tipo.h"

namespace hfsguardadir {

namespace objetos {

Tipo::Tipo()
{
    this->limparDados();
}

Tipo::Tipo(char codigo, const QString &nome) {
    this->codigo = codigo;
    this->nome = nome;
}

char Tipo::getCodigo() {
    return codigo;
}

void Tipo::setCodigo(char codigo) {
    this->codigo = codigo;
}

QString &Tipo::getNome() {
    return nome;
}

void Tipo::setNome(const QString &nome) {
    this->nome = nome;
}

void Tipo::limparDados() {
    this->codigo = ' ';
    this->nome = "";
}

bool Tipo::equals(Tipo obj) {
    return obj.getCodigo() == this->getCodigo()
            && obj.getNome() == this->getNome();
}

QString &Tipo::toString() {
    return this->nome;
}

}
}
