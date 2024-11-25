#ifndef EXTENSAOBO_H
#define EXTENSAOBO_H

#include "../objetos/Extensao.h"
#include "../objetos/Diretorio.h"
#include "../comum/Rotinas.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosbo {

class ExtensaoBO
{
private:
	Glib::RefPtr<Gdk::Pixbuf> diretorioBMP;
	Glib::RefPtr<Gdk::Pixbuf> arquivoBMP;

	Glib::RefPtr<Gdk::Pixbuf> Diretorio32XPM;
	Glib::RefPtr<Gdk::Pixbuf> Arquivo32XPM;
	Glib::RefPtr<Gdk::Pixbuf> DirAberto32XPM;


	ExtensaoBO();
	ExtensaoBO(ExtensaoBO const&);
	ExtensaoBO& operator=(ExtensaoBO const&);
	static ExtensaoBO* instancia;

public:
	Glib::RefPtr<Gdk::Pixbuf> DiretorioXPM;
	Glib::RefPtr<Gdk::Pixbuf> DirAbertoXPM;
	Glib::RefPtr<Gdk::Pixbuf> ArquivoXPM;
	Glib::RefPtr<Gdk::Pixbuf> CDOuroXPM;

	static ExtensaoBO* getInstancia();

	std::vector<Extensao> carregarExtensao(IProgressoLog progressoLog);
	int retMaxCodExtensao(const std::vector<Extensao>  &listaLocal);
	bool existeExtensao(const Glib::ustring &sExtensao, const std::vector<Extensao>  &listaLocal);
	bool incluirExtensao(Extensao extensao);
	bool SalvarExtensao(std::vector<Extensao>  &listaExtensao, const Glib::ustring &sNomeDiretorio,
						const Glib::ustring &sCaminhoOriginal, std::vector<Glib::ustring> &log);
	void salvarExtensoes(const std::vector<Diretorio>  &listaDiretorio,
			std::vector<Extensao>  &listaExtensao, IProgressoLog progressoLog);
	bool excluirExtensao(std::vector<Extensao>  &listaExtensao, int codigo);
	bool excluirTodasExtensoes(std::vector<Extensao>  &listaExtensao);
	bool criarTabelaExtensoes();
	int indiceExtensao(const std::vector<Extensao>  &lista, const Glib::ustring &nomeExtensao);
	Glib::RefPtr<Gdk::Pixbuf> pixbufExtensao(const std::vector<Extensao> &lista,
		const Glib::ustring &nomeExtensao);
	Extensao* pegaExtensaoPorOrdem(const std::vector<Extensao>  &lista, int ordem);
	Extensao* pegaExtensaoPorCodigo(const std::vector<Extensao>  &lista, int codigo);
	Extensao* pegaExtensaoPorNome(const std::vector<Extensao>  &lista,
			const Glib::ustring &nome, const Glib::ustring &tipo);
	bool ExportarExtensao(TipoExportarExtensao tipo,
						  const std::vector<Extensao>  &listaExtensao);
	void ImportarExtensao(const Glib::ustring &caminho, std::vector<Extensao>  &listaExtensao);
	void ExtrairExtensao(const Glib::ustring &caminho, std::vector<Extensao>  &listaExtensao);

};

}
}

#endif // EXTENSAOBO_H
