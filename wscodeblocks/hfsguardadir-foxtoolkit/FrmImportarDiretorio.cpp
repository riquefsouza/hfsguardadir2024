#include "resource.h"
#include "FrmImportarDiretorio.h"
#include "hfsguardadir/catalogador/Catalogador.h"
#include "hfsguardadir/objetosbo/ImportarBO.h"
#include "hfsguardadir/objetosbo/DiretorioBO.h"
#include "hfsguardadir/objetosgui/Dialogo.h"

using namespace hfsguardadir::catalogador;
using namespace hfsguardadir::objetosgui;
using namespace hfsguardadir::objetosbo;

FrmImportarDiretorio *frmImportarDiretorio = (FrmImportarDiretorio *) NULL;

FXIMPLEMENT(FrmImportarDiretorio, FXDialogBox,NULL,0)

FrmImportarDiretorio::FrmImportarDiretorio(FXWindow* owner):
	FXDialogBox(owner, "Importar Diretórios", DECOR_TITLE | DECOR_CLOSE,
	  0, 0, 375, 113, 0, 0, 0, 0, 0, 0) {

	form_vbox1 = new FXVerticalFrame(this, LAYOUT_FILL_X | LAYOUT_FILL_Y);

	frameStatus = new FXHorizontalFrame(form_vbox1, LAYOUT_SIDE_BOTTOM | LAYOUT_FILL_X);

	labStatus = new FXLabel(frameStatus, "", NULL, FRAME_SUNKEN |
		LAYOUT_FIX_WIDTH, 0, 0, 300, 20);
	labStatus->setJustify(FX::JUSTIFY_LEFT);
	barraStatus = new FXStatusBar(frameStatus, LAYOUT_FILL_X |
		STATUSBAR_WITH_DRAGCORNER);
	barraStatus->getStatusLine()->setNormalText("");

	memoImportaDir = new FXText(form_vbox1, this);
	
	pbImportar = new FXProgressBar(form_vbox1, this, PB_IMPORTAR, FRAME_SUNKEN | LAYOUT_FILL_X | LAYOUT_FILL_Y);	

	bSubDiretorio = false;
}

void FrmImportarDiretorio::create(){
	FXDialogBox::create();
}

FrmImportarDiretorio::~FrmImportarDiretorio(){
}

void FrmImportarDiretorio::Mostrar()
{
	frmImportarDiretorio->show(PLACEMENT_SCREEN);
}

void FrmImportarDiretorio::Fechar()
{
	frmImportarDiretorio->hide();
}

void FrmImportarDiretorio::ProgressoLog(Progresso progresso)
{
	FXString buffer;
	int pos;
	std::string texto = "";

	if (frmImportarDiretorio != NULL) {
		if (progresso.posicao == 0) {
			frmImportarDiretorio->pbImportar->setProgress(progresso.minimo);
		}
		if (progresso.maximo > 0) {
			frmImportarDiretorio->pbImportar->setProgress(
				Rotinas::calculaProgresso(progresso.maximo, progresso.posicao));
		}

		if (progresso.log.length() > 0) {
			buffer = frmImportarDiretorio->memoImportaDir->getText();
			pos = frmImportarDiretorio->memoImportaDir->getLength();			
			texto = progresso.log + "\n";
			buffer.append(texto.c_str());
			frmImportarDiretorio->memoImportaDir->setText(buffer);
			//frmImportarDiretorio->memoImportaDir->scroll();			
			frmImportarDiretorio->labStatus->setText(Rotinas::IntToStr(pos).c_str());
		}
	}
}

void FrmImportarDiretorio::ImportarDir()
{
	FXString buffer;
	int nlinhas;
	std::string sLog;
	FXchar* texto = new FXchar();
	Importar importar;
	std::vector<std::string> log;

	for (unsigned int i = 0; i < listaImportar.size(); i++) {
		importar = listaImportar.at(i);

		catalogador->diretorioOrdem.setOrdem(1);

		if (!bSubDiretorio) {
			getApp()->beginWaitCursor();

			ImportarBO::getInstancia()->ImportacaoCompleta(importar,
				&catalogador->diretorioOrdem, catalogador->listaExtensoes,
				ProgressoLog);

			getApp()->endWaitCursor();
		}
		else {
			if (!DiretorioBO::getInstancia()->verificaCodDir(importar.getAba(),
				importar.getRotuloRaiz(), catalogador->listaDiretorioPai)) {
				getApp()->beginWaitCursor();

				ImportarBO::getInstancia()->ImportacaoCompleta(importar,
					&catalogador->diretorioOrdem, catalogador->listaExtensoes,
					ProgressoLog);

				getApp()->endWaitCursor();
			}
			else {
				Dialogo::mensagemInfo(frmImportarDiretorio,
					"DiretorioExisteCatalogo");
			}
		}
	}
	
	if (frmPrincipal->menuGravarLogImportacao->getCheck()) {
		nlinhas = memoImportaDir->getLength();
		if (nlinhas > 0) {
			DateTime dt1 = DateTime::Now();

			sLog = Rotinas::AppDirPath() +
				dt1.FormatDateTime(Rotinas::FORMATO_DHARQUIVO) + "_Importacao.log";

			for (int nlinha = 0; nlinha < nlinhas; nlinha++) {
				memoImportaDir->getText(texto, nlinha);
				log.push_back(texto);
			}

			Rotinas::SListSaveToFile(log, sLog);
		}
	}
	
}