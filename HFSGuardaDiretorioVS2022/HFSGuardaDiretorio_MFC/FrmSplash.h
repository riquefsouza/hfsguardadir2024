#pragma once
#include "afxcmn.h"
#include "hfsguardadir\comum\Rotinas.h"

using namespace hfsguardadir::comum;

class FrmSplash : public CDialogEx
{
	DECLARE_DYNAMIC(FrmSplash)

public:
	FrmSplash(CWnd* pParent = NULL);   // standard constructor
	virtual ~FrmSplash();
	static void ProgressoLog(Progresso progresso);
	static bool Criar(CWnd* hwndPai);
	static VOID Mostrar();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = FRMSPLASH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl pb;
	virtual BOOL OnInitDialog();
};

extern FrmSplash *frmSplash;
