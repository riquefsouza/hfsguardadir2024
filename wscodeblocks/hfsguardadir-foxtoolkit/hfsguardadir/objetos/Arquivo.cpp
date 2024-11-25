#include "Arquivo.h"
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetos {

Arquivo::Arquivo()
{

}

Arquivo::Arquivo(const std::string &nome, const unsigned long long &tamanho, 
	DateTime modificado, const std::string &atributos) {
    this->nome = nome;
    this->tamanho = tamanho;
    this->modificado = modificado;
    this->atributos = atributos;
}

std::string &Arquivo::getNome() {
    return nome;
}

void Arquivo::setNome(const std::string &nome) {
    this->nome = nome;
}

unsigned long long &Arquivo::getTamanho() {
    return tamanho;
}

void Arquivo::setTamanho(const unsigned long long &tamanho) {
    this->tamanho = tamanho;
}

DateTime Arquivo::getModificado() {
    return modificado;
}

void Arquivo::setModificado(DateTime modificado) {
    this->modificado = modificado;
}

std::string &Arquivo::getAtributos() {
    return atributos;
}

void Arquivo::setAtributos(const std::string &atributos) {
    this->atributos = atributos;
}

void Arquivo::limparDados() {
    this->nome = "";
    this->tamanho = 0;
	this->modificado = DateTime::Now();
    this->atributos = "";
}

bool Arquivo::equals(Arquivo *obj) {
    return (obj->getNome() == this->getNome()
            && obj->getTamanho() == this->getTamanho()
            //&& obj->getModificado() == this->getModificado()
            && obj->getAtributos() == this->getAtributos());
}

std::string &Arquivo::toString() {
    return this->nome;
}

}

}
