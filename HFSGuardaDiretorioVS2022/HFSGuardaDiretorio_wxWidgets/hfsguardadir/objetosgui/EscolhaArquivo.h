#ifndef ESCOLHAARQUIVO_H
#define ESCOLHAARQUIVO_H

#include <wx/string.h>
#include <wx/window.h>

namespace hfsguardadir {

namespace objetosgui {

class EscolhaArquivo
{
private:
	EscolhaArquivo();
	static wxString getTextoExtensao(const wxString &extensao);

public:    
    static wxString abrirDiretorio(wxWindow *parent);
	static wxString abrirArquivo(wxWindow *parent);
	static wxString abrirArquivo(wxWindow *parent, const wxString &arquivo, const wxString &extensao);
	static wxString salvarArquivo(wxWindow *parent, const wxString &arquivo, const wxString &extensao);

};

}
}

#endif // ESCOLHAARQUIVO_H
