// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CompararDiretorio.h"
#include "Principal.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmCompararDiretorio *FrmCompararDiretorio;

// ---------------------------------------------------------------------------
__fastcall TFrmCompararDiretorio::TFrmCompararDiretorio(TComponent* Owner)
	: TForm(Owner) {
}
// ---------------------------------------------------------------------------
void TFrmCompararDiretorio::ProgressoLog(TProgresso progresso)
{
  if (FrmCompararDiretorio!=NULL) {
	  if (progresso.posicao == 0) {
		 FrmCompararDiretorio->pb->Min = progresso.minimo;
		 FrmCompararDiretorio->pb->Max = progresso.maximo;
		 FrmCompararDiretorio->pb->Step = progresso.passo;
	  }

	  FrmCompararDiretorio->pb->Position = progresso.posicao;
  }
}
// ---------------------------------------------------------------------------
void TFrmCompararDiretorio::LimparComparacao() {
	pb->Position = 1;
	lvCompara->Clear();
	btnSalvarLog->Enabled = false;
	barraStatus->Panels->Items[1]->Text = "";
}

// ---------------------------------------------------------------------------
String TFrmCompararDiretorio::SQLCompara(TAba aba1, TAba aba2, String caminho1,
	String caminho2) {
	String sSQL;

	sSQL = SQL_CONSULTA_ARQUIVO + " WHERE aba=" + IntToStr(aba1.codigo) +
		" AND caminho LIKE " + QuotedStr(caminho1 + "%") + " AND nome NOT IN ( " \
 " SELECT nome " \
 " FROM Diretorios " \
 " WHERE aba=" + IntToStr(aba2.codigo) + " AND caminho LIKE " +
		QuotedStr(caminho2 + "%") + ")" + " ORDER BY 1, 2, 3";
	return sSQL;
}

// ---------------------------------------------------------------------------
void TFrmCompararDiretorio::Comparar(String sCaminhoDir1, String sCaminhoDir2) {
	// String sSQL;
	TAba aba1, aba2;
	int tamLista;

	aba1 = Aba->pegaAbaPorOrdem(FrmPrincipal->listaAbas,
		cmbAba1->ItemIndex + 1);
	aba2 = Aba->pegaAbaPorOrdem(FrmPrincipal->listaAbas,
		cmbAba2->ItemIndex + 1);
	dm->consultaAuxiliar->SQL->Text = SQLCompara(aba1, aba2, sCaminhoDir1,
		sCaminhoDir2);
	// Diretorio->carregarDiretorio(sSQL, listaCompara, pb);
	Diretorio->carregarDiretorio(dm->consultaAuxiliar, listaCompara,
		ProgressoLog);

	if (listaCompara->size() > 0) {
		FrmPrincipal->CarregarItensLista(true, lvCompara, listaCompara);
		tamLista = listaCompara->size();
		barraStatus->Panels->Items[1]->Text = IntToStr(tamLista);
		barraStatus->Refresh();
		btnSalvarLog->Enabled = true;
	}
	else
		MessageDlg("Nenhuma diferença encontrada!", mtInformation,
		TMsgDlgButtons() << mbOK, 0);
}
// ---------------------------------------------------------------------------

void __fastcall TFrmCompararDiretorio::btnCompararDiretoriosClick
	(TObject *Sender)

{
	String sCaminhoDir1, sCaminhoDir2;
	bool bSelecionado;

	bSelecionado = false;

	if (tvDiretorio1->Selected != NULL) {
		if (tvDiretorio1->Selected->Selected) {
			FrmPrincipal->LerArvoreDiretorio(tvDiretorio1->Selected,
			barraStatus);
			sCaminhoDir1 = barraStatus->Panels->Items[1]->Text;

			if (tvDiretorio2->Selected != NULL) {
				if (tvDiretorio2->Selected->Selected) {
					FrmPrincipal->LerArvoreDiretorio(tvDiretorio2->Selected,
						barraStatus);
					sCaminhoDir2 = barraStatus->Panels->Items[1]->Text;
					bSelecionado = true;
				}
			}

		}
	}

	LimparComparacao();

	if (bSelecionado)
		Comparar(sCaminhoDir1, sCaminhoDir2);
	else
		MessageDlg("Diretórios não selecionados!", mtInformation,
		TMsgDlgButtons() << mbOK, 0);
}
// ---------------------------------------------------------------------------

void __fastcall TFrmCompararDiretorio::btnSalvarLogClick(TObject *Sender) {
	String sLog;
	TDiretorio diretorio;
	TStringList *listaLocal;

	if (listaCompara->size() > 0) {
		listaLocal = new TStringList();
		try {
			sLog = ExtractFilePath(ParamStr(0)) + FormatDateTime
				("yyyy-mm-dd_hh_nn_ss", Now()) + "_Comparacao.log";

			for (unsigned int i = 0; i < listaCompara->size(); i++) {
				diretorio = listaCompara->at(i);
				listaLocal->Append(diretorio.caminho);
			}
			listaLocal->SaveToFile(sLog);
			MessageDlg("Log salvo no mesmo diretório do sistema!",
				mtInformation, TMsgDlgButtons() << mbOK, 0);
		}
		__finally {
			listaLocal->Free();
		}
	}
}
// ---------------------------------------------------------------------------

void __fastcall TFrmCompararDiretorio::cmbAba1Change(TObject *Sender) {
	TAba aba;

	Screen->Cursor = crHourGlass;
	tvDiretorio1->Items->Clear();
	aba = Aba->pegaAbaPorOrdem(FrmPrincipal->listaAbas, cmbAba1->ItemIndex + 1);
	FrmPrincipal->CarregarArvore(tvDiretorio1, aba);
	LimparComparacao();
	Screen->Cursor = crDefault;
}
// ---------------------------------------------------------------------------

void __fastcall TFrmCompararDiretorio::cmbAba2Change(TObject *Sender) {
	TAba aba;

	Screen->Cursor = crHourGlass;
	tvDiretorio2->Items->Clear();
	aba = Aba->pegaAbaPorOrdem(FrmPrincipal->listaAbas, cmbAba2->ItemIndex + 1);
	FrmPrincipal->CarregarArvore(tvDiretorio2, aba);
	LimparComparacao();
	Screen->Cursor = crDefault;
}

// ---------------------------------------------------------------------------
void __fastcall TFrmCompararDiretorio::FormShow(TObject *Sender) {
	TAba aba;

	for (unsigned int i = 0; i < FrmPrincipal->listaAbas->size(); i++) {
		aba = FrmPrincipal->listaAbas->at(i);
		cmbAba1->Items->Append(aba.nome);
		cmbAba2->Items->Append(aba.nome);
	}
	cmbAba1->ItemIndex = 0;
	cmbAba2->ItemIndex = 0;

	aba = Aba->pegaAbaPorOrdem(FrmPrincipal->listaAbas, cmbAba1->ItemIndex + 1);
	FrmPrincipal->CarregarArvore(tvDiretorio1, aba);

	aba = Aba->pegaAbaPorOrdem(FrmPrincipal->listaAbas, cmbAba2->ItemIndex + 1);
	FrmPrincipal->CarregarArvore(tvDiretorio2, aba);
}

// ---------------------------------------------------------------------------
void __fastcall TFrmCompararDiretorio::FormCreate(TObject *Sender) {
	listaCompara = new std::vector<TDiretorio>();
}
// ---------------------------------------------------------------------------

void __fastcall TFrmCompararDiretorio::FormDestroy(TObject *Sender) {
	listaCompara->clear();
	delete listaCompara;
}
//---------------------------------------------------------------------------

void __fastcall TFrmCompararDiretorio::lvComparaColumnClick(TObject *Sender, TListColumn *Column)

{
  FrmPrincipal->listaColunaClick(Sender, Column);
}
// ---------------------------------------------------------------------------

void __fastcall TFrmCompararDiretorio::lvComparaCompare(TObject *Sender, TListItem *Item1,
		  TListItem *Item2, int Data, int &Compare)
{
  FrmPrincipal->listaCompara(Sender, Item1, Item2, Data, Compare);
}
//---------------------------------------------------------------------------

