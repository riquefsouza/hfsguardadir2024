#include "Aba.h"

namespace hfsguardadir {

namespace objetos {

Aba::Aba()
{
    this->limparDados();
}

Aba::Aba(int codigo, const QString &nome, int ordem) {
    this->codigo = codigo;
    this->nome = nome;
    this->ordem = ordem;
}

int Aba::getCodigo() {
    return codigo;
}

void Aba::setCodigo(int codigo) {
    this->codigo = codigo;
}

QString &Aba::getNome() {
    return nome;
}

void Aba::setNome(const QString &nome) {
    this->nome = nome;
}

int Aba::getOrdem() {
    return ordem;
}

void Aba::setOrdem(int ordem) {
    this->ordem = ordem;
}

void Aba::limparDados() {
    this->codigo = 0;
    this->nome = "";
    this->ordem = 0;
}

bool Aba::equals(Aba obj) {
    return (obj.getCodigo() == this->getCodigo()
            && obj.getNome() == this->getNome()
            && obj.getOrdem() == this->getOrdem());
}

QString &Aba::toString() {
    return this->nome;
}

}

}
