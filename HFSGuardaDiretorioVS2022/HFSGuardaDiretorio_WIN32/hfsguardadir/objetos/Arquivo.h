#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "hfsguardadir/comum/ListaString.h"

struct SArquivo {
	String nome;
	unsigned long long tamanho;
	SYSTEMTIME modificado;
	String atributos;
};
typedef struct SArquivo Arquivo;

struct SListaArquivo {
	unsigned int ordem;
	Arquivo arquivo;
	struct SListaArquivo *proximo;
};
typedef struct SListaArquivo *ListaArquivo;

Arquivo* Arquivo_new();
Arquivo Arquivo_copiar(Arquivo arquivo);
BOOL Arquivo_comparar(Arquivo arquivo1, Arquivo arquivo2);

ListaArquivo ListaArquivo_aloca();
ListaArquivo ListaArquivo_inicia();
VOID ListaArquivo_libera(ListaArquivo *ls);
VOID ListaArquivo_insereFim(ListaArquivo *ls, Arquivo arquivo);
BOOL ListaArquivo_remove(ListaArquivo *ls, Arquivo *arquivo);
VOID ListaArquivo_arrumaOrdem(ListaArquivo *ls);
VOID ListaArquivo_removeItem(ListaArquivo *ls, Arquivo arquivo, BOOL bArrumaOrdem);
VOID ListaArquivo_removeItemOrd(ListaArquivo *ls, UINT ordem, BOOL bArrumaOrdem);
VOID ListaArquivo_removeTodos(ListaArquivo *ls);
BOOL ListaArquivo_pesquisaItem(ListaArquivo ls, Arquivo arquivo);
Arquivo* ListaArquivo_pesquisaItemOrd(ListaArquivo ls, UINT ordem);
INT ListaArquivo_conta(ListaArquivo ls);

#endif
