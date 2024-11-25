#ifndef EXTENSAODAO_H
#define EXTENSAODAO_H

#include "hfsguardadir/objetos/Extensao.h"
#include "hfsguardadir/comum/Rotinas.h"

void ExtensaoDAO_fecharSqlPreparado(sqlite3_stmt* pstmt);
Extensao ExtensaoDAO_novoObjeto(sqlite3_stmt* pstmt);
int ExtensaoDAO_consultarTotal();
ListaExtensao ExtensaoDAO_consultarTudo(IProgressoLog progressoLog);
void ExtensaoDAO_atribuirCampos(sqlite3_stmt* pstmt, Extensao obj);
gboolean ExtensaoDAO_incluir(Extensao obj);
gboolean ExtensaoDAO_excluir(int codigo);
gboolean ExtensaoDAO_excluirTudo();
gboolean ExtensaoDAO_criarTabela();

#endif
