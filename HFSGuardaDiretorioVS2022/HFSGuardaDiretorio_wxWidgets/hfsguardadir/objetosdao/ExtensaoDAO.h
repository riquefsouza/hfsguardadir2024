#ifndef EXTENSAODAO_H
#define EXTENSAODAO_H

#include <wx/string.h>
#include <wx/vector.h>
#include <wx/wxsqlite3.h>
#include "hfsguardadir/objetos/Extensao.h"
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosdao {

class ExtensaoDAO
{
private:
	wxSQLite3Database *conexao;
	wxSQLite3Statement pstmt;

    ExtensaoDAO();
    ExtensaoDAO(ExtensaoDAO const&);
    ExtensaoDAO& operator=(ExtensaoDAO const&);
    static ExtensaoDAO* instancia;

    void fecharSqlPreparado();
    Extensao novoObjeto(wxSQLite3ResultSet res);

public:
    static ExtensaoDAO* getInstancia();
    int consultarTotal();
    wxVector<Extensao> consultarTudo(IProgressoLog progressoLog);
    bool incluir(Extensao obj);
    bool excluir(int codigo);
    bool excluirTudo();
    bool criarTabela();
};

}
}

#endif // EXTENSAODAO_H
