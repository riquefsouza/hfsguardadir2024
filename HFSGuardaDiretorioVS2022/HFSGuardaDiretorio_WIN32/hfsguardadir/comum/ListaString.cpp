#include "stdafx.h"

#include <windows.h>
#include <commctrl.h>

#include "ListaString.h"

/* Lista de strings */

ListaString ListaString_aloca()
{
	ListaString ls;
	ls = (ListaString) GlobalAlloc(GPTR, sizeof(struct nostr));
	
	return(ls);
}

ListaString ListaString_inicia() 
{
  return NULL;
}

VOID ListaString_libera(ListaString *ls)
{
	GlobalFree(*ls);
}

VOID ListaString_insereFim(ListaString *ls, String str)
{
	ListaString local, temp;

	local = ListaString_aloca();
	local->ordem = 0;
	local->str = String_copiar(str);
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

BOOL ListaString_remove(ListaString *ls, String *str)
{
	ListaString local;

	if ((ls == NULL) || ((*ls)->proximo == NULL)) {
		// remoção nula
		return FALSE;
	}
	local = (*ls)->proximo;

	*str = local->str;
	(*ls)->proximo = local->proximo;
	ListaString_libera(&local);
	return TRUE;
}

VOID ListaString_arrumaOrdem(ListaString *ls)
{
ListaString local;
UINT nordem;

  nordem = 0;
  for (local = *ls; local != NULL; local = local->proximo) {
	local->ordem = nordem;
	nordem++;
  }
}

VOID ListaString_removeItem(ListaString *ls, String str, BOOL bArrumaOrdem)
{
	ListaString local, temp;

	String localstr;
	temp = NULL;
	local = *ls;
	while (local != NULL) {	
		if (String_comparar(str, local->str)){
			local = local->proximo;
			if (temp == NULL){
				/* remove o primeiro no da lista */
				ListaString_libera(ls);
				*ls = local;
			} else
				ListaString_remove(&temp, &localstr);
		} else {
			temp = local;
			local = local->proximo;
		}
	}
	if (bArrumaOrdem)	
  	ListaString_arrumaOrdem(ls);
}

VOID ListaString_removeItemOrd(ListaString *ls, UINT ordem, BOOL bArrumaOrdem)
{
	ListaString local, temp;

	String localstr;
	temp = NULL;
	local = *ls;
	while (local != NULL) {	
		if (local->ordem == ordem){
			local = local->proximo;
			if (temp == NULL){
				/* remove o primeiro no da lista */
				ListaString_libera(ls);
				*ls = local;
			} else
				ListaString_remove(&temp, &localstr);
		} else {
			temp = local;
			local = local->proximo;
		}
	}
	if (bArrumaOrdem)
  		ListaString_arrumaOrdem(ls);
}

VOID ListaString_removeTodos(ListaString *ls)
{ 
	INT ncont, ntotal;
	ntotal = ListaString_conta(*ls);  
	for (ncont=0; ncont < ntotal; ncont++)
		ListaString_removeItemOrd(ls, ncont, FALSE);
}

BOOL ListaString_pesquisaItem(ListaString ls, String str)
{
	ListaString local;

	for (local = ls; local != NULL; local = local->proximo) {
		if (String_comparar(local->str, str))
			return TRUE;
	}
	return FALSE;
}

String ListaString_pesquisaItemOrd(ListaString ls, UINT ordem)
{
	ListaString local;  

	for (local = ls; local != NULL; local = local->proximo) {
		if (local->ordem == ordem)
			return local->str;
	}
	return String_limpar();
}

INT ListaString_conta(ListaString ls)
{
	ListaString local;
	INT ncont;
	ncont = 0;
	for (local = ls; local != NULL; local = local->proximo)
		ncont++;

	return ncont;
}

VOID ListaString_inverter(ListaString *ls) {
	ListaString local = ListaString_inicia();
	int nordem, ntotal = ListaString_conta(*ls);
	String item;

	if (ntotal > 1) {
		nordem = ntotal - 1;
		while (nordem >= 0) {
			item = ListaString_pesquisaItemOrd(*ls, nordem);
			ListaString_insereFim(&local, item);
			nordem--;
		}
		*ls = local;
	}
}

/* Lista de array de strings */

ListaMString ListaString_alocaM()
{
	ListaMString ls;
	ls = (ListaMString) GlobalAlloc(GPTR, sizeof(struct nomstr));
	
	return(ls);
}

ListaMString ListaString_iniciaM()
{
  return NULL;
}

VOID ListaString_liberaM(ListaMString *ls)
{
	GlobalFree(*ls);
}

VOID ListaString_insereFimM(ListaMString *ls, String str, UINT nColuna)
{
	ListaMString local, temp;

	local = ListaString_alocaM();
	local->ordem = 0;
	local->str[nColuna] = String_copiar(str);
	local->proximo = NULL;
	if (*ls == NULL) {
		*ls = local;
	}
	else {
		// procura o ultimo no
		for (temp = *ls; temp->proximo != NULL; temp = temp->proximo);
		local->ordem = temp->ordem;
		local->ordem++;
		temp->proximo = local;
	}
}

BOOL ListaString_removeM(ListaMString *ls, String *str, UINT nColuna)
{
	ListaMString local;
	
	if ((ls == NULL) || ((*ls)->proximo == NULL)) {
		// remoção nula
		return FALSE;
	}
	local = (*ls)->proximo;
	*str = local->str[nColuna];
	(*ls)->proximo = local->proximo;
	ListaString_liberaM(&local);
	return TRUE;
}

VOID ListaString_arrumaOrdemM(ListaMString *ls)
{
ListaMString local;
UINT nordem;

  nordem = 0;
  for (local = *ls; local != NULL; local = local->proximo) {
    local->ordem = nordem;
 	  nordem++;
  }
}

VOID ListaString_removeItemM(ListaMString *ls, String str, UINT nQtdColuna, BOOL bArrumaOrdem)
{
	ListaMString local, temp;
	UINT nColuna;
	String localstr;
	temp = NULL;
	local = *ls;
	while (local != NULL) {	
		for (nColuna = 0; nColuna < nQtdColuna; nColuna++){
			if (String_comparar(str, local->str[nColuna])){
				local = local->proximo;
				if (temp == NULL){
					/* remove o primeiro no da lista */
					ListaString_liberaM(ls);
					*ls = local;
				} else
					ListaString_removeM(&temp, &localstr, nColuna);
			} else {
				temp = local;
				local = local->proximo;
			}
		}
	}
	if (bArrumaOrdem)
  		ListaString_arrumaOrdemM(ls);
}

VOID ListaString_removeItemOrdM(ListaMString *ls, UINT ordem, UINT nQtdColuna, BOOL bArrumaOrdem)
{
	ListaMString local, temp;

	String localstr;
	temp = NULL;
	local = *ls;
	while (local != NULL) {	
		if (local->ordem == ordem){
			local = local->proximo;
			if (temp == NULL){
				/* remove o primeiro no da lista */
				ListaString_liberaM(ls);
				*ls = local;
			}
			else
				ListaString_removeM(&temp, &localstr, nQtdColuna);
		} else {
			temp = local;
			local = local->proximo;
		}
	}
	if (bArrumaOrdem)
  	ListaString_arrumaOrdemM(ls);
}

VOID ListaString_removeTodosM(ListaMString *ls, UINT nQtdColuna)
{ 
	INT ncont, ntotal;
  ntotal = ListaString_contaM(*ls);
  for (ncont=0; ncont < ntotal; ncont++)
    ListaString_removeItemOrdM(ls, ncont, nQtdColuna, FALSE);
}

BOOL ListaString_pesquisaItemM(ListaMString ls, String str, UINT nQtdColuna)
{
	ListaMString local;
	UINT ncont;
	for (local = ls; local != NULL; local = local->proximo) {
		for (ncont = 0; ncont < nQtdColuna; ncont++) {
			if (String_comparar(local->str[ncont], str))
				return TRUE;
		}
	}
	return FALSE;
}

String ListaString_pesquisaItemOrdM(ListaMString ls, UINT nColuna, UINT ordem)
{
	ListaMString local;

	for (local = ls; local != NULL; local = local->proximo) {
		if (local->ordem == ordem)
			return local->str[nColuna];
	}
	return String_limpar();
}

INT ListaString_contaM(ListaMString ls)
{
	ListaMString local;
	INT ncont;
	ncont = 0;
	for (local = ls; local != NULL; local = local->proximo)
		ncont++;

	return ncont;
}

