#ifndef CATALOGADOR_H
#define CATALOGADOR_H

#include "hfsguardadir/objetos/Aba.h"
#include "hfsguardadir/objetos/Diretorio.h"
#include "hfsguardadir/objetos/DiretorioOrdem.h"
#include "hfsguardadir/objetos/Extensao.h"
#include "hfsguardadir/objetosgui/Tabela.h"
#include "hfsguardadir/objetosgui/Arvore.h"
#include "hfsguardadir/comum/ListaString.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/catalogador/RotuloRaiz.h"
#include "FrmPrincipal.h"
//#include "FrmImportarDiretorio.h"

struct SCatalogador {
	GString* CONSULTA_DIR_PAI;
	GString* CONSULTA_DIR_FILHO;
	GString* CONSULTA_ARQUIVO;

	gboolean bGravarLogImportacao;
	DiretorioOrdem diretorioOrdem;
	ListaAba listaAbas;
	ListaDiretorio listaDiretorioPai;
	ListaExtensao listaExtensoes;

	ListaDiretorio listaDiretorioFilho;
	ListaDiretorio listaArquivos;	
};
extern struct SCatalogador Catalogador;

void Catalogador_New();
void Catalogador_iniciarSistema();
void Catalogador_CarregarDados(IProgressoLog pLog, gboolean bExtensao, gboolean bDiretorio);
void Catalogador_ExcluirDados(Aba aba, GString* sCaminho);
void Catalogador_AddItemArvore(GtkTreeStore* arvore_store, Diretorio diretorio, int Nivel, GtkTreeIter* node1);
void Catalogador_IncluirNovaAba();
/*
void Catalogador_AlterarNomeAbaAtiva(IProgressoLog pLog);
void Catalogador_ExcluirAbaAtiva(IProgressoLog pLog);
*/
void Catalogador_incluirNovaAba(GString* nomeAba);
GtkTreeView* Catalogador_getArvoreAtualIndice(int nIndicePagina);
GtkTreeView* Catalogador_getArvoreAtual();
GtkPaned* Catalogador_getSplitAtual();
GtkTreeView* Catalogador_getTabelaAtual();
GtkLabel* Catalogador_getLabStatus1();
GtkLabel* Catalogador_getLabStatus2();
void Catalogador_mostrarOcultarArvore();
void Catalogador_mostrarOcultarListaItensPesquisados();
void Catalogador_CarregarArvore(GtkTreeView* arvore, Aba aba);
void Catalogador_CarregarAbas();

Aba Catalogador_getAbaAtual();
void Catalogador_CarregarArquivosLista(gboolean bLista1, GtkTreeView* tabela, const GString* sCaminho);
void Catalogador_TamTotalDiretorio(const GString* sCaminho);
/*
ListaString Catalogador_montaCaminho(const GString* sCaminho, gboolean bRemover);
ListaString Catalogador_montaCaminhoStatus(GtkTreeModel* arvore_modelo, GtkTreeIter iter);
void Catalogador_Pesquisar();
void Catalogador_PesquisarArvoreDiretorio(const GString* sCaminho, Aba aba);
*/
void Catalogador_LerArvoreDiretorio(GtkTreeModel* arvore_modelo, GtkTreeIter iter,
	GtkLabel* barraStatus);
void Catalogador_ListarArquivos(GtkTreeView* tabela, GtkTreeView* arvore, GtkTreeIter iter);
void Catalogador_tabPanelMudou();
/*
void Catalogador_DuploCliqueLista(const GString* nome, const GString* tipo);
void Catalogador_EncontrarItemLista(const GString* nomeAba, const GString* nome, const GString* caminho);
int Catalogador_verificaNomeDiretorio(const GString* sCaminho, RotuloRaiz sRotuloRaiz);
void Catalogador_ExportarArquivo(TipoExportar tipo, IProgressoLog pLog);
void Catalogador_ExcluirDiretorioSelecionado(IProgressoLog pLog);
void Catalogador_ImportarArquivo(ListaString log, IProgressoLog pLog);
gboolean Catalogador_ImportarDiretorios(ListaString listaCaminho,
	gboolean bSubDiretorio, GtkWidget* frmImportarDiretorio);
void Catalogador_FinalizaImportacao(IProgressoLog pLog);
void Catalogador_ComecaImportacao(gboolean bSubDiretorios, IProgressoLog pLog);
void Catalogador_InformacoesDiretorioArquivo();
*/
void Catalogador_waitCursor(GtkWidget* widget);
void Catalogador_defaultCursor(GtkWidget* widget);

#endif
