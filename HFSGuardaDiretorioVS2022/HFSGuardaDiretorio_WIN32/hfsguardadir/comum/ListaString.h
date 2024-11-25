#ifndef LISTASTRING_H
#define LISTASTRING_H

#include "hfsguardadir\comum\String.h"

#define QTD_MAX_COL 10

struct nostr {
	unsigned int ordem;
	String str;
	struct nostr *proximo;
};
typedef struct nostr *ListaString;

struct nomstr {
	unsigned int ordem;
	String str[QTD_MAX_COL];
	struct nomstr *proximo;
};
typedef struct nomstr *ListaMString;

ListaString ListaString_aloca();
ListaString ListaString_inicia();
VOID ListaString_libera(ListaString *ls);
VOID ListaString_insereFim(ListaString *ls, String str);
BOOL ListaString_remove(ListaString *ls, String *str);
VOID ListaString_arrumaOrdem(ListaString *ls);
VOID ListaString_removeItem(ListaString *ls, String str, BOOL bArrumaOrdem);
VOID ListaString_removeItemOrd(ListaString *ls, UINT ordem, BOOL bArrumaOrdem);
VOID ListaString_removeTodos(ListaString *ls);
BOOL ListaString_pesquisaItem(ListaString ls, String str);
String ListaString_pesquisaItemOrd(ListaString ls, UINT ordem);
INT ListaString_conta(ListaString ls);
VOID ListaString_inverter(ListaString *ls);

ListaMString ListaString_alocaM();
ListaMString ListaString_iniciaM();
VOID ListaString_liberaM(ListaMString *ls);
VOID ListaString_insereFimM(ListaMString *ls, String str, UINT nColuna);
BOOL ListaString_removeM(ListaMString *ls, String *str, UINT nColuna);
VOID ListaString_arrumaOrdemM(ListaMString *ls);
VOID ListaString_removeItemM(ListaMString *ls, String str, UINT nQtdColuna, BOOL bArrumaOrdem);
VOID ListaString_removeItemOrdM(ListaMString *ls, UINT ordem, UINT nQtdColuna, BOOL bArrumaOrdem);
VOID ListaString_removeTodosM(ListaMString *ls, UINT nQtdColuna);
BOOL ListaString_pesquisaItemM(ListaMString ls, String str, UINT nQtdColuna);
String ListaString_pesquisaItemOrdM(ListaMString ls, UINT nColuna, UINT ordem);
INT ListaString_contaM(ListaMString ls);

#endif


