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

std::string &ConexaoParams::getDriver() {
    return driver;
}

void ConexaoParams::setDriver(const std::string &driver) {
    this->driver = driver;
}

std::string &ConexaoParams::getLogin() {
    return login;
}

void ConexaoParams::setLogin(const std::string &login) {
    this->login = login;
}

std::string &ConexaoParams::getNome() {
    return nome;
}

void ConexaoParams::setNome(const std::string &nome) {
    this->nome = nome;
}

std::string &ConexaoParams::getSenha() {
    return senha;
}

void ConexaoParams::setSenha(const std::string &senha) {
    this->senha = senha;
}

std::string &ConexaoParams::getUrl() {
    return url;
}

void ConexaoParams::setUrl(const std::string &url) {
    this->url = url;
}

std::string &ConexaoParams::toString() {
    return this->nome;
}

}

}
