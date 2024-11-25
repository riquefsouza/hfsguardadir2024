#ifndef CONEXAOPARAMS_H
#define CONEXAOPARAMS_H

#pragma once

namespace hfsguardadir {

namespace objetos {

class ConexaoParams
{
private:
    CString nome;
    CString driver;
    CString url;
    CString login;
    CString senha;

public:
    ConexaoParams();
    CString &getDriver();
    void setDriver(const CString &driver);
    CString &getLogin();
    void setLogin(const CString &login);
    CString &getNome();
    void setNome(const CString &nome);
    CString &getSenha();
    void setSenha(const CString &senha);
    CString &getUrl();
    void setUrl(const CString &url);
    CString &toString();

};

}
}

#endif // CONEXAOPARAMS_H
