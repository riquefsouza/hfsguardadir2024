// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CadExtensao.h"
#include "Extensao.h"
#include "Principal.h"
#include "EscolherDir.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmCadExtensao *FrmCadExtensao;

// ---------------------------------------------------------------------------
__fastcall TFrmCadExtensao::TFrmCadExtensao(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
void __fastcall TFrmCadExtensao::FormShow(TObject *Sender) {
	CarregarExtensoesNaGrid();
}
// ---------------------------------------------------------------------------

void __fastcall TFrmCadExtensao::ExcluirExtensao1Click(TObject *Sender) {
	TExtensao extensao;

	if (FrmPrincipal->listaExtensoes->size() > 0) {
		if (MessageDlg("Tem Certeza, que você deseja excluir esta extensão?",
			mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes) {

			extensao = Extensao->pegaExtensaoPorOrdem
				(FrmPrincipal->listaExtensoes, sgExtensao->Row);

			if (Extensao->excluirExtensao(FrmPrincipal->listaExtensoes,
				extensao.codigo)) {
				CarregarExtensoesNaGrid();
				MessageDlg("Extensão excluída com sucesso!", mtInformation,
					TMsgDlgButtons() << mbOK, 0);
			}
		}
	}

}
// ---------------------------------------------------------------------------

void __fastcall TFrmCadExtensao::IncluirExtensao1Click(TObject *Sender) {
	TStringList* log;
	TExtensao extensao;

	if (OpenDialog1->Execute()) {
		log = new TStringList();
		// dm->conexao->beginTransaction;
		dm->cdsExtensoes->Open();
		try {
			if (Extensao->SalvarExtensao(FrmPrincipal->listaExtensoes,
				ExtractFileName(OpenDialog1->FileName),
				OpenDialog1->FileName, log)) {

				dm->cdsExtensoes->ApplyUpdates(0);

				sgExtensao->RowCount = FrmPrincipal->listaExtensoes->size() + 1;
				extensao = FrmPrincipal->listaExtensoes->at
					(sgExtensao->RowCount - 2);
				sgExtensao->Cells[0][sgExtensao->RowCount - 1] = extensao.nome;
				sgExtensao->Cells[1][sgExtensao->RowCount - 1] = "";
				extensao.ordem = FrmPrincipal->listaExtensoes->size();
				FrmPrincipal->ImageList1->Add(extensao.bmp16, NULL);
				FrmPrincipal->ImageList2->Add(extensao.bmp32, NULL);

				MessageDlg("Extensão salva com sucesso!", mtInformation,
					TMsgDlgButtons() << mbOK, 0);
			}
			else {
				MessageDlg("Extensão já existe cadastrada!", mtInformation,
					TMsgDlgButtons() << mbOK, 0);
			}
		}
		__finally {
			log->Free();
			dm->cdsExtensoes->Close();
			/*
			 if (dm->conexao->RowsChanged > 0) {
			 dm->conexao->Commit;
			 }
			 */
		}
	}
}
// ---------------------------------------------------------------------------

void __fastcall TFrmCadExtensao::ExcluirTodasExtensoes1Click(TObject *Sender) {
	if (FrmPrincipal->listaExtensoes->size() > 0) {
		if (MessageDlg
			("Tem Certeza, que você deseja excluir todas as extensões?",
			mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes) {
			if (Extensao->excluirTodasExtensoes(FrmPrincipal->listaExtensoes)) {
				CarregarExtensoesNaGrid();
				MessageDlg("Extensões excluídas com sucesso!", mtInformation,
					TMsgDlgButtons() << mbOK, 0);
			}
		}
	}

}
// ---------------------------------------------------------------------------

void __fastcall TFrmCadExtensao::ExportarBitmap1Click(TObject *Sender) {
	Extensao->ExportarExtensao(teBMP, FrmPrincipal->listaExtensoes);
}
// ---------------------------------------------------------------------------

void __fastcall TFrmCadExtensao::ExportarIcone1Click(TObject *Sender) {
	Extensao->ExportarExtensao(teICO, FrmPrincipal->listaExtensoes);
}
// ---------------------------------------------------------------------------

void __fastcall TFrmCadExtensao::ExportarGIF1Click(TObject *Sender) {
	Extensao->ExportarExtensao(teGIF, FrmPrincipal->listaExtensoes);
}
// ---------------------------------------------------------------------------

void __fastcall TFrmCadExtensao::ExportarJPEG1Click(TObject *Sender) {
	Extensao->ExportarExtensao(teJPG, FrmPrincipal->listaExtensoes);
}
// ---------------------------------------------------------------------------

void __fastcall TFrmCadExtensao::ExportarPNG1Click(TObject *Sender) {
	Extensao->ExportarExtensao(tePNG, FrmPrincipal->listaExtensoes);
}
// ---------------------------------------------------------------------------

void __fastcall TFrmCadExtensao::ExportarTIFF1Click(TObject *Sender) {
	Extensao->ExportarExtensao(teTIF, FrmPrincipal->listaExtensoes);
}
// ---------------------------------------------------------------------------

void __fastcall TFrmCadExtensao::ImportarIconesArquivos1Click(TObject *Sender) {
	String sCaminho;

	Application->CreateForm(__classid(TFrmEscolherDir), &FrmEscolherDir);
	if (FrmEscolherDir->ShowModal() == mrOk) {
		sCaminho = FrmEscolherDir->labDiretorio->Caption;
		Extensao->ImportarExtensao(sCaminho, FrmPrincipal->listaExtensoes);
		CarregarExtensoesNaGrid();
	}
	FrmEscolherDir->Free();
}
// ---------------------------------------------------------------------------

void __fastcall TFrmCadExtensao::ExtrairIconesArquivos1Click(TObject *Sender) {
	String sCaminho;

	Application->CreateForm(__classid(TFrmEscolherDir), &FrmEscolherDir);
	if (FrmEscolherDir->ShowModal() == mrOk) {
		sCaminho = FrmEscolherDir->labDiretorio->Caption;
		Extensao->ExtrairExtensao(sCaminho, FrmPrincipal->listaExtensoes);
		CarregarExtensoesNaGrid();
	}
	FrmEscolherDir->Free();

}
// ---------------------------------------------------------------------------

void __fastcall TFrmCadExtensao::sgExtensaoDrawCell(TObject *Sender, int ACol,
	int ARow, TRect &Rect, TGridDrawState State) {
	TExtensao extensao;

	if ((ACol == 1) && (ARow > 0)) {
		if (FrmPrincipal->listaExtensoes->size() > 0) {
			extensao = FrmPrincipal->listaExtensoes->at(ARow - 1);
			sgExtensao->Canvas->Draw(Rect.Left + 2, Rect.Top + 2,
				extensao.bmp16);
		}
	}

}

// ---------------------------------------------------------------------------
void TFrmCadExtensao::CarregarExtensoesNaGrid() {
	TExtensao extensao;

	sgExtensao->ColCount = 2;
	if (FrmPrincipal->listaExtensoes->size() > 0)
		sgExtensao->RowCount = FrmPrincipal->listaExtensoes->size() + 1;
	else
		sgExtensao->RowCount = 2;
	sgExtensao->DefaultColWidth = 100;
	sgExtensao->DefaultRowHeight = 18;
	sgExtensao->FixedCols = 0;
	sgExtensao->FixedRows = 1;

	sgExtensao->Cells[0][0] = "Extensão";
	sgExtensao->Cells[1][0] = "Ícone";

	sgExtensao->Cells[0][1] = "";
	sgExtensao->Cells[1][1] = "";

	for (unsigned int i = 0; i < FrmPrincipal->listaExtensoes->size(); i++) {
		extensao = FrmPrincipal->listaExtensoes->at(i);
		sgExtensao->Cells[0][i + 1] = extensao.nome;
	}

}
