#ifndef TABELA_H
#define TABELA_H

#include <wx/string.h>
#include <wx/gauge.h>
#include <wx/listctrl.h>
#include <wx/imaglist.h>
#include "hfsguardadir/objetos/Diretorio.h"
#include "hfsguardadir/objetos/Extensao.h"
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::comum;
using namespace hfsguardadir::objetos;

namespace hfsguardadir {

namespace objetosgui {

class Tabela : public wxListView
{
private:
    bool bTabelaDir;
	void modeloColunas();
	//wxImage getIconePorExtensao(wxVector<Extensao> extensoes,
		//const wxString &nome, const wxString &tipo);

public:
    Tabela(wxWindow *parent, bool bTabelaDir, wxImageList *imageList16, wxImageList *imageList32);
	~Tabela();
	int encontrarLinha(const wxString &nome);
	Diretorio* getLinhaSelecionada();
	void modeloTabela(wxVector<Diretorio> diretorios, 
		wxVector<Extensao> extensoes,
		wxGauge *barraProgresso);
	bool isSelecionado();
	void selecionaLinha(int linha);
	void deselecionaLinha(int linha);
	long primeiraLinhaSelecionada();
	void limpar();

};

}
}

#endif // TABELA_H
