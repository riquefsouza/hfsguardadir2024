#ifndef CATALOGADOR_H
#define CATALOGADOR_H

#include <commctrl.h>

#include "hfsguardadir/objetos/Diretorio.h"
#include "hfsguardadir/objetos/DiretorioOrdem.h"
#include "hfsguardadir/objetos/Extensao.h"
#include "hfsguardadir/objetosgui/Tabela.h"
#include "hfsguardadir/objetosgui/Arvore.h"
#include "hfsguardadir/comum/String.h"
#include "hfsguardadir/comum/ListaString.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/catalogador/RotuloRaiz.h"
#include "FrmPrincipal.h"
#include "FrmImportarDiretorio.h"

struct SCatalogador {
	String CONSULTA_DIR_PAI;
	String CONSULTA_DIR_FILHO;
	String CONSULTA_ARQUIVO;
	String NO_RAIZ;

	BOOL bGravarLogImportacao;
	DiretorioOrdem diretorioOrdem;
	ListaAba listaAbas;
	ListaDiretorio listaDiretorioPai;
	ListaExtensao listaExtensoes;

	ListaDiretorio listaDiretorioFilho;
	ListaDiretorio listaArquivos;
	HTREEITEM nodeRaiz;
};
extern struct SCatalogador Catalogador;

void Catalogador_New();
void Catalogador_Delete();
void Catalogador_AddItemArvore(Arvore arvore, Diretorio diretorio, int Nivel,
		HTREEITEM item1);
void Catalogador_IncluirNovaAba(String nomeAba, int numAba);
BOOL Catalogador_testaSeparadorArquivo(String sDir);
ListaString Catalogador_montaCaminho(String sCaminho, BOOL bRemover);
void Catalogador_iniciarSistema();
Aba Catalogador_getAbaAtual();
void Catalogador_CarregarDados(IProgressoLog pLog, BOOL bExtensao, BOOL bDiretorio);
void Catalogador_ExcluirDados(Aba aba, String sCaminho);
void Catalogador_IncluirNovaAba();
void Catalogador_AlterarNomeAbaAtiva(IProgressoLog pLog);
void Catalogador_ExcluirAbaAtiva(IProgressoLog pLog);
Arvore Catalogador_getArvoreAtual();
Arvore Catalogador_getArvoreAtual(int nIndicePagina);
//HWND Catalogador_getSplitAtual();
Tabela Catalogador_getTabelaAtual(int nIndicePagina);
Tabela Catalogador_getTabelaAtual();
//void Catalogador_mostrarOcultarArvore();
//void Catalogador_mostrarListaItensPesquisados(BOOL bMostrar);
void Catalogador_CarregarArvore(Arvore tvAba, Aba aba);
void Catalogador_CarregarAbas();
void Catalogador_CarregarArquivosLista(Tabela tabela, BOOL bLista1,
	String caminho);
void Catalogador_TamTotalDiretorio(Aba aba, String sCaminho);
void Catalogador_Pesquisar();
void Catalogador_PesquisarArvoreDiretorio(String  sCaminho, Aba aba, BOOL bRemover);
void Catalogador_LerArvoreDiretorio(Arvore arvore, HTREEITEM item,
	HWND barraStatus);
void Catalogador_DuploCliqueLista(String nome, String tipo);
void Catalogador_EncontrarItemLista(String nomeAba, String nome, String caminho);
int Catalogador_verificaNomeDiretorio(String sCaminho, RotuloRaiz *sRotuloRaiz);
void Catalogador_ExportarArquivo(TipoExportar tipo, IProgressoLog pLog);
void Catalogador_ListarArquivos();
void Catalogador_tabPanelMudou();
void Catalogador_tabPanelMudou(Aba aba);
void Catalogador_arvoreValorMudou(Arvore arvore, HTREEITEM item);
ListaString Catalogador_montaCaminho(Arvore arvore, HTREEITEM item);
void Catalogador_ExcluirDiretorioSelecionado(IProgressoLog pLog);
void Catalogador_ImportarArquivo(ListaString log, IProgressoLog pLog);
BOOL Catalogador_ImportarDiretorios(ListaString listaCaminho,
	BOOL bSubDiretorio, HWND frmImportarDiretorio);
void Catalogador_FinalizaImportacao(IProgressoLog pLog);
void Catalogador_ComecaImportacao(BOOL bSubDiretorios, IProgressoLog pLog);

#endif
