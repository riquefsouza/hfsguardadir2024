#ifndef ABADAO_H
#define ABADAO_H

#ifndef PTRDIFF_MAX
#define PTRDIFF_MAX (std::numeric_limits<ptrdiff_t>::max())
#endif

#include "hfsguardadir/objetos/Aba.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/comum/SQLite3Lib.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosdao {
	
class AbaDAO
{
private:
	AbaDAO();
	AbaDAO(AbaDAO const&);
	AbaDAO& operator=(AbaDAO const&);
	static AbaDAO* instancia;

	void fecharSqlPreparado(sqlite3_stmt* pstmt);
	Aba novoObjeto(sqlite3_stmt* pstmt);
	void atribuirCampos(sqlite3_stmt* pstmt, Aba obj);
	int consultarTotal();

public:
	static AbaDAO* getInstancia();

	std::vector<Aba> consultarTudo(IProgressoLog progressoLog);
	bool incluir(Aba obj);
	bool alterar(Aba obj);
	bool excluir(int codigo);
	bool criarTabela();

};

}
}

#endif

