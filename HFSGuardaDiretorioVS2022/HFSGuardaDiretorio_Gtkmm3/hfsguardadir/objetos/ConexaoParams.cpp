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

Glib::ustring &ConexaoParams::getDriver() {
    return driver;
}

void ConexaoParams::setDriver(const Glib::ustring &driver) {
    this->driver = driver;
}

Glib::ustring &ConexaoParams::getLogin() {
    return login;
}

void ConexaoParams::setLogin(const Glib::ustring &login) {
    this->login = login;
}

Glib::ustring &ConexaoParams::getNome() {
    return nome;
}

void ConexaoParams::setNome(const Glib::ustring &nome) {
    this->nome = nome;
}

Glib::ustring &ConexaoParams::getSenha() {
    return senha;
}

void ConexaoParams::setSenha(const Glib::ustring &senha) {
    this->senha = senha;
}

Glib::ustring &ConexaoParams::getUrl() {
    return url;
}

void ConexaoParams::setUrl(const Glib::ustring &url) {
    this->url = url;
}

Glib::ustring &ConexaoParams::toString() {
    return this->nome;
}

}

}
