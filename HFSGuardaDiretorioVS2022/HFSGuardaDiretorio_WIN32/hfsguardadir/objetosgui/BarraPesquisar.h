#ifndef BARRAPESQUISAR_H
#define BARRAPESQUISAR_H

struct SFrmBarraPesquisar {
	HWND btnImportarDiretorio;
	HWND pb;
	HWND edtPesquisa;
	HWND btnPesquisa;

	HWND frmBarraPesquisar;
};
extern struct SFrmBarraPesquisar FrmBarraPesquisar;

LRESULT CALLBACK frmBarraPesquisarProc( HWND hDlg, UINT uMsg, WPARAM wParam, 
    LPARAM lParam );

#endif
