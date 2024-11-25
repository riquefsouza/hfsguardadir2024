#ifndef INFODIRETORIO_H
#define INFODIRETORIO_H

#include "hfsguardadir/objetos/Diretorio.h"

using namespace hfsguardadir::objetos;

class FrmInfoDiretorio : public FXDialogBox {
  FXDECLARE(FrmInfoDiretorio)

public:
  enum { BTN_OK = FXDialogBox::ID_LAST,
	  TABELA_INFO
  };

  FrmInfoDiretorio(FXWindow* owner);
  virtual void create();
  virtual ~FrmInfoDiretorio();
  static void Mostrar(FXWindow* owner);
  void setDiretorio(Diretorio diretorio);

  long on_btnOk_clicked(FXObject* obj, FXSelector sel, void* ptr);


protected:
	FXGroupBox *grupo;
	FXMatrix *matrix;
	FXLabel *labArquivoComum;
	FXLabel *labArquivoOculto;
	FXLabel *labArquivoSistema;
	FXLabel *labLegendaDiretorio;
	FXLabel *labVolumeID;
	FXLabel *labArquivoSomenteLeitura;
	FXTable *tabelaInfo;
	FXButton *btnOk;

private:
  FrmInfoDiretorio(){}
  void ConstruirGrid();
};

extern FrmInfoDiretorio *frmInfoDiretorio;

#endif
