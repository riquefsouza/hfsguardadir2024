#ifndef CONEXAOPARAMS_H
#define CONEXAOPARAMS_H

#include <string>

namespace hfsguardadir {

namespace objetos {

class ConexaoParams
{
private:
    std::string nome;
    std::string driver;
    std::string url;
    std::string login;
    std::string senha;

public:
    ConexaoParams();
    std::string &getDriver();
    void setDriver(const std::string &driver);
    std::string &getLogin();
    void setLogin(const std::string &login);
    std::string &getNome();
    void setNome(const std::string &nome);
    std::string &getSenha();
    void setSenha(const std::string &senha);
    std::string &getUrl();
    void setUrl(const std::string &url);
    std::string &toString();

};

}
}

#endif // CONEXAOPARAMS_H
