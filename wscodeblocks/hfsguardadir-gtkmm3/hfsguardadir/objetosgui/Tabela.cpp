#include "hfsguardadir/objetosgui/Tabela.h"
#include "hfsguardadir/objetosbo/ExtensaoBO.h"

using namespace hfsguardadir::objetosbo;
using namespace hfsguardadir::objetosgui;

namespace hfsguardadir {

namespace objetosgui {

Tabela::Tabela(bool bTabelaDir)
{
	this->bTabelaDir = bTabelaDir;

	if (!bTabelaDir) {
		colunaAba = manage(new class Gtk::TreeViewColumn("Aba", modeloTabela.coluna7));
		colunaAba->set_resizable(true);
		colunaAba->set_sizing(Gtk::TREE_VIEW_COLUMN_AUTOSIZE);
		colunaAba->set_title("Aba");
		colunaAba->set_sort_indicator(true);
		colunaAba->set_sort_column(7);
	}

	colunaCaminho = manage(new class Gtk::TreeViewColumn("Caminho", modeloTabela.coluna6));
	colunaCaminho->set_resizable(true);
	colunaCaminho->set_sizing(Gtk::TREE_VIEW_COLUMN_AUTOSIZE);
	colunaCaminho->set_title("Caminho");
	colunaCaminho->set_sort_indicator(true);
	colunaCaminho->set_sort_column(6);

	colunaAtributos = manage(new class Gtk::TreeViewColumn("Atributos", modeloTabela.coluna5));
	colunaAtributos->set_resizable(true);
	colunaAtributos->set_sizing(Gtk::TREE_VIEW_COLUMN_AUTOSIZE);
	colunaAtributos->set_title("Atributos");
	colunaAtributos->set_sort_indicator(true);
	colunaAtributos->set_sort_column(5);

	colunaModificado = manage(new class Gtk::TreeViewColumn("Modificado", modeloTabela.coluna4));
	colunaModificado->set_resizable(true);
	colunaModificado->set_sizing(Gtk::TREE_VIEW_COLUMN_AUTOSIZE);
	colunaModificado->set_title("Modificado");
	colunaModificado->set_sort_indicator(true);
	colunaModificado->set_sort_column(4);

	colunaTipo = manage(new class Gtk::TreeViewColumn("Tipo", modeloTabela.coluna3));
	colunaTipo->set_resizable(true);
	colunaTipo->set_sizing(Gtk::TREE_VIEW_COLUMN_AUTOSIZE);
	colunaTipo->set_title("Tipo");
	colunaTipo->set_sort_indicator(true);
	colunaTipo->set_sort_column(3);

	colunaTamanho = manage(new class Gtk::TreeViewColumn("Tamanho", modeloTabela.coluna2));
	colunaTamanho->set_resizable(true);
	colunaTamanho->set_sizing(Gtk::TREE_VIEW_COLUMN_AUTOSIZE);
	colunaTamanho->set_title("Tamanho");
	colunaTamanho->set_sort_indicator(true);
	colunaTamanho->set_sort_column(2);

	colunaNome = manage(new class Gtk::TreeViewColumn());
	colunaNome->set_title("Nome");

	Gtk::CellRendererPixbuf pixbufRender;
	colunaNome->pack_start(pixbufRender, false);
	colunaNome->add_attribute(pixbufRender, "pixbuf", modeloTabela.coluna0);

	Gtk::CellRendererText textRender;
	colunaNome->pack_start(textRender, true);
	colunaNome->add_attribute(textRender, "text", modeloTabela.coluna1);

	colunaNome->set_resizable(true);
	colunaNome->set_sizing(Gtk::TREE_VIEW_COLUMN_AUTOSIZE);
	colunaNome->set_sort_indicator(true);
	colunaNome->set_sort_column(1);

	append_column(*colunaNome);
	append_column(*colunaTamanho);
	append_column(*colunaTipo);
	append_column(*colunaModificado);
	append_column(*colunaAtributos);
	append_column(*colunaCaminho);
	if (!bTabelaDir) {
		append_column(*colunaAba);
	}

	get_selection()->set_mode(Gtk::SELECTION_SINGLE);
	set_model(Gtk::ListStore::create(modeloTabela));
	columns_autosize();
}

Tabela::~Tabela()
{
}

Glib::RefPtr<Gtk::ListStore> Tabela::getStore() {
	Glib::RefPtr<Gtk::ListStore> store;
	store = Glib::RefPtr<Gtk::ListStore>::cast_static(this->get_model());
	return store;
}

void Tabela::limpar() {
	getStore()->clear();
}

void Tabela::adicionaItem(Diretorio dir, const std::vector<Extensao> &listaExtensao) {
	Gtk::TreeRow tLinha;
	Glib::RefPtr<Gdk::Pixbuf> icone;

	tLinha = *(getStore()->append());
	tLinha[modeloTabela.coluna1] = dir.getNome();

	if (dir.getTipo().getCodigo() == 'D') {
		icone = ExtensaoBO::getInstancia()->DiretorioXPM;
		tLinha[modeloTabela.coluna0] = icone;
		tLinha[modeloTabela.coluna2] = "";
	}
	else {
		icone = ExtensaoBO::getInstancia()->pixbufExtensao(listaExtensao, dir.getNome());
		if (icone) {
			icone = ExtensaoBO::getInstancia()->ArquivoXPM;
		}
		tLinha[modeloTabela.coluna0] = icone;
		tLinha[modeloTabela.coluna2] = dir.getTamanhoFormatado();
	}

	tLinha[modeloTabela.coluna3] = dir.getTipo().getNome();
	tLinha[modeloTabela.coluna4] = dir.getModificadoFormatado();
	tLinha[modeloTabela.coluna5] = dir.getAtributos();
	tLinha[modeloTabela.coluna6] = dir.getCaminho();

	if (bTabelaDir) {
		tLinha[modeloTabela.coluna7] = "";
	}
	else {
		tLinha[modeloTabela.coluna7] = dir.getAba().getNome();
	}

}

void Tabela::carregar(const std::vector<Diretorio> &listaDir,
	const std::vector<Extensao> &listaExtensao, Gtk::ProgressBar* barraProgresso) {

	Diretorio dir;
	guint nTamListaDir = listaDir.size();
	getStore()->clear();

	barraProgresso->set_fraction(0);
	barraProgresso->set_pulse_step(0.1);

	for (unsigned int i = 0; i < nTamListaDir; i++) {
		dir = listaDir.at(i);

		adicionaItem(dir, listaExtensao);

		barraProgresso->set_fraction(Rotinas::calculaProgresso(nTamListaDir, i));
	}
	barraProgresso->set_fraction(0);

}

Diretorio Tabela::getLinhaSelecionada() {
	Diretorio dir;
	Tipo tipo;
	Aba aba;
	Gtk::TreeIter iter;

	iter = get_selection()->get_selected();
	if (iter)
	{
		if (get_selection()->is_selected(iter)) {
			dir.setNome(iter->children()->get_value(modeloTabela.coluna1));
			dir.setTamanhoFormatado(iter->children()->get_value(modeloTabela.coluna2));
			tipo.setNome(iter->children()->get_value(modeloTabela.coluna3));

			if (tipo.getNome() == Rotinas::getRecurso("TipoLista.diretorio")) {
				tipo.setCodigo('D');
			}
			else {
				tipo.setCodigo('A');
			}
			dir.setTipo(tipo);

			dir.setModificadoFormatado(iter->children()->get_value(modeloTabela.coluna4));
			dir.setAtributos(iter->children()->get_value(modeloTabela.coluna5));
			dir.setCaminho(iter->children()->get_value(modeloTabela.coluna6));

			if (!bTabelaDir) {
				aba.setNome(iter->children()->get_value(modeloTabela.coluna7));
			}
			dir.setAba(aba);
		}
	}

	return dir;
}

Gtk::TreePath Tabela::encontrarCaminhoPorNome(const Glib::ustring &nome) {
	Glib::ustring valor;
	Gtk::TreeIter iter;
	Gtk::TreePath path;

	for (iter = getStore()->children().begin(); iter != getStore()->children().end(); ++iter) {
		valor = iter->get_value(modeloTabela.coluna1);

		if (valor == nome) {
			break;
		}
	}

	if (getStore()->iter_is_valid(iter)) {
		path = getStore()->get_path(iter);
	}

	return path;
}

}
}
