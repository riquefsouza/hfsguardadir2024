#ifndef DIRETORIODAO_H
#define DIRETORIODAO_H

#include "hfsguardadir/objetos/Diretorio.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/comum/SQLite3Lib.h"

VOID DiretorioDAO_fecharSqlPreparado(sqlite3_stmt* pstmt);
Diretorio DiretorioDAO_novoObjeto(sqlite3_stmt* pstmt);
int DiretorioDAO_consultarTotal(String sSQL, String sCondicaoTotal);
ListaDiretorio DiretorioDAO_consultarTudo(
	String sSQL, String sCondicaoTotal, IProgressoLog progressoLog);
VOID DiretorioDAO_atribuirCampos(sqlite3_stmt* pstmt, Diretorio obj);
BOOL DiretorioDAO_incluir(Diretorio obj);
BOOL DiretorioDAO_excluir(Aba aba, String sCaminho);
BOOL DiretorioDAO_criarTabela();

#endif
