#pragma once

#include "FrmFilho.h"

class FrmMDIFilho : public CMDIChildWnd
{
	DECLARE_DYNCREATE(FrmMDIFilho)
public:
	FrmMDIFilho();

// Overrides
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

// Implementation
public:
	// view for the client area of the frame.
	virtual ~FrmMDIFilho();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	FrmFilho frmFilho;

// Generated message map functions
protected:
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
