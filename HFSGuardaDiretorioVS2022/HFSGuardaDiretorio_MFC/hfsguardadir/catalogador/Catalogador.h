#ifndef CATALOGADOR_H
#define CATALOGADOR_H

#pragma once

#include <commctrl.h>

#include "hfsguardadir/objetos/Diretorio.h"
#include "hfsguardadir/objetos/DiretorioOrdem.h"
#include "hfsguardadir/objetos/Extensao.h"
#include "hfsguardadir/objetosgui/Tabela.h"
#include "hfsguardadir/objetosgui/Arvore.h"
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
	static const CString CONSULTA_DIR_PAI;
	static const CString CONSULTA_DIR_FILHO;
	static const CString CONSULTA_ARQUIVO;
	static const CString NO_RAIZ;

	CList<Diretorio, Diretorio&> *listaDiretorioFilho;
	CList<Diretorio, Diretorio&> *listaArquivos;

	HTREEITEM nodeRaiz;
	
public:
	bool bGravarLogImportacao;

	DiretorioOrdem diretorioOrdem;
	CList<Aba, Aba&> *listaAbas;
	CList<Diretorio, Diretorio&> *listaDiretorioPai;
	CList<Extensao, Extensao&> *listaExtensoes;

	Catalogador();
	~Catalogador();
	
	void AddItemArvore(CTreeCtrl &arvore, Diretorio diretorio, int Nivel,
			HTREEITEM item1);
	void IncluirNovaAba(const CString &nomeAba, int numAba);
	BOOL testaSeparadorArquivo(const CString &sDir);
	CStringList* montaCaminho(const CString &sCaminho, BOOL bRemover);
	void iniciarSistema();
	Aba getAbaAtual();
	void CarregarDados(IProgressoLog pLog, BOOL bExtensao, BOOL bDiretorio);
	void ExcluirDados(Aba aba, const CString &sCaminho);
	void IncluirNovaAba();
	void AlterarNomeAbaAtiva(IProgressoLog pLog);
	void ExcluirAbaAtiva(IProgressoLog pLog);
	CTreeCtrl* getArvoreAtual();
	CTreeCtrl* getArvoreAtual(int nIndicePagina);
	CListCtrl* getTabelaAtual(int nIndicePagina);
	CListCtrl* getTabelaAtual();
	void CarregarArvore(CTreeCtrl &tvAba, Aba aba);
	void CarregarAbas();
	void CarregarArquivosLista(CListCtrl &tabela, BOOL bLista1,
		const CString &caminho);
	void TamTotalDiretorio(Aba aba, const CString &sCaminho);
	void Pesquisar();
	void PesquisarArvoreDiretorio(const CString &sCaminho, Aba aba, BOOL bRemover);
	void LerArvoreDiretorio(CTreeCtrl &arvore, HTREEITEM item,
		CStatusBar &barraStatus);
	void DuploCliqueLista(const CString &nome, const CString &tipo);
	void EncontrarItemLista(const CString &nomeAba, const CString &nome, const CString &caminho);
	int verificaNomeDiretorio(const CString &sCaminho, RotuloRaiz *sRotuloRaiz);
	void ExportarArquivo(TipoExportar tipo, IProgressoLog pLog);
	void ListarArquivos();
	void tabPanelMudou();
	void tabPanelMudou(Aba aba);
	void arvoreValorMudou(CTreeCtrl &arvore, HTREEITEM item);
	CStringList* montaCaminho(CTreeCtrl &arvore, HTREEITEM item);
	void ExcluirDiretorioSelecionado(IProgressoLog pLog);
	void ImportarArquivo(const CStringList &log, IProgressoLog pLog);
	BOOL ImportarDiretorios(const CStringList &listaCaminho,
		BOOL bSubDiretorio);
	void FinalizaImportacao(IProgressoLog pLog);
	void ComecaImportacao(BOOL bSubDiretorios, IProgressoLog pLog);

};

}
}

extern hfsguardadir::catalogador::Catalogador *catalogo;

#endif // CATALOGADOR_H
