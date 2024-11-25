#include "stdafx.h"
#include "Arquivo.h"

namespace hfsguardadir {

namespace objetos {

Arquivo::Arquivo()
{
	limparDados();
}

Arquivo::Arquivo(const CString &nome, long long tamanho, const CTime &modificado, const CString &atributos) {
    this->nome = nome;
    this->tamanho = tamanho;
    this->modificado = modificado;
    this->atributos = atributos;
}

CString &Arquivo::getNome() {
    return nome;
}

void Arquivo::setNome(const CString &nome) {
    this->nome = nome;
}

long long Arquivo::getTamanho() {
    return tamanho;
}

void Arquivo::setTamanho(long long tamanho) {
    this->tamanho = tamanho;
}

CTime &Arquivo::getModificado() {
    return modificado;
}

void Arquivo::setModificado(const CTime &modificado) {
    this->modificado = modificado;
}

CString &Arquivo::getAtributos() {
    return atributos;
}

void Arquivo::setAtributos(const CString &atributos) {
    this->atributos = atributos;
}

void Arquivo::limparDados() {
    this->nome = "";
    this->tamanho = 0;
	this->modificado = CTime::GetCurrentTime();
    this->atributos = "";
}

bool Arquivo::equals(Arquivo *obj) {
    return (obj->getNome() == this->getNome()
            && obj->getTamanho() == this->getTamanho()
            && obj->getModificado() == this->getModificado()
            && obj->getAtributos() == this->getAtributos());
}

CString &Arquivo::toString() {
    return this->nome;
}

}

}
