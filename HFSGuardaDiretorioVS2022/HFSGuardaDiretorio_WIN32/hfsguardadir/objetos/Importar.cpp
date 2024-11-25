#include "stdafx.h"

#include "Importar.h"

Importar* Importar_new() {
	Importar *importar;
	importar = (Importar*)GlobalAlloc(GPTR, sizeof(struct SImportar));

	return(importar);
}

Importar Importar_copiar(Importar importar) {
	Importar limportar;

	limportar.aba = importar.aba;
	limportar.codDirRaiz = importar.codDirRaiz;
	limportar.rotuloRaiz = String_copiar(importar.rotuloRaiz);
	limportar.nomeDirRaiz = String_copiar(importar.nomeDirRaiz);
	limportar.caminho = String_copiar(importar.caminho);

	return limportar;
}

BOOL Importar_comparar(Importar importar1, Importar importar2) {
	return
		(importar1.aba == importar2.aba
		&& importar1.codDirRaiz == importar2.codDirRaiz
		&& String_comparar(importar1.rotuloRaiz, importar2.rotuloRaiz) 
		&& String_comparar(importar1.nomeDirRaiz, importar2.nomeDirRaiz)
		&& String_comparar(importar1.caminho, importar2.caminho));
}

ListaImportar ListaImportar_aloca()
{
	ListaImportar ls;
	ls = (ListaImportar)GlobalAlloc(GPTR, sizeof(struct SListaImportar));

	return(ls);
}

ListaImportar ListaImportar_inicia()
{
	return NULL;
}

VOID ListaImportar_libera(ListaImportar *ls)
{
	GlobalFree(*ls);
}

VOID ListaImportar_insereFim(ListaImportar *ls, Importar importar)
{
	ListaImportar local, temp;

	local = ListaImportar_aloca();
	local->ordem = 0;

	local->importar = Importar_copiar(importar);
	
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

BOOL ListaImportar_remove(ListaImportar *ls, Importar *importar)
{
	ListaImportar local;

	if ((ls == NULL) || ((*ls)->proximo == NULL)) {
		// remoção nula
		return FALSE;
	}
	local = (*ls)->proximo;

	*importar = Importar_copiar(local->importar);

	(*ls)->proximo = local->proximo;
	ListaImportar_libera(&local);
	return TRUE;
}

VOID ListaImportar_arrumaOrdem(ListaImportar *ls)
{
	ListaImportar local;
	UINT nordem;

	nordem = 0;
	for (local = *ls; local != NULL; local = local->proximo) {
		local->ordem = nordem;
		nordem++;
	}
}

VOID ListaImportar_removeItem(ListaImportar *ls, Importar importar, BOOL bArrumaOrdem)
{
	ListaImportar local, temp;

	Importar localimportar;
	temp = NULL;
	local = *ls;
	while (local != NULL) {
		if (Importar_comparar(importar, local->importar)) {
			local = local->proximo;
			if (temp == NULL) {
				/* remove o primeiro no da lista */
				ListaImportar_libera(ls);
				*ls = local;
			}
			else
				ListaImportar_remove(&temp, &localimportar);
		}
		else {
			temp = local;
			local = local->proximo;
		}
	}
	if (bArrumaOrdem)
		ListaImportar_arrumaOrdem(ls);
}

VOID ListaImportar_removeItemOrd(ListaImportar *ls, UINT ordem, BOOL bArrumaOrdem)
{
	ListaImportar local, temp;

	Importar localimportar;
	temp = NULL;
	local = *ls;
	while (local != NULL) {
		if (local->ordem == ordem) {
			local = local->proximo;
			if (temp == NULL) {
				/* remove o primeiro no da lista */
				ListaImportar_libera(ls);
				*ls = local;
			}
			else
				ListaImportar_remove(&temp, &localimportar);
		}
		else {
			temp = local;
			local = local->proximo;
		}
	}
	if (bArrumaOrdem)
		ListaImportar_arrumaOrdem(ls);
}

VOID ListaImportar_removeTodos(ListaImportar *ls)
{
	INT ncont, ntotal;
	ntotal = ListaImportar_conta(*ls);
	for (ncont = 0; ncont < ntotal; ncont++)
		ListaImportar_removeItemOrd(ls, ncont, FALSE);
}

BOOL ListaImportar_pesquisaItem(ListaImportar ls, Importar importar)
{
	ListaImportar local;

	for (local = ls; local != NULL; local = local->proximo) {
		if (Importar_comparar(local->importar, importar))
			return TRUE;
	}
	return FALSE;
}

Importar* ListaImportar_pesquisaItemOrd(ListaImportar ls, UINT ordem)
{
	ListaImportar local;
	Importar *importar = Importar_new();

	for (local = ls; local != NULL; local = local->proximo) {
		if (local->ordem == ordem)
			return &(local->importar);
	}
	return importar;
}

INT ListaImportar_conta(ListaImportar ls)
{
	ListaImportar local;
	INT ncont;
	ncont = 0;
	for (local = ls; local != NULL; local = local->proximo)
		ncont++;

	return ncont;
}
