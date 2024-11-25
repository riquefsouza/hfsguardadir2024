#ifndef ABADAO_H
#define ABADAO_H

#pragma once

#include "hfsguardadir/objetos/Aba.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/comum/SQLite3Lib.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosdao {
	
class AbaDAO
{
private:
	AbaDAO();
	AbaDAO(AbaDAO const&);
	AbaDAO& operator=(AbaDAO const&);
	static AbaDAO* instancia;

	VOID fecharSqlPreparado(sqlite3_stmt* pstmt);
	Aba novoObjeto(sqlite3_stmt* pstmt);
	VOID atribuirCampos(sqlite3_stmt* pstmt, Aba obj);
	int consultarTotal();

public:
	static AbaDAO* getInstancia();

	CList<Aba, Aba&>* consultarTudo(IProgressoLog progressoLog);
	BOOL incluir(Aba obj);
	BOOL alterar(Aba obj);
	BOOL excluir(int codigo);
	BOOL criarTabela();

};

}
}

#endif

