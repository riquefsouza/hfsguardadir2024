#ifndef EXTENSAO_H
#define EXTENSAO_H

#include "hfsguardadir/comum/ListaString.h"

struct SExtensao {
    int codigo;
	String nome;
    int ordem;
	BITMAP bmp16;
	BITMAP bmp32;
};
typedef struct SExtensao Extensao;

struct SListaExtensao {
	unsigned int ordem;
	Extensao extensao;
	struct SListaExtensao *proximo;
};
typedef struct SListaExtensao *ListaExtensao;

Extensao* Extensao_new();
Extensao Extensao_copiar(Extensao extensao);
BOOL Extensao_comparar(Extensao extensao1, Extensao extensao2);

ListaExtensao ListaExtensao_aloca();
ListaExtensao ListaExtensao_inicia();
VOID ListaExtensao_libera(ListaExtensao *ls);
VOID ListaExtensao_insereFim(ListaExtensao *ls, Extensao extensao);
BOOL ListaExtensao_remove(ListaExtensao *ls, Extensao *extensao);
VOID ListaExtensao_arrumaOrdem(ListaExtensao *ls);
VOID ListaExtensao_removeItem(ListaExtensao *ls, Extensao extensao, BOOL bArrumaOrdem);
VOID ListaExtensao_removeItemOrd(ListaExtensao *ls, UINT ordem, BOOL bArrumaOrdem);
VOID ListaExtensao_removeTodos(ListaExtensao *ls);
BOOL ListaExtensao_pesquisaItem(ListaExtensao ls, Extensao extensao);
Extensao* ListaExtensao_pesquisaItemOrd(ListaExtensao ls, UINT ordem);
INT ListaExtensao_conta(ListaExtensao ls);

#endif
