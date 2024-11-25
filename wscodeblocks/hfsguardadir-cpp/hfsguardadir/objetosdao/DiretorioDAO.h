#ifndef DIRETORIODAO_H
#define DIRETORIODAO_H

#include "../objetos/Diretorio.h"
#include "../comum/Rotinas.h"
//#include "../comum/SQLite3Lib.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosdao {

class DiretorioDAO
{
private:
	DiretorioDAO();
	DiretorioDAO(DiretorioDAO const&);
	DiretorioDAO& operator=(DiretorioDAO const&);
	static DiretorioDAO* instancia;

	void fecharSqlPreparado(sqlite3_stmt* pstmt);
	Diretorio novoObjeto(sqlite3_stmt* pstmt);
	void atribuirCampos(sqlite3_stmt* pstmt, Diretorio obj);

public:
	static DiretorioDAO* getInstancia();

	int consultarTotal(const std::string &sSQL, const std::string &sCondicaoTotal);
	std::vector<Diretorio> consultarTudo(
		const std::string &sSQL, const std::string &sCondicaoTotal, IProgressoLog progressoLog);
	bool incluir(Diretorio obj);
	bool excluir(Aba aba, const std::string &sCaminho);
	bool criarTabela();
};

}

}

#endif // DIRETORIODAO_H
