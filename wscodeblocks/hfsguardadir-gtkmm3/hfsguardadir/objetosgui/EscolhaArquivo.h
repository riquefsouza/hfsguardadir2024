#ifndef ESCOLHAARQUIVO_H
#define ESCOLHAARQUIVO_H

#include <gtkmm/filechooserdialog.h>

#include "../comum/Rotinas.h"

using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosgui {

class EscolhaArquivo
{
private:
	static void montaFiltro(Gtk::FileChooserDialog &fcdialog, const Glib::ustring &filtro);
	static Glib::ustring getTextoExtensao(const Glib::ustring &extensao);
	static Glib::ustring escolher(Gtk::Window* pai, const Glib::ustring &filtro, const Glib::ustring &titulo,
		Gtk::FileChooserAction acao, const gchar* textoAcao,
		const Glib::ustring &diretorio, const Glib::ustring &arquivo);
public:
	static const Glib::ustring FILTRO_TODOS_DIRETORIOS;
	static const Glib::ustring FILTRO_TODOS_ARQUIVOS;
	static const Glib::ustring FILTRO_XML;
	static const Glib::ustring FILTRO_EXPORTAR;
	static const Glib::ustring FILTRO_IMAGEM;

	EscolhaArquivo();
	virtual ~EscolhaArquivo();

	static Glib::ustring abrirArquivo2(Gtk::Window* pai, const Glib::ustring filtro,
		const Glib::ustring &diretorio, const Glib::ustring &arquivo);
	static Glib::ustring abrirArquivo(Gtk::Window* pai, const Glib::ustring filtro);
	static Glib::ustring salvarArquivo2(Gtk::Window* pai, const Glib::ustring filtro,
		const Glib::ustring &diretorio, const Glib::ustring &arquivo);
	static Glib::ustring salvarArquivo(Gtk::Window* pai, const Glib::ustring filtro);
	static Glib::ustring abrirDiretorio2(Gtk::Window* pai, const Glib::ustring &diretorio);
	static Glib::ustring abrirDiretorio(Gtk::Window* pai);
};

}
}

#endif
