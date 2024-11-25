// FrmSplash.cpp : implementation file
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "HFSGuardaDiretorio.h"
#include "FrmSplash.h"

FrmSplash *frmSplash;

IMPLEMENT_DYNAMIC(FrmSplash, CDialogEx)

FrmSplash::FrmSplash(CWnd* pParent /*=NULL*/)
	: CDialogEx(FRMSPLASH, pParent)
{

}

FrmSplash::~FrmSplash()
{
}

void FrmSplash::ProgressoLog(Progresso progresso)
{
	if (frmSplash != NULL) {
		if (progresso.posicao == 0) {
			frmSplash->pb.SetRange32(progresso.minimo, progresso.maximo);
			frmSplash->pb.SetStep(progresso.passo);
		}

		frmSplash->pb.SetPos(progresso.posicao);
	}

}

bool FrmSplash::Criar(CWnd* hwndPai)
{
	if (!frmSplash->Create(MAKEINTRESOURCEW(FRMSPLASH), hwndPai)) {
		hwndPai->MessageBox(Rotinas::lerStr(STR_NCCRIADLG), _T("Erro"), MB_ICONERROR | MB_OK);
		return false;
	}

	return true;
}

VOID FrmSplash::Mostrar() {	
	frmSplash->ShowWindow(SW_SHOW);
	frmSplash->UpdateWindow();
}

void FrmSplash::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_FRMSPLASH_PB, pb);
}


BEGIN_MESSAGE_MAP(FrmSplash, CDialogEx)
END_MESSAGE_MAP()


// FrmSplash message handlers


BOOL FrmSplash::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	Rotinas::setBarraProgresso(&pb, 0, 100, 1);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
