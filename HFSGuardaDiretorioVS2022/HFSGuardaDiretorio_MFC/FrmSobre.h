#pragma once
#include "afxwin.h"


// FrmSobre dialog

class FrmSobre : public CDialogEx
{
	DECLARE_DYNAMIC(FrmSobre)

public:
	FrmSobre(CWnd* pParent = NULL);   // standard constructor
	virtual ~FrmSobre();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = FRMSOBRE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClicked_BtnOk();
	virtual BOOL OnInitDialog();
	CStatic label1;
};
