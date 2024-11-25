#include "Importar.h"

Importar Importar_new() {
	Importar importar;
	importar = (Importar)malloc(sizeof(struct SImportar));

	Importar_limpar(importar);

	return(importar);
}

void Importar_limpar(Importar importar) {
	importar->aba = 0;
	importar->codDirRaiz = 0;
	importar->rotuloRaiz = g_string_new("");
	importar->nomeDirRaiz = g_string_new("");
	importar->caminho = g_string_new("");
}

void Importar_free(Importar *importar) {
	g_string_free((*importar)->rotuloRaiz, TRUE);
	g_string_free((*importar)->nomeDirRaiz, TRUE);
	g_string_free((*importar)->caminho, TRUE);
	free(*importar);
	*importar = NULL;
}

Importar Importar_copiar(const Importar importar) {
	Importar limportar = Importar_new();

	limportar->aba = importar->aba;
	limportar->codDirRaiz = importar->codDirRaiz;
	limportar->rotuloRaiz = g_string_new(importar->rotuloRaiz->str);
	limportar->nomeDirRaiz = g_string_new(importar->nomeDirRaiz->str);
	limportar->caminho = g_string_new(importar->caminho->str);

	return limportar;
}

gboolean Importar_comparar(const Importar importar1, const Importar importar2) {
	return
		(importar1->aba == importar2->aba
			&& importar1->codDirRaiz == importar2->codDirRaiz
			&& g_string_equal(importar1->rotuloRaiz, importar2->rotuloRaiz)
			&& g_string_equal(importar1->nomeDirRaiz, importar2->nomeDirRaiz)
			&& g_string_equal(importar1->caminho, importar2->caminho));
}

ListaImportar ListaImportar_inicia()
{
	return g_slist_alloc();
}

void ListaImportar_libera(ListaImportar *ls)
{
	g_slist_free(*ls);
}

ListaImportar ListaImportar_insere(ListaImportar ls, Importar importar, gint posicao)
{
	return g_slist_insert(ls, importar, posicao);
}

gboolean ListaImportar_removeItem(ListaImportar *ls, const Importar importar)
{
	ListaImportar local;
	Importar linha;
	guint tamlista = ListaImportar_conta(*ls);

	for (local = *ls; local != NULL; local = local->next) {
		linha = local->data;

		if (Importar_comparar(linha, importar)) {
			g_slist_remove(local, local->data);
			break;
		}
	}

	guint ntamlista = ListaImportar_conta(*ls);
	return (tamlista != ntamlista);
}

gboolean ListaImportar_removeItemOrd(ListaImportar *ls, unsigned int ordem)
{
	ListaImportar local;
	guint tamlista = ListaImportar_conta(*ls);

	local = g_slist_nth(*ls, ordem);
	g_slist_remove(local, local->data);

	guint ntamlista = ListaImportar_conta(*ls);
	return (tamlista != ntamlista);
}

void ListaImportar_removeTodos(ListaImportar *ls)
{
	ListaImportar local;
	guint tamlista = ListaImportar_conta(*ls);

	if (tamlista > 0) {
		for (int i = tamlista - 1; i >= 0; i--) {
			local = g_slist_nth(*ls, i);
			g_slist_remove(local, local->data);
		}
	}
}

gboolean ListaImportar_pesquisaItem(ListaImportar ls, const Importar importar)
{
	Importar linha = Importar_new();
	guint tamlista = ListaImportar_conta(ls);

	if (tamlista > 0) {
		for (unsigned int i = 0; i < tamlista; i++) {
			linha = g_slist_nth_data(ls, i);
			if (Importar_comparar(linha, importar))
				return TRUE;
		}
	}
	return FALSE;
}

Importar ListaImportar_pesquisaItemOrd(ListaImportar ls, unsigned int ordem)
{
	return g_slist_nth_data(ls, ordem);
}

guint ListaImportar_conta(ListaImportar ls)
{
	return g_slist_length(ls) - 1;
}
