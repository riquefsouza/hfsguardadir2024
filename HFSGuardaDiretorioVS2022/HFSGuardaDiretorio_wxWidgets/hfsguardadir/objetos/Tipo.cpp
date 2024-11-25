#include "Tipo.h"

namespace hfsguardadir {

namespace objetos {

Tipo::Tipo()
{
    this->limparDados();
}

Tipo::Tipo(const wxChar &codigo, const wxString &nome) {
    this->codigo = codigo;
    this->nome = nome;
}

wxChar &Tipo::getCodigo() {
    return codigo;
}

void Tipo::setCodigo(const wxChar &codigo) {
    this->codigo = codigo;
}

wxString &Tipo::getNome() {
    return nome;
}

void Tipo::setNome(const wxString &nome) {
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

wxString &Tipo::toString() {
    return this->nome;
}

}
}
