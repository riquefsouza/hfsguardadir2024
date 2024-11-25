#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "hfsguardadir/comum/ListaString.h"
#include "hfsguardadir/comum/DateTime.h"

struct SArquivo {
	GString* nome;
	unsigned long long tamanho;
	GDateTime* modificado;
	GString* atributos;
};
typedef struct SArquivo* Arquivo;

typedef GSList* ListaArquivo;

Arquivo Arquivo_new();
void Arquivo_free(Arquivo *arquivo);
void Arquivo_limpar(Arquivo arquivo);
Arquivo Arquivo_copiar(const Arquivo arquivo);
gboolean Arquivo_comparar(const Arquivo arquivo1, const Arquivo arquivo2);

ListaArquivo ListaArquivo_inicia();
void ListaArquivo_libera(ListaArquivo *ls);
ListaArquivo ListaArquivo_insere(ListaArquivo ls, Arquivo arquivo, gint posicao);
gboolean ListaArquivo_removeItem(ListaArquivo *ls, const Arquivo arquivo);
gboolean ListaArquivo_removeItemOrd(ListaArquivo *ls, unsigned int ordem);
void ListaArquivo_removeTodos(ListaArquivo *ls);
gboolean ListaArquivo_pesquisaItem(ListaArquivo ls, const Arquivo arquivo);
Arquivo ListaArquivo_pesquisaItemOrd(ListaArquivo ls, unsigned int ordem);
guint ListaArquivo_conta(ListaArquivo ls);

#endif
