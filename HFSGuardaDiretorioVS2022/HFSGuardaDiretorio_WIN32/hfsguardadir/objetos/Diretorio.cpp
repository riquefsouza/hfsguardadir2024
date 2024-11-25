#include "stdafx.h"

#include "Diretorio.h"

Diretorio* Diretorio_new() {
	Diretorio *diretorio;
	diretorio = (Diretorio*)GlobalAlloc(GPTR, sizeof(struct SDiretorio));

	return(diretorio);
}

Diretorio Diretorio_copiar(Diretorio diretorio) {
	Diretorio ldiretorio;

	ldiretorio.aba = Aba_copiar(diretorio.aba);
	ldiretorio.arquivo = Arquivo_copiar(diretorio.arquivo);
	ldiretorio.codigo = diretorio.codigo;
	ldiretorio.ordem = diretorio.ordem;
	ldiretorio.codDirPai = diretorio.codDirPai;
	ldiretorio.tipo = Tipo_copiar(diretorio.tipo);
	ldiretorio.caminho = String_copiar(diretorio.caminho);
	ldiretorio.nomePai = String_copiar(diretorio.nomePai);
	ldiretorio.caminhoPai = String_copiar(diretorio.caminhoPai);
	ldiretorio.tamanhoFormatado = String_copiar(diretorio.tamanhoFormatado);
	ldiretorio.modificadoFormatado = String_copiar(diretorio.modificadoFormatado);
	ldiretorio.caminhoOriginal = String_copiar(diretorio.caminhoOriginal);
	
	return ldiretorio;
}

BOOL Diretorio_comparar(Diretorio diretorio1, Diretorio diretorio2) {
	return
		(Aba_comparar(diretorio1.aba, diretorio2.aba)
		//&& Arquivo_comparar(diretorio1.arquivo, diretorio2.arquivo)
		&& diretorio1.codigo == diretorio2.codigo
		&& diretorio1.ordem == diretorio2.ordem
		//&& diretorio1.codDirPai == diretorio2.codDirPai
		//&& Tipo_comparar(diretorio1.tipo, diretorio2.tipo)
		//&& String_comparar(diretorio1.caminho, diretorio2.caminho)
		//&& String_comparar(diretorio1.nomePai, diretorio2.nomePai)
		//&& String_comparar(diretorio1.tamanhoFormatado, diretorio2.tamanhoFormatado)
		//&& String_comparar(diretorio1.modificadoFormatado, diretorio2.modificadoFormatado)
		//&& String_comparar(diretorio1.caminhoOriginal, diretorio2.caminhoOriginal)
			);
}

ListaDiretorio ListaDiretorio_aloca()
{
	ListaDiretorio ls;
	ls = (ListaDiretorio)GlobalAlloc(GPTR, sizeof(struct SListaDiretorio));

	return(ls);
}

ListaDiretorio ListaDiretorio_inicia()
{
	return NULL;
}

VOID ListaDiretorio_libera(ListaDiretorio *ls)
{
	GlobalFree(*ls);
}

VOID ListaDiretorio_insereFim(ListaDiretorio *ls, Diretorio diretorio)
{
	ListaDiretorio local, temp;

	local = ListaDiretorio_aloca();
	local->ordem = 0;

	local->diretorio = Diretorio_copiar(diretorio);
	
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

BOOL ListaDiretorio_remove(ListaDiretorio *ls, Diretorio *diretorio)
{
	ListaDiretorio local;

	if ((ls == NULL) || ((*ls)->proximo == NULL)) {
		// remoção nula
		return FALSE;
	}
	local = (*ls)->proximo;

	*diretorio = Diretorio_copiar(local->diretorio);

	(*ls)->proximo = local->proximo;
	ListaDiretorio_libera(&local);
	return TRUE;
}

VOID ListaDiretorio_arrumaOrdem(ListaDiretorio *ls)
{
	ListaDiretorio local;
	UINT nordem;

	nordem = 0;
	for (local = *ls; local != NULL; local = local->proximo) {
		local->ordem = nordem;
		nordem++;
	}
}

VOID ListaDiretorio_removeItem(ListaDiretorio *ls, Diretorio diretorio, BOOL bArrumaOrdem)
{
	ListaDiretorio local, temp;

	Diretorio localdiretorio;
	temp = NULL;
	local = *ls;
	while (local != NULL) {
		if (Diretorio_comparar(diretorio, local->diretorio)) {
			local = local->proximo;
			if (temp == NULL) {
				/* remove o primeiro no da lista */
				ListaDiretorio_libera(ls);
				*ls = local;
			}
			else
				ListaDiretorio_remove(&temp, &localdiretorio);
		}
		else {
			temp = local;
			local = local->proximo;
		}
	}
	if (bArrumaOrdem)
		ListaDiretorio_arrumaOrdem(ls);
}

VOID ListaDiretorio_removeItemOrd(ListaDiretorio *ls, UINT ordem, BOOL bArrumaOrdem)
{
	ListaDiretorio local, temp;

	Diretorio localdiretorio;
	temp = NULL;
	local = *ls;
	while (local != NULL) {
		if (local->ordem == ordem) {
			local = local->proximo;
			if (temp == NULL) {
				/* remove o primeiro no da lista */
				ListaDiretorio_libera(ls);
				*ls = local;
			}
			else
				ListaDiretorio_remove(&temp, &localdiretorio);
		}
		else {
			temp = local;
			local = local->proximo;
		}
	}
	if (bArrumaOrdem)
		ListaDiretorio_arrumaOrdem(ls);
}

VOID ListaDiretorio_removeTodos(ListaDiretorio *ls)
{
	INT ncont, ntotal;
	ntotal = ListaDiretorio_conta(*ls);
	for (ncont = 0; ncont < ntotal; ncont++)
		ListaDiretorio_removeItemOrd(ls, ncont, FALSE);
}

BOOL ListaDiretorio_pesquisaItem(ListaDiretorio ls, Diretorio diretorio)
{
	ListaDiretorio local;

	for (local = ls; local != NULL; local = local->proximo) {
		if (Diretorio_comparar(local->diretorio, diretorio))
			return TRUE;
	}
	return FALSE;
}

Diretorio* ListaDiretorio_pesquisaItemOrd(ListaDiretorio ls, UINT ordem)
{
	ListaDiretorio local;
	Diretorio* diretorio = Diretorio_new();

	for (local = ls; local != NULL; local = local->proximo) {
		if (local->ordem == ordem)
			return &(local->diretorio);
	}
	return diretorio;
}

INT ListaDiretorio_conta(ListaDiretorio ls)
{
	ListaDiretorio local;
	INT ncont;
	ncont = 0;
	for (local = ls; local != NULL; local = local->proximo)
		ncont++;

	return ncont;
}
