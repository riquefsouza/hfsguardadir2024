#ifndef EXTENSAODAO_H
#define EXTENSAODAO_H

#include <QString>
#include <QList>
#include <QtSql>
#include "hfsguardadir/objetos/Extensao.h"
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosdao {

class ExtensaoDAO
{
private:
    QSqlQuery *query;

    ExtensaoDAO();
    ExtensaoDAO(ExtensaoDAO const&);
    ExtensaoDAO& operator=(ExtensaoDAO const&);
    static ExtensaoDAO* instancia;

    void fecharSqlPreparado();
    Extensao novoObjeto(QSqlQuery *res);

public:
    static ExtensaoDAO* getInstancia();
    int consultarTotal();
    QList<Extensao> consultarTudo(IProgressoLog progressoLog);
    bool incluir(Extensao obj);
    bool excluir(int codigo);
    bool excluirTudo();
    bool criarTabela();
};

}
}

#endif // EXTENSAODAO_H
