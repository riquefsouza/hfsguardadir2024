#ifndef SOBRE_H
#define SOBRE_H

class FrmSobre : public FXDialogBox {
  FXDECLARE(FrmSobre)

public:
  FrmSobre(FXWindow* owner);
  virtual void create();
  virtual ~FrmSobre();
  static void mostrar(FXWindow* owner);
protected:
  FXGroupBox          *grupo;
  //FXIcon              *bmpLivrusVirtus;
  FXHorizontalFrame   *frameok;

private:
  FrmSobre(){}

  void IniciaControles();
};

extern FrmSobre *frmSobre;

#endif
