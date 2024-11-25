#include "Arvore.h"
#include "../comum/Rotinas.h"

void Arvore_cria(GtkTreeView* tvArvore)
{
	GtkTreeViewColumn *arvore_coluna = gtk_tree_view_column_new();
	gtk_tree_view_column_set_title(arvore_coluna, "coluna");

	GtkCellRenderer* pixbufRender = gtk_cell_renderer_pixbuf_new();
	gtk_tree_view_column_pack_start(arvore_coluna, pixbufRender, FALSE);
	gtk_tree_view_column_add_attribute(arvore_coluna, pixbufRender, "pixbuf", 0);

	GtkCellRenderer* textRender = gtk_cell_renderer_text_new();
	gtk_tree_view_column_pack_start(arvore_coluna, textRender, TRUE);
	gtk_tree_view_column_add_attribute(arvore_coluna, textRender, "text", 1);

	gtk_tree_view_append_column(tvArvore, arvore_coluna);
	gtk_tree_view_set_headers_visible(tvArvore, FALSE);

	GtkTreeSelection *arvore_selecao = gtk_tree_view_get_selection(tvArvore);
	gtk_tree_selection_set_mode(arvore_selecao, GTK_SELECTION_SINGLE);

	GtkTreeStore *arvore_store = GTK_TREE_STORE(gtk_tree_store_new(2, GDK_TYPE_PIXBUF, G_TYPE_STRING));

	GtkTreeModel *arvore_modelo = GTK_TREE_MODEL(arvore_store);
	gtk_tree_view_set_model(tvArvore, arvore_modelo);
}

void Arvore_limpar(GtkTreeView* arvore) {
	GtkTreeModel* arvore_modelo = gtk_tree_view_get_model(arvore);
	GtkTreeStore* arvore_store = GTK_TREE_STORE(arvore_modelo);

	gtk_tree_store_clear(arvore_store);
}

void Arvore_expandirTodos(GtkTreeView* arvore) {
	gtk_tree_view_expand_all(arvore);
}

void Arvore_colapsarTodos(GtkTreeView* arvore) {
	gtk_tree_view_collapse_all(arvore);
}

void Arvore_selecionarPrimeiroItem(GtkTreeView* arvore) {
	GtkTreeIter iter;
	GtkTreeModel* arvore_modelo = gtk_tree_view_get_model(arvore);
	GtkTreeSelection *arvore_selecao = gtk_tree_view_get_selection(arvore);

	if (gtk_tree_model_get_iter_first(arvore_modelo, &iter)) {
		gtk_tree_selection_select_iter(arvore_selecao, &iter);
	}

}

GtkTreeIter* Arvore_encontrarCaminho(GtkTreeModel* arvore_modelo, GtkTreeIter *pai, ListaString nomes, int nivel) {
	GtkTreeIter filho;
	gboolean bValido;
	GString *valorPai, *nome;
	GValue value = { 0, };
	guint ntamlista = ListaString_conta(nomes);
	GtkTreeStore* arvore_store = GTK_TREE_STORE(arvore_modelo);

	bValido = gtk_tree_store_iter_is_valid(arvore_store, pai);
	if (bValido) {
		while (bValido) {

			gtk_tree_model_get_value(arvore_modelo, pai, 1, &value);
			valorPai = g_string_new(g_value_get_string(&value));
			g_value_unset(&value);

			nome = ListaString_pesquisaItemOrd(nomes, nivel);

			if (g_string_equal(valorPai, nome)) {

				if (nivel == (ntamlista - 2)) {
					return pai;
				}

				if (gtk_tree_model_iter_has_child(arvore_modelo, pai)) {
					gtk_tree_model_iter_children(arvore_modelo, &filho, pai);

					return Arvore_encontrarCaminho(arvore_modelo, &filho, nomes, nivel + 1);
				}

			}

			bValido = gtk_tree_model_iter_next(arvore_modelo, pai);
		}
	}

	return pai;
}

GtkTreePath* Arvore_encontrarCaminhoPorNome(GtkTreeView* arvore, ListaString nomes) {
	GtkTreeIter iter;
	GtkTreeModel* arvore_modelo = gtk_tree_view_get_model(arvore);
	GtkTreePath* path = NULL;
	gint total = gtk_tree_model_iter_n_children(arvore_modelo, NULL);

	if (gtk_tree_model_get_iter_first(arvore_modelo, &iter)) {
		iter = *(Arvore_encontrarCaminho(arvore_modelo, &iter, nomes, 0));
		path = gtk_tree_model_get_path(arvore_modelo, &iter);
	}

	if (path == NULL) {
		path = gtk_tree_path_new_from_indices(total - 1, -1);
	}

	return path;
}

void Arvore_expandirSelecionado(GtkTreeView* arvore) {
	GtkTreeModel* arvore_modelo;
	GtkTreeSelection *arvore_selecao;
	GtkTreeIter iter;
	GtkTreePath* path;

	arvore_modelo = gtk_tree_view_get_model(arvore);
	arvore_selecao = gtk_tree_view_get_selection(arvore);

	if (gtk_tree_selection_get_selected(arvore_selecao, &arvore_modelo, &iter)) {
		if (gtk_tree_selection_iter_is_selected(arvore_selecao, &iter)) {
			path = gtk_tree_model_get_path(arvore_modelo, &iter);

			if (gtk_tree_view_row_expanded(arvore, path)) {
				gtk_tree_view_collapse_row(arvore, path);
			}
			else {
				gtk_tree_view_expand_to_path(arvore, path);
			}

		}
	}
}
