#include "stdafx.h"

#include <windowsx.h>
#include <commctrl.h>
#include <stdio.h>
#include <Strsafe.h>

#include "HFSGuardaDiretorio.h"
#include "FrmPrincipal.h"
#include "FrmImportarDiretorio.h"
#include "resource.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/catalogador/Catalogador.h"
#include "hfsguardadir/objetosgui/Dialogo.h"
#include "hfsguardadir/objetosbo/ImportarBO.h"
#include "hfsguardadir/objetosbo/DiretorioBO.h"
   
struct SFrmImportarDiretorio FrmImportarDiretorio;

LRESULT CALLBACK frmImportarDiretorioProc(HWND hwnd, UINT Message, WPARAM wParam, 
    LPARAM lParam )
{ 
   switch( Message ) {
      case WM_INITDIALOG:
      {      
		  int iStatusWidths[] = { 250, -1 };
		  
		  FrmImportarDiretorio.barraStatus = CreateWindowEx(0, STATUSCLASSNAME, NULL,
			  WS_CHILD | WS_VISIBLE, 0, 0, 0, 0,
			  hwnd, (HMENU)ID_FRMCOMPARARDIRETORIO_BARRASTATUS1, g_hInstancia, NULL);
		  SendMessage(FrmImportarDiretorio.barraStatus, SB_SETPARTS, 2, (LPARAM)iStatusWidths);
		  SendMessage(FrmImportarDiretorio.barraStatus, SB_SETTEXT, 0,
			  (LPARAM)Rotinas_lerStr(STR_FRMIMPORTARDIRETORIO_BARRASTATUS1));

		  FrmImportarDiretorio.memoImportaDir = GetDlgItem(hwnd, ID_FRMIMPORTARDIRETORIO_MEMOIMPORTADIR);
		  FrmImportarDiretorio.pbImportar = Rotinas_pegaBarraProgresso(hwnd, ID_FRMIMPORTARDIRETORIO_PBIMPORTAR, 0, 100, 1);
		  
		  //SendMessage(hFrmImportarDiretorio.memoImportaDir, EM_SETWORDBREAKPROC, 0,
			//  (LPARAM)frmImportarDiretorio_EditWordBreakProc);
		  //frmImportarDiretorio_EditWordBreakProc = (int)SendMessage(hFrmImportarDiretorio.memoImportaDir, EM_GETWORDBREAKPROC, 0, 0);
		  
		  FrmImportarDiretorio.frmImportarDiretorio = hwnd;

        return TRUE;
      }
      break;       	  
	  case WM_CLOSE:
		  EndDialog(hwnd, TRUE);
      break;
   }
  
   return FALSE;
}

int CALLBACK FrmImportarDiretorio_EditWordBreakProc(LPTSTR lpch, int ichCurrent, int cch, int code) {
	OutputDebugString(lpch);
	return TRUE;
}

VOID FrmImportarDiretorio_AppendText(HWND hwndEdit, TCHAR *stexto){
	DWORD posInicio, posFim;

	SendMessage(hwndEdit, EM_GETSEL, (WPARAM)(&posInicio), (LPARAM)(&posFim));

	int tamanho = GetWindowTextLength(hwndEdit);
	SendMessage(hwndEdit, EM_SETSEL, tamanho, tamanho);
	SendMessage(hwndEdit, EM_REPLACESEL, TRUE, (LPARAM)(stexto));
	SendMessage(hwndEdit, EM_SETSEL, posInicio, posFim);
}

/*
VOID FrmImportarDiretorio_Mostrar(HWND hwnd) {
	DialogBox(g_hInstancia, MAKEINTRESOURCEW(FRMIMPORTARDIRETORIO), hwnd,
		(DLGPROC)frmImportarDiretorioProc);
}
*/

BOOL FrmImportarDiretorio_Criar(HWND hwndPai)
{
	FrmImportarDiretorio.frmImportarDiretorio = CreateDialog(g_hInstancia,
		MAKEINTRESOURCEW(FRMIMPORTARDIRETORIO), hwndPai, (DLGPROC)frmImportarDiretorioProc);

	if (!FrmImportarDiretorio.frmImportarDiretorio) {
		MessageBox(0, Rotinas_lerStr(STR_NCCRIADLG), _T("Erro"), MB_ICONERROR | MB_OK);
		return FALSE;
	}

	return TRUE;
}

VOID FrmImportarDiretorio_Mostrar() {
	ShowWindow(FrmImportarDiretorio.frmImportarDiretorio, SW_SHOW);
	UpdateWindow(FrmImportarDiretorio.frmImportarDiretorio);
}


void FrmImportarDiretorio_ProgressoLog(Progresso progresso)
{
	if (FrmImportarDiretorio.frmImportarDiretorio != NULL) {
		if (progresso.posicao == 0) {
			SendMessage(FrmImportarDiretorio.pbImportar, PBM_SETRANGE, 0, MAKELPARAM(progresso.minimo, progresso.maximo));
			SendMessage(FrmImportarDiretorio.pbImportar, PBM_SETSTEP, progresso.passo, 0);
		}
		SendMessage(FrmImportarDiretorio.pbImportar, PBM_SETPOS, progresso.posicao, 0);

		if (progresso.log.length > 0) {
			int pos = Edit_GetLineCount(FrmImportarDiretorio.memoImportaDir);

			progresso.log = String_concatenar(progresso.log, "\n");
			FrmImportarDiretorio_AppendText(FrmImportarDiretorio.memoImportaDir, progresso.log.wstr);		

			Edit_Scroll(FrmImportarDiretorio.memoImportaDir, pos, 0);
			SendMessage(FrmImportarDiretorio.barraStatus, SB_SETTEXT, 1, (LPARAM)String_FromInt(pos).wstr);
		}
	}
}


VOID FrmImportarDiretorio_iniciarImportacao(HWND hwnd) {
	String sLog;
	ListaString log = ListaString_inicia();
	ListaImportar local;
	Importar importar;

	for (local = FrmImportarDiretorio.listaImportar; local != NULL; local = local->proximo) {
		importar = local->importar;

		Catalogador.diretorioOrdem.ordem = 1;

		if (!FrmImportarDiretorio.bSubDiretorio) {
			SetCursor(LoadCursor(NULL, IDC_WAIT));

			ImportarBO_ImportacaoCompleta(importar,
				&Catalogador.diretorioOrdem, Catalogador.listaExtensoes,
				FrmImportarDiretorio_ProgressoLog);

			SetCursor(LoadCursor(NULL, IDC_ARROW));
		}
		else {
			if (!DiretorioBO_verificaCodDir(importar.aba,
				importar.rotuloRaiz, Catalogador.listaDiretorioPai)) {
				SetCursor(LoadCursor(NULL, IDC_WAIT));

				ImportarBO_ImportacaoCompleta(importar,
					&Catalogador.diretorioOrdem, Catalogador.listaExtensoes,
					FrmImportarDiretorio_ProgressoLog);

				SetCursor(LoadCursor(NULL, IDC_ARROW));
			}
			else {
				Dialogo_mensagemInfo(hwnd,
					STR_FRMIMPORTARDIRETORIO_DIRETORIOEXISTECATALOGO);
			}
		}
	}

	if (Catalogador.bGravarLogImportacao) {
		int tamanho = GetWindowTextLength(FrmImportarDiretorio.memoImportaDir);
		if (tamanho > 0) {
			sLog = String_iniciar(Rotinas_AppDirPath());
			sLog = String_concatenar(Rotinas_BARRA_INVERTIDA, 
				Rotinas_formataDate(Rotinas_FORMATO_DHARQUIVO, Rotinas_DataHoraNow()),
				"_Importacao.log");

			int nLinhas = Edit_GetLineCount(FrmImportarDiretorio.memoImportaDir);
			String sLinha = String_iniciar("");
			for (int i = 0; i < nLinhas; i++)
			{
				Edit_GetLine(FrmImportarDiretorio.memoImportaDir, i, sLinha.wstr, TAM_MAX_STR);
				sLinha = String_copiar(sLinha.wstr);
				ListaString_insereFim(&log, sLinha);
			}
			Rotinas_SListSaveToFile(log, sLog);
			ListaString_removeTodos(&log);
		}
	}

	//EndDialog(FrmImportarDiretorio.frmImportarDiretorio, TRUE);
}

