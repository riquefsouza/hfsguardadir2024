#include "Tabela.h"

#include "hfsguardadir\objetosbo\ExtensaoBO.h"

using namespace hfsguardadir::objetosbo;

namespace hfsguardadir {

namespace objetosgui {

Tabela::Tabela(wxWindow *parent, bool bTabelaDir, wxImageList *imageList16, wxImageList *imageList32):
	wxListView(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 
		wxLC_HRULES | wxLC_REPORT | wxLC_SINGLE_SEL | wxLC_VRULES)
{
	this->bTabelaDir = bTabelaDir;
	this->SetImageList(imageList32, wxIMAGE_LIST_NORMAL);
	this->SetImageList(imageList16, wxIMAGE_LIST_SMALL);
	SetName("Tabela");

	modeloColunas();
}

Tabela::~Tabela() 
{

}

int Tabela::encontrarLinha(const wxString &nome) {
	wxString slinha;
	int nlinha = 0;

	for (int i = 0; i < this->GetItemCount(); i++) {
		slinha = this->GetItemText(i);
		if (slinha == nome) {
			nlinha = i;
			break;
		}
	}
	return nlinha;
}

Diretorio* Tabela::getLinhaSelecionada() {	
	long item;
	Diretorio *dir = NULL;
	Aba aba;
	Tipo tipo;
	
	if (this->GetSelectedItemCount() > 0) {
		item = this->GetFirstSelected();

		dir = new Diretorio();
		dir->setNome(this->GetItemText(item, 0));
		dir->setTamanhoFormatado(this->GetItemText(item, 1));
		tipo.setNome(this->GetItemText(item, 2));
		dir->setTipo(tipo);
		dir->setModificadoFormatado(this->GetItemText(item, 3));
		dir->setAtributos(this->GetItemText(item, 4));
		dir->setCaminho(this->GetItemText(item, 5));
		if (!bTabelaDir) {
			aba.setNome(this->GetItemText(item, 6));
			dir->setAba(aba);
		}
	}

	return dir;
}

void Tabela::modeloColunas() {

	if (bTabelaDir) {
		this->AppendColumn(wxT("Nome"), wxLIST_FORMAT_LEFT, 300);
		this->AppendColumn(wxT("Tamanho"), wxLIST_FORMAT_LEFT, 100);
		this->AppendColumn(wxT("Tipo"), wxLIST_FORMAT_LEFT, 70);
		this->AppendColumn(wxT("Modificado"), wxLIST_FORMAT_LEFT, 120);
		this->AppendColumn(wxT("Atributos"), wxLIST_FORMAT_LEFT, 90);
		this->AppendColumn(wxT("Caminho"), wxLIST_FORMAT_LEFT, 500);
	}
	else {
		this->AppendColumn(wxT("Nome"), wxLIST_FORMAT_LEFT, 300);
		this->AppendColumn(wxT("Tamanho"), wxLIST_FORMAT_LEFT, 100);
		this->AppendColumn(wxT("Tipo"), wxLIST_FORMAT_LEFT, 70);
		this->AppendColumn(wxT("Modificado"), wxLIST_FORMAT_LEFT, 120);
		this->AppendColumn(wxT("Atributos"), wxLIST_FORMAT_LEFT, 90);
		this->AppendColumn(wxT("Caminho"), wxLIST_FORMAT_LEFT, 300);
		this->AppendColumn(wxT("Aba"), wxLIST_FORMAT_LEFT, 70);
		this->AppendColumn(wxT("Numero Aba"), wxLIST_FORMAT_LEFT, 0);
		this->AppendColumn(wxT("Nome do Pai"), wxLIST_FORMAT_LEFT, 0);
		//this->SetColumnWidth(7, wxLIST_AUTOSIZE);
		//this->SetColumnWidth(8, wxLIST_AUTOSIZE);
	}
}

void Tabela::modeloTabela(wxVector<Diretorio> diretorios,
	wxVector<Extensao> extensoes,
	wxGauge *barraProgresso) {
	wxImage icone;
	Diretorio dir;
	int nIndiceImagem;
	long nItem;

	this->ClearAll();
	modeloColunas();

	barraProgresso->SetRange(diretorios.size());
	barraProgresso->SetValue(0);
	
	for (unsigned int nLinha = 0; nLinha < diretorios.size(); nLinha++)	{
		dir = diretorios[nLinha];

		if (dir.getTipo().getCodigo() == 'D') {
			nItem = this->InsertItem(nLinha, dir.getNome(), 0);
			this->SetItemData(nItem, nLinha);
			this->SetItem(nItem, 1, "");
		}
		else {
			nIndiceImagem = ExtensaoBO::getInstancia()->indiceExtensao(
				extensoes, dir.getNome());

			if (nIndiceImagem == -1) {
				nIndiceImagem = 1;
			}

			nItem = this->InsertItem(nLinha, dir.getNome(), nIndiceImagem);
			this->SetItemData(nItem, nLinha);
			this->SetItem(nItem, 1, dir.getTamanhoFormatado());
		}
		this->SetItem(nItem, 2, dir.getTipo().getNome());
		this->SetItem(nItem, 3, dir.getModificadoFormatado());
		this->SetItem(nItem, 4, dir.getAtributos());
		this->SetItem(nItem, 5, dir.getCaminho());

		if (!bTabelaDir) {
			this->SetItem(nItem, 6, dir.getAba().getNome());
			this->SetItem(nItem, 7, Rotinas::IntToStr(dir.getAba().getCodigo()));
			this->SetItem(nItem, 8, dir.getNomePai());
		}

		barraProgresso->SetValue(barraProgresso->GetValue() + 1);
	}
	barraProgresso->SetValue(0);

}

bool Tabela::isSelecionado() {
	return this->IsSelected(this->GetFirstSelected());
}

void Tabela::selecionaLinha(int linha) {
	this->Select(linha, true);
}

void Tabela::deselecionaLinha(int linha) {
	this->Select(linha, false);
}

long Tabela::primeiraLinhaSelecionada() {
	int linha = this->GetFirstSelected();
	return linha;
}

void Tabela::limpar() {
	this->ClearAll();
	modeloColunas();
}

}
}
