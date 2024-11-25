#include "resource.h"
#include "FrmCompararDiretorio.h"

#include "hfsguardadir/catalogador/catalogador.h"
#include "hfsguardadir/objetosbo/AbaBO.h"
#include "hfsguardadir/objetosbo/DiretorioBO.h"
#include "hfsguardadir/objetosgui/Dialogo.h"

using namespace hfsguardadir::catalogador;
using namespace hfsguardadir::objetosgui;
using namespace hfsguardadir::objetosbo;

FrmCompararDiretorio *frmCompararDiretorio = (FrmCompararDiretorio *) NULL;

FXDEFMAP(FrmCompararDiretorio) FrmCompararDiretorioMap[]={
	FXMAPFUNC(SEL_CLICKED, FrmCompararDiretorio::BTN_COMPARARDIRETORIOS, FrmCompararDiretorio::on_btnCompararDiretorios_clicked),
	FXMAPFUNC(SEL_CLICKED, FrmCompararDiretorio::BTN_SALVARLOG, FrmCompararDiretorio::on_btnSalvarLog_clicked),
	FXMAPFUNC(SEL_COMMAND, FrmCompararDiretorio::CMB_ABA1, FrmCompararDiretorio::on_cmbAba1_changed),
	FXMAPFUNC(SEL_COMMAND, FrmCompararDiretorio::CMB_ABA2, FrmCompararDiretorio::on_cmbAba2_changed),
	FXMAPFUNC(SEL_LEFTBUTTONPRESS, FrmCompararDiretorio::ARVORE_DIR1, FrmCompararDiretorio::on_tvDiretorio1_LeftBtnPress),
	FXMAPFUNC(SEL_LEFTBUTTONPRESS, FrmCompararDiretorio::ARVORE_DIR2, FrmCompararDiretorio::on_tvDiretorio2_LeftBtnPress)
};
FXIMPLEMENT(FrmCompararDiretorio, FXDialogBox,FrmCompararDiretorioMap,ARRAYNUMBER(FrmCompararDiretorioMap))


FrmCompararDiretorio::FrmCompararDiretorio(FXWindow* owner):
	FXDialogBox(owner, "Comparar Diretórios", DECOR_TITLE | DECOR_CLOSE,
	  0, 0, 700, 600, 0, 0, 0, 0, 0, 0) {

	barraComparar = new FXHorizontalFrame(this, LAYOUT_SIDE_TOP | LAYOUT_FILL_X);
	btnCompararDiretorios = new FXButton(barraComparar, "Comparar Diretórios", 0,
		this, BTN_COMPARARDIRETORIOS, (FRAME_RAISED | FRAME_THICK | LAYOUT_TOP | LAYOUT_LEFT));
	pb2 = new FXProgressBar(barraComparar, this, PB_COMPARAR, FRAME_SUNKEN | LAYOUT_FILL_X | LAYOUT_FILL_Y);
	btnSalvarLog = new FXButton(barraComparar, "Salvar Log", 0,
		this, BTN_SALVARLOG, (FRAME_RAISED | FRAME_THICK | LAYOUT_TOP | LAYOUT_LEFT));

	framePrincipal = new FXVerticalFrame(this, LAYOUT_FILL_X | LAYOUT_FILL_Y);
	
	frameArvores = new FXHorizontalFrame(framePrincipal, LAYOUT_FILL_X | LAYOUT_FILL_Y);

	grupo1 = new FXGroupBox(frameArvores, "Diretório 1",
		GROUPBOX_TITLE_LEFT | FRAME_RIDGE | LAYOUT_FILL_X | LAYOUT_FILL_Y);
	cmbAba1 = new FXComboBox(grupo1, 10, this, CMB_ABA1, FRAME_SUNKEN | LAYOUT_FILL_X);
	tvDiretorio1 = new Arvore(grupo1, this, ARVORE_DIR1, TREELIST_SINGLESELECT | TREELIST_ROOT_BOXES |
		TREELIST_SHOWS_BOXES | TREELIST_SHOWS_LINES | LAYOUT_FILL_X | LAYOUT_FILL_Y);

	grupo2 = new FXGroupBox(frameArvores, "Diretório 2",
		GROUPBOX_TITLE_LEFT | FRAME_RIDGE | LAYOUT_FILL_X | LAYOUT_FILL_Y);
	cmbAba2 = new FXComboBox(grupo2, 10, this, CMB_ABA1, FRAME_SUNKEN | LAYOUT_FILL_X);
	tvDiretorio2 = new Arvore(grupo2, this, ARVORE_DIR2, TREELIST_SINGLESELECT | TREELIST_ROOT_BOXES |
		TREELIST_SHOWS_BOXES | TREELIST_SHOWS_LINES | LAYOUT_FILL_X | LAYOUT_FILL_Y);

	new FXLabel(framePrincipal, "Diferenças Encontradas", NULL, LAYOUT_LEFT);

	tabelaCompara = new Tabela(framePrincipal, this, TABELA_COMPARA, LAYOUT_FILL_X | LAYOUT_FILL_Y, true);

	frameStatus = new FXHorizontalFrame(framePrincipal, LAYOUT_SIDE_BOTTOM | LAYOUT_FILL_X);

	labStatus = new FXLabel(frameStatus, "Total de diferenças encontradas:", NULL, FRAME_SUNKEN |
		LAYOUT_FIX_WIDTH, 0, 0, 200, 20);
	labStatus->setJustify(FX::JUSTIFY_LEFT);
	barraStatus = new FXStatusBar(frameStatus, LAYOUT_FILL_X);
	barraStatus->getStatusLine()->setNormalText("");

	CarregarDados();
	LimparComparacao();
}

void FrmCompararDiretorio::create(){
	FXDialogBox::create();
}

FrmCompararDiretorio::~FrmCompararDiretorio(){
}

void FrmCompararDiretorio::mostrar(FXWindow* owner)
{
	frmCompararDiretorio = new FrmCompararDiretorio(owner);
	frmCompararDiretorio->execute(PLACEMENT_SCREEN);
}

void FrmCompararDiretorio::ProgressoLog(Progresso progresso)
{
	if (frmCompararDiretorio != NULL) {
		if (progresso.posicao == 0) {
			frmCompararDiretorio->pb2->setProgress(progresso.minimo);
		}
		frmCompararDiretorio->pb2->setProgress(
			Rotinas::calculaProgresso(progresso.maximo, progresso.posicao));
	}
}

long FrmCompararDiretorio::on_btnCompararDiretorios_clicked(FXObject* obj, FXSelector sel, void* ptr) {
	std::string sCaminhoDir1, sCaminhoDir2;
	bool bSelecionado;
	FXTreeItem *iter1, *iter2;

	bSelecionado = false;
	iter1 = tvDiretorio1->getCurrentItem();
	if (iter1) {
		if (tvDiretorio1->isItemSelected(iter1)) {
			catalogador->LerArvoreDiretorio(tvDiretorio1, iter1, this->labStatus);
			sCaminhoDir1 = labStatus->getText().text();

			iter2 = tvDiretorio2->getCurrentItem();
			if (iter2) {
				if (tvDiretorio2->isItemSelected(iter2)) {
					catalogador->LerArvoreDiretorio(tvDiretorio2, iter2, this->labStatus);
					sCaminhoDir2 = labStatus->getText().text();
					bSelecionado = true;
				}
			}
		}
	}

	LimparComparacao();

	if (bSelecionado) {
		Comparar(sCaminhoDir1, sCaminhoDir2);
	}
	else {
		Dialogo::mensagemInfo(frmCompararDiretorio,
			"DiretoriosNaoSelecionados");
	}
	return true;
}

long FrmCompararDiretorio::on_btnSalvarLog_clicked(FXObject* obj, FXSelector sel, void* ptr) {
	std::string sLog;
	Diretorio diretorio;
	std::vector<std::string> listaLocal;
	size_t tamlista = listaCompara.size();

	if (tamlista > 0) {
		DateTime dt1 = DateTime::Now();

		sLog = Rotinas::AppDirPath() +
			dt1.FormatDateTime(Rotinas::FORMATO_DHARQUIVO) + "_Comparacao.log";	

		for (unsigned int i = 0; i < tamlista; i++) {
			diretorio = listaCompara.at(i);

			listaLocal.push_back(diretorio.getCaminho());
		}

		Rotinas::SListSaveToFile(listaLocal, sLog);

		Dialogo::mensagemInfo(frmCompararDiretorio,
			"LogSalvoMemoDirSistema");
	}
	return true;
}

long FrmCompararDiretorio::on_cmbAba1_changed(FXObject* obj, FXSelector sel, void* ptr) {
	Aba aba;

	getApp()->beginWaitCursor();

	tvDiretorio1->limpar();

	int indice = cmbAba1->getCurrentItem();

	aba = *AbaBO::getInstancia()->pegaAbaPorOrdem(catalogador->listaAbas, indice + 1);
	catalogador->CarregarArvore(frmPrincipal, tvDiretorio1, aba);

	tvDiretorio1->setFocus();
	LimparComparacao();

	getApp()->endWaitCursor();
	return true;
}

long FrmCompararDiretorio::on_tvDiretorio1_LeftBtnPress(FXObject* obj, FXSelector sel, void* ptr) {
	tvDiretorio1->expandirSelecionado();
	return true;
}

long FrmCompararDiretorio::on_cmbAba2_changed(FXObject* obj, FXSelector sel, void* ptr){
	Aba aba;

	getApp()->beginWaitCursor();

	tvDiretorio2->limpar();

	int indice = cmbAba2->getCurrentItem();

	aba = *AbaBO::getInstancia()->pegaAbaPorOrdem(catalogador->listaAbas, indice + 1);
	catalogador->CarregarArvore(frmPrincipal, tvDiretorio2, aba);

	tvDiretorio2->setFocus();
	LimparComparacao();

	getApp()->endWaitCursor();
	return true;
}

long FrmCompararDiretorio::on_tvDiretorio2_LeftBtnPress(FXObject* obj, FXSelector sel, void* ptr) {
	tvDiretorio2->expandirSelecionado();
	return true;
}

void FrmCompararDiretorio::CarregarDados() {
	Aba aba;
	Aba aba1;

	for (unsigned int i = 0; i < catalogador->listaAbas.size(); i++) {
		aba = catalogador->listaAbas.at(i);

		cmbAba1->insertItem(i, aba.getNome().c_str());
		cmbAba2->insertItem(i, aba.getNome().c_str());
	}
	cmbAba1->setNumVisible((int)catalogador->listaAbas.size());
	cmbAba2->setNumVisible((int)catalogador->listaAbas.size());

	cmbAba1->setCurrentItem(0);
	cmbAba2->setCurrentItem(0);

	aba1 = *AbaBO::getInstancia()->pegaAbaPorOrdem(catalogador->listaAbas, 1);
	catalogador->CarregarArvore(frmPrincipal, tvDiretorio1, aba1);

	aba1 = *AbaBO::getInstancia()->pegaAbaPorOrdem(catalogador->listaAbas, 1);
	catalogador->CarregarArvore(frmPrincipal, tvDiretorio2, aba1);
}

void FrmCompararDiretorio::LimparComparacao() {
	pb2->setProgress(0);
	tabelaCompara->limpar();	
	labStatus->setText("");
}

std::string FrmCompararDiretorio::SQLCompara(Aba aba1, Aba aba2, const std::string caminho1, const std::string caminho2) {
	char* sSQL = (char*)DiretorioBO::SQL_CONSULTA_ARQUIVO.c_str();

	std::snprintf(sSQL, TAM_MAX_STR, " WHERE aba=%d AND caminho LIKE %s AND nome NOT IN " \
		"(SELECT nome FROM Diretorios WHERE aba=%d AND caminho LIKE %s) ORDER BY 1, 2, 3",
		aba1.getCodigo(), Rotinas::QuotedStr(caminho1 + "%").c_str(),
		aba2.getCodigo(), Rotinas::QuotedStr(caminho2 + "%").c_str());
	return sSQL;
}

void FrmCompararDiretorio::Comparar(const std::string sCaminhoDir1, const std::string sCaminhoDir2) {
	std::string sSQL;
	Aba aba1, aba2;
	int tamlista;
	
	int indice = cmbAba1->getCurrentItem();
	aba1 = *AbaBO::getInstancia()->pegaAbaPorOrdem(catalogador->listaAbas, indice + 1);

	indice = cmbAba2->getCurrentItem();
	aba2 = *AbaBO::getInstancia()->pegaAbaPorOrdem(catalogador->listaAbas, indice + 1);

	sSQL = SQLCompara(aba1, aba2, sCaminhoDir1, sCaminhoDir2);
	listaCompara = DiretorioBO::getInstancia()->carregarDiretorio(sSQL, "consultaarquivo", ProgressoLog);
	tamlista = (int)listaCompara.size();

	if (tamlista > 0) {
		tabelaCompara->carregar(listaCompara, catalogador->listaExtensoes, pb2);

		labStatus->setText(Rotinas::IntToStr(tamlista).c_str());
	}
	else {
		Dialogo::mensagemInfo(frmCompararDiretorio, "NenhumaDiferencaEncontrada");
	}
}

