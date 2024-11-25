#ifndef TABELA_H
#define TABELA_H

#define MAXLINHAS_VISAOLISTA 100000
#define QTD_MAX_COL 9

#include "hfsguardadir/objetos/Diretorio.h"
#include "hfsguardadir/objetos/Extensao.h"

#pragma once

struct SMString {
	CString str[QTD_MAX_COL];
};

using namespace hfsguardadir::objetos;

namespace hfsguardadir {

namespace objetosgui {

class Tabela //: public CListCtrl
{
	//DECLARE_DYNCREATE(Tabela)
	
private:		
	BOOL insere(CListCtrl &tabela, UINT nQtdColunas, const CList<SMString, SMString> sLinhas, INT nImagem);

public:	
	Tabela();
	virtual ~Tabela();

	static int CALLBACK comparaASC(LPARAM item1, LPARAM item2, LPARAM lParamSort);
	static int CALLBACK comparaDESC(LPARAM item1, LPARAM item2, LPARAM lParamSort);

	static void modeloColunas(CListCtrl &tabela, BOOL bTabelaDir, CImageList *imageList16, CImageList *imageList32);
	static BOOL insereColunas(CListCtrl &tabela, UINT largura[], const CStringList &sColunas);
	static BOOL insereLinha(CListCtrl &tabela, UINT nQtdColunas, UINT nLinha, INT nImagem,
		const SMString colunas);
	static void limpar(CListCtrl &tabela);
	static void adiciona(CListCtrl &tabela, BOOL bTabelaDir, CList<Diretorio, Diretorio&> &listaDir,
		CList<Extensao, Extensao&> &listaExtensao, CProgressCtrl *barraProgresso);
	static BOOL isSelecionado(CListCtrl &tabela, UINT nLinha);
	static VOID selecionaLinha(CListCtrl &tabela, UINT nLinha);
	static VOID ScrollLines(CListCtrl &tabela, UINT nLinha);
	static VOID deselecionaLinha(CListCtrl &tabela, UINT nLinha);
	static UINT encontrarLinha(CListCtrl &tabela, const CString &nome);
	static Diretorio* getItemSelecionado(CListCtrl &tabela, BOOL bTabelaDir);
	//static Diretorio* getItemSelecionado();
	//static void setItemSelicionado(Diretorio* dir);

/*
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
*/

};

}
}

#endif
