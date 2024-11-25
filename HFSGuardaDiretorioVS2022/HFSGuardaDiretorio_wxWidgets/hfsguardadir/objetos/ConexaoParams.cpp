#include "ConexaoParams.h"

namespace hfsguardadir {

namespace objetos {

ConexaoParams::ConexaoParams()
{
    this->nome = "SQLITE";
    this->driver = "";
    this->url = "GuardaDir.db";
    this->login = "";
    this->senha = "";
}

wxString &ConexaoParams::getDriver() {
    return driver;
}

void ConexaoParams::setDriver(const wxString &driver) {
    this->driver = driver;
}

wxString &ConexaoParams::getLogin() {
    return login;
}

void ConexaoParams::setLogin(const wxString &login) {
    this->login = login;
}

wxString &ConexaoParams::getNome() {
    return nome;
}

void ConexaoParams::setNome(const wxString &nome) {
    this->nome = nome;
}

wxString &ConexaoParams::getSenha() {
    return senha;
}

void ConexaoParams::setSenha(const wxString &senha) {
    this->senha = senha;
}

wxString &ConexaoParams::getUrl() {
    return url;
}

void ConexaoParams::setUrl(const wxString &url) {
    this->url = url;
}

wxString &ConexaoParams::toString() {
    return this->nome;
}

}

}
