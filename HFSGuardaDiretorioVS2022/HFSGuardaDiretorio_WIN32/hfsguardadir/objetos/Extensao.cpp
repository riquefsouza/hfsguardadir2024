#include "stdafx.h"

#include "Extensao.h"

Extensao* Extensao_new() {
	Extensao *extensao;
	extensao = (Extensao*)GlobalAlloc(GPTR, sizeof(struct SExtensao));

	return(extensao);
}

Extensao Extensao_copiar(Extensao extensao) {
	Extensao lextensao;
	lextensao.codigo = extensao.codigo;
	lextensao.nome = String_copiar(extensao.nome);
	lextensao.ordem = extensao.ordem;
	lextensao.bmp16 = extensao.bmp16;
	lextensao.bmp32 = extensao.bmp32;

	return lextensao;
}

BOOL Extensao_comparar(Extensao extensao1, Extensao extensao2) {
	return
		(extensao1.codigo == extensao2.codigo
		&& String_comparar(extensao1.nome, extensao2.nome)
		&& extensao1.ordem == extensao2.ordem);
}

ListaExtensao ListaExtensao_aloca()
{
	ListaExtensao ls;
	ls = (ListaExtensao)GlobalAlloc(GPTR, sizeof(struct SListaExtensao));

	return(ls);
}

ListaExtensao ListaExtensao_inicia()
{
	return NULL;
}

VOID ListaExtensao_libera(ListaExtensao *ls)
{
	GlobalFree(*ls);
}

VOID ListaExtensao_insereFim(ListaExtensao *ls, Extensao extensao)
{
	ListaExtensao local, temp;

	local = ListaExtensao_aloca();
	local->ordem = 0;

	local->extensao = Extensao_copiar(extensao);
	
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

BOOL ListaExtensao_remove(ListaExtensao *ls, Extensao *extensao)
{
	ListaExtensao local;

	if ((ls == NULL) || ((*ls)->proximo == NULL)) {
		// remoção nula
		return FALSE;
	}
	local = (*ls)->proximo;

	*extensao = Extensao_copiar(local->extensao);

	(*ls)->proximo = local->proximo;
	ListaExtensao_libera(&local);
	return TRUE;
}

VOID ListaExtensao_arrumaOrdem(ListaExtensao *ls)
{
	ListaExtensao local;
	UINT nordem;

	nordem = 0;
	for (local = *ls; local != NULL; local = local->proximo) {
		local->ordem = nordem;
		nordem++;
	}
}

VOID ListaExtensao_removeItem(ListaExtensao *ls, Extensao extensao, BOOL bArrumaOrdem)
{
	ListaExtensao local, temp;

	Extensao localextensao;
	temp = NULL;
	local = *ls;
	while (local != NULL) {
		if (Extensao_comparar(extensao, local->extensao)) {
			local = local->proximo;
			if (temp == NULL) {
				/* remove o primeiro no da lista */
				ListaExtensao_libera(ls);
				*ls = local;
			}
			else
				ListaExtensao_remove(&temp, &localextensao);
		}
		else {
			temp = local;
			local = local->proximo;
		}
	}
	if (bArrumaOrdem)
		ListaExtensao_arrumaOrdem(ls);
}

VOID ListaExtensao_removeItemOrd(ListaExtensao *ls, UINT ordem, BOOL bArrumaOrdem)
{
	ListaExtensao local, temp;

	Extensao localextensao;
	temp = NULL;
	local = *ls;
	while (local != NULL) {
		if (local->ordem == ordem) {
			local = local->proximo;
			if (temp == NULL) {
				/* remove o primeiro no da lista */
				ListaExtensao_libera(ls);
				*ls = local;
			}
			else
				ListaExtensao_remove(&temp, &localextensao);
		}
		else {
			temp = local;
			local = local->proximo;
		}
	}
	if (bArrumaOrdem)
		ListaExtensao_arrumaOrdem(ls);
}

VOID ListaExtensao_removeTodos(ListaExtensao *ls)
{
	INT ncont, ntotal;
	ntotal = ListaExtensao_conta(*ls);
	for (ncont = 0; ncont < ntotal; ncont++)
		ListaExtensao_removeItemOrd(ls, ncont, FALSE);
}

BOOL ListaExtensao_pesquisaItem(ListaExtensao ls, Extensao extensao)
{
	ListaExtensao local;

	for (local = ls; local != NULL; local = local->proximo) {
		if (Extensao_comparar(local->extensao, extensao))
			return TRUE;
	}
	return FALSE;
}

Extensao* ListaExtensao_pesquisaItemOrd(ListaExtensao ls, UINT ordem)
{
	ListaExtensao local;
	Extensao *extensao = Extensao_new();

	for (local = ls; local != NULL; local = local->proximo) {
		if (local->ordem == ordem)
			return &(local->extensao);
	}
	return extensao;
}

INT ListaExtensao_conta(ListaExtensao ls)
{
	ListaExtensao local;
	INT ncont;
	ncont = 0;
	for (local = ls; local != NULL; local = local->proximo)
		ncont++;

	return ncont;
}
