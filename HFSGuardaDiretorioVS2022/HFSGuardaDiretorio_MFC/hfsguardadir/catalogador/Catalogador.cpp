#include "stdafx.h"

#include <windowsx.h>
#include "hfsguardadir/catalogador/Catalogador.h"
#include "HFSGuardaDiretorio.h"
#include "FrmSplash.h"
#include "hfsguardadir/objetosbo/AbaBO.h"
#include "hfsguardadir/objetosbo/ExtensaoBO.h"
#include "hfsguardadir/objetosbo/DiretorioBO.h"
#include "hfsguardadir/objetosdao/VisaoDAO.h"
#include "hfsguardadir/objetosgui/Dialogo.h"
#include "hfsguardadir/objetosgui/EscolhaArquivo.h"
#include "hfsguardadir/objetos/Importar.h"
#include "hfsguardadir/objetosgui/TabControle.h"

using namespace hfsguardadir::objetosbo;
using namespace hfsguardadir::objetosdao;
using namespace hfsguardadir::objetos;
using namespace hfsguardadir::catalogador;

hfsguardadir::catalogador::Catalogador *catalogo;

namespace hfsguardadir {

namespace catalogador {

const CString Catalogador::CONSULTA_DIR_PAI =
	_T("select aba, cod, ordem, coddirpai, nome, tam, tipo, modificado, " \
	"atributos, caminho, nomeaba, nomepai, caminhopai " \
	"from consultadirpai " \
	"order by 1,2,3,4");
const CString Catalogador::CONSULTA_DIR_FILHO =
	_T("select aba, cod, ordem, coddirpai, nome, tam, tipo, modificado, " \
	"atributos, caminho, nomeaba, nomepai, caminhopai " \
	"from consultadirfilho " \
	"order by 1,2,3,4");
const CString Catalogador::CONSULTA_ARQUIVO =
	_T("select aba, cod, ordem, coddirpai, nome, tam, tipo, modificado, " \
	"atributos, caminho, nomeaba, nomepai, caminhopai " \
	"from consultaarquivo " \
	"order by tipo desc, ordem");

const CString Catalogador::NO_RAIZ = _T("Raiz");

Catalogador::Catalogador() {
	bGravarLogImportacao = FALSE;

	Catalogador::iniciarSistema();
	SetCursor(LoadCursor(NULL, IDC_WAIT));

	frmSplash = new FrmSplash();
	
	if (FrmSplash::Criar(frmPrincipal)) {
		FrmSplash::Mostrar();
	}
		
	CarregarDados(FrmSplash::ProgressoLog, TRUE, TRUE);
	CarregarAbas();
	tabPanelMudou();

	frmSplash->EndDialog(TRUE);
	frmSplash->DestroyWindow();
	delete frmSplash;

	SetCursor(LoadCursor(NULL, IDC_ARROW));
}

Catalogador::~Catalogador() {
	listaDiretorioFilho->RemoveAll();
	listaArquivos->RemoveAll();
	listaAbas->RemoveAll();
	listaDiretorioPai->RemoveAll();
	listaExtensoes->RemoveAll();
	
	delete listaDiretorioFilho;
	delete listaArquivos;
	delete listaAbas;
	delete listaDiretorioPai;
	delete listaExtensoes;
}

void Catalogador::iniciarSistema() {
	Aba aba;
	CString sBanco = Rotinas::AppDirName();
	sBanco += _T("GuardaDir.db");

    if (!Rotinas::FileExists(sBanco)){
        Rotinas::getInstancia()->BancoConectar(sBanco);

        AbaBO::getInstancia()->criarTabelaAbas();

		aba.setCodigo(1);
		aba.setNome(_T("DISCO1"));
		aba.setOrdem(0);
        AbaBO::getInstancia()->incluirAba(aba);

        ExtensaoBO::getInstancia()->criarTabelaExtensoes();
        DiretorioBO::getInstancia()->criarTabelaDiretorios();
        VisaoDAO::getInstancia()->criarVisao(_T("consultadirpai"));
        VisaoDAO::getInstancia()->criarVisao(_T("consultadirfilho"));
        VisaoDAO::getInstancia()->criarVisao(_T("consultaarquivo"));
    } else
        Rotinas::getInstancia()->BancoConectar(sBanco);

}

void Catalogador::CarregarDados(IProgressoLog pLog, BOOL bExtensao, BOOL bDiretorio) {
	listaAbas = AbaBO::getInstancia()->carregarAba(pLog);
    if (bExtensao) {
		listaExtensoes = ExtensaoBO::getInstancia()->carregarExtensao(pLog);
    }
    if (bDiretorio) {
		listaDiretorioPai = DiretorioBO::getInstancia()->carregarDiretorio(
			CONSULTA_DIR_PAI, pLog);
		listaDiretorioFilho = DiretorioBO::getInstancia()->carregarDiretorio(
			CONSULTA_DIR_FILHO, pLog);
		listaArquivos = DiretorioBO::getInstancia()->carregarDiretorio(
			CONSULTA_ARQUIVO, pLog);
    }		
}

void Catalogador::ExcluirDados(Aba aba, const CString &sCaminho) {
    DiretorioBO::getInstancia()->excluirListaDiretorio(listaDiretorioPai, aba, sCaminho);
    DiretorioBO::getInstancia()->excluirListaDiretorio(listaDiretorioFilho, aba, sCaminho);
    DiretorioBO::getInstancia()->excluirListaDiretorio(listaArquivos, aba, sCaminho);
}

void Catalogador::AddItemArvore(CTreeCtrl &arvore, Diretorio diretorio, int Nivel,
        HTREEITEM item1) {
	POSITION pos;
	CList<Diretorio, Diretorio&> *listaFilhos;
    HTREEITEM item2;
    Diretorio filho;

    if (Nivel == 0) {
		item1 = arvore.InsertItem(&Arvore::item(diretorio.getNome(), NULL, TVI_ROOT, Nivel));
    }

    listaFilhos = DiretorioBO::getInstancia()->itensFilhos(*listaDiretorioFilho,
            diretorio.getAba().getCodigo(), diretorio.getOrdem(),
            diretorio.getCodigo());

	for (int i = 0; i < listaFilhos->GetSize(); ++i) {
		pos = listaFilhos->FindIndex(i);
		filho = listaFilhos->GetAt(pos);

		item2 = arvore.InsertItem(&Arvore::item(filho.getNome(), item1, TVI_LAST, Nivel));
		AddItemArvore(arvore, filho, ++Nivel, item2);
    }
}

void Catalogador::IncluirNovaAba() {
    Aba aba;

    CString sAba =  Dialogo::entrada(frmPrincipal, STR_FRMPRINCIPAL_DIGITAINCLUIRNOVAABA);

    if ((sAba.GetLength() > 0) && (Rotinas::Trim(sAba).GetLength() > 0)) {
        aba.setCodigo(AbaBO::getInstancia()->retMaxCodAba(*listaAbas));
        aba.setNome(Rotinas::SubString(sAba, 1, 10));
        aba.setOrdem(listaAbas->GetSize() + 1);
        AbaBO::getInstancia()->incluirAba(aba);
        Catalogador::IncluirNovaAba(aba.getNome(), aba.getOrdem()-1);
		listaAbas->AddTail(aba);
    }
}

void Catalogador::AlterarNomeAbaAtiva(IProgressoLog pLog) {
    Aba aba = Catalogador::getAbaAtual();
    CString sAba = Dialogo::entrada(frmPrincipal, STR_FRMPRINCIPAL_DIGITAALTERARNOMEABA,
            aba.getNome());
    if ((sAba.GetLength() > 0) && (Rotinas::Trim(sAba).GetLength() > 0)) {
		aba.setNome(Rotinas::SubString(sAba, 1, 10));
        AbaBO::getInstancia()->alterarAba(aba);
		TabControle::altera(frmPrincipal->frmFilho.tabControl, 
			frmPrincipal->frmFilho.tabControl.GetCurSel(), sAba);
		Catalogador::CarregarDados(pLog, FALSE, TRUE);
    }
}

void Catalogador::ExcluirAbaAtiva(IProgressoLog pLog) {
    Aba aba;
	int indiceSel = frmPrincipal->frmFilho.tabControl.GetCurSel();
    if (indiceSel > 0) {
        if (Dialogo::confirma(frmPrincipal, STR_FRMPRINCIPAL_CONFIRMAEXCLUIRABA)) {
			SetCursor(LoadCursor(NULL, IDC_WAIT));

            aba = getAbaAtual();
			ExcluirDados(aba, _T(""));
            AbaBO::getInstancia()->excluirAba(aba);
			TabControle::remove(frmPrincipal->frmFilho.tabControl, indiceSel);

			Catalogador::CarregarDados(pLog, FALSE, FALSE);

			frmPrincipal->barraStatus.SetPaneText(1, _T(""));

			SetCursor(LoadCursor(NULL, IDC_ARROW));
        }
    } else
            Dialogo::mensagemErro(frmPrincipal, STR_FRMPRINCIPAL_VALIDAEXCLUIRABA);
}

void Catalogador::IncluirNovaAba(const CString &nomeAba, int numAba){
	TabControle::adiciona(frmPrincipal->frmFilho.tabControl, numAba, nomeAba);
}

CTreeCtrl* Catalogador::getArvoreAtual() {
	return &frmPrincipal->frmFilho.arvore;
}

CTreeCtrl* Catalogador::getArvoreAtual(int nIndicePagina) {
	return &frmPrincipal->frmFilho.arvore;
}

CListCtrl* Catalogador::getTabelaAtual(int nIndicePagina) {
	return &frmPrincipal->frmFilho.tabela;
}

CListCtrl* Catalogador::getTabelaAtual() {
	return &frmPrincipal->frmFilho.tabela;
}

void Catalogador::CarregarArvore(CTreeCtrl &tvAba, Aba aba) {
	POSITION pos;
	Diretorio diretorio;

	//Catalogador.nodeRaiz = TreeView_InsertItem(tvAba, 
		//&Arvore_item(Catalogador.NO_RAIZ.wstr, TVI_ROOT));
	//TreeView_SelectSetFirstVisible(tvAba, Catalogador.nodeRaiz);

	for (int i = 0; i < listaDiretorioPai->GetSize(); ++i) {
		pos = listaDiretorioPai->FindIndex(i);
		diretorio = listaDiretorioPai->GetAt(pos);

        if (diretorio.getAba().getCodigo() == aba.getCodigo()) {
			AddItemArvore(tvAba, diretorio, 0, NULL);
        }
    }
}

void Catalogador::CarregarAbas() {
	CTreeCtrl* tvAba;
	POSITION pos;
    Aba aba;

	for (int i = 0; i < listaAbas->GetSize(); ++i) {
		pos = listaAbas->FindIndex(i);
		aba = listaAbas->GetAt(pos);

		IncluirNovaAba(aba.getNome(), i);
        tvAba = getArvoreAtual(i);
    }
}

Aba Catalogador::getAbaAtual() {
	int indiceSel = frmPrincipal->frmFilho.tabControl.GetCurSel();
    return *AbaBO::getInstancia()->pegaAbaPorOrdem(*listaAbas, indiceSel + 1);
}

void Catalogador::CarregarArquivosLista(CListCtrl &tabela, BOOL bLista1, const CString &caminho) {
	CString sPaiCaminho, sCaminho = caminho;
    CList<Diretorio, Diretorio&> listaLocal;
	POSITION pos;
	Diretorio diretorio;
    int nAba;

    if (bLista1) {
        sPaiCaminho = sCaminho;
        if (Rotinas::SubString(sCaminho, sCaminho.GetLength(), 1) != Rotinas::BARRA_INVERTIDA) {
            sCaminho += Rotinas::BARRA_INVERTIDA;
        }
        nAba = getAbaAtual().getCodigo();

		for (int i = 0; i < listaArquivos->GetSize(); ++i) {
			pos = listaArquivos->FindIndex(i);
			diretorio = listaArquivos->GetAt(pos);

            if (diretorio.getAba().getCodigo() == nAba) {
                if (diretorio.getCaminhoPai() == sPaiCaminho) {
                    if (Rotinas::StartsStr(sCaminho, diretorio.getCaminho())) {
						listaLocal.AddTail(diretorio);
                    }
                }
            }
        }
    } else {
		for (int i = 0; i < listaArquivos->GetSize(); ++i) {
			pos = listaArquivos->FindIndex(i);
			diretorio = listaArquivos->GetAt(pos);

			if (Rotinas::ContainsStr(Rotinas::UpperCase(diretorio.getCaminho()), 
				Rotinas::UpperCase(sCaminho))) {
				listaLocal.AddTail(diretorio);
            }
        }
    }
	Tabela::adiciona(tabela, bLista1, listaLocal, *listaExtensoes, frmPrincipal->getBarraProgresso());

	listaLocal.RemoveAll();
}

void Catalogador::TamTotalDiretorio(Aba aba, const CString &sCaminho) {
	POSITION pos;
	Diretorio diretorio;
    long conta;
    int nAba;
    unsigned long long soma, tam;
	CString status = _T(""), scaminho = sCaminho;

    conta = 0;
    soma = 0;

	for (int i = 0; i < listaArquivos->GetSize(); ++i) {
		pos = listaArquivos->FindIndex(i);
		diretorio = listaArquivos->GetAt(pos);

		nAba = aba.getCodigo();
        if (diretorio.getAba().getCodigo() == nAba) {
            if (diretorio.getTipo().getCodigo() != 'D') {
                if (Rotinas::Trim(scaminho).GetLength() > 0) {
                    if (Rotinas::StartsStr(scaminho, diretorio.getCaminho())) {
                        conta++;
                        tam = diretorio.getTamanho();
                        soma += tam;
                    }
                } else {
                    conta++;
                    tam = diretorio.getTamanho();
                    soma += tam;
                }
            }
        }
    }

	status += _T("Quantidade Total: ") + Rotinas::FromULong(conta) +
		_T(", Tamanho Total: ") + Rotinas::MontaTamanho(soma);

	frmPrincipal->barraStatus.SetPaneText(0, status);
}

BOOL Catalogador::testaSeparadorArquivo(const CString &sDir) {
    CString dir = Rotinas::SubString(sDir, sDir.GetLength(), 1);
    if (dir == Rotinas::BARRA_NORMAL
            || dir == Rotinas::BARRA_INVERTIDA) {
        return TRUE;
    } else {
        return FALSE;
    }
}

CStringList* Catalogador::montaCaminho(const CString &sCaminho, BOOL bRemover) {
    CString caminho = sCaminho;
	CStringList* sl = new CStringList();
	CString item;
	POSITION pos;
    sl = Rotinas::SListSeparador(caminho, Rotinas::BARRA_INVERTIDA);
	int tamlista = sl->GetSize();

	if (tamlista > 1) {
		pos = sl->FindIndex(tamlista - 1);
		item = sl->GetAt(pos);
		
		if (Rotinas::Trim(item).GetLength() == 0) {
			sl->RemoveAt(pos);
		}
		if (bRemover) {
			sl->RemoveAt(pos);
		}
	}
    return sl;
}

void Catalogador::Pesquisar() {
	CTreeCtrl* arvoreLocal = getArvoreAtual();

    if (arvoreLocal->GetCount() > 0) {
		CString edtPesquisa = frmPrincipal->getEdtPesquisaText();

        if (edtPesquisa.GetLength() >= 2) {
			frmPrincipal->frmFilho.mostraOcultarTabelaPesquisa(TRUE);

			CarregarArquivosLista(frmPrincipal->frmFilho.tabelaPesquisa, FALSE,
				edtPesquisa);
        } else {
			frmPrincipal->frmFilho.mostraOcultarTabelaPesquisa(FALSE);
			Tabela::limpar(frmPrincipal->frmFilho.tabelaPesquisa);
            Dialogo::mensagemInfo(frmPrincipal, STR_FRMPRINCIPAL_TAMMAXPESQUISA);
        }
    }
}

void Catalogador::PesquisarArvoreDiretorio(const CString &sCaminho, Aba aba, BOOL bRemover) {
	frmPrincipal->frmFilho.tabControl.SetCurSel(aba.getOrdem()-1);
	CTreeCtrl* arvore = getArvoreAtual();
	CStringList* sl = Catalogador::montaCaminho(sCaminho, bRemover);
	Arvore::encontrarCaminhoPorNome(*arvore, *sl);

	sl->RemoveAll();
	delete sl;
}

void Catalogador::LerArvoreDiretorio(CTreeCtrl &arvore, HTREEITEM item,
	CStatusBar &barraStatus) {
	POSITION pos;
	CString texto = _T("");
    CString caminho = _T("");	
	CStringList* lista = montaCaminho(arvore, item);
	int ntamlista = lista->GetSize();

	for (int i = 0; i < lista->GetSize(); ++i) {
		pos = lista->FindIndex(i);
		texto = lista->GetAt(pos);

		caminho += texto + Rotinas::BARRA_INVERTIDA;
	}

    if (ntamlista > 0) {
		caminho = Rotinas::SubString(caminho, 1, caminho.GetLength() - 1);
		barraStatus.SetPaneText(1, caminho);
    }

	lista->RemoveAll();
	delete lista;
}

void Catalogador::ListarArquivos() {
	CListCtrl* tabela = getTabelaAtual();
	CString texto = frmPrincipal->BarraStatusGetStatusText(1);
	CarregarArquivosLista(*tabela, TRUE, texto);
	TamTotalDiretorio(Catalogador::getAbaAtual(), texto);
}

void Catalogador::tabPanelMudou(){
	tabPanelMudou(Catalogador::getAbaAtual());
}

void Catalogador::tabPanelMudou(Aba aba) {
	Arvore::limpar(*getArvoreAtual());
	Tabela::limpar(*getTabelaAtual());
	CarregarArvore(*getArvoreAtual(), aba);
	TamTotalDiretorio(aba, _T(""));
}

void Catalogador::arvoreValorMudou(CTreeCtrl &arvore, HTREEITEM item) {
	LerArvoreDiretorio(arvore, item, frmPrincipal->barraStatus);
	ListarArquivos();
}

void Catalogador::DuploCliqueLista(const CString &nome, const CString &tipo) {
    if (tipo == Rotinas::lerStr(STR_TIPOLISTA_DIRETORIO)) {
		SetCursor(LoadCursor(NULL, IDC_WAIT));

        CString sCaminho = frmPrincipal->BarraStatusGetStatusText(1);
        if (testaSeparadorArquivo(sCaminho)) {
            sCaminho += nome;
        } else {
            sCaminho += Rotinas::BARRA_INVERTIDA + nome;
        }
		frmPrincipal->barraStatus.SetPaneText(1, sCaminho);

		PesquisarArvoreDiretorio(sCaminho, getAbaAtual(), FALSE);
		
		CarregarArquivosLista(*getTabelaAtual(), TRUE, sCaminho);
		TamTotalDiretorio(getAbaAtual(), sCaminho);

		SetCursor(LoadCursor(NULL, IDC_ARROW));
    }
}

void Catalogador::EncontrarItemLista(const CString &nomeAba, 
	const CString &nome, const CString &caminho) {

	SetCursor(LoadCursor(NULL, IDC_WAIT));
    
	Aba *aba = AbaBO::getInstancia()->pegaAbaPorNome(*listaAbas, nomeAba);
	tabPanelMudou(*aba);
	PesquisarArvoreDiretorio(caminho, *aba, TRUE);

	CTreeCtrl* arvore = getArvoreAtual();
	arvoreValorMudou(*arvore, arvore->GetSelectedItem());

	CListCtrl* tabela = getTabelaAtual();
	int nlinha = Tabela::encontrarLinha(*tabela, nome);
	Tabela::selecionaLinha(*tabela, nlinha);
	Tabela::ScrollLines(*tabela, nlinha);

	SetCursor(LoadCursor(NULL, IDC_ARROW));
}

int Catalogador::verificaNomeDiretorio(const CString &sCaminho, RotuloRaiz *sRotuloRaiz) {
    sRotuloRaiz->setRotulo(DiretorioBO::getInstancia()->removerDrive(sCaminho));
    if (sRotuloRaiz->getRotulo().GetLength() == 0) {

        sRotuloRaiz->setRotulo(
			Dialogo::entrada(frmPrincipal, STR_FRMPRINCIPAL_DIGITANOMEDIRETORIO));

        if (Rotinas::Trim(sRotuloRaiz->getRotulo()).GetLength() > 0) {
            sRotuloRaiz->setRotulo(Rotinas::Trim(sRotuloRaiz->getRotulo()));

            if (sRotuloRaiz->getRotulo().GetLength() > 0) {
                return 1;
            } else {
                Dialogo::mensagemInfo(frmPrincipal, STR_FRMPRINCIPAL_VALIDANOMEDIRETORIO);
                return 0;
            }
        } else {
            return 0;
        }
    } else if (Rotinas::Pos(CString(Rotinas::BARRA_INVERTIDA),
            sRotuloRaiz->getRotulo()) > 0) {
        sRotuloRaiz->setRotulo(Rotinas::SubString(sRotuloRaiz->getRotulo(),
                Rotinas::LastDelimiter(Rotinas::BARRA_INVERTIDA,
                        sRotuloRaiz->getRotulo()) + 1,
                sRotuloRaiz->getRotulo().GetLength()));
        return 2;
    } else {
        return 3;
    }
}

void Catalogador::ExportarArquivo(TipoExportar tipo, IProgressoLog pLog) {
    CString sExtensao = _T("");

    switch (tipo) {
        case teTXT:
            sExtensao = _T("txt");
            break;
        case teCSV:
            sExtensao = _T("csv");
            break;
        case teHTML:
            sExtensao = _T("html");
            break;
        case teXML:
            sExtensao = _T("xml");
            break;
        case teSQL:
            sExtensao = _T("sql");
            break;
    }

    Aba aba = Catalogador::getAbaAtual();
    
	CString sArq = Rotinas::AppDirPath();
	sArq += Rotinas::BARRA_INVERTIDA + aba.getNome() + _T(".") + sExtensao;
	CString arqSelecionado = EscolhaArquivo::salvarArquivo(frmPrincipal, sArq, sExtensao);
    if (arqSelecionado.GetLength() > 0) {
        if (Rotinas::FileExists(arqSelecionado)) {
			SetCursor(LoadCursor(NULL, IDC_WAIT));
            DiretorioBO::getInstancia()->exportarDiretorio(tipo, getAbaAtual(),
                    arqSelecionado, pLog);
			SetCursor(LoadCursor(NULL, IDC_ARROW));

            Dialogo::mensagemErro(frmPrincipal, STR_FRMPRINCIPAL_SUCESSOEXPORTAR);
        }
    }
    
}

CStringList* Catalogador::montaCaminho(CTreeCtrl &arvore, HTREEITEM item) {
	HTREEITEM pai = item;
	CStringList* lista = new CStringList();
	CString texto;

	do {
		texto = Arvore::GetItemText(arvore, pai);
		if (texto.GetLength() > 0) {
			lista->AddTail(texto);
			pai = arvore.GetParentItem(pai);
		}
		else {
			break;
		}
	} while (pai != NULL); // && pai != arvore.GetRoot());

	lista = Rotinas::SListInverter(*lista);

	return lista;
}

void Catalogador::ExcluirDiretorioSelecionado(IProgressoLog pLog) {
	CStringList* sl;
	CTreeCtrl* arvore = getArvoreAtual();
	
    if (Arvore::isSelecionado(*arvore)) {
		CListCtrl* tabela = getTabelaAtual();

		if (Dialogo::confirma(frmPrincipal, 
			STR_FRMPRINCIPAL_EXCLUIRDIRETORIOSELECIONADO)) {

			SetCursor(LoadCursor(NULL, IDC_WAIT));
            
			sl = montaCaminho(*arvore, arvore->GetSelectedItem());
			CString caminho = Rotinas::SListTexto(*sl);

			sl->RemoveAll();
			delete sl;

			DiretorioBO::getInstancia()->excluirDiretorio(getAbaAtual(), caminho);
			ExcluirDados(getAbaAtual(), caminho);

			arvore->DeleteItem(arvore->GetSelectedItem());
			Tabela::limpar(*tabela);

			CarregarDados(pLog, FALSE, FALSE);

			SetCursor(LoadCursor(NULL, IDC_ARROW));
        }
    }
}

void Catalogador::ImportarArquivo(const CStringList &log, IProgressoLog pLog) {
    int nResultado;

	CString arquivo = EscolhaArquivo::abrirArquivo(frmPrincipal);
	if (arquivo.GetLength() > 0) {
        if (Rotinas::FileExists(arquivo)) {
			SetCursor(LoadCursor(NULL, IDC_WAIT));
            nResultado = DiretorioBO::getInstancia()->importarDiretorioViaXML(
				getAbaAtual(), arquivo, *listaDiretorioPai, pLog);
            if (nResultado == -1) {
                Dialogo::mensagemErro(frmPrincipal,
                        STR_FRMPRINCIPAL_IMPORTACAONAOREALIZADA);
            } else if (nResultado == -2) {
                Dialogo::mensagemErro(frmPrincipal,
                        STR_FRMPRINCIPAL_DIRETORIOEXISTECATALOGO);
            } else {
				FinalizaImportacao(pLog);
            }
			SetCursor(LoadCursor(NULL, IDC_ARROW));
        }
    }
}

BOOL Catalogador::ImportarDiretorios(const CStringList &listaCaminho,
        BOOL bSubDiretorio) {
	POSITION pos;
    int nAba, nRotuloRaiz, nCodDirRaiz;
    RotuloRaiz *sRotuloRaiz = new RotuloRaiz();
    CString sCaminhoSemDrive;
    Importar importar;
	CString sCaminho = _T("");

    nAba = getAbaAtual().getCodigo();
    nCodDirRaiz = DiretorioBO::getInstancia()->retMaxCodDir(nAba, *listaDiretorioPai);

	frmImportarDiretorio = new FrmImportarDiretorio();

	for (int i = 0; i < listaCaminho.GetSize(); ++i) {
		pos = listaCaminho.FindIndex(i);
		sCaminho = listaCaminho.GetAt(pos);

        nRotuloRaiz = verificaNomeDiretorio(sCaminho, sRotuloRaiz);
        if (nRotuloRaiz > 0) {
            importar.setAba(nAba);
            importar.setCodDirRaiz(nCodDirRaiz);
            importar.setRotuloRaiz(sRotuloRaiz->getRotulo());
            if (nRotuloRaiz == 1) {
                importar.setNomeDirRaiz(sRotuloRaiz->getRotulo());
            } else if (nRotuloRaiz == 2) {
                sCaminhoSemDrive = DiretorioBO::getInstancia()->removerDrive(sCaminho);
                importar.setNomeDirRaiz(Rotinas::SubString(
                        sCaminhoSemDrive, 1,
                        Rotinas::LastDelimiter(Rotinas::BARRA_INVERTIDA,
                                sCaminhoSemDrive) - 1));
            } else if (nRotuloRaiz == 3) {
                importar.setNomeDirRaiz(_T(""));
            }
            importar.setCaminho(sCaminho);

			frmImportarDiretorio->listaImportar->AddTail(importar);
            nCodDirRaiz++;
        }
    }

	frmImportarDiretorio->bSubDiretorio = bSubDiretorio;

    if (bSubDiretorio) {

		if (FrmImportarDiretorio::Criar(frmPrincipal)) {
			FrmImportarDiretorio::Mostrar();
			frmImportarDiretorio->iniciarImportacao();
			frmImportarDiretorio->EndDialog(TRUE);
			frmImportarDiretorio->DestroyWindow();
		}
		delete frmImportarDiretorio;

		return TRUE;
    } else {
        if (!DiretorioBO::getInstancia()->verificaCodDir(importar.getAba(), importar.getRotuloRaiz(),
			*listaDiretorioPai)) {

			if (FrmImportarDiretorio::Criar(frmPrincipal)) {
				FrmImportarDiretorio::Mostrar();
				frmImportarDiretorio->iniciarImportacao();
				frmImportarDiretorio->EndDialog(TRUE);
				frmImportarDiretorio->DestroyWindow();
			}
			delete frmImportarDiretorio;
			
			return TRUE;
        } else {
            Dialogo::mensagemErro(frmPrincipal,
                    STR_FRMPRINCIPAL_DIRETORIOEXISTECATALOGO);

            return FALSE;
        }
    }

}

void Catalogador::FinalizaImportacao(IProgressoLog pLog) {
	CTreeCtrl* tvAba;

	SetCursor(LoadCursor(NULL, IDC_WAIT));

	CarregarDados(pLog, TRUE, TRUE);
    tvAba = getArvoreAtual();
	CarregarArvore(*tvAba, getAbaAtual());

	SetCursor(LoadCursor(NULL, IDC_ARROW));
    Dialogo::mensagemInfo(frmPrincipal, STR_FRMPRINCIPAL_DIRIMPORTACAOSUCESSO);

}


void Catalogador::ComecaImportacao(BOOL bSubDiretorios, IProgressoLog pLog) {
    CString sCaminho;
	CStringList listaCaminho;

	CString diretorio = EscolhaArquivo::abrirDiretorio(frmPrincipal);
	if (diretorio.GetLength() > 0) {
		
		if (Rotinas::DirectoryExists(diretorio)) {
			SetCursor(LoadCursor(NULL, IDC_WAIT));
			sCaminho = diretorio;

            if (bSubDiretorios) {
                DiretorioBO::getInstancia()->carregarSubDiretorios(sCaminho, listaCaminho);
            } else {                
				listaCaminho.AddTail(sCaminho);
            }

            if (ImportarDiretorios(listaCaminho, bSubDiretorios)) {
				FinalizaImportacao(pLog);
            }

			SetCursor(LoadCursor(NULL, IDC_ARROW));
        }
    }

}

}
}
