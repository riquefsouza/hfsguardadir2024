#ifndef ABABO_H
#define ABABO_H

#include "hfsguardadir/objetos/Aba.h"
#include "hfsguardadir/comum/Rotinas.h"

ListaAba AbaBO_carregarAba(IProgressoLog progressoLog);
int AbaBO_retMaxCodAba(ListaAba listaLocal);
GString* AbaBO_abaToSQL(Aba aba);
gboolean AbaBO_incluirAba(Aba aba);
gboolean AbaBO_alterarAba(Aba aba);
gboolean AbaBO_excluirAba(Aba aba);
gboolean AbaBO_criarTabelaAbas();
Aba AbaBO_pegaAbaPorOrdem(ListaAba lista, int ordem);
Aba AbaBO_getElemento(ListaAba lista, int codigo);
Aba AbaBO_pegaAbaPorNome(ListaAba lista, GString *nome);

#endif
