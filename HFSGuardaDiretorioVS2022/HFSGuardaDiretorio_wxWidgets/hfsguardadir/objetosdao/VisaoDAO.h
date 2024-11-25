#ifndef VISAODAO_H
#define VISAODAO_H

#include <wx/string.h>
#include <wx/wxsqlite3.h>
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosdao {

class VisaoDAO
{
private:
    VisaoDAO();
    VisaoDAO(VisaoDAO const&);
    VisaoDAO& operator=(VisaoDAO const&);
    static VisaoDAO* instancia;

    wxString sqlVisao(const wxString &visao);

public:
    static VisaoDAO* getInstancia();
    bool criarVisao(const wxString &visao);

};

}
}

#endif // VISAODAO_H
