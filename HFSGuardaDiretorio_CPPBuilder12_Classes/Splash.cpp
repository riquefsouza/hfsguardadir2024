// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Splash.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmSplash *FrmSplash;

// ---------------------------------------------------------------------------
__fastcall TFrmSplash::TFrmSplash(TComponent* Owner) : TForm(Owner) {
}
// ---------------------------------------------------------------------------
void TFrmSplash::ProgressoLog(TProgresso progresso)
{
  if (FrmSplash!=NULL) {
	  if (progresso.posicao == 0) {
		 FrmSplash->pb->Min = progresso.minimo;
		 FrmSplash->pb->Max = progresso.maximo;
		 FrmSplash->pb->Step = progresso.passo;
	  }

	  FrmSplash->pb->Position = progresso.posicao;
  }
}
// ---------------------------------------------------------------------------
