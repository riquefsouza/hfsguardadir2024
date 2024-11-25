#include "stdafx.h"
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

CString &Importar::getRotuloRaiz() {
    return rotuloRaiz;
}

void Importar::setRotuloRaiz(const CString &rotuloRaiz) {
    this->rotuloRaiz = rotuloRaiz;
}

CString Importar::getNomeDirRaiz() {
    return nomeDirRaiz;
}

void Importar::setNomeDirRaiz(const CString &nomeDirRaiz) {
    this->nomeDirRaiz = nomeDirRaiz;
}

CString &Importar::getCaminho() {
    return caminho;
}

void Importar::setCaminho(const CString &caminho) {
    this->caminho = caminho;
}


}

}
