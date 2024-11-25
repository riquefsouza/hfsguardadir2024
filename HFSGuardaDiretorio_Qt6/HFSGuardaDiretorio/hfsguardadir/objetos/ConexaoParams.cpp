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

QString &ConexaoParams::getDriver() {
    return driver;
}

void ConexaoParams::setDriver(const QString &driver) {
    this->driver = driver;
}

QString &ConexaoParams::getLogin() {
    return login;
}

void ConexaoParams::setLogin(const QString &login) {
    this->login = login;
}

QString &ConexaoParams::getNome() {
    return nome;
}

void ConexaoParams::setNome(const QString &nome) {
    this->nome = nome;
}

QString &ConexaoParams::getSenha() {
    return senha;
}

void ConexaoParams::setSenha(const QString &senha) {
    this->senha = senha;
}

QString &ConexaoParams::getUrl() {
    return url;
}

void ConexaoParams::setUrl(const QString &url) {
    this->url = url;
}

QString &ConexaoParams::toString() {
    return this->nome;
}

}

}
