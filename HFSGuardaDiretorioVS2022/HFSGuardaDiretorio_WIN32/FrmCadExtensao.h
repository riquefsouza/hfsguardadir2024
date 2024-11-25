#ifndef FRMCADEXTENSAO_H
#define FRMCADEXTENSAO_H

struct SFrmCadExtensao {
	HWND tabelaExtensao;
	HIMAGELIST imageList16, imageList32;
	HWND frmCadExtensao;
};
extern struct SFrmCadExtensao FrmCadExtensao;

LRESULT CALLBACK frmCadExtensaoProc( HWND hDlg, UINT uMsg, WPARAM wParam, 
    LPARAM lParam );
VOID FrmCadExtensao_Mostrar(HWND hwnd);
void FrmCadExtensao_menuIncluirExtensao(HWND hwnd);
void FrmCadExtensao_menuExcluirExtensao(HWND hwnd);
void FrmCadExtensao_menuExcluirTodasExtensoes(HWND hwnd);
void FrmCadExtensao_menuExportarBitmap(HWND hwnd);
void FrmCadExtensao_menuExportarIcone(HWND hwnd);
void FrmCadExtensao_menuExportarGIF(HWND hwnd);
void FrmCadExtensao_menuExportarJPEG(HWND hwnd);
void FrmCadExtensao_menuExportarPNG(HWND hwnd);
void FrmCadExtensao_menuExportarTIFF(HWND hwnd);
void FrmCadExtensao_menuImportarIconesArquivos(HWND hwnd);
void FrmCadExtensao_menuExtrairIconesArquivos(HWND hwnd);
void FrmCadExtensao_CarregarExtensoesNaGrid();

#endif
