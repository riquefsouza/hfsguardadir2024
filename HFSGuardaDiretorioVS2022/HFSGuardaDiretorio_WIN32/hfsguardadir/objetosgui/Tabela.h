#ifndef TABELA_H
#define TABELA_H

#define MAXLINHAS_VISAOLISTA 100000

#include <commctrl.h>
#include "hfsguardadir/comum/ListaString.h"
#include "hfsguardadir/objetos/Diretorio.h"
#include "hfsguardadir/objetos/Extensao.h"

typedef HWND Tabela;

HWND Tabela_cria(HWND hwnd, INT id, INT x, INT y, INT altura);
BOOL Tabela_insereColunas(HWND hwndTabela, UINT largura[],
    ListaString sColunas);
BOOL Tabela_insereLinha(HWND hwndTabela, UINT nQtdColunas, UINT nLinha, INT nImagem,
	String colunas[QTD_MAX_COL]);
BOOL Tabela_insere(HWND hwndTabela, UINT nQtdColunas, ListaMString sLinhas, INT nImagem);
int CALLBACK Tabela_comparaASC(LPARAM item1, LPARAM item2, LPARAM lParamSort);
int CALLBACK Tabela_comparaDESC(LPARAM item1, LPARAM item2, LPARAM lParamSort);
BOOL Tabela_notifica(HWND hwndTabela, WPARAM wParam, LPARAM lParam, INT nIdItem, BOOL bTabelaDir);
void Tabela_modeloColunas(HWND hTabela, BOOL bTabelaDir, HIMAGELIST imageList16, HIMAGELIST imageList32);
void Tabela_limpar(HWND hTabela);
void Tabela_adiciona(HWND hTabela, BOOL bTabelaDir, ListaDiretorio listaDir,
	ListaExtensao listaExtensao, HWND barraProgresso);
BOOL Tabela_isSelecionado(HWND hTabela, UINT nLinha);
VOID Tabela_selecionaLinha(HWND hTabela, UINT nLinha);
VOID Tabela_deselecionaLinha(HWND hTabela, UINT nLinha);
UINT Tabela_encontrarLinha(HWND hTabela, LPCWSTR nome);
Diretorio* Tabela_getItemSelecionado(HWND hTabela, BOOL bTabelaDir);
VOID Tabela_ScrollLines(HWND hTabela, UINT nLinha);

#endif
