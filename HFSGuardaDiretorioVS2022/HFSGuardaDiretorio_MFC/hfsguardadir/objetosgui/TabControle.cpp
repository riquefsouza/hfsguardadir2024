#include "stdafx.h"
#include "HFSGuardaDiretorio.h"
#include "hfsguardadir\objetosgui\TabControle.h"

namespace hfsguardadir {

namespace objetosgui {

//IMPLEMENT_DYNAMIC(TabControle, CTabCtrl)

TabControle::TabControle()
{

}

TabControle::~TabControle()
{
}

void TabControle::adiciona(CTabCtrl &tabControle, const int nIndice, const CString &sTab) {
	TCITEM tcItem;
	tcItem.mask = TCIF_TEXT | TCIF_IMAGE; // | TCIF_PARAM;
	tcItem.pszText = (LPWSTR)sTab.GetString();
	tcItem.cchTextMax = sTab.GetLength();
	tcItem.iImage = 0;
	//tcItem.lParam = (DWORD)&parent;

	tabControle.InsertItem(nIndice, &tcItem);
}

void TabControle::altera(CTabCtrl &tabControle, const int nIndice, const CString &sTab) {
	TCITEM tcItem;
	tcItem.mask = TCIF_TEXT | TCIF_IMAGE; // | TCIF_PARAM;
	tcItem.pszText = (LPWSTR)sTab.GetString();
	tcItem.cchTextMax = sTab.GetLength();
	tcItem.iImage = 0;
	//tcItem.lParam = (DWORD)&parent;

	tabControle.SetItem(nIndice, &tcItem);
}

void TabControle::remove(CTabCtrl &tabControle, const int nIndice) {
	tabControle.DeleteItem(nIndice);
}

/*
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
	case TCN_SELCHANGING:
	{
	return TRUE;
	}
	break;
	}
	return FALSE;
}
*/

//BEGIN_MESSAGE_MAP(TabControle, CTabCtrl)
//END_MESSAGE_MAP()



// TabControle message handlers
}
}
