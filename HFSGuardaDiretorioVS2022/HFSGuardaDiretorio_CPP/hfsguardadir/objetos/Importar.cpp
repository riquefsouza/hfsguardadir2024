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

std::string &Importar::getRotuloRaiz() {
    return rotuloRaiz;
}

void Importar::setRotuloRaiz(const std::string &rotuloRaiz) {
    this->rotuloRaiz = rotuloRaiz;
}

std::string Importar::getNomeDirRaiz() {
    return nomeDirRaiz;
}

void Importar::setNomeDirRaiz(const std::string &nomeDirRaiz) {
    this->nomeDirRaiz = nomeDirRaiz;
}

std::string &Importar::getCaminho() {
    return caminho;
}

void Importar::setCaminho(const std::string &caminho) {
    this->caminho = caminho;
}


}

}
