#include "Catalogador.h"
#include "HFSGuardaDiretorio.h"
#include "FrmSplash.h"
//#include "FrmInfoDiretorio.h"
#include "hfsguardadir/objetosbo/AbaBO.h"
#include "hfsguardadir/objetosbo/ExtensaoBO.h"
#include "hfsguardadir/objetosbo/DiretorioBO.h"
#include "hfsguardadir/objetosdao/VisaoDAO.h"
#include "hfsguardadir/objetosgui/Dialogo.h"
#include "hfsguardadir/objetosgui/EscolhaArquivo.h"
#include "hfsguardadir/objetos/Importar.h"

G_GNUC_BEGIN_IGNORE_DEPRECATIONS

struct SCatalogador Catalogador;

void Catalogador_New() {
	Catalogador.CONSULTA_DIR_PAI = g_string_new(
		"select aba, cod, ordem, coddirpai, nome, tam, tipo, modificado, " \
		"atributos, caminho, nomeaba, nomepai, caminhopai " \
		"from consultadirpai " \
		"order by 1,2,3,4");
	Catalogador.CONSULTA_DIR_FILHO = g_string_new(
		"select aba, cod, ordem, coddirpai, nome, tam, tipo, modificado, " \
		"atributos, caminho, nomeaba, nomepai, caminhopai " \
		"from consultadirfilho " \
		"order by 1,2,3,4");
	Catalogador.CONSULTA_ARQUIVO = g_string_new(
		"select aba, cod, ordem, coddirpai, nome, tam, tipo, modificado, " \
		"atributos, caminho, nomeaba, nomepai, caminhopai " \
		"from consultaarquivo " \
		"order by tipo desc, ordem");
	//Catalogador.NO_RAIZ = g_string_new("Raiz");

	Catalogador.bGravarLogImportacao = FALSE;

	Catalogador.diretorioOrdem = DiretorioOrdem_new();
	Catalogador.listaAbas = ListaAba_inicia();
	Catalogador.listaExtensoes = ListaExtensao_inicia();
	Catalogador.listaDiretorioPai = ListaDiretorio_inicia();
	Catalogador.listaDiretorioFilho = ListaDiretorio_inicia();
	Catalogador.listaArquivos = ListaDiretorio_inicia();
	
	Catalogador_waitCursor(FrmPrincipal.frmPrincipal);
	
	Catalogador_mostrarOcultarListaItensPesquisados();

	FrmSplash_Mostrar();
	
	Catalogador_CarregarDados(FrmSplash_ProgressoLog, TRUE, TRUE);
	Catalogador_CarregarAbas();
	Catalogador_tabPanelMudou();

	FrmSplash_Fechar();
	
	Catalogador_defaultCursor(FrmPrincipal.frmPrincipal);
}

void Catalogador_iniciarSistema() {
	Aba aba;
	GString* sBanco = Rotinas_AppDirPath();
	sBanco = g_string_append(sBanco, "GuardaDir.db");

    if (!Rotinas_FileExists(sBanco)){
        Rotinas_BancoConectar(sBanco);

        AbaBO_criarTabelaAbas();

		aba = Aba_new();
		aba->codigo = 1;
		aba->nome = g_string_new("DISCO1");
		aba->ordem = 0;
        AbaBO_incluirAba(aba);

        ExtensaoBO_criarTabelaExtensoes();
        DiretorioBO_criarTabelaDiretorios();
        VisaoDAO_criarVisao(g_string_new("consultadirpai"));
        VisaoDAO_criarVisao(g_string_new("consultadirfilho"));
        VisaoDAO_criarVisao(g_string_new("consultaarquivo"));
    } else
        Rotinas_BancoConectar(sBanco);

}

void Catalogador_CarregarDados(IProgressoLog pLog, gboolean bExtensao, gboolean bDiretorio) {
	Catalogador.listaAbas = AbaBO_carregarAba(pLog);
    if (bExtensao) {
		Catalogador.listaExtensoes = ExtensaoBO_carregarExtensao(pLog);
    }
    if (bDiretorio) {
		Catalogador.listaDiretorioPai = DiretorioBO_carregarDiretorio(
			Catalogador.CONSULTA_DIR_PAI, g_string_new(""), pLog);
		Catalogador.listaDiretorioFilho = DiretorioBO_carregarDiretorio(
			Catalogador.CONSULTA_DIR_FILHO, g_string_new(""), pLog);
		Catalogador.listaArquivos = DiretorioBO_carregarDiretorio(
			Catalogador.CONSULTA_ARQUIVO, g_string_new(""), pLog);
    }		
}

void Catalogador_ExcluirDados(Aba aba, GString* sCaminho) {
    DiretorioBO_excluirListaDiretorio(&Catalogador.listaDiretorioPai, aba, sCaminho);
    DiretorioBO_excluirListaDiretorio(&Catalogador.listaDiretorioFilho, aba, sCaminho);
    DiretorioBO_excluirListaDiretorio(&Catalogador.listaArquivos, aba, sCaminho);
}

void Catalogador_AddItemArvore(GtkTreeStore* arvore_store, Diretorio diretorio,
	int Nivel, GtkTreeIter* node1) {
	ListaDiretorio listaFilhos = ListaDiretorio_inicia();
	GtkTreeIter node2;
	Diretorio filho = Diretorio_new();
	guint tamListaFilhos;

	if (Nivel == 0) {
		gtk_tree_store_append(arvore_store, node1, NULL);		
		gtk_tree_store_set(arvore_store, node1, 0, ExtensaoBO_DiretorioXPM, 1, diretorio->arquivo->nome->str, -1);
	}

	listaFilhos = DiretorioBO_itensFilhos(Catalogador.listaDiretorioFilho,
		diretorio->aba->codigo, diretorio->ordem, diretorio->codigo);

	tamListaFilhos = ListaDiretorio_conta(listaFilhos);
	for (unsigned int i = 0; i < tamListaFilhos; i++) {
		filho = ListaDiretorio_pesquisaItemOrd(listaFilhos, i);

		gtk_tree_store_append(arvore_store, &node2, node1);
		gtk_tree_store_set(arvore_store, &node2, 0, ExtensaoBO_DiretorioXPM, 1, filho->arquivo->nome->str, -1);

		Catalogador_AddItemArvore(arvore_store, filho, ++Nivel, &node2);
	}
}

void Catalogador_IncluirNovaAba() {
	Aba aba;

	GString* sAba = Dialogo_entrada(FrmPrincipal.frmPrincipal, 
		"FrmPrincipal.DigitaIncluirNovaAba");

	if (Rotinas_Trim(sAba)->len > 0) {
		aba = Aba_new();
		aba->codigo = AbaBO_retMaxCodAba(Catalogador.listaAbas);
		aba->nome = Rotinas_SubString(sAba, 1, 10);
		aba->ordem = ListaAba_conta(Catalogador.listaAbas) + 1;
		AbaBO_incluirAba(aba);
		Catalogador_incluirNovaAba(aba->nome);
		Catalogador.listaAbas = ListaAba_insere(Catalogador.listaAbas, aba, aba->ordem-1);
	}
}
/*
void Catalogador_AlterarNomeAbaAtiva(IProgressoLog pLog) {
	Aba aba = Catalogador_getAbaAtual();
	GString* sAba = Dialogo_entrada2(FrmPrincipal.frmPrincipal,
		"FrmPrincipal.DigitaAlterarNomeAba", aba->nome);
	if (Rotinas_Trim(sAba)->len > 0) {
		aba->nome = Rotinas_SubString(sAba, 1, 10);
		AbaBO_alterarAba(aba);

		gint pagina = gtk_notebook_get_current_page(GTK_NOTEBOOK(FrmPrincipal.notebook1));
		GtkWidget* tabPage = gtk_notebook_get_nth_page(GTK_NOTEBOOK(FrmPrincipal.notebook1), pagina);		
		GtkWidget* tabAba = gtk_notebook_get_tab_label(GTK_NOTEBOOK(FrmPrincipal.notebook1), tabPage);
		GList* lista = gtk_container_get_children(GTK_CONTAINER(tabAba));
		GtkLabel* labAba = g_list_nth_data(lista, 1);
		gtk_label_set_label(labAba, sAba->str);

		Catalogador_CarregarDados(pLog, FALSE, TRUE);
	}
}

void Catalogador_ExcluirAbaAtiva(IProgressoLog pLog) {
	Aba aba;
	gint pagina = gtk_notebook_get_current_page(GTK_NOTEBOOK(FrmPrincipal.notebook1));
	if (pagina > 0) {
		bool res = Dialogo_confirma(FrmPrincipal.frmPrincipal, 
			"FrmPrincipal.ConfirmaExcluirAba");
		if (res) {
			Catalogador_SetCursor(GDK_WATCH);

			aba = Catalogador_getAbaAtual();
			Catalogador_ExcluirDados(aba, g_string_new(""));
			AbaBO_excluirAba(aba);
			gtk_notebook_remove_page(GTK_NOTEBOOK(FrmPrincipal.notebook1), pagina);

			Catalogador_CarregarDados(pLog, false, false);
			gtk_label_set_text(Catalogador_getLabStatus2(), "");

			Catalogador_SetCursor(GDK_ARROW);
		}
	}
	else
		Dialogo_mensagemErro(FrmPrincipal.frmPrincipal, 
			"FrmPrincipal.ValidaExcluirAba");
}
*/
void Catalogador_incluirNovaAba(GString* nomeAba) {
	GtkWidget *spPanel;
	GtkWidget *arvore;
	GtkWidget *tabela;
	GtkWidget *scrollArvore;
	GtkWidget *scrollTabela;

	arvore = gtk_tree_view_new();
	//gtk_widget_set_parent(arvore, FrmPrincipal.frmPrincipal);
	gtk_widget_set_name(GTK_WIDGET(arvore), Rotinas_concatenar("arvore_", nomeAba->str)->str);
	gtk_widget_set_visible(GTK_WIDGET(arvore), TRUE);
	gtk_widget_set_can_focus(GTK_WIDGET(arvore), TRUE);

	scrollArvore = gtk_scrolled_window_new();
	//gtk_widget_set_parent(scrollArvore, FrmPrincipal.frmPrincipal);
	gtk_widget_set_name(GTK_WIDGET(scrollArvore), Rotinas_concatenar("scrollArvore_", nomeAba->str)->str);
	gtk_widget_set_visible(scrollArvore, TRUE);
	gtk_widget_set_can_focus(scrollArvore, TRUE);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollArvore), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrollArvore), GTK_WIDGET(arvore));
	gtk_scrolled_window_set_has_frame(GTK_SCROLLED_WINDOW(scrollArvore), TRUE);

	tabela = gtk_tree_view_new();
	//gtk_widget_set_parent(tabela, FrmPrincipal.frmPrincipal);
	gtk_widget_set_name(GTK_WIDGET(tabela), Rotinas_concatenar("tabela_", nomeAba->str)->str);
	gtk_widget_set_visible(GTK_WIDGET(tabela), TRUE);
	gtk_widget_set_can_focus(GTK_WIDGET(tabela), TRUE);	

	scrollTabela = gtk_scrolled_window_new();
	//gtk_widget_set_parent(scrollTabela, FrmPrincipal.frmPrincipal);
	gtk_widget_set_name(scrollTabela, Rotinas_concatenar("scrollTabela_", nomeAba->str)->str);
	gtk_widget_set_visible(scrollTabela, TRUE);
	gtk_widget_set_can_focus(scrollTabela, TRUE);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollTabela), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrollTabela), GTK_WIDGET(tabela));
	gtk_scrolled_window_set_has_frame(GTK_SCROLLED_WINDOW(scrollTabela), TRUE);	

	spPanel = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
	//gtk_widget_set_parent(spPanel, FrmPrincipal.frmPrincipal);
	gtk_widget_set_name(GTK_WIDGET(spPanel), Rotinas_concatenar("spPanel_", nomeAba->str)->str);
	gtk_widget_set_visible(spPanel, TRUE);
	gtk_widget_set_can_focus(spPanel, TRUE);
	gtk_paned_set_position(GTK_PANED(spPanel), 250);
	gtk_paned_set_start_child(GTK_PANED(spPanel), scrollArvore);
	gtk_paned_set_start_child(GTK_PANED(spPanel), scrollTabela);

	GtkTreeSelection* selecaoArvoreLocal = gtk_tree_view_get_selection(GTK_TREE_VIEW(arvore));
	GtkTreeModel* modeloArvoreLocal = gtk_tree_view_get_model(GTK_TREE_VIEW(arvore));

	g_signal_connect((gpointer) selecaoArvoreLocal, "changed", G_CALLBACK(on_arvoreFixa_selection_changed), modeloArvoreLocal);
	g_signal_connect((gpointer) arvore, "row_collapsed", G_CALLBACK(on_arvoreFixa_row_collapsed), NULL);
	//g_signal_connect((gpointer) arvore, "button_release_event", G_CALLBACK(on_arvoreFixa_button_release_event), NULL);
	g_signal_connect((gpointer) arvore, "row_expanded", G_CALLBACK(on_arvoreFixa_row_expanded), NULL);
	//g_signal_connect((gpointer) arvore, "button_press_event", G_CALLBACK(on_arvoreFixa_button_press_event), NULL);

	//g_signal_connect((gpointer) tabela, "button_release_event", G_CALLBACK(on_tabelaFixa_button_release_event), NULL);
	g_signal_connect((gpointer) tabela, "row_activated", G_CALLBACK(on_tabelaFixa_row_activated), NULL);
		
	Arvore_cria(GTK_TREE_VIEW(arvore));
	Tabela_cria(TRUE, GTK_TREE_VIEW(tabela));

	FrmPrincipal_adicionaTabPage(GTK_NOTEBOOK(FrmPrincipal.notebook1), GTK_PANED(spPanel), nomeAba);
}

GtkTreeView* Catalogador_getArvoreAtualIndice(int nIndicePagina) {
	GtkWidget* tabPage = gtk_notebook_get_nth_page(GTK_NOTEBOOK(FrmPrincipal.notebook1), nIndicePagina);
	GtkWidget* scrollArvore = gtk_paned_get_start_child(GTK_PANED(tabPage));
	GtkTreeView* arvore = GTK_TREE_VIEW(gtk_scrolled_window_get_child(GTK_SCROLLED_WINDOW(scrollArvore)));
	return arvore;
}

GtkTreeView* Catalogador_getArvoreAtual() {
	gint pagina = gtk_notebook_get_current_page(GTK_NOTEBOOK(FrmPrincipal.notebook1));
	return Catalogador_getArvoreAtualIndice(pagina);
}

GtkPaned* Catalogador_getSplitAtual() {
	gint pagina = gtk_notebook_get_current_page(GTK_NOTEBOOK(FrmPrincipal.notebook1));
	GtkWidget* tabPage = gtk_notebook_get_nth_page(GTK_NOTEBOOK(FrmPrincipal.notebook1), pagina);
	GtkPaned* split = GTK_PANED(tabPage);
	return split;
}

GtkTreeView* Catalogador_getTabelaAtual() {
	gint pagina = gtk_notebook_get_current_page(GTK_NOTEBOOK(FrmPrincipal.notebook1));
	GtkWidget* tabPage = gtk_notebook_get_nth_page(GTK_NOTEBOOK(FrmPrincipal.notebook1), pagina);
	GtkWidget* scrollTabela = gtk_paned_get_start_child(GTK_PANED(tabPage));
	GtkTreeView* tabela = GTK_TREE_VIEW(gtk_scrolled_window_get_child(GTK_SCROLLED_WINDOW(scrollTabela)));
	return tabela;
}

GtkLabel* Catalogador_getLabStatus1() {
	/*
	GList* lista = gtk_container_get_children(GTK_CONTAINER(FrmPrincipal.barraStatus111));
	GtkFrame* frameStatus1 = g_list_nth_data(lista, 0);

	lista = gtk_container_get_children(GTK_CONTAINER(frameStatus1));
	GtkBox* hboxStatus1 = g_list_nth_data(lista, 0);

	lista = gtk_container_get_children(GTK_CONTAINER(hboxStatus1));
	GtkLabel* labStatus1 = g_list_nth_data(lista, 0);
	*/
	GtkLabel* labStatus1 = GTK_LABEL(FrmPrincipal.barraStatus111);

	return labStatus1;
}

GtkLabel* Catalogador_getLabStatus2() {
	/*
	GList* lista = gtk_container_get_children(GTK_CONTAINER(FrmPrincipal.barraStatus211));
	GtkFrame* frameStatus2 = g_list_nth_data(lista, 0);

	lista = gtk_container_get_children(GTK_CONTAINER(frameStatus2));
	GtkBox* hboxStatus2 = g_list_nth_data(lista, 0);

	lista = gtk_container_get_children(GTK_CONTAINER(hboxStatus2));
	GtkLabel* labStatus2 = g_list_nth_data(lista, 0);
	*/
	GtkLabel* labStatus2 = GTK_LABEL(FrmPrincipal.barraStatus211);

	return labStatus2;
}

void Catalogador_mostrarOcultarArvore() {
	GtkPaned* split = Catalogador_getSplitAtual();
	GtkWidget* scrollArvore = gtk_paned_get_start_child(GTK_PANED(split));

	gboolean bVisivel = gtk_widget_get_visible(scrollArvore);
	gtk_widget_set_visible(scrollArvore, !bVisivel);
}

void Catalogador_mostrarOcultarListaItensPesquisados() {
	GtkPaned* split = GTK_PANED(FrmPrincipal.spPesquisa);
	GtkWidget* scrollTabela = gtk_paned_get_end_child(GTK_PANED(split));

	gboolean bVisivel = gtk_widget_get_visible(scrollTabela);
	gtk_widget_set_visible(scrollTabela, !bVisivel);
}

void Catalogador_CarregarArvore(GtkTreeView* arvore, Aba aba) {
	Diretorio dir = Diretorio_new();
	GtkTreeIter nodeRaiz;
	GtkTreeModel* arvore_modelo = gtk_tree_view_get_model(arvore);
	GtkTreeStore* arvore_store = GTK_TREE_STORE(arvore_modelo);
	
	Arvore_limpar(arvore);

	guint tamLista = ListaDiretorio_conta(Catalogador.listaDiretorioPai);
	for (unsigned int i = 0; i < tamLista; i++) {
		dir = ListaDiretorio_pesquisaItemOrd(Catalogador.listaDiretorioPai, i);

		if (dir->aba->codigo == aba->codigo) {
			Catalogador_AddItemArvore(arvore_store, dir, 0, &nodeRaiz);
		}
	}
}

void Catalogador_CarregarAbas() {
	GtkTreeView* tvAba;
	Aba aba = Aba_new();

	int nMaximum = ListaAba_conta(Catalogador.listaAbas) - 1;
	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(FrmPrincipal.pbImportarDiretorio), 0);
	
	for (int i = 0; i < (nMaximum+1); i++) {
		aba = ListaAba_pesquisaItemOrd(Catalogador.listaAbas, i);

		if (i > 0) {
			Catalogador_incluirNovaAba(aba->nome);
		}
		tvAba = Catalogador_getArvoreAtualIndice(i);
		Catalogador_CarregarArvore(tvAba, aba);

		gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(FrmSplash.pb1),
			Rotinas_calculaProgresso(nMaximum, i));
	}
}

Aba Catalogador_getAbaAtual() {
	gint pagina = gtk_notebook_get_current_page(GTK_NOTEBOOK(FrmPrincipal.notebook1));
	return AbaBO_pegaAbaPorOrdem(
		Catalogador.listaAbas, pagina + 1);
}

void Catalogador_CarregarArquivosLista(gboolean bLista1, GtkTreeView* tabela, const GString* sCaminho) {
	GString* sPaiCaminho = g_string_new("");
	ListaDiretorio listaLocal = ListaDiretorio_inicia();
	int nAba;
	Diretorio dir = Diretorio_new();
	listaLocal = ListaDiretorio_inicia();
	gint posicao = 0;
	GString* scaminho = g_string_new(sCaminho->str);

	Tabela_limpar(tabela);

	if (bLista1) {
		sPaiCaminho = g_string_new(scaminho->str);
		if (!Rotinas_comparar(Rotinas_SubString(scaminho, scaminho->len, 1), Rotinas_BARRA_INVERTIDA)) {
			scaminho = g_string_append(scaminho, Rotinas_BARRA_INVERTIDA);
		}
		nAba = Catalogador_getAbaAtual()->codigo;

		guint tamLista = ListaDiretorio_conta(Catalogador.listaArquivos);
		for (unsigned int i = 0; i < tamLista; i++) {
			dir = ListaDiretorio_pesquisaItemOrd(Catalogador.listaArquivos, i);

			if (dir->aba->codigo == nAba) {
				if (g_string_equal(dir->caminhoPai, sPaiCaminho)) {
					if (Rotinas_StartsStr(scaminho, dir->caminho)) {
						listaLocal = ListaDiretorio_insere(listaLocal, dir, posicao);
						posicao++;
					}
				}
			}
		}
	}
	else {
		guint tamLista = ListaDiretorio_conta(Catalogador.listaArquivos);
		for (unsigned int i = 0; i < tamLista; i++) {
			dir = ListaDiretorio_pesquisaItemOrd(Catalogador.listaArquivos, i);

			if (Rotinas_ContainsStr(Rotinas_UpperCase(dir->caminho),
				Rotinas_UpperCase(scaminho))) {
				listaLocal = ListaDiretorio_insere(listaLocal, dir, posicao);
				posicao++;
			}
		}
	}
	Tabela_carregar(tabela, bLista1, listaLocal, Catalogador.listaExtensoes, GTK_PROGRESS_BAR(FrmPrincipal.pbImportarDiretorio));

}

void Catalogador_TamTotalDiretorio(const GString* sCaminho) {
	long conta;
	int nAba;
	unsigned long long soma, tam;
	Diretorio dir = Diretorio_new();
	GString* status = g_string_new("");

	conta = 0;
	soma = 0;

	guint tamLista = ListaDiretorio_conta(Catalogador.listaArquivos);
	for (unsigned int i = 0; i < tamLista; i++) {
		dir = ListaDiretorio_pesquisaItemOrd(Catalogador.listaArquivos, i);

		nAba = Catalogador_getAbaAtual()->codigo;
		if (dir->aba->codigo == nAba) {
			if (dir->tipo->codigo != 'D') {
				if (Rotinas_Trim(sCaminho)->len > 0) {
					if (Rotinas_StartsStr(sCaminho, dir->caminho)) {
						conta++;
						tam = dir->arquivo->tamanho;
						soma = soma + tam;
					}
				}
				else {
					conta++;
					tam = dir->arquivo->tamanho;
					soma = soma + tam;
				}
			}
		}
	}

	status = Rotinas_concatenar("Quantidade Total: ", Rotinas_ULongToStr(conta)->str);
	status = Rotinas_concatenar1(status, ", Tamanho Total: ", Rotinas_MontaTamanho(soma)->str);
	gtk_label_set_text(Catalogador_getLabStatus1(), status->str);
}
/*
ListaString Catalogador_montaCaminho(const GString* sCaminho, gboolean bRemover) {
	//sCaminho = NO_RAIZ + Rotinas.BARRA_INVERTIDA + sCaminho;
	ListaString sl = Rotinas_SListSeparador(sCaminho, Rotinas_BARRA_INVERTIDA[0]);
	guint tam = ListaString_conta(sl);
	GString* item = ListaString_pesquisaItemOrd(sl, tam - 1);

	if (Rotinas_Trim(item)->len == 0) {
		ListaString_removeItemOrd(&sl, tam - 1);
	}
	if (bRemover) {
		ListaString_removeItemOrd(&sl, tam - 1);
	}
	return sl;
}

void Catalogador_Pesquisar() {
	GtkTreeView* arvoreLocal = Catalogador_getArvoreAtual();
	GtkTreeModel* arvore_modelo = gtk_tree_view_get_model(arvoreLocal);
	GtkTreeStore* arvore_store = GTK_TREE_STORE(arvore_modelo);

	if (gtk_tree_model_iter_n_children(arvore_modelo, NULL) > 0) {

		const gchar* texto = gtk_entry_get_text(GTK_ENTRY(FrmPrincipal.edtPesquisa));
		GtkVPaned* splitPesquisa = GTK_VPANED(FrmPrincipal.spPesquisa);
		GtkWidget* scrollTabelaPesquisa = gtk_paned_get_child2(GTK_PANED(splitPesquisa));

		if (strlen(texto) >= 2) {
			gtk_widget_set_visible(scrollTabelaPesquisa, TRUE);						
			Catalogador_CarregarArquivosLista(FALSE, 
				GTK_TREE_VIEW(FrmPrincipal.tabelaPesquisa), g_string_new(texto));
			Arvore_selecionarPrimeiroItem(arvoreLocal);
		}
		else {
			gtk_widget_set_visible(scrollTabelaPesquisa, FALSE);
			Tabela_limpar(GTK_TREE_VIEW(FrmPrincipal.tabelaPesquisa));
			Dialogo_mensagemInfo(FrmPrincipal.frmPrincipal, "FrmPrincipal.TamMaxPesquisa");
		}
	}
}

void Catalogador_PesquisarArvoreDiretorio(const GString* sCaminho, Aba aba) {
	gtk_notebook_set_current_page(GTK_NOTEBOOK(FrmPrincipal.notebook1), aba->ordem - 1);

	GtkTreeView* arvore = Catalogador_getArvoreAtual();
	GtkTreeModel* arvore_modelo = gtk_tree_view_get_model(arvore);
	GtkTreeStore* arvore_store = GTK_TREE_STORE(arvore_modelo);

	ListaString sl = Catalogador_montaCaminho(sCaminho, FALSE);
	GtkTreePath* path = Arvore_encontrarCaminhoPorNome(arvore, sl);

	if (path != NULL) {
		gtk_tree_view_expand_to_path(arvore, path);

		GtkTreeSelection *selecao = gtk_tree_view_get_selection(arvore);
		gtk_tree_selection_select_path(selecao, path);
		gtk_tree_view_scroll_to_cell(arvore, path, NULL, FALSE, 0, 0);
	}
}
*/
ListaString Catalogador_montaCaminhoStatus(GtkTreeModel* arvore_modelo, GtkTreeIter iter) {
	GValue value = { 0, };
	GtkTreeIter iterPai;
	GtkTreeStore* arvore_store = GTK_TREE_STORE(arvore_modelo);
	ListaString lista = ListaString_inicia();
	GString *texto;
	gint posicao = 0;

	do {
		gtk_tree_model_get_value(arvore_modelo, &iter, 1, &value);
		texto = g_string_new(g_value_get_string(&value));
		g_value_unset(&value);

		if (texto->len > 0) {
			lista = ListaString_insere(lista, texto, posicao);
			posicao++;

			gtk_tree_model_iter_parent(arvore_modelo, &iterPai, &iter);
			iter = iterPai;
		}
		else {
			break;
		}		
	} while (gtk_tree_store_iter_is_valid(arvore_store, &iter));

	lista = ListaString_inverter(lista);

	return lista;
}

void Catalogador_LerArvoreDiretorio(GtkTreeModel* arvore_modelo, GtkTreeIter iter,
	GtkLabel* barraStatus) {	
	GString* texto = g_string_new("");
	GString* caminho = g_string_new("");
	ListaString lista = Catalogador_montaCaminhoStatus(arvore_modelo, iter);
	guint tamlista = ListaString_conta(lista);

	for (unsigned int i = 0; i < tamlista; i++) {
		texto = ListaString_pesquisaItemOrd(lista, i);

		caminho = Rotinas_concatenar2(caminho, texto, Rotinas_BARRA_INVERTIDA);
	}

	if (tamlista > 0) {
		caminho = Rotinas_SubString(caminho, 1, caminho->len - 1);
		gtk_label_set_text(barraStatus, caminho->str);
	}
}

void Catalogador_ListarArquivos(GtkTreeView* tabela, GtkTreeView* arvore, GtkTreeIter iter) {
	GtkTreeModel* arvore_modelo = gtk_tree_view_get_model(arvore);
	GtkTreeStore* arvore_store = GTK_TREE_STORE(arvore_modelo);
	GtkTreeSelection *arvore_selecao = gtk_tree_view_get_selection(arvore);
	GString* stexto;
	const gchar* texto;

	if (gtk_tree_selection_iter_is_selected(arvore_selecao, &iter)) {
		Catalogador_LerArvoreDiretorio(arvore_modelo, iter, Catalogador_getLabStatus2());
		
		texto = gtk_label_get_text(Catalogador_getLabStatus2());
		stexto = g_string_new(texto);

		Catalogador_CarregarArquivosLista(TRUE, tabela, stexto);
		Catalogador_TamTotalDiretorio(stexto);
	}
}
void Catalogador_tabPanelMudou() {
	GtkTreeView* arvore = Catalogador_getArvoreAtual();
	GtkTreeModel* arvore_modelo = gtk_tree_view_get_model(arvore);
	GtkTreeStore* arvore_store = GTK_TREE_STORE(arvore_modelo);
	GtkTreeSelection *arvore_selecao = gtk_tree_view_get_selection(arvore);

	GtkTreeView* tabela = Catalogador_getTabelaAtual();
	GtkTreeModel* tabela_modelo = gtk_tree_view_get_model(tabela);
	GtkListStore* tabela_store = GTK_LIST_STORE(tabela_modelo);

	GtkTreeIter iter;

	if (gtk_tree_model_iter_n_children(arvore_modelo, NULL) > 0) {
		if (gtk_tree_model_get_iter_first(arvore_modelo, &iter)) {
			Catalogador_ListarArquivos(tabela, arvore, iter);
		}
	}
}
/*
Aba Catalogador_getAbaSelecionada() {
	return Catalogador_getAbaAtual();
}

void Catalogador_DuploCliqueLista(const GString* nome, const GString* tipo) {
	if (g_string_equal(tipo, Rotinas_getRecurso("TipoLista.diretorio") )) {
		Catalogador_SetCursor(GDK_WATCH);
		
		const gchar* texto = gtk_label_get_text(Catalogador_getLabStatus2());
		GString* sCaminho = g_string_new(texto);

		if (Rotinas_testaSeparadorArquivo(sCaminho)) {
			sCaminho = g_string_append(sCaminho, nome->str);
		}
		else {
			sCaminho = Rotinas_concatenar1(sCaminho, Rotinas_BARRA_INVERTIDA, nome->str);
		}

		Catalogador_PesquisarArvoreDiretorio(sCaminho, Catalogador_getAbaAtual());

		Catalogador_SetCursor(GDK_ARROW);
	}
}

void Catalogador_EncontrarItemLista(const GString* nomeAba, const GString* nome, const GString* caminho) {
	Catalogador_SetCursor(GDK_WATCH);

	Aba aba = AbaBO_pegaAbaPorNome(Catalogador.listaAbas, (GString*)nomeAba);
	Catalogador_PesquisarArvoreDiretorio(caminho, aba);

	GtkTreeView* tabela = Catalogador_getTabelaAtual();
	GtkTreePath* path = Tabela_encontrarCaminhoPorNome(tabela, (GString*)nome);

	if (path != NULL) {
		GtkTreeSelection *selecao = gtk_tree_view_get_selection(tabela);
		gtk_tree_selection_select_path(selecao, path);
		gtk_tree_view_scroll_to_cell(tabela, path, NULL, FALSE, 0, 0);
	}

	Catalogador_SetCursor(GDK_ARROW);
}

int Catalogador_verificaNomeDiretorio(const GString* sCaminho, RotuloRaiz sRotuloRaiz) {
	sRotuloRaiz->rotulo = DiretorioBO_removerDrive((GString*)sCaminho);

	if (sRotuloRaiz->rotulo->len == 0) {

		sRotuloRaiz->rotulo = Dialogo_entrada(FrmPrincipal.frmPrincipal,
			"FrmPrincipal.DigitaNomeDiretorio");

		if ((sRotuloRaiz->rotulo != NULL)
			&& (Rotinas_Trim(sRotuloRaiz->rotulo)->len > 0)) {
			sRotuloRaiz->rotulo = Rotinas_Trim(sRotuloRaiz->rotulo);

			if (sRotuloRaiz->rotulo->len > 0) {
				return 1;
			}
			else {
				Dialogo_mensagemInfo(FrmPrincipal.frmPrincipal, 
					"FrmPrincipal.ValidaNomeDiretorio");
				return 0;
			}
		}
		else {
			return 0;
		}
	}
	else if (Rotinas_cPos(Rotinas_BARRA_INVERTIDA,
		sRotuloRaiz->rotulo->str) > 0) {
		sRotuloRaiz->rotulo = Rotinas_SubString(sRotuloRaiz->rotulo,
			Rotinas_cLastDelimiter(Rotinas_BARRA_INVERTIDA,
				sRotuloRaiz->rotulo->str) + 1,
			sRotuloRaiz->rotulo->len);
		return 2;
	}
	else {
		return 3;
	}
}

void Catalogador_ExportarArquivo(TipoExportar tipo, IProgressoLog pLog) {
	GString* sExtensao = g_string_new("");

	switch (tipo) {
	case teTXT:
		sExtensao = g_string_new("txt");
		break;
	case teCSV:
		sExtensao = g_string_new("csv");
		break;
	case teHTML:
		sExtensao = g_string_new("html");
		break;
	case teXML:
		sExtensao = g_string_new("xml");
		break;
	case teSQL:
		sExtensao = g_string_new("sql");
		break;
	}

	Aba aba = Catalogador_getAbaAtual();
	GString* sDiretorio = Rotinas_AppDirPath();
	GString* sArquivo = Rotinas_concatenar1(aba->nome, ".", sExtensao->str);
	GString* arquivo = EscolhaArquivo_salvarArquivo2(FrmPrincipal.frmPrincipal, 
		EscolhaArquivo_FILTRO_EXPORTAR, sDiretorio, sArquivo);
	if (arquivo->len > 0) {
		//GFileInfo* info = Rotinas_getFileInfo(arquivo);				
		if (!Rotinas_FileExists(arquivo)) {
			Catalogador_SetCursor(GDK_WATCH);

			DiretorioBO_exportarDiretorio(tipo, aba, arquivo, pLog);
			
			Catalogador_SetCursor(GDK_ARROW);

			Dialogo_mensagemErro(FrmPrincipal.frmPrincipal, "FrmPrincipal.SucessoExportar");
		}
	}
}

void Catalogador_ExcluirDiretorioSelecionado(IProgressoLog pLog)
{
	GtkTreeView* arvore = Catalogador_getArvoreAtual();
	GtkTreeModel* arvore_modelo = gtk_tree_view_get_model(arvore);
	GtkTreeStore* arvore_store = GTK_TREE_STORE(arvore_modelo);
	GtkTreeSelection *arvore_selecao = gtk_tree_view_get_selection(arvore);
	
	GtkTreeIter iter;

	if (gtk_tree_selection_get_selected(arvore_selecao, &arvore_modelo, &iter))
	{
		if (gtk_tree_selection_iter_is_selected(arvore_selecao, &iter)) {
			GtkTreeView* tabela = Catalogador_getTabelaAtual();

			gboolean res = Dialogo_confirma(FrmPrincipal.frmPrincipal, "FrmPrincipal.ExcluirDiretorioSelecionado");
			if (res) {
				Catalogador_SetCursor(GDK_WATCH);

				ListaString sl = Catalogador_montaCaminhoStatus(arvore_modelo, iter);
				GString* caminho = Rotinas_SListTexto(sl);
				
				Aba aba = Catalogador_getAbaAtual();

				DiretorioBO_excluirDiretorio(aba, caminho);
				Catalogador_ExcluirDados(aba, caminho);

				gtk_tree_store_remove(arvore_store, &iter);
				Tabela_limpar(tabela);

				Catalogador_CarregarDados(pLog, FALSE, FALSE);

				Catalogador_SetCursor(GDK_ARROW);
			}
		}
	}
}

void Catalogador_ImportarArquivo(ListaString log, IProgressoLog pLog) {
	int nResultado;

	GString* arquivo = EscolhaArquivo_abrirArquivo(FrmPrincipal.frmPrincipal, EscolhaArquivo_FILTRO_XML);
	//FileInfo arquivo = new FileInfo(EscolhaArquivo.NomeArquivo);

	if (Rotinas_FileExists(arquivo)) {
		Catalogador_SetCursor(GDK_WATCH);

		nResultado = DiretorioBO_importarDiretorioViaXML(
			Catalogador_getAbaAtual(), arquivo, Catalogador.listaDiretorioPai, pLog);
		if (nResultado == -1) {
			Dialogo_mensagemErro(FrmPrincipal.frmPrincipal, "FrmPrincipal.ImportacaoNaoRealizada");
		}
		else if (nResultado == -2) {
			Dialogo_mensagemErro(FrmPrincipal.frmPrincipal, "FrmPrincipal.DiretorioExisteCatalogo");
		}
		else {
			Catalogador_FinalizaImportacao(pLog);
		}
		Catalogador_SetCursor(GDK_ARROW);
	}
	
}

gboolean Catalogador_ImportarDiretorios(ListaString listaCaminho,
	gboolean bSubDiretorio, GtkWidget* frmImportarDiretorio) {
	int nAba, nRotuloRaiz, nCodDirRaiz;
	RotuloRaiz sRotuloRaiz = RotuloRaiz_new();
	GString *sCaminhoSemDrive, *sCaminho = g_string_new("");
	Importar importar = Importar_new();
	gint posicao = 0;

	nAba = Catalogador_getAbaAtual()->codigo;
	nCodDirRaiz = DiretorioBO_retMaxCodDir(nAba,
		Catalogador.listaDiretorioPai);

	guint tamLista = ListaString_conta(listaCaminho);
	for (unsigned int i = 0; i < tamLista; i++) {
		sCaminho = ListaString_pesquisaItemOrd(listaCaminho, i);

		nRotuloRaiz = Catalogador_verificaNomeDiretorio(sCaminho, sRotuloRaiz);
		if (nRotuloRaiz > 0) {
			importar = Importar_new();
			importar->aba = nAba;
			importar->codDirRaiz = nCodDirRaiz;
			importar->rotuloRaiz = sRotuloRaiz->rotulo;
			if (nRotuloRaiz == 1) {
				importar->nomeDirRaiz = sRotuloRaiz->rotulo;
			}
			else if (nRotuloRaiz == 2) {
				sCaminhoSemDrive = DiretorioBO_removerDrive(sCaminho);
				importar->nomeDirRaiz = Rotinas_SubString(
					sCaminhoSemDrive, 1,
					Rotinas_cLastDelimiter(Rotinas_BARRA_INVERTIDA,
						sCaminhoSemDrive->str) - 1);
			}
			else if (nRotuloRaiz == 3) {
				importar->nomeDirRaiz = g_string_new("");
			}
			importar->caminho = sCaminho;

			FrmImportarDiretorio.listaImportar = ListaImportar_insere(
				FrmImportarDiretorio.listaImportar, importar, posicao);
			posicao++;
			nCodDirRaiz++;
		}
	}

	FrmImportarDiretorio.bSubDiretorio = bSubDiretorio;

	if (bSubDiretorio) {
		FrmImportarDiretorio_Mostrar();
		FrmImportarDiretorio_Importar();
		FrmImportarDiretorio_Fechar();
		return true;
	}
	else {
		if (!DiretorioBO_verificaCodDir(
			importar->aba, importar->rotuloRaiz,
			Catalogador.listaDiretorioPai)) {
			FrmImportarDiretorio_Mostrar();
			FrmImportarDiretorio_Importar();
			FrmImportarDiretorio_Fechar();
			return true;
		}
		else {
			Dialogo_mensagemErro(FrmPrincipal.frmPrincipal,
				"FrmPrincipal.DiretorioExisteCatalogo");

			return FALSE;
		}
	}

}

void Catalogador_FinalizaImportacao(IProgressoLog pLog) {
	GtkTreeView* tvAba;

	Catalogador_SetCursor(GDK_WATCH);

	Catalogador_CarregarDados(pLog, TRUE, TRUE);
	tvAba = Catalogador_getArvoreAtual();
	Catalogador_CarregarArvore(tvAba, Catalogador_getAbaAtual());
	Catalogador_tabPanelMudou();

	Catalogador_SetCursor(GDK_ARROW);

	Dialogo_mensagemInfo(FrmPrincipal.frmPrincipal, "FrmPrincipal.DirImportacaoSucesso");
}


void Catalogador_ComecaImportacao(gboolean bSubDiretorios, IProgressoLog pLog) {
	GString* sCaminho = g_string_new("");
	ListaString listaCaminho;
	gint posicao = 0;
	//FrmImportarDiretorio frmImportarDiretorio;

	sCaminho = EscolhaArquivo_abrirDiretorio(FrmPrincipal.frmPrincipal);
	if (sCaminho->len > 0) {
		//FileInfo arquivo = new FileInfo(EscolhaArquivo.NomeArquivo);
		if (Rotinas_DirectoryExists(sCaminho)) {
			Catalogador_SetCursor(GDK_WATCH);
			//sCaminho = arquivo.FullName;

			FrmImportarDiretorio.frmImportarDiretorio = FrmImportarDiretorio_Criar();
			listaCaminho = ListaString_inicia();

			if (bSubDiretorios) {
				DiretorioBO_carregarSubDiretorios(sCaminho, listaCaminho);
			}
			else {
				listaCaminho = ListaString_insere(listaCaminho, sCaminho, posicao);
				posicao++;
			}

			if (Catalogador_ImportarDiretorios(listaCaminho, bSubDiretorios,
				FrmImportarDiretorio.frmImportarDiretorio)) {
				Catalogador_FinalizaImportacao(pLog);
			}

			Catalogador_SetCursor(GDK_ARROW);
		}
	}

}

void Catalogador_InformacoesDiretorioArquivo()
{
	GtkTreeView* tabela = Catalogador_getTabelaAtual();
	GtkTreeModel* tabela_modelo = gtk_tree_view_get_model(tabela);
	GtkListStore* tabela_store = GTK_LIST_STORE(tabela_modelo);
	GtkTreeIter iter;
	GtkTreeSelection *tabela_selecao = gtk_tree_view_get_selection(GTK_TREE_VIEW(tabela));

	if (gtk_tree_selection_get_selected(tabela_selecao, &tabela_modelo, &iter)) {
		if (gtk_tree_selection_iter_is_selected(tabela_selecao, &iter)) {
			//frmInfo = new FrmInfoDiretorio();
			Aba aba = Catalogador_getAbaSelecionada();
			Diretorio dir = Tabela_getLinhaSelecionada(tabela, FALSE);
			dir->aba->nome = aba->nome;
			FrmInfoDiretorio.frmInfoDiretorio = FrmInfoDiretorio_Criar();
			FrmInfoDiretorio_setDiretorio(dir);
			FrmInfoDiretorio_Mostrar();
		}
	}
}
*/
void Catalogador_waitCursor(GtkWidget* widget) {
	GdkDisplay* display = gtk_widget_get_display(widget);
	GdkCursor* cursor = gdk_cursor_new_from_name("wait", NULL);
	gdk_surface_set_cursor(gtk_native_get_surface(gtk_widget_get_native(widget)), cursor);
}

void Catalogador_defaultCursor(GtkWidget* widget) {
	GdkDisplay* display = gtk_widget_get_display(widget);
	GdkCursor* cursor = gdk_cursor_new_from_name("default", NULL);
	gdk_surface_set_cursor(gtk_native_get_surface(gtk_widget_get_native(widget)), cursor);
}
