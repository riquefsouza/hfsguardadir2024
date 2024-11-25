#include "stdafx.h"

#include <windows.h>
#include <commctrl.h>
#include "HFSGuardaDiretorio.h"
#include "resource.h"
#include "FrmSplash.h"

struct SFrmSplash FrmSplash;

LRESULT CALLBACK frmSplashProc(HWND hDlg, UINT uMsg, WPARAM wParam, 
    LPARAM lParam )
{
   UINT idTimer = 1;
   switch( uMsg ) {
      case WM_INITDIALOG:
      {      
		FrmSplash.pb1 = Rotinas_pegaBarraProgresso(hDlg, ID_FRMSPLASH_PB, 0, 100, 1);
		
        //SetTimer(hDlg, idTimer, 3000, (TIMERPROC) NULL); 

		FrmSplash.frmSplash = hDlg;

        return TRUE;
      }  
      break;       
      case WM_PAINT:
      {     
        RECT rc;    
        GetClientRect(hDlg, &rc);
        Rotinas_copiaBitmap(hDlg, BITMAP_SPLASH,rc);
      }  
      break;
	  /*
      case WM_TIMER:       
         EndDialog( hDlg, TRUE );
      break;      
	  */
      case WM_CLOSE:
         EndDialog( hDlg, TRUE );
      break;
   }
  
   return FALSE;
}

void FrmSplash_ProgressoLog(Progresso progresso)
{
	if (FrmSplash.frmSplash != NULL) {
		if (progresso.posicao == 0) {
			SendMessage(FrmSplash.pb1, PBM_SETRANGE, 0, MAKELPARAM(progresso.minimo, progresso.maximo));
			SendMessage(FrmSplash.pb1, PBM_SETSTEP, progresso.passo, 0);
		}

		SendMessage(FrmSplash.pb1, PBM_SETPOS, progresso.posicao, 0);
	}

}

BOOL FrmSplash_Criar(HWND hwndPai)
{
	FrmSplash.frmSplash = CreateDialog(g_hInstancia,
		MAKEINTRESOURCEW(FRMSPLASH), hwndPai, (DLGPROC)frmSplashProc);

	if (!FrmSplash.frmSplash) {
		MessageBox(0, Rotinas_lerStr(STR_NCCRIADLG), _T("Erro"), MB_ICONERROR | MB_OK);
		return FALSE;
	}
	
	return TRUE;
}

VOID FrmSplash_Mostrar() {
	ShowWindow(FrmSplash.frmSplash, SW_SHOW);
	UpdateWindow(FrmSplash.frmSplash);
}

