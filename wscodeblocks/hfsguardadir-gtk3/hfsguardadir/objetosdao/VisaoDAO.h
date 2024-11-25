#ifndef VISAODAO_H
#define VISAODAO_H

#include "../comum/Rotinas.h"

GString* VisaoDAO_sqlVisao(GString *visao);
gboolean VisaoDAO_criarVisao(GString *visao);

#endif
