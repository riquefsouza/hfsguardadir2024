#include "hfsguardadir/objetosgui/Arvore.h"

namespace hfsguardadir {

namespace objetosgui {

Arvore::Arvore()
{
	coluna.set_title("coluna");

	Gtk::CellRendererPixbuf pixbufRender;
	coluna.pack_start(pixbufRender, false);
	coluna.add_attribute(pixbufRender, "pixbuf", modeloArvore.coluna0);

	Gtk::CellRendererText textRender;
	coluna.pack_start(textRender, true);
	coluna.add_attribute(textRender, "text", modeloArvore.coluna1);

	append_column(coluna);
	set_headers_visible(false);

	get_selection()->set_mode(Gtk::SELECTION_SINGLE);
	set_model(Gtk::TreeStore::create(modeloArvore));
}

Arvore::~Arvore()
{
}

Glib::RefPtr<Gtk::TreeStore> Arvore::getStore() {
	Glib::RefPtr<Gtk::TreeStore> store;
	store = Glib::RefPtr<Gtk::TreeStore>::cast_static(this->get_model());
	return store;
}

void Arvore::limpar() {
	getStore()->clear();
}

void Arvore::expandirTodos() {
	this->expand_all();
}

void Arvore::colapsarTodos() {
	this->collapse_all();
}

void Arvore::selecionarPrimeiroItem() {
	Gtk::TreeIter iter;

	iter = get_model()->children().begin();
	if (iter) {
		get_selection()->select(iter);
	}

}

Gtk::TreeIter Arvore::encontrarCaminho(Gtk::TreeIter pai,
	const std::vector<Glib::ustring> &nomes, int nivel) {
	Gtk::TreeRow linha;
	Gtk::TreeIter filho;
	Glib::ustring valor, nome;
	guint ntamlista = nomes.size();

	for (filho = pai->children().begin(); filho != pai->children().end(); ++filho){
		valor = filho->get_value(modeloArvore.coluna1);

		nome = nomes.at(nivel);

		if (valor == nome) {

			if (nivel == (ntamlista - 1)) {
				return filho;
			}

			if (filho->children().size() > 0) {
				return encontrarCaminho(filho, nomes, nivel + 1);
			}
			else {
				return filho;
			}
		}
	}

	return pai;

}

Gtk::TreePath Arvore::encontrarCaminhoPorNome(const std::vector<Glib::ustring> &nomes) {
	Gtk::TreeIter iter;
	Gtk::TreePath path;
	int nivel = 0;
	Glib::ustring valor, nome;
	guint ntamlista = nomes.size();

	for (iter = getStore()->children().begin(); iter != getStore()->children().end(); ++iter) {
		valor = iter->get_value(modeloArvore.coluna1);

		nome = nomes.at(nivel);

		if (valor == nome) {

			if (nivel == (ntamlista - 1)) {
				break;
			}

			if (iter->children().size() > 0) {
				iter = encontrarCaminho(iter, nomes, nivel + 1);
				break;
			}

		}
	}

	if (getStore()->iter_is_valid(iter)) {
		path = getStore()->get_path(iter);
	}

	return path;
}

void Arvore::expandirSelecionado() {
	Glib::RefPtr<Gtk::TreeModel> arvore_modelo = get_model();
	Glib::RefPtr<Gtk::TreeSelection> arvore_selecao = get_selection();
	Gtk::TreeIter iter;
	Gtk::TreePath path;

	iter = arvore_selecao->get_selected();
	if (iter) {
		if (arvore_selecao->is_selected(iter)) {
			path = arvore_modelo->get_path(iter);

			if (row_expanded(path)) {
				collapse_row(path);
			}
			else {
				expand_to_path(path);
			}
		}
	}
}

}
}
