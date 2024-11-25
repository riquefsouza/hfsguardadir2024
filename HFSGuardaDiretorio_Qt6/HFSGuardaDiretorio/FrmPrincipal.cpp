#include "FrmPrincipal.h"
#include "ui_FrmPrincipal.h"
#include "FrmSobre.h"
#include "FrmInfoDiretorio.h"
#include "FrmCadExtensao.h"
#include "FrmCompararDiretorio.h"
#include "hfsguardadir/comum/Rotinas.h"

#include <QStandardItemModel>
#include <QStandardItem>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QFileDialog>

#include <QDirIterator>
#include <QDebug>
#include <QtSql>

FrmPrincipal *frmPrincipal;

using namespace hfsguardadir::comum;

FrmPrincipal::FrmPrincipal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FrmPrincipal)
{
    ui->setupUi(this);

    //ui->statusBar->setStyleSheet("QStatusBar::item { border: 1px groove; } ");

	actionInformacoesDiretorioArquivo = new QAction(Rotinas::getRecurso("FrmPrincipal.menuInformacoesDiretorioArquivo"));
	actionExcluirDiretorioSelecionado = new QAction(Rotinas::getRecurso("FrmPrincipal.menuExcluirDiretorioSelecionado"));

    barraStatus1 = new QLabel("Quantidade Total:,Tamanho Total:");
    barraStatus1->setMinimumSize(300, barraStatus1->minimumHeight());

    barraStatus2 = new QLabel("");

    ui->statusbar->addWidget(barraStatus1);
    ui->statusbar->addWidget(barraStatus2, 1);

    panelCentral = new QWidget();
    panelTopo = new QWidget();

    btnImportarDiretorio = new QPushButton("Importar Diretório");
    pb = new QProgressBar();
    pb->setTextVisible(false);
    edtPesquisa = new QLineEdit();
    edtPesquisa->setMaxLength(255);
    edtPesquisa->setToolTip("Digite aqui para pesquisar");
    btnPesquisa = new QPushButton("Pesquisar");

    QHBoxLayout *hbox = new QHBoxLayout();
    //hbox->setMargin(0);
    hbox->addWidget(btnImportarDiretorio);
    hbox->addWidget(pb);
    hbox->addWidget(edtPesquisa);
    hbox->addWidget(btnPesquisa);

    panelTopo->setLayout(hbox);

    spPesquisa = new QSplitter(Qt::Vertical, parent);

    tabPanel = new QTabWidget(parent);
	tabPanel->setContextMenuPolicy(Qt::CustomContextMenu);
	
    tabelaPesquisa = new Tabela(parent, false);

    spPesquisa->addWidget(tabPanel);
    spPesquisa->addWidget(tabelaPesquisa);
    spPesquisa->setStretchFactor(0, 50);
    spPesquisa->widget(1)->setVisible(false);

    QVBoxLayout *vbox = new QVBoxLayout();
    //vbox->setMargin(0);
    vbox->addWidget(panelTopo);
    vbox->addWidget(spPesquisa);

    panelCentral->setLayout(vbox);

    setCentralWidget(panelCentral);
//connect(ui->menuNOVO, &QMenu::triggered, this, &MainWindow::MenuClicked);
    connect(ui->actionIncluirNovaAba, SIGNAL(triggered()), this, SLOT(actionIncluirNovaAbaTriggered()));
    connect(ui->actionAlterarNomeAbaAtiva, SIGNAL(triggered()), this, SLOT(actionAlterarNomeAbaAtivaTriggered()));
    connect(ui->actionExcluirAbaAtiva, SIGNAL(triggered()), this, SLOT(actionExcluirAbaAtivaTriggered()));
    connect(ui->actionImportarDiretorio, SIGNAL(triggered()), this, SLOT(actionImportarDiretorioTriggered()));
    connect(ui->actionImportarSubDiretorios, SIGNAL(triggered()), this, SLOT(actionImportarSubDiretoriosTriggered()));
    connect(ui->actionCompararDiretorios, SIGNAL(triggered()), this, SLOT(actionCompararDiretoriosTriggered()));
    connect(ui->actionCadastrarExtensaoArquivo, SIGNAL(triggered()),
            this, SLOT(actionCadastrarExtensaoArquivoTriggered()));
    connect(ui->actionExpandirDiretorios, SIGNAL(triggered()), this, SLOT(actionExpandirDiretoriosTriggered()));
    connect(ui->actionColapsarDiretorios, SIGNAL(triggered()), this, SLOT(actionColapsarDiretoriosTriggered()));
    connect(ui->actionTXT, SIGNAL(triggered()), this, SLOT(actionTXTTriggered()));
    connect(ui->actionCSV, SIGNAL(triggered()), this, SLOT(actionCSVTriggered()));
    connect(ui->actionHTML, SIGNAL(triggered()), this, SLOT(actionHTMLTriggered()));
    connect(ui->actionXML, SIGNAL(triggered()), this, SLOT(actionXMLTriggered()));
    connect(ui->actionSQL, SIGNAL(triggered()), this, SLOT(actionSQLTriggered()));
    connect(ui->actionImportarDiretoriosViaXML, SIGNAL(triggered()),
            this, SLOT(actionImportarDiretoriosViaXMLTriggered()));
    connect(ui->actionGravarLogImportacao, SIGNAL(triggered()), this, SLOT(actionGravarLogImportacaoTriggered()));
    connect(ui->actionMostrarOcultarArvoreDirAbaAtiva, SIGNAL(triggered()),
            this, SLOT(actionMostrarOcultarArvoreDirAbaAtivaTriggered()));
    connect(ui->actionMostrarOcultarListaItensPesquisados, SIGNAL(triggered()),
            this, SLOT(actionMostrarOcultarListaItensPesquisadosTriggered()));
    connect(ui->actionSobreCatalogador, SIGNAL(triggered()), this, SLOT(actionSobreCatalogadorTriggered()));

    connect(btnImportarDiretorio, SIGNAL( clicked() ),
            this, SLOT( btnImportarDiretorioClicked() ) );
    connect(btnPesquisa, SIGNAL( clicked() ),
            this, SLOT( btnPesquisaClicked() ) );
    connect(tabPanel, SIGNAL( tabBarClicked(int) ),
            this, SLOT( tabTabBarClicked(int) ) );

	connect(tabelaPesquisa, SIGNAL(clicked(QModelIndex)),
		this, SLOT(tabelaPesquisaClicked(QModelIndex)));

	connect(tabPanel, SIGNAL(customContextMenuRequested(const QPoint &)), 
		this, SLOT(contextMenu(const QPoint &)));
	
	connect(actionInformacoesDiretorioArquivo, SIGNAL(triggered()), 
		this, SLOT(actionInformacoesDiretorioArquivoTriggered()));
	connect(actionExcluirDiretorioSelecionado, SIGNAL(triggered()),
		this, SLOT(actionExcluirDiretorioSelecionadoTriggered()));

}

FrmPrincipal::~FrmPrincipal()
{
    disconnect(ui->actionIncluirNovaAba, SIGNAL(triggered()), this, SLOT(actionIncluirNovaAbaTriggered()));
    disconnect(ui->actionAlterarNomeAbaAtiva, SIGNAL(triggered()), this, SLOT(actionAlterarNomeAbaAtivaTriggered()));
    disconnect(ui->actionExcluirAbaAtiva, SIGNAL(triggered()), this, SLOT(actionExcluirAbaAtivaTriggered()));
    disconnect(ui->actionImportarDiretorio, SIGNAL(triggered()), this, SLOT(actionImportarDiretorioTriggered()));
    disconnect(ui->actionImportarSubDiretorios, SIGNAL(triggered()), this, SLOT(actionImportarSubDiretoriosTriggered()));
    disconnect(ui->actionCompararDiretorios, SIGNAL(triggered()), this, SLOT(actionCompararDiretoriosTriggered()));
    disconnect(ui->actionCadastrarExtensaoArquivo, SIGNAL(triggered()),
            this, SLOT(actionCadastrarExtensaoArquivoTriggered()));
    disconnect(ui->actionExpandirDiretorios, SIGNAL(triggered()), this, SLOT(actionExpandirDiretoriosTriggered()));
    disconnect(ui->actionColapsarDiretorios, SIGNAL(triggered()), this, SLOT(actionColapsarDiretoriosTriggered()));
    disconnect(ui->actionTXT, SIGNAL(triggered()), this, SLOT(actionTXTTriggered()));
    disconnect(ui->actionCSV, SIGNAL(triggered()), this, SLOT(actionCSVTriggered()));
    disconnect(ui->actionHTML, SIGNAL(triggered()), this, SLOT(actionHTMLTriggered()));
    disconnect(ui->actionXML, SIGNAL(triggered()), this, SLOT(actionXMLTriggered()));
    disconnect(ui->actionSQL, SIGNAL(triggered()), this, SLOT(actionSQLTriggered()));
    disconnect(ui->actionImportarDiretoriosViaXML, SIGNAL(triggered()),
            this, SLOT(actionImportarDiretoriosViaXMLTriggered()));
    disconnect(ui->actionGravarLogImportacao, SIGNAL(triggered()), this, SLOT(actionGravarLogImportacaoTriggered()));
    disconnect(ui->actionMostrarOcultarArvoreDirAbaAtiva, SIGNAL(triggered()),
            this, SLOT(actionMostrarOcultarArvoreDirAbaAtivaTriggered()));
    disconnect(ui->actionMostrarOcultarListaItensPesquisados, SIGNAL(triggered()),
            this, SLOT(actionMostrarOcultarListaItensPesquisadosTriggered()));
    disconnect(ui->actionSobreCatalogador, SIGNAL(triggered()), this, SLOT(actionSobreCatalogadorTriggered()));

    disconnect(btnImportarDiretorio, SIGNAL( clicked() ),
            this, SLOT( btnImportarDiretorioClicked() ) );
    disconnect(btnPesquisa, SIGNAL( clicked() ),
            this, SLOT( btnPesquisaClicked() ) );
    disconnect(tabPanel, SIGNAL( tabBarClicked(int) ),
            this, SLOT( tabTabBarClicked(int) ) );

	disconnect(tabelaPesquisa, SIGNAL(clicked(QModelIndex)),
		this, SLOT(tabelaPesquisaClicked(QModelIndex)));

	disconnect(tabPanel, SIGNAL(customContextMenuRequested(const QPoint &)), 
		this, SLOT(contextMenu(const QPoint &)));
	disconnect(actionInformacoesDiretorioArquivo, SIGNAL(triggered()),
		this, SLOT(actionInformacoesDiretorioArquivoTriggered()));
	disconnect(actionExcluirDiretorioSelecionado, SIGNAL(triggered()),
		this, SLOT(actionExcluirDiretorioSelecionadoTriggered()));

    delete ui;
}

void FrmPrincipal::ProgressoLog(Progresso progresso)
{
	if (frmPrincipal != NULL) {
		if (progresso.posicao == 0) {
			frmPrincipal->pb->setMinimum(progresso.minimo);
			frmPrincipal->pb->setMaximum(progresso.maximo);
		}

		frmPrincipal->pb->setValue(progresso.posicao);
	}

}

void FrmPrincipal::actionIncluirNovaAbaTriggered(){
	catalogador->IncluirNovaAba();
}

void FrmPrincipal::actionAlterarNomeAbaAtivaTriggered(){
	catalogador->AlterarNomeAbaAtiva(ProgressoLog);
}

void FrmPrincipal::actionExcluirAbaAtivaTriggered(){
	catalogador->ExcluirAbaAtiva(ProgressoLog);
}

void FrmPrincipal::actionImportarDiretorioTriggered(){
	catalogador->ComecaImportacao(false, ProgressoLog);
}

void FrmPrincipal::actionImportarSubDiretoriosTriggered(){
	catalogador->ComecaImportacao(true, ProgressoLog);
}

void FrmPrincipal::actionCompararDiretoriosTriggered(){
	frmCompararDiretorio = new FrmCompararDiretorio();
    frmCompararDiretorio->exec();
}

void FrmPrincipal::actionCadastrarExtensaoArquivoTriggered(){
    FrmCadExtensao frmCadExtensao;
    frmCadExtensao.exec();
}

void FrmPrincipal::actionExpandirDiretoriosTriggered(){
	catalogador->getArvoreAtual()->expandAll();
}

void FrmPrincipal::actionColapsarDiretoriosTriggered(){
	catalogador->getArvoreAtual()->collapseAll();
}

void FrmPrincipal::actionTXTTriggered(){
	catalogador->ExportarArquivo(teTXT, ProgressoLog);
}

void FrmPrincipal::actionCSVTriggered(){
	catalogador->ExportarArquivo(teCSV, ProgressoLog);
}

void FrmPrincipal::actionHTMLTriggered(){
	catalogador->ExportarArquivo(teHTML, ProgressoLog);
}

void FrmPrincipal::actionXMLTriggered(){
	catalogador->ExportarArquivo(teXML, ProgressoLog);
}

void FrmPrincipal::actionSQLTriggered(){
	catalogador->ExportarArquivo(teSQL, ProgressoLog);
}

void FrmPrincipal::actionImportarDiretoriosViaXMLTriggered(){
    //QStringList log;
    catalogador->ImportarArquivo(ProgressoLog);
}

void FrmPrincipal::actionGravarLogImportacaoTriggered(){
	catalogador->bGravarLogImportacao = ui->actionGravarLogImportacao->isChecked();
}

void FrmPrincipal::actionMostrarOcultarArvoreDirAbaAtivaTriggered(){
	QSplitter *sp = catalogador->getSplitAtual();
    sp->widget(0)->setVisible(!sp->widget(0)->isVisible());
}

void FrmPrincipal::actionMostrarOcultarListaItensPesquisadosTriggered(){
    spPesquisa->widget(1)->setVisible(!spPesquisa->widget(1)->isVisible());
}

void FrmPrincipal::actionSobreCatalogadorTriggered(){
    FrmSobre frmSobre;
    frmSobre.exec();
}

void FrmPrincipal::btnImportarDiretorioClicked(){
	catalogador->ComecaImportacao(false, ProgressoLog);
}

void FrmPrincipal::btnPesquisaClicked(){
	catalogador->Pesquisar();
}

void FrmPrincipal::tabTabBarClicked(){
	catalogador->tabPanelMudou();
}

void FrmPrincipal::tabelaPesquisaClicked(const QModelIndex & mi) {
	QStandardItemModel *modelo = (QStandardItemModel*)mi.model();
	QString nome = modelo->item(mi.row(), 0)->text();
	QString nomeAba = modelo->item(mi.row(), 6)->text();
	QString caminho = modelo->item(mi.row(), 5)->text();
	catalogador->EncontrarItemLista(nomeAba, nome, caminho);
}

void FrmPrincipal::arvorePressed(const QModelIndex & mi) {
	catalogador->arvoreValorMudou(mi);
}

void FrmPrincipal::arvoreExpanded(const QModelIndex & mi) {
	QStandardItemModel *modelo = (QStandardItemModel*)mi.model();
	QStandardItem *item = modelo->itemFromIndex(mi);
	item->setIcon(Rotinas::getInstancia()->dirabertoIcone);
}

void FrmPrincipal::arvoreCollapsed(const QModelIndex & mi) {
	QStandardItemModel *modelo = (QStandardItemModel*)mi.model();
	QStandardItem *item = modelo->itemFromIndex(mi);
	item->setIcon(Rotinas::getInstancia()->diretorioIcone);
}

void FrmPrincipal::tabelaDoubleClicked(const QModelIndex & mi) {
	QStandardItemModel *modelo = (QStandardItemModel*)mi.model();
	QString nome = modelo->item(mi.row(), 0)->text();
	QString tipo = modelo->item(mi.row(), 2)->text();
	catalogador->DuploCliqueLista(nome, tipo);
}

void FrmPrincipal::contextMenu(const QPoint &pos) {
	QMenu *menu = new QMenu;
	menu->addAction(actionInformacoesDiretorioArquivo);
	menu->addAction(actionExcluirDiretorioSelecionado);
	menu->addAction(ui->actionExpandirDiretorios);
	menu->addAction(ui->actionColapsarDiretorios);
	menu->addSeparator();
	menu->addAction(ui->actionIncluirNovaAba);
	menu->addAction(ui->actionAlterarNomeAbaAtiva);
	menu->addAction(ui->actionExcluirAbaAtiva);
	menu->exec(tabPanel->mapToGlobal(pos));
}

void FrmPrincipal::actionInformacoesDiretorioArquivoTriggered() {
	FrmInfoDiretorio *frmInfo;

	Tabela *tabela = catalogador->getTabelaAtual();
	QItemSelectionModel *selecao = tabela->selectionModel();

	if (selecao->hasSelection()) {
		frmInfo = new FrmInfoDiretorio(this);
		Aba aba = catalogador->getAbaAtual();
		Diretorio *dir = tabela->getLinhaSelecionada();
		dir->setAba(aba);
		frmInfo->setDiretorio(*dir);
		frmInfo->exec();
	}
}

void FrmPrincipal::actionExcluirDiretorioSelecionadoTriggered() {
	catalogador->ExcluirDiretorioSelecionado(ProgressoLog);
}
