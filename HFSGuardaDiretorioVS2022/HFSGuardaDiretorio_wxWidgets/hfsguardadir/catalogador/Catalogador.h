#ifndef CATALOGADOR_H
#define CATALOGADOR_H

#include <wx/string.h>
#include <wx/vector.h>
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
    static const wxString CONSULTA_DIR_PAI;
    static const wxString CONSULTA_DIR_FILHO;
    static const wxString CONSULTA_ARQUIVO;
    static const wxString NO_RAIZ;

    //bool bSombrearLinhas, bSombrearColunas;
	
    wxVector<Diretorio> listaDiretorioFilho;
    wxVector<Diretorio> listaArquivos;
	        
    wxTreeItemId nodeRaiz;
	
    void AddItemArvore(Arvore *arvore, Diretorio diretorio, int Nivel,
            wxTreeItemId item1);
    void IncluirNovaAba(const wxString &nomeAba);   
    bool testaSeparadorArquivo(const wxString &sDir);
	wxArrayString montaCaminho(const wxString &sCaminho, bool bRemover);

public:
	bool bGravarLogImportacao;
	
	DiretorioOrdem diretorioOrdem;
	wxVector<Aba> listaAbas;
	wxVector<Diretorio> listaDiretorioPai;
	wxVector<Extensao> listaExtensoes;

	Catalogador();
	~Catalogador();

    static void iniciarSistema();
	void DesconectarEventos();
	Aba getAbaAtual();
    void CarregarDados(IProgressoLog pLog, bool bExtensao, bool bDiretorio);
    void ExcluirDados(Aba aba, const wxString &sCaminho);
    void IncluirNovaAba();
    void AlterarNomeAbaAtiva(IProgressoLog pLog);
    void ExcluirAbaAtiva(IProgressoLog pLog);
    Arvore* getArvoreAtual();
    Arvore* getArvoreAtual(int nIndicePagina);
    wxSplitterWindow* getSplitAtual();
	Tabela* getTabelaAtual(int nIndicePagina);
    Tabela* getTabelaAtual();
    void mostrarOcultarArvore();
	void mostrarListaItensPesquisados(bool bMostrar);
    void CarregarArvore(Arvore *tvAba, Aba aba);
    void CarregarAbas();
	void CarregarArquivosLista(Tabela* tabela, bool bLista1,
        const wxString &caminho);
    void TamTotalDiretorio(wxString &sCaminho);
    void Pesquisar();
	void PesquisarArvoreDiretorio(const wxString & sCaminho, Aba aba, bool bRemover);
    void LerArvoreDiretorio(Arvore *arvore, const wxTreeItemId &item,
		wxStatusBar *barraStatus);
	void DuploCliqueLista(const wxString &nome, const wxString &tipo);
	void EncontrarItemLista(const wxString &nomeAba, const wxString &nome, const wxString &caminho);
    int verificaNomeDiretorio(wxString &sCaminho, RotuloRaiz *sRotuloRaiz);
    void ExportarArquivo(TipoExportar tipo, IProgressoLog pLog);
	void ListarArquivos();
	void tabPanelMudou();
	void arvoreValorMudou(Arvore *arvore, const wxTreeItemId &item);
	wxArrayString montaCaminho(Arvore *arvore, const wxTreeItemId &item);
	void ExcluirDiretorioSelecionado(IProgressoLog pLog);
	void ImportarArquivo(wxArrayString log, IProgressoLog pLog);
	bool ImportarDiretorios(wxArrayString listaCaminho,
		bool bSubDiretorio, FrmImportarDiretorio *frmImportarDiretorio);
    void FinalizaImportacao(IProgressoLog pLog);
	void ComecaImportacao(bool bSubDiretorios, IProgressoLog pLog);
};

}
}

extern hfsguardadir::catalogador::Catalogador *catalogador;

#endif // CATALOGADOR_H
