#include "stdafx.h"

#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <commctrl.h>

#include "resource.h"
#include "FrmPrincipal.h"
#include "FrmFilho.h"
#include "hfsguardadir/comum/ListaString.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/objetosgui/TabControle.h"
#include "hfsguardadir/objetosgui/Arvore.h"
#include "hfsguardadir/objetosgui/Tabela.h"
#include "resource.h"
#include "HFSGuardaDiretorio.h"
#include "FrmInfoDiretorio.h"

struct SFrmFilho FrmFilho;
static bool bMostrarArvore = TRUE, bMostrarTabelaPesquisa = FALSE;
RECT rectFilho, rectArvore, rectTabControl, rectTabela, rectTabelaPesquisa;
UINT alturaFilho, larguraFilho, alturaTabControl, larguraArvore, alturaTabela, 
alturaTabelaPesquisa, alturaArvoreTabela;
HWND hTelaAtiva;

LRESULT CALLBACK frmFilhoProc(HWND hwnd, UINT Message, WPARAM wParam,
   LPARAM lParam)
{
	switch (Message)
	{
	case WM_CREATE:
	{
		//Remover botoes da janela
		LONG_PTR style = GetWindowLongPtr(hwnd, GWL_STYLE);
		SetWindowLongPtr(hwnd, GWL_STYLE, style & ~WS_SYSMENU);
	}
	break;
	case WM_INITDIALOG:
	{
		FrmFilho.tabControl = GetDlgItem(hwnd, ID_FRMPRINCIPAL_TABCONTROL);
		FrmFilho.arvore = GetDlgItem(hwnd, ID_FRMPRINCIPAL_ARVORE);
		FrmFilho.tabela = GetDlgItem(hwnd, ID_FRMPRINCIPAL_TABELA);
		FrmFilho.tabelaPesquisa = GetDlgItem(hwnd, ID_FRMPRINCIPAL_TABELAPESQUISA);

		TabCtrl_SetImageList(FrmFilho.tabControl, FrmPrincipal.imageListTabs);
		TreeView_SetImageList(FrmFilho.arvore, FrmPrincipal.imageList16, LVSIL_NORMAL);

		Tabela_modeloColunas(FrmFilho.tabela, TRUE, 
			FrmPrincipal.imageList16, FrmPrincipal.imageList32);
		Tabela_modeloColunas(FrmFilho.tabelaPesquisa, FALSE, 
			FrmPrincipal.imageList16, FrmPrincipal.imageList32);

		return TRUE;
	}
	break;
	case WM_MDIACTIVATE:
	{
		FrmFilho.bAtivaFilho = FrmFilho_Ativar(hwnd, wParam, lParam);
		return FALSE;
	}
	break;
	case WM_NOTIFY:
	{
		TabControle_notifica(FrmFilho.tabControl, lParam, FrmFilho.arvore, FrmFilho.tabela);
		Arvore_notifica(hwnd, FrmFilho.arvore, wParam, lParam, ID_FRMPRINCIPAL_ARVORE);
		Tabela_notifica(FrmFilho.tabela, wParam, lParam, ID_FRMPRINCIPAL_TABELA, TRUE);
		Tabela_notifica(FrmFilho.tabelaPesquisa, wParam, lParam, ID_FRMPRINCIPAL_TABELAPESQUISA, FALSE);
	}
	break;
	case WM_SIZE:
	{
		FrmFilho_redimensionarControles(hwnd, bMostrarArvore, bMostrarTabelaPesquisa);
	}
	break;
	case WM_DESTROY:
	{
		FrmFilho_Fechar(hwnd);
	}
	break;
	}
   
   return DefMDIChildProc(hwnd, Message, wParam, lParam);
}

BOOL FrmFilho_Criar(HWND hwnd)
{ 
  
  FrmFilho.frmFilho = CreateDialog((HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),
	  MAKEINTRESOURCEW(FRMPRINCIPAL), hTelaAtiva, (DLGPROC)frmFilhoProc);
    
  if (!FrmFilho.frmFilho) {
    MessageBox(0, Rotinas_lerStr(STR_NCCRIADLG), _T("Erro"), MB_ICONERROR | MB_OK);
    return FALSE;    
  }
  SetWindowLong(hwnd, HWNDMDIFILHA, (LONG)FrmFilho.frmFilho);

  hTelaAtiva = FrmFilho.frmFilho;

  return TRUE;
}

BOOL FrmFilho_Ativar(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
if (GET_WM_MDIACTIVATE_FACTIVATE(hwnd, wParam, lParam) &&
    (hTelaAtiva != hwnd))
  hTelaAtiva = hwnd;

return (hwnd == (HWND)lParam);
}

VOID FrmFilho_Fechar(HWND hwnd)
{
  DLGPROC lpDlgProc;
  
  lpDlgProc = (DLGPROC)GetWindowLong(
    (HWND)GetWindowLong(hwnd, HWNDMDIFILHA), DWL_DLGPROC);
  DestroyWindow((HWND)GetWindowLong(hwnd, HWNDMDIFILHA));
  FreeProcInstance(lpDlgProc);
  if (hwnd == hTelaAtiva)
   hTelaAtiva = (HWND)NULL;  
}

VOID FrmFilho_arvoreExpandirTodos() {
	Arvore_expandirTodos(FrmFilho.arvore);
}

VOID FrmFilho_arvoreColapsarTodos() {
	Arvore_colapsarTodos(FrmFilho.arvore);
}

VOID FrmFilho_redimensionarControles(HWND hwnd, 
	BOOL bMostrarArvore, BOOL bMostrarTabelaPesquisa) {
	GetClientRect(hwnd, &rectFilho);
	GetWindowRect(FrmFilho.tabControl, &rectTabControl);
	GetWindowRect(FrmFilho.arvore, &rectArvore);
	GetWindowRect(FrmFilho.tabela, &rectTabela);
	GetWindowRect(FrmFilho.tabelaPesquisa, &rectTabelaPesquisa);

	alturaFilho = rectFilho.bottom - rectFilho.top;
	larguraFilho = rectFilho.right - rectFilho.left;
	alturaTabControl = rectTabControl.bottom - rectTabControl.top;
	larguraArvore = rectArvore.right - rectArvore.left;
	alturaTabela = rectTabela.bottom - rectTabela.top;
	alturaTabelaPesquisa = rectFilho.bottom - 300;
	alturaArvoreTabela = alturaFilho - alturaTabelaPesquisa - alturaTabControl;

	MoveWindow(FrmFilho.tabControl, 0, 0, larguraFilho, alturaTabControl, TRUE);
	MoveWindow(FrmFilho.arvore, 0, alturaTabControl, larguraArvore, alturaArvoreTabela, TRUE);

	if (bMostrarArvore) {
		ShowWindow(FrmFilho.arvore, SW_SHOW);
		MoveWindow(FrmFilho.tabela, larguraArvore, alturaTabControl,
			rectFilho.right - larguraArvore, alturaArvoreTabela, TRUE);
	}
	else {
		ShowWindow(FrmFilho.arvore, SW_HIDE);
		MoveWindow(FrmFilho.tabela, 0, alturaTabControl,
			rectFilho.right, alturaFilho - alturaTabControl, TRUE);
	}

	if (bMostrarTabelaPesquisa) {
		ShowWindow(FrmFilho.tabelaPesquisa, SW_SHOW);
		MoveWindow(FrmFilho.arvore, 0, alturaTabControl, larguraArvore, alturaArvoreTabela, TRUE);
		
		MoveWindow(FrmFilho.tabelaPesquisa, 0, alturaTabControl + alturaArvoreTabela,
			larguraFilho, alturaTabelaPesquisa, TRUE);
	}
	else {
		ShowWindow(FrmFilho.tabelaPesquisa, SW_HIDE);
		
		MoveWindow(FrmFilho.tabelaPesquisa, 0, alturaTabControl + alturaArvoreTabela,
			larguraFilho, alturaTabelaPesquisa, TRUE);

		MoveWindow(FrmFilho.arvore, 0, alturaTabControl, larguraArvore, 
			alturaFilho - alturaTabControl, TRUE);

		if (bMostrarArvore) {
			MoveWindow(FrmFilho.tabela, larguraArvore, alturaTabControl,
				rectFilho.right - larguraArvore, alturaFilho - alturaTabControl, TRUE);
		}
		else {
			MoveWindow(FrmFilho.tabela, 0, alturaTabControl,
				rectFilho.right, alturaFilho - alturaTabControl, TRUE);
		}

	}

}

VOID FrmFilho_mostraOcultarArvore() {
	bMostrarArvore = !bMostrarArvore;

	FrmFilho_redimensionarControles(FrmFilho.frmFilho, bMostrarArvore, bMostrarTabelaPesquisa);
		
}

VOID FrmFilho_mostraOcultarTabelaPesquisa(BOOL bMostrar) {
	FrmFilho_redimensionarControles(FrmFilho.frmFilho, bMostrarArvore, bMostrar);
}

VOID FrmFilho_mostraOcultarTabelaPesquisa() {
	bMostrarTabelaPesquisa = !bMostrarTabelaPesquisa;

	FrmFilho_mostraOcultarTabelaPesquisa(bMostrarTabelaPesquisa);
}

VOID FrmFilho_setVisao(DWORD nVisao) {
	ListView_SetView(FrmFilho.tabela, nVisao);
	//SendMessage(GetDlgItem(hwnd, ID_FRMPRINCIPAL_TABELA), LVM_SETVIEW, LV_VIEW_ICON, 0);
	//UpdateWindow()
	
	//ListView_SetView(FrmFilho.tabela, LV_VIEW_ICON);
	
	//LVM_SETVIEW, 

	//UpdateWindow(FrmFilho.tabela);
	//LV_VIEW_DETAILS
	//LV_VIEW_ICON
	//LV_VIEW_LIST
	//LV_VIEW_SMALLICON
	//LV_VIEW_TILE
}