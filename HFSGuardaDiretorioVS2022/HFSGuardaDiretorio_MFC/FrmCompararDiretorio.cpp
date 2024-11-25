// FrmCompararDiretorio.cpp : implementation file
//

#include "stdafx.h"
#include "HFSGuardaDiretorio.h"
#include "FrmCompararDiretorio.h"
#include "afxdialogex.h"

#include "hfsguardadir\objetosgui\Dialogo.h"
#include "hfsguardadir\catalogador\Catalogador.h"
#include "hfsguardadir\objetosbo\AbaBO.h"
#include "hfsguardadir\objetosbo\DiretorioBO.h"

using namespace hfsguardadir::objetosgui;
using namespace hfsguardadir::objetosbo;
using namespace hfsguardadir::catalogador;

static UINT cindicadores[] =
{
	STR_FRMCOMPARARDIRETORIO_BARRASTATUS1,
	STR_FRMCOMPARARDIRETORIO_BARRASTATUS2,
};

FrmCompararDiretorio *frmCompararDiretorio;

IMPLEMENT_DYNAMIC(FrmCompararDiretorio, CDialogEx)

FrmCompararDiretorio::FrmCompararDiretorio(CWnd* pParent /*=NULL*/)
	: CDialogEx(FRMCOMPARARDIRETORIO, pParent)
{
	listaCompara = new CList<Diretorio, Diretorio&>();
	imageList16 = new CImageList();
	imageList32 = new CImageList();
}

FrmCompararDiretorio::~FrmCompararDiretorio()
{
	listaCompara->RemoveAll();
	imageList16->DeleteImageList();
	imageList32->DeleteImageList();

	delete listaCompara;
	delete imageList16;
	delete imageList32;
}

void FrmCompararDiretorio::ProgressoLog(Progresso progresso)
{
	if (frmCompararDiretorio != NULL) {
		if (progresso.posicao == 0) {
			frmCompararDiretorio->pb.SetRange(progresso.minimo, progresso.maximo);
			frmCompararDiretorio->pb.SetStep(progresso.passo);
		}
		frmCompararDiretorio->pb.SetPos(progresso.posicao);
	}
}

void FrmCompararDiretorio::LimparComparacao() {
	pb.SetPos(0);
	Tabela::limpar(tabelaCompara);
	Tabela::selecionaLinha(tabelaCompara, 0);
	btnSalvarLog.EnableWindow(FALSE);
	barraStatus.SetPaneText(1, _T(""));
}

CString FrmCompararDiretorio::BarraStatusGetStatusText(int indice) {
	CString texto = barraStatus.GetPaneText(indice);
	return texto;
}

void FrmCompararDiretorio::montarArvores()
{
	Aba aba;
	Aba *aba1;
	POSITION pos;

	for (int i = 0; i < catalogo->listaAbas->GetSize(); ++i) {
			pos = catalogo->listaAbas->FindIndex(i);
			aba = catalogo->listaAbas->GetAt(pos);

		cmbAba1.AddString(aba.getNome());
		cmbAba2.AddString(aba.getNome());
	}
	cmbAba1.SetCurSel(0);
	cmbAba2.SetCurSel(0);

	aba1 = AbaBO::getInstancia()->pegaAbaPorOrdem(*catalogo->listaAbas,
		cmbAba1.GetCurSel() + 1);
	catalogo->CarregarArvore(arvoreDir1, *aba1);

	aba1 = AbaBO::getInstancia()->pegaAbaPorOrdem(*catalogo->listaAbas,
		cmbAba2.GetCurSel() + 1);
	catalogo->CarregarArvore(arvoreDir2, *aba1);
}

CString FrmCompararDiretorio::SQLCompara(Aba aba1, Aba aba2, const CString &caminho1,
	const CString &caminho2) {
	CString sSQL;

	sSQL = DiretorioBO::SQL_CONSULTA_ARQUIVO +
		_T(" WHERE aba=") + Rotinas::FromInt(aba1.getCodigo()) +
		_T(" AND caminho LIKE ") + Rotinas::QuotedStr(caminho1 + _T("%")) +
		_T(" AND nome NOT IN (SELECT nome FROM Diretorios ") +
		_T(" WHERE aba=") + Rotinas::FromInt(aba2.getCodigo()) + _T(" AND caminho LIKE ") +
		Rotinas::QuotedStr(caminho2 + _T("%")) + _T(") ORDER BY 1, 2, 3");
	return sSQL;
}

void FrmCompararDiretorio::Comparar(const CString &sCaminhoDir1, const CString &sCaminhoDir2)
{
	CString sSQL;
	Aba *aba1, *aba2;
	int tamLista;

	aba1 = AbaBO::getInstancia()->pegaAbaPorOrdem(*catalogo->listaAbas,
		cmbAba1.GetCurSel() + 1);
	aba2 = AbaBO::getInstancia()->pegaAbaPorOrdem(*catalogo->listaAbas,
		cmbAba2.GetCurSel() + 1);

	sSQL = SQLCompara(*aba1, *aba2, sCaminhoDir1, sCaminhoDir2);
	listaCompara = DiretorioBO::getInstancia()->carregarDiretorio(sSQL,
		_T("consultaarquivo"), FrmCompararDiretorio::ProgressoLog);

	tamLista = listaCompara->GetSize();

	if (tamLista > 0) {
		Tabela::adiciona(tabelaCompara, TRUE,
			*listaCompara,
			*catalogo->listaExtensoes, &pb);
		Tabela::selecionaLinha(tabelaCompara, 0);

		barraStatus.SetPaneText(1, Rotinas::FromInt(tamLista));
		btnSalvarLog.EnableWindow(TRUE);
	}
	else {
		Dialogo::mensagemInfo(this,
			STR_FRMCOMPARARDIRETORIO_NENHUMADIFERENCAENCONTRADA);
	}
}

void FrmCompararDiretorio::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_FRMCOMPARARDIRETORIO_BTNCOMPARARDIRETORIOS, btnCompararDiretorios);
	DDX_Control(pDX, ID_FRMCOMPARARDIRETORIO_PB, pb);
	DDX_Control(pDX, ID_FRMCOMPARARDIRETORIO_BTNSALVARLOG, btnSalvarLog);
	DDX_Control(pDX, ID_FRMCOMPARARDIRETORIO_CMBABA1, cmbAba1);
	DDX_Control(pDX, ID_FRMCOMPARARDIRETORIO_TVDIR1, arvoreDir1);
	DDX_Control(pDX, ID_FRMCOMPARARDIRETORIO_CMBABA2, cmbAba2);
	DDX_Control(pDX, ID_FRMCOMPARARDIRETORIO_TVDIR2, arvoreDir2);
	DDX_Control(pDX, ID_FRMCOMPARARDIRETORIO_LVCOMPARA, tabelaCompara);
}


BEGIN_MESSAGE_MAP(FrmCompararDiretorio, CDialogEx)
	ON_BN_CLICKED(ID_FRMCOMPARARDIRETORIO_BTNCOMPARARDIRETORIOS, &FrmCompararDiretorio::OnBnClicked_BtnCompararDiretorios)
	ON_BN_CLICKED(ID_FRMCOMPARARDIRETORIO_BTNSALVARLOG, &FrmCompararDiretorio::OnBnClicked_BtnSalvarLog)
	ON_CBN_SELCHANGE(ID_FRMCOMPARARDIRETORIO_CMBABA1, &FrmCompararDiretorio::OnCbnSelchange_CmbAba1)
	ON_CBN_SELCHANGE(ID_FRMCOMPARARDIRETORIO_CMBABA2, &FrmCompararDiretorio::OnCbnSelchange_CmbAba2)
	ON_NOTIFY(LVN_COLUMNCLICK, ID_FRMCOMPARARDIRETORIO_LVCOMPARA, &FrmCompararDiretorio::OnLvnColumnclick_TabelaCompara)
END_MESSAGE_MAP()


// FrmCompararDiretorio message handlers


BOOL FrmCompararDiretorio::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (!barraStatus.Create(this))
	{
		TRACE0("Falhou ao criar a barra de status\n");
		return -1;
	}
	barraStatus.SetIndicators(cindicadores, sizeof(cindicadores) / sizeof(UINT));

	barraStatus.SetPaneInfo(0, STR_FRMCOMPARARDIRETORIO_BARRASTATUS1, SBPS_NORMAL, 200);
	barraStatus.SetPaneInfo(1, STR_FRMCOMPARARDIRETORIO_BARRASTATUS2, SBPS_STRETCH, 0);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	Rotinas::setBarraProgresso(&pb, 0, 100, 1);
	
	arvoreDir1.SetImageList(frmPrincipal->imageList16, LVSIL_NORMAL);
	arvoreDir2.SetImageList(frmPrincipal->imageList16, LVSIL_NORMAL);

	Rotinas::criaImageLists(imageList16, imageList32);
	Tabela::modeloColunas(tabelaCompara, TRUE, imageList16, imageList32);

	montarArvores();
	LimparComparacao();
	
	return TRUE;
}


void FrmCompararDiretorio::OnBnClicked_BtnCompararDiretorios()
{
	CString sCaminhoDir1 = _T(""), sCaminhoDir2 = _T("");
	BOOL bSelecionado;

	bSelecionado = FALSE;
	if (Arvore::isSelecionado(arvoreDir1)) {
		catalogo->LerArvoreDiretorio(arvoreDir1,
			arvoreDir1.GetSelectedItem(), barraStatus);
		sCaminhoDir1 = BarraStatusGetStatusText(1);

		if (Arvore::isSelecionado(arvoreDir2)) {
			catalogo->LerArvoreDiretorio(arvoreDir2,
				arvoreDir2.GetSelectedItem(), barraStatus);
			sCaminhoDir2 = BarraStatusGetStatusText(1);
			bSelecionado = TRUE;
		}
	}

	LimparComparacao();

	if (bSelecionado) {
		Comparar(sCaminhoDir1, sCaminhoDir2);
	}
	else {
		Dialogo::mensagemInfo(this,
			STR_FRMCOMPARARDIRETORIO_DIRETORIOSNAOSELECIONADOS);
	}

}


void FrmCompararDiretorio::OnBnClicked_BtnSalvarLog()
{
	CString sLog;
	CStringList listaLocal;
	POSITION pos;
	Diretorio diretorio;

	int ntamlista = listaCompara->GetSize();

	if (ntamlista > 0) {
		sLog = Rotinas::AppDirPath();
		sLog += Rotinas::BARRA_INVERTIDA +
			Rotinas::formataDate(Rotinas::FORMATO_DHARQUIVO, Rotinas::DataHoraNow()) +
			_T("_Comparacao.log");

		for (int i = 0; i < listaCompara->GetSize(); ++i) {
			pos = listaCompara->FindIndex(i);
			diretorio = listaCompara->GetAt(pos);
			listaLocal.AddTail(diretorio.getCaminho());
		}

		Rotinas::SListSaveToFile(listaLocal, sLog);

		Dialogo::mensagemInfo(this,
			STR_FRMCOMPARARDIRETORIO_LOGSALVOMEMODIRSISTEMA);
	}

}


void FrmCompararDiretorio::OnCbnSelchange_CmbAba1()
{
	Aba *aba;

	Arvore::limpar(arvoreDir1);
	aba = AbaBO::getInstancia()->pegaAbaPorOrdem(*catalogo->listaAbas,
		cmbAba1.GetCurSel() + 1);
	catalogo->CarregarArvore(arvoreDir1, *aba);

	if (arvoreDir1.GetCount() > 0) {
		arvoreDir1.SelectItem(arvoreDir1.GetFirstVisibleItem());
	}
	LimparComparacao();
}


void FrmCompararDiretorio::OnCbnSelchange_CmbAba2()
{
	Aba *aba;

	Arvore::limpar(arvoreDir2);
	aba = AbaBO::getInstancia()->pegaAbaPorOrdem(*catalogo->listaAbas,
		cmbAba2.GetCurSel() + 1);
	catalogo->CarregarArvore(arvoreDir2, *aba);

	if (arvoreDir2.GetCount() > 0) {
		arvoreDir2.SelectItem(arvoreDir2.GetFirstVisibleItem());
	}
	LimparComparacao();
}

void FrmCompararDiretorio::OnLvnColumnclick_TabelaCompara(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	static bool bTabelaComparaOrdemColuna = true;

	bTabelaComparaOrdemColuna = !bTabelaComparaOrdemColuna;

	if (bTabelaComparaOrdemColuna)
		tabelaCompara.SortItems(Tabela::comparaASC, 0);
	else
		tabelaCompara.SortItems(Tabela::comparaDESC, 0);

	*pResult = 0;
}
