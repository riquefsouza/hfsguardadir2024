#include "resource.h"
#include "FrmSplash.h"
#include <FXUTF8Codec.h>

FrmSplash *frmSplash = (FrmSplash *) NULL;
/*
FXDEFMAP(FrmSplash) FrmSplashMap[]={
  FXMAPFUNC(SEL_TIMEOUT, FrmSplash::PB_SPLASH, FrmSplash::onTimer)
};
FXIMPLEMENT(FrmSplash,FXDialogBox,FrmSplashMap,ARRAYNUMBER(FrmSplashMap))
*/

FXIMPLEMENT(FrmSplash, FXMainWindow, NULL, 0)

FrmSplash::FrmSplash(FXApp* owner):
	FXMainWindow(owner, "Splash", NULL, NULL, DECOR_NONE, 0, 0, 375, 113) {
	//FXWindow(owner, DECOR_NONE, 0, 0, 375, 113){
	//FXDialogBox(owner, "Splash", DECOR_NONE, 0, 0, 375, 113, 0, 0, 0, 0, 4, 4){
  IniciaControles();
}

void FrmSplash::IniciaControles() {
  //bmpLivrusVirtus = new FXBMPIcon(getApp(), splash);  
  //new FXLabel(this, "", bmpLivrusVirtus, LAYOUT_CENTER_X); 
	label = new FXLabel(this, "HFSGuardaDiretorio 2.0", NULL, LAYOUT_CENTER_X);
	FXFont *fonte20 = new FXFont(getApp(), label->getFont()->getFamily(), 20, FXFont::Bold);
	label->setFont(fonte20);
		
	//FXUTF8Codec *uc = new FXUTF8Codec();
	label2 = new FXLabel(this, "Catalogador de Diretórios", NULL, LAYOUT_CENTER_X);
	FXFont *fonte15 = new FXFont(getApp(), label2->getFont()->getFamily(), 15, FXFont::Bold);
	label2->setFont(fonte15);

	pb1 = new FXProgressBar(this, this, PB_SPLASH, FRAME_SUNKEN | LAYOUT_FILL_X | LAYOUT_FIX_HEIGHT);
	pb1->setHeight(20);
	pb1->setTotal(100);
	pb1->setProgress(80);
}

void FrmSplash::create(){
	FXMainWindow::create();
}
/*
void FrmSplash::iniciaTimer(){
  getApp()->addTimeout(this, ID_FRMSPLASH_TIMER, 1000);
}
*/
FrmSplash::~FrmSplash(){
	delete label;
	delete label2;
	delete pb1;

  //delete bmpLivrusVirtus;
  //getApp()->removeTimeout(this, ID_FRMSPLASH_TIMER);
}
/*
long FrmSplash::onTimer(FXObject*,FXSelector,void*) {
  mTimer = NULL;
  frmPrincipal->show(PLACEMENT_SCREEN);
  this->close();
  return true;
}
*/

// ---------------------------------------------------------------------------
void FrmSplash::Mostrar(FXApp* app)
{
	frmSplash = new FrmSplash(app);
	frmSplash->show(PLACEMENT_SCREEN);
}

void FrmSplash::Fechar()
{
	frmSplash->hide();
}

void FrmSplash::ProgressoLog(Progresso progresso)
{
	if (frmSplash != NULL) {
		if (progresso.posicao == 0) {
			frmSplash->pb1->setProgress(progresso.minimo);
		}
		frmSplash->pb1->setProgress(
			Rotinas::calculaProgresso(progresso.maximo, progresso.posicao));
	}
}
