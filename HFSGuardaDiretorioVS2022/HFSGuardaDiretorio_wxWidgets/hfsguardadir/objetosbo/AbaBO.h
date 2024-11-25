#ifndef ABABO_H
#define ABABO_H

#include <wx/vector.h>
#include "hfsguardadir/objetos/Aba.h"
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosbo {

class AbaBO
{
private:
    AbaBO();
    AbaBO(AbaBO const&);
    AbaBO& operator=(AbaBO const&);
    static AbaBO* instancia;

public:
    static AbaBO* getInstancia();

    wxVector<Aba> carregarAba(IProgressoLog progressoLog);
    int retMaxCodAba(wxVector<Aba> listaLocal);
    wxString abaToSQL(Aba aba);
    bool incluirAba(Aba aba);
    bool alterarAba(Aba aba);
    bool excluirAba(Aba aba);
    bool criarTabelaAbas();
    Aba* pegaAbaPorOrdem(wxVector<Aba> lista, int ordem);
    Aba* getElemento(wxVector<Aba> lista, int codigo);
    Aba* pegaAbaPorNome(wxVector<Aba> lista, const wxString &nome);

};

}
}

#endif // ABABO_H
