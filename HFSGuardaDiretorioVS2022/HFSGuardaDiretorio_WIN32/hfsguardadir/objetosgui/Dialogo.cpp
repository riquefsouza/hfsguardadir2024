#include "stdafx.h"

#include "Dialogo.h"
#include "resource.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "FrmEntrada.h"

void Dialogo_mensagemErro(HWND pai, UINT recurso, String texto) {
	WCHAR log[TAM_MAX_STR], msg[TAM_MAX_STR], titulo[TAM_MAX_STR];
	log[0] = '\0';
	msg[0] = '\0';
	titulo[0] = '\0';

	lstrcpy(msg, Rotinas_lerStr(recurso));
	lstrcat(msg, _T(" "));
	lstrcat(msg, texto.wstr);
	lstrcpy(titulo, Rotinas_lerStr(STR_DIALOGO_ERRO));
	
	MessageBox(pai, msg, titulo, MB_ICONERROR | MB_OK);

	wsprintf(log, _T("warning: %s\n"), msg); 
	OutputDebugString(log);
}

void Dialogo_mensagemErro(HWND pai, UINT recurso) {
	Dialogo_mensagemErro(pai, recurso, String_iniciar(""));
}

void Dialogo_mensagemInfo(HWND pai, UINT recurso) {
	WCHAR log[TAM_MAX_STR], msg[TAM_MAX_STR], titulo[TAM_MAX_STR];
	log[0] = '\0';
	msg[0] = '\0';
	titulo[0] = '\0';

	lstrcpy(msg, Rotinas_lerStr(recurso));
	lstrcpy(titulo, Rotinas_lerStr(STR_DIALOGO_INFO));

	MessageBox(pai, msg, titulo, MB_ICONINFORMATION | MB_OK);

	wsprintf(log, _T("info: %s\n"), msg);
	OutputDebugString(log);
}

BOOL Dialogo_confirma(HWND pai, UINT recurso) {
	WCHAR msg[TAM_MAX_STR], titulo[TAM_MAX_STR];
	msg[0] = '\0';
	titulo[0] = '\0';

	lstrcpy(msg, Rotinas_lerStr(recurso));
	lstrcpy(titulo, Rotinas_lerStr(STR_DIALOGO_CONFIRMA));
	return (MessageBox(pai, msg, titulo, MB_ICONQUESTION | MB_YESNO) == IDYES);
}

String Dialogo_entrada(HWND pai, UINT recurso) {
	return Dialogo_entrada(pai, recurso, String_iniciar(""));
}

String Dialogo_entrada(HWND pai, UINT recurso,
        String valorInicial) {
	WCHAR titulo[TAM_MAX_STR], rotulo[TAM_MAX_STR];
	titulo[0] = '\0';
	rotulo[0] = '\0';

	String texto = String_iniciar("");
	lstrcpy(titulo, Rotinas_lerStr(STR_DIALOGO_ENTRADA));
	lstrcpy(rotulo, Rotinas_lerStr(recurso));

	texto = FrmEntrada_Mostrar(pai, titulo, rotulo, valorInicial.wstr);

	return texto;
}
