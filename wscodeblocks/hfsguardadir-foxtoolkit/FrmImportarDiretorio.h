#ifndef IMPORTARDIRETORIO_H
#define IMPORTARDIRETORIO_H

#include <FXText.h>
#include "hfsguardadir/objetos/Diretorio.h"
#include "hfsguardadir/objetos/Importar.h"
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

class FrmImportarDiretorio : public FXDialogBox {
  FXDECLARE(FrmImportarDiretorio)

public:
  enum { BTN_OK = FXDialogBox::ID_LAST, PB_IMPORTAR };

  bool bSubDiretorio;
  FXText* memoImportaDir;
  FXProgressBar* pbImportar;
  std::vector<Importar> listaImportar;

  FrmImportarDiretorio(FXWindow* owner);
  virtual void create();
  virtual ~FrmImportarDiretorio();

  FXLabel* labStatus;

  static void Mostrar();
  static void Fechar();
  static void ProgressoLog(Progresso progresso);
  void ImportarDir();

protected:
	FXHorizontalFrame* frameStatus;
	FXStatusBar* barraStatus;
	FXVerticalFrame* form_vbox1;

private:
  FrmImportarDiretorio(){}

};

extern FrmImportarDiretorio *frmImportarDiretorio;

#endif
