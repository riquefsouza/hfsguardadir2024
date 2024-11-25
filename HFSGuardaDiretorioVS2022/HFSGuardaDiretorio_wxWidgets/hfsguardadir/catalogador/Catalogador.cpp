#include "Catalogador.h"
#include "FrmSplash.h"
#include "hfsguardadir/objetosbo/AbaBO.h"
#include "hfsguardadir/objetosbo/ExtensaoBO.h"
#include "hfsguardadir/objetosbo/DiretorioBO.h"
#include "hfsguardadir/objetosdao/VisaoDAO.h"
#include "hfsguardadir/objetosgui/Dialogo.h"
#include "hfsguardadir/objetosgui/EscolhaArquivo.h"
#include "hfsguardadir/objetos/Importar.h"

using namespace hfsguardadir::objetosbo;
using namespace hfsguardadir::objetosdao;
using namespace hfsguardadir::objetos;

hfsguardadir::catalogador::Catalogador *catalogador;

namespace hfsguardadir {

namespace catalogador {

const wxString Catalogador::CONSULTA_DIR_PAI =
        "select aba, cod, ordem, coddirpai, nome, tam, tipo, modificado, " \
        "atributos, caminho, nomeaba, nomepai, caminhopai " \
        "from consultadirpai " \
        "order by 1,2,3,4";
const wxString Catalogador::CONSULTA_DIR_FILHO =
        "select aba, cod, ordem, coddirpai, nome, tam, tipo, modificado, " \
        "atributos, caminho, nomeaba, nomepai, caminhopai " \
        "from consultadirfilho " \
        "order by 1,2,3,4";
const wxString Catalogador::CONSULTA_ARQUIVO =
        "select aba, cod, ordem, coddirpai, nome, tam, tipo, modificado, " \
        "atributos, caminho, nomeaba, nomepai, caminhopai " \
        "from consultaarquivo " \
        "order by tipo desc, ordem";

const wxString Catalogador::NO_RAIZ = "Raiz";

Catalogador::Catalogador() {
	bGravarLogImportacao = false;
    //bSombrearLinhas = false;
    //bSombrearColunas = false;

	iniciarSistema();	
	frmPrincipal->SetCursor(wxCURSOR_WAIT);

	frmSplash = new FrmSplash(frmPrincipal);
    frmSplash->Show();
	frmSplash->Update();

	CarregarDados(frmSplash->ProgressoLog, true, true);
	CarregarAbas();
	tabPanelMudou();

    frmSplash->Close();
	delete frmSplash;

	frmPrincipal->SetCursor(wxCURSOR_ARROW);
}

Catalogador::~Catalogador() {
	DesconectarEventos();
}

void Catalogador::iniciarSistema() {
    wxString sBanco = Rotinas::AppDirPath() +
            Rotinas::BARRA_INVERTIDA + "GuardaDir.db";

    if (!Rotinas::FileExists(sBanco)){
        Rotinas::getInstancia()->Conectar(sBanco);

        AbaBO::getInstancia()->criarTabelaAbas();

        Aba aba(1, "DISCO1",0);
        AbaBO::getInstancia()->incluirAba(aba);

        ExtensaoBO::getInstancia()->criarTabelaExtensoes();
        DiretorioBO::getInstancia()->criarTabelaDiretorios();
        VisaoDAO::getInstancia()->criarVisao(wxString("consultadirpai"));
        VisaoDAO::getInstancia()->criarVisao(wxString("consultadirfilho"));
        VisaoDAO::getInstancia()->criarVisao(wxString("consultaarquivo"));
    } else
        Rotinas::getInstancia()->Conectar(sBanco);

}

void Catalogador::CarregarDados(IProgressoLog pLog, bool bExtensao, bool bDiretorio) {
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

void Catalogador::ExcluirDados(Aba aba, const wxString &sCaminho) {
    DiretorioBO::getInstancia()->excluirListaDiretorio(listaDiretorioPai, aba, sCaminho);
    DiretorioBO::getInstancia()->excluirListaDiretorio(listaDiretorioFilho, aba, sCaminho);
    DiretorioBO::getInstancia()->excluirListaDiretorio(listaArquivos, aba, sCaminho);
}

void Catalogador::AddItemArvore(Arvore *arvore, Diretorio diretorio, int Nivel,
        wxTreeItemId item1) {
    wxVector<Diretorio> listaFilhos;
    wxTreeItemId item2;
    Diretorio filho;

    if (Nivel == 0) {
		item1 = arvore->AppendItem(nodeRaiz, diretorio.getNome(), 0);
    }

    listaFilhos = DiretorioBO::getInstancia()->itensFilhos(listaDiretorioFilho,
            diretorio.getAba().getCodigo(), diretorio.getOrdem(),
            diretorio.getCodigo());

    for (unsigned int i = 0; i < listaFilhos.size(); i++) {
        filho = listaFilhos.at(i);
		item2 = arvore->AppendItem(item1, filho.getNome(), 0);      
        AddItemArvore(arvore, filho, ++Nivel, item2);
    }
}

void Catalogador::IncluirNovaAba() {
    Aba aba;

    wxString sAba =  Dialogo::entrada(frmPrincipal, "FrmPrincipal.DigitaIncluirNovaAba");

    if ((!sAba.IsEmpty()) && (sAba.Trim().length() > 0)) {
        //aba = new Aba();
        aba.setCodigo(AbaBO::getInstancia()->retMaxCodAba(listaAbas));
        aba.setNome(Rotinas::SubString(sAba, 1, 10));
        aba.setOrdem(listaAbas.size() + 1);
        AbaBO::getInstancia()->incluirAba(aba);
        IncluirNovaAba(aba.getNome());
        listaAbas.push_back(aba);
    }
}

void Catalogador::AlterarNomeAbaAtiva(IProgressoLog pLog) {
    Aba aba = getAbaAtual();
    wxString sAba = Dialogo::entrada(frmPrincipal, "FrmPrincipal.DigitaAlterarNomeAba",
            aba.getNome());
    if ((!sAba.IsEmpty()) && (sAba.Trim().length() > 0)) {
        aba.setNome(Rotinas::SubString(sAba, 1, 10));
        AbaBO::getInstancia()->alterarAba(aba);
		frmPrincipal->notebook->SetPageText(frmPrincipal->notebook->GetSelection(), sAba);
        CarregarDados(pLog, false, true);
    }
}

void Catalogador::ExcluirAbaAtiva(IProgressoLog pLog) {
    Aba aba;
	int indiceSel = frmPrincipal->notebook->GetSelection();
    if (indiceSel > 0) {
        int res = Dialogo::confirma(frmPrincipal, "FrmPrincipal.ConfirmaExcluirAba");
        if (res == wxYES) {
			frmPrincipal->SetCursor(wxCURSOR_WAIT);

            aba = getAbaAtual();
            ExcluirDados(aba, "");
            AbaBO::getInstancia()->excluirAba(aba);
			frmPrincipal->notebook->RemovePage(indiceSel);

            CarregarDados(pLog, false, false);

			frmPrincipal->barraStatus->SetStatusText("", 1);

			frmPrincipal->SetCursor(wxCURSOR_ARROW);
        }
    } else
            Dialogo::mensagemErro(frmPrincipal, "FrmPrincipal.ValidaExcluirAba");
}

void Catalogador::IncluirNovaAba(const wxString &nomeAba){
    wxPanel *panelAba;
    Arvore *arvore;
    wxSplitterWindow *sp;
    Tabela *tabela;
	wxPanel* panelEsquerdo;
	wxPanel* panelDireito;

	panelAba = new wxPanel(frmPrincipal->notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, "panelAba");
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer(wxVERTICAL);

	sp = new wxSplitterWindow(panelAba, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D, "splitter");
	//sp->Connect( wxEVT_IDLE, wxIdleEventHandler( FrmPrincipal::spOnIdle ), NULL, this );

	panelEsquerdo = new wxPanel(sp, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, "panelEsquerdo");
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer(wxVERTICAL);

	arvore = new Arvore(panelEsquerdo, frmPrincipal->imageList16);
	bSizer5->Add(arvore, 1, wxALL | wxEXPAND, 5);

	panelEsquerdo->SetSizer(bSizer5);
	panelEsquerdo->Layout();
	bSizer5->Fit(panelEsquerdo);
	panelDireito = new wxPanel(sp, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, "panelDireito");
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer(wxVERTICAL);

	tabela = new Tabela(panelDireito, true, frmPrincipal->imageList16, frmPrincipal->imageList32);

	bSizer6->Add(tabela, 1, wxALL | wxEXPAND, 5);

	panelDireito->SetSizer(bSizer6);
	panelDireito->Layout();
	bSizer6->Fit(panelDireito);
	sp->SplitVertically(panelEsquerdo, panelDireito, 200);
	bSizer7->Add(sp, 1, wxEXPAND, 5);


	panelAba->SetSizer(bSizer7);
	panelAba->Layout();
	bSizer7->Fit(panelAba);
	frmPrincipal->notebook->AddPage(panelAba, nomeAba, false, 0);


	arvore->Connect(wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler(FrmPrincipal::arvoreSelChanged), NULL, frmPrincipal);
	tabela->Connect(wxEVT_COMMAND_LIST_COL_CLICK, wxListEventHandler(FrmPrincipal::tabelaListColClick), NULL, frmPrincipal);
	tabela->Connect(wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler(FrmPrincipal::tabelaListItemSelected), NULL, frmPrincipal);
	
}

void Catalogador::DesconectarEventos() {
	Arvore *arvore;
	Tabela *tabela;

	for (unsigned int i = 0; i < listaAbas.size(); i++)
	{
		tabela = getTabelaAtual(i);
		arvore = getArvoreAtual(i);
	
		arvore->Disconnect(wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler(FrmPrincipal::arvoreSelChanged), NULL, frmPrincipal);
		tabela->Disconnect(wxEVT_COMMAND_LIST_COL_CLICK, wxListEventHandler(FrmPrincipal::tabelaListColClick), NULL, frmPrincipal);
		tabela->Disconnect(wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler(FrmPrincipal::tabelaListItemSelected), NULL, frmPrincipal);
	}
}

Arvore* Catalogador::getArvoreAtual() {
    return getArvoreAtual(frmPrincipal->notebook->GetSelection());
}

Arvore* Catalogador::getArvoreAtual(int nIndicePagina) {	
	wxPanel *panelAba;
	wxSplitterWindow* split;
	wxPanel* panelEsquerdo;
	Arvore* arvore;

	panelAba = (wxPanel *)frmPrincipal->notebook->GetPage(nIndicePagina);
	split = (wxSplitterWindow*)panelAba->GetChildren().GetFirst()->GetData();
	panelEsquerdo = (wxPanel *)split->GetWindow1();
	arvore = (Arvore*)panelEsquerdo->GetChildren().GetFirst()->GetData();
	
    return arvore;
}

wxSplitterWindow* Catalogador::getSplitAtual() {
	int nIndicePagina = frmPrincipal->notebook->GetSelection();
	wxPanel *panelAba;
	wxSplitterWindow* split;
	
	panelAba = (wxPanel *)frmPrincipal->notebook->GetPage(nIndicePagina);
	split = (wxSplitterWindow*)panelAba->GetChildren().GetFirst()->GetData();

    return split;
}

Tabela* Catalogador::getTabelaAtual(int nIndicePagina) {	
	wxPanel *panelAba;
	wxSplitterWindow* split;
	wxPanel* panelDireito;
	Tabela* tabela;

	panelAba = (wxPanel *)frmPrincipal->notebook->GetPage(nIndicePagina);
	split = (wxSplitterWindow*)panelAba->GetChildren().GetFirst()->GetData();
	panelDireito = (wxPanel *)split->GetWindow2();
	tabela = (Tabela*)panelDireito->GetChildren().GetFirst()->GetData();

	return tabela;
}

Tabela* Catalogador::getTabelaAtual() {	
    return getTabelaAtual(frmPrincipal->notebook->GetSelection());
}

void Catalogador::mostrarOcultarArvore(){
    wxSplitterWindow* split = (wxSplitterWindow*) getSplitAtual();
	wxPanel* panelEsquerdo = (wxPanel*)split->GetChildren().GetFirst()->GetData();
	wxPanel* panelDireito = (wxPanel*)split->GetChildren().GetLast()->GetData();

	if (split->IsSplit()) {
		split->Unsplit(panelEsquerdo);
	}
	else {
		panelEsquerdo->Show(true);
		panelDireito->Show(true);
		split->SplitVertically(panelEsquerdo, panelDireito, 200);
	}

}

void Catalogador::mostrarListaItensPesquisados(bool bMostrar) {

	if (!bMostrar) {
		frmPrincipal->spPesquisa->Unsplit();
	}
	else {
		frmPrincipal->m_panel2->Show(true);
		frmPrincipal->m_panel3->Show(true);
		frmPrincipal->spPesquisa->SplitHorizontally(
			frmPrincipal->m_panel2, frmPrincipal->m_panel3, 0);
	}
}


void Catalogador::CarregarArvore(Arvore *tvAba, Aba aba) {
	//frmPrincipal->SetCursor(*wxHOURGLASS_CURSOR);
	
	nodeRaiz = tvAba->GetRootItem();

	if (!nodeRaiz.IsOk()) {
		nodeRaiz = tvAba->AddRoot(NO_RAIZ);
	}
	   
    for each (Diretorio diretorio in listaDiretorioPai) {
        if (diretorio.getAba().getCodigo() == aba.getCodigo()) {
            AddItemArvore(tvAba, diretorio, 0, NULL);
        }
    }
	//frmPrincipal->SetCursor(*wxSTANDARD_CURSOR);
}

void Catalogador::CarregarAbas() {
    Arvore *tvAba;
    Aba aba;

    //frmPrincipal->pb->setMinimum(0);
    //frmPrincipal->pb->setMaximum(listaAbas.size() - 1);
    //frmPrincipal->pb->setValue(0);

    for (unsigned int i = 0; i < listaAbas.size(); i++) {
        aba = listaAbas.at(i);

        IncluirNovaAba(aba.getNome());
        tvAba = getArvoreAtual(i);
        CarregarArvore(tvAba, aba);
        //frmPrincipal->pb->setValue(i);
    }
}

Aba Catalogador::getAbaAtual() {
    return *AbaBO::getInstancia()->pegaAbaPorOrdem(
            listaAbas, frmPrincipal->notebook->GetSelection() + 1);
}

void Catalogador::CarregarArquivosLista(Tabela* tabela, bool bLista1, const wxString &caminho) {
    wxString sPaiCaminho, sCaminho = caminho;
    wxVector<Diretorio> listaLocal;
    int nAba;

    if (bLista1) {
        sPaiCaminho = sCaminho;
        if (Rotinas::SubString(sCaminho, sCaminho.length(), 1) != wxString(Rotinas::BARRA_INVERTIDA)) {
            sCaminho += Rotinas::BARRA_INVERTIDA;
        }
        nAba = getAbaAtual().getCodigo();
        for each (Diretorio diretorio in listaArquivos) {
            if (diretorio.getAba().getCodigo() == nAba) {
                if (diretorio.getCaminhoPai() == sPaiCaminho) {
                    if (Rotinas::StartsStr(sCaminho, diretorio.getCaminho())) {
                        listaLocal.push_back(diretorio);
                    }
                }
            }
        }
    } else {
        for each (Diretorio diretorio in listaArquivos) {
            if (Rotinas::ContainsStr(diretorio.getCaminho().Upper(),
                    sCaminho.Upper())) {
                listaLocal.push_back(diretorio);
            }
        }
    }
	tabela->modeloTabela(listaLocal, listaExtensoes, frmPrincipal->pb);

    listaLocal.clear();
}

void Catalogador::TamTotalDiretorio(wxString &sCaminho) {
    long conta;
    int nAba;
    wxULongLong soma, tam;

    conta = 0;
    soma = 0;

    for each (Diretorio diretorio in listaArquivos) {
        nAba = getAbaAtual().getCodigo();
        if (diretorio.getAba().getCodigo() == nAba) {
            if (diretorio.getTipo().getCodigo() != 'D') {
                if (sCaminho.Trim().length() > 0) {
                    if (Rotinas::StartsStr(sCaminho, diretorio.getCaminho())) {
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

	frmPrincipal->barraStatus->SetStatusText(
            "Quantidade Total: " + Rotinas::FormatLong(conta)
            + ", Tamanho Total: " + Rotinas::MontaTamanhoBig(soma.GetValue()), 0);
}

bool Catalogador::testaSeparadorArquivo(const wxString &sDir) {
    wxString dir = Rotinas::SubString(sDir, sDir.length(), 1);
    if (dir == wxString(Rotinas::BARRA_INVERTIDA)
            || dir == wxString(Rotinas::BARRA_NORMAL)
            || dir == wxString(Rotinas::BARRA_INVERTIDA)) {
        return true;
    } else {
        return false;
    }
}

wxArrayString Catalogador::montaCaminho(const wxString &sCaminho, bool bRemover) {
    wxString caminho = sCaminho;
    wxArrayString sl;

    sl = Rotinas::SListSeparador(caminho, Rotinas::BARRA_INVERTIDA);

	if (sl.size() > 1) {
		if (sl[sl.size() - 1].Trim().length() == 0) {
			sl.RemoveAt(sl.size() - 1);
		}
		if (bRemover) {
			sl.RemoveAt(sl.size() - 1);
		}
	}
    return sl;
}

void Catalogador::Pesquisar() {
    Arvore *arvoreLocal = getArvoreAtual();

    if (arvoreLocal->GetCount() > 0) {
        if (frmPrincipal->edtPesquisa->GetValue().length() >= 2) {
			mostrarListaItensPesquisados(true);

            CarregarArquivosLista(frmPrincipal->tabelaPesquisa, false,
				frmPrincipal->edtPesquisa->GetValue());
			//frmPrincipal->tabelaPesquisa->selectionModel()->clear();
            //frmPrincipal->tabelaPesquisa.setSombrearLinhas(true);
        } else {
			mostrarListaItensPesquisados(false);
			frmPrincipal->tabelaPesquisa->limpar();
            Dialogo::mensagemInfo(frmPrincipal, "FrmPrincipal.TamMaxPesquisa");
        }
    }
}

void Catalogador::PesquisarArvoreDiretorio(const wxString &sCaminho, Aba aba, bool bRemover) {
	frmPrincipal->notebook->SetSelection(aba.getOrdem()-1);
    Arvore *arvore = getArvoreAtual();
	wxArrayString sl = montaCaminho(sCaminho, bRemover);
	arvore->encontrarCaminhoPorNome(sl);
}

void Catalogador::LerArvoreDiretorio(Arvore *arvore, const wxTreeItemId &item,
	wxStatusBar *barraStatus) {
    wxString caminho = "";
	wxArrayString lista = montaCaminho(arvore, item);

	for (unsigned int i = 0; i < lista.size(); i++)
	{
		caminho += lista[i] + Rotinas::BARRA_INVERTIDA;
	}

    if (lista.size() > 0) {
		caminho = caminho.substr(0, caminho.length() - 1);
        barraStatus->SetStatusText(caminho, 1);
    }

}

void Catalogador::ListarArquivos() {
	Tabela* tabela = getTabelaAtual();
	CarregarArquivosLista(tabela, true, frmPrincipal->barraStatus->GetStatusText(1));
    TamTotalDiretorio(frmPrincipal->barraStatus->GetStatusText(1));
}

void Catalogador::tabPanelMudou(){
	/*
    Arvore *arvore = getArvoreAtual();
	wxTreeItemIdModel *modelo = (wxTreeItemIdModel*)arvore->model();
	QItemSelectionModel *selecao = (QItemSelectionModel*)arvore->selectionModel();
	*/

    TamTotalDiretorio(wxString(""));

	/*
    if (modelo->rowCount() > 1){
	//if (!selecao->hasSelection()) {
		arvore->setCurrentIndex(modelo->item(0)->index());
		arvoreValorMudou(arvore->currentIndex());
    }
	*/
}

void Catalogador::arvoreValorMudou(Arvore *arvore, const wxTreeItemId &item) {
    LerArvoreDiretorio(arvore, item, frmPrincipal->barraStatus);
    ListarArquivos();
}

void Catalogador::DuploCliqueLista(const wxString &nome, const wxString &tipo) {
    if (tipo == Rotinas::getRecurso("TipoLista.diretorio")) {        
		frmPrincipal->SetCursor(wxCURSOR_WAIT);

        wxString sCaminho = frmPrincipal->barraStatus->GetStatusText(1);
        if (testaSeparadorArquivo(sCaminho)) {
            sCaminho += nome;
        } else {
            sCaminho += Rotinas::BARRA_INVERTIDA + nome;
        }
		frmPrincipal->barraStatus->SetStatusText(sCaminho, 1);

        PesquisarArvoreDiretorio(sCaminho, getAbaAtual(), false);

		CarregarArquivosLista(getTabelaAtual(), true, sCaminho);
		TamTotalDiretorio(sCaminho);

		frmPrincipal->SetCursor(wxCURSOR_ARROW);
    }
}

void Catalogador::EncontrarItemLista(const wxString &nomeAba, 
	const wxString &nome, const wxString &caminho) {

	frmPrincipal->SetCursor(wxCURSOR_WAIT);
    
	Aba *aba = AbaBO::getInstancia()->pegaAbaPorNome(listaAbas, nomeAba);
    PesquisarArvoreDiretorio(caminho, *aba, true);

	Arvore *arvore = getArvoreAtual();
	arvoreValorMudou(arvore, arvore->GetSelection());

    Tabela *tabela = getTabelaAtual();
	int nlinha = tabela->encontrarLinha(nome);
	tabela->selecionaLinha(nlinha);
	tabela->ScrollLines(nlinha);

	frmPrincipal->SetCursor(wxCURSOR_ARROW);
}

int Catalogador::verificaNomeDiretorio(wxString &sCaminho, RotuloRaiz *sRotuloRaiz) {
    sRotuloRaiz->setRotulo(
            DiretorioBO::getInstancia()->removerDrive(sCaminho));
    if (sRotuloRaiz->getRotulo().length() == 0) {

        sRotuloRaiz->setRotulo(Dialogo::entrada(frmPrincipal,
                "FrmPrincipal.DigitaNomeDiretorio"));

        if (sRotuloRaiz->getRotulo().Trim().length() > 0) {
            sRotuloRaiz->setRotulo(sRotuloRaiz->getRotulo().Trim());

            if (sRotuloRaiz->getRotulo().length() > 0) {
                return 1;
            } else {
                Dialogo::mensagemInfo(frmPrincipal,
                        "FrmPrincipal.ValidaNomeDiretorio");
                return 0;
            }
        } else {
            return 0;
        }
    } else if (Rotinas::Pos(Rotinas::BARRA_INVERTIDA,
            sRotuloRaiz->getRotulo()) > 0) {
        sRotuloRaiz->setRotulo(Rotinas::SubString(sRotuloRaiz->getRotulo(),
                Rotinas::LastDelimiter(Rotinas::BARRA_INVERTIDA,
                        sRotuloRaiz->getRotulo()) + 1,
                sRotuloRaiz->getRotulo().length()));
        return 2;
    } else {
        return 3;
    }
}

void Catalogador::ExportarArquivo(TipoExportar tipo, IProgressoLog pLog) {
    wxString sExtensao = "";

    switch (tipo) {
        case teTXT:
            sExtensao = "txt";
            break;
        case teCSV:
            sExtensao = "csv";
            break;
        case teHTML:
            sExtensao = "html";
            break;
        case teXML:
            sExtensao = "xml";
            break;
        case teSQL:
            sExtensao = "sql";
            break;
    }

    Aba aba = getAbaAtual();
    
    wxString sArq = Rotinas::AppDirPath() +
            Rotinas::BARRA_INVERTIDA+
            aba.getNome()+"."+sExtensao;
	wxString arqSelecionado = EscolhaArquivo::salvarArquivo(frmPrincipal, sArq, sExtensao);
    if (!arqSelecionado.IsEmpty()) {
		wxFileName arquivo(arqSelecionado);
		
        if (arquivo.Exists()) {
			frmPrincipal->SetCursor(wxCURSOR_WAIT);
            DiretorioBO::getInstancia()->exportarDiretorio(tipo, getAbaAtual(),
                    arquivo.GetFullPath(), pLog);
			frmPrincipal->SetCursor(wxCURSOR_ARROW);

            Dialogo::mensagemErro(frmPrincipal, "FrmPrincipal.SucessoExportar");
        }
    }
    
}

wxArrayString Catalogador::montaCaminho(Arvore *arvore, const wxTreeItemId &item) {
	wxTreeItemId pai = item;
	wxArrayString lista;

	do {		
		lista.Add(arvore->GetItemText(pai));
		pai = arvore->GetItemParent(pai);
	} while (pai.IsOk() && pai != arvore->GetRootItem());

	std::reverse(lista.begin(), lista.end());

	return lista;
}

void Catalogador::ExcluirDiretorioSelecionado(IProgressoLog pLog) {
    Arvore *arvore = getArvoreAtual();

    if (arvore->GetSelection().IsOk()) {
        Tabela *tabela = getTabelaAtual();
		int res = Dialogo::confirma(frmPrincipal, "FrmPrincipal.ExcluirDiretorioSelecionado");
		if (res == wxYES) {
			frmPrincipal->SetCursor(wxCURSOR_WAIT);
            wxArrayString sl = montaCaminho(arvore, arvore->GetSelection());
			wxString caminho = Rotinas::SListTexto(sl);

			DiretorioBO::getInstancia()->excluirDiretorio(getAbaAtual(), caminho);
            ExcluirDados(getAbaAtual(), caminho);

			arvore->Delete(arvore->GetSelection());
			tabela->limpar();

            CarregarDados(pLog, false, false);

			frmPrincipal->SetCursor(wxCURSOR_ARROW);
        }
    }
}

void Catalogador::ImportarArquivo(wxArrayString log, IProgressoLog pLog) {
    int nResultado;

	wxString arqSelecionado = EscolhaArquivo::abrirArquivo(frmPrincipal);
	if (!arqSelecionado.IsEmpty()) {
		wxFileName arquivo(arqSelecionado);

        if (arquivo.Exists()) {
			frmPrincipal->SetCursor(wxCURSOR_WAIT);
            nResultado = DiretorioBO::getInstancia()->importarDiretorioViaXML(
            getAbaAtual(), arquivo.GetFullPath(), listaDiretorioPai, pLog);
            if (nResultado == -1) {
                Dialogo::mensagemErro(frmPrincipal,
                        "FrmPrincipal.ImportacaoNaoRealizada");
            } else if (nResultado == -2) {
                Dialogo::mensagemErro(frmPrincipal,
                        "FrmPrincipal.DiretorioExisteCatalogo");
            } else {
                FinalizaImportacao(pLog);
            }
			frmPrincipal->SetCursor(wxCURSOR_ARROW);
        }
    }
}

bool Catalogador::ImportarDiretorios(wxArrayString listaCaminho,
        bool bSubDiretorio, FrmImportarDiretorio *frmImportarDiretorio) {
    int nAba, nRotuloRaiz, nCodDirRaiz;
    RotuloRaiz *sRotuloRaiz = new RotuloRaiz();
    wxString sCaminhoSemDrive;
    Importar importar;

    nAba = getAbaAtual().getCodigo();
    nCodDirRaiz = DiretorioBO::getInstancia()->retMaxCodDir(nAba,
            listaDiretorioPai);

    for each (wxString sCaminho in listaCaminho) {
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
                importar.setNomeDirRaiz(wxString(""));
            }
            importar.setCaminho(sCaminho);

            frmImportarDiretorio->listaImportar.push_back(importar);
            nCodDirRaiz++;
        }
    }

    frmImportarDiretorio->bSubDiretorio = bSubDiretorio;

    if (bSubDiretorio) {
		frmImportarDiretorio->Show();
		frmImportarDiretorio->iniciarImportacao();
        return true;
    } else {
        if (!DiretorioBO::getInstancia()->verificaCodDir(
                importar.getAba(), importar.getRotuloRaiz(),
                listaDiretorioPai)) {
			frmImportarDiretorio->Show();
			frmImportarDiretorio->iniciarImportacao();
            return true;
        } else {
            Dialogo::mensagemErro(frmPrincipal,
                    "FrmPrincipal.DiretorioExisteCatalogo");

            return false;
        }
    }

}

void Catalogador::FinalizaImportacao(IProgressoLog pLog) {
    Arvore *tvAba;

	frmPrincipal->SetCursor(wxCURSOR_WAIT);

    CarregarDados(pLog, true, true);
    tvAba = getArvoreAtual();
    CarregarArvore(tvAba, getAbaAtual());

	frmPrincipal->SetCursor(wxCURSOR_ARROW);
    Dialogo::mensagemInfo(frmPrincipal, "FrmPrincipal.DirImportacaoSucesso");

}


void Catalogador::ComecaImportacao(bool bSubDiretorios, IProgressoLog pLog) {
    wxString sCaminho;
    wxArrayString listaCaminho;

	wxString dirSelecionado = EscolhaArquivo::abrirDiretorio(frmPrincipal);
	if (!dirSelecionado.IsEmpty()) {
		wxFileName diretorio(dirSelecionado);
		if (diretorio.Exists()) {
			frmPrincipal->SetCursor(wxCURSOR_WAIT);
			sCaminho = diretorio.GetFullPath();

            frmImportarDiretorio = new FrmImportarDiretorio(frmPrincipal);

            if (bSubDiretorios) {
                DiretorioBO::getInstancia()->
                        carregarSubDiretorios(sCaminho, listaCaminho);
            } else {
                listaCaminho.Add(sCaminho);
            }

            if (ImportarDiretorios(listaCaminho, bSubDiretorios,
                    frmImportarDiretorio)) {
                FinalizaImportacao(pLog);
            }

			frmPrincipal->SetCursor(wxCURSOR_ARROW);
        }
    }

}


}
}
