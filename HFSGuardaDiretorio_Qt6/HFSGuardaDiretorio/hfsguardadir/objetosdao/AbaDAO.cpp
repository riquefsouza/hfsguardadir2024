#include "AbaDAO.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosdao {

AbaDAO* AbaDAO::instancia = NULL;

AbaDAO::AbaDAO()
{

}

AbaDAO::AbaDAO(AbaDAO const&){

}

AbaDAO& AbaDAO::operator=(AbaDAO const&){
    return *instancia;
}

AbaDAO* AbaDAO::getInstancia() {
    if (!instancia) {
        instancia = new AbaDAO();
    }
    return instancia;
}

void AbaDAO::fecharSqlPreparado() {
    if (query->isActive()) {
        query->finish();
    }
    delete query;
}

Aba AbaDAO::novoObjeto(QSqlQuery *res) {
    Aba ret;
    ret.setCodigo(res->value(0).toInt());
    ret.setNome(res->value(1).toString());
    return ret;
}

int AbaDAO::consultarTotal() {
    int total = 0;

    query = new QSqlQuery(Rotinas::getInstancia()->getConexao());
    query->clear();
    query->prepare("select count(*) from Abas");

    if (query->exec())
    {
       if (query->next())
       {
          total = query->value(0).toInt();
       }
    } else {
        qDebug() << "AbaDAO::consultarTotal(): "
                 << query->lastError();
    }

    this->fecharSqlPreparado();

    return total;
}

QList<Aba> AbaDAO::consultarTudo(IProgressoLog progressoLog) {
    Aba obj;
    QList<Aba> lista;
    Progresso pb;
    int i = 0;
    int total = this->consultarTotal();

    query = new QSqlQuery(Rotinas::getInstancia()->getConexao());
    query->clear();
    query->prepare("select cod, nome from Abas");

    if (query->exec())
    {

        if (total > 0) {
            pb.minimo = 0;
            pb.maximo = total - 1;
            pb.posicao = 0;
            pb.passo = 1;

            while (query->next()) {
                obj = novoObjeto(std::move(query));
                obj.setOrdem(i + 1);

                lista.append(obj);

                pb.posicao = i;

                if (progressoLog != NULL) {
                    progressoLog(pb);
                }

                i++;
            }
        }

    } else {
        qDebug() << "AbaDAO::consultarTudo(): "
                 << query->lastError();
    }

    this->fecharSqlPreparado();

    return lista;
}

bool AbaDAO::incluir(Aba obj) {
    bool ret;

    query = new QSqlQuery(Rotinas::getInstancia()->getConexao());
    query->clear();
    query->prepare("insert into Abas(cod, nome) values(:cod,:nome)");
    query->bindValue(":cod", obj.getCodigo());
    query->bindValue(":nome", obj.getNome());
    ret = query->exec();
    this->fecharSqlPreparado();
    return ret;
}

bool AbaDAO::alterar(Aba obj) {
    bool ret;

    query = new QSqlQuery(Rotinas::getInstancia()->getConexao());
    query->clear();
    query->prepare("update Abas set nome=:nome where cod=:cod");
    query->bindValue(":cod", obj.getCodigo());
    query->bindValue(":nome", obj.getNome());
    ret = query->exec();
    this->fecharSqlPreparado();
    return ret;
}

bool AbaDAO::excluir(int codigo) {
    bool ret;

    query = new QSqlQuery(Rotinas::getInstancia()->getConexao());
    query->clear();
    query->prepare("delete from Diretorios where aba=:aba");
    query->bindValue(":aba", codigo);
    ret = query->exec();

    if (ret){
        query->clear();
        query->prepare("delete from Abas where cod=:cod");
        query->bindValue(":cod", codigo);
        ret = query->exec();
    }

    this->fecharSqlPreparado();
    return ret;
}

bool AbaDAO::criarTabela() {
    bool ret;

    query = new QSqlQuery(Rotinas::getInstancia()->getConexao());
    query->clear();
    query->prepare("create table IF NOT EXISTS Abas(" \
                  "cod integer not null, nome varchar(10) not null, " \
                  "primary key (cod))");
    ret = query->exec();
    this->fecharSqlPreparado();
    return ret;
}

}
}
