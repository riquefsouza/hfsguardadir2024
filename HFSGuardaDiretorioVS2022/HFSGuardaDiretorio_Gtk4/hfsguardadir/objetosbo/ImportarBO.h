#ifndef IMPORTARBO_H
#define IMPORTARBO_H

#include "hfsguardadir/objetos/Importar.h"
#include "hfsguardadir/objetos/Extensao.h"
#include "hfsguardadir/objetos/Diretorio.h"
#include "hfsguardadir/objetos/DiretorioOrdem.h"
#include "hfsguardadir/comum/Rotinas.h"

void ImportarBO_CarregarListaDiretorios(Importar importar,
		DiretorioOrdem *dirOrdem, ListaDiretorio *listaDiretorio,
		IProgressoLog progressoLog);
void ImportarBO_ImportacaoCompleta(Importar importar, DiretorioOrdem *dirOrdem,
		ListaExtensao listaExtensao,
		IProgressoLog progressoLog);

#endif
