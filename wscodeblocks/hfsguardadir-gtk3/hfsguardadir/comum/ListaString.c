#include "ListaString.h"

/* Lista de GStrings */

ListaString ListaString_inicia()
{
  return g_slist_alloc();
}

void ListaString_libera(ListaString *ls)
{
	g_slist_free(*ls);
}

ListaString ListaString_insere(ListaString ls, GString *str, gint posicao)
{
	return g_slist_insert(ls, str, posicao);
}

/*
void ListaString_insereFim(ListaString ls, GString *str)
{
	g_slist_append(ls, str);
}
*/

gboolean ListaString_removeItem(ListaString *ls, const GString *str)
{
	ListaString local;
	GString* linha;
	guint tamlista = ListaString_conta(*ls);

	for (local = *ls; local != NULL; local = local->next) {
		linha = local->data;

		if (g_string_equal(linha, str)) {
			local = g_slist_remove(local, local->data);
			break;
		}
	}

	guint ntamlista = ListaString_conta(*ls);
	return (tamlista != ntamlista);
}

gboolean ListaString_removeItemOrd(ListaString *ls, unsigned int ordem)
{
	ListaString local;
	guint tamlista = ListaString_conta(*ls);

	local = g_slist_nth(*ls, ordem);
	local = g_slist_remove(local, local->data);

	guint ntamlista = ListaString_conta(*ls);
	return (tamlista != ntamlista);
}

void ListaString_removeTodos(ListaString *ls)
{
	ListaString local;
	guint tamlista = ListaString_conta(*ls);

	if (tamlista > 0) {
		for (int i = tamlista; i >=0 ; i--) {
			local = g_slist_nth(*ls, i);
			local = g_slist_remove(local, local->data);
		}
	}
}

gboolean ListaString_pesquisaItem(ListaString ls, const GString *str)
{
	GString* linha = g_string_new("");
	guint tamlista = ListaString_conta(ls);

	if (tamlista > 0) {
		for (unsigned int i = 0; i < tamlista; i++) {
			linha = g_slist_nth_data(ls, i);
			if (g_string_equal(linha, str))
				return TRUE;
		}
	}
	return FALSE;
}

GString* ListaString_pesquisaItemOrd(ListaString ls, unsigned int ordem)
{
	return g_slist_nth_data(ls, ordem);
}

guint ListaString_conta(ListaString ls)
{
	return g_slist_length(ls) - 1;
}

ListaString ListaString_inverter(ListaString ls) {
	GString* item;
	ListaString rls;
	guint ntotal = ListaString_conta(ls);
	gint posicao = 0;

	if (ntotal > 1) {
		rls = g_slist_reverse(ls);
		ntotal = g_slist_length(rls);
		item = g_string_new("");

		for (unsigned int i = 1; i < ntotal; i++) {
			item = g_slist_nth_data(rls, i);
			ls = g_slist_insert(ls, item, posicao);
			posicao++;
		}
		g_slist_free(rls);
	}

	return ls;
}
