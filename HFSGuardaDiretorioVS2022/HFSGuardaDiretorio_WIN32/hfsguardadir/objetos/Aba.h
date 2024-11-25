#ifndef ABA_H
#define ABA_H

#include "hfsguardadir/comum/ListaString.h"

struct SAba {
    int codigo;
	String nome;
    int ordem;
};
typedef struct SAba Aba;

struct SListaAba {
	unsigned int ordem;
	Aba aba;
	struct SListaAba *proximo;
};
typedef struct SListaAba *ListaAba;

Aba* Aba_new();
Aba Aba_copiar(Aba aba);
BOOL Aba_comparar(Aba aba1, Aba aba2);

ListaAba ListaAba_aloca();
ListaAba ListaAba_inicia();
VOID ListaAba_libera(ListaAba *ls);
VOID ListaAba_insereFim(ListaAba *ls, Aba aba);
BOOL ListaAba_remove(ListaAba *ls, Aba *aba);
VOID ListaAba_arrumaOrdem(ListaAba *ls);
VOID ListaAba_removeItem(ListaAba *ls, Aba aba, BOOL bArrumaOrdem);
VOID ListaAba_removeItemOrd(ListaAba *ls, UINT ordem, BOOL bArrumaOrdem);
VOID ListaAba_removeTodos(ListaAba *ls);
BOOL ListaAba_pesquisaItem(ListaAba ls, Aba aba);
Aba* ListaAba_pesquisaItemOrd(ListaAba ls, UINT ordem);
INT ListaAba_conta(ListaAba ls);

#endif
