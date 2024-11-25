#ifndef DIALOGO_H
#define DIALOGO_H

#include "resource.h"
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosgui {

class Dialogo
{
private:	
	static int MsgDlg(FXWindow* pai, const char* sTitulo, const char* sMensagem);
		
public:
	Dialogo();
	virtual ~Dialogo();
	
	static void mensagemErro2(FXWindow* pai, const char* recurso, const std::string &texto);
	static void mensagemErro(FXWindow* pai, const char* recurso);
	static void mensagemInfo(FXWindow* pai, const char* recurso);
	static bool confirma(FXWindow* pai, const char* recurso);
	static std::string entrada(FXWindow* pai, const char* recurso);
	static std::string entrada2(FXWindow* pai, const char* recurso,
		const std::string &valorInicial);		
};

}
}

#endif
