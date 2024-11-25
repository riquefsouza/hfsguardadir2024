#include "stdafx.h"

#include <stdio.h>

#include <commctrl.h>
#include "hfsguardadir/objetosgui/TabControle.h"
#include "hfsguardadir/objetosgui/Arvore.h"
#include "hfsguardadir/objetosgui/Tabela.h"
#include "hfsguardadir/comum/ListaString.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/catalogador/Catalogador.h"

HWND TabControle_cria(HWND hwnd, INT id, INT x, INT y, INT altura)
{ 
HWND hwndTabControle;
DWORD nEstilo;
INT largura;
RECT rc;

GetClientRect(hwnd, &rc);
largura = rc.right - rc.left;
nEstilo = TCS_MULTILINE | WS_GROUP | WS_TABSTOP;
      
hwndTabControle = CreateWindowEx(WS_EX_CLIENTEDGE, WC_TABCONTROL, _T(""),  nEstilo,                  
     x, y, largura, altura, hwnd, (HMENU)id, 
    (HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE), NULL); 

return hwndTabControle;
}

void TabControle_adiciona(HWND hTabControle, UINT nIndice, LPTSTR sTab) {
	TCITEM tcItem;
	tcItem.mask = TCIF_TEXT | TCIF_IMAGE; // | TCIF_PARAM;
	tcItem.pszText = sTab;
	tcItem.cchTextMax = lstrlen(sTab);
	tcItem.iImage = 0;
	//tcItem.lParam = (DWORD)&parent;
	
	TabCtrl_InsertItem(hTabControle, nIndice, &tcItem);
}

void TabControle_altera(HWND hTabControle, UINT nIndice, LPTSTR sTab) {
	TCITEM tcItem;
	tcItem.mask = TCIF_TEXT | TCIF_IMAGE; // | TCIF_PARAM;
	tcItem.pszText = sTab;
	tcItem.cchTextMax = lstrlen(sTab);
	tcItem.iImage = 0;
	//tcItem.lParam = (DWORD)&parent;

	TabCtrl_SetItem(hTabControle, nIndice, &tcItem);
}

void TabControle_remove(HWND hTabControle, UINT nIndice) {
	TabCtrl_DeleteItem(hTabControle, nIndice);
}

BOOL TabControle_notifica(HWND hTabControle, LPARAM lParam, HWND hArvore, HWND hTabela)
{
	NMHDR *nm = (LPNMHDR)lParam;

	switch (nm->code) {
	case TCN_SELCHANGE:
	{	
		Catalogador_tabPanelMudou();
		
		return TRUE;
	}
	break;
	/*
	case TCN_SELCHANGING:
	{
		return TRUE;
	}
	break;
	*/
	}
	return FALSE;
}
