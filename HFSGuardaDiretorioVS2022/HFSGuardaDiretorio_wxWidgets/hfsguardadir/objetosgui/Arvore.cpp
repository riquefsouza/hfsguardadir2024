#include "Arvore.h"

namespace hfsguardadir {

namespace objetosgui {

Arvore::Arvore(wxWindow *parent, wxImageList *imageList16) :
	wxTreeCtrl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 
		wxTR_DEFAULT_STYLE | wxTR_SINGLE | wxTR_HIDE_ROOT)
{
	SetImageList(imageList16);
	SetName("Arvore");
}

Arvore::~Arvore()
{

}

void Arvore::encontrarCaminhoPorNome(wxArrayString nomes){
	wxTreeItemId proximoItem, diretorioItem;
	wxString texto;
	unsigned int nivel;

	proximoItem = this->GetFirstVisibleItem();
	nivel = 0;
	while (proximoItem.IsOk()) {
		texto = this->GetItemText(proximoItem);

		if (nomes[nivel] == texto) {
			diretorioItem = proximoItem;
			this->Expand(diretorioItem);

			if (nivel == (nomes.size() - 1)) {				
				break;
			}
			nivel++;
		}
		proximoItem = this->GetNextVisible(proximoItem);
	}

	if (diretorioItem.IsOk()) {
		this->SelectItem(diretorioItem, true);
		
	}
}

bool Arvore::isSelecionado(const wxTreeItemId &item) {
	if (this->GetCount() > 0) {
		return (this->IsSelected(item));
	}

	return false;
}

void Arvore::limpar() {	
	this->DeleteAllItems();
}

}
}
