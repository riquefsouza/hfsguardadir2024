#include "Importar.h"

namespace hfsguardadir {

namespace objetos {

Importar::Importar()
{

}

int Importar::getAba() {
    return aba;
}

void Importar::setAba(int aba) {
    this->aba = aba;
}

int Importar::getCodDirRaiz() {
    return codDirRaiz;
}

void Importar::setCodDirRaiz(int codDirRaiz) {
    this->codDirRaiz = codDirRaiz;
}

QString &Importar::getRotuloRaiz() {
    return rotuloRaiz;
}

void Importar::setRotuloRaiz(const QString &rotuloRaiz) {
    this->rotuloRaiz = rotuloRaiz;
}

QString Importar::getNomeDirRaiz() {
    return nomeDirRaiz;
}

void Importar::setNomeDirRaiz(const QString &nomeDirRaiz) {
    this->nomeDirRaiz = nomeDirRaiz;
}

QString &Importar::getCaminho() {
    return caminho;
}

void Importar::setCaminho(const QString &caminho) {
    this->caminho = caminho;
}


}

}
