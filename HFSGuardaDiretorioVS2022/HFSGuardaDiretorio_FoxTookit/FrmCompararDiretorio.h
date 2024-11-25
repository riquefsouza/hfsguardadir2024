#ifndef COMPARARDIRETORIO_H
#define COMPARARDIRETORIO_H

#include "hfsguardadir/objetosgui/Arvore.h"
#include "hfsguardadir/objetosgui/Tabela.h"
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::comum;
using namespace hfsguardadir::objetosgui;

class FrmCompararDiretorio : public FXDialogBox {
  FXDECLARE(FrmCompararDiretorio)

public:
  enum { BTN_COMPARARDIRETORIOS = FXDialogBox::ID_LAST,
	  BTN_SALVARLOG, CMB_ABA1, CMB_ABA2, PB_COMPARAR, TABELA_COMPARA,
	  ARVORE_DIR1, ARVORE_DIR2
  };

  FXProgressBar *pb2;

  FrmCompararDiretorio(FXWindow* owner);
  virtual void create();
  virtual ~FrmCompararDiretorio();

  static void mostrar(FXWindow* owner);
  static void ProgressoLog(Progresso progresso);

  long on_btnCompararDiretorios_clicked(FXObject* obj, FXSelector sel, void* ptr);
  long on_btnSalvarLog_clicked(FXObject* obj, FXSelector sel, void* ptr);
  long on_cmbAba1_changed(FXObject* obj, FXSelector sel, void* ptr);
  long on_cmbAba2_changed(FXObject* obj, FXSelector sel, void* ptr);
  long on_tvDiretorio1_LeftBtnPress(FXObject* obj, FXSelector sel, void* ptr);
  long on_tvDiretorio2_LeftBtnPress(FXObject* obj, FXSelector sel, void* ptr);

protected:
	FXHorizontalFrame *barraComparar;
	FXButton *btnCompararDiretorios;
	FXButton *btnSalvarLog;

	FXVerticalFrame *framePrincipal;
	FXHorizontalFrame *frameArvores;

	FXGroupBox *grupo1;
	FXComboBox *cmbAba1;
	Arvore *tvDiretorio1;

	FXGroupBox *grupo2;
	FXComboBox *cmbAba2;
	Arvore *tvDiretorio2;
	FXLabel *labDiferencasEncontradas;
	Tabela *tabelaCompara;

	FXHorizontalFrame *frameStatus;
	FXLabel    *labStatus;
	FXStatusBar *barraStatus;

	std::vector<Diretorio> listaCompara;

private:
  FrmCompararDiretorio(){}

  void CarregarDados();
  void LimparComparacao();
  std::string SQLCompara(Aba aba1, Aba aba2, const std::string caminho1, const std::string caminho2);
  void Comparar(const std::string sCaminhoDir1, const std::string sCaminhoDir2);

};

extern FrmCompararDiretorio *frmCompararDiretorio;

#endif
