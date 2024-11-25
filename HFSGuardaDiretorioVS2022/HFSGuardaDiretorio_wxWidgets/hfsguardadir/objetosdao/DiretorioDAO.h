#ifndef DIRETORIODAO_H
#define DIRETORIODAO_H

#include <wx/string.h>
#include <wx/vector.h>
#include <wx/wxsqlite3.h>
#include "hfsguardadir/objetos/Diretorio.h"
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosdao {

class DiretorioDAO
{
private:
	wxSQLite3Database *conexao;
	wxSQLite3Statement pstmt;

    DiretorioDAO();
    DiretorioDAO(DiretorioDAO const&);
    DiretorioDAO& operator=(DiretorioDAO const&);
    static DiretorioDAO* instancia;

    void fecharSqlPreparado();
    Diretorio novoObjeto(wxSQLite3ResultSet res);
    void atribuirCampos(Diretorio obj);

public:
    static DiretorioDAO* getInstancia();
    int consultarTotal(const wxString &sSQL, const wxString &sCondicaoTotal);
    wxVector<Diretorio> consultarTudo(const wxString &sSQL,
                                   const wxString &sCondicaoTotal,
                                   IProgressoLog progressoLog);
    bool incluir(Diretorio obj);
    bool excluir(Aba aba, const wxString &sCaminho);
    bool criarTabela();
};

}

}

#endif // DIRETORIODAO_H
