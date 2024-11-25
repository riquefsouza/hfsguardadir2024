#include "Tipo.h"

Tipo Tipo_new() {
	Tipo tipo;
	tipo = (Tipo)malloc(sizeof(struct STipo));

	Tipo_limpar(tipo);

	return(tipo);
}

void Tipo_limpar(Tipo tipo) {
	tipo->codigo = 0;
	tipo->nome = g_string_new("");
}

void Tipo_free(Tipo *tipo) {
	g_string_free((*tipo)->nome, TRUE);
	free(*tipo);
	*tipo = NULL;
}

Tipo Tipo_copiar(const Tipo tipo) {
	Tipo ltipo = Tipo_new();

	ltipo->codigo = tipo->codigo;
	ltipo->nome = g_string_new(tipo->nome->str);

	return ltipo;
}

gboolean Tipo_comparar(const Tipo tipo1, const Tipo tipo2) {
	return
		(tipo1->codigo == tipo2->codigo
		&& g_string_equal(tipo1->nome, tipo2->nome));
}
