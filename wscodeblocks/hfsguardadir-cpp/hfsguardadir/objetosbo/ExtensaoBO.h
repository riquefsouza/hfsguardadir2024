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
	ImagemBuffer diretorioBMP;
	ImagemBuffer arquivoBMP;

	ImagemBuffer Diretorio32XPM;
	ImagemBuffer Arquivo32XPM;
	ImagemBuffer DirAberto32XPM;


	ExtensaoBO();
	ExtensaoBO(ExtensaoBO const&);
	ExtensaoBO& operator=(ExtensaoBO const&);
	static ExtensaoBO* instancia;

public:
	ImagemBuffer DiretorioXPM;
	ImagemBuffer DirAbertoXPM;
	ImagemBuffer ArquivoXPM;
	ImagemBuffer CDOuroXPM;

	static ExtensaoBO* getInstancia();

	std::vector<Extensao> carregarExtensao(IProgressoLog progressoLog);
	int retMaxCodExtensao(const std::vector<Extensao>  &listaLocal);
	bool existeExtensao(const std::string &sExtensao, const std::vector<Extensao>  &listaLocal);
	bool incluirExtensao(Extensao extensao);
	bool SalvarExtensao(std::vector<Extensao>  &listaExtensao, const std::string &sNomeDiretorio,
						const std::string &sCaminhoOriginal, std::vector<std::string> &log);
	void salvarExtensoes(const std::vector<Diretorio>  &listaDiretorio,
			std::vector<Extensao>  &listaExtensao, IProgressoLog progressoLog);
	bool excluirExtensao(std::vector<Extensao>  &listaExtensao, int codigo);
	bool excluirTodasExtensoes(std::vector<Extensao>  &listaExtensao);
	bool criarTabelaExtensoes();
	int indiceExtensao(const std::vector<Extensao>  &lista, const std::string &nomeExtensao);
	ImagemBuffer pixbufExtensao(const std::vector<Extensao> &lista,
		const std::string &nomeExtensao);
	Extensao* pegaExtensaoPorOrdem(const std::vector<Extensao>  &lista, int ordem);
	Extensao* pegaExtensaoPorCodigo(const std::vector<Extensao>  &lista, int codigo);
	Extensao* pegaExtensaoPorNome(const std::vector<Extensao>  &lista,
			const std::string &nome, const std::string &tipo);
	bool ExportarExtensao(TipoExportarExtensao tipo,
						  const std::vector<Extensao>  &listaExtensao);
	void ImportarExtensao(const std::string &caminho, std::vector<Extensao>  &listaExtensao);
	void ExtrairExtensao(const std::string &caminho, std::vector<Extensao>  &listaExtensao);

};

}
}

#endif // EXTENSAOBO_H
