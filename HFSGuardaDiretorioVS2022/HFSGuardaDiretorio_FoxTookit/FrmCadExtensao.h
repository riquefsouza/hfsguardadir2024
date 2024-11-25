#ifndef CADEXTENSAO_H
#define CADEXTENSAO_H

class FrmCadExtensao : public FXDialogBox {
  FXDECLARE(FrmCadExtensao)

public:
  enum {
	  MENU_INCLUIREXTENSAO = FXDialogBox::ID_LAST,	  
	  MENU_EXCLUIREXTENSAO,
	  MENU_EXCLUIRTODASEXTENSOES,
	  MENU_EXPORTARBITMAP,
	  MENU_EXPORTARICONE,
	  MENU_EXPORTARGIF,
	  MENU_EXPORTARJPEG,
	  MENU_EXPORTARPNG,
	  MENU_EXPORTARTIFF,
	  MENU_IMPORTARICONESARQUIVOS,
	  MENU_EXTRAIRICONESARQUIVOS,
	  TABELA_EXTENSAO,
	  BTN_INCLUIR,
	  BTN_EXCLUIR
  };

  FrmCadExtensao(FXWindow* owner);
  virtual void create();
  virtual ~FrmCadExtensao();
  static void mostrar(FXWindow* owner);

  long on_menuIncluirExtensao(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuExcluirExtensao(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuExcluirTodasExtensoes(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuExportarBitmap(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuExportarIcone(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuExportarGIF(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuExportarJPEG(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuExportarPNG(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuExportarTIFF(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuImportarIconesArquivos(FXObject* obj, FXSelector sel, void* ptr);
  long on_menuExtrairIconesArquivos(FXObject* obj, FXSelector sel, void* ptr);
  long on_btnIncluir_clicked(FXObject* obj, FXSelector sel, void* ptr);
  long on_btnExcluir_clicked(FXObject* obj, FXSelector sel, void* ptr);

protected:
	FXMenuBar  *barraMenu;
	FXMenuPane *menuExtensao;	
	FXMenuCommand *menuIncluirExtensao;
	FXMenuCommand *menuExcluirExtensao;
	FXMenuCommand *menuExcluirTodasExtensoes;
	
	FXMenuPane *menuExportarTodos;	
	FXMenuCommand *menuExportarBitmap;
	FXMenuCommand *menuExportarIcone;
	FXMenuCommand *menuExportarGIF;
	FXMenuCommand *menuExportarJPEG;
	FXMenuCommand *menuExportarPNG;
	FXMenuCommand *menuExportarTIFF;

	FXMenuPane *menuImportarTodos;
	FXMenuCommand *menuImportarIconesArquivos;
	FXMenuCommand *menuExtrairIconesArquivos;
	FXTable *tabelaExtensao;
	FXButton *btnIncluir;
	FXButton *btnExcluir;

private:
  FrmCadExtensao(){}

  void definirColunas(int numRows);
  void CarregarExtensoesNaGrid();
  void limparTabelaExtensao();
};

extern FrmCadExtensao *frmCadExtensao;

#endif
