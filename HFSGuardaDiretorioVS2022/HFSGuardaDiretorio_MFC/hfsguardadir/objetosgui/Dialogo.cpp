#include "stdafx.h"
#include "hfsguardadir\objetosgui\Dialogo.h"
#include "resource.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "FrmEntrada.h"

using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosgui {

Dialogo::Dialogo()
{
}


Dialogo::~Dialogo()
{
}

void Dialogo::mensagemErro(CWnd *pai, UINT recurso, const CString &texto) {
	WCHAR log[TAM_MAX_STR], msg[TAM_MAX_STR], titulo[TAM_MAX_STR];
	log[0] = '\0';
	msg[0] = '\0';
	titulo[0] = '\0';

	lstrcpy(msg, Rotinas::lerStr(recurso));
	lstrcat(msg, _T(" "));
	lstrcat(msg, texto);
	lstrcpy(titulo, Rotinas::lerStr(STR_DIALOGO_ERRO));

	pai->MessageBox(msg, titulo, MB_ICONERROR | MB_OK);

	wsprintf(log, _T("warning: %s\n"), msg);
	OutputDebugString(log);
}

void Dialogo::mensagemErro(CWnd *pai, UINT recurso) {
	Dialogo::mensagemErro(pai, recurso, _T(""));
}

void Dialogo::mensagemInfo(CWnd *pai, UINT recurso) {
	WCHAR log[TAM_MAX_STR], msg[TAM_MAX_STR], titulo[TAM_MAX_STR];
	log[0] = '\0';
	msg[0] = '\0';
	titulo[0] = '\0';

	lstrcpy(msg, Rotinas::lerStr(recurso));
	lstrcpy(titulo, Rotinas::lerStr(STR_DIALOGO_INFO));

	pai->MessageBox(msg, titulo, MB_ICONINFORMATION | MB_OK);

	wsprintf(log, _T("info: %s\n"), msg);
	OutputDebugString(log);
}

BOOL Dialogo::confirma(CWnd *pai, UINT recurso) {
	WCHAR msg[TAM_MAX_STR], titulo[TAM_MAX_STR];
	msg[0] = '\0';
	titulo[0] = '\0';

	lstrcpy(msg, Rotinas::lerStr(recurso));
	lstrcpy(titulo, Rotinas::lerStr(STR_DIALOGO_CONFIRMA));
	return (pai->MessageBox(msg, titulo, MB_ICONQUESTION | MB_YESNO) == IDYES);
}

CString Dialogo::entrada(CWnd *pai, UINT recurso) {
	return Dialogo::entrada(pai, recurso, _T(""));
}

CString Dialogo::entrada(CWnd *pai, UINT recurso,
	const CString &valorInicial) {
	WCHAR titulo[TAM_MAX_STR], rotulo[TAM_MAX_STR];
	titulo[0] = '\0';
	rotulo[0] = '\0';

	CString texto = _T("");
	lstrcpy(titulo, Rotinas::lerStr(STR_DIALOGO_ENTRADA));
	lstrcpy(rotulo, Rotinas::lerStr(recurso));

	texto = FrmEntrada::Mostrar(pai, titulo, rotulo, valorInicial);

	return texto;
}

}
}