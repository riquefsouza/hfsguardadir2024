// FrmImportarDiretorio.cpp : implementation file
//

#include "stdafx.h"
#include "HFSGuardaDiretorio.h"
#include "FrmImportarDiretorio.h"
#include "afxdialogex.h"
#include "resource.h"
#include "hfsguardadir/catalogador/Catalogador.h"
#include "hfsguardadir/objetosgui/Dialogo.h"
#include "hfsguardadir/objetosbo/ImportarBO.h"
#include "hfsguardadir/objetosbo/DiretorioBO.h"

using namespace hfsguardadir::catalogador;
using namespace hfsguardadir::objetosbo;
using namespace hfsguardadir::objetosgui;

static UINT mindicadores[] =
{
	STR_FRMIMPORTARDIRETORIO_BARRASTATUS1,
	STR_FRMIMPORTARDIRETORIO_BARRASTATUS2,
};

FrmImportarDiretorio *frmImportarDiretorio;

IMPLEMENT_DYNAMIC(FrmImportarDiretorio, CDialogEx)

FrmImportarDiretorio::FrmImportarDiretorio(CWnd* pParent /*=NULL*/)
	: CDialogEx(FRMIMPORTARDIRETORIO, pParent)
{
	listaImportar = new CList<Importar, Importar&>();
}

FrmImportarDiretorio::~FrmImportarDiretorio()
{
	listaImportar->RemoveAll();

	delete listaImportar;
}

int CALLBACK FrmImportarDiretorio::EditWordBreakProc(LPTSTR lpch, int ichCurrent, int cch, int code) {
	OutputDebugString(lpch);
	return TRUE;
}

VOID FrmImportarDiretorio::AppendText(CEdit &edit, const CString &stexto) {
	int posInicio, posFim;

	edit.GetSel(posInicio, posFim);

	int tamanho = edit.GetWindowTextLength();
	edit.SetSel(tamanho, tamanho);
	edit.ReplaceSel(stexto.GetString(), TRUE);
	edit.SetSel(posInicio, posFim);
}

bool FrmImportarDiretorio::Criar(CWnd* hwndPai)
{
	if (!frmImportarDiretorio->Create(MAKEINTRESOURCEW(FRMIMPORTARDIRETORIO), hwndPai)) {
		hwndPai->MessageBox(Rotinas::lerStr(STR_NCCRIADLG), _T("Erro"), MB_ICONERROR | MB_OK);
		return false;
	}

	return true;
}

VOID FrmImportarDiretorio::Mostrar() {
	frmImportarDiretorio->ShowWindow(SW_SHOW);
	frmImportarDiretorio->UpdateWindow();
}


void FrmImportarDiretorio::ProgressoLog(Progresso progresso)
{
	if (frmImportarDiretorio != NULL) {
		if (progresso.posicao == 0) {
			frmImportarDiretorio->pbImportar.SetRange32(progresso.minimo, progresso.maximo);
			frmImportarDiretorio->pbImportar.SetStep(progresso.passo);
		}
		frmImportarDiretorio->pbImportar.SetPos(progresso.posicao);

		if (progresso.log.GetLength() > 0) {
			int pos = frmImportarDiretorio->memoImportaDir.GetLineCount();

			progresso.log += _T("\n");
			frmImportarDiretorio->AppendText(frmImportarDiretorio->memoImportaDir, progresso.log);

			frmImportarDiretorio->memoImportaDir.SetScrollPos(pos, 0);
			frmImportarDiretorio->barraStatus.SetPaneText(1, Rotinas::FromInt(pos));
		}
	}
}


VOID FrmImportarDiretorio::iniciarImportacao() {
	CString sLog;
	CStringList log;
	POSITION pos;
	Importar importar;
	LPTSTR sLinha = Rotinas::NewStr();

	for (int i = 0; i < listaImportar->GetSize(); ++i) {
		pos = listaImportar->FindIndex(i);
		importar = listaImportar->GetAt(pos);

		catalogo->diretorioOrdem.setOrdem(1);

		if (!bSubDiretorio) {
			SetCursor(LoadCursor(NULL, IDC_WAIT));

			ImportarBO::getInstancia()->ImportacaoCompleta(importar,
				&catalogo->diretorioOrdem, *catalogo->listaExtensoes,
				FrmImportarDiretorio::ProgressoLog);

			SetCursor(LoadCursor(NULL, IDC_ARROW));
		}
		else {
			if (!DiretorioBO::getInstancia()->verificaCodDir(importar.getAba(),
				importar.getRotuloRaiz(), *catalogo->listaDiretorioPai)) {
				SetCursor(LoadCursor(NULL, IDC_WAIT));

				ImportarBO::getInstancia()->ImportacaoCompleta(importar,
					&catalogo->diretorioOrdem, *catalogo->listaExtensoes,
					FrmImportarDiretorio::ProgressoLog);

				SetCursor(LoadCursor(NULL, IDC_ARROW));
			}
			else {
				Dialogo::mensagemInfo(this,
					STR_FRMIMPORTARDIRETORIO_DIRETORIOEXISTECATALOGO);
			}
		}
	}

	if (catalogo->bGravarLogImportacao) {
		int tamanho = memoImportaDir.GetWindowTextLength();
		if (tamanho > 0) {
			sLog = Rotinas::AppDirPath();
			sLog += Rotinas::BARRA_INVERTIDA +
				Rotinas::formataDate(Rotinas::FORMATO_DHARQUIVO, Rotinas::DataHoraNow()) +
				_T("_Importacao.log");

			int nLinhas = memoImportaDir.GetLineCount();
			for (int i = 0; i < nLinhas; i++)
			{
				memoImportaDir.GetLine(i, sLinha, TAM_MAX_STR);
				log.AddTail(sLinha);
			}
			Rotinas::SListSaveToFile(log, sLog);
			log.RemoveAll();
		}
	}

	//EndDialog(FrmImportarDiretorio.frmImportarDiretorio, TRUE);
}



void FrmImportarDiretorio::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_FRMIMPORTARDIRETORIO_MEMOIMPORTADIR, memoImportaDir);
	DDX_Control(pDX, ID_FRMIMPORTARDIRETORIO_PBIMPORTAR, pbImportar);
}


BEGIN_MESSAGE_MAP(FrmImportarDiretorio, CDialogEx)
END_MESSAGE_MAP()


// FrmImportarDiretorio message handlers


BOOL FrmImportarDiretorio::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (!barraStatus.Create(this))
	{
		TRACE0("Falhou ao criar a barra de status\n");
		return -1;
	}
	barraStatus.SetIndicators(mindicadores, sizeof(mindicadores) / sizeof(UINT));

	barraStatus.SetPaneInfo(0, STR_FRMIMPORTARDIRETORIO_BARRASTATUS1, SBPS_NORMAL, 250);
	barraStatus.SetPaneInfo(1, STR_FRMIMPORTARDIRETORIO_BARRASTATUS2, SBPS_STRETCH, 0);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	Rotinas::setBarraProgresso(&pbImportar, 0, 100, 1);

	return TRUE;
}
