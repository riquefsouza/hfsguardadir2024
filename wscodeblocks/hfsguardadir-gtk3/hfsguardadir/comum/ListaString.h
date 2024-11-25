#ifndef LISTASTRING_H
#define LISTASTRING_H

#include <glib.h>

#define TAM_MAX_STR 512
//#define QTD_MAX_COL 10

typedef GSList* ListaString;
//typedef GSList* ListaMString;

ListaString ListaString_inicia();
void ListaString_libera(ListaString *ls);
ListaString ListaString_insere(ListaString ls, GString *str, gint posicao);
//void ListaString_insereFim(ListaString ls, GString *str);
gboolean ListaString_removeItem(ListaString *ls, const GString *str);
gboolean ListaString_removeItemOrd(ListaString *ls, unsigned int ordem);
void ListaString_removeTodos(ListaString *ls);
gboolean ListaString_pesquisaItem(ListaString ls, const GString *str);
GString* ListaString_pesquisaItemOrd(ListaString ls, unsigned int ordem);
guint ListaString_conta(ListaString ls);
ListaString ListaString_inverter(ListaString ls);

#endif


