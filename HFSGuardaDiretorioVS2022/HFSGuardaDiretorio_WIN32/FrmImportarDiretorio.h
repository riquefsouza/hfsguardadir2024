#ifndef FRMIMPORTARDIRETORIO_H
#define FRMIMPORTARDIRETORIO_H

#include "hfsguardadir\objetos\Importar.h"

struct SFrmImportarDiretorio {
	HWND memoImportaDir;
	HWND pbImportar;
	HWND barraStatus;

	BOOL bSubDiretorio;
	ListaImportar listaImportar;
	
	HWND frmImportarDiretorio;
};
extern struct SFrmImportarDiretorio FrmImportarDiretorio;

LRESULT CALLBACK frmImportarDiretorioProc( HWND hDlg, UINT uMsg, WPARAM wParam, 
    LPARAM lParam );
VOID FrmImportarDiretorio_AppendText(HWND hwndEdit, TCHAR *stexto);
int CALLBACK FrmImportarDiretorio_EditWordBreakProc(LPTSTR lpch, int ichCurrent, int cch, int code);
BOOL FrmImportarDiretorio_Criar(HWND hwndPai);
VOID FrmImportarDiretorio_Mostrar();
void FrmImportarDiretorio_ProgressoLog(Progresso progresso);
VOID FrmImportarDiretorio_iniciarImportacao(HWND hwnd);

#endif
