#include "RotuloRaiz.h"

RotuloRaiz RotuloRaiz_new() {
	RotuloRaiz rotuloRaiz;
	rotuloRaiz = (RotuloRaiz)malloc(sizeof(struct SRotuloRaiz));

	RotuloRaiz_limpar(rotuloRaiz);

	return(rotuloRaiz);
}

void RotuloRaiz_limpar(RotuloRaiz rotuloRaiz) {
	rotuloRaiz->rotulo = g_string_new("");
}

void RotuloRaiz_free(RotuloRaiz *rotuloRaiz) {
	g_string_free((*rotuloRaiz)->rotulo, TRUE);
	free(*rotuloRaiz);
	*rotuloRaiz = NULL;
}
