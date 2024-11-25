#include "Diretorio.h"

Diretorio Diretorio_new() {
	Diretorio diretorio;
	diretorio = (Diretorio)malloc(sizeof(struct SDiretorio));

	diretorio->aba = Aba_new();
	diretorio->arquivo = Arquivo_new();
	diretorio->tipo = Tipo_new();
	Diretorio_limpar(diretorio);

	return(diretorio);
}

void Diretorio_limpar(Diretorio diretorio) {
	Aba_limpar(diretorio->aba);
	Arquivo_limpar(diretorio->arquivo);
	diretorio->codigo = 0;
	diretorio->ordem = 0;
	diretorio->codDirPai = 0;
	Tipo_limpar(diretorio->tipo);
	diretorio->caminho = g_string_new("");
	diretorio->nomePai = g_string_new("");
	diretorio->caminhoPai = g_string_new("");
	diretorio->tamanhoFormatado = g_string_new("");
	diretorio->modificadoFormatado = g_string_new("");
	diretorio->caminhoOriginal = g_string_new("");
}

void Diretorio_free(Diretorio *diretorio) {
	Aba_free(&((*diretorio)->aba));
	Arquivo_free(&((*diretorio)->arquivo));
	Tipo_free(&((*diretorio)->tipo));
	g_string_free((*diretorio)->caminho, TRUE);
	g_string_free((*diretorio)->nomePai, TRUE);
	g_string_free((*diretorio)->caminhoPai, TRUE);
	g_string_free((*diretorio)->tamanhoFormatado, TRUE);
	g_string_free((*diretorio)->modificadoFormatado, TRUE);
	g_string_free((*diretorio)->caminhoOriginal, TRUE);
	free(*diretorio);
	*diretorio = NULL;
}

Diretorio Diretorio_copiar(const Diretorio diretorio) {
	Diretorio ldiretorio = Diretorio_new();

	ldiretorio->aba = Aba_copiar(diretorio->aba);
	ldiretorio->arquivo = Arquivo_copiar(diretorio->arquivo);
	ldiretorio->codigo = diretorio->codigo;
	ldiretorio->ordem = diretorio->ordem;
	ldiretorio->codDirPai = diretorio->codDirPai;
	ldiretorio->tipo = Tipo_copiar(diretorio->tipo);
	ldiretorio->caminho = g_string_new(diretorio->caminho->str);
	ldiretorio->nomePai = g_string_new(diretorio->nomePai->str);
	ldiretorio->caminhoPai = g_string_new(diretorio->caminhoPai->str);
	ldiretorio->tamanhoFormatado = g_string_new(diretorio->tamanhoFormatado->str);
	ldiretorio->modificadoFormatado = g_string_new(diretorio->modificadoFormatado->str);
	ldiretorio->caminhoOriginal = g_string_new(diretorio->caminhoOriginal->str);

	return ldiretorio;
}

gboolean Diretorio_comparar(const Diretorio diretorio1, const Diretorio diretorio2) {
	return
		(Aba_comparar(diretorio1->aba, diretorio2->aba)
			//&& Arquivo_comparar(diretorio1->arquivo, diretorio2->arquivo)
			&& diretorio1->codigo == diretorio2->codigo
			&& diretorio1->ordem == diretorio2->ordem
			//&& diretorio1->codDirPai == diretorio2->codDirPai
			//&& Tipo_comparar(diretorio1->tipo, diretorio2->tipo)
			//&& g_string_equal(diretorio1->caminho, diretorio2->caminho)
			//&& g_string_equal(diretorio1->nomePai, diretorio2->nomePai)
			//&& g_string_equal(diretorio1->tamanhoFormatado, diretorio2->tamanhoFormatado)
			//&& g_string_equal(diretorio1->modificadoFormatado, diretorio2->modificadoFormatado)
			//&& g_string_equal(diretorio1->caminhoOriginal, diretorio2->caminhoOriginal)
			);
}

ListaDiretorio ListaDiretorio_inicia()
{
	return g_slist_alloc();
}

void ListaDiretorio_libera(ListaDiretorio *ls)
{
	g_slist_free(*ls);
}

ListaDiretorio ListaDiretorio_insere(ListaDiretorio ls, Diretorio diretorio, gint posicao)
{
	return g_slist_insert(ls, diretorio, posicao);
}

gboolean ListaDiretorio_removeItem(ListaDiretorio *ls, const Diretorio diretorio)
{
	ListaDiretorio local;
	Diretorio linha;
	guint tamlista = ListaDiretorio_conta(*ls);

	for (local = *ls; local != NULL; local = local->next) {
		linha = local->data;

		if (Diretorio_comparar(linha, diretorio)) {
			g_slist_remove(local, local->data);
			break;
		}
	}

	guint ntamlista = ListaDiretorio_conta(*ls);
	return (tamlista != ntamlista);
}

gboolean ListaDiretorio_removeItemOrd(ListaDiretorio *ls, unsigned int ordem)
{
	ListaDiretorio local;
	guint tamlista = ListaDiretorio_conta(*ls);

	local = g_slist_nth(*ls, ordem);
	g_slist_remove(local, local->data);

	guint ntamlista = ListaDiretorio_conta(*ls);
	return (tamlista != ntamlista);
}

void ListaDiretorio_removeTodos(ListaDiretorio *ls)
{
	ListaDiretorio local;
	guint tamlista = ListaDiretorio_conta(*ls);

	if (tamlista > 0) {
		for (int i = tamlista - 1; i >= 0; i--) {
			local = g_slist_nth(*ls, i);
			g_slist_remove(local, local->data);
		}
	}
}

gboolean ListaDiretorio_pesquisaItem(ListaDiretorio ls, const Diretorio diretorio)
{
	Diretorio linha = Diretorio_new();
	guint tamlista = ListaDiretorio_conta(ls);

	if (tamlista > 0) {
		for (unsigned int i = 0; i < tamlista; i++) {
			linha = g_slist_nth_data(ls, i);
			if (Diretorio_comparar(linha, diretorio))
				return TRUE;
		}
	}
	return FALSE;
}

Diretorio ListaDiretorio_pesquisaItemOrd(ListaDiretorio ls, unsigned int ordem)
{
	return g_slist_nth_data(ls, ordem);
}

guint ListaDiretorio_conta(ListaDiretorio ls)
{
	return g_slist_length(ls) - 1;
}
