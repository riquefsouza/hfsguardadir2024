// FrmEntrada.cpp : implementation file
//

#include "stdafx.h"
#include "HFSGuardaDiretorio.h"
#include "FrmEntrada.h"
#include "afxdialogex.h"
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::comum;

IMPLEMENT_DYNAMIC(FrmEntrada, CDialogEx)

FrmEntrada::FrmEntrada(CWnd* pParent /*=NULL*/)
	: CDialogEx(FRMENTRADA, pParent)
{

}

FrmEntrada::~FrmEntrada()
{
}

void FrmEntrada::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_FRMENTRADA_EDIT, edtEntrada);
	DDX_Control(pDX, ID_FRMENTRADA_LABEL, labEntrada);
}


BEGIN_MESSAGE_MAP(FrmEntrada, CDialogEx)
	ON_BN_CLICKED(ID_FRMENTRADA_BTNOK, &FrmEntrada::OnBnClicked_BtnOk)
	ON_BN_CLICKED(ID_FRMENTRADA_BTNCANCELAR, &FrmEntrada::OnBnClicked_BtnCancelar)
END_MESSAGE_MAP()


// FrmEntrada message handlers


void FrmEntrada::OnBnClicked_BtnOk()
{
	edtEntrada.GetWindowTextW(retorno);
	this->EndDialog(TRUE);
}


void FrmEntrada::OnBnClicked_BtnCancelar()
{
	this->EndDialog(TRUE);
}


BOOL FrmEntrada::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	this->SetWindowText(titulo);

	edtEntrada.SetLimitText(TAM_MAX_STR);
	labEntrada.SetWindowTextW(rotulo);
	edtEntrada.SetWindowTextW(texto);

	edtEntrada.SetFocus();

	CenterWindow();

	return FALSE;
}

CString FrmEntrada::Mostrar(CWnd *pai, 
	const CString &titulo, const CString &rotulo, const CString &texto) {
	
	FrmEntrada frmEntrada(pai);

	frmEntrada.titulo = titulo;
	frmEntrada.rotulo = rotulo;
	frmEntrada.texto = texto;

	frmEntrada.retorno = _T("");
		
	frmEntrada.DoModal();
	frmEntrada.DestroyWindow();
	
	return frmEntrada.retorno;
}