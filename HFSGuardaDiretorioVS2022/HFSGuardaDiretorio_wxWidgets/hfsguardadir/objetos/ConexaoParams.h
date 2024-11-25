#ifndef CONEXAOPARAMS_H
#define CONEXAOPARAMS_H

#include <wx/string.h>

namespace hfsguardadir {

namespace objetos {

class ConexaoParams
{
private:
    wxString nome;
    wxString driver;
    wxString url;
    wxString login;
    wxString senha;

public:
    ConexaoParams();
    wxString &getDriver();
    void setDriver(const wxString &driver);
    wxString &getLogin();
    void setLogin(const wxString &login);
    wxString &getNome();
    void setNome(const wxString &nome);
    wxString &getSenha();
    void setSenha(const wxString &senha);
    wxString &getUrl();
    void setUrl(const wxString &url);
    wxString &toString();

};

}
}

#endif // CONEXAOPARAMS_H
