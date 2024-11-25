#ifndef FRMFILHO_H
#define FRMFILHO_H

struct SFrmFilho {
	HWND tabControl;
	HWND arvore;
	HWND tabela;
	HWND tabelaPesquisa;

	BOOL bAtivaFilho;

	HWND frmFilho;
};
extern struct SFrmFilho FrmFilho;

LRESULT CALLBACK frmFilhoProc(HWND hwnd, UINT Message, WPARAM wParam,
   LPARAM lParam);
BOOL FrmFilho_Criar(HWND hwnd);
BOOL FrmFilho_Ativar(HWND hwnd, WPARAM wParam, LPARAM lParam);
VOID FrmFilho_Fechar(HWND hwnd);
VOID FrmFilho_arvoreExpandirTodos();
VOID FrmFilho_arvoreColapsarTodos();
VOID FrmFilho_redimensionarControles(HWND hwnd, 
	BOOL bMostrarArvore, BOOL bMostrarTabelaPesquisa);
VOID FrmFilho_mostraOcultarArvore();
VOID FrmFilho_mostraOcultarTabelaPesquisa(BOOL bMostrar);
VOID FrmFilho_mostraOcultarTabelaPesquisa();
VOID FrmFilho_setVisao(DWORD nVisao);

#endif
