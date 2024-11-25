#pragma once

#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/objetos/Diretorio.h"
#include "hfsguardadir/objetos/Importar.h"
#include "afxwin.h"
#include "afxcmn.h"

using namespace hfsguardadir::comum;
using namespace hfsguardadir::objetos;

class FrmImportarDiretorio : public CDialogEx
{
	DECLARE_DYNAMIC(FrmImportarDiretorio)

public:
	BOOL bSubDiretorio;
	CList<Importar, Importar&>* listaImportar;
	
	FrmImportarDiretorio(CWnd* pParent = NULL);   // standard constructor
	virtual ~FrmImportarDiretorio();
	static int CALLBACK EditWordBreakProc(LPTSTR lpch, int ichCurrent, int cch, int code);	
	static bool Criar(CWnd* hwndPai);
	static VOID Mostrar();
	static void ProgressoLog(Progresso progresso);
	VOID AppendText(CEdit &edit, const CString &stexto);
	VOID iniciarImportacao();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = FRMIMPORTARDIRETORIO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit memoImportaDir;
	CProgressCtrl pbImportar;
	CStatusBar  barraStatus;
	virtual BOOL OnInitDialog();
};

extern FrmImportarDiretorio *frmImportarDiretorio;
