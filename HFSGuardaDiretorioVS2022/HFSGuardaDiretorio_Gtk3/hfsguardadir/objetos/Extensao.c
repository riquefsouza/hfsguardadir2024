#include "Extensao.h"

Extensao Extensao_new() {
	Extensao extensao;
	extensao = (Extensao)malloc(sizeof(struct SExtensao));

	Extensao_limpar(extensao);

	return(extensao);
}

void Extensao_limpar(Extensao extensao) {
	extensao->codigo = 0;
	extensao->nome = g_string_new("");
	extensao->ordem = 0;
	//extensao->bmp16 = ;
	//extensao->bmp32 = ;
}

void Extensao_free(Extensao *extensao) {
	g_string_free((*extensao)->nome, TRUE);
	g_object_unref((*extensao)->bmp16);
	g_object_unref((*extensao)->bmp32);
	free(*extensao);
	*extensao = NULL;
}

Extensao Extensao_copiar(const Extensao extensao) {
	Extensao lextensao = Extensao_new();

	lextensao->codigo = extensao->codigo;
	lextensao->nome = g_string_new(extensao->nome->str);
	lextensao->ordem = extensao->ordem;
	lextensao->bmp16 = extensao->bmp16;
	lextensao->bmp32 = extensao->bmp32;

	return lextensao;
}

gboolean Extensao_comparar(const Extensao extensao1, const Extensao extensao2) {
	return
		(extensao1->codigo == extensao2->codigo
			&& g_string_equal(extensao1->nome, extensao2->nome)
			&& extensao1->ordem == extensao2->ordem);
}

ListaExtensao ListaExtensao_inicia()
{
	return g_slist_alloc();
}

void ListaExtensao_libera(ListaExtensao *ls)
{
	g_slist_free(*ls);
}

ListaExtensao ListaExtensao_insere(ListaExtensao ls, Extensao extensao, gint posicao)
{
	return g_slist_insert(ls, extensao, posicao);
}

gboolean ListaExtensao_removeItem(ListaExtensao *ls, const Extensao extensao)
{
	ListaExtensao local;
	Extensao linha;
	guint tamlista = ListaExtensao_conta(*ls);

	for (local = *ls; local != NULL; local = local->next) {
		linha = local->data;

		if (Extensao_comparar(linha, extensao)) {
			g_slist_remove(local, local->data);
			break;
		}
	}

	guint ntamlista = ListaExtensao_conta(*ls);
	return (tamlista != ntamlista);
}

gboolean ListaExtensao_removeItemOrd(ListaExtensao *ls, unsigned int ordem)
{
	ListaExtensao local;
	guint tamlista = ListaExtensao_conta(*ls);

	local = g_slist_nth(*ls, ordem);
	g_slist_remove(local, local->data);

	guint ntamlista = ListaExtensao_conta(*ls);
	return (tamlista != ntamlista);
}

void ListaExtensao_removeTodos(ListaExtensao *ls)
{
	ListaExtensao local;
	guint tamlista = ListaExtensao_conta(*ls);

	if (tamlista > 0) {
		for (int i = tamlista - 1; i >= 0; i--) {
			local = g_slist_nth(*ls, i);
			g_slist_remove(local, local->data);
		}
	}
}

gboolean ListaExtensao_pesquisaItem(ListaExtensao ls, const Extensao extensao)
{
	Extensao linha = Extensao_new();
	guint tamlista = ListaExtensao_conta(ls);

	if (tamlista > 0) {
		for (unsigned int i = 0; i < tamlista; i++) {
			linha = g_slist_nth_data(ls, i);
			if (Extensao_comparar(linha, extensao))
				return TRUE;
		}
	}
	return FALSE;
}

Extensao ListaExtensao_pesquisaItemOrd(ListaExtensao ls, unsigned int ordem)
{
	return g_slist_nth_data(ls, ordem);
}

guint ListaExtensao_conta(ListaExtensao ls)
{
	return g_slist_length(ls) - 1;
}

