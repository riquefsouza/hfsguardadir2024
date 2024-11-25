#ifndef DIRETORIODAO_H
#define DIRETORIODAO_H

#include "hfsguardadir/objetos/Diretorio.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "sqlite3.h"

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

	int consultarTotal(const Glib::ustring &sSQL, const Glib::ustring &sCondicaoTotal);
	std::vector<Diretorio> consultarTudo(
		const Glib::ustring &sSQL, const Glib::ustring &sCondicaoTotal, IProgressoLog progressoLog);
	bool incluir(Diretorio obj);
	bool excluir(Aba aba, const Glib::ustring &sCaminho);
	bool criarTabela();
};

}

}

#endif // DIRETORIODAO_H
