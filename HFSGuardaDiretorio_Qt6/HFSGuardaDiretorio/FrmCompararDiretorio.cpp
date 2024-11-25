#include "FrmCompararDiretorio.h"
#include "ui_FrmCompararDiretorio.h"

#include <QStandardItemModel>
#include <QStandardItem>
#include <QMessageBox>
#include <QVBoxLayout>

#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/objetosgui/Dialogo.h"
#include "hfsguardadir/catalogador/Catalogador.h"
#include "hfsguardadir/objetosbo/AbaBO.h"
#include "hfsguardadir/objetosbo/DiretorioBO.h"

using namespace hfsguardadir::comum;
using namespace hfsguardadir::objetosgui;
using namespace hfsguardadir::objetosbo;
using namespace hfsguardadir::catalogador;

FrmCompararDiretorio *frmCompararDiretorio;

FrmCompararDiretorio::FrmCompararDiretorio(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmCompararDiretorio)
{
    ui->setupUi(this);

    setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    setMinimumSize(688,572);
    setMaximumSize(minimumSize());
    setWindowFlags(windowFlags() & (~Qt::WindowContextHelpButtonHint));

    QVBoxLayout *vbox = new QVBoxLayout();

    panelCentral = new QWidget();
    panelTopo = new QWidget();

    btnCompararDiretorios = new QPushButton("Comparar Diretórios");
    pb = new QProgressBar();
    pb->setTextVisible(false);
    btnSalvarLog = new QPushButton("Salvar Log");

    QHBoxLayout *hbox = new QHBoxLayout();
    //hbox->setMargin(0);
    hbox->addWidget(btnCompararDiretorios);
    hbox->addWidget(pb);
    hbox->addWidget(btnSalvarLog);

    panelTopo->setLayout(hbox);

    QHBoxLayout *hbox2 = new QHBoxLayout();
    //hbox2->setMargin(0);

    panelDiretorio1 = new QGroupBox("Diretório 1");
    QVBoxLayout *vboxDir1 = new QVBoxLayout();
    cmbAba1 = new QComboBox();

    arvoreDiretorio1 = new Arvore(this);
    
    vboxDir1->addWidget(cmbAba1);
    vboxDir1->addWidget(arvoreDiretorio1);
    panelDiretorio1->setLayout(vboxDir1);

    panelDiretorio2 = new QGroupBox("Diretório 2");
    QVBoxLayout *vboxDir2 = new QVBoxLayout();
    cmbAba2 = new QComboBox();
    
	arvoreDiretorio2 = new Arvore(this);

    vboxDir2->addWidget(cmbAba2);
    vboxDir2->addWidget(arvoreDiretorio2);
    panelDiretorio2->setLayout(vboxDir2);

    hbox2->addWidget(panelDiretorio1);
    hbox2->addWidget(panelDiretorio2);
    panelCentral->setLayout(hbox2);

    labDiferencasEncontradas = new QLabel("Diferenças Encontradas");

    tabelaComparador = new Tabela(this, true);

    barraStatus1 = new QLabel("Total de diferenças encontradas:");
    barraStatus1->setMinimumSize(200, barraStatus1->minimumHeight());

    barraStatus2 = new QLabel("");

    barraStatus = new QStatusBar();
    barraStatus->setSizeGripEnabled(false);
    barraStatus->addWidget(barraStatus1);
    barraStatus->addWidget(barraStatus2, 1);

    //vbox->setMargin(0);
    vbox->addWidget(panelTopo);
    vbox->addWidget(panelCentral);
    vbox->addWidget(labDiferencasEncontradas);
    vbox->addWidget(tabelaComparador);
    vbox->addWidget(barraStatus);

    setLayout(vbox);

	montarArvores();
	LimparComparacao();

    connect(btnCompararDiretorios, SIGNAL( clicked() ),
            this, SLOT( btnCompararDiretoriosClicked() ) );
    connect(btnSalvarLog, SIGNAL( clicked() ),
            this, SLOT( btnSalvarLogClicked() ) );

    connect( cmbAba1, SIGNAL( currentTextChanged(QString) ),
             this, SLOT( cmbAba1CurrentTextChanged(QString) ) );
    connect( cmbAba2, SIGNAL( currentTextChanged(QString) ),
             this, SLOT( cmbAba2CurrentTextChanged(QString) ) );

    connect( arvoreDiretorio1, SIGNAL( expanded(QModelIndex) ),
             this, SLOT( arvoreDiretorio1Expanded(QModelIndex) ) );
    connect( arvoreDiretorio1, SIGNAL( collapsed(QModelIndex) ),
             this, SLOT( arvoreDiretorio1Collapsed(QModelIndex) ) );

    connect( arvoreDiretorio2, SIGNAL( expanded(QModelIndex) ),
             this, SLOT( arvoreDiretorio2Expanded(QModelIndex) ) );
    connect( arvoreDiretorio2, SIGNAL( collapsed(QModelIndex) ),
             this, SLOT( arvoreDiretorio2Collapsed(QModelIndex) ) );

}

FrmCompararDiretorio::~FrmCompararDiretorio()
{
    disconnect(btnCompararDiretorios, SIGNAL( clicked() ),
            this, SLOT( btnCompararDiretoriosClicked() ) );
    disconnect(btnSalvarLog, SIGNAL( clicked() ),
            this, SLOT( btnSalvarLogClicked() ) );

    disconnect( cmbAba1, SIGNAL( currentTextChanged(QString) ),
             this, SLOT( cmbAba1CurrentTextChanged(QString) ) );
    disconnect( cmbAba2, SIGNAL( currentTextChanged(QString) ),
             this, SLOT( cmbAba2CurrentTextChanged(QString) ) );

    disconnect( arvoreDiretorio1, SIGNAL( expanded(QModelIndex) ),
             this, SLOT( arvoreDiretorio1Expanded(QModelIndex) ) );
    disconnect( arvoreDiretorio1, SIGNAL( collapsed(QModelIndex) ),
             this, SLOT( arvoreDiretorio1Collapsed(QModelIndex) ) );

    disconnect( arvoreDiretorio2, SIGNAL( expanded(QModelIndex) ),
             this, SLOT( arvoreDiretorio2Expanded(QModelIndex) ) );
    disconnect( arvoreDiretorio2, SIGNAL( collapsed(QModelIndex) ),
             this, SLOT( arvoreDiretorio2Collapsed(QModelIndex) ) );

    delete ui;
}

void FrmCompararDiretorio::btnCompararDiretoriosClicked(){
	QString sCaminhoDir1 = "", sCaminhoDir2 = "";
	bool bSelecionado;

	bSelecionado = false;
	if (arvoreDiretorio1->isSelecionado()) {
		catalogador->LerArvoreDiretorio(arvoreDiretorio1->currentIndex(),
			barraStatus2);
		sCaminhoDir1 = barraStatus2->text();

		if (arvoreDiretorio2->isSelecionado()) {
			catalogador->LerArvoreDiretorio(
				arvoreDiretorio2->currentIndex(), barraStatus2);
			sCaminhoDir2 = barraStatus2->text();
			bSelecionado = true;
		}
	}

	LimparComparacao();

	if (bSelecionado) {
		Comparar(sCaminhoDir1, sCaminhoDir2);
	}
	else {
		Dialogo::mensagemInfo(this,
			"FrmCompararDiretorio.DiretoriosNaoSelecionados");
	}
}

void FrmCompararDiretorio::btnSalvarLogClicked(){
	QString sLog;
	QStringList listaLocal;

	if (listaCompara.size() > 0) {
		sLog = qApp->applicationDirPath() + Rotinas::BARRA_INVERTIDA
			+ Rotinas::formataDate(Rotinas::FORMATO_DHARQUIVO, QDateTime())
			+ "_Comparacao.log";

		foreach (Diretorio diretorio, listaCompara) {
			listaLocal.append(diretorio.getCaminho());
		}

		Rotinas::SListSaveToFile(listaLocal, sLog);

		Dialogo::mensagemInfo(this,
			"FrmCompararDiretorio.LogSalvoMemoDirSistema");
	}
}

void FrmCompararDiretorio::cmbAba1CurrentTextChanged(){
	Aba *aba;

	setCursor(Qt::WaitCursor);
	
	arvoreDiretorio1->limpar();
	aba = AbaBO::getInstancia()->pegaAbaPorOrdem(catalogador->listaAbas,
		cmbAba1->currentIndex() + 1);
	catalogador->CarregarArvore(arvoreDiretorio1, *aba);
	arvoreDiretorio1->selecioneLinha(0);
	LimparComparacao();

	setCursor(Qt::ArrowCursor);
}

void FrmCompararDiretorio::cmbAba2CurrentTextChanged(){
	Aba *aba;

	setCursor(Qt::WaitCursor);

	arvoreDiretorio2->limpar();
	aba = AbaBO::getInstancia()->pegaAbaPorOrdem(catalogador->listaAbas,
		cmbAba2->currentIndex() + 1);
	catalogador->CarregarArvore(arvoreDiretorio2, *aba);
	arvoreDiretorio2->selecioneLinha(0);
	LimparComparacao();

	setCursor(Qt::ArrowCursor);
}

void FrmCompararDiretorio::montarArvores()
{
	Aba *aba1;

	foreach (Aba aba, catalogador->listaAbas) {
		cmbAba1->addItem(aba.getNome());
		cmbAba2->addItem(aba.getNome());
	}
	cmbAba1->setCurrentIndex(0);
	cmbAba2->setCurrentIndex(0);

	aba1 = AbaBO::getInstancia()->pegaAbaPorOrdem(catalogador->listaAbas,
		cmbAba1->currentIndex() + 1);
	catalogador->CarregarArvore(arvoreDiretorio1, *aba1);

	aba1 = AbaBO::getInstancia()->pegaAbaPorOrdem(catalogador->listaAbas,
		cmbAba2->currentIndex() + 1);
	catalogador->CarregarArvore(arvoreDiretorio2, *aba1);
}

void FrmCompararDiretorio::arvoreDiretorio1Expanded(const QModelIndex & mi){
	QStandardItemModel *modelo = (QStandardItemModel*)mi.model();
	QStandardItem *item = modelo->itemFromIndex(mi);
	item->setIcon(Rotinas::getInstancia()->dirabertoIcone);
}

void FrmCompararDiretorio::arvoreDiretorio1Collapsed(const QModelIndex & mi){
	QStandardItemModel *modelo = (QStandardItemModel*)mi.model();
	QStandardItem *item = modelo->itemFromIndex(mi);
	item->setIcon(Rotinas::getInstancia()->diretorioIcone);
}

void FrmCompararDiretorio::arvoreDiretorio2Expanded(const QModelIndex & mi){
	QStandardItemModel *modelo = (QStandardItemModel*)mi.model();
	QStandardItem *item = modelo->itemFromIndex(mi);
	item->setIcon(Rotinas::getInstancia()->dirabertoIcone);
}

void FrmCompararDiretorio::arvoreDiretorio2Collapsed(const QModelIndex & mi){
	QStandardItemModel *modelo = (QStandardItemModel*)mi.model();
	QStandardItem *item = modelo->itemFromIndex(mi);
	item->setIcon(Rotinas::getInstancia()->diretorioIcone);
}

void FrmCompararDiretorio::LimparComparacao() {
	pb->setValue(0);
	tabelaComparador->limpar();
	tabelaComparador->selecioneLinha(0);
	//tabelaCompara.setSombrearLinhas(true);
	
	btnSalvarLog->setEnabled(false);
	barraStatus2->setText("");
}

QString FrmCompararDiretorio::SQLCompara(Aba aba1, Aba aba2, const QString &caminho1,
	const QString &caminho2) {
	QString sSQL;

    sSQL = DiretorioBO::SQL_CONSULTA_ARQUIVO + " WHERE aba=" + QString::number(aba1.getCodigo())
		+ " AND caminho LIKE " + Rotinas::QuotedStr(caminho1 + "%")
		+ " AND nome NOT IN (SELECT nome FROM Diretorios "
        + " WHERE aba=" + QString::number(aba2.getCodigo()) + " AND caminho LIKE "
		+ Rotinas::QuotedStr(caminho2 + "%") + ")" + " ORDER BY 1, 2, 3";
	return sSQL;
}

void FrmCompararDiretorio::Comparar(const QString &sCaminhoDir1, const QString &sCaminhoDir2)
{
	QString sSQL;
	Aba *aba1, *aba2;
	int tamLista;

	aba1 = AbaBO::getInstancia()->pegaAbaPorOrdem(catalogador->listaAbas,
		cmbAba1->currentIndex() + 1);
	aba2 = AbaBO::getInstancia()->pegaAbaPorOrdem(catalogador->listaAbas,
		cmbAba2->currentIndex() + 1);

	sSQL = SQLCompara(*aba1, *aba2, sCaminhoDir1, sCaminhoDir2);
	listaCompara = DiretorioBO::getInstancia()->carregarDiretorio(sSQL,
		"consultaarquivo", ProgressoLog);

	if (listaCompara.size() > 0) {
		tabelaComparador->modeloTabela(listaCompara, catalogador->listaExtensoes, pb);
		tabelaComparador->selecioneLinha(0);
		//tabelaCompara.setSombrearLinhas(true);

		tamLista = listaCompara.size();
		barraStatus2->setText(QString::number(tamLista));
		btnSalvarLog->setEnabled(true);
	}
	else {
		Dialogo::mensagemInfo(this,
			"FrmCompararDiretorio.NenhumaDiferencaEncontrada");
	}
}

void FrmCompararDiretorio::ProgressoLog(Progresso progresso)
{
	if (frmCompararDiretorio != NULL) {
		if (progresso.posicao == 0) {
			frmCompararDiretorio->pb->setMinimum(progresso.minimo);
			frmCompararDiretorio->pb->setMaximum(progresso.maximo);
		}

		frmCompararDiretorio->pb->setValue(progresso.posicao);
	}

}
