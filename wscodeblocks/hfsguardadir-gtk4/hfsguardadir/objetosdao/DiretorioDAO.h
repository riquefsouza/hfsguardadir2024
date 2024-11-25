#ifndef DIRETORIODAO_H
#define DIRETORIODAO_H

#include "../objetos/Diretorio.h"
#include "../comum/Rotinas.h"

void DiretorioDAO_fecharSqlPreparado(sqlite3_stmt* pstmt);
Diretorio DiretorioDAO_novoObjeto(sqlite3_stmt* pstmt);
int DiretorioDAO_consultarTotal(GString *sSQL, GString *sCondicaoTotal);
ListaDiretorio DiretorioDAO_consultarTudo(
	GString *sSQL, GString *sCondicaoTotal, IProgressoLog progressoLog);
void DiretorioDAO_atribuirCampos(sqlite3_stmt* pstmt, Diretorio obj);
gboolean DiretorioDAO_incluir(Diretorio obj);
gboolean DiretorioDAO_excluir(Aba aba, GString *sCaminho);
gboolean DiretorioDAO_criarTabela();

#endif
