// FrmSobre.cpp : implementation file
//

#include "stdafx.h"
#include "HFSGuardaDiretorio.h"
#include "FrmSobre.h"
#include "afxdialogex.h"


// FrmSobre dialog

IMPLEMENT_DYNAMIC(FrmSobre, CDialogEx)

FrmSobre::FrmSobre(CWnd* pParent /*=NULL*/)
	: CDialogEx(FRMSOBRE, pParent)
{

}

FrmSobre::~FrmSobre()
{
}

void FrmSobre::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_FRMSOBRE_LAB1, label1);
}


BEGIN_MESSAGE_MAP(FrmSobre, CDialogEx)
	ON_BN_CLICKED(ID_FRMSOBRE_BTNOK, &FrmSobre::OnBnClicked_BtnOk)
END_MESSAGE_MAP()


// FrmSobre message handlers


void FrmSobre::OnBnClicked_BtnOk()
{
	this->EndDialog(TRUE);
}


BOOL FrmSobre::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CFont fonte;
	fonte.CreateFontW(8, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, _T("MS Sans Serif"));

	label1.SetFont(&fonte, TRUE);

	return TRUE;
}
