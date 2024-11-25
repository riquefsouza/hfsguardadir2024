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

ImportarBO::ImportarBO(ImportarBO const&){

}

ImportarBO& ImportarBO::operator=(ImportarBO const&){
    return *instancia;
}

ImportarBO* ImportarBO::getInstancia() {
    if (!instancia) {
        instancia = new ImportarBO();
    }
    return instancia;
}

void ImportarBO::CarregarListaDiretorios(Importar importar,
        DiretorioOrdem *dirOrdem, QList<Diretorio> *listaDiretorio,
        IProgressoLog progressoLog) {
    Arquivo arquivo;
    Diretorio diretorio;
    Progresso pb;

    arquivo.setNome(importar.getRotuloRaiz());
    arquivo.setTamanho(0);
    arquivo.setModificado(QDateTime::currentDateTime());
    arquivo.setAtributos(QString("[DIR]"));

    diretorio = DiretorioBO::getInstancia()->atribuiDiretorio(
            importar.getAba(), importar.getCodDirRaiz(),
            importar.getNomeDirRaiz(), QString(""), true, *listaDiretorio,
            arquivo, dirOrdem);

    listaDiretorio->append(diretorio);
    pb.log = importar.getCaminho();

    DiretorioBO::getInstancia()->ImportarDiretorio(importar.getAba(),
            importar.getCodDirRaiz(), importar.getNomeDirRaiz(),
            importar.getCaminho(), listaDiretorio, dirOrdem, progressoLog);

    if (progressoLog != NULL) {
        progressoLog(pb);
    }
}

void ImportarBO::ImportacaoCompleta(Importar importar, DiretorioOrdem *dirOrdem,
        IProgressoLog progressoLog) {
    QList<Diretorio> *listaDiretorio = new QList<Diretorio>();

    CarregarListaDiretorios(importar, dirOrdem, listaDiretorio, progressoLog);

    //Por ser multiplataforma somente tem função para pegar icone de arquivo do windows
/*
#ifdef Q_WS_WIN
    ExtensaoBO::getInstancia()->salvarExtensoes(*listaDiretorio,
            listaExtensao, progressoLog);
#endif
*/
    DiretorioBO::getInstancia()->salvarDiretorio(*listaDiretorio,
            progressoLog);

    listaDiretorio->clear();
}


}
}
