#ifndef DIALOGO_H
#define DIALOGO_H

#include "hfsguardadir/comum/String.h"

void Dialogo_mensagemErro(HWND pai, UINT recurso, String texto);
void Dialogo_mensagemErro(HWND pai, UINT recurso);
void Dialogo_mensagemInfo(HWND pai, UINT recurso);
BOOL Dialogo_confirma(HWND pai, UINT recurso);
String Dialogo_entrada(HWND pai, UINT recurso);
String Dialogo_entrada(HWND pai, UINT recurso,
	String valorInicial);

#endif
