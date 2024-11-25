#ifndef ABADAO_H
#define ABADAO_H

#include <wx/string.h>
#include <wx/vector.h>
#include <wx/wxsqlite3.h>
#include "hfsguardadir/objetos/Aba.h"
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosdao {

class AbaDAO
{
private:
	wxSQLite3Database *conexao;
    wxSQLite3Statement pstmt;

    AbaDAO();
    AbaDAO(AbaDAO const&);
    AbaDAO& operator=(AbaDAO const&);
    static AbaDAO* instancia;

    void fecharSqlPreparado();
    Aba novoObjeto(wxSQLite3ResultSet res);

public:
    static AbaDAO* getInstancia();
    int consultarTotal();
    wxVector<Aba> consultarTudo(IProgressoLog progressoLog);
    bool incluir(Aba obj);
    bool alterar(Aba obj);
    bool excluir(int codigo);
    bool criarTabela();
};

}

}

#endif // ABADAO_H
