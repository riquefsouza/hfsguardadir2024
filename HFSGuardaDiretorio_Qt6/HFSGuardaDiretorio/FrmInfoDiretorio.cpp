#include "FrmInfoDiretorio.h"
#include "qheaderview.h"
#include "ui_FrmInfoDiretorio.h"

#include <QStandardItemModel>
#include <QStandardItem>

FrmInfoDiretorio::FrmInfoDiretorio(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmInfoDiretorio)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags() & (~Qt::WindowContextHelpButtonHint));

    panelLegenda = new QGroupBox("Legenda dos Atributos");

    QGridLayout *gridLayout = new QGridLayout();
    labArquivoComum = new QLabel("[ARQ] - Arquivo comum");
    labArquivoOculto = new QLabel("[HID] - Arquivo Oculto");
    labArquivoSistema = new QLabel("[SYS] - Arquivo de Sistema");
    labLegendaDiretorio = new QLabel("[DIR] - Diretório");
    labVolumeID = new QLabel("[VOL] - Volume ID");
    labArquivoSomenteLeitura = new QLabel("[ROL] - Arquivo Somente Leitura");

    gridLayout->addWidget(labArquivoComum,0,0,1,1);
    gridLayout->addWidget(labArquivoOculto,1,0,1,1);
    gridLayout->addWidget(labArquivoSistema,2,0,1,1);
    gridLayout->addWidget(labLegendaDiretorio,0,1,1,1);
    gridLayout->addWidget(labVolumeID,1,1,1,1);
    gridLayout->addWidget(labArquivoSomenteLeitura,2,1,1,1);

    panelLegenda->setLayout(gridLayout);

    tabelaInfo = new QTableView();
    tabelaInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tabelaInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
    tabelaInfo->setSelectionMode(QAbstractItemView::SingleSelection);
    tabelaInfo->verticalHeader()->setVisible(false);
    tabelaInfo->verticalHeader()->sectionResizeMode(QHeaderView::Fixed);
    tabelaInfo->verticalHeader()->setDefaultSectionSize(18);

    modeloInfo = new QStandardItemModel(0,2,this);
    modeloInfo->setHorizontalHeaderItem(0, new QStandardItem(QString("Item")));
    modeloInfo->setHorizontalHeaderItem(1, new QStandardItem(QString("Descrição")));

    modeloInfo->setItem(0, 0, new QStandardItem("Aba:"));
    modeloInfo->setItem(1, 0, new QStandardItem("Nome:"));
    modeloInfo->setItem(2, 0, new QStandardItem("Tamanho:"));
    modeloInfo->setItem(3, 0, new QStandardItem("Tipo:"));
    modeloInfo->setItem(4, 0, new QStandardItem("Modificado:"));
    modeloInfo->setItem(5, 0, new QStandardItem("Atributos:"));
    modeloInfo->setItem(6, 0, new QStandardItem("Caminho:"));

    tabelaInfo->setModel(modeloInfo);
    tabelaInfo->setColumnWidth(0,80);
    tabelaInfo->setColumnWidth(1,220);

    QFont font = modeloInfo->item(0,0)->font();
    font.setBold(true);
    modeloInfo->item(0,0)->setFont(font);
    modeloInfo->item(1,0)->setFont(font);
    modeloInfo->item(2,0)->setFont(font);
    modeloInfo->item(3,0)->setFont(font);
    modeloInfo->item(4,0)->setFont(font);
    modeloInfo->item(5,0)->setFont(font);
    modeloInfo->item(6,0)->setFont(font);

    ui->vbox->addWidget(panelLegenda);
    ui->vbox->addWidget(tabelaInfo);
}

FrmInfoDiretorio::~FrmInfoDiretorio()
{
    delete ui;
}

void FrmInfoDiretorio::setDiretorio(Diretorio diretorio) {

	modeloInfo->setItem(0, 1, new QStandardItem(diretorio.getAba().getNome()));
	modeloInfo->setItem(1, 1, new QStandardItem(diretorio.getNome()));
	modeloInfo->setItem(2, 1, new QStandardItem(diretorio.getTamanhoFormatado()));
	modeloInfo->setItem(3, 1, new QStandardItem(diretorio.getTipo().getNome()));
	modeloInfo->setItem(4, 1, new QStandardItem(diretorio.getModificadoFormatado()));
	modeloInfo->setItem(5, 1, new QStandardItem(diretorio.getAtributos()));
	modeloInfo->setItem(6, 1, new QStandardItem(diretorio.getCaminho()));

	tabelaInfo->setColumnWidth(1, diretorio.getCaminho().length() * 7);
}
