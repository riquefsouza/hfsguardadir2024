#ifndef IMPORTARBO_H
#define IMPORTARBO_H

#include "../objetos/Importar.h"
#include "../objetos/Extensao.h"
#include "../objetos/Diretorio.h"
#include "../objetos/DiretorioOrdem.h"
#include "../comum/Rotinas.h"

void ImportarBO_CarregarListaDiretorios(Importar importar,
		DiretorioOrdem *dirOrdem, ListaDiretorio *listaDiretorio,
		IProgressoLog progressoLog);
void ImportarBO_ImportacaoCompleta(Importar importar, DiretorioOrdem *dirOrdem,
		ListaExtensao listaExtensao,
		IProgressoLog progressoLog);

#endif
