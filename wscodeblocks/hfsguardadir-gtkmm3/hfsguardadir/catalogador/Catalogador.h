#ifndef CATALOGADOR_H
#define CATALOGADOR_H

#include "../objetos/Diretorio.h"
#include "../objetos/DiretorioOrdem.h"
#include "../objetos/Extensao.h"
#include "../objetosgui/Tabela.h"
#include "../objetosgui/Arvore.h"
#include "../comum/Rotinas.h"
#include "../catalogador/RotuloRaiz.h"
#include "../../FrmPrincipal.h"
#include "../../FrmImportarDiretorio.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::objetosgui;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace catalogador {

class Catalogador
{
private:
	Glib::ustring CONSULTA_DIR_PAI;
	Glib::ustring CONSULTA_DIR_FILHO;
	Glib::ustring CONSULTA_ARQUIVO;

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
	void ExcluirDados(Aba aba, const Glib::ustring sCaminho);
	void AddItemArvore(Arvore* arvore, Diretorio diretorio, int Nivel, Gtk::TreeRow node1);
	void IncluirNovaAba();
	void AlterarNomeAbaAtiva(IProgressoLog pLog);
	void ExcluirAbaAtiva(IProgressoLog pLog);
	void incluirNovaAba(const Glib::ustring nomeAba);
	Arvore* getArvoreAtualIndice(int nIndicePagina);
	Arvore* getArvoreAtual();
	Gtk::HPaned* getSplitAtual();
	Tabela* getTabelaAtual();
	void mostrarOcultarArvore();
	void mostrarOcultarListaItensPesquisados();
	void CarregarArvore(Arvore* arvore, Aba aba);
	void CarregarAbas();
	Aba getAbaAtual();
	void CarregarArquivosLista(bool bLista1, Tabela* tabela, const Glib::ustring sCaminho);
	void TamTotalDiretorio(const Glib::ustring sCaminho);
	std::vector<Glib::ustring> montaCaminho(const Glib::ustring sCaminho, bool bRemover);
	std::vector<Glib::ustring> montaCaminhoStatus(Arvore* arvore, Gtk::TreeIter iter);
	void Pesquisar();
	void PesquisarArvoreDiretorio(const Glib::ustring sCaminho, Aba aba);
	void LerArvoreDiretorio(Arvore* arvore, Gtk::TreeIter iter,	Gtk::Label* barraStatus);
	void ListarArquivos(Tabela* tabela, Arvore* arvore, Gtk::TreeIter iter);
	void tabPanelMudou();
	void DuploCliqueLista(const Glib::ustring nome, const Glib::ustring tipo);
	void EncontrarItemLista(const Glib::ustring nomeAba, const Glib::ustring nome,
		const Glib::ustring caminho);
	int verificaNomeDiretorio(const Glib::ustring sCaminho, RotuloRaiz *sRotuloRaiz);
	void ExportarArquivo(TipoExportar tipo, IProgressoLog pLog);
	void ExcluirDiretorioSelecionado(IProgressoLog pLog);
	void ImportarArquivo(std::vector<Glib::ustring> log, IProgressoLog pLog);
	bool ImportarDiretorios(std::vector<Glib::ustring> listaCaminho,
		bool bSubDiretorio, FrmImportarDiretorio* frmImportarDiretorio);
	void FinalizaImportacao(IProgressoLog pLog);
	void ComecaImportacao(bool bSubDiretorios, IProgressoLog pLog);
	void InformacoesDiretorioArquivo();

};

}
}

extern hfsguardadir::catalogador::Catalogador *catalogador;

#endif // CATALOGADOR_H
