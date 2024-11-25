#ifndef DIRETORIODAO_H
#define DIRETORIODAO_H

#pragma once

#include "hfsguardadir/objetos/Diretorio.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/comum/SQLite3Lib.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosdao {

class DiretorioDAO
{
private:
	DiretorioDAO();
	DiretorioDAO(DiretorioDAO const&);
	DiretorioDAO& operator=(DiretorioDAO const&);
	static DiretorioDAO* instancia;

	VOID fecharSqlPreparado(sqlite3_stmt* pstmt);
	Diretorio novoObjeto(sqlite3_stmt* pstmt);
	VOID atribuirCampos(sqlite3_stmt* pstmt, Diretorio obj);

public:
	static DiretorioDAO* getInstancia();

	int consultarTotal(const CString &sSQL, const CString &sCondicaoTotal);
	CList<Diretorio, Diretorio&>* consultarTudo(
		const CString &sSQL, const CString &sCondicaoTotal, IProgressoLog progressoLog);
	BOOL incluir(Diretorio obj);
	BOOL excluir(Aba aba, const CString &sCaminho);
	BOOL criarTabela();
};

}

}

#endif // DIRETORIODAO_H
