#pragma once
#include "afxcmn.h"

// FrmFilho dialog

class FrmFilho : public CDialogEx
{
	DECLARE_DYNAMIC(FrmFilho)

private:
	bool bIniciou;
	void redimensionarControles(bool bMostrarArvore, bool bMostrarTabelaPesquisa);

public:
	FrmFilho(CWnd* pParent = NULL);   // standard constructor
	virtual ~FrmFilho();

	VOID arvoreExpandirTodos();
	VOID arvoreColapsarTodos();
	VOID mostraOcultarArvore();
	VOID mostraOcultarTabelaPesquisa(bool bMostrar);
	VOID mostraOcultarTabelaPesquisa();
	VOID setVisao(int nVisao);
	
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = FRMPRINCIPAL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl tabControl;
	CTreeCtrl arvore;
	CListCtrl tabela;
	CListCtrl tabelaPesquisa;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchange_TabControl(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnColumnclick_Tabela(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnColumnclick_TabelaPesquisa(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClick_Tabela(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClick_TabelaPesquisa(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclk_Tabela(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclk_TabelaPesquisa(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchanged_Arvore(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchanging_Arvore(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClick_Arvore(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclk_Arvore(NMHDR *pNMHDR, LRESULT *pResult);
};
