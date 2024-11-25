#ifndef EXTENSAODAO_H
#define EXTENSAODAO_H

#pragma once

#include "hfsguardadir/objetos/Extensao.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/comum/SQLite3Lib.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosdao {

class ExtensaoDAO
{
private:
	ExtensaoDAO();
	ExtensaoDAO(ExtensaoDAO const&);
	ExtensaoDAO& operator=(ExtensaoDAO const&);
	static ExtensaoDAO* instancia;

	VOID fecharSqlPreparado(sqlite3_stmt* pstmt);
	Extensao novoObjeto(sqlite3_stmt* pstmt);
	int consultarTotal();
	VOID atribuirCampos(sqlite3_stmt* pstmt, Extensao obj);

public:
	static ExtensaoDAO* getInstancia();

	CList<Extensao, Extensao&>* consultarTudo(IProgressoLog progressoLog);
	BOOL incluir(Extensao obj);
	BOOL excluir(int codigo);
	BOOL excluirTudo();
	BOOL criarTabela();

};

}
}

#endif // EXTENSAODAO_H

