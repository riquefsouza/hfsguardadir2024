#ifndef TABELA_H
#define TABELA_H

#include "../comum/Rotinas.h"
#include "../objetos/Diretorio.h"
#include "../objetos/Extensao.h"

void Tabela_cria(gboolean bTabelaDir, GtkTreeView *tabela);
void Tabela_limpar(GtkTreeView* tabela);
void Tabela_adicionaItem(GtkTreeView* tabela, gboolean bTabelaDir, Diretorio dir,
	ListaExtensao listaExtensao);
void Tabela_carregar(GtkTreeView* tabela, gboolean bTabelaDir, ListaDiretorio listaDir,
	ListaExtensao listaExtensao, GtkProgressBar* barraProgresso);
Diretorio Tabela_getLinhaSelecionada(GtkTreeView* tabela, gboolean bTabelaDir);
GtkTreePath* Tabela_encontrarCaminhoPorNome(GtkTreeView* tabela, GString* nome);

#endif
