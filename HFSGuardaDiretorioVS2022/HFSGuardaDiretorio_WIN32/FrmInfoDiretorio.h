#ifndef FRMINFODIRETORIO_H
#define FRMINFODIRETORIO_H

#include "hfsguardadir/objetos/Diretorio.h"

struct SFrmInfoDiretorio {
	HWND tabelaInfo;
	Diretorio diretorio;

	HWND frmInfoDiretorio;
};
extern struct SFrmInfoDiretorio FrmInfoDiretorio;

LRESULT CALLBACK frmInfoDiretorioProc( HWND hDlg, UINT uMsg, WPARAM wParam, 
    LPARAM lParam );
BOOL FrmInfoDiretorio_insereLinha(HWND hwndTabela, INT nLinha, LPWSTR stexto);
VOID FrmInfoDiretorio_setDiretorio(HWND hwndTabela, Diretorio diretorio);
VOID FrmInfoDiretorio_Mostrar(HWND hwnd, Diretorio diretorio);

#endif
