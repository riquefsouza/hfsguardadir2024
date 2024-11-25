#include "stdafx.h"

#include "Aba.h"

Aba* Aba_new() {
	Aba *aba;
	aba = (Aba*)GlobalAlloc(GPTR, sizeof(struct SAba));

	return(aba);
}

Aba Aba_copiar(Aba aba) {
	Aba laba;

	laba.codigo = aba.codigo;
	laba.nome = String_copiar(aba.nome);
	laba.ordem = aba.ordem;

	return laba;
}

BOOL Aba_comparar(Aba aba1, Aba aba2) {
	return
		(aba1.codigo == aba2.codigo
		&& String_comparar(aba1.nome, aba2.nome)
		&& aba1.ordem == aba2.ordem);
}

ListaAba ListaAba_aloca()
{
	ListaAba ls;
	ls = (ListaAba)GlobalAlloc(GPTR, sizeof(struct SListaAba));

	return(ls);
}

ListaAba ListaAba_inicia()
{
	return NULL;
}

VOID ListaAba_libera(ListaAba *ls)
{
	GlobalFree(*ls);	
}

VOID ListaAba_insereFim(ListaAba *ls, Aba aba)
{
	ListaAba local, temp;

	local = ListaAba_aloca();
	local->ordem = 0;

	local->aba = Aba_copiar(aba);
	
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

BOOL ListaAba_remove(ListaAba *ls, Aba *aba)
{
	ListaAba local;

	if ((*ls == NULL) || ((*ls)->proximo == NULL)) {
		// remoção nula
		return FALSE;
	}
	local = (*ls)->proximo;

	*aba = Aba_copiar(local->aba);

	(*ls)->proximo = local->proximo;
	ListaAba_libera(&local);
	return TRUE;
}

VOID ListaAba_arrumaOrdem(ListaAba *ls)
{
	ListaAba local;
	UINT nordem;

	nordem = 0;
	for (local = *ls; local != NULL; local = local->proximo) {
		local->ordem = nordem;
		nordem++;
	}
}

VOID ListaAba_removeItem(ListaAba *ls, Aba aba, BOOL bArrumaOrdem)
{
	ListaAba local, temp;

	Aba localaba;
	temp = NULL;
	local = *ls;
	while (local != NULL) {
		if (Aba_comparar(aba, local->aba)) {
			local = local->proximo;
			if (temp == NULL) {
				/* remove o primeiro no da lista */
				ListaAba_libera(ls);
				*ls = local;
			}
			else
				ListaAba_remove(&temp, &localaba);
		}
		else {
			temp = local;
			local = local->proximo;
		}
	}
	if (bArrumaOrdem)
		ListaAba_arrumaOrdem(ls);
}

VOID ListaAba_removeItemOrd(ListaAba *ls, UINT ordem, BOOL bArrumaOrdem)
{
	ListaAba local, temp;

	Aba localaba;
	temp = NULL;
	local = *ls;
	while (local != NULL) {
		if (local->ordem == ordem) {
			local = local->proximo;
			if (temp == NULL) {
				/* remove o primeiro no da lista */
				ListaAba_libera(ls);
				*ls = local;
			}
			else
				ListaAba_remove(&temp, &localaba);
		}
		else {
			temp = local;
			local = local->proximo;
		}
	}
	if (bArrumaOrdem)
		ListaAba_arrumaOrdem(ls);
}

VOID ListaAba_removeTodos(ListaAba *ls)
{
	INT ncont, ntotal;
	ntotal = ListaAba_conta(*ls);
	for (ncont = 0; ncont < ntotal; ncont++)
		ListaAba_removeItemOrd(ls, ncont, FALSE);
}

BOOL ListaAba_pesquisaItem(ListaAba ls, Aba aba)
{
	ListaAba local;

	for (local = ls; local != NULL; local = local->proximo) {
		if (Aba_comparar(local->aba, aba))
			return TRUE;
	}
	return FALSE;
}

Aba* ListaAba_pesquisaItemOrd(ListaAba ls, UINT ordem)
{
	ListaAba local;
	Aba *aba = Aba_new();

	for (local = ls; local != NULL; local = local->proximo) {
		if (local->ordem == ordem)
			return &(local->aba);
	}
	return aba;
}

INT ListaAba_conta(ListaAba ls)
{
	ListaAba local;
	INT ncont;
	ncont = 0;
	for (local = ls; local != NULL; local = local->proximo)
		ncont++;

	return ncont;
}
