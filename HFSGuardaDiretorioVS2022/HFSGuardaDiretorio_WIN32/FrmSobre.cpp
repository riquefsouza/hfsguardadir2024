#include "stdafx.h"

#include <windows.h>
#include <commctrl.h>
#include "HFSGuardaDiretorio.h"
#include "resource.h"
#include "FrmSobre.h"
#include "hfsguardadir/comum/Rotinas.h"

struct SFrmSobre FrmSobre;

LRESULT CALLBACK frmSobreProc( HWND hDlg, UINT uMsg, WPARAM wParam, 
    LPARAM lParam )
{
   switch( uMsg ) {
      case WM_INITDIALOG:
      {
		  HFONT hFont = CreateFont(8, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 
			  OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			  DEFAULT_QUALITY, DEFAULT_PITCH, _T("MS Sans Serif"));
		  SendDlgItemMessage(hDlg, ID_FRMSOBRE_LAB1, WM_SETFONT, (WPARAM)hFont, (LPARAM)TRUE);
		  
		  FrmSobre.frmSobre = hDlg;

		  return TRUE;
      }
      break;       
      case WM_COMMAND:
      {
         switch( wParam ) {
            case ID_FRMSOBRE_BTNOK:
               EndDialog( hDlg, TRUE );
               return TRUE;
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

VOID FrmSobre_Mostrar(HWND hwnd) {
	DialogBox(g_hInstancia, MAKEINTRESOURCEW(FRMSOBRE), hwnd,
		(DLGPROC)frmSobreProc);
}