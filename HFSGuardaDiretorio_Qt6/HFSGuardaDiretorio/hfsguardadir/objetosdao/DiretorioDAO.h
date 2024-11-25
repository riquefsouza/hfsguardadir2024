#ifndef DIRETORIODAO_H
#define DIRETORIODAO_H

#include <QString>
#include <QList>
#include <QtSql>
#include "hfsguardadir/objetos/Diretorio.h"
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosdao {

class DiretorioDAO
{
private:
    QSqlQuery *query;

    DiretorioDAO();
    DiretorioDAO(DiretorioDAO const&);
    DiretorioDAO& operator=(DiretorioDAO const&);
    static DiretorioDAO* instancia;

    void fecharSqlPreparado();
    Diretorio novoObjeto(QSqlQuery *res);
    void atribuirCampos(QSqlQuery *query, Diretorio obj);

public:
    static DiretorioDAO* getInstancia();
    int consultarTotal(const QString &sSQL, const QString &sCondicaoTotal);
    QList<Diretorio> consultarTudo(const QString &sSQL,
                                   const QString &sCondicaoTotal,
                                   IProgressoLog progressoLog);
    bool incluir(Diretorio obj);
    bool excluir(Aba aba, const QString &sCaminho);
    bool criarTabela();
};

}

}

#endif // DIRETORIODAO_H
