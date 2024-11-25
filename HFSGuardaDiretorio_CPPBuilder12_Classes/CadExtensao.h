// ---------------------------------------------------------------------------

#ifndef CadExtensaoH
#define CadExtensaoH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ExtCtrls.hpp>

// ---------------------------------------------------------------------------
class TFrmCadExtensao : public TForm {
__published: // IDE-managed Components
	TOpenDialog *OpenDialog1;
	TMainMenu *MainMenu1;
	TMenuItem *Extensao1;
	TMenuItem *ExportarTodos1;
	TMenuItem *IncluirExtensao1;
	TMenuItem *ExcluirExtensao1;
	TMenuItem *ExcluirTodasExtensoes1;
	TMenuItem *ExportarBitmap1;
	TMenuItem *ExportarIcone1;
	TMenuItem *ExportarGIF1;
	TMenuItem *ExportarJPEG1;
	TMenuItem *ExportarPNG1;
	TMenuItem *ExportarTIFF1;
	TStringGrid *sgExtensao;
	TMenuItem *ImportarTodos1;
	TMenuItem *ImportarIconesArquivos1;
	TMenuItem *ExtrairIconesArquivos1;
	TPanel *Panel1;
	TButton *btnIncluir;
	TButton *btnExcluir;

	void __fastcall FormShow(TObject *Sender);
	void __fastcall ExcluirExtensao1Click(TObject *Sender);
	void __fastcall IncluirExtensao1Click(TObject *Sender);
	void __fastcall ExcluirTodasExtensoes1Click(TObject *Sender);
	void __fastcall ExportarBitmap1Click(TObject *Sender);
	void __fastcall ExportarIcone1Click(TObject *Sender);
	void __fastcall ExportarGIF1Click(TObject *Sender);
	void __fastcall ExportarJPEG1Click(TObject *Sender);
	void __fastcall ExportarPNG1Click(TObject *Sender);
	void __fastcall ExportarTIFF1Click(TObject *Sender);
	void __fastcall ImportarIconesArquivos1Click(TObject *Sender);
	void __fastcall ExtrairIconesArquivos1Click(TObject *Sender);
	void __fastcall sgExtensaoDrawCell(TObject *Sender, int ACol, int ARow,
		TRect &Rect, TGridDrawState State);

private: // User declarations
	void CarregarExtensoesNaGrid();

public: // User declarations
	__fastcall TFrmCadExtensao(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TFrmCadExtensao *FrmCadExtensao;
// ---------------------------------------------------------------------------
#endif
