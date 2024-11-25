#pragma once
#include "afxwin.h"


// FrmEntrada dialog

class FrmEntrada : public CDialogEx
{
	DECLARE_DYNAMIC(FrmEntrada)

public:
	FrmEntrada(CWnd* pParent = NULL);   // standard constructor
	virtual ~FrmEntrada();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = FRMENTRADA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:	
	CString titulo;
	CString rotulo;
	CString texto;
	CString retorno;
	CEdit edtEntrada;
	CStatic labEntrada;
	static CString Mostrar(CWnd *pai, const CString &titulo, const CString &rotulo, const CString &texto);
	afx_msg void OnBnClicked_BtnOk();
	afx_msg void OnBnClicked_BtnCancelar();
	virtual BOOL OnInitDialog();
};
