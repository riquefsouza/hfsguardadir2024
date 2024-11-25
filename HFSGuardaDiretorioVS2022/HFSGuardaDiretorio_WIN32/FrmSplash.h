#ifndef FRMSPLASH_H
#define FRMSPLASH_H

#include "hfsguardadir/comum/Rotinas.h"

struct SFrmSplash {
	HWND pb1;
	HWND frmSplash;
};
extern struct SFrmSplash FrmSplash;

LRESULT CALLBACK frmSplashProc( HWND hDlg, UINT uMsg, WPARAM wParam, 
    LPARAM lParam );
void FrmSplash_ProgressoLog(Progresso progresso);
BOOL FrmSplash_Criar(HWND hwndPai);
VOID FrmSplash_Mostrar();

#endif


