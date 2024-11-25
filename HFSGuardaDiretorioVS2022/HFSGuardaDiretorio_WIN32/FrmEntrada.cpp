#include "stdafx.h"

#include <windows.h>
#include <commctrl.h>
#include "HFSGuardaDiretorio.h"
#include "resource.h"
#include "FrmEntrada.h"
#include "hfsguardadir/comum/Rotinas.h"

HWND FrmEntrada_Edit;
WCHAR FrmEntrada_titulo[TAM_MAX_STR], FrmEntrada_rotulo[TAM_MAX_STR], FrmEntrada_texto[TAM_MAX_STR];
String FrmEntrada_retorno;

LRESULT CALLBACK frmEntradaProc( HWND hDlg, UINT uMsg, WPARAM wParam, 
    LPARAM lParam )
{
   switch( uMsg ) {
      case WM_INITDIALOG:
      {
		  SetWindowText(hDlg, FrmEntrada_titulo);
		  
		  HWND FrmEntrada_Label = GetDlgItem(hDlg, ID_FRMENTRADA_LABEL);
		  FrmEntrada_Edit = GetDlgItem(hDlg, ID_FRMENTRADA_EDIT);

		  SendMessage(FrmEntrada_Edit, EM_SETLIMITTEXT, (WPARAM)TAM_MAX_STR, 0);
		  
		  SetWindowText(FrmEntrada_Label, FrmEntrada_rotulo);
		  SetWindowText(FrmEntrada_Edit, FrmEntrada_texto);
		  
		  SetFocus(FrmEntrada_Edit);

		  return FALSE;
      }
      break;       
      case WM_COMMAND:
      {
         switch( wParam ) {
		 case ID_FRMENTRADA_BTNOK: {
			 FrmEntrada_retorno = Rotinas_retTexto(FrmEntrada_Edit);
			 EndDialog(hDlg, TRUE);
		 }
		 break;   
		 case ID_FRMENTRADA_BTNCANCELAR: {
			 EndDialog(hDlg, TRUE);
		 }
		 break;   
         }
      }   
      break;
	  case WM_CLOSE:
      {
         EndDialog( hDlg, FALSE );
      }   
      break;
   }
  
   return FALSE;
}

String FrmEntrada_Mostrar(HWND hwnd, LPCWSTR titulo, LPCWSTR rotulo, LPCWSTR texto) {
	lstrcpy(FrmEntrada_titulo, titulo);
	lstrcpy(FrmEntrada_rotulo, rotulo);
	lstrcpy(FrmEntrada_texto, texto);
	
	FrmEntrada_retorno = String_limpar();

	DialogBox(g_hInstancia, MAKEINTRESOURCEW(FRMENTRADA), hwnd,
		(DLGPROC)frmEntradaProc);
	
	return FrmEntrada_retorno;
}