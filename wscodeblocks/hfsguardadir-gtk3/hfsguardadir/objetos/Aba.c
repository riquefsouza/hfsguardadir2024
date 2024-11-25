#include "Aba.h"

Aba Aba_new() {
	Aba aba;
	aba = (Aba)malloc(sizeof(struct SAba));

	Aba_limpar(aba);

	return(aba);
}

void Aba_limpar(Aba aba) {
	aba->codigo = 0;
	aba->nome = g_string_new("");
	aba->ordem = 0;
}

void Aba_free(Aba *aba) {
	g_string_free((*aba)->nome, TRUE);
	free(*aba);
	*aba = NULL;
}

Aba Aba_copiar(const Aba aba) {
	Aba laba = Aba_new();

	laba->codigo = aba->codigo;
	laba->nome = g_string_new(aba->nome->str);
	laba->ordem = aba->ordem;

	return laba;
}

gboolean Aba_comparar(const Aba aba1, const Aba aba2) {
	return
		(aba1->codigo == aba2->codigo
		&& g_string_equal(aba1->nome, aba2->nome)
		&& aba1->ordem == aba2->ordem);
}

ListaAba ListaAba_inicia()
{
	return g_slist_alloc();
}

void ListaAba_libera(ListaAba *ls)
{
	g_slist_free(*ls);
}

ListaAba ListaAba_insere(ListaAba ls, Aba aba, gint posicao)
{
	return g_slist_insert(ls, aba, posicao);
}

gboolean ListaAba_removeItem(ListaAba *ls, const Aba aba)
{
	ListaAba local;
	Aba linha;
	guint tamlista = ListaAba_conta(*ls);

	for (local = *ls; local != NULL; local = local->next) {
		linha = local->data;

		if (Aba_comparar(linha, aba)) {
			local = g_slist_remove(local, local->data);
			break;
		}
	}

	guint ntamlista = ListaAba_conta(*ls);
	return (tamlista != ntamlista);
}

gboolean ListaAba_removeItemOrd(ListaAba *ls, unsigned int ordem)
{
	ListaAba local;
	guint tamlista = ListaAba_conta(*ls);

	local = g_slist_nth(*ls, ordem);
	local = g_slist_remove(local, local->data);

	guint ntamlista = ListaAba_conta(*ls);
	return (tamlista != ntamlista);
}

void ListaAba_removeTodos(ListaAba *ls)
{
	ListaAba local;
	guint tamlista = ListaAba_conta(*ls);

	if (tamlista > 0) {
		for (int i = tamlista - 1; i >= 0; i--) {
			local = g_slist_nth(*ls, i);
			local = g_slist_remove(local, local->data);
		}
	}
}

gboolean ListaAba_pesquisaItem(ListaAba ls, const Aba aba)
{
	Aba linha = Aba_new();
	guint tamlista = ListaAba_conta(ls);

	if (tamlista > 0) {
		for (unsigned int i = 0; i < tamlista; i++) {
			linha = g_slist_nth_data(ls, i);
			if (Aba_comparar(linha, aba))
				return TRUE;
		}
	}
	return FALSE;
}

Aba ListaAba_pesquisaItemOrd(ListaAba ls, unsigned int ordem)
{
	return g_slist_nth_data(ls, ordem);
}

guint ListaAba_conta(ListaAba ls)
{
	return g_slist_length(ls) - 1;
}
