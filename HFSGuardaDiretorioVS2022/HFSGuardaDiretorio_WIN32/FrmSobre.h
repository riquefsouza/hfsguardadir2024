#ifndef FRMSOBRE_H
#define FRMSOBRE_H

struct SFrmSobre {
	HWND frmSobre;
};
extern struct SFrmSobre FrmSobre;

LRESULT CALLBACK frmSobreProc( HWND hDlg, UINT uMsg, WPARAM wParam, 
    LPARAM lParam );
VOID FrmSobre_Mostrar(HWND hwnd);

#endif


