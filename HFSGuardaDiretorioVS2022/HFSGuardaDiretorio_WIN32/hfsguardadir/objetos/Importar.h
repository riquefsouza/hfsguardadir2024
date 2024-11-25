#ifndef IMPORTAR_H
#define IMPORTAR_H

#include "hfsguardadir/comum/ListaString.h"

struct SImportar {
    int aba;
	int codDirRaiz;
	String rotuloRaiz;
	String nomeDirRaiz;
	String caminho;
};
typedef struct SImportar Importar;

struct SListaImportar {
	unsigned int ordem;
	Importar importar;
	struct SListaImportar *proximo;
};
typedef struct SListaImportar *ListaImportar;

Importar* Importar_new();
Importar Importar_copiar(Importar importar);
BOOL Importar_comparar(Importar importar1, Importar importar2);

ListaImportar ListaImportar_aloca();
ListaImportar ListaImportar_inicia();
VOID ListaImportar_libera(ListaImportar *ls);
VOID ListaImportar_insereFim(ListaImportar *ls, Importar importar);
BOOL ListaImportar_remove(ListaImportar *ls, Importar *importar);
VOID ListaImportar_arrumaOrdem(ListaImportar *ls);
VOID ListaImportar_removeItem(ListaImportar *ls, Importar importar, BOOL bArrumaOrdem);
VOID ListaImportar_removeItemOrd(ListaImportar *ls, UINT ordem, BOOL bArrumaOrdem);
VOID ListaImportar_removeTodos(ListaImportar *ls);
BOOL ListaImportar_pesquisaItem(ListaImportar ls, Importar importar);
Importar* ListaImportar_pesquisaItemOrd(ListaImportar ls, UINT ordem);
INT ListaImportar_conta(ListaImportar ls);

#endif
