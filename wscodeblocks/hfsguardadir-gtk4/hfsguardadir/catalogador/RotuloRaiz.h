#ifndef ROTULORAIZ_H
#define ROTULORAIZ_H

#include "../../resource.h"

struct SRotuloRaiz {
	GString* rotulo;
};
typedef struct SRotuloRaiz* RotuloRaiz;

RotuloRaiz RotuloRaiz_new();
void RotuloRaiz_limpar(RotuloRaiz rotuloRaiz);
void RotuloRaiz_free(RotuloRaiz *rotuloRaiz);

#endif
