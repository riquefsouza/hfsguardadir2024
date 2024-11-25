// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <System.Math.hpp>
#include "Principal.h"
#include "Sobre.h"
#include "CadExtensao.h"
#include "Splash.h"
#include "EscolherDir.h"
#include "ImportarDiretorio.h"
#include "CompararDiretorio.h"
#include "InfoDiretorio.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmPrincipal *FrmPrincipal;

// ---------------------------------------------------------------------------
__fastcall TFrmPrincipal::TFrmPrincipal(TComponent* Owner) : TForm(Owner) {
}
// ---------------------------------------------------------------------------
void TFrmPrincipal::ProgressoLog(TProgresso progresso)
{
  if (FrmPrincipal!=NULL) {
	  if (progresso.posicao == 0) {
		 FrmPrincipal->pb->Min = progresso.minimo;
		 FrmPrincipal->pb->Max = progresso.maximo;
		 FrmPrincipal->pb->Step = progresso.passo;
	  }

	  FrmPrincipal->pb->Position = progresso.posicao;
  }
}
// ---------------------------------------------------------------------------
void TFrmPrincipal::CarregarDados(TProgressoLog pLog, boolean bExtensao,
	boolean bDiretorio) {
	Aba->carregarAba(listaAbas, pLog);
	if (bExtensao) {
		Extensao->carregarExtensao(listaExtensoes, pLog);
		Extensao->carregarExtensoes(listaExtensoes, ImageList1, ImageList2);
	}
	if (bDiretorio) {
		Diretorio->carregarDiretorio(dm->consultaDirPai, listaDiretorioPai, pLog);
		Diretorio->carregarDiretorio(dm->consultaDirFilho, listaDiretorioFilho, pLog);
		Diretorio->carregarDiretorio(dm->consultaArquivo, listaArquivos, pLog);
    }
}
// ---------------------------------------------------------------------------
void TFrmPrincipal::ExcluirDados(TAba aba, String sCaminho)
{
  Diretorio->excluirListaDiretorio(listaDiretorioPai, aba, sCaminho);
  Diretorio->excluirListaDiretorio(listaDiretorioFilho, aba, sCaminho);
  Diretorio->excluirListaDiretorio(listaArquivos, aba, sCaminho);
}
// ---------------------------------------------------------------------------
void TFrmPrincipal::AddItemArvore(TTreeView *tvAba, TDiretorio diretorio,
	int Nivel, TTreeNode *node1) {
	std::vector<TDiretorio> *listaFilhos;
	TDiretorio filho;
	TTreeNode *node2;

	if (Nivel == 0) {
		node1 = tvAba->Items->Add(NULL, diretorio.nome);
		node1->ImageIndex = 0;
		node1->ExpandedImageIndex = 1;
	}

	listaFilhos = Diretorio->itensFilhos(listaDiretorioFilho,
		diretorio.aba.codigo, diretorio.ordem, diretorio.codigo);

	for (unsigned int j = 0; j < listaFilhos->size(); j++) {
		filho = listaFilhos->at(j);
		node2 = tvAba->Items->AddChild(node1, filho.nome);
		node2->ImageIndex = 0;
		node2->ExpandedImageIndex = 1;
		AddItemArvore(tvAba, filho, ++Nivel, node2);
	}
	listaFilhos->clear();
	delete listaFilhos;
}

// ---------------------------------------------------------------------------
void TFrmPrincipal::IncluirNovaAba(String nomeAba) {
	TTabSheet *sheet;
	TTreeView *tv;
	TSplitter *sp;
	TListView *lv;
	TListColumn *coluna;

	sheet = new TTabSheet(this);
	sheet->PageControl = this->pageControl;
	sheet->Caption = nomeAba;

	sp = new TSplitter(this);
	sp->Name = "sp" + nomeAba;
	sp->Left = 213;
	sp->Top = 0;
	sp->Width = 5;
	sp->Height = 408;
	sp->Beveled = true;
	pageControl->Pages[pageControl->PageCount - 1]->InsertControl(sp);

	tv = new TTreeView(this);
	tv->Name = "tv" + nomeAba;
	tv->Left = 0;
	tv->Top = 0;
	tv->Width = 300;
	tv->Height = 408;
	tv->Align = alLeft;
	tv->OnChange = tvFixaChange;
	tv->Images = ImageList1;
	tv->HideSelection = false;
	tv->ReadOnly = true;
	pageControl->Pages[pageControl->PageCount - 1]->InsertControl(tv);

	lv = new TListView(this);
	lv->Name = "lv" + nomeAba;
	lv->Left = 218;
	lv->Top = 0;
	lv->Width = 618;
	lv->Height = 408;
	lv->Align = alClient;
	lv->GridLines = true;
	lv->ViewStyle = vsReport;
	lv->SmallImages = ImageList1;
	lv->LargeImages = ImageList2;
	lv->OnDblClick = lvFixaDblClick;
	lv->OnColumnClick = lvFixaColumnClick;
	lv->OnCompare = lvFixaCompare;
	coluna = lv->Columns->Add();
	coluna->Caption = "Nome";
	coluna->Width = 300;
	coluna = lv->Columns->Add();
	coluna->Caption = "Tamanho";
	coluna->Width = 100;
	coluna = lv->Columns->Add();
	coluna->Caption = "Tipo";
	coluna->Width = 70;
	coluna = lv->Columns->Add();
	coluna->Caption = "Modificado";
	coluna->Width = 120;
	coluna = lv->Columns->Add();
	coluna->Caption = "Atributos";
	coluna->Width = 90;
	coluna = lv->Columns->Add();
	coluna->AutoSize = true;
	coluna->Caption = "Caminho";
	coluna->Width = 300;

	pageControl->Pages[pageControl->PageCount - 1]->InsertControl(lv);

}

// ---------------------------------------------------------------------------
void TFrmPrincipal::CarregarAbas() {
	TTreeView *tvAba;

	pb->Min = 0;
	pb->Max = listaAbas->size() - 1;
	pb->Position = 0;
	pb->Step = 1;

	for (unsigned int i = 0; i < listaAbas->size(); i++) {
		if (i == 0)
			pageControl->Pages[i]->Caption = listaAbas->at(i).nome;
		else
			IncluirNovaAba(listaAbas->at(i).nome);

		tvAba = getTreeViewAtual(i);

		CarregarArvore(tvAba, listaAbas->at(i));

		pb->Position = i;
	}
}

// ---------------------------------------------------------------------------
void TFrmPrincipal::ListarArquivos(TListView *lvArquivos, TTreeNode *Node) {
	if (Node != NULL) {
		if (Node->Selected) {
			LerArvoreDiretorio(Node, barraStatus);
			CarregarArquivosLista(true, lvArquivos,
				barraStatus->Panels->Items[1]->Text);
			TamTotalDiretorio(barraStatus->Panels->Items[1]->Text);
		}
	}
}

// ---------------------------------------------------------------------------
void TFrmPrincipal::AdicionaItemLista(bool bLista1, TListView *lvArquivos,
	TDiretorio diretorio) {
	TListItem *list1;

	list1 = lvArquivos->Items->Add();

	list1->Caption = diretorio.nome;
	if (diretorio.tipo.codigo == 'D') {
		list1->SubItems->Append("");
		list1->ImageIndex = 0;
	}
	else {
		list1->SubItems->Append(diretorio.tamanhoFormatado);
		list1->ImageIndex = Extensao->indiceExtensao(listaExtensoes,
			diretorio.nome);
	}
	list1->SubItems->Append(diretorio.tipo.nome);
	list1->SubItems->Append(diretorio.modificadoFormatado);
	list1->SubItems->Append(diretorio.atributos);
	list1->SubItems->Append(diretorio.caminho);

	if (!bLista1) {
		list1->SubItems->Append(diretorio.aba.nome);
		list1->SubItems->Append(IntToStr(diretorio.aba.codigo));
		list1->SubItems->Append(diretorio.nomePai);
	}

}

// ---------------------------------------------------------------------------
void TFrmPrincipal::CarregarArquivosLista(bool bLista1, TListView *lvArquivos,
	String sCaminho) {
	String sPaiCaminho;
	TDiretorio diretorio;
	std::vector<TDiretorio> *listaLocal;

	listaLocal = new std::vector<TDiretorio>();
	lvArquivos->Items->Clear();

	if (bLista1) {
		sPaiCaminho = sCaminho;
		if (sCaminho.SubString(sCaminho.Length(), 1) != BARRA_INVERTIDA)
			sCaminho = sCaminho + BARRA_INVERTIDA;

		for (unsigned int i = 0; i < listaArquivos->size(); i++) {
			diretorio = listaArquivos->at(i);
			if (diretorio.aba.codigo == getAbaAtual().codigo) {
				if ((diretorio.caminhoPai == sPaiCaminho)) {
					if (AnsiStartsStr(sCaminho, diretorio.caminho)) {
						listaLocal->push_back(diretorio);
					}
				}
			}
		}
	}
	else {
		for (unsigned int i = 0; i < listaArquivos->size(); i++) {
			diretorio = listaArquivos->at(i);
			if (AnsiContainsText(diretorio.caminho.UpperCase(),
				sCaminho.UpperCase())) {
				listaLocal->push_back(diretorio);
			}
		}
	}
	CarregarItensLista(bLista1, lvArquivos, listaLocal);

	listaLocal->clear();
	delete listaLocal;
}

// ---------------------------------------------------------------------------
void TFrmPrincipal::TamTotalDiretorio(String sCaminho) {
	TDiretorio diretorio;
	Extended conta, soma;

	conta = 0;
	soma = 0;

	for (unsigned int i = 0; i < listaArquivos->size(); i++) {
		diretorio = listaArquivos->at(i);

		if (diretorio.aba.codigo == getAbaAtual().codigo) {
			if ((diretorio.tipo.codigo != 'D')) {
				if (sCaminho.Trim().Length() > 0) {
					if (AnsiStartsStr(sCaminho, diretorio.caminho)) {
						conta++;
						soma = soma + diretorio.tamanho;
					}
				}
				else {
					conta++;
					soma = soma + diretorio.tamanho;
				}
			}
		}
	}

	barraStatus->Panels->Items[0]->Text =
		"Quantidade Total: " + FormatFloat("0000", conta) +
		", Tamanho Total: " + Diretorio->MontaTamanhoBig(soma);
}

// ---------------------------------------------------------------------------
void TFrmPrincipal::DuploCliqueLista(TListView *lvLocal, TTreeView *tvLocal) {
	String sCaminho;

	if (lvLocal->SelCount > 0) {
		if (lvLocal->Selected->SubItems->Strings[1] == "Diretório") {
			sCaminho = barraStatus->Panels->Items[1]->Text;
			if (sCaminho.SubString(sCaminho.Length(), 1) == BARRA_INVERTIDA)
				sCaminho = barraStatus->Panels->Items[1]->Text +
					lvLocal->Selected->Caption;
			else
				sCaminho = barraStatus->Panels->Items[1]->Text +
					BARRA_INVERTIDA + lvLocal->Selected->Caption;

			tvLocal->Selected = PesquisarArvoreDiretorio(tvLocal, sCaminho);

			CarregarArquivosLista(true, lvLocal, sCaminho);
			TamTotalDiretorio(sCaminho);
		}
	}
}

// ---------------------------------------------------------------------------
TTreeView* TFrmPrincipal::getTreeViewAtual(int nIndicePagina) {
	if (nIndicePagina == 0)
		return (TTreeView*)pageControl->Pages[nIndicePagina]->Controls[2];
	else
		return (TTreeView*)pageControl->Pages[nIndicePagina]->Controls[1];
}

// ---------------------------------------------------------------------------
TSplitter* TFrmPrincipal::getSplitterAtual() {
	return (TSplitter*)pageControl->Pages[pageControl->ActivePageIndex]
		->Controls[0];
}

// ---------------------------------------------------------------------------
TListView* TFrmPrincipal::getListViewAtual() {
	if (pageControl->ActivePageIndex == 0)
		return (TListView*)pageControl->Pages[pageControl->ActivePageIndex]
			->Controls[1];
	else
		return (TListView*)pageControl->Pages[pageControl->ActivePageIndex]
			->Controls[2];
}

// ---------------------------------------------------------------------------
TAba TFrmPrincipal::getAbaAtual() {
	return Aba->pegaAbaPorOrdem(listaAbas, pageControl->ActivePageIndex + 1);
}

// ---------------------------------------------------------------------------
void TFrmPrincipal::Pesquisar(TTreeView *tvLocal) {
	if (tvLocal->Items->Count > 0) {
		if (edtPesquisa->Text.Length() >= 2) {
			lvPesquisa->Visible = true;
			spPesquisa->Visible = true;
			CarregarArquivosLista(false, lvPesquisa, edtPesquisa->Text);
		}
		else {
			lvPesquisa->Visible = false;
			spPesquisa->Visible = false;
			lvPesquisa->Items->Clear();
			MessageDlg("A pesquisa só é feita com pelo menos 2 caracteres!",
				mtInformation, TMsgDlgButtons() << mbOK, 0);
		}
	}
}

// ---------------------------------------------------------------------------
TTreeNode* TFrmPrincipal::PesquisarArvoreDiretorio(TTreeView *tvLocal,
	String sCaminhoPai) {
	TTreeNode *proximoNode, *diretorioNode;
	TStringList *slTemp;
	int nPos;

	Screen->Cursor = crHourGlass;

	slTemp = new TStringList();
	slTemp->Text = StringReplace(sCaminhoPai, BARRA_INVERTIDA,
		"\n", TReplaceFlags() << rfReplaceAll << rfIgnoreCase);

	proximoNode = tvLocal->Items->Item[0];
	diretorioNode = NULL;
	nPos = 0;
	while (proximoNode != NULL) {

		if (slTemp->Strings[nPos] == proximoNode->Text) {
			diretorioNode = proximoNode;

			if (nPos == (slTemp->Count - 1)) {
				break;
			}
			nPos = nPos + 1;
		}

		proximoNode = proximoNode->GetNext();
	}
	slTemp->Free();
	Screen->Cursor = crDefault;

	return diretorioNode;
}

// ---------------------------------------------------------------------------
void TFrmPrincipal::EncontrarItemLista() {
	TListItem *ti;
	int nAltura, nNumeroAba;
	TTreeView *tvLocal;
	TListView *lvLocal;

	if (lvPesquisa->SelCount > 0) {
		nNumeroAba = Aba->pegaOrdemPorNomeAba(listaAbas,lvPesquisa->Selected->SubItems->Strings[5]) - 1;
		//nNumeroAba = StrToInt(lvPesquisa->Selected->SubItems->Strings[6]) - 1;

		pageControl->ActivePageIndex = nNumeroAba;
		tvLocal = getTreeViewAtual(pageControl->ActivePageIndex);
		lvLocal = getListViewAtual();

		tvLocal->Selected = PesquisarArvoreDiretorio(tvLocal,
			lvPesquisa->Selected->SubItems->Strings[4]); // Caminho

		ti = lvLocal->FindCaption(0, lvPesquisa->Selected->Caption, false,
			true, true);
		lvLocal->SetFocus();
		if (ti != NULL) {
			lvLocal->ItemFocused = ti;
			lvLocal->Selected = ti;

			nAltura = round(abs(lvLocal->Font->Height * lvLocal->Font->PixelsPerInch) / 72)+2;
			lvLocal->Scroll(ti->GetPosition().x, ti->GetPosition().y - nAltura);
		}
	}
}

// ---------------------------------------------------------------------------
int TFrmPrincipal::verificaNomeDiretorio(String sCaminho, String* sRotuloRaiz) {
	(*sRotuloRaiz) = Diretorio->removerDrive(sCaminho);
	if (sRotuloRaiz->Length() == 0) {
		if (InputQuery("Este diretório não possui um nome!",
			"Digite o nome do diretório: ", *sRotuloRaiz)) {
			(*sRotuloRaiz) = sRotuloRaiz->Trim();

			if (sRotuloRaiz->Length() > 0)
				return 1;
			else {
				MessageDlg("Nenhum nome de diretório informado!", mtInformation,
					TMsgDlgButtons() << mbOK, 0);
				return 0;
			}
		}
		else
			return 0;
	}
	else if (Pos(BARRA_INVERTIDA, *sRotuloRaiz) > 0) {
		(*sRotuloRaiz) = sRotuloRaiz->SubString(LastDelimiter(BARRA_INVERTIDA,
			*sRotuloRaiz) + 1, sRotuloRaiz->Length());
		return 2;
	}
	else
		return 3;
}

// ---------------------------------------------------------------------------
void TFrmPrincipal::ExportarArquivo(TTipoExportar tipo) {
	String sExtensao;

	switch (tipo) {
	case TTipoExportar::teTXT:
		sExtensao = "txt";
		break;
	case TTipoExportar::teCSV:
		sExtensao = "csv";
		break;
	case TTipoExportar::teHTML:
		sExtensao = "html";
		break;
	case TTipoExportar::teXML:
		sExtensao = "xml";
		break;
	case TTipoExportar::teSQL:
		sExtensao = "sql";
		break;
	}

	sdExportar->FileName = getAbaAtual().nome + "." + sExtensao;
	sdExportar->Filter = "Arquivo " + sExtensao.UpperCase() + "|*." + sExtensao;
	sdExportar->DefaultExt = "." + sExtensao;
	if (sdExportar->Execute()) {
		if (FileExists(sdExportar->FileName))
			throw new Exception("Arquivo já existe.");
		else {
			Screen->Cursor = crHourGlass;
			Diretorio->exportarDiretorio(tipo, getAbaAtual(),
				sdExportar->FileName, ProgressoLog);
			Screen->Cursor = crDefault;
			MessageDlg("Exportação realizada com sucesso!", mtInformation,
				TMsgDlgButtons() << mbOK, 0);
		}
	}
}

// ---------------------------------------------------------------------------
void TFrmPrincipal::ExcluirDiretorioSelecionado() {
	TTreeView *tvLocal;
	TListView *lvLocal;

	tvLocal = getTreeViewAtual(pageControl->ActivePageIndex);
	lvLocal = getListViewAtual();

	if (tvLocal->Selected != NULL) {
		if (tvLocal->Selected->Selected) {
			if (MessageDlg
				("Tem Certeza, que você deseja excluir este diretório, " \
 "isto implicará na destruição de todos os seus items catalogados?",
				mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
			{
				Screen->Cursor = crHourGlass;

				Diretorio->excluirDiretorio(getAbaAtual(), barraStatus->Panels->Items[1]->Text);
				ExcluirDados(getAbaAtual(), barraStatus->Panels->Items[1]->Text);

				tvLocal->Items->Delete(tvLocal->Selected);
				lvLocal->Items->Clear();

				CarregarDados(ProgressoLog, false, false);

				Screen->Cursor = crDefault;
			}
		}
	}

}

// ---------------------------------------------------------------------------
void TFrmPrincipal::ImportarArquivo(TStrings *log) {
	int nResultado;

	if (odImportar->Execute()) {
		if (!FileExists(odImportar->FileName))
			throw new Exception("Arquivo não existe->");
		else {
			Screen->Cursor = crHourGlass;
			nResultado = Diretorio->importarDiretorioViaXML(getAbaAtual(),
				odImportar->FileName, listaDiretorioPai, log, ProgressoLog);
			if (nResultado == -1)
				MessageDlg("Importação não realizada!", mtError,
				TMsgDlgButtons() << mbOK, 0);
			else if (nResultado == -2)
				MessageDlg("Este diretório já existe no catálogo!", mtError,
				TMsgDlgButtons() << mbOK, 0);
			else
			   FinalizaImportacao();
			Screen->Cursor = crDefault;
		}
	}
}

// ---------------------------------------------------------------------------
bool TFrmPrincipal::ImportarDiretorios(TStringList *listaCaminho,
	bool bSubDiretorio) {
	int nAba, nRotuloRaiz, nCodDirRaiz;
	String sRotuloRaiz, sCaminhoSemDrive, sCaminho;
	TImportar importar;

	FrmImportarDiretorio->listaImportar = new std::vector<TImportar>();

	nAba = getAbaAtual().codigo;
	nCodDirRaiz = Diretorio->retMaxCodDir(nAba, listaDiretorioPai);

	for (int i = 0; i < listaCaminho->Count; i++) {
		sCaminho = listaCaminho->Strings[i];

		nRotuloRaiz = verificaNomeDiretorio(sCaminho, &sRotuloRaiz);
		if (nRotuloRaiz > 0) {
			importar.aba = nAba;
			importar.codDirRaiz = nCodDirRaiz;
			importar.rotuloRaiz = sRotuloRaiz;
			if (nRotuloRaiz == 1) {
				importar.nomeDirRaiz = sRotuloRaiz;
			}
			else if (nRotuloRaiz == 2) {
				sCaminhoSemDrive = Diretorio->removerDrive(sCaminho);
				importar.nomeDirRaiz =
					sCaminhoSemDrive.SubString(1, LastDelimiter(BARRA_INVERTIDA,
					sCaminhoSemDrive) - 1);
			}
			else if (nRotuloRaiz == 3) {
				importar.nomeDirRaiz = "";
			}
			importar.caminho = sCaminho;

			FrmImportarDiretorio->listaImportar->push_back(importar);
			nCodDirRaiz++;
		}

	}

	FrmImportarDiretorio->bSubDiretorio = bSubDiretorio;

	if (bSubDiretorio) {
		FrmImportarDiretorio->ShowModal();
		return true;
	}
	else {
		if (!Diretorio->verificaCodDir(importar.aba, importar.rotuloRaiz,
			listaDiretorioPai)) {
			FrmImportarDiretorio->ShowModal();
			return true;
		}
		else {
			MessageDlg("Este diretório [" + importar.rotuloRaiz +
				"] já existe no catálogo!", mtError,
			TMsgDlgButtons() << mbOK, 0);
			return false;
		}
	}

}

// ---------------------------------------------------------------------------
void TFrmPrincipal::ComecaImportacao(bool bSubDiretorios) {
	String sCaminho;
	TStringList *listaCaminho;

	Application->CreateForm(__classid(TFrmEscolherDir), &FrmEscolherDir);
	if (FrmEscolherDir->ShowModal() == mrOk) {
		sCaminho = FrmEscolherDir->labDiretorio->Caption;

		Application->CreateForm(__classid(TFrmImportarDiretorio),
			&FrmImportarDiretorio);
		listaCaminho = new TStringList();
		try {
			if (bSubDiretorios)
				Diretorio->carregarSubDiretorios(sCaminho, listaCaminho);
			else
				listaCaminho->Add(sCaminho);

			if (ImportarDiretorios(listaCaminho, bSubDiretorios)) {
				FinalizaImportacao();
			}
		}
		__finally {
			listaCaminho->Free();
			FrmImportarDiretorio->Free();
		}
	}
	FrmEscolherDir->Free();
}

// ---------------------------------------------------------------------------
void TFrmPrincipal::FinalizaImportacao() {
	TTreeView *tvAba;

	Screen->Cursor = crHourGlass;

	CarregarDados(ProgressoLog, true, true);
	tvAba = getTreeViewAtual(pageControl->ActivePageIndex);
	CarregarArvore(tvAba, getAbaAtual());

	Screen->Cursor = crDefault;
	MessageDlg("Importação do(s) diretório(s) realizada com sucesso!",
		mtInformation, TMsgDlgButtons() << mbOK, 0);

}

// ---------------------------------------------------------------------------
void TFrmPrincipal::CarregarArvore(TTreeView *tvAba, TAba aba) {
	TTreeNode *Node;
	TDiretorio diretorio;

	tvAba->Items->Clear();

	tvAba->Items->BeginUpdate();
	try {
		Node = NULL;
		for (unsigned int i = 0; i < listaDiretorioPai->size(); i++) {
			diretorio = listaDiretorioPai->at(i);
			if (diretorio.aba.codigo == aba.codigo) {
				AddItemArvore(tvAba, diretorio, 0, Node);
			}
		}
	}
	__finally {
		tvAba->Items->EndUpdate();
	}
}

// ---------------------------------------------------------------------------
TTreeNode* TFrmPrincipal::LerArvoreDiretorio(TTreeNode *MyTreeNode1,
	TStatusBar *barraStatus) {
	TTreeNode *resultado;
	TTreeNode *NodeAnterior;
	String sSep;

	barraStatus->Panels->Items[1]->Text = MyTreeNode1->Text;
	barraStatus->Refresh();
	NodeAnterior = MyTreeNode1->Parent;
	resultado = NodeAnterior;
	while (NodeAnterior != NULL) {
		if (NodeAnterior->Text.SubString(NodeAnterior->Text.Length(),
			1) == BARRA_INVERTIDA)
			sSep = "";
		else
			sSep = BARRA_INVERTIDA;

		barraStatus->Panels->Items[1]->Text = NodeAnterior->Text + sSep +
			barraStatus->Panels->Items[1]->Text;
		barraStatus->Refresh();
		resultado = NodeAnterior;
		NodeAnterior = NodeAnterior->Parent;
	}
	if (resultado == NULL) {
		resultado = MyTreeNode1;
	}

	return resultado;
}

// ---------------------------------------------------------------------------
void TFrmPrincipal::CarregarItensLista(bool bLista1, TListView *lvArquivos,
	std::vector<TDiretorio> *listaLocal) {
	TDiretorio diretorio;

	if (listaLocal->size() > 0) {
		pb->Min = 0;
		pb->Max = listaLocal->size() - 1;
		pb->Position = 0;
		pb->Step = 1;
		for (unsigned int i = 0; i < listaLocal->size(); i++) {
			diretorio = listaLocal->at(i);
			AdicionaItemLista(bLista1, lvArquivos, diretorio);
			pb->Position = i;
		}
	}
}
// ---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::IncluirNovaAba1Click(TObject *Sender) {
	TAba aba;

	// aba = new TAba();
	if (InputQuery("Digite o nome da nova Aba?", "Nome da Aba: ", aba.nome)) {
		aba.codigo = Aba->retMaxCodAba(listaAbas);
		aba.nome = aba.nome.SubString(1, 10);
		aba.ordem = listaAbas->size() + 1;
		Aba->incluirAba(aba);
		IncluirNovaAba(aba.nome);
		listaAbas->push_back(aba);
	}
}
// ---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::tvFixaChange(TObject *Sender, TTreeNode *Node) {
	TListView *lvArquivos;

	lvArquivos = getListViewAtual();
	ListarArquivos(lvArquivos, Node);
}
// ---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::lvFixaDblClick(TObject *Sender) {
	DuploCliqueLista((TListView*)Sender,
		getTreeViewAtual(pageControl->ActivePageIndex));
}
// ---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::CadastrarExtensaoArquivo1Click(TObject *Sender) {
	Application->CreateForm(__classid(TFrmCadExtensao), &FrmCadExtensao);
	try {
		FrmCadExtensao->ShowModal();
	}
	__finally {
		FrmCadExtensao->Free();
	}
}
// ---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::AlterarNomeAbaAtiva1Click(TObject *Sender) {
	TAba aba;

	aba = getAbaAtual();
	if (InputQuery("Digite o novo nome da Aba ativa?", "Nome da Aba: ",
		aba.nome)) {
		aba.nome = aba.nome.SubString(1, 10);
		Aba->alterarAba(aba);
		pageControl->ActivePage->Caption = aba.nome;
		CarregarDados(ProgressoLog, false, true);
	}
}
// ---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::btnPesquisaClick(TObject *Sender) {
	Pesquisar(getTreeViewAtual(pageControl->ActivePageIndex));
}
// ---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::ExcluirAbaAtiva1Click(TObject *Sender) {
	TAba aba;

	if (pageControl->ActivePageIndex > 0) {
		if (MessageDlg("Tem Certeza, que você deseja excluir esta aba, " \
 "isto implicará na destruição de todos os seus items catalogados?",
			mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes) {
			Screen->Cursor = crHourGlass;

			aba = getAbaAtual();
			Aba->excluirAba(aba);
			delete pageControl->ActivePage;

			ExcluirDados(aba, "");
			CarregarDados(ProgressoLog, false, false);

			getListViewAtual()->Clear();
			barraStatus->Panels->Items[1]->Text = "";

			Screen->Cursor = crDefault;
		}
	}
	else
		MessageDlg("A primeira Aba não pode ser excluída!", mtError,
		TMsgDlgButtons() << mbOK, 0);

}
// ---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::ExcluirDiretorioSelecionado1Click(TObject *Sender) {
	ExcluirDiretorioSelecionado();
}
// ---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::ExpandirDiretorios1Click(TObject *Sender) {
	TTreeView *tvLocal;
	TTreeNode *ANode;

	tvLocal = getTreeViewAtual(pageControl->ActivePageIndex);
	ANode = tvLocal->Items->GetFirstNode();
	while (ANode != NULL) {
		ANode->Expand(true);
		ANode = ANode->getNextSibling();
	}

}
// ---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::FormClose(TObject *Sender, TCloseAction &Action)
{
	// dm->conexao->Free();
	if (dm->conexao->Connected)
		dm->conexao->Close();
}
// ---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::FormCreate(TObject *Sender) {
	Rotinas = new TRotinas();
	Arquivo = new TArquivo();
	Diretorio = new TDiretorio();
	Aba = new TAba();
	Extensao = new TExtensao();
	Importar = new TImportar();

	listaAbas = new std::vector<TAba>();
	listaExtensoes = new std::vector<TExtensao>();
	listaDiretorioFilho = new std::vector<TDiretorio>();
	listaDiretorioPai = new std::vector<TDiretorio>();
	listaArquivos = new std::vector<TDiretorio>();

}
// ---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::FormDestroy(TObject *Sender) {
	listaAbas->clear();
	listaExtensoes->clear();
	listaDiretorioFilho->clear();
	listaDiretorioPai->clear();
	listaArquivos->clear();

	delete listaAbas;
	delete listaExtensoes;
	delete listaDiretorioFilho;
	delete listaDiretorioPai;
	delete listaArquivos;

	delete Rotinas;
	delete Arquivo;
	delete Diretorio;
	delete Aba;
	delete Extensao;
	delete Importar;
}
// ---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::ColapsarDiretorios1Click(TObject *Sender) {
	TTreeView *tvLocal;
	TTreeNode *ANode;

	tvLocal = getTreeViewAtual(pageControl->ActivePageIndex);
	ANode = tvLocal->Items->GetFirstNode();
	while (ANode != NULL) {
		ANode->Collapse(true);
		ANode = ANode->getNextSibling();
	}
}
// ---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::FormShow(TObject *Sender) {
	if (Rotinas->atribuirParamsConexao()) {
		Screen->Cursor = crHourGlass;
		CarregarDados(FrmSplash->ProgressoLog, true, true);
		CarregarAbas();
		TamTotalDiretorio("");

		FrmSplash->Hide();
		FrmSplash->Free();

		Screen->Cursor = crDefault;
	}
	else {
		MessageDlg("Biblioteca do SQLlite 3 não encontrada!", mtError,
			TMsgDlgButtons() << mbOK, 0);
		this->Close();
	}
}
// ---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::Icones1Click(TObject *Sender) {
	TListView *lvLocal;

	((TMenuItem*)Sender)->Checked = true;
	lvLocal = getListViewAtual();
	lvLocal->ViewStyle = vsIcon;
}
// ---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::IconesPequenos1Click(TObject *Sender) {
	TListView *lvLocal;

	((TMenuItem*)Sender)->Checked = true;
	lvLocal = getListViewAtual();
	lvLocal->ViewStyle = vsSmallIcon;
}
// ---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::ImportarDiretorio1Click(TObject *Sender) {
	ComecaImportacao(false);
}
// ---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::ImportarDiretoriosViaXML1Click(TObject *Sender) {
	TStringList* log;

	log = new TStringList();
	try {
		ImportarArquivo(log);
	}
	__finally {
		log->Free();
	}
}
// ---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::ImportarSubDiretorios1Click(TObject *Sender) {
	ComecaImportacao(true);
}
// ---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::CompararDiretorios1Click(TObject *Sender) {
	Application->CreateForm(__classid(TFrmCompararDiretorio),
		&FrmCompararDiretorio);
	try {
		FrmCompararDiretorio->ShowModal();
	}
	__finally {
		FrmCompararDiretorio->Free();
	}
}
// ---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::Detalhes1Click(TObject *Sender) {
	TListView *lvLocal;

	((TMenuItem*)Sender)->Checked = true;
	lvLocal = getListViewAtual();
	lvLocal->ViewStyle = vsReport;
}
// ---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::Lista1Click(TObject *Sender) {
	TListView *lvLocal;

	((TMenuItem*)Sender)->Checked = true;
	lvLocal = getListViewAtual();
	lvLocal->ViewStyle = vsList;
}
// ---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::pageControlChange(TObject *Sender) {
	TListView *lvArquivos;
	lvArquivos = getListViewAtual();
	if (Icones1->Checked)
		lvArquivos->ViewStyle = vsIcon;
	else if (Lista1->Checked)
		lvArquivos->ViewStyle = vsList;
	else if (Detalhes1->Checked)
		lvArquivos->ViewStyle = vsReport;
	else if (IconesPequenos1->Checked)
		lvArquivos->ViewStyle = vsSmallIcon;

	TamTotalDiretorio("");

}
// ---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::lvPesquisaClick(TObject *Sender) {
	EncontrarItemLista();
}
// ---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::MostrarOcultarListaItensPesquisados1Click
	(TObject *Sender)

{
	if (lvPesquisa->Visible == false) {
		lvPesquisa->Visible = true;
		spPesquisa->Visible = true;
	}
	else {
		lvPesquisa->Items->Clear();
		edtPesquisa->Clear();
		lvPesquisa->Visible = false;
		spPesquisa->Visible = false;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::MostrarOcultArvoreDirAbaAtiva1Click
	(TObject *Sender)

{
	TTreeView *tvLocal;
	TSplitter *spLocal;

	tvLocal = getTreeViewAtual(pageControl->ActivePageIndex);
	spLocal = getSplitterAtual();

	if (tvLocal->Visible) {
		tvLocal->Visible = false;
		spLocal->Visible = false;
	}
	else {
		spLocal->Visible = true;
		tvLocal->Visible = true;
	}

}
// ---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::SQL1Click(TObject *Sender) {
	ExportarArquivo(teSQL);
}
// ---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::CSV1Click(TObject *Sender) {
	ExportarArquivo(teCSV);
}
// ---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::XML1Click(TObject *Sender) {
	ExportarArquivo(teXML);
}
// ---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::TXT1Click(TObject *Sender) {
	ExportarArquivo(teTXT);
}
// ---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::HTML1Click(TObject *Sender) {
	ExportarArquivo(teHTML);
}
// ---------------------------------------------------------------------------
void __fastcall TFrmPrincipal::GravarLogImportacao1Click(TObject *Sender)
{
	GravarLogImportacao1->Checked = !GravarLogImportacao1->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::SobreCatalogador1Click(TObject *Sender)
{
	Application->CreateForm(__classid(TFrmSobre), &FrmSobre);
	FrmSobre->ShowModal();
	FrmSobre->Free();
}
//---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::InformacoesDiretorioArquivo1Click(TObject *Sender)
{
  TAba aba;
  TListView *lvArquivos;

  aba = getAbaAtual();
  lvArquivos = getListViewAtual();
  if (lvArquivos->SelCount > 0) {
	Application->CreateForm(__classid(TFrmInfoDiretorio), &FrmInfoDiretorio);
	FrmInfoDiretorio->diretorio.aba.nome = aba.nome;
	FrmInfoDiretorio->diretorio.nome = lvArquivos->Selected->Caption;
	FrmInfoDiretorio->diretorio.tamanhoFormatado = lvArquivos->Selected->SubItems->Strings[0];
	FrmInfoDiretorio->diretorio.tipo.nome = lvArquivos->Selected->SubItems->Strings[1];
	FrmInfoDiretorio->diretorio.modificadoFormatado = lvArquivos->Selected->SubItems->Strings[2];
	FrmInfoDiretorio->diretorio.atributos = lvArquivos->Selected->SubItems->Strings[3];
	FrmInfoDiretorio->diretorio.caminho = lvArquivos->Selected->SubItems->Strings[4];
	FrmInfoDiretorio->ShowModal();
	FrmInfoDiretorio->Free();
  }
}
//---------------------------------------------------------------------------
void TFrmPrincipal::listaColunaClick(TObject *Sender, TListColumn *Column)
{
  colOrdem = Column->Index;
  Column->Tag = Column->Tag * -1;
  if (Column->Tag == 0) Column->Tag = -1;
 ((TCustomListView*)Sender)->AlphaSort();
}
//---------------------------------------------------------------------------
void TFrmPrincipal::listaCompara(TObject *Sender, TListItem *Item1,
	TListItem *Item2, int Data, int &Compare)
{
  int tag = ((TListView*)Sender)->Column[colOrdem]->Tag;

  switch (colOrdem) {
	case 0:  Compare = tag * CompareText(Item1->Caption, Item2->Caption); break;
	case 1:  Compare = tag * CompareText(Item1->SubItems->Strings[colOrdem-1],
	  Item2->SubItems->Strings[colOrdem-1]); break;
	case 2:  Compare = tag * CompareText(Item1->SubItems->Strings[colOrdem-1],
	  Item2->SubItems->Strings[colOrdem-1]); break;
	case 3:  Compare = tag * Rotinas->CompareTextAsDateTime(
		Item1->SubItems->Strings[colOrdem-1],
		Item2->SubItems->Strings[colOrdem-1]); break;
	case 4:  Compare = tag * CompareText(Item1->SubItems->Strings[colOrdem-1],
	  Item2->SubItems->Strings[colOrdem-1]); break;
	case 5:  Compare = tag * CompareText(Item1->SubItems->Strings[colOrdem-1],
	  Item2->SubItems->Strings[colOrdem-1]); break;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFrmPrincipal::lvFixaColumnClick(TObject *Sender, TListColumn *Column)
{
  listaColunaClick(Sender, Column);
}
//---------------------------------------------------------------------------
void __fastcall TFrmPrincipal::lvFixaCompare(TObject *Sender, TListItem *Item1,
	TListItem *Item2, int Data, int &Compare)
{
  listaCompara(Sender, Item1, Item2, Data, Compare);
}
//---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::lvPesquisaColumnClick(TObject *Sender, TListColumn *Column)

{
  listaColunaClick(Sender, Column);
}
//---------------------------------------------------------------------------

void __fastcall TFrmPrincipal::lvPesquisaCompare(TObject *Sender, TListItem *Item1,
		  TListItem *Item2, int Data, int &Compare)
{
  listaCompara(Sender, Item1, Item2, Data, Compare);
}
//---------------------------------------------------------------------------

