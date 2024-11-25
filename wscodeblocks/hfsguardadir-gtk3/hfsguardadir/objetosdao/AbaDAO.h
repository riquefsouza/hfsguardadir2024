#ifndef ABADAO_H
#define ABADAO_H

#include "../objetos/Aba.h"
#include "../comum/Rotinas.h"

void AbaDAO_fecharSqlPreparado(sqlite3_stmt* pstmt);
Aba AbaDAO_novoObjeto(sqlite3_stmt* pstmt);
int AbaDAO_consultarTotal();
ListaAba AbaDAO_consultarTudo(IProgressoLog progressoLog);
void AbaDAO_atribuirCampos(sqlite3_stmt* pstmt, Aba obj);
gboolean AbaDAO_incluir(Aba obj);
gboolean AbaDAO_alterar(Aba obj);
gboolean AbaDAO_excluir(int codigo);
gboolean AbaDAO_criarTabela();

#endif
