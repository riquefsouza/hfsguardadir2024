#include "resource.h"
#include "FrmSobre.h"

FrmSobre *frmSobre = (FrmSobre *) NULL;

FXIMPLEMENT(FrmSobre,FXDialogBox,NULL,0)

FrmSobre::FrmSobre(FXWindow* owner):
  FXDialogBox(owner, "Sobre o Catalogador", DECOR_TITLE | DECOR_CLOSE, 
    0, 0, 0, 0, 0, 0, 0, 0, 4, 4){
  IniciaControles();
}

void FrmSobre::IniciaControles() {
  //this->setIcon(new FXBMPIcon(getApp(), cdouro));

  grupo = new FXGroupBox(this, "",
  GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X);

  //bmpLivrusVirtus = new FXBMPIcon(getApp(), splash);
  FXLabel *label = new FXLabel(grupo, "HFSGuardaDir 2.0 - Catalogador de Diretórios", NULL, LAYOUT_CENTER_X);
  FXFont *fonte = new FXFont(getApp(), label->getFont()->getFamily(), 12, FXFont::Bold);
  label->setFont(fonte);

  new FXLabel(grupo, "Desenvolvido em C++ com a FOXToolKit, Versão: 2.0", NULL, LAYOUT_CENTER_X);
  new FXLabel(grupo, "Por Henrique Figueiredo de Souza", 
    NULL, LAYOUT_CENTER_X);
  new FXLabel(grupo, "Todos os direitos reservados, 2024",
    NULL, LAYOUT_CENTER_X);
  
  frameok = new FXHorizontalFrame(this,
    LAYOUT_BOTTOM|LAYOUT_FILL_X|PACK_UNIFORM_WIDTH);
  new FXButton(frameok, "&Ok", NULL, this, FXDialogBox::ID_CANCEL,
    LAYOUT_CENTER_X|FRAME_RAISED|FRAME_THICK, 0, 0, 0, 0, 30, 30);
}

void FrmSobre::create(){
  FXDialogBox::create();
  show(PLACEMENT_SCREEN);
}

FrmSobre::~FrmSobre(){
  delete grupo;
  //delete bmpLivrusVirtus;
  delete frameok;
}

void FrmSobre::mostrar(FXWindow* owner)
{
    frmSobre = new FrmSobre(owner);
    frmSobre->execute(PLACEMENT_SCREEN);
}
