#include "../objetosbo/ExtensaoBO.h"
#include "../objetosgui/Tabela.h"
//#include "../catalogador/Catalogador.h"
//#include "FrmPrincipal.h"

G_GNUC_BEGIN_IGNORE_DEPRECATIONS

void Tabela_cria(gboolean bTabelaDir, GtkTreeView *tabela)
{
	GtkTreeViewColumn *colunaNome;
	GtkTreeViewColumn *colunaTamanho;
	GtkTreeViewColumn *colunaTipo;
	GtkTreeViewColumn *colunaModificado;
	GtkTreeViewColumn *colunaAtributos;
	GtkTreeViewColumn *colunaCaminho;
	GtkTreeViewColumn *colunaAba = NULL;
	GtkListStore *store;
	GtkTreeModel *modelo;
	GtkTreeSelection *selecao;

	if (!bTabelaDir) {
		colunaAba = gtk_tree_view_column_new_with_attributes("Aba", gtk_cell_renderer_text_new(), "text", 7, NULL);
		gtk_tree_view_column_set_resizable(colunaAba, TRUE);
		gtk_tree_view_column_set_sizing(colunaAba, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
		gtk_tree_view_column_set_title(colunaAba, "Aba");
		gtk_tree_view_column_set_sort_indicator(colunaAba, TRUE);
		gtk_tree_view_column_set_sort_column_id(colunaAba, 7);
	}

	colunaCaminho = gtk_tree_view_column_new_with_attributes("Caminho", gtk_cell_renderer_text_new(), "text", 6, NULL);
	gtk_tree_view_column_set_resizable(colunaCaminho, TRUE);
	gtk_tree_view_column_set_sizing(colunaCaminho, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
	gtk_tree_view_column_set_title(colunaCaminho, "Caminho");
	gtk_tree_view_column_set_sort_indicator(colunaCaminho, TRUE);
	gtk_tree_view_column_set_sort_column_id(colunaCaminho, 6);

	colunaAtributos = gtk_tree_view_column_new_with_attributes("Atributos", gtk_cell_renderer_text_new(), "text", 5, NULL);
	gtk_tree_view_column_set_resizable(colunaAtributos, TRUE);
	gtk_tree_view_column_set_sizing(colunaAtributos, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
	gtk_tree_view_column_set_title(colunaAtributos, "Atributos");
	gtk_tree_view_column_set_sort_indicator(colunaAtributos, TRUE);
	gtk_tree_view_column_set_sort_column_id(colunaAtributos, 5);

	colunaModificado = gtk_tree_view_column_new_with_attributes("Modificado", gtk_cell_renderer_text_new(), "text", 4, NULL);
	gtk_tree_view_column_set_resizable(colunaModificado, TRUE);
	gtk_tree_view_column_set_sizing(colunaModificado, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
	gtk_tree_view_column_set_title(colunaModificado, "Modificado");
	gtk_tree_view_column_set_sort_indicator(colunaModificado, TRUE);
	gtk_tree_view_column_set_sort_column_id(colunaModificado, 4);

	colunaTipo = gtk_tree_view_column_new_with_attributes("Tipo", gtk_cell_renderer_text_new(), "text", 3, NULL);
	gtk_tree_view_column_set_resizable(colunaTipo, TRUE);
	gtk_tree_view_column_set_sizing(colunaTipo, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
	gtk_tree_view_column_set_title(colunaTipo, "Tipo");
	gtk_tree_view_column_set_sort_indicator(colunaTipo, TRUE);
	gtk_tree_view_column_set_sort_column_id(colunaTipo, 3);

	colunaTamanho = gtk_tree_view_column_new_with_attributes("Tamanho", gtk_cell_renderer_text_new(), "text", 2, NULL);
	gtk_tree_view_column_set_resizable(colunaTamanho, TRUE);
	gtk_tree_view_column_set_sizing(colunaTamanho, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
	gtk_tree_view_column_set_title(colunaTamanho, "Tamanho");
	gtk_tree_view_column_set_sort_indicator(colunaTamanho, TRUE);
	gtk_tree_view_column_set_sort_column_id(colunaTamanho, 2);

	colunaNome = gtk_tree_view_column_new();
	gtk_tree_view_column_set_title(colunaNome, "Nome");

	GtkCellRenderer* pixbufRender = gtk_cell_renderer_pixbuf_new();
	gtk_tree_view_column_pack_start(colunaNome, pixbufRender, FALSE);
	gtk_tree_view_column_add_attribute(colunaNome, pixbufRender, "pixbuf", 0);

	GtkCellRenderer* textRender = gtk_cell_renderer_text_new();
	gtk_tree_view_column_pack_start(colunaNome, textRender, TRUE);
	gtk_tree_view_column_add_attribute(colunaNome, textRender, "text", 1);

	gtk_tree_view_column_set_resizable(colunaNome, TRUE);
	gtk_tree_view_column_set_sizing(colunaNome, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
	gtk_tree_view_column_set_sort_indicator(colunaNome, TRUE);
	gtk_tree_view_column_set_sort_column_id(colunaNome, 1);

	gtk_tree_view_append_column(GTK_TREE_VIEW(tabela), colunaNome);
	gtk_tree_view_append_column(GTK_TREE_VIEW(tabela), colunaTamanho);
	gtk_tree_view_append_column(GTK_TREE_VIEW(tabela), colunaTipo);
	gtk_tree_view_append_column(GTK_TREE_VIEW(tabela), colunaModificado);
	gtk_tree_view_append_column(GTK_TREE_VIEW(tabela), colunaAtributos);
	gtk_tree_view_append_column(GTK_TREE_VIEW(tabela), colunaCaminho);
	if (!bTabelaDir) {
		gtk_tree_view_append_column(GTK_TREE_VIEW(tabela), colunaAba);
	}

	if (bTabelaDir) {
		store = gtk_list_store_new(7, GDK_TYPE_PIXBUF,
			G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	}
	else {
		store = gtk_list_store_new(8, GDK_TYPE_PIXBUF,
			G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	}
	modelo = GTK_TREE_MODEL(store);
	gtk_tree_view_set_model(GTK_TREE_VIEW(tabela), modelo);

	selecao = gtk_tree_view_get_selection(GTK_TREE_VIEW(tabela));
	gtk_tree_selection_set_mode(selecao, GTK_SELECTION_SINGLE);
	gtk_tree_view_columns_autosize(GTK_TREE_VIEW(tabela));

}

void Tabela_limpar(GtkTreeView* tabela) {
	GtkTreeModel* tabela_modelo = gtk_tree_view_get_model(tabela);
	GtkListStore* tabela_store = GTK_LIST_STORE(tabela_modelo);

	gtk_list_store_clear(tabela_store);
}

void Tabela_adicionaItem(GtkTreeView* tabela, gboolean bTabelaDir, Diretorio dir,
	ListaExtensao listaExtensao) {
	GtkTreeModel* tabela_modelo = gtk_tree_view_get_model(tabela);
	GtkListStore* tabela_store = GTK_LIST_STORE(tabela_modelo);
	GtkTreeIter iter;
	GString* sColuna[9];
	GdkPixbuf* icone;

	sColuna[0] = g_string_new(dir->arquivo->nome->str);

	if (dir->tipo->codigo == 'D') {
		icone = ExtensaoBO_DiretorioXPM; //Rotinas_LerArquivoPixbuf("diretorio.xpm");

		sColuna[1] = g_string_new("");
	}
	else {
		icone = ExtensaoBO_pixbufExtensao(listaExtensao, dir->arquivo->nome);
		if (icone == NULL) {
			icone = ExtensaoBO_ArquivoXPM;
		}


		sColuna[1] = g_string_new(dir->tamanhoFormatado->str);
	}


	sColuna[2] = g_string_new(dir->tipo->nome->str);
	sColuna[3] = g_string_new(dir->modificadoFormatado->str);
	sColuna[4] = g_string_new(dir->arquivo->atributos->str);
	sColuna[5] = g_string_new(dir->caminho->str);

	if (bTabelaDir) {
		sColuna[6] = g_string_new("");
		//sColuna[7] = g_string_new("");
		//sColuna[8] = g_string_new("");

		gtk_list_store_append(tabela_store, &iter);
		gtk_list_store_set(tabela_store, &iter, 0, icone, 1, sColuna[0]->str, 2, sColuna[1]->str, 3,
			sColuna[2]->str, 4, sColuna[3]->str, 5, sColuna[4]->str, 6, sColuna[5]->str, -1);
	}
	else {
		sColuna[6] = g_string_new(dir->aba->nome->str);
		//sColuna[7] = g_string_new(Rotinas_IntToStr(dir->aba->codigo)->str);
		//sColuna[8] = g_string_new(dir->nomePai->str);
		gtk_list_store_append(tabela_store, &iter);
		gtk_list_store_set(tabela_store, &iter, 0, icone, 1, sColuna[0]->str, 2, sColuna[1]->str, 3,
			sColuna[2]->str, 4, sColuna[3]->str, 5, sColuna[4]->str, 6, sColuna[5]->str, 7, sColuna[6]->str, -1);
	}


}

void Tabela_carregar(GtkTreeView* tabela, gboolean bTabelaDir, ListaDiretorio listaDir,
	ListaExtensao listaExtensao, GtkProgressBar* barraProgresso) {

	Diretorio dir = Diretorio_new();
	guint nTamListaDir = ListaDiretorio_conta(listaDir);

	Tabela_limpar(tabela);

	gtk_progress_bar_set_fraction(barraProgresso, 0);
	gtk_progress_bar_set_pulse_step(barraProgresso, 0.1);

	for (unsigned int i = 0; i < nTamListaDir; i++) {
		dir = ListaDiretorio_pesquisaItemOrd(listaDir, i);

		Tabela_adicionaItem(tabela, bTabelaDir, dir, listaExtensao);

		gtk_progress_bar_set_fraction(barraProgresso,
			Rotinas_calculaProgresso(nTamListaDir, i));
	}
	gtk_progress_bar_set_fraction(barraProgresso, 0);

}

Diretorio Tabela_getLinhaSelecionada(GtkTreeView* tabela, gboolean bTabelaDir) {
	GValue value = { 0, };
	Diretorio dir = NULL;
	GtkTreeModel* tabela_modelo = gtk_tree_view_get_model(tabela);
	GtkTreeIter iter;
	GtkTreeSelection *tabela_selecao = gtk_tree_view_get_selection(GTK_TREE_VIEW(tabela));

	if (gtk_tree_selection_get_selected(tabela_selecao, &tabela_modelo, &iter))
	{

		if (gtk_tree_selection_iter_is_selected(tabela_selecao, &iter)) {
			dir = Diretorio_new();

			gtk_tree_model_get_value(tabela_modelo, &iter, 1, &value);
			dir->arquivo->nome = g_string_new(g_value_get_string(&value));
			g_value_unset(&value);

			gtk_tree_model_get_value(tabela_modelo, &iter, 2, &value);
			dir->tamanhoFormatado = g_string_new(g_value_get_string(&value));
			g_value_unset(&value);

			gtk_tree_model_get_value(tabela_modelo, &iter, 3, &value);
			dir->tipo->nome = g_string_new(g_value_get_string(&value));
			g_value_unset(&value);

			if (g_string_equal(dir->tipo->nome, Rotinas_getRecurso("TipoLista.diretorio"))) {
				dir->tipo->codigo = 'D';
			}
			else {
				dir->tipo->codigo = 'A';
			}

			gtk_tree_model_get_value(tabela_modelo, &iter, 4, &value);
			dir->modificadoFormatado = g_string_new(g_value_get_string(&value));
			g_value_unset(&value);

			gtk_tree_model_get_value(tabela_modelo, &iter, 5, &value);
			dir->arquivo->atributos = g_string_new(g_value_get_string(&value));
			g_value_unset(&value);

			gtk_tree_model_get_value(tabela_modelo, &iter, 6, &value);
			dir->caminho = g_string_new(g_value_get_string(&value));
			g_value_unset(&value);

			if (!bTabelaDir) {
				gtk_tree_model_get_value(tabela_modelo, &iter, 7, &value);
				dir->aba->nome = g_string_new(g_value_get_string(&value));
				g_value_unset(&value);
			}
		}
	}

	return dir;
}

GtkTreePath* Tabela_encontrarCaminhoPorNome(GtkTreeView* tabela, GString* nome) {
	GValue value = { 0, };
	GString* slinha;
	GtkTreeModel* tabela_modelo = gtk_tree_view_get_model(tabela);
	GtkTreeIter iter;
	GtkTreePath* path = NULL;

	gint total = gtk_tree_model_iter_n_children(tabela_modelo, NULL);

	for (int i = 0; i < total; i++) {
		gtk_tree_model_iter_nth_child(tabela_modelo, &iter, NULL, i);

		gtk_tree_model_get_value(tabela_modelo, &iter, 1, &value);
		slinha = g_string_new(g_value_get_string(&value));
		g_value_unset(&value);

		if (g_string_equal(slinha, nome)) {
			path = gtk_tree_model_get_path(tabela_modelo, &iter);
			break;
		}
	}

	if (path == NULL) {
		path = gtk_tree_path_new_from_indices(total - 1, -1);
	}

	return path;
}

