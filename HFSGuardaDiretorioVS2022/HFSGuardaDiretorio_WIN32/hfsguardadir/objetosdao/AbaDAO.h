#ifndef ABADAO_H
#define ABADAO_H

#include "hfsguardadir/objetos/Aba.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/comum/SQLite3Lib.h"

VOID AbaDAO_fecharSqlPreparado(sqlite3_stmt* pstmt);
Aba AbaDAO_novoObjeto(sqlite3_stmt* pstmt);
int AbaDAO_consultarTotal();
ListaAba AbaDAO_consultarTudo(IProgressoLog progressoLog);
VOID AbaDAO_atribuirCampos(sqlite3_stmt* pstmt, Aba obj);
BOOL AbaDAO_incluir(Aba obj);
BOOL AbaDAO_alterar(Aba obj);
BOOL AbaDAO_excluir(int codigo);
BOOL AbaDAO_criarTabela();

#endif
