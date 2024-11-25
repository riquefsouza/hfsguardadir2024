#include "Dialogo.h"

#include <wx/log.h>
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosgui {

Dialogo::Dialogo()
{

}

void Dialogo::mensagemErro(wxWindow *pai, const wxString &recurso, const wxString &texto) {
	wxMessageBox(Rotinas::getRecurso(recurso) + " " + texto, 
		Rotinas::getRecurso("Dialogo.erro"), wxOK | wxCENTRE | wxICON_ERROR, pai);

	wxLogDebug("warning: %s", Rotinas::getRecurso(recurso) + " " + texto);
}

void Dialogo::mensagemErro(wxWindow *pai, const wxString &recurso) {
    mensagemErro(pai, recurso, wxString(""));
}

void Dialogo::mensagemInfo(wxWindow *pai, const wxString &recurso) {
	wxMessageBox(Rotinas::getRecurso(recurso),
		Rotinas::getRecurso("Dialogo.info"), wxOK | wxCENTRE | wxICON_INFORMATION, pai);

	wxLogDebug("info: %s", Rotinas::getRecurso(recurso));
}

int Dialogo::confirma(wxWindow *pai, const wxString &recurso) {
	return wxMessageBox(Rotinas::getRecurso(recurso), 
		Rotinas::getRecurso("Dialogo.confirma"), wxYES_NO | wxCENTRE | wxICON_QUESTION, pai);
}

wxString Dialogo::entrada(wxWindow *pai, const wxString &recurso) {
    return wxGetTextFromUser(Rotinas::getRecurso(recurso), 
		Rotinas::getRecurso("Dialogo.entrada"), wxEmptyString, pai);
}

wxString Dialogo::entrada(wxWindow *pai, const wxString &recurso,
        const wxString &valorInicial) {
	return wxGetTextFromUser(Rotinas::getRecurso(recurso),
		Rotinas::getRecurso("Dialogo.entrada"), valorInicial, pai);
}

}
}
