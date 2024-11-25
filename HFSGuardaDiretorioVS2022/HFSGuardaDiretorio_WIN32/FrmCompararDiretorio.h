#ifndef FRMCOMPARARDIRETORIO_H
#define FRMCOMPARARDIRETORIO_H

#include "hfsguardadir/objetos/Aba.h"
#include "hfsguardadir/objetos/Diretorio.h"

struct SFrmCompararDiretorio {
	HWND btnCompararDiretorios;
	HWND pb;
	HWND btnSalvarLog;
	HWND cmbAba1;
	HWND arvoreDir1;
	HWND cmbAba2;
	HWND arvoreDir2;
	HWND tabelaCompara;
	HWND barraStatus;

	ListaDiretorio listaCompara;
	HIMAGELIST imageList16, imageList32;

	HWND frmCompararDiretorio;
};
extern struct SFrmCompararDiretorio FrmCompararDiretorio;

LRESULT CALLBACK frmCompararDiretorioProc( HWND hDlg, UINT uMsg, WPARAM wParam, 
    LPARAM lParam );
VOID FrmCompararDiretorio_Mostrar(HWND hwnd);
VOID FrmCompararDiretorio_Delete();
void FrmCompararDiretorio_ProgressoLog(Progresso progresso);
void FrmCompararDiretorio_LimparComparacao();
String FrmCompararDiretorio_BarraStatusGetStatusText(int indice);
void FrmCompararDiretorio_btnCompararDiretoriosClick(HWND hwnd);
void FrmCompararDiretorio_btnSalvarLogClick(HWND hwnd);
void FrmCompararDiretorio_cmbAba1Choice();
void FrmCompararDiretorio_cmbAba2Choice();
void FrmCompararDiretorio_montarArvores();
String FrmCompararDiretorio_SQLCompara(Aba aba1, Aba aba2, String caminho1,
	String caminho2);
void FrmCompararDiretorio_Comparar(HWND hwnd, String sCaminhoDir1, String sCaminhoDir2);

#endif
