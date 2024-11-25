#include "Tipo.h"

namespace hfsguardadir {

namespace objetos {

Tipo::Tipo()
{
    this->limparDados();
}

Tipo::Tipo(const char codigo, const Glib::ustring nome) {
    this->codigo = codigo;
    this->nome = nome;
}

char Tipo::getCodigo() {
    return codigo;
}

void Tipo::setCodigo(const char codigo) {
    this->codigo = codigo;
}

Glib::ustring Tipo::getNome() {
    return nome;
}

void Tipo::setNome(const Glib::ustring nome) {
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

Glib::ustring Tipo::toString() {
    return this->nome;
}

}
}
