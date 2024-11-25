#include "stdafx.h"
#include "HFSGuardaDiretorio.h"

#include "FrmMDIFilho.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(FrmMDIFilho, CMDIChildWnd)

BEGIN_MESSAGE_MAP(FrmMDIFilho, CMDIChildWnd)
	ON_WM_SETFOCUS()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()

FrmMDIFilho::FrmMDIFilho()
{
	// TODO: add member initialization code here
}

FrmMDIFilho::~FrmMDIFilho()
{
}


BOOL FrmMDIFilho::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.style = WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
		| FWS_ADDTOTITLE | WS_THICKFRAME;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// FrmFilho diagnostics

#ifdef _DEBUG
void FrmMDIFilho::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void FrmMDIFilho::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}
#endif //_DEBUG

// FrmMDIFilho message handlers
int FrmMDIFilho::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//Remover botoes da janela
	SetWindowLongPtr(this->GetSafeHwnd(), GWL_STYLE, GetStyle() & ~WS_SYSMENU);
			
	return 0;
}

void FrmMDIFilho::OnSetFocus(CWnd* pOldWnd)
{
	CMDIChildWnd::OnSetFocus(pOldWnd);
}

BOOL FrmMDIFilho::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	
	// otherwise, do default handling
	return CMDIChildWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


BOOL FrmMDIFilho::OnEraseBkgnd(CDC* pDC)
{
	DWORD dw = GetSysColor(COLOR_3DFACE);
	CBrush bkBrush(dw);

	CRect rect;
	GetClientRect(&rect);

	pDC->FillRect(rect, &bkBrush);
	return TRUE;

	//return CMDIChildWnd::OnEraseBkgnd(pDC);
}


void FrmMDIFilho::OnSize(UINT nType, int cx, int cy)
{
	CMDIChildWnd::OnSize(nType, cx, cy);

}
