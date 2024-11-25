#ifndef IMPORTAR_H
#define IMPORTAR_H

#include "../comum/ListaString.h"

struct SImportar {
    int aba;
	int codDirRaiz;
	GString* rotuloRaiz;
	GString* nomeDirRaiz;
	GString* caminho;
};
typedef struct SImportar* Importar;

typedef GSList* ListaImportar;

Importar Importar_new();
void Importar_free(Importar *importar);
void Importar_limpar(Importar importar);
Importar Importar_copiar(const Importar importar);
gboolean Importar_comparar(const Importar importar1, const Importar importar2);

ListaImportar ListaImportar_inicia();
void ListaImportar_libera(ListaImportar *ls);
ListaImportar ListaImportar_insere(ListaImportar ls, Importar importar, gint posicao);
gboolean ListaImportar_removeItem(ListaImportar *ls, const Importar importar);
gboolean ListaImportar_removeItemOrd(ListaImportar *ls, unsigned int ordem);
void ListaImportar_removeTodos(ListaImportar *ls);
gboolean ListaImportar_pesquisaItem(ListaImportar ls, const Importar importar);
Importar ListaImportar_pesquisaItemOrd(ListaImportar ls, unsigned int ordem);
guint ListaImportar_conta(ListaImportar ls);

#endif
