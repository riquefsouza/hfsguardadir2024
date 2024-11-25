#include "stdafx.h"
#include "HFSGuardaDiretorio.h"
#include "hfsguardadir\objetosgui\Arvore.h"
#include "hfsguardadir\comum\Rotinas.h"

namespace hfsguardadir {

namespace objetosgui {

//IMPLEMENT_DYNCREATE(Arvore, CTreeCtrl)

Arvore::Arvore()
{

}

Arvore::~Arvore()
{
}

TV_INSERTSTRUCT Arvore::item(const CString &stexto, HTREEITEM hPrev, HTREEITEM hInsertAfter, int nNivel) {
	TV_INSERTSTRUCT tvi;

	tvi.hParent = hPrev;
	tvi.hInsertAfter = hInsertAfter;
	tvi.item.lParam = (LPARAM)nNivel;
	tvi.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	tvi.item.pszText = (LPWSTR)stexto.GetString();
	tvi.item.iImage = 0;
	tvi.item.iSelectedImage = 2;

	return tvi;
}

void Arvore::limpar(CTreeCtrl &arvore) {
	arvore.DeleteAllItems();
}

VOID Arvore::expandirTodos(CTreeCtrl &arvore) {
	HTREEITEM proximoItem;

	proximoItem = arvore.GetFirstVisibleItem();
	while (proximoItem != NULL) {
		arvore.Expand(proximoItem, TVE_EXPAND);
		proximoItem = arvore.GetNextVisibleItem(proximoItem);
	}
}

VOID Arvore::colapsarTodos(CTreeCtrl &arvore) {
	HTREEITEM proximoItem;

	proximoItem = arvore.GetFirstVisibleItem();
	while (proximoItem != NULL) {
		arvore.Expand(proximoItem, TVE_COLLAPSE);
		proximoItem = arvore.GetNextVisibleItem(proximoItem);
	}
}

CString Arvore::GetItemText(CTreeCtrl &arvore, HTREEITEM item) {
	CString texto;
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

	if (arvore.GetItem(&tvi)) {
		texto = tvi.pszText;
	}
	else {
		texto = _T("");
	}

	return texto;
}

VOID Arvore::encontrarCaminhoPorNome(CTreeCtrl &arvore, CStringList &nomes) {
	HTREEITEM proximoItem, diretorioItem;
	CString texto, snome;
	UINT nivel, total;
	POSITION pos;

	total = nomes.GetSize();

	proximoItem = arvore.GetFirstVisibleItem();
	nivel = 0;
	while (proximoItem != NULL) {
		texto = arvore.GetItemText(proximoItem);

		pos = nomes.FindIndex(nivel);
		snome = nomes.GetAt(pos);

		if (snome == texto) {
			diretorioItem = proximoItem;
			arvore.Expand(diretorioItem, TVE_EXPAND);

			if (nivel == (total - 1)) {
				break;
			}
			nivel++;
		}
		proximoItem = arvore.GetNextVisibleItem(proximoItem);
	}

	if (diretorioItem != NULL) {
		arvore.SelectItem(diretorioItem);

	}
}

BOOL Arvore::isSelecionado(CTreeCtrl &arvore) {
	//DWORD ntotal = arvore.GetSelectedCount(hArvore);
	//return (ntotal > 0);
	HTREEITEM selectedItem = arvore.GetSelectedItem();
	return (selectedItem != NULL);
}

/*
BOOL Arvore_notifica(HWND hwnd, HWND hArvore, WPARAM wParam, LPARAM lParam, INT nIdItem)
{
	LPNMHDR pnmhdr = (LPNMHDR)lParam;

	if (LOWORD(wParam) == nIdItem) {

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
*/

/*
BEGIN_MESSAGE_MAP(Arvore, CTreeCtrl)
END_MESSAGE_MAP()


// Arvore diagnostics

#ifdef _DEBUG
void Arvore::AssertValid() const
{
	CTreeCtrl::AssertValid();
}

#ifndef _WIN32_WCE
void Arvore::Dump(CDumpContext& dc) const
{
	CTreeCtrl::Dump(dc);
}
#endif
#endif //_DEBUG


// Arvore message handlers
*/
}
}
