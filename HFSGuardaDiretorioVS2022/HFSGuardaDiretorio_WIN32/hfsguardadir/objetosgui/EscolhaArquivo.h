#ifndef ESCOLHAARQUIVO_H
#define ESCOLHAARQUIVO_H

#include "hfsguardadir/comum/String.h"

String EscolhaArquivo_getTextoExtensao(String extensao);
String EscolhaArquivo_abrirDiretorio(HWND pai);
String EscolhaArquivo_abrirArquivo(HWND pai);
String EscolhaArquivo_abrirArquivo(HWND pai, String arquivo, String extensao);
String EscolhaArquivo_salvarArquivo(HWND pai, String arquivo, String extensao);

#endif
