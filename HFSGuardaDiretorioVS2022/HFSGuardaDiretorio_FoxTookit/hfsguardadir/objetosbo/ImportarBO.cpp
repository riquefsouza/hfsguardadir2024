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
        DiretorioOrdem *dirOrdem, std::vector<Diretorio> *listaDiretorio,
        IProgressoLog progressoLog) {
    Arquivo arquivo;
    Diretorio diretorio;
    Progresso pb;
	pb.log = "";
	
    arquivo.setNome(importar.getRotuloRaiz());
    arquivo.setTamanho(0);
	arquivo.setModificado(DateTime::Now());
	arquivo.setAtributos("[DIR]");
		
    diretorio = DiretorioBO::getInstancia()->atribuiDiretorio(
            importar.getAba(), importar.getCodDirRaiz(),
            importar.getNomeDirRaiz(), "", true, *listaDiretorio,
            arquivo, dirOrdem);

	listaDiretorio->push_back(diretorio);
	pb.log = importar.getCaminho();

    DiretorioBO::getInstancia()->ImportarDiretorio(importar.getAba(),
            importar.getCodDirRaiz(), importar.getNomeDirRaiz(),
            importar.getCaminho(), listaDiretorio, dirOrdem, progressoLog);
	
	if (progressoLog != NULL) {
        progressoLog(pb);
    }
}

void ImportarBO::ImportacaoCompleta(Importar importar, DiretorioOrdem *dirOrdem,
	std::vector<Extensao>  &listaExtensao,
        IProgressoLog progressoLog) {
	std::vector<Diretorio>  listaDiretorio;

	CarregarListaDiretorios(importar, dirOrdem, &listaDiretorio, progressoLog);

    //ExtensaoBO::getInstancia()->salvarExtensoes(listaDiretorio, listaExtensao, progressoLog);

    DiretorioBO::getInstancia()->salvarDiretorio(listaDiretorio, progressoLog);

	listaDiretorio.clear();
}

}
}
