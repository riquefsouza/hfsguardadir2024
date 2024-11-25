#ifndef ABADAO_H
#define ABADAO_H

#include <QString>
#include <QList>
#include <QtSql>
#include "hfsguardadir/objetos/Aba.h"
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosdao {

class AbaDAO
{
private:
    QSqlQuery *query;

    AbaDAO();
    AbaDAO(AbaDAO const&);
    AbaDAO& operator=(AbaDAO const&);
    static AbaDAO* instancia;

    void fecharSqlPreparado();
    Aba novoObjeto(QSqlQuery *res);

public:
    static AbaDAO* getInstancia();
    int consultarTotal();
    QList<Aba> consultarTudo(IProgressoLog progressoLog);
    bool incluir(Aba obj);
    bool alterar(Aba obj);
    bool excluir(int codigo);
    bool criarTabela();
};

}

}

#endif // ABADAO_H
