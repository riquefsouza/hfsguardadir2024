// ---------------------------------------------------------------------------

#ifndef CompararDiretorioH
#define CompararDiretorioH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <vector>
#include "Aba.h"
#include "Diretorio.h"

// ---------------------------------------------------------------------------
class TFrmCompararDiretorio : public TForm {
__published: // IDE-managed Components

	TGroupBox *gbDiretorio1;
	TComboBox *cmbAba1;
	TTreeView *tvDiretorio1;
	TGroupBox *gbDiretorio2;
	TComboBox *cmbAba2;
	TTreeView *tvDiretorio2;
	TPanel *panelPesquisa;
	TProgressBar *pb;
	TButton *btnCompararDiretorios;
	TButton *btnSalvarLog;
	TListView *lvCompara;
	TStatusBar *barraStatus;
	TLabel *Label1;

	void __fastcall btnCompararDiretoriosClick(TObject *Sender);
	void __fastcall btnSalvarLogClick(TObject *Sender);
	void __fastcall cmbAba1Change(TObject *Sender);
	void __fastcall cmbAba2Change(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall lvComparaCompare(TObject *Sender, TListItem *Item1, TListItem *Item2,
          int Data, int &Compare);
	void __fastcall lvComparaColumnClick(TObject *Sender, TListColumn *Column);

private: // User declarations
	static void ProgressoLog(TProgresso progresso);
public : // User declarations
	std::vector<TDiretorio> *listaCompara;

	__fastcall TFrmCompararDiretorio(TComponent* Owner);
	void LimparComparacao();
	String SQLCompara(TAba aba1, TAba aba2, String caminho1, String caminho2);
	void Comparar(String sCaminhoDir1, String sCaminhoDir2);
};

// ---------------------------------------------------------------------------
extern PACKAGE TFrmCompararDiretorio *FrmCompararDiretorio;
// ---------------------------------------------------------------------------
#endif
