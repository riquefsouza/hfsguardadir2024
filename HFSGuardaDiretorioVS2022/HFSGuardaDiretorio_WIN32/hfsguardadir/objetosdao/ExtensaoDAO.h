#ifndef EXTENSAODAO_H
#define EXTENSAODAO_H

#include "hfsguardadir/objetos/Extensao.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/comum/SQLite3Lib.h"

VOID ExtensaoDAO_fecharSqlPreparado(sqlite3_stmt* pstmt);
Extensao ExtensaoDAO_novoObjeto(sqlite3_stmt* pstmt);
int ExtensaoDAO_consultarTotal();
ListaExtensao ExtensaoDAO_consultarTudo(IProgressoLog progressoLog);
VOID ExtensaoDAO_atribuirCampos(sqlite3_stmt* pstmt, Extensao obj);
BOOL ExtensaoDAO_incluir(Extensao obj);
BOOL ExtensaoDAO_excluir(int codigo);
BOOL ExtensaoDAO_excluirTudo();
BOOL ExtensaoDAO_criarTabela();

#endif
