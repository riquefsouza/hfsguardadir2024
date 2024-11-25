#ifndef DIALOGO_H
#define DIALOGO_H

#include <wx/string.h>
#include <wx/msgdlg.h>
#include <wx/textdlg.h>

namespace hfsguardadir {

namespace objetosgui {

class Dialogo
{
public:
    Dialogo();

    static void mensagemErro(wxWindow *pai, const wxString &recurso, const wxString &texto);
    static void mensagemErro(wxWindow *pai, const wxString &recurso);
    static void mensagemInfo(wxWindow *pai, const wxString &recurso);
    static int confirma(wxWindow *pai, const wxString &recurso);
    static wxString entrada(wxWindow *pai, const wxString &recurso);
    static wxString entrada(wxWindow *pai, const wxString &recurso,
        const wxString &valorInicial);
};

}
}

#endif // DIALOGO_H
