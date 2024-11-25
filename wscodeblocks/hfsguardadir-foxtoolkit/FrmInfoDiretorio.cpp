#include "resource.h"
#include "FrmInfoDiretorio.h"
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::comum;

FrmInfoDiretorio *frmInfoDiretorio = (FrmInfoDiretorio *) NULL;

FXDEFMAP(FrmInfoDiretorio) FrmInfoDiretorioMap[]={
  FXMAPFUNC(SEL_CLICKED, FrmInfoDiretorio::BTN_OK, FrmInfoDiretorio::on_btnOk_clicked)
};
FXIMPLEMENT(FrmInfoDiretorio, FXDialogBox,FrmInfoDiretorioMap,ARRAYNUMBER(FrmInfoDiretorioMap))


FrmInfoDiretorio::FrmInfoDiretorio(FXWindow* owner):
	FXDialogBox(owner, "Informações do Diretório / Arquivo", DECOR_TITLE | DECOR_CLOSE,
	  0, 0, 385, 329, 0, 0, 0, 0, 0, 0) {

	FXVerticalFrame *frame = new FXVerticalFrame(this, LAYOUT_FILL_X | LAYOUT_FILL_Y);

	grupo = new FXGroupBox(frame, "Legenda dos Atributos",
		GROUPBOX_TITLE_LEFT | FRAME_RIDGE | LAYOUT_FILL_X);
	
	matrix = new FXMatrix(grupo, 3);

	labArquivoComum = new FXLabel(matrix, "[ARQ] - Arquivo comum", NULL, LAYOUT_CENTER_X);
	labArquivoOculto = new FXLabel(matrix, "[HID] - Arquivo Oculto");
	labArquivoSistema = new FXLabel(matrix, "[SYS] - Arquivo de Sistema");
	labLegendaDiretorio = new FXLabel(matrix, "[DIR] - Diretório");
	labVolumeID = new FXLabel(matrix, "[VOL] - Volume ID");
	labArquivoSomenteLeitura = new FXLabel(matrix, "[ROL] - Arquivo Somente Leitura");

	tabelaInfo = new FXTable(frame, this, TABELA_INFO, LAYOUT_FILL_X | LAYOUT_FILL_Y);
	tabelaInfo->setTableSize(7, 2);
	tabelaInfo->setColumnText(0, "Item");
	tabelaInfo->setColumnText(1, "Descrição");
	//tabelaInfo->setColumnWidth(1, 180);

	FXHorizontalFrame *frameBotoes = new FXHorizontalFrame(frame,
		LAYOUT_SIDE_BOTTOM | LAYOUT_FILL_X);

	btnOk = new FXButton(frameBotoes, "&Ok", 0, this, FXDialogBox::ID_CANCEL,
		LAYOUT_CENTER_X | FRAME_RAISED | FRAME_THICK, 0, 0, 0, 0, 30, 30);

}

void FrmInfoDiretorio::create(){
	FXDialogBox::create();
}

FrmInfoDiretorio::~FrmInfoDiretorio(){
}

void FrmInfoDiretorio::Mostrar(FXWindow* owner)
{
	frmInfoDiretorio = new FrmInfoDiretorio(owner);
	frmInfoDiretorio->execute(PLACEMENT_SCREEN);
}

long FrmInfoDiretorio::on_btnOk_clicked(FXObject* obj, FXSelector sel, void* ptr) {
	frmInfoDiretorio->hide();
	return true;
}

void FrmInfoDiretorio::ConstruirGrid() {

}

void FrmInfoDiretorio::setDiretorio(Diretorio diretorio) {
	int row = 0;

	tabelaInfo->setItemText(row, 0, "Aba:");
	tabelaInfo->setItemText(row, 1, diretorio.getAba().getNome().c_str());
	
	tabelaInfo->setItemText(row++, 0, "Nome:");
	tabelaInfo->setItemText(row++, 1, diretorio.getNome().c_str());

	tabelaInfo->setItemText(row++, 0, "Tamanho:");
	tabelaInfo->setItemText(row++, 1, diretorio.getTamanhoFormatado().c_str());

	tabelaInfo->setItemText(row++, 0, "Tipo:");
	tabelaInfo->setItemText(row++, 1, diretorio.getTipo().getNome().c_str());

	tabelaInfo->setItemText(row++, 0, "Modificado:");
	tabelaInfo->setItemText(row++, 1, diretorio.getModificadoFormatado().c_str());

	tabelaInfo->setItemText(row++, 0, "Atributos:");
	tabelaInfo->setItemText(row++, 1, diretorio.getAtributos().c_str());

	tabelaInfo->setItemText(row++, 0, "Caminho:");
	tabelaInfo->setItemText(row++, 1, diretorio.getCaminho().c_str());
}
