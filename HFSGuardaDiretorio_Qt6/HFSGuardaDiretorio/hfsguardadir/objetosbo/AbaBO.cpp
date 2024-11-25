#include "AbaBO.h"

#include "hfsguardadir/objetosdao/AbaDAO.h"

using namespace hfsguardadir::objetosdao;

namespace hfsguardadir {

namespace objetosbo {

AbaBO* AbaBO::instancia = NULL;

AbaBO::AbaBO()
{

}

AbaBO::AbaBO(AbaBO const&){

}

AbaBO& AbaBO::operator=(AbaBO const&){
    return *instancia;
}

AbaBO* AbaBO::getInstancia() {
    if (!instancia) {
        instancia = new AbaBO();
    }
    return instancia;
}

QList<Aba> AbaBO::carregarAba(IProgressoLog progressoLog) {
    return AbaDAO::getInstancia()->consultarTudo(progressoLog);
}

int AbaBO::retMaxCodAba(QList<Aba> listaLocal) {
    int nMaior = 0;
    Aba aba;

    for (int i = 0; i < listaLocal.size(); ++i) {
        aba = listaLocal.at(i);

        if (aba.getCodigo() > nMaior) {
            nMaior = aba.getCodigo();
        }
    }
    return nMaior + 1;
}

QString AbaBO::abaToSQL(Aba aba) {
    QString sql = QString("insert into Abas(cod, nome) values(")
                  + QString::number(aba.getCodigo()) + QString(",")
        + Rotinas::QuotedStr(aba.getNome()) + QString(")");

    return sql;

}

bool AbaBO::incluirAba(Aba aba) {
    return AbaDAO::getInstancia()->incluir(aba);
}

bool AbaBO::alterarAba(Aba aba) {
    return AbaDAO::getInstancia()->alterar(aba);
}

bool AbaBO::excluirAba(Aba aba) {
    return AbaDAO::getInstancia()->excluir(aba.getCodigo());
}

bool AbaBO::criarTabelaAbas() {
    return AbaDAO::getInstancia()->criarTabela();
}

Aba* AbaBO::pegaAbaPorOrdem(QList<Aba> lista, int ordem) {
    Aba *aba = new Aba();

    for (int i = 0; i < lista.size(); ++i) {
        *aba = lista.at(i);

        if (aba->getOrdem() == ordem) {
            return aba;
        }
    }
    return NULL;
}

Aba* AbaBO::getElemento(QList<Aba> lista, int codigo) {
    Aba *aba = new Aba();

    for (int i = 0; i < lista.size(); ++i) {
        *aba = lista.at(i);

        if (aba->getCodigo() == codigo) {
            return aba;
        }
    }
    return NULL;
}

Aba* AbaBO::pegaAbaPorNome(QList<Aba> lista, QString nome) {
    Aba *aba = new Aba();

    for (int i = 0; i < lista.size(); ++i) {
        *aba = lista.at(i);

        if (aba->getNome() == nome) {
            return aba;
        }
    }
    return NULL;
}

}
}
