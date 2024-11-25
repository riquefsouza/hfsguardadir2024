#include "stdafx.h"

#include "ImportarBO.h"

#include "hfsguardadir/objetos/Arquivo.h"
#include "hfsguardadir/objetosbo/DiretorioBO.h"
#include "hfsguardadir/objetosbo/ExtensaoBO.h"

using namespace hfsguardadir::objetosbo;

namespace hfsguardadir {

namespace objetosbo {

ImportarBO* ImportarBO::instancia = NULL;

ImportarBO::ImportarBO()
{

}

ImportarBO::ImportarBO(ImportarBO const&) {

}

ImportarBO& ImportarBO::operator=(ImportarBO const&) {
	return *instancia;
}

ImportarBO* ImportarBO::getInstancia() {
	if (!instancia) {
		instancia = new ImportarBO();
	}
	return instancia;
}

void ImportarBO::CarregarListaDiretorios(Importar importar,
        DiretorioOrdem *dirOrdem, CList<Diretorio, Diretorio&> *listaDiretorio,
        IProgressoLog progressoLog) {
    Arquivo arquivo;
    Diretorio diretorio;
    Progresso pb;
	pb.log = _T("");
	
    arquivo.setNome(importar.getRotuloRaiz());
    arquivo.setTamanho(0);
	arquivo.setModificado(CTime::GetCurrentTime());
	arquivo.setAtributos(_T("[DIR]"));
		
    diretorio = DiretorioBO::getInstancia()->atribuiDiretorio(
            importar.getAba(), importar.getCodDirRaiz(),
            importar.getNomeDirRaiz(), _T(""), TRUE, *listaDiretorio,
            arquivo, dirOrdem);

	listaDiretorio->AddTail(diretorio);
	pb.log = importar.getCaminho();

    DiretorioBO::getInstancia()->ImportarDiretorio(importar.getAba(),
            importar.getCodDirRaiz(), importar.getNomeDirRaiz(),
            importar.getCaminho(), listaDiretorio, dirOrdem, progressoLog);
	
	if (progressoLog != NULL) {
        progressoLog(pb);
    }
}

void ImportarBO::ImportacaoCompleta(Importar importar, DiretorioOrdem *dirOrdem,
	CList<Extensao, Extensao&> &listaExtensao,
        IProgressoLog progressoLog) {
	CList<Diretorio, Diretorio&> listaDiretorio;

	CarregarListaDiretorios(importar, dirOrdem, &listaDiretorio, progressoLog);

    ExtensaoBO::getInstancia()->salvarExtensoes(listaDiretorio, listaExtensao, progressoLog);

    DiretorioBO::getInstancia()->salvarDiretorio(listaDiretorio, progressoLog);

	listaDiretorio.RemoveAll();
}

}
}
