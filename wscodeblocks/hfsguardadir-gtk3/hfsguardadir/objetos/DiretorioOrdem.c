#include "DiretorioOrdem.h"

DiretorioOrdem DiretorioOrdem_new() {
	DiretorioOrdem diretorioOrdem;
	diretorioOrdem = (DiretorioOrdem)malloc(sizeof(struct SDiretorioOrdem));

	return(diretorioOrdem);
}

void DiretorioOrdem_free(DiretorioOrdem *diretorioOrdem) {
	free(*diretorioOrdem);
	*diretorioOrdem = NULL;
}
