#include "stdafx.h"

#include "Arquivo.h"
#include "hfsguardadir/comum/Rotinas.h"

Arquivo* Arquivo_new() {
	Arquivo *arquivo;
	arquivo = (Arquivo*)GlobalAlloc(GPTR, sizeof(struct SArquivo));

	return(arquivo);
}

Arquivo Arquivo_copiar(Arquivo arquivo) {
	Arquivo larquivo;
	larquivo.nome = String_copiar(arquivo.nome);
	larquivo.tamanho = arquivo.tamanho;
	larquivo.modificado = arquivo.modificado;
	larquivo.atributos = String_copiar(arquivo.atributos);

	return larquivo;
}

BOOL Arquivo_comparar(Arquivo arquivo1, Arquivo arquivo2) {
	return
		(String_comparar(arquivo1.nome, arquivo2.nome)
		&& arquivo1.tamanho == arquivo2.tamanho
		&& Rotinas_DataHoraComparar(arquivo1.modificado, arquivo2.modificado)
		&& String_comparar(arquivo1.atributos, arquivo2.atributos));
}

ListaArquivo ListaArquivo_aloca()
{
	ListaArquivo ls;
	ls = (ListaArquivo)GlobalAlloc(GPTR, sizeof(struct SListaArquivo));

	return(ls);
}

ListaArquivo ListaArquivo_inicia()
{
	return NULL;
}

VOID ListaArquivo_libera(ListaArquivo *ls)
{
	GlobalFree(*ls);
}

VOID ListaArquivo_insereFim(ListaArquivo *ls, Arquivo arquivo)
{
	ListaArquivo local, temp;

	local = ListaArquivo_aloca();
	local->ordem = 0;

	local->arquivo = Arquivo_copiar(arquivo);
	
	local->proximo = NULL;
	if (*ls == NULL)
		*ls = local;
	else {
		/* procura o ulitmo no */
		for (temp = *ls; temp->proximo != NULL; temp = temp->proximo);
		local->ordem = temp->ordem;
		local->ordem++;
		temp->proximo = local;
	}
}

BOOL ListaArquivo_remove(ListaArquivo *ls, Arquivo *arquivo)
{
	ListaArquivo local;

	if ((ls == NULL) || ((*ls)->proximo == NULL)) {
		// remoção nula
		return FALSE;
	}
	local = (*ls)->proximo;

	*arquivo = Arquivo_copiar(local->arquivo);

	(*ls)->proximo = local->proximo;
	ListaArquivo_libera(&local);
	return TRUE;
}

VOID ListaArquivo_arrumaOrdem(ListaArquivo *ls)
{
	ListaArquivo local;
	UINT nordem;

	nordem = 0;
	for (local = *ls; local != NULL; local = local->proximo) {
		local->ordem = nordem;
		nordem++;
	}
}

VOID ListaArquivo_removeItem(ListaArquivo *ls, Arquivo arquivo, BOOL bArrumaOrdem)
{
	ListaArquivo local, temp;

	Arquivo localarquivo;
	temp = NULL;
	local = *ls;
	while (local != NULL) {
		if (Arquivo_comparar(arquivo, local->arquivo)) {
			local = local->proximo;
			if (temp == NULL) {
				/* remove o primeiro no da lista */
				ListaArquivo_libera(ls);
				*ls = local;
			}
			else
				ListaArquivo_remove(&temp, &localarquivo);
		}
		else {
			temp = local;
			local = local->proximo;
		}
	}
	if (bArrumaOrdem)
		ListaArquivo_arrumaOrdem(ls);
}

VOID ListaArquivo_removeItemOrd(ListaArquivo *ls, UINT ordem, BOOL bArrumaOrdem)
{
	ListaArquivo local, temp;

	Arquivo localarquivo;
	temp = NULL;
	local = *ls;
	while (local != NULL) {
		if (local->ordem == ordem) {
			local = local->proximo;
			if (temp == NULL) {
				/* remove o primeiro no da lista */
				ListaArquivo_libera(ls);
				*ls = local;
			}
			else
				ListaArquivo_remove(&temp, &localarquivo);
		}
		else {
			temp = local;
			local = local->proximo;
		}
	}
	if (bArrumaOrdem)
		ListaArquivo_arrumaOrdem(ls);
}

VOID ListaArquivo_removeTodos(ListaArquivo *ls)
{
	INT ncont, ntotal;
	ntotal = ListaArquivo_conta(*ls);
	for (ncont = 0; ncont < ntotal; ncont++)
		ListaArquivo_removeItemOrd(ls, ncont, FALSE);
}

BOOL ListaArquivo_pesquisaItem(ListaArquivo ls, Arquivo arquivo)
{
	ListaArquivo local;

	for (local = ls; local != NULL; local = local->proximo) {
		if (Arquivo_comparar(local->arquivo, arquivo))
			return TRUE;
	}
	return FALSE;
}

Arquivo* ListaArquivo_pesquisaItemOrd(ListaArquivo ls, UINT ordem)
{
	ListaArquivo local;
	Arquivo* arquivo = Arquivo_new();

	for (local = ls; local != NULL; local = local->proximo) {
		if (local->ordem == ordem)
			return &(local->arquivo);
	}
	return arquivo;
}

INT ListaArquivo_conta(ListaArquivo ls)
{
	ListaArquivo local;
	INT ncont;
	ncont = 0;
	for (local = ls; local != NULL; local = local->proximo)
		ncont++;

	return ncont;
}
