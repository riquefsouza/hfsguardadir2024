#ifndef TABELA_H
#define TABELA_H

#include "resource.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/objetos/Diretorio.h"
#include "hfsguardadir/objetos/Extensao.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosgui {

class Tabela: public FXTable
{
	
private:		
	bool bTabelaDir;
	void definirColunas(int numRows);

public:	
	Tabela(FXComposite* p, bool bTabelaDir);
	Tabela(FXComposite* p, FXObject* tgt, FXSelector sel, FXuint opts, bool bTabelaDir);
	virtual ~Tabela();
	
	void limpar();
	void adicionaItem(int row, Diretorio dir, const std::vector<Extensao> &listaExtensao);
	void carregar(const std::vector<Diretorio> &listaDir,
		const std::vector<Extensao> &listaExtensao, FXProgressBar* barraProgresso);
	Diretorio getLinhaSelecionada();
	unsigned int encontrarCaminhoPorNome(const std::string &nome);
	
};

}
}

#endif
