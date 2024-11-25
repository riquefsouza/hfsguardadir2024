#include "VisaoDAO.h"
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosdao {

VisaoDAO* VisaoDAO::instancia = NULL;

VisaoDAO::VisaoDAO()
{

}

VisaoDAO::VisaoDAO(VisaoDAO const&){

}

VisaoDAO& VisaoDAO::operator=(VisaoDAO const&){
    return *instancia;
}

VisaoDAO* VisaoDAO::getInstancia() {
    if (!instancia) {
        instancia = new VisaoDAO();
    }
    return instancia;
}

void VisaoDAO::fecharSqlPreparado() {
    if (query->isActive()) {
        query->finish();
    }
    delete query;
}

bool VisaoDAO::criarVisao(QString visao) {
    bool ret;

    query = new QSqlQuery(Rotinas::getInstancia()->getConexao());
    query->clear();
    query->prepare(sqlVisao(visao));
    ret = query->exec();
    this->fecharSqlPreparado();
    return ret;
}

QString VisaoDAO::sqlVisao(QString visao) {
    QString sSQL = "create view " + visao + " as "
            + "SELECT d.aba,d.cod,d.ordem,d.coddirpai,d.nome,d.tam,"
            + "d.tipo,d.modificado,d.atributos,d.caminho"
            + ",(select nome as nomeaba from Abas where cod=d.aba) as nomeaba"
            + ",(select nome as nomepai from Diretorios where cod=d.cod "
            + "  and ordem=d.coddirpai and aba=d.aba) as nomepai"
            + ",(select caminho as caminhopai from Diretorios where cod=d.cod "
            + " and ordem=d.coddirpai and aba=d.aba) as caminhopai "
            + "FROM Diretorios d ";

    if (visao == "consultadirpai") {
        sSQL += "where d.tipo='D' and d.coddirpai = 0";
    } else if (visao == "consultadirfilho") {
        sSQL += "where d.tipo='D' and d.coddirpai > 0";
    }

    return sSQL;
}

}
}
