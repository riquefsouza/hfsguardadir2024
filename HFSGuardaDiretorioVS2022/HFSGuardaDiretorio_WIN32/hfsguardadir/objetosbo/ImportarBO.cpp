#include "stdafx.h"

#include "ImportarBO.h"

#include "hfsguardadir/objetos/Arquivo.h"
#include "hfsguardadir/objetosbo/DiretorioBO.h"
#include "hfsguardadir/objetosbo/ExtensaoBO.h"

void ImportarBO_CarregarListaDiretorios(Importar importar,
        DiretorioOrdem *dirOrdem, ListaDiretorio *listaDiretorio,
        IProgressoLog progressoLog) {
    Arquivo arquivo;
    Diretorio diretorio;
    Progresso pb;
	pb.log = String_iniciar("");
	
    arquivo.nome = String_copiar(importar.rotuloRaiz);
    arquivo.tamanho = 0;
	arquivo.modificado = Rotinas_DataHoraNow();
	arquivo.atributos = String_copiar("[DIR]");

	
    diretorio = DiretorioBO_atribuiDiretorio(
            importar.aba, importar.codDirRaiz,
            importar.nomeDirRaiz, String_iniciar(""), TRUE, *listaDiretorio,
            arquivo, dirOrdem);

	ListaDiretorio_insereFim(listaDiretorio, diretorio);
	pb.log = String_copiar(importar.caminho);

    DiretorioBO_ImportarDiretorio(importar.aba,
            importar.codDirRaiz, importar.nomeDirRaiz,
            importar.caminho, listaDiretorio, dirOrdem, progressoLog);
	
	if (progressoLog != NULL) {
        progressoLog(pb);
    }
}

void ImportarBO_ImportacaoCompleta(Importar importar, DiretorioOrdem *dirOrdem,
        ListaExtensao listaExtensao,
        IProgressoLog progressoLog) {
    ListaDiretorio listaDiretorio = ListaDiretorio_inicia();

	ImportarBO_CarregarListaDiretorios(importar, dirOrdem, &listaDiretorio, progressoLog);

    ExtensaoBO_salvarExtensoes(listaDiretorio, listaExtensao, progressoLog);

    DiretorioBO_salvarDiretorio(listaDiretorio, progressoLog);

	ListaDiretorio_removeTodos(&listaDiretorio);
}
