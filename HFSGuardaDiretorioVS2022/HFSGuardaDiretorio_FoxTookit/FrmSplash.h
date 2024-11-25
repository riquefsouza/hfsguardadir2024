#ifndef SPLASH_H
#define SPLASH_H

#include "hfsguardadir/comum/Rotinas.h"

class FrmSplash : public FXMainWindow {
  FXDECLARE(FrmSplash)

public:
  enum { PB_SPLASH = FXMainWindow::ID_LAST };

  FrmSplash(FXApp* owner);
  virtual void create();
  virtual ~FrmSplash();
  //long onTimer(FXObject*,FXSelector,void*);
  //void iniciaTimer();
  static void Mostrar(FXApp* app);
  static void Fechar();
  static void ProgressoLog(Progresso progresso);

protected:
  //FXIcon   *bmpLivrusVirtus;
  //FXTimer  *mTimer;
	FXLabel *label;
	FXLabel *label2;
	FXProgressBar *pb1;

private:
  FrmSplash(){}

  void IniciaControles();
};

extern FrmSplash *frmSplash;

#endif
