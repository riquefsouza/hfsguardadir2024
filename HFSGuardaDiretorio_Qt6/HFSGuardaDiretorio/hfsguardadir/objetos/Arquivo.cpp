#include "Arquivo.h"

namespace hfsguardadir {

namespace objetos {

Arquivo::Arquivo()
{

}

Arquivo::Arquivo(const QString &nome, long long tamanho, const QDateTime &modificado, const QString &atributos) {
    this->nome = nome;
    this->tamanho = tamanho;
    this->modificado = modificado;
    this->atributos = atributos;
}

QString &Arquivo::getNome() {
    return nome;
}

void Arquivo::setNome(const QString &nome) {
    this->nome = nome;
}

long long Arquivo::getTamanho() {
    return tamanho;
}

void Arquivo::setTamanho(long long tamanho) {
    this->tamanho = tamanho;
}

QDateTime &Arquivo::getModificado() {
    return modificado;
}

void Arquivo::setModificado(const QDateTime &modificado) {
    this->modificado = modificado;
}

QString &Arquivo::getAtributos() {
    return atributos;
}

void Arquivo::setAtributos(const QString &atributos) {
    this->atributos = atributos;
}

void Arquivo::limparDados() {
    this->nome = "";
    this->tamanho = 0;
    this->modificado = QDateTime::currentDateTime();
    this->atributos = "";
}

bool Arquivo::equals(Arquivo *obj) {
    return (obj->getNome() == this->getNome()
            && obj->getTamanho() == this->getTamanho()
            && obj->getModificado() == this->getModificado()
            && obj->getAtributos() == this->getAtributos());
}

QString &Arquivo::toString() {
    return this->nome;
}

}

}
