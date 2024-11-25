#include "stdafx.h"

#include "Tipo.h"

Tipo Tipo_copiar(Tipo tipo) {
	Tipo ltipo;
	ltipo.codigo = tipo.codigo;
	ltipo.nome = String_copiar(tipo.nome);

	return ltipo;
}

BOOL Tipo_comparar(Tipo tipo1, Tipo tipo2) {
	return
		(tipo1.codigo == tipo2.codigo
		&& String_comparar(tipo1.nome, tipo2.nome));
}
