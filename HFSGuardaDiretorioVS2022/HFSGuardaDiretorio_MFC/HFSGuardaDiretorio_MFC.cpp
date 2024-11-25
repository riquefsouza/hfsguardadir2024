
// HFSGuardaDiretorio.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "HFSGuardaDiretorio.h"
#include "FrmPrincipal.h"

#include "FrmMDIFilho.h"
#include "hfsguardadir\comum\Rotinas.h"
#include "hfsguardadir/catalogador/Catalogador.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// HFSGuardaDiretorio

BEGIN_MESSAGE_MAP(HFSGuardaDiretorio, CWinApp)
END_MESSAGE_MAP()

using namespace hfsguardadir::comum;
using namespace hfsguardadir::catalogador;

// HFSGuardaDiretorio construction

HFSGuardaDiretorio::HFSGuardaDiretorio()
{
	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("HFSGuardaDiretorio.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only HFSGuardaDiretorio object

HFSGuardaDiretorio theApp;


// HFSGuardaDiretorio initialization

BOOL HFSGuardaDiretorio::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2() is required to use RichEdit control	
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	if (!Rotinas::getInstancia()->VerificaInstancia(_T("HFSGuardaDiretorio"), 
		NULL))
		return FALSE;

	// try to load shared MDI menus and accelerator table
	//TODO: add additional member variables and load calls for
	//	additional menu types your application may need
	HINSTANCE hInst = AfxGetResourceHandle();
	this->m_hMDIMenu = ::LoadMenu(hInst, MAKEINTRESOURCE(IDC_HFSGUARDADIRETORIO));
	this->m_hMDIAccel = ::LoadAccelerators(hInst, MAKEINTRESOURCE(IDC_HFSGUARDADIRETORIO));

	//Rotinas::testar();

	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object
	frmPrincipal = new FrmPrincipal();
	if (!frmPrincipal)
		return FALSE;
	m_pMainWnd = frmPrincipal;
	// create main MDI frame window
	if (!frmPrincipal->LoadFrame(IDC_HFSGUARDADIRETORIO))
		return FALSE;

	catalogo = new Catalogador();

	// The main window has been initialized, so show and update it
	frmPrincipal->ShowWindow(m_nCmdShow);
	frmPrincipal->UpdateWindow();

	return TRUE;
}

int HFSGuardaDiretorio::ExitInstance()
{
	//TODO: handle additional resources you may have added
	if (m_hMDIMenu != NULL)
		FreeResource(m_hMDIMenu);
	if (m_hMDIAccel != NULL)
		FreeResource(m_hMDIAccel);

	return CWinApp::ExitInstance();
}
