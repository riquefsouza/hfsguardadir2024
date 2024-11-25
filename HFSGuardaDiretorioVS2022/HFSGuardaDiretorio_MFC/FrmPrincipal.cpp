#include "stdafx.h"
#include "FrmPrincipal.h"
#include "HFSGuardaDiretorio.h"
#include "resource.h"
#include "FrmSplash.h"
#include "FrmSobre.h"
#include "FrmFilho.h"
#include "FrmCompararDiretorio.h"
#include "FrmImportarDiretorio.h"
#include "FrmInfoDiretorio.h"
#include "FrmCadExtensao.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// FrmPrincipal

IMPLEMENT_DYNAMIC(FrmPrincipal, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(FrmPrincipal, CMDIFrameWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()	
	ON_WM_CLOSE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(IDM_INCLUIR_NOVA_ABA, &FrmPrincipal::OnIncluirNovaAba)
	ON_COMMAND(IDM_ALTERAR_NOME_ABA_ATIVA, &FrmPrincipal::OnAlterarNomeAbaAtiva)
	ON_COMMAND(IDM_EXCLUIR_ABA_ATIVA, &FrmPrincipal::OnExcluirAbaAtiva)
	ON_COMMAND(IDM_IMPORTAR_DIRETORIO, &FrmPrincipal::OnImportarDiretorio)
	ON_COMMAND(IDM_IMPORTAR_SUBDIRETORIOS, &FrmPrincipal::OnImportarSubdiretorios)
	ON_COMMAND(IDM_COMPARAR_DIRETORIOS, &FrmPrincipal::OnCompararDiretorios)
	ON_COMMAND(IDM_CADASTRAR_EXTENSAO_ARQUIVO, &FrmPrincipal::OnCadastrarExtensaoArquivo)
	ON_COMMAND(IDM_EXPANDIR_DIRETORIOS, &FrmPrincipal::OnExpandirDiretorios)
	ON_COMMAND(IDM_COLAPSAR_DIRETORIOS, &FrmPrincipal::OnColapsarDiretorios)
	ON_COMMAND(IDM_TXT, &FrmPrincipal::OnTxt)
	ON_COMMAND(IDM_CSV, &FrmPrincipal::OnCsv)
	ON_COMMAND(IDM_HTML, &FrmPrincipal::OnHtml)
	ON_COMMAND(IDM_XML, &FrmPrincipal::OnXml)
	ON_COMMAND(IDM_SQL, &FrmPrincipal::OnSql)
	ON_COMMAND(IDM_IMPORTAR_DIRETORIOS_VIA_XML, &FrmPrincipal::OnImportarDiretoriosViaXml)
	ON_COMMAND(IDM_GRAVAR_LOG_IMPORTACAO, &FrmPrincipal::OnGravarLogImportacao)
	ON_COMMAND(IDM_MOSTRAR_OCULTAR_ARVORE_DIR_ABA_ATIVA, &FrmPrincipal::OnMostrarOcultarArvoreDirAbaAtiva)
	ON_COMMAND(IDM_MOSTRAR_OCULTAR_LISTA_ITENS_PESQUISADOS, &FrmPrincipal::OnMostrarOcultarListaItensPesquisados)
	ON_COMMAND(IDM_ICONES, &FrmPrincipal::OnIcones)
	ON_COMMAND(IDM_LISTA, &FrmPrincipal::OnLista)
	ON_COMMAND(IDM_DETALHES, &FrmPrincipal::OnDetalhes)
	ON_COMMAND(IDM_ICONES_PEQUENOS, &FrmPrincipal::OnIconesPequenos)
	ON_COMMAND(IDM_SOBRE, &FrmPrincipal::OnSobre)
	ON_COMMAND(IDM_INFORMACOES_DIRETORIO_ARQUIVO, &FrmPrincipal::OnInformacoesDiretorioArquivo)
	ON_COMMAND(IDM_EXCLUIR_DIRETORIO_SELECIONADO, &FrmPrincipal::OnExcluirDiretorioSelecionado)
	ON_BN_CLICKED(ID_FRMPRINCIPAL_BTNIMPORTARDIRETORIO, &FrmPrincipal::OnBnClicked_BtnImportarDiretorio)
	ON_UPDATE_COMMAND_UI(ID_FRMPRINCIPAL_BTNIMPORTARDIRETORIO, &FrmPrincipal::OnUpdate_BtnImportarDiretorio)
	ON_BN_CLICKED(ID_FRMPRINCIPAL_BTNPESQUISAR, &FrmPrincipal::OnBnClicked_BtnPesquisar)
	ON_UPDATE_COMMAND_UI(ID_FRMPRINCIPAL_BTNPESQUISAR, &FrmPrincipal::OnUpdate_BtnPesquisar)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	STR_FRMPRINCIPAL_BARRASTATUS1,
	STR_FRMPRINCIPAL_BARRASTATUS2,
};

FrmPrincipal *frmPrincipal;

// FrmPrincipal construction/destruction

FrmPrincipal::FrmPrincipal()
{
	bCriou = false;	

	imageListTabs = new CImageList();
	imageList16 = new CImageList();
	imageList32 = new CImageList();

	criaImageListTabs();
	Rotinas::criaImageLists(imageList16, imageList32);

}

FrmPrincipal::~FrmPrincipal()
{
	imageListTabs->DeleteImageList();
	imageList16->DeleteImageList();
	imageList32->DeleteImageList();

	delete imageListTabs;
	delete imageList16;
	delete imageList32;
}

VOID FrmPrincipal::criaImageListTabs() {	
	imageListTabs->Create(16, 16, ILC_COLOR8 | ILC_MASK, 2, 0);

	CBitmap *hbmCDOURO, *hbmCDPRATA;
	hbmCDOURO = new CBitmap();
	hbmCDPRATA = new CBitmap();

	hbmCDOURO->LoadBitmapW(MAKEINTRESOURCE(CDOURO));
	hbmCDPRATA->LoadBitmapW(MAKEINTRESOURCE(CDPRATA));

	imageListTabs->Add(hbmCDOURO, RGB(255, 0, 255));
	imageListTabs->Add(hbmCDPRATA, RGB(255, 0, 255));

	DeleteObject(hbmCDOURO);
	DeleteObject(hbmCDPRATA);

	delete hbmCDOURO;
	delete hbmCDPRATA;
}

void FrmPrincipal::ProgressoLog(Progresso progresso)
{
	if (frmPrincipal != NULL) {
		if (progresso.posicao == 0) {
			frmPrincipal->getBarraProgresso()->SetRange32(progresso.minimo, progresso.maximo);
			frmPrincipal->getBarraProgresso()->SetStep(progresso.passo);
		}

		frmPrincipal->getBarraProgresso()->SetPos(progresso.posicao);
	}

}

CString FrmPrincipal::BarraStatusGetStatusText(int indice) {
	CString texto = barraStatus.GetPaneText(indice);
	return texto;
}

CString FrmPrincipal::getEdtPesquisaText() {
	CString texto = _T("");

	CEdit* edtPesquisa = reinterpret_cast<CEdit*>(barraPesquisar.GetDlgItem(ID_FRMPRINCIPAL_EDTPESQUISA));
	edtPesquisa->GetWindowTextW(texto);

	return texto;
}

CProgressCtrl* FrmPrincipal::getBarraProgresso() {
	return reinterpret_cast<CProgressCtrl*>(barraPesquisar.GetDlgItem(ID_FRMPRINCIPAL_PB));
}


int FrmPrincipal::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	frmMDIFilho = (FrmMDIFilho*)this->CreateNewChild(RUNTIME_CLASS(FrmMDIFilho),
		STR_FILHO, theApp.m_hMDIMenu, theApp.m_hMDIAccel);
	frmMDIFilho->ShowWindow(SW_SHOWMAXIMIZED);

	if (!barraStatus.Create(this))
	{
		TRACE0("Falhou ao criar a barra de status\n");
		return -1;      // fail to create
	}
	barraStatus.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	barraStatus.SetPaneInfo(0, STR_FRMPRINCIPAL_BARRASTATUS1, SBPS_NORMAL, 300);
	barraStatus.SetPaneInfo(1, STR_FRMPRINCIPAL_BARRASTATUS2, SBPS_STRETCH, 0);
	
	if (!barraPesquisar.Create(this, MAKEINTRESOURCEW(BARRAPESQUISAR), CBRS_ALIGN_TOP, BARRAPESQUISAR))
	{
		TRACE0("Falhou ao criar a barraPesquisar\n");
		return -1;      // fail to create
	}

	MoveWindow(0, 0, 924, 546, TRUE);
	CenterWindow();
	
	frmFilho.Create(FRMPRINCIPAL, frmMDIFilho);
	SetWindowLong(GetSafeHwnd(), 0, (LONG)frmFilho.GetSafeHwnd());
		
	bCriou = true;

	return 0;
}

BOOL FrmPrincipal::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

// FrmPrincipal diagnostics

#ifdef _DEBUG
void FrmPrincipal::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void FrmPrincipal::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}
#endif //_DEBUG


// FrmPrincipal message handlers

void FrmPrincipal::OnSize(UINT nType, int cx, int cy)
{
	CMDIFrameWnd::OnSize(nType, cx, cy);

	RECT rectClient, rectStatus, rectBarraPesquisar;
	UINT uBarraPesquisarHeight, uStatusHeight, uClientAlreaHeight;

	this->GetClientRect(&rectClient);
	barraStatus.GetWindowRect(&rectStatus);
	barraPesquisar.GetWindowRect(&rectBarraPesquisar);

	uBarraPesquisarHeight = rectBarraPesquisar.bottom - rectBarraPesquisar.top;
	uStatusHeight = rectStatus.bottom - rectStatus.top;
	uClientAlreaHeight = rectClient.bottom;
		
	if (bCriou) {
		frmFilho.MoveWindow(0, 0, rectClient.right - 2,
			uClientAlreaHeight - uStatusHeight - uBarraPesquisarHeight - 2, TRUE);
	}
	

}

void FrmPrincipal::OnClose()
{
	Rotinas::getInstancia()->BancoDesconectar();
	delete catalogo;

	CMDIFrameWnd::OnClose();
}

void FrmPrincipal::OnSetFocus(CWnd* pOldWnd)
{
	CMDIFrameWnd::OnSetFocus(pOldWnd);

	//if (frmFilho != NULL) {
	//frmFilho->SetFocus();
	//}

}

void FrmPrincipal::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu hmenu;
	CMenu* hmenuTrackPopup;
	
	hmenu.LoadMenuW(MAKEINTRESOURCE(IDM_POPUP));

	hmenuTrackPopup = hmenu.GetSubMenu(0);
	ASSERT(hmenuTrackPopup);

	hmenuTrackPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);

	hmenu.DestroyMenu();
}

void FrmPrincipal::OnIncluirNovaAba()
{
	catalogo->IncluirNovaAba();
}

void FrmPrincipal::OnAlterarNomeAbaAtiva()
{
	catalogo->AlterarNomeAbaAtiva(FrmPrincipal::ProgressoLog);
}

void FrmPrincipal::OnExcluirAbaAtiva()
{
	catalogo->ExcluirAbaAtiva(FrmPrincipal::ProgressoLog);
}

void FrmPrincipal::OnImportarDiretorio()
{
	catalogo->ComecaImportacao(FALSE, FrmPrincipal::ProgressoLog);
}

void FrmPrincipal::OnImportarSubdiretorios()
{
	catalogo->ComecaImportacao(TRUE, FrmPrincipal::ProgressoLog);
}

void FrmPrincipal::OnCompararDiretorios()
{
	frmCompararDiretorio = new FrmCompararDiretorio();
	frmCompararDiretorio->DoModal();
	frmCompararDiretorio->DestroyWindow();

	delete frmCompararDiretorio;
}

void FrmPrincipal::OnCadastrarExtensaoArquivo()
{
	FrmCadExtensao frmCadExtensao;
	frmCadExtensao.DoModal();
	frmCadExtensao.DestroyWindow();
}

void FrmPrincipal::OnExpandirDiretorios()
{
	frmFilho.arvoreExpandirTodos();
}

void FrmPrincipal::OnColapsarDiretorios()
{
	frmFilho.arvoreColapsarTodos();
}

void FrmPrincipal::OnTxt()
{
	catalogo->ExportarArquivo(teTXT, FrmPrincipal::ProgressoLog);
}

void FrmPrincipal::OnCsv()
{
	catalogo->ExportarArquivo(teCSV, FrmPrincipal::ProgressoLog);
}

void FrmPrincipal::OnHtml()
{
	catalogo->ExportarArquivo(teHTML, FrmPrincipal::ProgressoLog);
}

void FrmPrincipal::OnXml()
{
	catalogo->ExportarArquivo(teXML, FrmPrincipal::ProgressoLog);
}

void FrmPrincipal::OnSql()
{
	catalogo->ExportarArquivo(teSQL, FrmPrincipal::ProgressoLog);
}

void FrmPrincipal::OnImportarDiretoriosViaXml()
{
	CStringList log;
	catalogo->ImportarArquivo(log, FrmPrincipal::ProgressoLog);
}

void FrmPrincipal::OnGravarLogImportacao()
{	
	static bool bGravarLogImportacao = false;
	bGravarLogImportacao = !bGravarLogImportacao;

	if (bGravarLogImportacao) {
		this->GetMenu()->CheckMenuItem(IDM_GRAVAR_LOG_IMPORTACAO, MF_BYCOMMAND | MF_CHECKED);
		catalogo->bGravarLogImportacao = bGravarLogImportacao;
	}
	else {
		this->GetMenu()->CheckMenuItem(IDM_GRAVAR_LOG_IMPORTACAO, MF_BYCOMMAND | MF_UNCHECKED);
		catalogo->bGravarLogImportacao = bGravarLogImportacao;
	}
}

void FrmPrincipal::OnMostrarOcultarArvoreDirAbaAtiva()
{
	frmFilho.mostraOcultarArvore();
}

void FrmPrincipal::OnMostrarOcultarListaItensPesquisados()
{
	frmFilho.mostraOcultarTabelaPesquisa();
}

void FrmPrincipal::OnIcones()
{
	frmFilho.setVisao(LVS_ICON);
}

void FrmPrincipal::OnLista()
{
	frmFilho.setVisao(LVS_LIST);
}

void FrmPrincipal::OnDetalhes()
{
	frmFilho.setVisao(LVS_REPORT);
}

void FrmPrincipal::OnIconesPequenos()
{
	frmFilho.setVisao(LVS_SMALLICON);
}

void FrmPrincipal::OnSobre()
{
	FrmSobre frmSobre;
	frmSobre.DoModal();
	frmSobre.DestroyWindow();
}

void FrmPrincipal::OnInformacoesDiretorioArquivo()
{
	CListCtrl *tabela = catalogo->getTabelaAtual();

	if (tabela->GetSelectedCount() > 0) {
		Aba aba = catalogo->getAbaAtual();
		Diretorio *dir = Tabela::getItemSelecionado(*tabela, true);
		dir->setAba(aba);
		FrmInfoDiretorio::Mostrar(*dir);
	}
}

void FrmPrincipal::OnExcluirDiretorioSelecionado()
{
	catalogo->ExcluirDiretorioSelecionado(FrmPrincipal::ProgressoLog);
}


void FrmPrincipal::OnBnClicked_BtnImportarDiretorio()
{
	catalogo->ComecaImportacao(false, FrmPrincipal::ProgressoLog);
}


void FrmPrincipal::OnUpdate_BtnImportarDiretorio(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}


void FrmPrincipal::OnBnClicked_BtnPesquisar()
{
	catalogo->Pesquisar();
}


void FrmPrincipal::OnUpdate_BtnPesquisar(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}
