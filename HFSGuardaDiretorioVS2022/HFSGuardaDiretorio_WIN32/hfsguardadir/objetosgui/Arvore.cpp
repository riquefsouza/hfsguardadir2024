#include "stdafx.h"

#include <commctrl.h>
#include "Arvore.h"
#include "FrmPrincipal.h"
#include "hfsguardadir\catalogador\Catalogador.h"

HWND Arvore_cria(HWND hwnd, INT id, INT x, INT y, INT altura)
{ 
HWND hwndArvore;
DWORD nEstilo;
INT largura;
RECT rc;

GetClientRect(hwnd, &rc);
largura = rc.right - rc.left;
nEstilo = WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP |
		TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT |
		TVS_SINGLEEXPAND | TVS_SHOWSELALWAYS |
		TVS_TRACKSELECT;
      
hwndArvore = CreateWindowEx(WS_EX_CLIENTEDGE, WC_TREEVIEW, _T(""),  nEstilo,                  
     x, y, largura, altura, hwnd, (HMENU)id, 
    (HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE), NULL); 

return hwndArvore;
}

TV_INSERTSTRUCT Arvore_item(LPTSTR stexto, HTREEITEM hPrev, HTREEITEM hInsertAfter, int nNivel) {
	TV_INSERTSTRUCT tvi;

	tvi.hParent = hPrev;
	tvi.hInsertAfter = hInsertAfter;
	tvi.item.lParam = (LPARAM)nNivel;
	tvi.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	tvi.item.pszText = stexto;
	tvi.item.iImage = 0;
	tvi.item.iSelectedImage = 2;

	return tvi;
}

void Arvore_limpar(HWND hArvore) {
	TreeView_DeleteAllItems(hArvore);
}


VOID Arvore_expandirTodos(HWND hArvore) {
	HTREEITEM proximoItem;

	//proximoItem = TreeView_GetRoot(hArvore);
	proximoItem = TreeView_GetFirstVisible(hArvore);	
	while (proximoItem != NULL) {
		TreeView_Expand(hArvore, proximoItem, TVE_EXPAND);
		proximoItem = TreeView_GetNextVisible(hArvore, proximoItem);
	}
}

VOID Arvore_colapsarTodos(HWND hArvore) {
	HTREEITEM proximoItem;

	//proximoItem = TreeView_GetRoot(hArvore);
	proximoItem = TreeView_GetFirstVisible(hArvore);
	while (proximoItem != NULL) {
		TreeView_Expand(hArvore, proximoItem, TVE_COLLAPSE);
		proximoItem = TreeView_GetNextVisible(hArvore, proximoItem);
	}
}

String Arvore_GetItemText(HWND hArvore, HTREEITEM item) {
	String texto;
	TVITEM tvi;
	WCHAR buffer[TAM_MAX_STR];
	buffer[0] = '\0';

	memset(&tvi, 0, sizeof(tvi));

	tvi.hItem = item;
	tvi.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	tvi.pszText = buffer;
	tvi.cchTextMax = TAM_MAX_STR;	
	tvi.iImage = 0;
	tvi.iSelectedImage = 2;

	if (TreeView_GetItem(hArvore, &tvi)) {
		texto = String_iniciar(tvi.pszText);
	}
	else {
		texto = String_iniciar("");
	}

	return texto;
}

VOID Arvore_encontrarCaminhoPorNome(HWND hArvore, ListaString nomes) {
	HTREEITEM proximoItem{}, diretorioItem{};
	String texto, snome;
	UINT nivel, total;

	total = ListaString_conta(nomes);
	
	proximoItem = TreeView_GetFirstVisible(hArvore);
	nivel = 0;
	while (proximoItem!=NULL) {
		texto = Arvore_GetItemText(hArvore, proximoItem);

		snome = ListaString_pesquisaItemOrd(nomes, nivel);

		if (String_comparar(snome, texto)) {
			diretorioItem = proximoItem;
			TreeView_Expand(hArvore, diretorioItem, TVE_EXPAND);

			if (nivel == (total - 1)) {
				break;
			}
			nivel++;
		}
		proximoItem = TreeView_GetNextVisible(hArvore, proximoItem);
	}

	if (diretorioItem!=NULL) {
		TreeView_SelectItem(hArvore, diretorioItem);

	}
}

BOOL Arvore_isSelecionado(HWND hArvore) {
	//DWORD ntotal = TreeView_GetSelectedCount(hArvore);
	//return (ntotal > 0);
	HTREEITEM selectedItem = TreeView_GetSelection(hArvore);
	return (selectedItem != NULL);
}

BOOL Arvore_notifica(HWND hwnd, HWND hArvore, WPARAM wParam, LPARAM lParam, INT nIdItem)
{
	LPNMHDR pnmhdr = (LPNMHDR)lParam;

	if (LOWORD(wParam) == nIdItem) {

		if (pnmhdr->code == TVN_SELCHANGED) {
			OutputDebugString(_T("TVN_SELCHANGED"));
		}

		if (pnmhdr->code == NM_DBLCLK) {
			//HTREEITEM selectedItem = TreeView_GetSelection(hwnd);
			HTREEITEM selectedItem = (HTREEITEM)SendDlgItemMessage(hwnd,
				nIdItem, TVM_GETNEXTITEM, TVGN_CARET, NULL);
			if (selectedItem != NULL)
			{
				TreeView_EnsureVisible(hwnd, selectedItem);
				//TreeView_SelectItem(hwnd, selectedItem);
				SendDlgItemMessage(hwnd, nIdItem,
					TVM_SELECTITEM, TVGN_CARET, (LPARAM)selectedItem);

				Catalogador_arvoreValorMudou(hArvore, selectedItem);
			}
		}

	}
	return TRUE;
}
