#ifndef DIRETORIO_H
#define DIRETORIO_H

#include "../comum/ListaString.h"
#include "../objetos/Aba.h"
#include "../objetos/Arquivo.h"
#include "../objetos/Tipo.h"

struct SDiretorio {
	Aba aba;
	Arquivo arquivo;
	int codigo;
	int ordem;
	int codDirPai;
	Tipo tipo;
	GString* caminho;
	GString* nomePai;
	GString* caminhoPai;
	GString* tamanhoFormatado;
	GString* modificadoFormatado;
	GString* caminhoOriginal;
};
typedef struct SDiretorio* Diretorio;

typedef GSList* ListaDiretorio;

Diretorio Diretorio_new();
void Diretorio_free(Diretorio *diretorio);
void Diretorio_limpar(Diretorio diretorio);
Diretorio Diretorio_copiar(const Diretorio diretorio);
gboolean Diretorio_comparar(const Diretorio diretorio1, const Diretorio diretorio2);

ListaDiretorio ListaDiretorio_inicia();
void ListaDiretorio_libera(ListaDiretorio *ls);
ListaDiretorio ListaDiretorio_insere(ListaDiretorio ls, Diretorio diretorio, gint posicao);
gboolean ListaDiretorio_removeItem(ListaDiretorio *ls, const Diretorio diretorio);
gboolean ListaDiretorio_removeItemOrd(ListaDiretorio *ls, unsigned int ordem);
void ListaDiretorio_removeTodos(ListaDiretorio *ls);
gboolean ListaDiretorio_pesquisaItem(ListaDiretorio ls, const Diretorio diretorio);
Diretorio ListaDiretorio_pesquisaItemOrd(ListaDiretorio ls, unsigned int ordem);
guint ListaDiretorio_conta(ListaDiretorio ls);

#endif
