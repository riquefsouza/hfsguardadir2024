// FrmCadExtensao.cpp : implementation file
//

#include "stdafx.h"
#include "afxdialogex.h"

#include "HFSGuardaDiretorio.h"
#include "FrmCadExtensao.h"
#include "FrmPrincipal.h"
#include "resource.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/objetosgui/EscolhaArquivo.h"
#include "hfsguardadir/objetosgui/Dialogo.h"
#include "hfsguardadir/objetosbo/ExtensaoBO.h"
#include "hfsguardadir/catalogador/Catalogador.h"

using namespace hfsguardadir::comum;
using namespace hfsguardadir::objetos;
using namespace hfsguardadir::objetosbo;
using namespace hfsguardadir::objetosgui;
using namespace hfsguardadir::catalogador;

IMPLEMENT_DYNAMIC(FrmCadExtensao, CDialogEx)

FrmCadExtensao::FrmCadExtensao(CWnd* pParent /*=NULL*/)
	: CDialogEx(FRMCADEXTENSAO, pParent)
{

}

FrmCadExtensao::~FrmCadExtensao()
{
//	imageList16.DeleteImageList();
//	imageList32.DeleteImageList();
}

void FrmCadExtensao::CarregarExtensoesNaGrid() {
	unsigned int nLinha = 0;
	POSITION pos;
	Extensao extensao;
	SMString cols;
	INT nImagem = 3; //ImageList_GetImageCount(FrmPrincipal.imageList16);

	for (int i = 0; i < catalogo->listaExtensoes->GetSize(); ++i) {
		pos = catalogo->listaExtensoes->FindIndex(i);
		extensao = catalogo->listaExtensoes->GetAt(pos);

		//ImageList_Add(FrmPrincipal.imageList16, extensao.hbmp16, NULL);
		//ImageList_Add(FrmPrincipal.imageList32, extensao.hbmp32, NULL);

		cols.str[0] = extensao.getNome();
		cols.str[1] = _T("");
		Tabela::insereLinha(tabelaExtensao, 2, nLinha, nImagem, cols);
		nLinha++;
		nImagem++;
	}

}

void FrmCadExtensao::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_FRMCADEXTENSAO_LVINFO, tabelaExtensao);
}


BEGIN_MESSAGE_MAP(FrmCadExtensao, CDialogEx)
	ON_COMMAND(IDM_INCLUIR_EXTENSAO, &FrmCadExtensao::OnIncluirExtensao)
	ON_COMMAND(IDM_EXCLUIR_EXTENSAO, &FrmCadExtensao::OnExcluirExtensao)
	ON_COMMAND(IDM_EXCLUIR_TODAS_EXTENSOES, &FrmCadExtensao::OnExcluirTodasExtensoes)
	ON_COMMAND(IDM_EXPORTAR_BITMAP, &FrmCadExtensao::OnExportarBitmap)
	ON_COMMAND(IDM_EXPORTAR_ICONE, &FrmCadExtensao::OnExportarIcone)
	ON_COMMAND(IDM_EXPORTAR_GIF, &FrmCadExtensao::OnExportarGif)
	ON_COMMAND(IDM_EXPORTAR_JPEG, &FrmCadExtensao::OnExportarJpeg)
	ON_COMMAND(IDM_EXPORTAR_PNG, &FrmCadExtensao::OnExportarPng)
	ON_COMMAND(IDM_EXPORTAR_TIFF, &FrmCadExtensao::OnExportarTiff)
	ON_COMMAND(IDM_IMPORTAR_ICONES_ARQUIVOS, &FrmCadExtensao::OnImportarIconesArquivos)
	ON_COMMAND(IDM_EXTRAIR_ICONES_ARQUIVOS, &FrmCadExtensao::OnExtrairIconesArquivos)
	ON_BN_CLICKED(ID_FRMCADEXTENSAO_BTNINCLUIR, &FrmCadExtensao::OnBnClicked_BtnIncluir)
	ON_BN_CLICKED(ID_FRMCADEXTENSAO_BTNEXCLUIR, &FrmCadExtensao::OnBnClicked_BtnExcluir)
END_MESSAGE_MAP()


// FrmCadExtensao message handlers

BOOL FrmCadExtensao::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CStringList sColunas;
	UINT nLargura[] = { 100, 100 };

	sColunas.AddTail(_T("Extensão"));
	sColunas.AddTail(_T("Ícone"));

	Tabela::insereColunas(tabelaExtensao, nLargura, sColunas);

	CarregarExtensoesNaGrid();

	tabelaExtensao.SetImageList(frmPrincipal->imageList16, LVSIL_SMALL);
	tabelaExtensao.SetImageList(frmPrincipal->imageList32, LVSIL_NORMAL);

	return TRUE;
}

void FrmCadExtensao::OnIncluirExtensao()
{
	CStringList log;

	CString arquivo = EscolhaArquivo::abrirArquivo(this);
	if (arquivo.GetLength() > 0) {
		if (Rotinas::FileExists(arquivo)) {
			CString nomeArquivo = Rotinas::ExtractFileName(arquivo);

			if (ExtensaoBO::getInstancia()->SalvarExtensao(
				*catalogo->listaExtensoes, nomeArquivo, arquivo, log)) {

				CarregarExtensoesNaGrid();

				Dialogo::mensagemInfo(this,
					STR_FRMCADEXTENSAO_EXTENSAOSALVASUCESSO);
			}
			else {
				Dialogo::mensagemInfo(this,
					STR_FRMCADEXTENSAO_EXTENSAOJACADASTRADA);
			}
		}
	}
}


void FrmCadExtensao::OnExcluirExtensao()
{
	Extensao *extensao;
	int ntamlista = catalogo->listaExtensoes->GetSize();

	if (ntamlista > 0) {
		if (Dialogo::confirma(this, STR_FRMCADEXTENSAO_EXTENSAOCERTEZAEXCLUIR)) {
			extensao = ExtensaoBO::getInstancia()->pegaExtensaoPorOrdem(
				*catalogo->listaExtensoes, tabelaExtensao.GetSelectionMark() + 1);

			if (ExtensaoBO::getInstancia()->excluirExtensao(
				*catalogo->listaExtensoes, extensao->getCodigo())) {
				CarregarExtensoesNaGrid();
				Dialogo::mensagemInfo(this,
					STR_FRMCADEXTENSAO_EXTENSAOEXCLUIDASUCESSO);
			}
		}
	}
}


void FrmCadExtensao::OnExcluirTodasExtensoes()
{
	int ntamlista = catalogo->listaExtensoes->GetSize();

	if (ntamlista > 0) {
		if (Dialogo::confirma(this, STR_FRMCADEXTENSAO_EXTENSAOCERTEZATODOSEXCLUIR)) {
			if (ExtensaoBO::getInstancia()->excluirTodasExtensoes(
				*catalogo->listaExtensoes)) {
				CarregarExtensoesNaGrid();
				Dialogo::mensagemInfo(this,
					STR_FRMCADEXTENSAO_EXTENSOESEXCLUIDASSUCESSO);
			}
		}
	}
}


void FrmCadExtensao::OnExportarBitmap()
{
	if (ExtensaoBO::getInstancia()->ExportarExtensao(teBMP,
		*catalogo->listaExtensoes)) {
		Dialogo::mensagemInfo(this, STR_FRMCADEXTENSAO_EXPORTAREXTENSAO);
	}
}


void FrmCadExtensao::OnExportarIcone()
{
	if (ExtensaoBO::getInstancia()->ExportarExtensao(teICO,
		*catalogo->listaExtensoes)) {
		Dialogo::mensagemInfo(this, STR_FRMCADEXTENSAO_EXPORTAREXTENSAO);
	}
}


void FrmCadExtensao::OnExportarGif()
{
	if (ExtensaoBO::getInstancia()->ExportarExtensao(teGIF,
		*catalogo->listaExtensoes)) {
		Dialogo::mensagemInfo(this, STR_FRMCADEXTENSAO_EXPORTAREXTENSAO);
	}
}


void FrmCadExtensao::OnExportarJpeg()
{
	if (ExtensaoBO::getInstancia()->ExportarExtensao(teJPG,
		*catalogo->listaExtensoes)) {
		Dialogo::mensagemInfo(this, STR_FRMCADEXTENSAO_EXPORTAREXTENSAO);
	}
}


void FrmCadExtensao::OnExportarPng()
{
	if (ExtensaoBO::getInstancia()->ExportarExtensao(tePNG,
		*catalogo->listaExtensoes)) {
		Dialogo::mensagemInfo(this, STR_FRMCADEXTENSAO_EXPORTAREXTENSAO);
	}
}


void FrmCadExtensao::OnExportarTiff()
{
	if (ExtensaoBO::getInstancia()->ExportarExtensao(teTIF,
		*catalogo->listaExtensoes)) {
		Dialogo::mensagemInfo(this, STR_FRMCADEXTENSAO_EXPORTAREXTENSAO);
	}
}


void FrmCadExtensao::OnImportarIconesArquivos()
{
	CString diretorio = EscolhaArquivo::abrirDiretorio(this);
	if (diretorio.GetLength() > 0) {

		if (Rotinas::DirectoryExists(diretorio)) {
			ExtensaoBO::getInstancia()->ImportarExtensao(diretorio,
				*catalogo->listaExtensoes);
			CarregarExtensoesNaGrid();
		}
	}
}


void FrmCadExtensao::OnExtrairIconesArquivos()
{
	CString diretorio = EscolhaArquivo::abrirDiretorio(this);
	if (diretorio.GetLength() > 0) {

		if (Rotinas::DirectoryExists(diretorio)) {
			ExtensaoBO::getInstancia()->ExtrairExtensao(diretorio,
				*catalogo->listaExtensoes);
			CarregarExtensoesNaGrid();
		}
	}

}


void FrmCadExtensao::OnBnClicked_BtnIncluir()
{
	OnIncluirExtensao();
}


void FrmCadExtensao::OnBnClicked_BtnExcluir()
{
	OnExcluirExtensao();
}


