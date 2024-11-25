#pragma once
#include "afxcmn.h"

#include "hfsguardadir/objetosgui/Tabela.h"

using namespace hfsguardadir::objetosgui;

// FrmCadExtensao dialog

class FrmCadExtensao : public CDialogEx
{
	DECLARE_DYNAMIC(FrmCadExtensao)

private:
	//CImageList imageList16, imageList32;
	void CarregarExtensoesNaGrid();

public:
	FrmCadExtensao(CWnd* pParent = NULL);   // standard constructor
	virtual ~FrmCadExtensao();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = FRMCADEXTENSAO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnIncluirExtensao();
	afx_msg void OnExcluirExtensao();
	afx_msg void OnExcluirTodasExtensoes();
	afx_msg void OnExportarBitmap();
	afx_msg void OnExportarIcone();
	afx_msg void OnExportarGif();
	afx_msg void OnExportarJpeg();
	afx_msg void OnExportarPng();
	afx_msg void OnExportarTiff();
	afx_msg void OnImportarIconesArquivos();
	afx_msg void OnExtrairIconesArquivos();
	afx_msg void OnBnClicked_BtnIncluir();
	afx_msg void OnBnClicked_BtnExcluir();
	virtual BOOL OnInitDialog();
	CListCtrl tabelaExtensao;
};
