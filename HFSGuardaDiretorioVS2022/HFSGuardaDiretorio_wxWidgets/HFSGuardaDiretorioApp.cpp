#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "HFSGuardaDiretorioApp.h"
#include "FrmPrincipal.h"
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::comum;

IMPLEMENT_APP(HFSGuardaDiretorioApp);

bool HFSGuardaDiretorioApp::OnInit()
{
    frmPrincipal = new FrmPrincipal(0L);

	catalogador = new Catalogador();

    frmPrincipal->SetIcon(wxICON(aaaa));
	frmPrincipal->Show();

	//Rotinas::getInstancia()->testar();
	
    return true;
}
