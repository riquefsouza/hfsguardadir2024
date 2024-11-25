#ifndef DIRETORIO_H
#define DIRETORIO_H

#include "hfsguardadir/comum/ListaString.h"
#include "hfsguardadir/objetos/Aba.h"
#include "hfsguardadir/objetos/Arquivo.h"
#include "hfsguardadir/objetos/Tipo.h"

struct SDiretorio {
	Aba aba;
	Arquivo arquivo;
	int codigo;
	int ordem;
	int codDirPai;
	Tipo tipo;
	String caminho;
	String nomePai;
	String caminhoPai;
	String tamanhoFormatado;
	String modificadoFormatado;
	String caminhoOriginal;
};
typedef struct SDiretorio Diretorio;

struct SListaDiretorio {
	unsigned int ordem;
	Diretorio diretorio;
	struct SListaDiretorio *proximo;
};
typedef struct SListaDiretorio *ListaDiretorio;

Diretorio* Diretorio_new();
Diretorio Diretorio_copiar(Diretorio diretorio);
BOOL Diretorio_comparar(Diretorio diretorio1, Diretorio diretorio2);

ListaDiretorio ListaDiretorio_aloca();
ListaDiretorio ListaDiretorio_inicia();
VOID ListaDiretorio_libera(ListaDiretorio *ls);
VOID ListaDiretorio_insereFim(ListaDiretorio *ls, Diretorio diretorio);
BOOL ListaDiretorio_remove(ListaDiretorio *ls, Diretorio *diretorio);
VOID ListaDiretorio_arrumaOrdem(ListaDiretorio *ls);
VOID ListaDiretorio_removeItem(ListaDiretorio *ls, Diretorio diretorio, BOOL bArrumaOrdem);
VOID ListaDiretorio_removeItemOrd(ListaDiretorio *ls, UINT ordem, BOOL bArrumaOrdem);
VOID ListaDiretorio_removeTodos(ListaDiretorio *ls);
BOOL ListaDiretorio_pesquisaItem(ListaDiretorio ls, Diretorio diretorio);
Diretorio* ListaDiretorio_pesquisaItemOrd(ListaDiretorio ls, UINT ordem);
INT ListaDiretorio_conta(ListaDiretorio ls);

#endif
