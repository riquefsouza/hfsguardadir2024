#ifndef ARVORE_H
#define ARVORE_H

#include "hfsguardadir/comum/ListaString.h"

typedef HWND Arvore;

HWND Arvore_cria(HWND hwnd, INT id, INT x, INT y, INT altura);
TV_INSERTSTRUCT Arvore_item(LPTSTR stexto, HTREEITEM hPrev, HTREEITEM hInsertAfter, int nNivel);
void Arvore_limpar(HWND hArvore);
VOID Arvore_expandirTodos(HWND hArvore);
VOID Arvore_colapsarTodos(HWND hArvore);
String Arvore_GetItemText(HWND hArvore, HTREEITEM item);
VOID Arvore_encontrarCaminhoPorNome(HWND hArvore, ListaString nomes);
BOOL Arvore_isSelecionado(HWND hArvore);
BOOL Arvore_notifica(HWND hwnd, HWND hArvore, WPARAM wParam, LPARAM lParam, INT nIdItem);

#endif
