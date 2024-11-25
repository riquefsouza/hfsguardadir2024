#ifndef ABA_H
#define ABA_H

#include "hfsguardadir/comum/ListaString.h"

struct SAba {
    int codigo;
	GString* nome;
    int ordem;
};
typedef struct SAba* Aba;

typedef GSList* ListaAba;

Aba Aba_new();
void Aba_free(Aba *aba);
void Aba_limpar(Aba aba);
Aba Aba_copiar(const Aba aba);
gboolean Aba_comparar(const Aba aba1, const Aba aba2);

ListaAba ListaAba_inicia();
void ListaAba_libera(ListaAba *ls);
ListaAba ListaAba_insere(ListaAba ls, Aba aba, gint posicao);
gboolean ListaAba_removeItem(ListaAba *ls, const Aba aba);
gboolean ListaAba_removeItemOrd(ListaAba *ls, unsigned int ordem);
void ListaAba_removeTodos(ListaAba *ls);
gboolean ListaAba_pesquisaItem(ListaAba ls, const Aba aba);
Aba ListaAba_pesquisaItemOrd(ListaAba ls, unsigned int ordem);
guint ListaAba_conta(ListaAba ls);


#endif
