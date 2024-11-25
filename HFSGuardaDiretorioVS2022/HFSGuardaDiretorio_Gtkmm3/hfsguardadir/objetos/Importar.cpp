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

Glib::ustring &Importar::getRotuloRaiz() {
    return rotuloRaiz;
}

void Importar::setRotuloRaiz(const Glib::ustring &rotuloRaiz) {
    this->rotuloRaiz = rotuloRaiz;
}

Glib::ustring Importar::getNomeDirRaiz() {
    return nomeDirRaiz;
}

void Importar::setNomeDirRaiz(const Glib::ustring &nomeDirRaiz) {
    this->nomeDirRaiz = nomeDirRaiz;
}

Glib::ustring &Importar::getCaminho() {
    return caminho;
}

void Importar::setCaminho(const Glib::ustring &caminho) {
    this->caminho = caminho;
}


}

}
