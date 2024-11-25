
// HFSGuardaDiretorio.h : main header file for the HFSGuardaDiretorio application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// HFSGuardaDiretorio:
// See HFSGuardaDiretorio.cpp for the implementation of this class
//

class HFSGuardaDiretorio : public CWinApp
{
public:
	HMENU  m_hMDIMenu;
	HACCEL m_hMDIAccel;

	HFSGuardaDiretorio();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
protected:

public:
	DECLARE_MESSAGE_MAP()
};

extern HFSGuardaDiretorio theApp;
