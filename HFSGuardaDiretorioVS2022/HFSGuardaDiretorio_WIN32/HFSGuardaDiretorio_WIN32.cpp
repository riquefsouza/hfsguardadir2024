// HFSGuardaDiretorio.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include <commctrl.h>

#include "resource.h"
#include "HFSGuardaDiretorio.h"
#include "FrmPrincipal.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/objetosdao/AbaDAO.h"
#include "hfsguardadir/comum/String.h"
#include "hfsguardadir/catalogador/Catalogador.h"
#include "FrmSplash.h"
#include "FrmFilho.h"

HINSTANCE g_hInstancia;
static LPCWSTR sNomeApp = _T("HFSGuardaDiretorio");
HWND hDlgAtual;

void testarDAO() {
	String sApp = Rotinas_AppDirPath();
	sApp = Rotinas_AppFileName();
	sApp = Rotinas_AppDirName();
	sApp = String_concatenar(sApp, "GuardaDir.db");
	Rotinas_BancoConectar(sApp);

	ListaAba lista = AbaDAO_consultarTudo(NULL);

	ListaAba local;
	for (local = lista; local != NULL; local = local->proximo){		
		OutputDebugString(String_concatenar(local->aba.nome,"\n").wstr);
	}

	ListaAba_removeTodos(&lista);

	Aba aba;
	aba.codigo = 3;
	aba.nome = String_copiar("DISCO3");
	aba.ordem = 3;
	AbaDAO_incluir(aba);

	Rotinas_BancoDesconectar();
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	MSG  Msg;
	WNDCLASSEX WndClassEx;
	HACCEL  hAccel;
	HWND  hMDIFilha, hTemp;
	BOOL  bDialogMessage = FALSE;

	InitCommonControls();

	g_hInstancia = hInstance;

	/* Checa se a aplicação já está rodando,
	se estiver então ativa e então atribui o foco */

	if (FrmPrincipal.frmPrincipal = FindWindow(sNomeApp, NULL)) {
		FrmPrincipal.frmPrincipal = GetLastActivePopup(FrmPrincipal.frmPrincipal);

		MessageBox(0, Rotinas_lerStr(STR_APPEXEC),
			_T("Erro"), MB_ICONEXCLAMATION | MB_OK);

		if (IsIconic(FrmPrincipal.frmPrincipal))
			OpenIcon(FrmPrincipal.frmPrincipal);
		else
			BringWindowToTop(FrmPrincipal.frmPrincipal);

		SetForegroundWindow(FrmPrincipal.frmPrincipal);
		return FALSE;
	}

	/* Registrar janela principal */

	WndClassEx.cbSize = sizeof(WNDCLASSEX);
	WndClassEx.style = CS_HREDRAW | CS_VREDRAW;
	WndClassEx.lpfnWndProc = frmPrincipalProc;
	WndClassEx.cbClsExtra = 0;
	WndClassEx.cbWndExtra = 0;
	WndClassEx.hInstance = hInstance;
	WndClassEx.hIcon = LoadIcon(hInstance,
		MAKEINTRESOURCE(IDI_HFSGUARDADIRETORIO));
	WndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClassEx.hbrBackground = (HBRUSH)(COLOR_3DSHADOW + 1);
	WndClassEx.lpszMenuName = MAKEINTRESOURCEW(IDC_HFSGUARDADIRETORIO);
	WndClassEx.lpszClassName = sNomeApp;
	WndClassEx.hIconSm = LoadIcon(hInstance,
		MAKEINTRESOURCE(IDI_SMALL));

	if (!RegisterClassEx(&WndClassEx))
	{
		MessageBox(0, Rotinas_lerStr(STR_NREGJAN), _T("Erro"), MB_ICONERROR | MB_OK);
		return -1;
	}

	/* Registrar a janela Filho */
	Rotinas_RegistrarClasseForm(WndClassEx, frmFilhoProc,
		MAKEINTRESOURCEW(FRMPRINCIPAL));

	FrmPrincipal.frmPrincipal = CreateWindowEx(WS_EX_APPWINDOW, sNomeApp,
		Rotinas_lerStr(STR_FRMPRINCIPAL_TITULO), WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		0, 0, hInstance, NULL);

	if (FrmPrincipal.frmPrincipal == NULL) {
		MessageBox(0, Rotinas_lerStr(STR_SEMJAN), _T("Erro"), MB_ICONERROR | MB_OK);
		return -1;
	}

	//String_testar();
	//testarDAO();
	
	Catalogador_New();

	/* Mostrar tela principal */
	ShowWindow(FrmPrincipal.frmPrincipal, nCmdShow);
	UpdateWindow(FrmPrincipal.frmPrincipal);

	hAccel = LoadAccelerators(g_hInstancia, MAKEINTRESOURCE(ID_ACELERADORES));

	while (GetMessage(&Msg, NULL, 0, 0))
	{
		/* Processa as teclas de atalho rápidas */
		if (TranslateAccelerator(FrmPrincipal.frmPrincipal, hAccel, &Msg))
			continue;
		/* Processa as tabulações da tela principal */
		if (TranslateMDISysAccel(FrmPrincipal.MDICliente, &Msg))
			continue;
		/* Processa as tabulações das dialogs não modais */
		if (hDlgAtual != NULL && IsDialogMessage(hDlgAtual, &Msg))
			continue;

		/* Cada Tela da MDI tem uma dialog não modal na sua área cliente
		para prover o controle da tabulação. Checa as mensagens das dialogs. */
		for (hMDIFilha = GetWindow(FrmPrincipal.MDICliente, GW_CHILD);
			hMDIFilha; hMDIFilha = GetWindow(hMDIFilha, GW_HWNDNEXT)) {
			hTemp = (HWND)GetWindowLong(hMDIFilha, HWNDMDIFILHA);
			if (hTemp != NULL && IsDialogMessage(hTemp, &Msg)) {
				bDialogMessage = TRUE;
				break;
			}
		}

		if (bDialogMessage) {
			bDialogMessage = FALSE;
			continue;
		}

		TranslateMessage(&Msg);
		DispatchMessage(&Msg);

	}
	return Msg.wParam;

}
