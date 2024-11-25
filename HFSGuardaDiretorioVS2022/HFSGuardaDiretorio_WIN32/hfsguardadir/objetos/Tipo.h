#ifndef TIPO_H
#define TIPO_H

#include "hfsguardadir/comum/ListaString.h"

struct STipo {
    char codigo;
	String nome;
};
typedef struct STipo Tipo;

Tipo Tipo_copiar(Tipo tipo);
BOOL Tipo_comparar(Tipo tipo1, Tipo tipo2);

#endif
