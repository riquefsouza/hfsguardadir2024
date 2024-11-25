#ifndef TABCONTROLE_H
#define TABCONTROLE_H

HWND TabControle_cria(HWND hwnd, INT id, INT x, INT y, INT altura);
void TabControle_adiciona(HWND hTabControle, UINT nIndice, LPTSTR sTab);
void TabControle_altera(HWND hTabControle, UINT nIndice, LPTSTR sTab);
void TabControle_remove(HWND hTabControle, UINT nIndice);
BOOL TabControle_notifica(HWND hTabControle, LPARAM lParam, HWND hArvore, HWND hTabela);

#endif
