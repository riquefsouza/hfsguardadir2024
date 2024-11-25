#include <QInputDialog>
#include <QHeaderView>

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

Catalogador *catalogador;

namespace hfsguardadir {

namespace catalogador {

const QString Catalogador::CONSULTA_DIR_PAI =
        "select aba, cod, ordem, coddirpai, nome, tam, tipo, modificado, " \
        "atributos, caminho, nomeaba, nomepai, caminhopai " \
        "from consultadirpai " \
        "order by 1,2,3,4";
const QString Catalogador::CONSULTA_DIR_FILHO =
        "select aba, cod, ordem, coddirpai, nome, tam, tipo, modificado, " \
        "atributos, caminho, nomeaba, nomepai, caminhopai " \
        "from consultadirfilho " \
        "order by 1,2,3,4";
const QString Catalogador::CONSULTA_ARQUIVO =
        "select aba, cod, ordem, coddirpai, nome, tam, tipo, modificado, " \
        "atributos, caminho, nomeaba, nomepai, caminhopai " \
        "from consultaarquivo " \
        "order by tipo desc, ordem";

const QString Catalogador::NO_RAIZ = "Raiz";

Catalogador::Catalogador() {
	bGravarLogImportacao = false;
    //bSombrearLinhas = false;
    //bSombrearColunas = false;

	iniciarSistema();
	frmPrincipal->setCursor(Qt::WaitCursor);

	frmSplash = new FrmSplash();
    frmSplash->show();
	frmSplash->update();

	CarregarDados(frmSplash->ProgressoLog, true, true);
	CarregarAbas();
	tabPanelMudou();

    frmSplash->close();
	delete frmSplash;

	frmPrincipal->setCursor(Qt::ArrowCursor);
}

Catalogador::~Catalogador() {
	DesconectarEventos();
}

void Catalogador::iniciarSistema() {
    QString sBanco = qApp->applicationDirPath() +
            Rotinas::BARRA_INVERTIDA + "GuardaDir.db";

    if (!Rotinas::FileExists(sBanco)){
        Rotinas::getInstancia()->Conectar(sBanco);

        AbaBO::getInstancia()->criarTabelaAbas();

        Aba aba(1, "DISCO1",0);
        AbaBO::getInstancia()->incluirAba(aba);

        ExtensaoBO::getInstancia()->criarTabelaExtensoes();
        DiretorioBO::getInstancia()->criarTabelaDiretorios();
        VisaoDAO::getInstancia()->criarVisao(QString("consultadirpai"));
        VisaoDAO::getInstancia()->criarVisao(QString("consultadirfilho"));
        VisaoDAO::getInstancia()->criarVisao(QString("consultaarquivo"));
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

void Catalogador::ExcluirDados(Aba aba, const QString &sCaminho) {
    DiretorioBO::getInstancia()->excluirListaDiretorio(listaDiretorioPai, aba, sCaminho);
    DiretorioBO::getInstancia()->excluirListaDiretorio(listaDiretorioFilho, aba, sCaminho);
    DiretorioBO::getInstancia()->excluirListaDiretorio(listaArquivos, aba, sCaminho);
}

void Catalogador::AddItemArvore(Diretorio diretorio, int Nivel,
        QStandardItem *node1) {
    QList<Diretorio> listaFilhos;
    QStandardItem *node2;
    Diretorio filho;

    if (Nivel == 0) {
        node1 = new QStandardItem(Rotinas::getInstancia()->diretorioIcone, diretorio.getNome());
        nodeRaiz->appendRow(node1);
    }

    listaFilhos = DiretorioBO::getInstancia()->itensFilhos(listaDiretorioFilho,
            diretorio.getAba().getCodigo(), diretorio.getOrdem(),
            diretorio.getCodigo());

    for (int i = 0; i < listaFilhos.size(); i++) {
        filho = listaFilhos.at(i);

        node2 = new QStandardItem(Rotinas::getInstancia()->diretorioIcone, filho.getNome());
        node1->appendRow(node2);
        AddItemArvore(filho, ++Nivel, node2);
    }
}

void Catalogador::IncluirNovaAba() {
    Aba aba;

    QString sAba =  Dialogo::entrada(frmPrincipal, "FrmPrincipal.DigitaIncluirNovaAba");

    if ((!sAba.isEmpty()) && (sAba.trimmed().length() > 0)) {
        //aba = new Aba();
        aba.setCodigo(AbaBO::getInstancia()->retMaxCodAba(listaAbas));
        aba.setNome(Rotinas::SubString(sAba, 1, 10));
        aba.setOrdem(listaAbas.size() + 1);
        AbaBO::getInstancia()->incluirAba(aba);
        IncluirNovaAba(aba.getNome());
        listaAbas.append(aba);
    }
}

void Catalogador::AlterarNomeAbaAtiva(IProgressoLog pLog) {
    Aba aba = getAbaAtual();
    QString sAba = Dialogo::entrada(frmPrincipal, "FrmPrincipal.DigitaAlterarNomeAba",
            aba.getNome());
    if ((!sAba.isEmpty()) && (sAba.trimmed().length() > 0)) {
        aba.setNome(Rotinas::SubString(sAba, 1, 10));
        AbaBO::getInstancia()->alterarAba(aba);
		frmPrincipal->tabPanel->setTabText(frmPrincipal->tabPanel->currentIndex(), sAba);
        CarregarDados(pLog, false, true);
    }
}

void Catalogador::ExcluirAbaAtiva(IProgressoLog pLog) {
    Aba aba;
    int indiceSel = frmPrincipal->tabPanel->currentIndex();
    if (indiceSel > 0) {
        QMessageBox::StandardButton res = Dialogo::confirma(frmPrincipal, "FrmPrincipal.ConfirmaExcluirAba");
        if (res == QMessageBox::Yes) {
			frmPrincipal->setCursor(Qt::WaitCursor);

            aba = getAbaAtual();
            ExcluirDados(aba, "");
            AbaBO::getInstancia()->excluirAba(aba);
			frmPrincipal->tabPanel->removeTab(indiceSel);

            CarregarDados(pLog, false, false);

			frmPrincipal->barraStatus2->setText("");

			frmPrincipal->setCursor(Qt::ArrowCursor);
        }
    } else
            Dialogo::mensagemErro(frmPrincipal, "FrmPrincipal.ValidaExcluirAba");
}

void Catalogador::IncluirNovaAba(const QString &nomeAba){
    //QWidget *panelAba;
    Arvore *arvore;
    QSplitter *split;
    Tabela *tabela;
    //QStandardItemModel *modeloTabela;

    //panelAba = new QWidget(frmPrincipal);
    split = new QSplitter(Qt::Horizontal, frmPrincipal);
	frmPrincipal->tabPanel->addTab(split, Rotinas::getInstancia()->cdouroIcone, nomeAba);

    arvore = new Arvore(frmPrincipal);
    tabela = new Tabela(frmPrincipal, true);

	tabela->connect(tabela, SIGNAL(doubleClicked(QModelIndex)),
		frmPrincipal, SLOT(tabelaDoubleClicked(QModelIndex)));

	arvore->connect(arvore, SIGNAL(pressed(QModelIndex)),
		frmPrincipal, SLOT(arvorePressed(QModelIndex)));
	arvore->connect(arvore, SIGNAL(expanded(QModelIndex)),
		frmPrincipal, SLOT(arvoreExpanded(QModelIndex)));
	arvore->connect(arvore, SIGNAL(collapsed(QModelIndex)),
		frmPrincipal, SLOT(arvoreCollapsed(QModelIndex)));
		
    split->addWidget(arvore);
    split->addWidget(tabela);
    split->setStretchFactor(1, 50);

}

void Catalogador::DesconectarEventos() {
	Arvore *arvore;
	Tabela *tabela;

	for (int i = 0; i < listaAbas.size(); i++)
	{
		tabela = getTabelaAtual(i);
		arvore = getArvoreAtual(i);
		
		tabela->disconnect(tabela, SIGNAL(doubleClicked(QModelIndex)),
			frmPrincipal, SLOT(tabelaDoubleClicked(QModelIndex)));

		arvore->disconnect(arvore, SIGNAL(pressed(QModelIndex)),
			frmPrincipal, SLOT(arvorePressed(QModelIndex)));
		arvore->disconnect(arvore, SIGNAL(expanded(QModelIndex)),
			frmPrincipal, SLOT(arvoreExpanded(QModelIndex)));
		arvore->disconnect(arvore, SIGNAL(collapsed(QModelIndex)),
			frmPrincipal, SLOT(arvoreCollapsed(QModelIndex)));

	}
}

Arvore* Catalogador::getArvoreAtual() {
    return getArvoreAtual(frmPrincipal->tabPanel->currentIndex());
}

Arvore* Catalogador::getArvoreAtual(int nIndicePagina) {
    QSplitter* split = (QSplitter*)frmPrincipal->tabPanel->widget(nIndicePagina);
    Arvore* arvore = (Arvore*) split->widget(0);

    return arvore;
}

QSplitter* Catalogador::getSplitAtual() {
    int nIndicePagina = frmPrincipal->tabPanel->currentIndex();
    QSplitter* split = (QSplitter*)frmPrincipal->tabPanel->widget(nIndicePagina);
    return split;
}

Tabela* Catalogador::getTabelaAtual(int nIndicePagina) {	
	QSplitter* split = (QSplitter*)frmPrincipal->tabPanel->widget(nIndicePagina);
	Tabela* tabela = (Tabela*)split->widget(1);

	return tabela;
}

Tabela* Catalogador::getTabelaAtual() {	
    return getTabelaAtual(frmPrincipal->tabPanel->currentIndex());
}

void Catalogador::mostrarOcultarArvore(){
    QSplitter* split = (QSplitter*) getSplitAtual();
    split->widget(1)->setVisible(!split->widget(1)->isVisible());
}

void Catalogador::CarregarArvore(Arvore *tvAba, Aba aba) {

    QStandardItemModel *modelo = new QStandardItemModel();
    nodeRaiz = modelo->invisibleRootItem();
    nodeRaiz->setText(NO_RAIZ);

    foreach (Diretorio diretorio, listaDiretorioPai) {
        if (diretorio.getAba().getCodigo() == aba.getCodigo()) {
            AddItemArvore(diretorio, 0, NULL);
        }
    }

    tvAba->setModel(modelo);
}

void Catalogador::CarregarAbas() {
    Arvore *tvAba;
    Aba aba;

    //frmPrincipal->pb->setMinimum(0);
    //frmPrincipal->pb->setMaximum(listaAbas.size() - 1);
    //frmPrincipal->pb->setValue(0);

    for (int i = 0; i < listaAbas.size(); i++) {
        aba = listaAbas.at(i);

        IncluirNovaAba(aba.getNome());
        tvAba = getArvoreAtual(i);
        CarregarArvore(tvAba, aba);
        //frmPrincipal->pb->setValue(i);
    }
}

Aba Catalogador::getAbaAtual() {
    return *AbaBO::getInstancia()->pegaAbaPorOrdem(
            listaAbas, frmPrincipal->tabPanel->currentIndex() + 1);
}

void Catalogador::CarregarArquivosLista(Tabela* tabela, bool bLista1, const QString caminho) {
    QString sPaiCaminho, sCaminho = caminho;
    QList<Diretorio> listaLocal;
    //QStandardItemModel *lvArquivos;
    int nAba;

    if (bLista1) {
        sPaiCaminho = sCaminho;
        if (Rotinas::SubString(sCaminho, sCaminho.length(), 1) != QString(Rotinas::BARRA_INVERTIDA)) {
            sCaminho += Rotinas::BARRA_INVERTIDA;
        }
        nAba = getAbaAtual().getCodigo();
        foreach (Diretorio diretorio, listaArquivos) {
            if (diretorio.getAba().getCodigo() == nAba) {
                if (diretorio.getCaminhoPai() == sPaiCaminho) {
                    if (Rotinas::StartsStr(sCaminho, diretorio.getCaminho())) {
                        listaLocal.append(diretorio);
                    }
                }
            }
        }
    } else {
        foreach (Diretorio diretorio, listaArquivos) {
            if (Rotinas::ContainsStr(diretorio.getCaminho().toUpper(),
                    sCaminho.toUpper())) {
                listaLocal.append(diretorio);
            }
        }
    }
	tabela->modeloTabela(listaLocal, listaExtensoes, frmPrincipal->pb);

    listaLocal.clear();
}

void Catalogador::TamTotalDiretorio(QString sCaminho) {
    long conta;
    int nAba;
    long double soma, tam;

    conta = 0;
    soma = 0;

    foreach (Diretorio diretorio, listaArquivos) {
        nAba = getAbaAtual().getCodigo();
        if (diretorio.getAba().getCodigo() == nAba) {
            if (diretorio.getTipo().getCodigo() != 'D') {
                if (sCaminho.trimmed().length() > 0) {
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

	frmPrincipal->barraStatus1->setText(
            "Quantidade Total: " + Rotinas::FormatLong(conta)
            + ", Tamanho Total: " + Rotinas::MontaTamanhoBig(soma));
}

bool Catalogador::testaSeparadorArquivo(const QString &sDir) {
    QString dir = Rotinas::SubString(sDir, sDir.length(), 1);
    if (dir == QString(Rotinas::BARRA_INVERTIDA)
            || dir == QString(Rotinas::BARRA_NORMAL)
            || dir == QString(Rotinas::BARRA_INVERTIDA)) {
        return true;
    } else {
        return false;
    }
}

QStringList Catalogador::montaCaminho(const QString &sCaminho, bool bRemover) {
    QString caminho = sCaminho;
    QStringList sl;

    sl = Rotinas::SListSeparador(caminho, Rotinas::BARRA_INVERTIDA);

	if (sl.size() > 1) {
		if (sl.at(sl.size() - 1).trimmed().length() == 0) {
			sl.removeAt(sl.size() - 1);
		}
		if (bRemover) {
			sl.removeAt(sl.size() - 1);
		}
	}
    return sl;
}

void Catalogador::Pesquisar() {
    Arvore *arvoreLocal = getArvoreAtual();
    QStandardItemModel *modelo = (QStandardItemModel*) arvoreLocal->model();

    if (modelo->rowCount() > 0) {
        if (frmPrincipal->edtPesquisa->text().length() >= 2) {
			frmPrincipal->spPesquisa->widget(1)->setVisible(true);
            CarregarArquivosLista(frmPrincipal->tabelaPesquisa, false,
				frmPrincipal->edtPesquisa->text());
			frmPrincipal->tabelaPesquisa->selectionModel()->clear();
            //frmPrincipal->tabelaPesquisa.setSombrearLinhas(true);
        } else {
			frmPrincipal->spPesquisa->widget(1)->setVisible(false);
			frmPrincipal->tabelaPesquisa->limpar();
            Dialogo::mensagemInfo(frmPrincipal, "FrmPrincipal.TamMaxPesquisa");
        }
    }
}

void Catalogador::PesquisarArvoreDiretorio(const QString &sCaminho, Aba aba, bool bRemover) {
	frmPrincipal->tabPanel->setCurrentIndex(aba.getOrdem()-1);
    Arvore *arvore = getArvoreAtual();
	QStringList sl = montaCaminho(sCaminho, bRemover);
	arvore->encontrarCaminhoPorNome(sl);
}

void Catalogador::LerArvoreDiretorio(const QModelIndex & mi,
        QLabel *barraStatus) {
    QString caminho = "";
	QStringList lista = montaCaminho(mi);

	foreach (QString item, lista)
	{
		caminho += item + Rotinas::BARRA_INVERTIDA;
	}

    if (lista.size() > 0) {
        barraStatus->setText(caminho.mid(0, caminho.length()-1));
    }

}

void Catalogador::ListarArquivos() {
	Tabela* tabela = getTabelaAtual();
	CarregarArquivosLista(tabela, true, frmPrincipal->barraStatus2->text());
    TamTotalDiretorio(frmPrincipal->barraStatus2->text());
}

void Catalogador::tabPanelMudou(){
	/*
    Arvore *arvore = getArvoreAtual();
	QStandardItemModel *modelo = (QStandardItemModel*)arvore->model();
	QItemSelectionModel *selecao = (QItemSelectionModel*)arvore->selectionModel();
	*/

    TamTotalDiretorio(QString(""));

	/*
    if (modelo->rowCount() > 1){
	//if (!selecao->hasSelection()) {
		arvore->setCurrentIndex(modelo->item(0)->index());
		arvoreValorMudou(arvore->currentIndex());
    }
	*/
}

void Catalogador::arvoreValorMudou(const QModelIndex & mi) {
    LerArvoreDiretorio(mi, frmPrincipal->barraStatus2);
    ListarArquivos();
}

void Catalogador::DuploCliqueLista(const QString &nome, const QString &tipo) {
    if (tipo == Rotinas::getRecurso("TipoLista.diretorio")) {        
		frmPrincipal->setCursor(Qt::WaitCursor);

        QString sCaminho = frmPrincipal->barraStatus2->text();
        if (testaSeparadorArquivo(sCaminho)) {
            sCaminho += nome;
        } else {
            sCaminho += Rotinas::BARRA_INVERTIDA + nome;
        }
		frmPrincipal->barraStatus2->setText(sCaminho);

        PesquisarArvoreDiretorio(sCaminho, getAbaAtual(), false);

		CarregarArquivosLista(getTabelaAtual(), true, sCaminho);
		TamTotalDiretorio(sCaminho);

		frmPrincipal->setCursor(Qt::ArrowCursor);
    }
}

void Catalogador::EncontrarItemLista(const QString &nomeAba, 
	const QString &nome, const QString &caminho) {

	frmPrincipal->setCursor(Qt::WaitCursor);
    
	Aba *aba = AbaBO::getInstancia()->pegaAbaPorNome(listaAbas, nomeAba);
    PesquisarArvoreDiretorio(caminho, *aba, true);

	Arvore *arvore = getArvoreAtual();
	arvoreValorMudou(arvore->currentIndex());

    Tabela *tabela = getTabelaAtual();
	int nlinha = tabela->encontrarLinha(nome);
	tabela->selectRow(nlinha);
	tabela->scrollTo(tabela->currentIndex());

	frmPrincipal->setCursor(Qt::ArrowCursor);
}

int Catalogador::verificaNomeDiretorio(QString &sCaminho, RotuloRaiz *sRotuloRaiz) {
    sRotuloRaiz->setRotulo(
            DiretorioBO::getInstancia()->removerDrive(sCaminho));
    if (sRotuloRaiz->getRotulo().length() == 0) {

        sRotuloRaiz->setRotulo(Dialogo::entrada(frmPrincipal,
                "FrmPrincipal.DigitaNomeDiretorio"));

        if (sRotuloRaiz->getRotulo().trimmed().length() > 0) {
            sRotuloRaiz->setRotulo(sRotuloRaiz->getRotulo().trimmed());

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
    QString sExtensao = "";

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
    
    QString sArq = QDir::currentPath() +
            Rotinas::BARRA_INVERTIDA+
            aba.getNome()+"."+sExtensao;
	QString arqSelecionado = EscolhaArquivo::salvarArquivo(frmPrincipal, sArq, sExtensao);
    if (!arqSelecionado.isEmpty()) {
		QFileInfo arquivo(arqSelecionado);
		
        if (arquivo.exists()) {
			frmPrincipal->setCursor(Qt::WaitCursor);
            DiretorioBO::getInstancia()->exportarDiretorio(tipo, getAbaAtual(),
                    arquivo.path(), pLog);
			frmPrincipal->setCursor(Qt::ArrowCursor);

            Dialogo::mensagemErro(frmPrincipal, "FrmPrincipal.SucessoExportar");
        }
    }
    
}

QStringList Catalogador::montaCaminho(const QModelIndex & mi) {
	QStandardItemModel *modelo = (QStandardItemModel*)mi.model();
	QModelIndex pai = mi;
	QStringList lista;

	do {		
		lista.append(pai.data(Qt::DisplayRole).toString());	
		pai = modelo->parent(pai);
	} while (pai.isValid());

	std::reverse(lista.begin(), lista.end());

	return lista;
}

void Catalogador::ExcluirDiretorioSelecionado(IProgressoLog pLog) {
    Arvore *arvore = getArvoreAtual();
	QStandardItemModel *modelo = (QStandardItemModel*)arvore->model();
	QItemSelectionModel *selecao = (QItemSelectionModel*)arvore->selectionModel();

    if (selecao->hasSelection()) {
        Tabela *tabela = getTabelaAtual();
		QMessageBox::StandardButton res = Dialogo::confirma(frmPrincipal, "FrmPrincipal.ExcluirDiretorioSelecionado");
		if (res == QMessageBox::Yes) {
			frmPrincipal->setCursor(Qt::WaitCursor);
            QStringList sl = montaCaminho(arvore->currentIndex());
			QString caminho = sl.join(Rotinas::BARRA_INVERTIDA);

			DiretorioBO::getInstancia()->excluirDiretorio(getAbaAtual(), caminho);
            ExcluirDados(getAbaAtual(), caminho);

			modelo->removeRow(arvore->currentIndex().row());
			tabela->limpar();

            CarregarDados(pLog, false, false);

			frmPrincipal->setCursor(Qt::ArrowCursor);
        }
    }
}

void Catalogador::ImportarArquivo(IProgressoLog pLog) {
    int nResultado;

	QString arqSelecionado = EscolhaArquivo::abrirArquivo(frmPrincipal);
	if (!arqSelecionado.isEmpty()) {
		QFileInfo arquivo(arqSelecionado);

        if (arquivo.exists()) {
			frmPrincipal->setCursor(Qt::WaitCursor);
            nResultado = DiretorioBO::getInstancia()->importarDiretorioViaXML(
            getAbaAtual(), arquivo.path(), listaDiretorioPai, pLog);
            if (nResultado == -1) {
                Dialogo::mensagemErro(frmPrincipal,
                        "FrmPrincipal.ImportacaoNaoRealizada");
            } else if (nResultado == -2) {
                Dialogo::mensagemErro(frmPrincipal,
                        "FrmPrincipal.DiretorioExisteCatalogo");
            } else {
                FinalizaImportacao(pLog);
            }
			frmPrincipal->setCursor(Qt::ArrowCursor);
        }
    }
}

bool Catalogador::ImportarDiretorios(QStringList listaCaminho,
        bool bSubDiretorio, FrmImportarDiretorio *frmImportarDiretorio) {
    int nAba, nRotuloRaiz, nCodDirRaiz;
    RotuloRaiz *sRotuloRaiz = new RotuloRaiz();
    QString sCaminhoSemDrive;
    Importar importar;

    nAba = getAbaAtual().getCodigo();
    nCodDirRaiz = DiretorioBO::getInstancia()->retMaxCodDir(nAba,
            listaDiretorioPai);

    foreach (QString sCaminho, listaCaminho) {
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
                importar.setNomeDirRaiz(QString(""));
            }
            importar.setCaminho(sCaminho);

            frmImportarDiretorio->listaImportar.append(importar);
            nCodDirRaiz++;
        }
    }

    frmImportarDiretorio->bSubDiretorio = bSubDiretorio;

    if (bSubDiretorio) {
		frmImportarDiretorio->exec();
        return true;
    } else {
        if (!DiretorioBO::getInstancia()->verificaCodDir(
                importar.getAba(), importar.getRotuloRaiz(),
                listaDiretorioPai)) {
			frmImportarDiretorio->exec();
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

	frmPrincipal->setCursor(Qt::WaitCursor);

    CarregarDados(pLog, true, true);
    tvAba = getArvoreAtual();
    CarregarArvore(tvAba, getAbaAtual());

	frmPrincipal->setCursor(Qt::ArrowCursor);
    Dialogo::mensagemInfo(frmPrincipal, "FrmPrincipal.DirImportacaoSucesso");

}


void Catalogador::ComecaImportacao(bool bSubDiretorios, IProgressoLog pLog) {
    QString sCaminho;
    QStringList listaCaminho;

	QString dirSelecionado = EscolhaArquivo::abrirDiretorio(frmPrincipal);
	if (!dirSelecionado.isEmpty()) {
		QFileInfo diretorio(dirSelecionado);
		if (diretorio.exists()) {
			frmPrincipal->setCursor(Qt::WaitCursor);
			sCaminho = diretorio.absoluteFilePath();

            frmImportarDiretorio = new FrmImportarDiretorio();

            if (bSubDiretorios) {
                DiretorioBO::getInstancia()->
                        carregarSubDiretorios(sCaminho, listaCaminho);
            } else {
                listaCaminho.append(sCaminho);
            }

            if (ImportarDiretorios(listaCaminho, bSubDiretorios,
                    frmImportarDiretorio)) {
                FinalizaImportacao(pLog);
            }

			frmPrincipal->setCursor(Qt::ArrowCursor);
        }
    }

}


}
}
