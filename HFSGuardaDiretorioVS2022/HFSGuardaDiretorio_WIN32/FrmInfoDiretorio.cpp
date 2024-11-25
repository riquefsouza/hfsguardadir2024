#include "stdafx.h"

#include <windows.h>
#include <commctrl.h>

#include "HFSGuardaDiretorio.h"
#include "FrmPrincipal.h"
#include "FrmInfoDiretorio.h"
#include "resource.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/objetosgui/Tabela.h"

struct SFrmInfoDiretorio FrmInfoDiretorio;

LRESULT CALLBACK frmInfoDiretorioProc(HWND hwnd, UINT Message, WPARAM wParam, 
    LPARAM lParam )
{ 
   switch( Message ) {
      case WM_INITDIALOG:
      {      			
		  ListaString sColunas;
		  sColunas = ListaString_inicia();
		  UINT nLargura[] = { 100, 100 };

		  FrmInfoDiretorio.tabelaInfo = GetDlgItem(hwnd, ID_FRMINFODIRETORIO_LVINFO);
		  
		  ListaString_insereFim(&sColunas, String_iniciar("Item"));
		  ListaString_insereFim(&sColunas, String_iniciar("Descrição"));
		  
		  Tabela_insereColunas(FrmInfoDiretorio.tabelaInfo, nLargura, sColunas);
		  
		  FrmInfoDiretorio_setDiretorio(FrmInfoDiretorio.tabelaInfo, FrmInfoDiretorio.diretorio);

		  FrmInfoDiretorio.frmInfoDiretorio = hwnd;

		  return TRUE;
      }
      break;       
	  case WM_COMMAND:
	  {
		  switch (wParam) {
		  case ID_FRMINFODIRETORIO_BTNOK:
			  EndDialog(hwnd, TRUE);
			  return TRUE;
		  }
	  }
	  break;
	  case WM_CLOSE:
	  {
		  EndDialog(hwnd, FALSE);
	  }
	  break;
   }
  
   return FALSE;
}

BOOL FrmInfoDiretorio_insereLinha(HWND hwndTabela, INT nLinha, LPWSTR stexto)
{
	LVITEM lvItem;

	lvItem.mask = LVIF_TEXT | LVIF_PARAM | LVIF_STATE; //  | LVIF_IMAGE
	lvItem.state = LVIS_FOCUSED | LVIS_SELECTED;
	lvItem.stateMask = LVIS_FOCUSED | LVIS_SELECTED;

	lvItem.iItem = nLinha;
	lvItem.iSubItem = 0;
	lvItem.pszText = stexto;
	lvItem.cchTextMax = lstrlen(stexto);

	if (ListView_InsertItem(hwndTabela, &lvItem) == -1)
		return FALSE;
	else
		return TRUE;
}

VOID FrmInfoDiretorio_setDiretorio(HWND hwndTabela, Diretorio diretorio) 
{
	UINT nLinha = 0;

	FrmInfoDiretorio_insereLinha(hwndTabela, nLinha, const_cast<LPTSTR>(TEXT("Aba:")));
	ListView_SetItemText(hwndTabela, nLinha, 1, diretorio.aba.nome.wstr);
	nLinha++;

	FrmInfoDiretorio_insereLinha(hwndTabela, nLinha, const_cast<LPTSTR>(TEXT("Nome:")));
	ListView_SetItemText(hwndTabela, nLinha, 1, diretorio.arquivo.nome.wstr);
	nLinha++;

	FrmInfoDiretorio_insereLinha(hwndTabela, nLinha, const_cast<LPTSTR>(TEXT("Tamanho:")));
	ListView_SetItemText(hwndTabela, nLinha, 1, diretorio.tamanhoFormatado.wstr);
	nLinha++;

	FrmInfoDiretorio_insereLinha(hwndTabela, nLinha, const_cast<LPTSTR>(TEXT("Tipo:")));
	ListView_SetItemText(hwndTabela, nLinha, 1, diretorio.tipo.nome.wstr);
	nLinha++;

	FrmInfoDiretorio_insereLinha(hwndTabela, nLinha, const_cast<LPTSTR>(TEXT("Modificado:")));
	ListView_SetItemText(hwndTabela, nLinha, 1, diretorio.modificadoFormatado.wstr);
	nLinha++;

	FrmInfoDiretorio_insereLinha(hwndTabela, nLinha, const_cast<LPTSTR>(TEXT("Atributos:")));
	ListView_SetItemText(hwndTabela, nLinha, 1, diretorio.arquivo.atributos.wstr);
	nLinha++;

	FrmInfoDiretorio_insereLinha(hwndTabela, nLinha, const_cast<LPTSTR>(TEXT("Caminho:")));
	ListView_SetItemText(hwndTabela, nLinha, 1, diretorio.caminho.wstr);

	ListView_SetColumnWidth(hwndTabela, 1, diretorio.caminho.length * 8);		
}

VOID FrmInfoDiretorio_Mostrar(HWND hwnd, Diretorio diretorio) {
	FrmInfoDiretorio.diretorio = Diretorio_copiar(diretorio);

	DialogBox(g_hInstancia, MAKEINTRESOURCEW(FRMINFODIRETORIO), hwnd,
		(DLGPROC)frmInfoDiretorioProc);
}