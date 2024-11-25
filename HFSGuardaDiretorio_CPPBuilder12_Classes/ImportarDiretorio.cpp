// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ImportarDiretorio.h"
#include "Principal.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmImportarDiretorio *FrmImportarDiretorio;

// ---------------------------------------------------------------------------
__fastcall TFrmImportarDiretorio::TFrmImportarDiretorio(TComponent* Owner)
	: TForm(Owner) {
}
// ---------------------------------------------------------------------------
void TFrmImportarDiretorio::ProgressoLog(TProgresso progresso)
{
  if (FrmImportarDiretorio!=NULL){
	  if (progresso.posicao == 0) {
		 FrmImportarDiretorio->pbImportar->Min = progresso.minimo;
		 FrmImportarDiretorio->pbImportar->Max = progresso.maximo;
		 FrmImportarDiretorio->pbImportar->Step = progresso.passo;
	  }

	  FrmImportarDiretorio->pbImportar->Position = progresso.posicao;
  }
}
// ---------------------------------------------------------------------------
void __fastcall TFrmImportarDiretorio::FormActivate(TObject *Sender) {
	String sLog;
	TImportar importar;

	try {
		for (unsigned int i = 0; i < listaImportar->size(); i++) {
			importar = listaImportar->at(i);
			FrmPrincipal->nGlobalOrdem = 1;

			if (!bSubDiretorio) {
				Screen->Cursor = crHourGlass;

				Importar->ImportacaoCompleta(importar,
					&FrmPrincipal->nGlobalOrdem, FrmPrincipal->listaExtensoes,
					memoImportaDir->Lines, ProgressoLog);

				Screen->Cursor = crDefault;
			}
			else {
				if (!Diretorio->verificaCodDir(importar.aba,
					importar.rotuloRaiz, FrmPrincipal->listaDiretorioPai)) {
					Screen->Cursor = crHourGlass;

					Importar->ImportacaoCompleta(importar,
						&FrmPrincipal->nGlobalOrdem,
						FrmPrincipal->listaExtensoes, memoImportaDir->Lines,
						ProgressoLog);

					Screen->Cursor = crDefault;
				}
				else
					MessageDlg("Este diretório [" + importar.rotuloRaiz +
					"] já existe no catálogo!", mtError,
					TMsgDlgButtons() << mbOK, 0);
			}

		}
	}
	__finally {
		listaImportar->clear();
		delete listaImportar;
	}

	if (FrmPrincipal->GravarLogImportacao1->Checked) {
		if (memoImportaDir->Lines->Count > 0) {
			sLog = ExtractFilePath(ParamStr(0)) + FormatDateTime
				("yyyy-mm-dd_hh_nn_ss", Now()) + "_Importacao.log";
			memoImportaDir->Lines->SaveToFile(sLog);
		}
	}

	PostMessage(this->Handle, WM_CLOSE, 0, 0);
	ModalResult = mrCancel;
}
// ---------------------------------------------------------------------------

void __fastcall TFrmImportarDiretorio::memoImportaDirChange(TObject *Sender) {
	barraStatus->Panels->Items[1]->Text =
		IntToStr(memoImportaDir->Lines->Count);
	barraStatus->Refresh();
}
// ---------------------------------------------------------------------------
