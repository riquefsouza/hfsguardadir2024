#ifndef CONEXAOPARAMS_H
#define CONEXAOPARAMS_H

#ifndef PTRDIFF_MAX
#define PTRDIFF_MAX (std::numeric_limits<ptrdiff_t>::max())
#endif

#include <glibmm/ustring.h>

namespace hfsguardadir {

namespace objetos {

class ConexaoParams
{
private:
    Glib::ustring nome;
    Glib::ustring driver;
    Glib::ustring url;
    Glib::ustring login;
    Glib::ustring senha;

public:
    ConexaoParams();
    Glib::ustring &getDriver();
    void setDriver(const Glib::ustring &driver);
    Glib::ustring &getLogin();
    void setLogin(const Glib::ustring &login);
    Glib::ustring &getNome();
    void setNome(const Glib::ustring &nome);
    Glib::ustring &getSenha();
    void setSenha(const Glib::ustring &senha);
    Glib::ustring &getUrl();
    void setUrl(const Glib::ustring &url);
    Glib::ustring &toString();

};

}
}

#endif // CONEXAOPARAMS_H
