#include "FrmCadExtensao.h"
#include "qheaderview.h"
#include "ui_FrmCadExtensao.h"

#include <QList>
#include <QMessageBox>
#include <QStandardItem>

#include "hfsguardadir/objetos/Extensao.h"
#include "hfsguardadir/objetosbo/ExtensaoBO.h"
#include "hfsguardadir/catalogador/Catalogador.h"
#include "hfsguardadir/objetosgui/EscolhaArquivo.h"
#include "hfsguardadir/objetosgui/Dialogo.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::objetosbo;
using namespace hfsguardadir::objetosgui;
using namespace hfsguardadir::catalogador;

FrmCadExtensao::FrmCadExtensao(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmCadExtensao)
{
    ui->setupUi(this);

    setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    setMinimumSize(289,300);
    setMaximumSize(minimumSize());
    setWindowFlags(windowFlags() & (~Qt::WindowContextHelpButtonHint));

    barraMenu = new QMenuBar();
    menuExtensao = new QMenu("Extensão");

    actionIncluirExtensao = new QAction("Incluir Extensão", this);
    menuExtensao->addAction(actionIncluirExtensao);

    actionExcluirExtensao = new QAction("Excluir Extensão", this);
    menuExtensao->addAction(actionExcluirExtensao);

    actionExcluirTodasExtensoes = new QAction("Excluir Todas Extensões", this);
    menuExtensao->addAction(actionExcluirTodasExtensoes);

    barraMenu->addMenu(menuExtensao);

    menuExportarTodos = new QMenu("Exportar Todos");

    actionExportarBitmap = new QAction("Exportar para Bitmap", this);
    menuExportarTodos->addAction(actionExportarBitmap);

    actionExportarIcone = new QAction("Exportar para Ícone", this);
    menuExportarTodos->addAction(actionExportarIcone);

    actionExportarGIF = new QAction("Exportar para GIF", this);
    menuExportarTodos->addAction(actionExportarGIF);

    actionExportarJPEG = new QAction("Exportar para JPEG", this);
    menuExportarTodos->addAction(actionExportarJPEG);

    actionExportarPNG = new QAction("Exportar para PNG", this);
    menuExportarTodos->addAction(actionExportarPNG);

    actionExportarTIFF = new QAction("Exportar para TIFF", this);
    menuExportarTodos->addAction(actionExportarTIFF);

    barraMenu->addMenu(menuExportarTodos);

    menuImportarTodos = new QMenu("Importar Todos");

    actionImportarIconesArquivos = new QAction("Importar Ícones dos Arquivos", this);
    menuImportarTodos->addAction(actionImportarIconesArquivos);

    actionExtrairIconesArquivos = new QAction("Extrair Ícones dos Arquivos", this);
    menuImportarTodos->addAction(actionExtrairIconesArquivos);

    barraMenu->addMenu(menuImportarTodos);

    ui->vbox->setMenuBar(barraMenu);

    tabelaExtensao = new QTableView();
    tabelaExtensao->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tabelaExtensao->setSelectionBehavior(QAbstractItemView::SelectRows);
    tabelaExtensao->setSelectionMode(QAbstractItemView::SingleSelection);
    tabelaExtensao->verticalHeader()->setVisible(false);
    tabelaExtensao->verticalHeader()->sectionResizeMode(QHeaderView::Fixed);
    tabelaExtensao->verticalHeader()->setDefaultSectionSize(18);

	modeloColunas(true);

    ui->vbox->addWidget(tabelaExtensao);

    QList<QAbstractButton*> botoes = ui->buttonBox->buttons();
    botoes.at(0)->setText("Incluir");
    botoes.at(1)->setText("Excluir");

    connect(actionIncluirExtensao, SIGNAL(triggered()), this, SLOT(actionIncluirExtensaoTriggered()));
    connect(actionExcluirExtensao, SIGNAL(triggered()), this, SLOT(actionExcluirExtensaoTriggered()));
    connect(actionExcluirTodasExtensoes, SIGNAL(triggered()), this, SLOT(actionExcluirTodasExtensoesTriggered()));
    connect(actionExportarBitmap, SIGNAL(triggered()), this, SLOT(actionExportarBitmapTriggered()));
    connect(actionExportarIcone, SIGNAL(triggered()), this, SLOT(actionExportarIconeTriggered()));
    connect(actionExportarGIF, SIGNAL(triggered()), this, SLOT(actionExportarGIFTriggered()));
    connect(actionExportarJPEG, SIGNAL(triggered()), this, SLOT(actionExportarJPEGTriggered()));
    connect(actionExportarPNG, SIGNAL(triggered()), this, SLOT(actionExportarPNGTriggered()));
    connect(actionExportarTIFF, SIGNAL(triggered()), this, SLOT(actionExportarTIFFTriggered()));
    connect(actionImportarIconesArquivos, SIGNAL(triggered()), this, SLOT(actionImportarIconesArquivosTriggered()));
    connect(actionExtrairIconesArquivos, SIGNAL(triggered()), this, SLOT(actionExtrairIconesArquivosTriggered()));

    //connect( tabelaExtensao, SIGNAL( doubleClicked(QModelIndex) ),
      //       this, SLOT( tabelaExtensaoDoubleClicked(QModelIndex) ) );
    connect( ui->buttonBox, SIGNAL( clicked(QAbstractButton*) ),
             this, SLOT( grupoBotaoClicked(QAbstractButton*) ) );

	CarregarExtensoesNaGrid();
}

FrmCadExtensao::~FrmCadExtensao()
{
    disconnect(actionIncluirExtensao, SIGNAL(triggered()), this, SLOT(actionIncluirExtensaoTriggered()));
    disconnect(actionExcluirExtensao, SIGNAL(triggered()), this, SLOT(actionExcluirExtensaoTriggered()));
    disconnect(actionExcluirTodasExtensoes, SIGNAL(triggered()), this, SLOT(actionExcluirTodasExtensoesTriggered()));
    disconnect(actionExportarBitmap, SIGNAL(triggered()), this, SLOT(actionExportarBitmapTriggered()));
    disconnect(actionExportarIcone, SIGNAL(triggered()), this, SLOT(actionExportarIconeTriggered()));
    disconnect(actionExportarGIF, SIGNAL(triggered()), this, SLOT(actionExportarGIFTriggered()));
    disconnect(actionExportarJPEG, SIGNAL(triggered()), this, SLOT(actionExportarJPEGTriggered()));
    disconnect(actionExportarPNG, SIGNAL(triggered()), this, SLOT(actionExportarPNGTriggered()));
    disconnect(actionExportarTIFF, SIGNAL(triggered()), this, SLOT(actionExportarTIFFTriggered()));
    disconnect(actionImportarIconesArquivos, SIGNAL(triggered()), this, SLOT(actionImportarIconesArquivosTriggered()));
    disconnect(actionExtrairIconesArquivos, SIGNAL(triggered()), this, SLOT(actionExtrairIconesArquivosTriggered()));

    //disconnect( tabelaExtensao, SIGNAL( doubleClicked(QModelIndex) ),
      //       this, SLOT( tabelaExtensaoDoubleClicked(QModelIndex) ) );
    disconnect( ui->buttonBox, SIGNAL( clicked(QAbstractButton*) ),
             this, SLOT( grupoBotaoClicked(QAbstractButton*) ) );

    delete ui;
}

void FrmCadExtensao::actionIncluirExtensaoTriggered(){
	QStringList log;

	QString arqSelecionado = EscolhaArquivo::abrirArquivo(this);
	if (!arqSelecionado.isEmpty()) {
		QFileInfo arquivo(arqSelecionado);

		if (arquivo.exists()) {
			if (ExtensaoBO::getInstancia()->SalvarExtensao(
                catalogador->listaExtensoes, arquivo.fileName(), log)) {

				CarregarExtensoesNaGrid();

				Dialogo::mensagemInfo(this,
					"FrmCadExtensao.ExtensaoSalvaSucesso");
			}
			else {
				Dialogo::mensagemInfo(this,
					"FrmCadExtensao.ExtensaoJaCadastrada");
			}
		}
	}
	
}

void FrmCadExtensao::actionExcluirExtensaoTriggered(){
	Extensao *extensao;

	if (catalogador->listaExtensoes.size() > 0) {
		QMessageBox::StandardButton res = Dialogo::confirma(this, "FrmCadExtensao.ExtensaoCertezaExcluir");
		if (res == QMessageBox::Yes) {
			extensao = ExtensaoBO::getInstancia()->pegaExtensaoPorOrdem(
				catalogador->listaExtensoes, tabelaExtensao->currentIndex().row() + 1);

			if (ExtensaoBO::getInstancia()->excluirExtensao(
				catalogador->listaExtensoes, extensao->getCodigo())) {
				CarregarExtensoesNaGrid();
				Dialogo::mensagemInfo(this,
					"FrmCadExtensao.ExtensaoExcluidaSucesso");
			}
		}
	}

}

void FrmCadExtensao::actionExcluirTodasExtensoesTriggered(){
	if (catalogador->listaExtensoes.size() > 0) {
		QMessageBox::StandardButton res = Dialogo::confirma(this, "FrmCadExtensao.ExtensaoCertezaTodosExcluir");
		if (res == QMessageBox::Yes) {
			if (ExtensaoBO::getInstancia()->excluirTodasExtensoes(
				catalogador->listaExtensoes)) {
				CarregarExtensoesNaGrid();
				Dialogo::mensagemInfo(this,
					"FrmCadExtensao.ExtensoesExcluidasSucesso");
			}
		}
	}
}

void FrmCadExtensao::actionExportarBitmapTriggered(){
	if (ExtensaoBO::getInstancia()->ExportarExtensao(teBMP,
		catalogador->listaExtensoes)) {
		Dialogo::mensagemInfo(this, "FrmCadExtensao.ExportarExtensao");
	}
}

void FrmCadExtensao::actionExportarIconeTriggered(){
	if (ExtensaoBO::getInstancia()->ExportarExtensao(teICO,
		catalogador->listaExtensoes)) {
		Dialogo::mensagemInfo(this, "FrmCadExtensao.ExportarExtensao");
	}
}
void FrmCadExtensao::actionExportarGIFTriggered(){
	if (ExtensaoBO::getInstancia()->ExportarExtensao(teGIF,
		catalogador->listaExtensoes)) {
		Dialogo::mensagemInfo(this, "FrmCadExtensao.ExportarExtensao");
	}
}

void FrmCadExtensao::actionExportarJPEGTriggered(){
	if (ExtensaoBO::getInstancia()->ExportarExtensao(teJPG,
		catalogador->listaExtensoes)) {
		Dialogo::mensagemInfo(this, "FrmCadExtensao.ExportarExtensao");
	}
}

void FrmCadExtensao::actionExportarPNGTriggered(){
	if (ExtensaoBO::getInstancia()->ExportarExtensao(tePNG,
		catalogador->listaExtensoes)) {
		Dialogo::mensagemInfo(this, "FrmCadExtensao.ExportarExtensao");
	}
}

void FrmCadExtensao::actionExportarTIFFTriggered(){
	if (ExtensaoBO::getInstancia()->ExportarExtensao(teTIF,
		catalogador->listaExtensoes)) {
		Dialogo::mensagemInfo(this, "FrmCadExtensao.ExportarExtensao");
	}
}

void FrmCadExtensao::actionImportarIconesArquivosTriggered(){
	QString sCaminho;

	QString dirSelecionado = EscolhaArquivo::abrirDiretorio(this);
	if (!dirSelecionado.isEmpty()) {
		QFileInfo diretorio(dirSelecionado);
		if (diretorio.exists()) {
			sCaminho = diretorio.absoluteFilePath();

			ExtensaoBO::getInstancia()->ImportarExtensao(sCaminho,
				catalogador->listaExtensoes);
			CarregarExtensoesNaGrid();
		}
	}
}

void FrmCadExtensao::actionExtrairIconesArquivosTriggered(){
	QString sCaminho;
	QString dirSelecionado = EscolhaArquivo::abrirDiretorio(this);
	if (!dirSelecionado.isEmpty()) {
		QFileInfo diretorio(dirSelecionado);
		if (diretorio.exists()) {
			sCaminho = diretorio.absoluteFilePath();

			ExtensaoBO::getInstancia()->ExtrairExtensao(sCaminho,
				catalogador->listaExtensoes);
			CarregarExtensoesNaGrid();
		}
	}
}

/*
void FrmCadExtensao::tabelaExtensaoDoubleClicked(const QModelIndex & mi){

}
*/

void FrmCadExtensao::grupoBotaoClicked(QAbstractButton* botao){
	if (botao->text()=="Incluir"){
		actionIncluirExtensaoTriggered();
    } else {
		actionExcluirExtensaoTriggered();
    }
}

void FrmCadExtensao::modeloColunas(bool bConstruir) {
	if (bConstruir) {
		modeloExtensao = new QStandardItemModel(0, 2, this);
	}

	modeloExtensao->setHorizontalHeaderItem(0, new QStandardItem(QString("Extensão")));
	modeloExtensao->setHorizontalHeaderItem(1, new QStandardItem(QString("Ícone")));

	tabelaExtensao->setModel(modeloExtensao);
	tabelaExtensao->setColumnWidth(0, 130);
	tabelaExtensao->setColumnWidth(1, 130);
}

void FrmCadExtensao::CarregarExtensoesNaGrid() {
	QList<QStandardItem *> colunas;
	QPixmap pixmap;

	modeloExtensao->clear();
	modeloColunas(false);

	foreach (Extensao extensao, catalogador->listaExtensoes) {
		colunas.append(new QStandardItem(extensao.getNome()));

		pixmap = Rotinas::QByteArrayToQPixmap(extensao.getBmp16(), Rotinas::EXTENSAO_BMP);

		colunas.append(new QStandardItem(QIcon(pixmap),""));

		modeloExtensao->appendRow(colunas);

		colunas.clear();
	}

}
