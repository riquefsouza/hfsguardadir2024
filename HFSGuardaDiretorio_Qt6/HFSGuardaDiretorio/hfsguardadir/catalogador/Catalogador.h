#ifndef CATALOGADOR_H
#define CATALOGADOR_H

#include <QString>
#include <QList>
#include <QStandardItemModel>
#include "hfsguardadir/objetos/Diretorio.h"
#include "hfsguardadir/objetos/DiretorioOrdem.h"
#include "hfsguardadir/objetos/Extensao.h"
#include "hfsguardadir/objetosgui/Tabela.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/catalogador/RotuloRaiz.h"
#include "FrmPrincipal.h"
#include "FrmImportarDiretorio.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::objetosgui;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace catalogador {

class Catalogador
{
private:
    static const QString CONSULTA_DIR_PAI;
    static const QString CONSULTA_DIR_FILHO;
    static const QString CONSULTA_ARQUIVO;
    static const QString NO_RAIZ;

    //bool bSombrearLinhas, bSombrearColunas;
	
    QList<Diretorio> listaDiretorioFilho;
    QList<Diretorio> listaArquivos;
	        
    QStandardItem *nodeRaiz;
	
    void AddItemArvore(Diretorio diretorio, int Nivel,
            QStandardItem *node1);
    void IncluirNovaAba(const QString &nomeAba);   
    bool testaSeparadorArquivo(const QString &sDir);
    QStringList montaCaminho(const QString &sCaminho, bool bRemover);

public:
	bool bGravarLogImportacao;
	
	DiretorioOrdem diretorioOrdem;
	QList<Aba> listaAbas;
	QList<Diretorio> listaDiretorioPai;
	QList<Extensao> listaExtensoes;

	Catalogador();
	~Catalogador();

    static void iniciarSistema();
	void DesconectarEventos();
	Aba getAbaAtual();
    void CarregarDados(IProgressoLog pLog, bool bExtensao, bool bDiretorio);
    void ExcluirDados(Aba aba, const QString &sCaminho);
    void IncluirNovaAba();
    void AlterarNomeAbaAtiva(IProgressoLog pLog);
    void ExcluirAbaAtiva(IProgressoLog pLog);
    Arvore* getArvoreAtual();
    Arvore* getArvoreAtual(int nIndicePagina);
    QSplitter* getSplitAtual();
	Tabela* getTabelaAtual(int nIndicePagina);
    Tabela* getTabelaAtual();
    void setTabelaAtual(QStandardItemModel *modelo);
    void mostrarOcultarArvore();
    void CarregarArvore(Arvore *tvAba, Aba aba);
    void CarregarAbas();
    void CarregarArquivosLista(Tabela* tabela, bool bLista1,
        const QString caminho);
    void TamTotalDiretorio(QString sCaminho);
    void Pesquisar();
	void PesquisarArvoreDiretorio(const QString & sCaminho, Aba aba, bool bRemover);
    void LerArvoreDiretorio(const QModelIndex & mi,
            QLabel *barraStatus);
	void DuploCliqueLista(const QString &nome, const QString &tipo);
	void EncontrarItemLista(const QString &nomeAba, const QString &nome, const QString &caminho);
    int verificaNomeDiretorio(QString &sCaminho, RotuloRaiz *sRotuloRaiz);
    void ExportarArquivo(TipoExportar tipo, IProgressoLog pLog);
	void ListarArquivos();
	void tabPanelMudou();
	void arvoreValorMudou(const QModelIndex & mi);
	QStringList montaCaminho(const QModelIndex & mi);
	void ExcluirDiretorioSelecionado(IProgressoLog pLog);
    void ImportarArquivo(IProgressoLog pLog);
	bool ImportarDiretorios(QStringList listaCaminho,
		bool bSubDiretorio, FrmImportarDiretorio *frmImportarDiretorio);
    void FinalizaImportacao(IProgressoLog pLog);
	void ComecaImportacao(bool bSubDiretorios, IProgressoLog pLog);
};

}
}

extern hfsguardadir::catalogador::Catalogador *catalogador;

#endif // CATALOGADOR_H
