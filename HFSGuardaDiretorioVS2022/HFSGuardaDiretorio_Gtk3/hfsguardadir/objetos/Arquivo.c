#include "Arquivo.h"

Arquivo Arquivo_new() {
	Arquivo arquivo;
	arquivo = (Arquivo)malloc(sizeof(struct SArquivo));

	Arquivo_limpar(arquivo);

	return(arquivo);
}

void Arquivo_limpar(Arquivo arquivo) {
	arquivo->nome = g_string_new("");
	arquivo->tamanho = 0;
	arquivo->modificado = g_date_time_new_now_local();
	arquivo->atributos = g_string_new("");
}

void Arquivo_free(Arquivo *arquivo) {
	g_string_free((*arquivo)->nome, TRUE);
	free((*arquivo)->modificado);
	g_string_free((*arquivo)->atributos, TRUE);
	free(arquivo);
	arquivo = NULL;
}

Arquivo Arquivo_copiar(const Arquivo arquivo) {
	Arquivo larquivo = Arquivo_new();

	larquivo->nome = g_string_new(arquivo->nome->str);
	larquivo->tamanho = arquivo->tamanho;
	larquivo->modificado = arquivo->modificado;
	larquivo->atributos = g_string_new(arquivo->atributos->str);

	return larquivo;
}

gboolean Arquivo_comparar(const Arquivo arquivo1, const Arquivo arquivo2) {
	return
		(g_string_equal(arquivo1->nome, arquivo2->nome)
		&& arquivo1->tamanho == arquivo2->tamanho			
		&& g_date_time_equal(arquivo1->modificado, arquivo2->modificado)
		&& g_string_equal(arquivo1->atributos, arquivo2->atributos));
}

ListaArquivo ListaArquivo_inicia()
{
	return g_slist_alloc();
}

void ListaArquivo_libera(ListaArquivo *ls)
{
	g_slist_free(*ls);
}

ListaArquivo ListaArquivo_insere(ListaArquivo ls, Arquivo arquivo, gint posicao)
{
	return g_slist_insert(ls, arquivo, posicao);
}

gboolean ListaArquivo_removeItem(ListaArquivo *ls, const Arquivo arquivo)
{
	ListaArquivo local;
	Arquivo linha;
	guint tamlista = ListaArquivo_conta(*ls);

	for (local = *ls; local != NULL; local = local->next) {
		linha = local->data;

		if (Arquivo_comparar(linha, arquivo)) {
			g_slist_remove(local, local->data);
			break;
		}
	}

	guint ntamlista = ListaArquivo_conta(*ls);
	return (tamlista != ntamlista);
}

gboolean ListaArquivo_removeItemOrd(ListaArquivo *ls, unsigned int ordem)
{
	ListaArquivo local;
	guint tamlista = ListaArquivo_conta(*ls);

	local = g_slist_nth(*ls, ordem);
	g_slist_remove(local, local->data);

	guint ntamlista = ListaArquivo_conta(*ls);
	return (tamlista != ntamlista);
}

void ListaArquivo_removeTodos(ListaArquivo *ls)
{
	ListaArquivo local;
	guint tamlista = ListaArquivo_conta(*ls);

	if (tamlista > 0) {
		for (int i = tamlista - 1; i >= 0; i--) {
			local = g_slist_nth(*ls, i);
			g_slist_remove(local, local->data);
		}
	}
}

gboolean ListaArquivo_pesquisaItem(ListaArquivo ls, const Arquivo arquivo)
{
	Arquivo linha = Arquivo_new();
	guint tamlista = ListaArquivo_conta(ls);

	if (tamlista > 0) {
		for (unsigned int i = 0; i < tamlista; i++) {
			linha = g_slist_nth_data(ls, i);
			if (Arquivo_comparar(linha, arquivo))
				return TRUE;
		}
	}
	return FALSE;
}

Arquivo ListaArquivo_pesquisaItemOrd(ListaArquivo ls, unsigned int ordem)
{
	return g_slist_nth_data(ls, ordem);
}

guint ListaArquivo_conta(ListaArquivo ls)
{
	return g_slist_length(ls) - 1;
}
