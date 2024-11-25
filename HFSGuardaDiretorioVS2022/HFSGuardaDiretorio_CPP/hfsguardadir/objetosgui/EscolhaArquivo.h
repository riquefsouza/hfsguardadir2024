#ifndef ESCOLHAARQUIVO_H
#define ESCOLHAARQUIVO_H

#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosgui {
		
class EscolhaArquivo
{
private:
	/*
	static void montaFiltro(Gtk::FileChooserDialog &fcdialog, const std::string &filtro);
	static std::string getTextoExtensao(const std::string &extensao);
	static std::string escolher(Gtk::Window* pai, const std::string &filtro, const std::string &titulo,
		Gtk::FileChooserAction acao, const gchar* textoAcao,
		const std::string &diretorio, const std::string &arquivo);
	*/
public:
	static const std::string FILTRO_TODOS_DIRETORIOS;
	static const std::string FILTRO_TODOS_ARQUIVOS;
	static const std::string FILTRO_XML;
	static const std::string FILTRO_EXPORTAR;
	static const std::string FILTRO_IMAGEM;

	EscolhaArquivo();
	virtual ~EscolhaArquivo();
	/*
	static std::string abrirArquivo2(Gtk::Window* pai, const std::string filtro,
		const std::string &diretorio, const std::string &arquivo);
	static std::string abrirArquivo(Gtk::Window* pai, const std::string filtro);
	static std::string salvarArquivo2(Gtk::Window* pai, const std::string filtro,
		const std::string &diretorio, const std::string &arquivo);
	static std::string salvarArquivo(Gtk::Window* pai, const std::string filtro);
	static std::string abrirDiretorio2(Gtk::Window* pai, const std::string &diretorio);
	static std::string abrirDiretorio(Gtk::Window* pai);
	*/
};

}
}

#endif
