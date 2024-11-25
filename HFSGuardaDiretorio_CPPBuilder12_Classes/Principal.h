// ---------------------------------------------------------------------------

#ifndef PrincipalH
#define PrincipalH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
#include <System.ImageList.hpp>
#include <vector>
#include "Aba.h"
#include "Extensao.h"
#include "Diretorio.h"
#include "Importar.h"
// ---------------------------------------------------------------------------
class TFrmPrincipal : public TForm {
__published: // IDE-managed Components

	TMainMenu *MainMenu1;
	TMenuItem *Aba1;
	TMenuItem *Diretorio1;
	TMenuItem *IncluirNovaAba1;
	TMenuItem *AlterarNomeAbaAtiva1;
	TMenuItem *ExcluirAbaAtiva1;
	TMenuItem *ExpandirDiretorios1;
	TMenuItem *ColapsarDiretorios1;
	TStatusBar *barraStatus;
	TPanel *panelPesquisa;
	TBitBtn *btnPesquisa;
	TEdit *edtPesquisa;
	TTreeView *tvFixa;
	TSplitter *sp;
	TListView *lvFixa;
	TPageControl *pageControl;
	TTabSheet *TabSheet1;
	TMenuItem *ModoExibicao1;
	TMenuItem *Icones1;
	TMenuItem *Lista1;
	TMenuItem *Detalhes1;
	TMenuItem *IconesPequenos1;
	TMenuItem *ImportarDiretorio1;
	TMenuItem *N1;
	TProgressBar *pb;
	TImageList *ImageList3;
	TImageList *ImageList2;
	TImageList *ImageList1;
	TImageList *ToolbarImages;
	TSplitter *spPesquisa;
	TListView *lvPesquisa;
	TMenuItem *ExportarDiretoriosAbaAtiva1;
	TMenuItem *SQL1;
	TMenuItem *CSV1;
	TMenuItem *XML1;
	TSaveDialog *sdExportar;
	TPopupMenu *PopupMenu1;
	TMenuItem *ExcluirDiretorioSelecionado1;
	TMenuItem *MenuItem1;
	TMenuItem *MenuItem2;
	TMenuItem *Alterarabaativa1;
	TMenuItem *MenuItem3;
	TMenuItem *TXT1;
	TMenuItem *HTML1;
	TMenuItem *Viso1;
	TMenuItem *MostrarOcultArvoreDirAbaAtiva1;
	TMenuItem *MostrarOcultarListaItensPesquisados1;
	TMenuItem *Sobre1;
	TMenuItem *CadastrarExtensaoArquivo1;
	TMenuItem *ImportarDiretoriosViaXML1;
	TOpenDialog *odImportar;
	TButton *btnImportarDiretorio;
	TMenuItem *ImportarSubDiretorios1;
	TMenuItem *ExpandirDiretorios2;
	TMenuItem *ColapsarDiretorios2;
	TMenuItem *GravarLogImportacao1;
	TMenuItem *CompararDiretorios1;
	TMenuItem *SobreCatalogador1;
	TMenuItem *InformacoesDiretorioArquivo1;
	void __fastcall IncluirNovaAba1Click(TObject *Sender);
	void __fastcall tvFixaChange(TObject *Sender, TTreeNode *Node);
	void __fastcall lvFixaDblClick(TObject *Sender);
	void __fastcall CadastrarExtensaoArquivo1Click(TObject *Sender);
	void __fastcall AlterarNomeAbaAtiva1Click(TObject *Sender);
	void __fastcall btnPesquisaClick(TObject *Sender);
	void __fastcall ExcluirAbaAtiva1Click(TObject *Sender);
	void __fastcall ExcluirDiretorioSelecionado1Click(TObject *Sender);
	void __fastcall ExpandirDiretorios1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall ColapsarDiretorios1Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Icones1Click(TObject *Sender);
	void __fastcall IconesPequenos1Click(TObject *Sender);
	void __fastcall ImportarDiretorio1Click(TObject *Sender);
	void __fastcall ImportarDiretoriosViaXML1Click(TObject *Sender);
	void __fastcall ImportarSubDiretorios1Click(TObject *Sender);
	void __fastcall CompararDiretorios1Click(TObject *Sender);
	void __fastcall Detalhes1Click(TObject *Sender);
	void __fastcall Lista1Click(TObject *Sender);
	void __fastcall pageControlChange(TObject *Sender);
	void __fastcall lvPesquisaClick(TObject *Sender);
	void __fastcall MostrarOcultarListaItensPesquisados1Click(TObject *Sender);
	void __fastcall MostrarOcultArvoreDirAbaAtiva1Click(TObject *Sender);
	void __fastcall SQL1Click(TObject *Sender);
	void __fastcall CSV1Click(TObject *Sender);
	void __fastcall XML1Click(TObject *Sender);
	void __fastcall TXT1Click(TObject *Sender);
	void __fastcall HTML1Click(TObject *Sender);
	void __fastcall GravarLogImportacao1Click(TObject *Sender);
	void __fastcall SobreCatalogador1Click(TObject *Sender);
	void __fastcall InformacoesDiretorioArquivo1Click(TObject *Sender);
	void __fastcall lvFixaColumnClick(TObject *Sender, TListColumn *Column);
	void __fastcall lvFixaCompare(TObject *Sender, TListItem *Item1, TListItem *Item2,
          int Data, int &Compare);
	void __fastcall lvPesquisaColumnClick(TObject *Sender, TListColumn *Column);
	void __fastcall lvPesquisaCompare(TObject *Sender, TListItem *Item1, TListItem *Item2,
          int Data, int &Compare);

private: // User declarations
	int colOrdem;
	std::vector<TDiretorio> *listaDiretorioFilho;
	std::vector<TDiretorio> *listaArquivos;

	static void ProgressoLog(TProgresso progresso);
	void CarregarDados(TProgressoLog pLog, boolean bExtensao, boolean bDiretorio);
	void ExcluirDados(TAba aba, String sCaminho);
	void AddItemArvore(TTreeView *tvAba, TDiretorio diretorio, int Nivel,
		TTreeNode *node1);
	void IncluirNovaAba(String nomeAba);
	void CarregarAbas();
	void ListarArquivos(TListView *lvArquivos, TTreeNode *Node);
	void AdicionaItemLista(bool bLista1, TListView *lvArquivos,
		TDiretorio diretorio);
	void CarregarArquivosLista(bool bLista1, TListView *lvArquivos,
		String sCaminho);
	void TamTotalDiretorio(String sCaminho);
	void DuploCliqueLista(TListView *lvLocal, TTreeView *tvLocal);
	TTreeView* getTreeViewAtual(int nIndicePagina);
	TSplitter* getSplitterAtual();
	TListView* getListViewAtual();
	TAba getAbaAtual();
	void Pesquisar(TTreeView *tvLocal);
	TTreeNode* PesquisarArvoreDiretorio(TTreeView *tvLocal, String sCaminhoPai);
	void EncontrarItemLista();
	int verificaNomeDiretorio(String sCaminho, String* sRotuloRaiz);
	void ExportarArquivo(TTipoExportar tipo);
	void ExcluirDiretorioSelecionado();
	void ImportarArquivo(TStrings *log);
	bool ImportarDiretorios(TStringList *listaCaminho, bool bSubDiretorio);
	void ComecaImportacao(bool bSubDiretorios);
	void FinalizaImportacao();

public: // User declarations

	int nGlobalOrdem;

	std::vector<TAba> *listaAbas;
	std::vector<TDiretorio> *listaDiretorioPai;
	std::vector<TExtensao> *listaExtensoes;

	__fastcall TFrmPrincipal(TComponent* Owner);
	void CarregarArvore(TTreeView *tvAba, TAba aba);
	TTreeNode* LerArvoreDiretorio(TTreeNode *MyTreeNode1,
		TStatusBar *barraStatus);
	void CarregarItensLista(bool bLista1, TListView *lvArquivos,
		std::vector<TDiretorio> *listaLocal);
	void listaColunaClick(TObject *Sender, TListColumn *Column);
	void listaCompara(TObject *Sender, TListItem *Item1, TListItem *Item2,
			  int Data, int &Compare);
};

// ---------------------------------------------------------------------------

extern PACKAGE TFrmPrincipal *FrmPrincipal;
// ---------------------------------------------------------------------------
#endif
