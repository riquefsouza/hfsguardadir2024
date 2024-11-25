#ifndef ARVORE_H
#define ARVORE_H

#include <wx/treectrl.h>
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosgui {

class Arvore: public wxTreeCtrl
{
public:
    Arvore(wxWindow *parent, wxImageList *imageList16);
    ~Arvore();

    void encontrarCaminhoPorNome(wxArrayString nomes);
	bool isSelecionado(const wxTreeItemId &item);
	void limpar();

};

}
}

#endif // ARVORE_H
