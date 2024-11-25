// FrmFilho.cpp : implementation file
//

#include "stdafx.h"
#include "HFSGuardaDiretorio.h"
#include "FrmFilho.h"
#include "afxdialogex.h"
#include "FrmPrincipal.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/objetosgui/TabControle.h"
#include "hfsguardadir/objetosgui/Arvore.h"
#include "hfsguardadir/objetosgui/Tabela.h"
#include "hfsguardadir/catalogador/Catalogador.h"
#include "resource.h"
#include "FrmInfoDiretorio.h"

using namespace hfsguardadir::comum;
using namespace hfsguardadir::objetosgui;
using namespace hfsguardadir::catalogador;

IMPLEMENT_DYNAMIC(FrmFilho, CDialogEx)

static bool bMostrarArvore = true;
static bool bMostrarTabelaPesquisa = false;

FrmFilho::FrmFilho(CWnd* pParent /*=NULL*/)
	: CDialogEx(FRMPRINCIPAL, pParent)
{
	bIniciou = false;
}

FrmFilho::~FrmFilho()
{
}

void FrmFilho::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_FRMPRINCIPAL_TABCONTROL, tabControl);
	DDX_Control(pDX, ID_FRMPRINCIPAL_ARVORE, arvore);
	DDX_Control(pDX, ID_FRMPRINCIPAL_TABELA, tabela);
	DDX_Control(pDX, ID_FRMPRINCIPAL_TABELAPESQUISA, tabelaPesquisa);
}


BEGIN_MESSAGE_MAP(FrmFilho, CDialogEx)
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, ID_FRMPRINCIPAL_TABCONTROL, &FrmFilho::OnTcnSelchange_TabControl)
	ON_NOTIFY(LVN_COLUMNCLICK, ID_FRMPRINCIPAL_TABELA, &FrmFilho::OnLvnColumnclick_Tabela)
	ON_NOTIFY(LVN_COLUMNCLICK, ID_FRMPRINCIPAL_TABELAPESQUISA, &FrmFilho::OnLvnColumnclick_TabelaPesquisa)
	ON_NOTIFY(NM_CLICK, ID_FRMPRINCIPAL_TABELA, &FrmFilho::OnNMClick_Tabela)
	ON_NOTIFY(NM_CLICK, ID_FRMPRINCIPAL_TABELAPESQUISA, &FrmFilho::OnNMClick_TabelaPesquisa)
	ON_NOTIFY(NM_DBLCLK, ID_FRMPRINCIPAL_TABELA, &FrmFilho::OnNMDblclk_Tabela)
	ON_NOTIFY(NM_DBLCLK, ID_FRMPRINCIPAL_TABELAPESQUISA, &FrmFilho::OnNMDblclk_TabelaPesquisa)
	ON_NOTIFY(TVN_SELCHANGED, ID_FRMPRINCIPAL_ARVORE, &FrmFilho::OnTvnSelchanged_Arvore)
	ON_NOTIFY(TVN_SELCHANGING, ID_FRMPRINCIPAL_ARVORE, &FrmFilho::OnTvnSelchanging_Arvore)
	ON_NOTIFY(NM_CLICK, ID_FRMPRINCIPAL_ARVORE, &FrmFilho::OnNMClick_Arvore)
	ON_NOTIFY(NM_DBLCLK, ID_FRMPRINCIPAL_ARVORE, &FrmFilho::OnNMDblclk_Arvore)
END_MESSAGE_MAP()


// FrmFilho message handlers


void FrmFilho::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (bIniciou)
		redimensionarControles(bMostrarArvore, bMostrarTabelaPesquisa);
}

VOID FrmFilho::arvoreExpandirTodos() {
	Arvore::expandirTodos(arvore);
}

VOID FrmFilho::arvoreColapsarTodos() {
	Arvore::colapsarTodos(arvore);
}

void FrmFilho::redimensionarControles(bool bMostrarArvore, bool bMostrarTabelaPesquisa) {
	RECT rectFilho, rectArvore, rectTabControl, rectTabela, rectTabelaPesquisa;
	UINT alturaFilho, larguraFilho, alturaTabControl, larguraArvore, alturaTabela,
		alturaTabelaPesquisa, alturaArvoreTabela;

	GetClientRect(&rectFilho);
	tabControl.GetWindowRect(&rectTabControl);
	arvore.GetWindowRect(&rectArvore);
	tabela.GetWindowRect(&rectTabela);
	tabelaPesquisa.GetWindowRect(&rectTabelaPesquisa);

	alturaFilho = rectFilho.bottom - rectFilho.top;
	larguraFilho = rectFilho.right - rectFilho.left;
	alturaTabControl = rectTabControl.bottom - rectTabControl.top;
	larguraArvore = rectArvore.right - rectArvore.left;
	alturaTabela = rectTabela.bottom - rectTabela.top;
	alturaTabelaPesquisa = rectFilho.bottom - 300;
	alturaArvoreTabela = alturaFilho - alturaTabelaPesquisa - alturaTabControl;

	tabControl.MoveWindow(0, 0, larguraFilho, alturaTabControl, TRUE);
	arvore.MoveWindow(0, alturaTabControl, larguraArvore, alturaArvoreTabela, TRUE);

	if (bMostrarArvore) {
		arvore.ShowWindow(SW_SHOW);
		tabela.MoveWindow(larguraArvore, alturaTabControl,
			rectFilho.right - larguraArvore, alturaArvoreTabela, TRUE);
	}
	else {
		arvore.ShowWindow(SW_HIDE);
		tabela.MoveWindow(0, alturaTabControl,
			rectFilho.right, alturaFilho - alturaTabControl, TRUE);
	}

	if (bMostrarTabelaPesquisa) {
		tabelaPesquisa.ShowWindow(SW_SHOW);
		arvore.MoveWindow(0, alturaTabControl, larguraArvore, alturaArvoreTabela, TRUE);

		tabelaPesquisa.MoveWindow(0, alturaTabControl + alturaArvoreTabela,
			larguraFilho, alturaTabelaPesquisa, TRUE);
	}
	else {
		tabelaPesquisa.ShowWindow(SW_HIDE);

		tabelaPesquisa.MoveWindow(0, alturaTabControl + alturaArvoreTabela,
			larguraFilho, alturaTabelaPesquisa, TRUE);

		arvore.MoveWindow(0, alturaTabControl, larguraArvore,
			alturaFilho - alturaTabControl, TRUE);

		if (bMostrarArvore) {
			tabela.MoveWindow(larguraArvore, alturaTabControl,
				rectFilho.right - larguraArvore, alturaFilho - alturaTabControl, TRUE);
		}
		else {
			tabela.MoveWindow(0, alturaTabControl,
				rectFilho.right, alturaFilho - alturaTabControl, TRUE);
		}

	}

}

VOID FrmFilho::mostraOcultarArvore() {
	bMostrarArvore = !bMostrarArvore;

	redimensionarControles(bMostrarArvore, bMostrarTabelaPesquisa);
}

VOID FrmFilho::mostraOcultarTabelaPesquisa(bool bMostrar) {
	redimensionarControles(bMostrarArvore, bMostrar);
}

VOID FrmFilho::mostraOcultarTabelaPesquisa() {
	bMostrarTabelaPesquisa = !bMostrarTabelaPesquisa;

	mostraOcultarTabelaPesquisa(bMostrarTabelaPesquisa);
}

VOID FrmFilho::setVisao(int nVisao) {
	tabela.SetView(nVisao);
}

BOOL FrmFilho::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	bIniciou = true;
	redimensionarControles(bMostrarArvore, bMostrarTabelaPesquisa);

	tabControl.SetImageList(frmPrincipal->imageListTabs);
	arvore.SetImageList(frmPrincipal->imageList16, LVSIL_NORMAL);

	Tabela::modeloColunas(tabela, TRUE,
		frmPrincipal->imageList16, frmPrincipal->imageList32);
	Tabela::modeloColunas(tabelaPesquisa, FALSE,
		frmPrincipal->imageList16, frmPrincipal->imageList32);

	return TRUE;
}

void FrmFilho::OnTcnSelchange_TabControl(NMHDR *pNMHDR, LRESULT *pResult)
{
	catalogo->tabPanelMudou();

	*pResult = 0;
}


void FrmFilho::OnLvnColumnclick_Tabela(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	static bool bTabelaOrdemColuna = true;

	bTabelaOrdemColuna = !bTabelaOrdemColuna;

	if (bTabelaOrdemColuna)
		tabela.SortItems(Tabela::comparaASC, 0);
	else
		tabela.SortItems(Tabela::comparaDESC, 0);
	
	*pResult = 0;
}


void FrmFilho::OnLvnColumnclick_TabelaPesquisa(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	static bool bTabelaPesquisaOrdemColuna = true;

	bTabelaPesquisaOrdemColuna = !bTabelaPesquisaOrdemColuna;

	if (bTabelaPesquisaOrdemColuna)
		tabela.SortItems(Tabela::comparaASC, 0);
	else
		tabela.SortItems(Tabela::comparaDESC, 0);

	*pResult = 0;
}


void FrmFilho::OnNMClick_Tabela(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	*pResult = 0;
}


void FrmFilho::OnNMClick_TabelaPesquisa(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	*pResult = 0;
}


void FrmFilho::OnNMDblclk_Tabela(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	if (tabela.GetSelectedCount() > 0) {
		Diretorio dir = *Tabela::getItemSelecionado(tabela, true);
		catalogo->DuploCliqueLista(dir.getNome(),
			dir.getTipo().getNome());
	}


	*pResult = 0;
}


void FrmFilho::OnNMDblclk_TabelaPesquisa(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	if (tabelaPesquisa.GetSelectedCount() > 0) {
		Diretorio dir = *Tabela::getItemSelecionado(tabela, false);
		catalogo->EncontrarItemLista(dir.getAba().getNome(),
			dir.getNome(), dir.getCaminho());
	}

	*pResult = 0;
}


void FrmFilho::OnTvnSelchanged_Arvore(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
		
	HTREEITEM selectedItem = arvore.GetSelectedItem();
	if (selectedItem != NULL)
	{
		//arvore.EnsureVisible(selectedItem);
		//arvore.SelectItem(selectedItem);
		catalogo->arvoreValorMudou(arvore, selectedItem);
	}

	*pResult = 0;
}


void FrmFilho::OnTvnSelchanging_Arvore(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	

	*pResult = 0;
}


void FrmFilho::OnNMClick_Arvore(NMHDR *pNMHDR, LRESULT *pResult)
{
	//OutputDebugString(_T("OnNMClick_Arvore\n"));

	*pResult = 0;
}


void FrmFilho::OnNMDblclk_Arvore(NMHDR *pNMHDR, LRESULT *pResult)
{
	//OutputDebugString(_T("OnNMDblclk_Arvore\n"));
	/*
	HTREEITEM selectedItem = arvore.GetSelectedItem();
	//HTREEITEM selectedItem = (HTREEITEM)SendDlgItemMessage(hwnd, nIdItem, TVM_GETNEXTITEM, TVGN_CARET, NULL);
	if (selectedItem != NULL)
	{
		arvore.EnsureVisible(selectedItem);
		arvore.SelectItem(selectedItem);
		//SendDlgItemMessage(hwnd, nIdItem, TVM_SELECTITEM, TVGN_CARET, (LPARAM)selectedItem);

		catalogo->arvoreValorMudou(arvore, selectedItem);
	}
	*/

	*pResult = 0;
}
