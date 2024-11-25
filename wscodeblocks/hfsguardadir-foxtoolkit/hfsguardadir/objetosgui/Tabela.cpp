#include "resource.h"
#include "hfsguardadir\objetosgui\Tabela.h"
#include "hfsguardadir/objetosbo/ExtensaoBO.h"

using namespace hfsguardadir::objetosbo;
using namespace hfsguardadir::objetosgui;

namespace hfsguardadir {

namespace objetosgui {

Tabela::Tabela(FXComposite* p, FXObject* tgt, FXSelector sel, FXuint opts, bool bTabelaDir) : FXTable(p, tgt, sel, opts)
{
	this->bTabelaDir = bTabelaDir;

	setTableStyle(TABLE_COL_SIZABLE | TABLE_READONLY);
	setEditable(false);
	setDefRowHeight(20);

	definirColunas(1);
}

Tabela::Tabela(FXComposite* p, bool bTabelaDir) : Tabela(p, nullptr, 0, 0, bTabelaDir)
{
}

Tabela::~Tabela()
{
}

void Tabela::definirColunas(int numRows) {
	setTableSize(numRows, 7);

	setColumnText(0, "Nome");
	setColumnWidth(0, 250);
		
	setColumnText(1, "Tamanho");	
	setColumnText(2, "Tipo");
	setColumnText(3, "Modificado");
	setColumnText(4, "Atributos");
	
	setColumnText(5, "Caminho");
	setColumnWidth(5, 750);

	if (!bTabelaDir) {
		setColumnText(6, "Aba");
	}
	else {
		setColumnWidth(6, 0);
	}
}

void Tabela::limpar() {
	//this->clearItems();
	for (int r = 0; r < this->getNumRows(); r++) {
		for (int c = 0; c < this->getNumColumns(); c++) {
			this->setItemText(r, c, "");
		}
	}
}

void Tabela::adicionaItem(int row, Diretorio dir, const std::vector<Extensao> &listaExtensao) {
	this->setItemText(row, 0, dir.getNome().c_str());
	
	if (dir.getTipo().getCodigo() == 'D') {
		//icone = ExtensaoBO::getInstancia()->DiretorioXPM;
		//FXBMPIcon* icone = new FXBMPIcon(getApp(), Fechar);
		//this->setItemIcon(row, 0, icone);
		this->setItemText(row, 1, "");		
	}
	else {
		/*
		icone = ExtensaoBO::getInstancia()->pixbufExtensao(listaExtensao, dir.getNome());
		if (icone == NULL) {
			icone = ExtensaoBO::getInstancia()->ArquivoXPM;
		}
		*/
		//FXBMPIcon* icone = new FXBMPIcon(getApp(), arquivo);
		//this->setItemIcon(row, 0, icone);
		this->setItemText(row, 1, dir.getTamanhoFormatado().c_str());
	}	
	this->setItemText(row, 2, dir.getTipo().getNome().c_str());
	this->setItemText(row, 3, dir.getModificadoFormatado().c_str());
	this->setItemText(row, 4, dir.getAtributos().c_str());
	this->setItemText(row, 5, dir.getCaminho().c_str());

	if (bTabelaDir) {
		this->setItemText(row, 6, "");
	}
	else {
		this->setItemText(row, 6, dir.getAba().getNome().c_str());
	}
	
	this->setItemJustify(row, 0, FXTableItem::LEFT);
	this->setItemJustify(row, 1, FXTableItem::LEFT);
	this->setItemJustify(row, 2, FXTableItem::LEFT);
	this->setItemJustify(row, 3, FXTableItem::LEFT);
	this->setItemJustify(row, 4, FXTableItem::LEFT);
	this->setItemJustify(row, 5, FXTableItem::LEFT);
	this->setItemJustify(row, 6, FXTableItem::LEFT);
}

void Tabela::carregar(const std::vector<Diretorio> &listaDir,
	const std::vector<Extensao> &listaExtensao, FXProgressBar* barraProgresso) {

	Diretorio dir;
	int nTamListaDir = (int)listaDir.size();

	definirColunas(nTamListaDir);

	this->limpar();

	barraProgresso->setProgress(0);

	for (unsigned int i = 0; i < nTamListaDir; i++) {
		dir = listaDir.at(i);

		adicionaItem(i, dir, listaExtensao);

		barraProgresso->setProgress(Rotinas::calculaProgresso((int)nTamListaDir, i));
	}
	barraProgresso->setProgress(0);
}

Diretorio Tabela::getLinhaSelecionada() {
	Diretorio dir;
	Tipo tipo;
	Aba aba;	
	int row = this->getCurrentRow();
	if (this->isRowSelected(row)){
		dir.setNome(this->getItem(row, 0)->getText().text());
		dir.setTamanhoFormatado(this->getItem(row, 1)->getText().text());
		tipo.setNome(this->getItem(row, 2)->getText().text());
			
		if (tipo.getNome() == Rotinas::getRecurso("TipoLista.diretorio")) {
			tipo.setCodigo('D');
		}
		else {
			tipo.setCodigo('A');
		}
		dir.setTipo(tipo);

		dir.setModificadoFormatado(this->getItem(row, 3)->getText().text());
		dir.setAtributos(this->getItem(row, 4)->getText().text());
		dir.setCaminho(this->getItem(row, 5)->getText().text());

		if (!bTabelaDir) {
			aba.setNome(this->getItem(row, 6)->getText().text());
		}
		dir.setAba(aba);
	}

	return dir;
}

unsigned int Tabela::encontrarCaminhoPorNome(const std::string &nome) {
	std::string valor;
	int row = 0;
	
	for (row = 0; row < this->getNumRows(); row++) {
		//for (unsigned int col = 0; col < this->getNumColumns(); col++) {
			valor = this->getItem(row, 0)->getText().text();

			if (valor == nome) {
				break;
			}
		//}
	}

	//return this->getItem(row, 0);
	return row;
}

}
}
