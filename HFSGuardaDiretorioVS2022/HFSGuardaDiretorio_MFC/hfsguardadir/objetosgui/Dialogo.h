#ifndef DIALOGO_H
#define DIALOGO_H

#pragma once

namespace hfsguardadir {

namespace objetosgui {

class Dialogo
{
public:
	Dialogo();
	virtual ~Dialogo();
	static void mensagemErro(CWnd *pai, UINT recurso, const CString &texto);
	static void mensagemErro(CWnd *pai, UINT recurso);
	static void mensagemInfo(CWnd *pai, UINT recurso);
	static BOOL confirma(CWnd *pai, UINT recurso);
	static CString entrada(CWnd *pai, UINT recurso);
	static CString entrada(CWnd *pai, UINT recurso, const CString &valorInicial);
};

}
}

#endif
