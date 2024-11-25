#include "Arquivo.h"
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetos {

Arquivo::Arquivo()
{

}

Arquivo::Arquivo(const Glib::ustring nome, const unsigned long long tamanho,
	GDateTime* modificado, const Glib::ustring atributos) {
    this->nome = nome;
    this->tamanho = tamanho;
    this->modificado = modificado;
    this->atributos = atributos;
}

Glib::ustring Arquivo::getNome() {
    return nome;
}

void Arquivo::setNome(const Glib::ustring nome) {
    this->nome = nome;
}

unsigned long long Arquivo::getTamanho() {
    return tamanho;
}

void Arquivo::setTamanho(const unsigned long long tamanho) {
    this->tamanho = tamanho;
}

GDateTime* Arquivo::getModificado() {
    return modificado;
}

void Arquivo::setModificado(GDateTime* modificado) {
    this->modificado = modificado;
}

Glib::ustring Arquivo::getAtributos() {
    return atributos;
}

void Arquivo::setAtributos(const Glib::ustring atributos) {
    this->atributos = atributos;
}

void Arquivo::limparDados() {
    this->nome = "";
    this->tamanho = 0;
	//this->modificado = DateTime::Now();
	this->modificado = Rotinas::DataHoraNow();
    this->atributos = "";
}

bool Arquivo::equals(Arquivo obj) {
    return (obj.getNome() == this->getNome()
            && obj.getTamanho() == this->getTamanho()
            //&& obj->getModificado() == this->getModificado()
            && obj.getAtributos() == this->getAtributos());
}

Glib::ustring Arquivo::toString() {
    return this->nome;
}

}

}
