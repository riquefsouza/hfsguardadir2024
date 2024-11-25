#ifndef FRMPRINCIPAL_H
#define FRMPRINCIPAL_H

#include "hfsguardadir/comum/String.h"
#include "hfsguardadir/comum/Rotinas.h"

#define ID_BARRADESTATUS        50001

#define ID_MDI_CLIENTE          50003
#define ID_MDI_PRIMEIROFORM     50004

#define HWNDMDIFILHA            0

struct SFrmPrincipal {
	HWND menuGravarLogImportacao;
	HWND notebook1;
	HWND sp;
	HWND arvoreFixa;
	HWND tabelaFixa;
	HWND tabelaPesquisa;
	HWND barraStatus;

	HIMAGELIST imageListTabs, imageList16, imageList32;

	HWND frmPrincipal;
	HWND MDICliente;
};
extern struct SFrmPrincipal FrmPrincipal;

VOID FrmPrincipal_criaImageListTabs(HWND hwnd);
LRESULT CALLBACK frmPrincipalProc(HWND hwnd, UINT Message, WPARAM wParam,
   LPARAM lParam);
VOID FrmPrincipal_Delete();
VOID FrmPrincipal_OnContextMenu(HWND hwnd, LPARAM lParam);
String FrmPrincipal_BarraStatusGetStatusText(int indice);
void FrmPrincipal_ProgressoLog(Progresso progresso);

#endif
