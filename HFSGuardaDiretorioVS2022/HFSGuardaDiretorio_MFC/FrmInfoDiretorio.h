#pragma once

#include "hfsguardadir/objetos/Diretorio.h"
#include "afxcmn.h"

using namespace hfsguardadir::objetos;

class FrmInfoDiretorio : public CDialogEx
{
	DECLARE_DYNAMIC(FrmInfoDiretorio)

private:		
	bool insereLinha(int nLinha, const CString &stexto);

public:	
	Diretorio diretorio;
	FrmInfoDiretorio(CWnd* pParent = NULL);   // standard constructor
	virtual ~FrmInfoDiretorio();
	VOID setDiretorio(Diretorio diretorio);
	static VOID Mostrar(Diretorio diretorio);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = FRMINFODIRETORIO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl tabelaInfo;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClicked_BtnOk();
	
};

