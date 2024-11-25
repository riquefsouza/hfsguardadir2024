#ifndef EXTENSAOBO_H
#define EXTENSAOBO_H

#include <QList>
#include "hfsguardadir/objetos/Extensao.h"
#include "hfsguardadir/objetos/Diretorio.h"
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosbo {

class ExtensaoBO
{
private:
	QByteArray diretorioGIF, diretorioBMP, diretorio32BMP;
	//QByteArray dirabertoBMP, diraberto32BMP;
	QByteArray arquivoGIF, arquivoBMP, arquivo32BMP;

	ExtensaoBO();
    ExtensaoBO(ExtensaoBO const&);
    ExtensaoBO& operator=(ExtensaoBO const&);
    static ExtensaoBO* instancia;

public:
    static ExtensaoBO* getInstancia();

    QList<Extensao> carregarExtensao(IProgressoLog progressoLog);
    int retMaxCodExtensao(QList<Extensao> listaLocal);
    bool existeExtensao(QString &sExtensao, QList<Extensao> listaLocal);
    bool incluirExtensao(Extensao extensao);
    bool SalvarExtensao(QList<Extensao> listaExtensao, QString sNomeDiretorio, QStringList log);
    void salvarExtensoes(QList<Diretorio> listaDiretorio,
            QList<Extensao> listaExtensao, IProgressoLog progressoLog);
    bool excluirExtensao(QList<Extensao> listaExtensao, int codigo);
    bool excluirTodasExtensoes(QList<Extensao> listaExtensao);
    bool criarTabelaExtensoes();
    int indiceExtensao(QList<Extensao> lista, QString &nomeExtensao);
    Extensao* pegaExtensaoPorOrdem(QList<Extensao> lista, int ordem);
    Extensao* pegaExtensaoPorCodigo(QList<Extensao> lista, int codigo);
    Extensao pegaExtensaoPorNome(QList<Extensao> lista,
            const QString &nome, const QString &tipo);
    bool ExportarExtensao(TipoExportarExtensao tipo,
                          QList<Extensao> listaExtensao);
    void ImportarExtensao(QString &caminho, QList<Extensao> listaExtensao);
    void ExtrairExtensao(QString &caminho, QList<Extensao> listaExtensao);
};

}
}

#endif // EXTENSAOBO_H
