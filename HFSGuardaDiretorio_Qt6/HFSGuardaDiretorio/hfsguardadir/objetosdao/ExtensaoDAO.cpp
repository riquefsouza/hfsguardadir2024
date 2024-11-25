#include "ExtensaoDAO.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosdao {

ExtensaoDAO* ExtensaoDAO::instancia = NULL;

ExtensaoDAO::ExtensaoDAO()
{

}

ExtensaoDAO::ExtensaoDAO(ExtensaoDAO const&){

}

ExtensaoDAO& ExtensaoDAO::operator=(ExtensaoDAO const&){
    return *instancia;
}

ExtensaoDAO* ExtensaoDAO::getInstancia() {
    if (!instancia) {
        instancia = new ExtensaoDAO();
    }
    return instancia;
}

void ExtensaoDAO::fecharSqlPreparado() {
    if (query->isActive()) {
        query->finish();
    }
    delete query;
}

Extensao ExtensaoDAO::novoObjeto(QSqlQuery *res) {
    Extensao ret;
    ret.setCodigo(res->value(0).toInt());
    ret.setNome(res->value(1).toString());
    ret.setBmp16(res->value(2).toByteArray());
    ret.setBmp32(res->value(3).toByteArray());
	/*
    if (!ret.getBmp16().isEmpty()) {
        ret.setGif16(Rotinas::BmpParaImagem(ret.getBmp16(),
                Rotinas::EXTENSAO_GIF));
    }
    if (ret.getBmp32().isEmpty()) {
        ret.setGif32(Rotinas::BmpParaImagem(ret.getBmp32(),
                Rotinas::EXTENSAO_GIF));
    }
    */
    return ret;
}

int ExtensaoDAO::consultarTotal() {
    int total = 0;

    query = new QSqlQuery(Rotinas::getInstancia()->getConexao());
    query->clear();
    query->prepare("select count(*) from Extensoes");

    if (query->exec())
    {
       if (query->next())
       {
          total = query->value(0).toInt();
       }
    } else {
        qDebug() << "ExtensaoDAO::consultarTotal(): "
                 << query->lastError();
    }

    this->fecharSqlPreparado();

    return total;
}

QList<Extensao> ExtensaoDAO::consultarTudo(IProgressoLog progressoLog) {
    Extensao obj;
    QList<Extensao> lista;
    Progresso pb;
    int i = 0;
    int total = this->consultarTotal();

    query = new QSqlQuery(Rotinas::getInstancia()->getConexao());
    query->clear();
    query->prepare("select cod, nome, bmp16, bmp32 from Extensoes");

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
        qDebug() << "ExtensaoDAO::consultarTudo(): "
                 << query->lastError();
    }

    this->fecharSqlPreparado();

    return lista;
}

bool ExtensaoDAO::incluir(Extensao obj) {
    bool ret;

    query = new QSqlQuery(Rotinas::getInstancia()->getConexao());
    query->clear();
    query->prepare("insert into Extensoes(cod, nome, bmp16, bmp32) values(:cod,:nome,:bmp16,:bmp32)");
    query->bindValue(":cod", obj.getCodigo());
    query->bindValue(":nome", obj.getNome());
    query->bindValue(":bmp16", obj.getBmp16());
    query->bindValue(":bmp32", obj.getBmp32());
    ret = query->exec();
    this->fecharSqlPreparado();
    return ret;
}

bool ExtensaoDAO::excluir(int codigo) {
    bool ret;

    query = new QSqlQuery(Rotinas::getInstancia()->getConexao());
    query->clear();
    query->prepare("delete from Extensoes where cod=:cod");
    query->bindValue(":cod", codigo);
    ret = query->exec();

    this->fecharSqlPreparado();
    return ret;
}

bool ExtensaoDAO::excluirTudo() {
    bool ret;

    query = new QSqlQuery(Rotinas::getInstancia()->getConexao());
    query->clear();
    query->prepare("delete from Extensoes");
    ret = query->exec();

    this->fecharSqlPreparado();
    return ret;
}

bool ExtensaoDAO::criarTabela() {
    bool ret;

    query = new QSqlQuery(Rotinas::getInstancia()->getConexao());
    query->clear();
    query->prepare("create table IF NOT EXISTS Extensoes(" \
                  "cod integer not null," \
                  "nome varchar(20) not null," \
                  "bmp16 BLOB COLLATE NOCASE null," \
                  "bmp32 BLOB COLLATE NOCASE null," \
                  "primary key (cod))");
    ret = query->exec();
    this->fecharSqlPreparado();
    return ret;
}

}
}
