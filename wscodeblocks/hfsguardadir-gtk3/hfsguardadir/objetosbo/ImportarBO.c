#include "ImportarBO.h"

#include "../objetos/Arquivo.h"
#include "../objetosbo/DiretorioBO.h"
#include "../objetosbo/ExtensaoBO.h"

void ImportarBO_CarregarListaDiretorios(Importar importar,
        DiretorioOrdem *dirOrdem, ListaDiretorio *listaDiretorio,
        IProgressoLog progressoLog) {
    Arquivo arquivo = Arquivo_new();
    Diretorio diretorio = Diretorio_new();
    Progresso pb;
	pb.log = g_string_new("");

    arquivo->nome = g_string_new(importar->rotuloRaiz->str);
    arquivo->tamanho = 0;
	arquivo->modificado = Rotinas_DataHoraNow();
	arquivo->atributos = g_string_new("[DIR]");

	diretorio = DiretorioBO_atribuiDiretorio(
            importar->aba, importar->codDirRaiz,
            importar->nomeDirRaiz, g_string_new(""), TRUE, *listaDiretorio,
            arquivo, dirOrdem);

	*listaDiretorio = ListaDiretorio_insere(*listaDiretorio, diretorio,
		diretorio->ordem-1);

	pb.log = g_string_new(importar->caminho->str);

    DiretorioBO_ImportarDiretorio(importar->aba,
            importar->codDirRaiz, importar->nomeDirRaiz,
            importar->caminho, listaDiretorio, dirOrdem, progressoLog);

	if (progressoLog != NULL) {
        progressoLog(pb);
    }
}

void ImportarBO_ImportacaoCompleta(Importar importar, DiretorioOrdem *dirOrdem,
        ListaExtensao listaExtensao,
        IProgressoLog progressoLog) {
    ListaDiretorio listaDiretorio = ListaDiretorio_inicia();

	ImportarBO_CarregarListaDiretorios(importar, dirOrdem, &listaDiretorio, progressoLog);

    //ExtensaoBO_salvarExtensoes(listaDiretorio, listaExtensao, progressoLog);

    DiretorioBO_salvarDiretorio(listaDiretorio, progressoLog);

	ListaDiretorio_removeTodos(&listaDiretorio);
}
