#ifndef DIRETORIOORDEM_H
#define DIRETORIOORDEM_H

#include "resource.h"

struct SDiretorioOrdem {
	int ordem;
};
typedef struct SDiretorioOrdem* DiretorioOrdem;

DiretorioOrdem DiretorioOrdem_new();
void DiretorioOrdem_free(DiretorioOrdem *diretorioOrdem);

#endif
