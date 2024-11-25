#ifndef CONEXAOPARAMS_H
#define CONEXAOPARAMS_H

#include <QString>

namespace hfsguardadir {

namespace objetos {

class ConexaoParams
{
private:
    QString nome;
    QString driver;
    QString url;
    QString login;
    QString senha;

public:
    ConexaoParams();
    QString &getDriver();
    void setDriver(const QString &driver);
    QString &getLogin();
    void setLogin(const QString &login);
    QString &getNome();
    void setNome(const QString &nome);
    QString &getSenha();
    void setSenha(const QString &senha);
    QString &getUrl();
    void setUrl(const QString &url);
    QString &toString();

};

}
}

#endif // CONEXAOPARAMS_H
