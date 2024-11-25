#ifndef ABABO_H
#define ABABO_H

#include <QList>
#include "hfsguardadir/objetos/Aba.h"
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosbo {

class AbaBO
{
private:
    AbaBO();
    AbaBO(AbaBO const&);
    AbaBO& operator=(AbaBO const&);
    static AbaBO* instancia;

public:
    static AbaBO* getInstancia();

    QList<Aba> carregarAba(IProgressoLog progressoLog);
    int retMaxCodAba(QList<Aba> listaLocal);
    QString abaToSQL(Aba aba);
    bool incluirAba(Aba aba);
    bool alterarAba(Aba aba);
    bool excluirAba(Aba aba);
    bool criarTabelaAbas();
    Aba* pegaAbaPorOrdem(QList<Aba> lista, int ordem);
    Aba* getElemento(QList<Aba> lista, int codigo);
    Aba* pegaAbaPorNome(QList<Aba> lista, QString nome);

};

}
}

#endif // ABABO_H
