#include "stdafx.h"
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

CString &ConexaoParams::getDriver() {
    return driver;
}

void ConexaoParams::setDriver(const CString &driver) {
    this->driver = driver;
}

CString &ConexaoParams::getLogin() {
    return login;
}

void ConexaoParams::setLogin(const CString &login) {
    this->login = login;
}

CString &ConexaoParams::getNome() {
    return nome;
}

void ConexaoParams::setNome(const CString &nome) {
    this->nome = nome;
}

CString &ConexaoParams::getSenha() {
    return senha;
}

void ConexaoParams::setSenha(const CString &senha) {
    this->senha = senha;
}

CString &ConexaoParams::getUrl() {
    return url;
}

void ConexaoParams::setUrl(const CString &url) {
    this->url = url;
}

CString &ConexaoParams::toString() {
    return this->nome;
}

}

}
