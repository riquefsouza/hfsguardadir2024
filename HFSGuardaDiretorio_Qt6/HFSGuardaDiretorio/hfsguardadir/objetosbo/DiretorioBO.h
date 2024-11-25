#ifndef DIRETORIOBO_H
#define DIRETORIOBO_H

#include <QList>
#include "hfsguardadir/objetos/Diretorio.h"
#include "hfsguardadir/objetos/DiretorioOrdem.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/comum/DiretorioXML.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosbo {

class DiretorioBO
{
private:
    DiretorioBO();
    DiretorioBO(DiretorioBO const&);
    DiretorioBO& operator=(DiretorioBO const&);
    static DiretorioBO* instancia;

    QString diretorioToCSV(Diretorio diretorio);
    QString diretorioToXML(Diretorio diretorio);
    QString diretorioToTXT(Diretorio diretorio);
    QString diretorioToHTML(Diretorio diretorio);

public:
    static const QString SQL_CONSULTA_ARQUIVO;
    static DiretorioBO* getInstancia();

    QList<Diretorio> carregarDiretorio(const QString &sSQL,
                                       IProgressoLog progressoLog);
    QList<Diretorio> carregarDiretorio(const QString &sSQL,
                                       const QString &sCondicaoTotal,
                                       IProgressoLog progressoLog);
    QString removerDrive(QString &sDiretorio);
    QString arquivoAtributos(QFileInfo &info);
    int retCodDirPai(int nAba, QString &sDiretorio,
                                  QList<Diretorio> listaLocal);
    Diretorio atribuiDiretorio(int nAba, int nCodDirRaiz,
            QString sNomeDirRaiz, QString sDiretorio, bool bDiretorio,
            QList<Diretorio> listaLocal, Arquivo arquivo,
            DiretorioOrdem *dirOrdem);
    Arquivo QFileInfoToArquivo(QFileInfo &info);
    void atribuiListaDiretorio(int nAba, int nCodDirRaiz,
            QString &sNomeDirRaiz, QString &sDiretorio, QList<Diretorio> *listaLocal,
            QFileInfo &info, DiretorioOrdem *dirOrdem, IProgressoLog progressoLog);
    void ImportarDiretorio(int nAba, int nCodDirRaiz,
            QString sNomeDirRaiz, QString sDiretorio, QList<Diretorio> *listaLocal,
            DiretorioOrdem *dirOrdem, IProgressoLog progressoLog);
    bool verificaCodDir(int nAba, QString &sDiretorio,
            QList<Diretorio> listaLocal);
    int retMaxCodDir(int nAba, QList<Diretorio> listaLocal);
    QString diretorioToSQL(Diretorio diretorio, bool bInsert);
    void salvarDiretorio(QList<Diretorio> listaDiretorio,
            IProgressoLog progressoLog);
    bool excluirDiretorio(Aba aba, const QString sCaminho);
    void excluirListaDiretorio(QList<Diretorio> listaDiretorio,
            Aba aba, const QString sCaminho);
    void exportarDiretorio(TipoExportar tipo, Aba aba,
            QString sNomeArquivo, IProgressoLog progressoLog);
    bool criarTabelaDiretorios();
    int XMLParaDiretorio(QString sTexto, int nArquivo,
            DiretorioXML *diretorioXML);
    int importarDiretorioViaXML(Aba aba, QString sNomeArquivo,
            QList<Diretorio> listaDirPai,
            IProgressoLog progressoLog);
    bool carregarSubDiretorios(QString sDiretorio,
            QStringList listaLocal);
    bool carregarArquivos(QString sDiretorio,
            QStringList listaLocal);
    bool carregarTodosArquivos(QString sDiretorio,
            QStringList listaLocal);
    QList<Diretorio> itensFilhos(QList<Diretorio> lista_pai,
            int aba, int codDirPai, int codigo);
};

}
}

#endif // DIRETORIOBO_H
