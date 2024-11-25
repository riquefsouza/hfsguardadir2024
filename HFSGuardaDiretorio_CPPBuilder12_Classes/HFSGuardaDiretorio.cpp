// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include "Splash.h"
// ---------------------------------------------------------------------------
USEFORM("ImportarDiretorio.cpp", FrmImportarDiretorio);
USEFORM("Sobre.cpp", FrmSobre);
USEFORM("Splash.cpp", FrmSplash);
USEFORM("Principal.cpp", FrmPrincipal);
USEFORM("CadExtensao.cpp", FrmCadExtensao);
USEFORM("CompararDiretorio.cpp", FrmCompararDiretorio);
USEFORM("EscolherDir.cpp", FrmEscolherDir);
USEFORM("DataModule.cpp", dm); /* TDataModule: File Type */
USEFORM("InfoDiretorio.cpp", FrmInfoDiretorio);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int) {
	try {
		Application->Initialize();
		Application->MainFormOnTaskBar = true;

		// Application->CreateForm(__classid(TFrmSplash), &FrmSplash);
		FrmSplash = new TFrmSplash(Application);
		FrmSplash->Show();
		FrmSplash->Update();

		Application->CreateForm(__classid(TFrmPrincipal), &FrmPrincipal);
		Application->CreateForm(__classid(Tdm), &dm);
		Application->Run();
	}
	catch (Exception &exception) {
		Application->ShowException(&exception);
	}
	catch (...) {
		try {
			throw Exception("");
		}
		catch (Exception &exception) {
			Application->ShowException(&exception);
		}
	}
	return 0;
}
// ---------------------------------------------------------------------------
