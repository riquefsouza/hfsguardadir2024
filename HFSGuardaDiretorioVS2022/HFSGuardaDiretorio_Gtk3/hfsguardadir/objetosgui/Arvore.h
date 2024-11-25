#ifndef ARVORE_H
#define ARVORE_H

#include "resource.h"
#include "hfsguardadir/comum/ListaString.h"

void Arvore_cria(GtkTreeView* tvArvore);
void Arvore_limpar(GtkTreeView* arvore);
void Arvore_expandirTodos(GtkTreeView* arvore);
void Arvore_colapsarTodos(GtkTreeView* arvore);
void Arvore_selecionarPrimeiroItem(GtkTreeView* arvore);
GtkTreeIter* Arvore_encontrarCaminho(GtkTreeModel* arvore_modelo, GtkTreeIter* pai, ListaString nomes, int nivel);
GtkTreePath* Arvore_encontrarCaminhoPorNome(GtkTreeView* arvore, ListaString nomes);
void Arvore_expandirSelecionado(GtkTreeView* arvore);

#endif
