#ifndef FRMENTRADA_H
#define FRMENTRADA_H

#include "hfsguardadir/comum/String.h"

LRESULT CALLBACK frmEntradaProc( HWND hDlg, UINT uMsg, WPARAM wParam, 
    LPARAM lParam );
String FrmEntrada_Mostrar(HWND hwnd, LPCWSTR titulo, LPCWSTR rotulo, LPCWSTR texto);

#endif


