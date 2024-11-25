#ifndef EXTENSAODAO_H
#define EXTENSAODAO_H

#ifndef PTRDIFF_MAX
#define PTRDIFF_MAX (std::numeric_limits<ptrdiff_t>::max())
#endif

#include "hfsguardadir/objetos/Extensao.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/comum/SQLite3Lib.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosdao {

class ExtensaoDAO
{
private:
	ExtensaoDAO();
	ExtensaoDAO(ExtensaoDAO const&);
	ExtensaoDAO& operator=(ExtensaoDAO const&);
	static ExtensaoDAO* instancia;

	void fecharSqlPreparado(sqlite3_stmt* pstmt);
	Extensao novoObjeto(sqlite3_stmt* pstmt);
	int consultarTotal();
	void atribuirCampos(sqlite3_stmt* pstmt, Extensao obj);

public:
	static ExtensaoDAO* getInstancia();

	std::vector<Extensao> consultarTudo(IProgressoLog progressoLog);
	bool incluir(Extensao obj);
	bool excluir(int codigo);
	bool excluirTudo();
	bool criarTabela();

};

}
}

#endif // EXTENSAODAO_H

