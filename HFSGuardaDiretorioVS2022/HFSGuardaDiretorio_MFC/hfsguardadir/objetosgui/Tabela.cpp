#include "stdafx.h"
#include "HFSGuardaDiretorio.h"
#include "hfsguardadir\objetosgui\Tabela.h"
#include "hfsguardadir/objetosbo/ExtensaoBO.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/catalogador/Catalogador.h"
#include "FrmPrincipal.h"
#include "resource.h"

using namespace hfsguardadir::comum;
using namespace hfsguardadir::objetosbo;
using namespace hfsguardadir::objetosgui;
using namespace hfsguardadir::catalogador;

namespace hfsguardadir {

namespace objetosgui {

//IMPLEMENT_DYNCREATE(Tabela, CListCtrl)

//Diretorio* itemSelicionado;

Tabela::Tabela()
{

}

Tabela::~Tabela()
{
}

BOOL Tabela::insereColunas(CListCtrl &tabela, UINT largura[], const CStringList &sColunas)
{
	LV_COLUMN lvc;
	INT nColunas;
	POSITION pos;
	CString scol;

	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvc.fmt = LVCFMT_LEFT;

	nColunas = -1;
	for (int i = 0; i < sColunas.GetSize(); ++i) {
		pos = sColunas.FindIndex(i);
		scol = sColunas.GetAt(pos);

		nColunas++;
		lvc.cx = largura[nColunas];
		lvc.iSubItem = nColunas;
		lvc.pszText = (LPWSTR)scol.GetString();
		if (tabela.InsertColumn(nColunas, &lvc) == -1)
			return FALSE;
	}
	tabela.SetItemCount(MAXLINHAS_VISAOLISTA);
	return TRUE;
}

BOOL Tabela::insereLinha(CListCtrl &tabela, UINT nQtdColunas, UINT nLinha, INT nImagem,
	const SMString colunas)
{
	LVITEM lvItem;

	lvItem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
	lvItem.state = LVIS_FOCUSED | LVIS_SELECTED; //0;
	lvItem.stateMask = LVIS_FOCUSED | LVIS_SELECTED; //0;     
	lvItem.iItem = nLinha;
	lvItem.iImage = nImagem;
	lvItem.iSubItem = 0;
	lvItem.lParam = (LPARAM)nLinha;
	lvItem.pszText = (LPWSTR)colunas.str[0].GetString();
	lvItem.cchTextMax = TAM_MAX_STR;

	if (tabela.InsertItem(&lvItem) == -1)
		return FALSE;
	else {
		for (UINT nColuna = 1; nColuna < nQtdColunas; nColuna++)
		{
			tabela.SetItemText(nLinha, nColuna, colunas.str[nColuna].GetString());
		}
	}
	return TRUE;
}

BOOL Tabela::insere(CListCtrl &tabela, UINT nQtdColunas, const CList<SMString, SMString> sLinhas, INT nImagem)
{
	UINT nLinha;
	POSITION pos;
	SMString sitem;

	tabela.DeleteAllItems();

	nLinha = -1;
	for (int i = 0; i < sLinhas.GetSize(); ++i) {
		pos = sLinhas.FindIndex(i);
		sitem = sLinhas.GetAt(pos);

		nLinha++;
		if (!insereLinha(tabela, nQtdColunas, nLinha, nImagem, sitem))
			return FALSE;
	}

	return TRUE;
}

int CALLBACK Tabela::comparaASC(LPARAM item1, LPARAM item2, LPARAM lParamSort)
{
	if (item1 > item2)
		return 1;
	if (item1 < item2)
		return -1;

	return 0;
}

int CALLBACK Tabela::comparaDESC(LPARAM item1, LPARAM item2, LPARAM lParamSort)
{
	if (item1 < item2)
		return 1;
	if (item1 > item2)
		return -1;

	return 0;
}

void Tabela::modeloColunas(CListCtrl &tabela, BOOL bTabelaDir, CImageList *imageList16, CImageList *imageList32) {
	CStringList sColunas;

	//Tabela::bTabelaDir = bTabelaDir;

	tabela.SetImageList(imageList32, LVSIL_NORMAL);
	tabela.SetImageList(imageList16, LVSIL_SMALL);

	if (bTabelaDir) {
		UINT nLargura[] = { 300, 100, 70, 120, 90, 500 };

		sColunas.AddTail(_T("Nome"));
		sColunas.AddTail(_T("Tamanho"));
		sColunas.AddTail(_T("Tipo"));
		sColunas.AddTail(_T("Modificado"));
		sColunas.AddTail(_T("Atributos"));
		sColunas.AddTail(_T("Caminho"));

		insereColunas(tabela, nLargura, sColunas);
	}
	else {
		UINT nLargura[] = { 300, 100, 70, 120, 90, 300, 70, 0, 0 };

		sColunas.AddTail(_T("Nome"));
		sColunas.AddTail(_T("Tamanho"));
		sColunas.AddTail(_T("Tipo"));
		sColunas.AddTail(_T("Modificado"));
		sColunas.AddTail(_T("Atributos"));
		sColunas.AddTail(_T("Caminho"));
		sColunas.AddTail(_T("Aba"));
		sColunas.AddTail(_T("Numero Aba"));
		sColunas.AddTail(_T("Nome do Pai"));

		insereColunas(tabela, nLargura, sColunas);
	}
}

void Tabela::limpar(CListCtrl &tabela) {
	tabela.DeleteAllItems();
}

void Tabela::adiciona(CListCtrl &tabela, BOOL bTabelaDir, CList<Diretorio, Diretorio&> &listaDir,
	CList<Extensao, Extensao&> &listaExtensao, CProgressCtrl *barraProgresso) {
	POSITION pos;
	Diretorio dir;
	CString sLinha = _T("");
	UINT nQtdColunas = 0;
	UINT nTamListaDir = listaDir.GetSize();
	int nIndiceImagem;
	SMString sColuna;

	tabela.DeleteAllItems();

	
	barraProgresso->SetRange32(0, nTamListaDir-1);
	barraProgresso->SetStep(1);
	barraProgresso->SetPos(0);

	for (int i = 0; i < listaDir.GetSize(); ++i) {
		pos = listaDir.FindIndex(i);
		dir = listaDir.GetAt(pos);

		sColuna.str[0] = dir.getNome();

		if (dir.getTipo().getCodigo() == 'D') {
			sColuna.str[1] = _T("");
			nIndiceImagem = 0;
		}
		else {
			nIndiceImagem = ExtensaoBO::getInstancia()->indiceExtensao(
				listaExtensao, dir.getNome());

			if (nIndiceImagem == -1) {
				nIndiceImagem = 1;
			}

			sColuna.str[1] = dir.getTamanhoFormatado();
		}
		sColuna.str[2] = dir.getTipo().getNome();
		sColuna.str[3] = dir.getModificadoFormatado();
		sColuna.str[4] = dir.getAtributos();
		sColuna.str[5] = dir.getCaminho();

		if (bTabelaDir) {
			nQtdColunas = 6;
			sColuna.str[6] = _T("");
			sColuna.str[7] = _T("");
			sColuna.str[8] = _T("");
		}
		else {
			nQtdColunas = 9;
			sColuna.str[6] = dir.getAba().getNome();
			sColuna.str[7] = Rotinas::FromInt(dir.getAba().getCodigo());
			sColuna.str[8] = dir.getNomePai();
		}
		insereLinha(tabela, nQtdColunas, i, nIndiceImagem, sColuna);

		barraProgresso->SetPos(i);
	}
	//barraProgresso->SetPos(0);
}

BOOL Tabela::isSelecionado(CListCtrl &tabela, UINT nLinha) {
	if (tabela.GetSelectedCount() > 0) {
		return (tabela.GetItemState(nLinha, LVIS_SELECTED) == LVIS_SELECTED);
	}

	return false;
}

VOID Tabela::selecionaLinha(CListCtrl &tabela, UINT nLinha) {
	tabela.SetItemState(nLinha, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
	tabela.EnsureVisible(nLinha, FALSE);
}

VOID Tabela::ScrollLines(CListCtrl &tabela, UINT nLinha) {
	tabela.Scroll(CSize(0, nLinha));
}

VOID Tabela::deselecionaLinha(CListCtrl &tabela, UINT nLinha) {
	tabela.SetItemState(nLinha, 0, 0);
}

UINT Tabela::encontrarLinha(CListCtrl &tabela, const CString &nome) {
	LPWSTR slinha = Rotinas::NewStr();
	UINT nlinha = 0;

	for (INT i = 0; i < tabela.GetItemCount(); i++) {
		tabela.GetItemText(i, 0, slinha, TAM_MAX_STR);

		if (lstrcmp(slinha, nome.GetString()) == 0) {
			nlinha = i;
			break;
		}
	}
	return nlinha;
}

Diretorio* Tabela::getItemSelecionado(CListCtrl &tabela, BOOL bTabelaDir) {
	WCHAR slinha[TAM_MAX_STR];
	Diretorio *dir = NULL;	
	int nLinha;
	Aba aba;
	Tipo tipo;
	
	if (tabela.GetSelectedCount() > 0) {
		dir = new Diretorio();

		nLinha = tabela.GetSelectionMark();
		
		slinha[0] = '\0';
		tabela.GetItemText(nLinha, 0, slinha, TAM_MAX_STR);
		dir->setNome(slinha);

		slinha[0] = '\0';
		tabela.GetItemText(nLinha, 1, slinha, TAM_MAX_STR);
		dir->setTamanhoFormatado(slinha);

		slinha[0] = '\0';
		tabela.GetItemText(nLinha, 2, slinha, TAM_MAX_STR);
		tipo.setNome(slinha);

		if (tipo.getNome() == Rotinas::lerStr(STR_TIPOLISTA_DIRETORIO)) {
			tipo.setCodigo('D');
		}
		else {
			tipo.setCodigo('A');
		}
		dir->setTipo(tipo);

		slinha[0] = '\0';
		tabela.GetItemText(nLinha, 3, slinha, TAM_MAX_STR);
		dir->setModificadoFormatado(slinha);

		slinha[0] = '\0';
		tabela.GetItemText(nLinha, 4, slinha, TAM_MAX_STR);
		dir->setAtributos(slinha);

		slinha[0] = '\0';
		tabela.GetItemText(nLinha, 5, slinha, TAM_MAX_STR);
		dir->setCaminho(slinha);

		if (!bTabelaDir) {
			slinha[0] = '\0';
			tabela.GetItemText(nLinha, 6, slinha, TAM_MAX_STR);
			aba.setNome(slinha);

			slinha[0] = '\0';
			tabela.GetItemText(nLinha, 7, slinha, TAM_MAX_STR);
			aba.setCodigo(slinha[0]);

			dir->setAba(aba);

			slinha[0] = '\0';
			tabela.GetItemText(nLinha, 8, slinha, TAM_MAX_STR);
			dir->setCaminhoPai(slinha);
		}
	}

	return dir;
}

/*
Diretorio* Tabela::getItemSelecionado() {
	return itemSelicionado;
}

void Tabela::setItemSelicionado(Diretorio* dir) {
	itemSelicionado = dir;
}

BEGIN_MESSAGE_MAP(Tabela, CListCtrl)	
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, &Tabela::OnLvnColumnclick)
	ON_NOTIFY_REFLECT(NM_CLICK, &Tabela::OnNMClick)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &Tabela::OnNMDblclk)
END_MESSAGE_MAP()

// Tabela message handlers
void Tabela::OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	static BOOL bOrdemColuna = TRUE;
	bOrdemColuna = !bOrdemColuna;

	if (bOrdemColuna)
		this->SortItems(Tabela::comparaASC, 0);
	else
		this->SortItems(Tabela::comparaDESC, 0);


	*pResult = 0;
}

void Tabela::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	Diretorio* dir = getLinhaSelecionada(bTabelaDir, pNMItemActivate->iItem);
	itemSelicionado = *dir;
	
	*pResult = 0;
}

void Tabela::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	if (this->GetSelectedCount() > 0) {
		if (bTabelaDir) {
			catalogador->DuploCliqueLista(itemSelicionado.getNome(),
				itemSelicionado.getTipo().getNome());
		}
		else {
			catalogador->EncontrarItemLista(itemSelicionado.getAba().getNome(),
				itemSelicionado.getNome(), itemSelicionado.getCaminho());
		}
	}
	
	*pResult = 0;
}

// Tabela diagnostics

#ifdef _DEBUG
void Tabela::AssertValid() const
{
	CListCtrl::AssertValid();
}

#ifndef _WIN32_WCE
void Tabela::Dump(CDumpContext& dc) const
{
	CListCtrl::Dump(dc);
}
#endif
#endif //_DEBUG
*/

}
}
