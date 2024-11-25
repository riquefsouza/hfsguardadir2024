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

wxString &Importar::getRotuloRaiz() {
    return rotuloRaiz;
}

void Importar::setRotuloRaiz(const wxString &rotuloRaiz) {
    this->rotuloRaiz = rotuloRaiz;
}

wxString Importar::getNomeDirRaiz() {
    return nomeDirRaiz;
}

void Importar::setNomeDirRaiz(const wxString &nomeDirRaiz) {
    this->nomeDirRaiz = nomeDirRaiz;
}

wxString &Importar::getCaminho() {
    return caminho;
}

void Importar::setCaminho(const wxString &caminho) {
    this->caminho = caminho;
}


}

}
