#pragma once

#include "hfsguardadir\comum\Rotinas.h"
#include "hfsguardadir/catalogador/Catalogador.h"
#include "FrmMDIFilho.h"

using namespace hfsguardadir::comum;
using namespace hfsguardadir::objetosgui;
using namespace hfsguardadir::catalogador;

class FrmPrincipal : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(FrmPrincipal)
public:	
	CImageList *imageListTabs, *imageList16, *imageList32;
	FrmFilho frmFilho;
	CStatusBar barraStatus;
	CDialogBar barraPesquisar;

	FrmPrincipal();
	CString BarraStatusGetStatusText(int indice);
	CString getEdtPesquisaText();
	CProgressCtrl* getBarraProgresso();
	static void ProgressoLog(Progresso progresso);

private:
	bool bCriou;	
	//CProgressCtrl* pb;
	//CEdit* edtPesquisa;
	//CButton* btnImportarDiretorio;
	//CButton* btnPesquisar;
	VOID criaImageListTabs();
		
// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~FrmPrincipal();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members		
	FrmMDIFilho *frmMDIFilho;	

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnIncluirNovaAba();
	afx_msg void OnClose();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnAlterarNomeAbaAtiva();
	afx_msg void OnExcluirAbaAtiva();
	afx_msg void OnImportarDiretorio();
	afx_msg void OnImportarSubdiretorios();
	afx_msg void OnCompararDiretorios();
	afx_msg void OnCadastrarExtensaoArquivo();
	afx_msg void OnExpandirDiretorios();
	afx_msg void OnColapsarDiretorios();
	afx_msg void OnTxt();
	afx_msg void OnCsv();
	afx_msg void OnHtml();
	afx_msg void OnXml();
	afx_msg void OnSql();
	afx_msg void OnImportarDiretoriosViaXml();
	afx_msg void OnGravarLogImportacao();
	afx_msg void OnMostrarOcultarArvoreDirAbaAtiva();
	afx_msg void OnMostrarOcultarListaItensPesquisados();
	afx_msg void OnIcones();
	afx_msg void OnLista();
	afx_msg void OnDetalhes();
	afx_msg void OnIconesPequenos();
	afx_msg void OnSobre();
	afx_msg void OnInformacoesDiretorioArquivo();
	afx_msg void OnExcluirDiretorioSelecionado();
	afx_msg void OnBnClicked_BtnImportarDiretorio();
	afx_msg void OnUpdate_BtnImportarDiretorio(CCmdUI *pCmdUI);
	afx_msg void OnBnClicked_BtnPesquisar();
	afx_msg void OnUpdate_BtnPesquisar(CCmdUI *pCmdUI);
};

extern FrmPrincipal *frmPrincipal;
