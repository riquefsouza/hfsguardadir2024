#include "stdafx.h"

#include <commctrl.h>

#include "resource.h"
#include "hfsguardadir/objetosgui/BarraPesquisar.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/catalogador/Catalogador.h"
#include "FrmPrincipal.h"

struct SFrmBarraPesquisar FrmBarraPesquisar;

LRESULT CALLBACK frmBarraPesquisarProc(HWND hwnd, UINT Message, WPARAM wParam, 
    LPARAM lParam )
{ 
   switch( Message ) {
      case WM_INITDIALOG:
      {      
		  FrmBarraPesquisar.btnImportarDiretorio = GetDlgItem(hwnd, ID_FRMPRINCIPAL_BTNIMPORTARDIRETORIO);
		  FrmBarraPesquisar.pb = Rotinas_pegaBarraProgresso(hwnd, ID_FRMPRINCIPAL_PB, 0, 100, 1);
		  FrmBarraPesquisar.edtPesquisa = GetDlgItem(hwnd, ID_FRMPRINCIPAL_EDTPESQUISA);
		  FrmBarraPesquisar.btnPesquisa = GetDlgItem(hwnd, ID_FRMPRINCIPAL_BTNPESQUISAR);

		  FrmBarraPesquisar.frmBarraPesquisar = hwnd;

        return TRUE;
      }
      break;       
      case WM_ACTIVATE:
      {
         return FALSE;
      }
      break;      
      case WM_COMMAND:
      {
        switch( LOWORD(wParam) ) {
          case ID_FRMPRINCIPAL_BTNIMPORTARDIRETORIO: 
          {                       
			  Catalogador_ComecaImportacao(FALSE, FrmPrincipal_ProgressoLog);
          }
          break;
          case ID_FRMPRINCIPAL_BTNPESQUISAR: 
          {     
			  Catalogador_Pesquisar();
          }
          break;
        }
      }   
      break;
      case WM_CLOSE:
      {
        EndDialog(hwnd, TRUE);
        return TRUE;
      }
      break;
   }
  
   return FALSE;
}

