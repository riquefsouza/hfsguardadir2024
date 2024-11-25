#ifndef CATALOGADOR_H
#define CATALOGADOR_H

#include "hfsguardadir/objetos/Diretorio.h"
#include "hfsguardadir/objetos/DiretorioOrdem.h"
#include "hfsguardadir/objetos/Extensao.h"
#include "hfsguardadir/objetosgui/Tabela.h"
#include "hfsguardadir/objetosgui/Arvore.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/catalogador/RotuloRaiz.h"
//#include "FrmPrincipal.h"
//#include "FrmImportarDiretorio.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::objetosgui;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace catalogador {

class Catalogador
{
private:
	std::string CONSULTA_DIR_PAI;
	std::string CONSULTA_DIR_FILHO;
	std::string CONSULTA_ARQUIVO;

	bool bGravarLogImportacao;		
	std::vector<Diretorio> listaDiretorioFilho;
	std::vector<Diretorio> listaArquivos;
		
public:
	DiretorioOrdem diretorioOrdem;
	std::vector<Aba> listaAbas;
	std::vector<Extensao> listaExtensoes;
	std::vector<Diretorio> listaDiretorioPai;

	Catalogador();
	~Catalogador();

	static void iniciarSistema();
	void CarregarDados(IProgressoLog pLog, bool bExtensao, bool bDiretorio);
	void ExcluirDados(Aba aba, const std::string &sCaminho);
	/*
	void AddItemArvore(Arvore &arvore, Diretorio diretorio, int Nivel, Gtk::TreeRow node1);
	void IncluirNovaAba();
	void AlterarNomeAbaAtiva(IProgressoLog pLog);
	void ExcluirAbaAtiva(IProgressoLog pLog);
	void incluirNovaAba(const std::string &nomeAba);
	Arvore* getArvoreAtualIndice(int nIndicePagina);
	Arvore* getArvoreAtual();
	Gtk::HPaned* getSplitAtual();
	Tabela* getTabelaAtual();
	void mostrarOcultarArvore();
	void mostrarOcultarListaItensPesquisados();
	void CarregarArvore(Arvore* arvore, Aba aba);
	void CarregarAbas();
	Aba getAbaAtual();
	void CarregarArquivosLista(bool bLista1, Tabela* tabela, const std::string &sCaminho);
	void TamTotalDiretorio(const std::string &sCaminho);
	std::vector<std::string> montaCaminho(const std::string &sCaminho, bool bRemover);
	std::vector<std::string> montaCaminhoStatus(Arvore* arvore, Gtk::TreeIter iter);
	void Pesquisar();
	void PesquisarArvoreDiretorio(const std::string &sCaminho, Aba aba);
	void LerArvoreDiretorio(Arvore* arvore, Gtk::TreeIter iter,	Gtk::Label* barraStatus);
	void ListarArquivos(Tabela* tabela, Arvore* arvore, Gtk::TreeIter iter);
	void tabPanelMudou();
	void DuploCliqueLista(const std::string &nome, const std::string &tipo);
	void EncontrarItemLista(const std::string &nomeAba, const std::string &nome, 
		const std::string &caminho);
	int verificaNomeDiretorio(const std::string &sCaminho, RotuloRaiz *sRotuloRaiz);
	void ExportarArquivo(TipoExportar tipo, IProgressoLog pLog);
	void ExcluirDiretorioSelecionado(IProgressoLog pLog);
	void ImportarArquivo(std::vector<std::string> log, IProgressoLog pLog);
	bool ImportarDiretorios(std::vector<std::string> listaCaminho,
		bool bSubDiretorio, FrmImportarDiretorio* frmImportarDiretorio);
	void FinalizaImportacao(IProgressoLog pLog);
	void ComecaImportacao(bool bSubDiretorios, IProgressoLog pLog);
	void InformacoesDiretorioArquivo();
	*/
};

}
}

extern hfsguardadir::catalogador::Catalogador *catalogador;

#endif // CATALOGADOR_H
