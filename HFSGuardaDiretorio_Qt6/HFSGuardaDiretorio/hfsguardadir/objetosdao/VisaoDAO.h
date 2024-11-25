#ifndef VISAODAO_H
#define VISAODAO_H

#include <QString>
#include <QtSql>

namespace hfsguardadir {

namespace objetosdao {

class VisaoDAO
{
private:
    QSqlQuery *query;

    VisaoDAO();
    VisaoDAO(VisaoDAO const&);
    VisaoDAO& operator=(VisaoDAO const&);
    static VisaoDAO* instancia;

    void fecharSqlPreparado();
    QString sqlVisao(QString visao);

public:
    static VisaoDAO* getInstancia();
    bool criarVisao(QString visao);

};

}
}

#endif // VISAODAO_H
