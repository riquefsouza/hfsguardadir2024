#ifndef EXTENSAO_H
#define EXTENSAO_H

#include <gdk/gdk.h>
#include "../comum/ListaString.h"

struct SExtensao {
    int codigo;
	GString* nome;
    int ordem;
	GdkPixbuf* bmp16;
	GdkPixbuf* bmp32;
	int tamanhoBmp16;
	int tamanhoBmp32;
};
typedef struct SExtensao* Extensao;

typedef GSList* ListaExtensao;

Extensao Extensao_new();
void Extensao_free(Extensao *extensao);
void Extensao_limpar(Extensao extensao);
Extensao Extensao_copiar(const Extensao extensao);
gboolean Extensao_comparar(const Extensao extensao1, const Extensao extensao2);

ListaExtensao ListaExtensao_inicia();
void ListaExtensao_libera(ListaExtensao *ls);
ListaExtensao ListaExtensao_insere(ListaExtensao ls, Extensao extensao, gint posicao);
gboolean ListaExtensao_removeItem(ListaExtensao *ls, const Extensao extensao);
gboolean ListaExtensao_removeItemOrd(ListaExtensao *ls, unsigned int ordem);
void ListaExtensao_removeTodos(ListaExtensao *ls);
gboolean ListaExtensao_pesquisaItem(ListaExtensao ls, const Extensao extensao);
Extensao ListaExtensao_pesquisaItemOrd(ListaExtensao ls, unsigned int ordem);
guint ListaExtensao_conta(ListaExtensao ls);

#endif
