// FrmInfoDiretorio.cpp : implementation file
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "HFSGuardaDiretorio.h"
#include "FrmInfoDiretorio.h"
#include "FrmPrincipal.h"
#include "FrmInfoDiretorio.h"
#include "resource.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/objetosgui/Tabela.h"

using namespace hfsguardadir::comum;
using namespace hfsguardadir::objetosgui;

IMPLEMENT_DYNAMIC(FrmInfoDiretorio, CDialogEx)

FrmInfoDiretorio::FrmInfoDiretorio(CWnd* pParent /*=NULL*/)
	: CDialogEx(FRMINFODIRETORIO, pParent)
{

}

FrmInfoDiretorio::~FrmInfoDiretorio()
{
}

bool FrmInfoDiretorio::insereLinha(int nLinha, const CString &stexto)
{
	LVITEM lvItem;

	lvItem.mask = LVIF_TEXT | LVIF_PARAM | LVIF_STATE; //  | LVIF_IMAGE
	lvItem.state = LVIS_FOCUSED | LVIS_SELECTED;
	lvItem.stateMask = LVIS_FOCUSED | LVIS_SELECTED;

	lvItem.iItem = nLinha;
	lvItem.iSubItem = 0;
	lvItem.pszText = (LPWSTR)stexto.GetString();
	lvItem.cchTextMax = lstrlen(stexto);

	if (tabelaInfo.InsertItem(&lvItem) == -1)
		return false;
	else
		return true;
}

VOID FrmInfoDiretorio::setDiretorio(Diretorio diretorio)
{
	int nLinha = 0;

	this->insereLinha(nLinha, _T("Aba:"));
	tabelaInfo.SetItemText(nLinha, 1, diretorio.getAba().getNome());
	nLinha++;

	this->insereLinha(nLinha, _T("Nome:"));
	tabelaInfo.SetItemText(nLinha, 1, diretorio.getNome());
	nLinha++;

	this->insereLinha(nLinha, _T("Tamanho:"));
	tabelaInfo.SetItemText(nLinha, 1, diretorio.getTamanhoFormatado());
	nLinha++;

	this->insereLinha(nLinha, _T("Tipo:"));
	tabelaInfo.SetItemText(nLinha, 1, diretorio.getTipo().getNome());
	nLinha++;

	this->insereLinha(nLinha, _T("Modificado:"));
	tabelaInfo.SetItemText(nLinha, 1, diretorio.getModificadoFormatado());
	nLinha++;

	this->insereLinha(nLinha, _T("Atributos:"));
	tabelaInfo.SetItemText(nLinha, 1, diretorio.getAtributos());
	nLinha++;

	this->insereLinha(nLinha, _T("Caminho:"));
	tabelaInfo.SetItemText(nLinha, 1, diretorio.getCaminho());

	tabelaInfo.SetColumnWidth(1, diretorio.getCaminho().GetLength() * 8);
}

VOID FrmInfoDiretorio::Mostrar(Diretorio diretorio) {
	FrmInfoDiretorio *frmInfoDiretorio = new FrmInfoDiretorio();
	frmInfoDiretorio->diretorio = diretorio;
	frmInfoDiretorio->DoModal();
	frmInfoDiretorio->DestroyWindow();
}

void FrmInfoDiretorio::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_FRMINFODIRETORIO_LVINFO, tabelaInfo);
}


BEGIN_MESSAGE_MAP(FrmInfoDiretorio, CDialogEx)
	ON_BN_CLICKED(ID_FRMINFODIRETORIO_BTNOK, &FrmInfoDiretorio::OnBnClicked_BtnOk)
END_MESSAGE_MAP()


// FrmInfoDiretorio message handlers


BOOL FrmInfoDiretorio::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CStringList sColunas;
	UINT nLargura[] = { 100, 100 };

	sColunas.AddTail(_T("Item"));
	sColunas.AddTail(_T("Descrição"));

	Tabela::insereColunas(tabelaInfo, nLargura, sColunas);

	setDiretorio(diretorio);

	return TRUE;
}

void FrmInfoDiretorio::OnBnClicked_BtnOk()
{
	this->EndDialog(TRUE);
}
