#ifndef ABABO_H
#define ABABO_H

#pragma once

#include "hfsguardadir/objetos/Aba.h"
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosbo {

class AbaBO
{
private:
	AbaBO();
	AbaBO(AbaBO const&);
	AbaBO& operator=(AbaBO const&);
	static AbaBO* instancia;

public:
	static AbaBO* getInstancia();

	CList<Aba, Aba&>* carregarAba(IProgressoLog progressoLog);
	int retMaxCodAba(const CList<Aba, Aba&> &listaLocal);
	CString abaToSQL(Aba aba);
	BOOL incluirAba(Aba aba);
	BOOL alterarAba(Aba aba);
	BOOL excluirAba(Aba aba);
	BOOL criarTabelaAbas();
	Aba* pegaAbaPorOrdem(const CList<Aba, Aba&> &lista, int ordem);
	Aba* getElemento(const CList<Aba, Aba&> &lista, int codigo);
	Aba* pegaAbaPorNome(const CList<Aba, Aba&> &lista, const CString &nome);

};

}
}

#endif // ABABO_H

