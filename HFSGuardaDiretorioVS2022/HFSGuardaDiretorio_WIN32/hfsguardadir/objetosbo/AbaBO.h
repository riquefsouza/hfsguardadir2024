#ifndef ABABO_H
#define ABABO_H

#include "hfsguardadir/objetos/Aba.h"
#include "hfsguardadir/comum/Rotinas.h"

ListaAba AbaBO_carregarAba(IProgressoLog progressoLog);
int AbaBO_retMaxCodAba(ListaAba listaLocal);
String AbaBO_abaToSQL(Aba aba);
BOOL AbaBO_incluirAba(Aba aba);
BOOL AbaBO_alterarAba(Aba aba);
BOOL AbaBO_excluirAba(Aba aba);
BOOL AbaBO_criarTabelaAbas();
Aba* AbaBO_pegaAbaPorOrdem(ListaAba lista, int ordem);
Aba* AbaBO_getElemento(ListaAba lista, int codigo);
Aba* AbaBO_pegaAbaPorNome(ListaAba lista, String nome);

#endif
