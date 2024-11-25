#ifndef TIPO_H
#define TIPO_H

#include "hfsguardadir/comum/ListaString.h"

struct STipo {
    char codigo;
	GString* nome;
};
typedef struct STipo* Tipo;

Tipo Tipo_new();
void Tipo_free(Tipo *tipo);
void Tipo_limpar(Tipo tipo);
Tipo Tipo_copiar(const Tipo tipo);
gboolean Tipo_comparar(const Tipo tipo1, const Tipo tipo2);

#endif
