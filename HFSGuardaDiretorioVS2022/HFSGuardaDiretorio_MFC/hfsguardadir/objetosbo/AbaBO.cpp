#include "stdafx.h"

#include "AbaBO.h"
#include "hfsguardadir/objetosdao/AbaDAO.h"

using namespace hfsguardadir::objetosdao;

namespace hfsguardadir {

namespace objetosbo {

AbaBO* AbaBO::instancia = NULL;

AbaBO::AbaBO()
{

}

AbaBO::AbaBO(AbaBO const&) {

}

AbaBO& AbaBO::operator=(AbaBO const&) {
	return *instancia;
}

AbaBO* AbaBO::getInstancia() {
	if (!instancia) {
		instancia = new AbaBO();
	}
	return instancia;
}

CList<Aba, Aba&>* AbaBO::carregarAba(IProgressoLog progressoLog) {
    return AbaDAO::getInstancia()->consultarTudo(progressoLog);
}

int AbaBO::retMaxCodAba(const CList<Aba, Aba&> &listaLocal) {
	int nMaior = 0;
    Aba aba;
	POSITION pos;

	for (int i = 0; i < listaLocal.GetSize(); ++i) {
		pos = listaLocal.FindIndex(i);
		aba = listaLocal.GetAt(pos);

        if (aba.getCodigo() > nMaior) {
            nMaior = aba.getCodigo();
        }
    }
    return nMaior + 1;
}

CString AbaBO::abaToSQL(Aba aba) {
	CString sql = _T("insert into Abas(cod, nome) values(");
	sql += Rotinas::FromInt(aba.getCodigo()) + _T(",") +
		Rotinas::QuotedStr(aba.getNome()) + _T(")");

    return sql;
}

BOOL AbaBO::incluirAba(Aba aba) {
    return AbaDAO::getInstancia()->incluir(aba);
}

BOOL AbaBO::alterarAba(Aba aba) {
    return AbaDAO::getInstancia()->alterar(aba);
}

BOOL AbaBO::excluirAba(Aba aba) {
    return AbaDAO::getInstancia()->excluir(aba.getCodigo());
}

BOOL AbaBO::criarTabelaAbas() {
    return AbaDAO::getInstancia()->criarTabela();
}

Aba* AbaBO::pegaAbaPorOrdem(const CList<Aba, Aba&> &lista, int ordem) {
    Aba *aba = new Aba();
	POSITION pos;

	for (int i = 0; i < lista.GetSize(); ++i) {
		pos = lista.FindIndex(i);
		*aba = lista.GetAt(pos);

        if (aba->getOrdem() == ordem) {
            return aba;
        }
    }
    return NULL;
}

Aba* AbaBO::getElemento(const CList<Aba, Aba&> &lista, int codigo) {
    Aba *aba = new Aba();
	POSITION pos;

	for (int i = 0; i < lista.GetSize(); ++i) {
		pos = lista.FindIndex(i);
		*aba = lista.GetAt(pos);

        if (aba->getCodigo() == codigo) {
            return aba;
        }
    }
    return NULL;
}

Aba* AbaBO::pegaAbaPorNome(const CList<Aba, Aba&> &lista, const CString &nome) {
	Aba *aba = new Aba();
	POSITION pos;

	for (int i = 0; i < lista.GetSize(); ++i) {
		pos = lista.FindIndex(i);
		*aba = lista.GetAt(pos);

        if (aba->getNome() == nome) {
            return aba;
        }
    }
    return NULL;
}

}
}
