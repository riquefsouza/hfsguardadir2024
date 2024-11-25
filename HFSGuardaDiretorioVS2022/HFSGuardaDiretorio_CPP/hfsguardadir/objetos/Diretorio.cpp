#include "Diretorio.h"

namespace hfsguardadir {

namespace objetos {

Diretorio::Diretorio()
{
    this->aba.limparDados();
    this->tipo.limparDados();
    this->limparDados();
}

Aba Diretorio::getAba() {
    return aba;
}

void Diretorio::setAba(Aba aba) {
    this->aba = aba;
}

int Diretorio::getCodigo() {
    return codigo;
}

void Diretorio::setCodigo(int codigo) {
    this->codigo = codigo;
}

int Diretorio::getOrdem() {
    return ordem;
}

void Diretorio::setOrdem(int ordem) {
    this->ordem = ordem;
}

int Diretorio::getCodDirPai() {
    return codDirPai;
}

void Diretorio::setCodDirPai(int codDirPai) {
    this->codDirPai = codDirPai;
}

Tipo Diretorio::getTipo() {
    return tipo;
}

void Diretorio::setTipo(Tipo tipo) {
    this->tipo = tipo;
}

std::string &Diretorio::getCaminho() {
    return caminho;
}

void Diretorio::setCaminho(const std::string &caminho) {
    this->caminho = caminho;
}

std::string &Diretorio::getNomePai() {
    return nomePai;
}

void Diretorio::setNomePai(const std::string &nomePai) {
    this->nomePai = nomePai;
}

std::string &Diretorio::getCaminhoPai() {
    return caminhoPai;
}

void Diretorio::setCaminhoPai(const std::string &caminhoPai) {
    this->caminhoPai = caminhoPai;
}

std::string &Diretorio::getTamanhoFormatado() {
    return tamanhoFormatado;
}

void Diretorio::setTamanhoFormatado(const std::string &tamanhoFormatado) {
    this->tamanhoFormatado = tamanhoFormatado;
}

std::string &Diretorio::getModificadoFormatado() {
    return modificadoFormatado;
}

void Diretorio::setModificadoFormatado(const std::string &modificadoFormatado) {
    this->modificadoFormatado = modificadoFormatado;
}

std::string &Diretorio::getCaminhoOriginal() {
    return caminhoOriginal;
}

void Diretorio::setCaminhoOriginal(const std::string &caminhoOriginal) {
    this->caminhoOriginal = caminhoOriginal;
}

void Diretorio::limparDados() {
    Arquivo::limparDados();

    this->aba.limparDados();
    this->codigo = 0;
    this->ordem = 0;
    this->codDirPai = 0;
    this->tipo.limparDados();
    this->caminho = "";
    this->nomePai = "";
    this->caminhoPai = "";
    this->tamanhoFormatado = "";
    this->modificadoFormatado = "";
    this->caminhoOriginal = "";
}

bool Diretorio::equals(Diretorio *obj) {
    return (obj->getAba().equals(&this->getAba())
            && obj->getCodigo() == this->getCodigo()
            && obj->getOrdem() == this->getOrdem()
            && obj->getCodDirPai() == this->getCodDirPai()
            && obj->getNome() == this->getNome()
            && obj->getTamanho() == this->getTamanho()
            && obj->getModificado() == this->getModificado()
            && obj->getAtributos() == this->getAtributos()
            && obj->getTipo().equals(&this->getTipo())
            && obj->getCaminho() == this->getCaminho()
            && obj->getNomePai() == this->getNomePai()
            && obj->getCaminhoPai() == this->getCaminhoPai()
            && obj->getTamanhoFormatado() == this->getTamanhoFormatado()
            && obj->getModificadoFormatado() == this->getModificadoFormatado()
            && obj->getCaminhoOriginal() == this->getCaminhoOriginal());
}

std::string &Diretorio::toString() {
    return this->getNome();
}

}

}
