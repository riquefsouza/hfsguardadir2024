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

	Glib::ustring diretorioToCSV(Diretorio diretorio);
	Glib::ustring diretorioToXML(Diretorio diretorio);
	Glib::ustring diretorioToTXT(Diretorio diretorio);
	Glib::ustring diretorioToHTML(Diretorio diretorio);

public:
	static const Glib::ustring SQL_CONSULTA_ARQUIVO;
	static DiretorioBO* getInstancia();

	std::vector<Diretorio> carregarDiretorio(const Glib::ustring &sSQL,
								   IProgressoLog progressoLog);
	std::vector<Diretorio> carregarDiretorio(const Glib::ustring &sSQL,
									   const Glib::ustring &sCondicaoTotal,
									   IProgressoLog progressoLog);
	Glib::ustring removerDrive(const Glib::ustring &sDiretorio);
	int retCodDirPai(int nAba, const Glib::ustring &sDiretorio,
								  const std::vector<Diretorio>  &listaLocal);
	Diretorio atribuiDiretorio(int nAba, int nCodDirRaiz,
			const Glib::ustring &sNomeDirRaiz, const Glib::ustring &sDiretorio, bool bDiretorio,
			const std::vector<Diretorio>  &listaLocal, Arquivo arquivo,
			DiretorioOrdem *dirOrdem);
	void atribuiListaDiretorio(int nAba, int nCodDirRaiz,
			const Glib::ustring &sNomeDirRaiz, const Glib::ustring &sDiretorio, 
		std::vector<Diretorio> *listaLocal,
			Arquivo info, DiretorioOrdem *dirOrdem, IProgressoLog progressoLog);
	void ImportarDiretorio(int nAba, int nCodDirRaiz,
			const Glib::ustring &sNomeDirRaiz, const Glib::ustring &sDiretorio, 
		std::vector<Diretorio> *listaLocal,	DiretorioOrdem *dirOrdem, IProgressoLog progressoLog);
	bool verificaCodDir(int nAba, const Glib::ustring &sDiretorio,
			const std::vector<Diretorio>  &listaLocal);
	int retMaxCodDir(int nAba, const std::vector<Diretorio>  &listaLocal);
	Glib::ustring diretorioToSQL(Diretorio diretorio, bool bInsert);
	void salvarDiretorio(const std::vector<Diretorio>  &listaDiretorio,
			IProgressoLog progressoLog);
	bool excluirDiretorio(Aba aba, const Glib::ustring &sCaminho);
	void excluirListaDiretorio(std::vector<Diretorio> listaDiretorio,
			Aba aba, const Glib::ustring &sCaminho);
	void exportarDiretorio(TipoExportar tipo, Aba aba,
			const Glib::ustring &sNomeArquivo, IProgressoLog progressoLog);
	bool criarTabelaDiretorios();
	int XMLParaDiretorio(const Glib::ustring &sTexto, int nArquivo,
			DiretorioXML *diretorioXML);
	int importarDiretorioViaXML(Aba aba, const Glib::ustring &sNomeArquivo,
			const std::vector<Diretorio>  &listaDirPai,
			IProgressoLog progressoLog);
	bool carregarSubDiretorios(const Glib::ustring &sDiretorio,
			std::vector<Glib::ustring> &listaLocal);
	bool carregarArquivos(const Glib::ustring &sDiretorio,
			std::vector<Glib::ustring> &listaLocal);
	bool carregarTodosArquivos(const Glib::ustring &sDiretorio,
			std::vector<Glib::ustring> &listaLocal);
	std::vector<Diretorio> itensFilhos(const std::vector<Diretorio> &lista_pai,
			int aba, int codDirPai, int codigo);

};

}
}

#endif // DIRETORIOBO_H
