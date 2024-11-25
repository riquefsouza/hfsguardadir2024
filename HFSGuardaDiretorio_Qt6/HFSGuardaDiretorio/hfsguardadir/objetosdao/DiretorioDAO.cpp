#include "DiretorioDAO.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosdao {

DiretorioDAO* DiretorioDAO::instancia = NULL;

DiretorioDAO::DiretorioDAO()
{

}

DiretorioDAO::DiretorioDAO(DiretorioDAO const&){

}

DiretorioDAO& DiretorioDAO::operator=(DiretorioDAO const&){
    return *instancia;
}

DiretorioDAO* DiretorioDAO::getInstancia() {
    if (!instancia) {
        instancia = new DiretorioDAO();
    }
    return instancia;
}

void DiretorioDAO::fecharSqlPreparado() {
    if (query->isActive()) {
        query->finish();
    }
    delete query;
}

Diretorio DiretorioDAO::novoObjeto(QSqlQuery *res) {
    Diretorio ret;
    Aba aba;
    Tipo tipo;

    aba.setCodigo(res->value(0).toInt());
    ret.setCodigo(res->value(1).toInt());
    ret.setOrdem(res->value(2).toInt());

    if (!res->value(3).isNull()) {
        ret.setCodDirPai(res->value(3).toInt());
    } else {
        ret.setCodDirPai(-1);
    }
    ret.setNome(res->value(4).toString());
    ret.setTamanho(res->value(5).toLongLong());

    tipo.setCodigo(res->value(6).toString().at(0).toLatin1());
	if (tipo.getCodigo() == 'D') {
		tipo.setNome(Rotinas::getRecurso("TipoLista.diretorio"));
	}
	else {
		tipo.setNome(Rotinas::getRecurso("TipoLista.arquivo"));
	}

    ret.setTipo(tipo);
    ret.setModificado(Rotinas::StringToDate(res->value(7).toString()));
    ret.setAtributos(res->value(8).toString());
    ret.setCaminho(res->value(9).toString());
    aba.setNome(res->value(10).toString());
    ret.setAba(aba);
    ret.setNomePai(Rotinas::testaNull(res->value(11).toString()));
    ret.setCaminhoPai(Rotinas::testaNull(res->value(12).toString()));
    ret.setTamanhoFormatado(Rotinas::MontaTamanho(ret.getTamanho()));
    ret.setModificadoFormatado(Rotinas::formataDate(
            Rotinas::FORMATO_DATAHORA, ret.getModificado()));

    return ret;
}

int DiretorioDAO::consultarTotal(const QString &sSQL,
                                 const QString &sCondicaoTotal) {
    int total = 0;
    QString sTabela, sql;

    if (Rotinas::ContainsStr(sSQL, "consultadirpai"))
        sTabela = "consultadirpai";
    else if (Rotinas::ContainsStr(sSQL, "consultadirfilho"))
        sTabela = "consultadirfilho";
    else if (Rotinas::ContainsStr(sSQL, "consultaarquivo"))
        sTabela = "consultaarquivo";
    else
        sTabela = "Diretorios";

    sql = "select count(*) from " + sTabela;
    if (sCondicaoTotal.trimmed().length() > 0){
        sql += " " + sCondicaoTotal;
    }

    query = new QSqlQuery(Rotinas::getInstancia()->getConexao());
    query->clear();
    query->prepare(sql);

    if (query->exec())
    {
       if (query->next())
       {
          total = query->value(0).toInt();
       }
    } else {
        qDebug() << "DiretorioDAO::consultarTotal(): "
                 << query->lastError();
    }

    this->fecharSqlPreparado();

    return total;
}

QList<Diretorio> DiretorioDAO::consultarTudo(const QString &sSQL,
                                             const QString &sCondicaoTotal,
                                             IProgressoLog progressoLog) {
    Diretorio obj;
    QList<Diretorio> lista;
    Progresso pb;
    int i = 0;
    int total = this->consultarTotal(sSQL, sCondicaoTotal);

    query = new QSqlQuery(Rotinas::getInstancia()->getConexao());
    query->clear();
    query->prepare(sSQL);

    if (query->exec())
    {

        if (total > 0) {
            pb.minimo = 0;
            pb.maximo = total - 1;
            pb.posicao = 0;
            pb.passo = 1;

            while (query->next()) {
                obj = novoObjeto(std::move(query));

                lista.append(obj);

                pb.posicao = i;

                if (progressoLog != NULL) {
                    progressoLog(pb);
                }

                i++;
            }
        }

    } else {
        qDebug() << "DiretorioDAO::consultarTudo(): "
                 << query->lastError();
    }

    this->fecharSqlPreparado();

    return lista;
}

void DiretorioDAO::atribuirCampos(QSqlQuery *query, Diretorio obj) {
    query->bindValue(":aba", obj.getAba().getCodigo());
    query->bindValue(":cod", obj.getCodigo());
    query->bindValue(":ordem", obj.getOrdem());
    query->bindValue(":coddirpai", obj.getCodDirPai());
    query->bindValue(":nome", obj.getNome());
    query->bindValue(":tam", obj.getTamanho());
    query->bindValue(":tipo", QString(obj.getTipo().getCodigo()));
    query->bindValue(":modificado", obj.getModificadoFormatado());
    query->bindValue(":atributos", obj.getAtributos());
    query->bindValue(":caminho", obj.getCaminho());
}

bool DiretorioDAO::incluir(Diretorio obj) {
    bool ret;
	QString sSQL = "insert into Diretorios(aba, cod, ordem, coddirpai, nome, tam," \
		" tipo, modificado, atributos, caminho)" \
		" values (:aba, :cod, :ordem, :coddirpai, :nome, :tam," \
		" :tipo, :modificado, :atributos, :caminho)";

    query = new QSqlQuery(Rotinas::getInstancia()->getConexao());
    query->clear();
    query->prepare(sSQL);
    atribuirCampos(std::move(query), obj);
    ret = query->exec();
    this->fecharSqlPreparado();
    return ret;
}

bool DiretorioDAO::excluir(Aba aba, const QString &sCaminho) {
    bool ret;

    query = new QSqlQuery(Rotinas::getInstancia()->getConexao());
    query->clear();
    query->prepare("delete from Diretorios where caminho like :caminho and aba=:aba");
    query->bindValue(":caminho", sCaminho + "%");
    query->bindValue(":aba", aba.getCodigo());
    ret = query->exec();

    this->fecharSqlPreparado();
    return ret;
}

bool DiretorioDAO::criarTabela() {
    QString sSQL;
    bool ret;

    sSQL = "create table if NOT EXISTS Diretorios(" \
            "aba int not null," \
            "cod int not null," \
            "ordem int not null," \
            "nome varchar(255) not null," \
            "tam numeric not null," \
            "tipo char(1) not null," \
            "modificado date not null," \
            "atributos varchar(20) not null," \
            "coddirpai int not null," \
            "caminho varchar(255) not null," \
            "primary key (aba, cod, ordem))";

    query = new QSqlQuery(Rotinas::getInstancia()->getConexao());
    query->clear();
    query->prepare(sSQL);
    ret = query->exec();
    this->fecharSqlPreparado();
    return ret;
}

}
}
