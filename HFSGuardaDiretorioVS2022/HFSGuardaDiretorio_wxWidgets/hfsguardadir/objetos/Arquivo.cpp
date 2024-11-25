#include "Arquivo.h"

namespace hfsguardadir {

namespace objetos {

Arquivo::Arquivo()
{

}

Arquivo::Arquivo(const wxString &nome, const wxULongLong &tamanho, const wxDateTime &modificado, const wxString &atributos) {
    this->nome = nome;
    this->tamanho = tamanho;
    this->modificado = modificado;
    this->atributos = atributos;
}

wxString &Arquivo::getNome() {
    return nome;
}

void Arquivo::setNome(const wxString &nome) {
    this->nome = nome;
}

wxULongLong &Arquivo::getTamanho() {
    return tamanho;
}

void Arquivo::setTamanho(const wxULongLong &tamanho) {
    this->tamanho = tamanho;
}

wxDateTime &Arquivo::getModificado() {
    return modificado;
}

void Arquivo::setModificado(const wxDateTime &modificado) {
    this->modificado = modificado;
}

wxString &Arquivo::getAtributos() {
    return atributos;
}

void Arquivo::setAtributos(const wxString &atributos) {
    this->atributos = atributos;
}

void Arquivo::limparDados() {
    this->nome = "";
    this->tamanho = 0;
	this->modificado = wxDateTime::Now();
    this->atributos = "";
}

bool Arquivo::equals(Arquivo *obj) {
    return (obj->getNome() == this->getNome()
            && obj->getTamanho() == this->getTamanho()
            && obj->getModificado() == this->getModificado()
            && obj->getAtributos() == this->getAtributos());
}

wxString &Arquivo::toString() {
    return this->nome;
}

}

}
