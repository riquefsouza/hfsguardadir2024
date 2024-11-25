#ifndef DIRETORIOBO_H
#define DIRETORIOBO_H

#include "hfsguardadir/objetos/Diretorio.h"
#include "hfsguardadir/objetos/DiretorioOrdem.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/comum/DiretorioXML.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosbo {

class DiretorioBO
{
private:
	DiretorioBO();
	DiretorioBO(DiretorioBO const&);
	DiretorioBO& operator=(DiretorioBO const&);
	static DiretorioBO* instancia;

	std::string diretorioToCSV(Diretorio diretorio);
	std::string diretorioToXML(Diretorio diretorio);
	std::string diretorioToTXT(Diretorio diretorio);
	std::string diretorioToHTML(Diretorio diretorio);

public:
	static const std::string SQL_CONSULTA_ARQUIVO;
	static DiretorioBO* getInstancia();

	std::vector<Diretorio> carregarDiretorio(const std::string &sSQL,
								   IProgressoLog progressoLog);
	std::vector<Diretorio> carregarDiretorio(const std::string &sSQL,
									   const std::string &sCondicaoTotal,
									   IProgressoLog progressoLog);
	std::string removerDrive(const std::string &sDiretorio);
	int retCodDirPai(int nAba, const std::string &sDiretorio,
								  const std::vector<Diretorio>  &listaLocal);
	Diretorio atribuiDiretorio(int nAba, int nCodDirRaiz,
			const std::string &sNomeDirRaiz, const std::string &sDiretorio, bool bDiretorio,
			const std::vector<Diretorio>  &listaLocal, Arquivo arquivo,
			DiretorioOrdem *dirOrdem);
	void atribuiListaDiretorio(int nAba, int nCodDirRaiz,
			const std::string &sNomeDirRaiz, const std::string &sDiretorio, 
		std::vector<Diretorio> *listaLocal,
			Arquivo info, DiretorioOrdem *dirOrdem, IProgressoLog progressoLog);
	void ImportarDiretorio(int nAba, int nCodDirRaiz,
			const std::string &sNomeDirRaiz, const std::string &sDiretorio, 
		std::vector<Diretorio> *listaLocal,	DiretorioOrdem *dirOrdem, IProgressoLog progressoLog);
	bool verificaCodDir(int nAba, const std::string &sDiretorio,
			const std::vector<Diretorio>  &listaLocal);
	int retMaxCodDir(int nAba, const std::vector<Diretorio>  &listaLocal);
	std::string diretorioToSQL(Diretorio diretorio, bool bInsert);
	void salvarDiretorio(const std::vector<Diretorio>  &listaDiretorio,
			IProgressoLog progressoLog);
	bool excluirDiretorio(Aba aba, const std::string &sCaminho);
	void excluirListaDiretorio(std::vector<Diretorio> listaDiretorio,
			Aba aba, const std::string &sCaminho);
	void exportarDiretorio(TipoExportar tipo, Aba aba,
			const std::string &sNomeArquivo, IProgressoLog progressoLog);
	bool criarTabelaDiretorios();
	int XMLParaDiretorio(const std::string &sTexto, int nArquivo,
			DiretorioXML *diretorioXML);
	int importarDiretorioViaXML(Aba aba, const std::string &sNomeArquivo,
			const std::vector<Diretorio>  &listaDirPai,
			IProgressoLog progressoLog);
	bool carregarSubDiretorios(const std::string &sDiretorio,
			std::vector<std::string> &listaLocal);
	bool carregarArquivos(const std::string &sDiretorio,
			std::vector<std::string> &listaLocal);
	bool carregarTodosArquivos(const std::string &sDiretorio,
			std::vector<std::string> &listaLocal);
	std::vector<Diretorio> itensFilhos(const std::vector<Diretorio> &lista_pai,
			int aba, int codDirPai, int codigo);

};

}
}

#endif // DIRETORIOBO_H
