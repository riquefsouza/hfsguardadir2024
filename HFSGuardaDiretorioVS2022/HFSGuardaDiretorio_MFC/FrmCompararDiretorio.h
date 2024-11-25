#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "hfsguardadir\comum\Rotinas.h"
#include "hfsguardadir\objetos\Diretorio.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

class FrmCompararDiretorio : public CDialogEx
{
	DECLARE_DYNAMIC(FrmCompararDiretorio)

private:	
	CList<Diretorio, Diretorio&>* listaCompara;
	CImageList *imageList16, *imageList32;
	CString BarraStatusGetStatusText(int indice);

public:	
	FrmCompararDiretorio(CWnd* pParent = NULL);   // standard constructor
	virtual ~FrmCompararDiretorio();

	static void ProgressoLog(Progresso progresso);	
	void montarArvores();
	void LimparComparacao();
	CString SQLCompara(Aba aba1, Aba aba2, const CString &caminho1,
		const CString &caminho2);
	void Comparar(const CString &sCaminhoDir1, const CString &sCaminhoDir2);
	
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = FRMCOMPARARDIRETORIO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CButton btnCompararDiretorios;
	CProgressCtrl pb;
	CButton btnSalvarLog;
	CComboBox cmbAba1;
	CTreeCtrl arvoreDir1;
	CComboBox cmbAba2;
	CTreeCtrl arvoreDir2;
	CListCtrl tabelaCompara;
	CStatusBar  barraStatus;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClicked_BtnCompararDiretorios();
	afx_msg void OnBnClicked_BtnSalvarLog();
	afx_msg void OnCbnSelchange_CmbAba1();
	afx_msg void OnCbnSelchange_CmbAba2();
	afx_msg void OnLvnColumnclick_TabelaCompara(NMHDR *pNMHDR, LRESULT *pResult);
};

extern FrmCompararDiretorio *frmCompararDiretorio;
