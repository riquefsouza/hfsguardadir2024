#include "AbaBO.h"
#include "../objetosdao/AbaDAO.h"

ListaAba AbaBO_carregarAba(IProgressoLog progressoLog) {
    return AbaDAO_consultarTudo(progressoLog);
}

int AbaBO_retMaxCodAba(ListaAba listaLocal) {
	guint tamlista = ListaAba_conta(listaLocal);
	int nMaior = 0;
    Aba aba = Aba_new();

	for (unsigned int i = 0; i < tamlista; i++) {
		aba = ListaAba_pesquisaItemOrd(listaLocal, i);

        if (aba->codigo > nMaior) {
            nMaior = aba->codigo;
        }
    }
    return nMaior + 1;
}

GString* AbaBO_abaToSQL(Aba aba) {
	GString* sql = g_string_new("insert into Abas(cod, nome) values(");
	sql = Rotinas_concatenar2(sql, Rotinas_IntToStr(aba->codigo),
		Rotinas_QuotedStr(aba->nome)->str);

    return sql;
}

gboolean AbaBO_incluirAba(Aba aba) {
    return AbaDAO_incluir(aba);
}

gboolean AbaBO_alterarAba(Aba aba) {
    return AbaDAO_alterar(aba);
}

gboolean AbaBO_excluirAba(Aba aba) {
    return AbaDAO_excluir(aba->codigo);
}

gboolean AbaBO_criarTabelaAbas() {
    return AbaDAO_criarTabela();
}

Aba AbaBO_pegaAbaPorOrdem(ListaAba lista, int ordem) {
    Aba aba = Aba_new();
	guint tamlista = ListaAba_conta(lista);

	for (unsigned int i = 0; i < tamlista; i++) {
		aba = ListaAba_pesquisaItemOrd(lista, i);

        if (aba->ordem == ordem) {
            return aba;
        }
    }
    return NULL;
}

Aba AbaBO_getElemento(ListaAba lista, int codigo) {
    Aba aba = Aba_new();
	guint tamlista = ListaAba_conta(lista);

	for (unsigned int i = 0; i < tamlista; i++) {
		aba = ListaAba_pesquisaItemOrd(lista, i);

        if (aba->codigo == codigo) {
            return aba;
        }
    }
    return NULL;
}

Aba AbaBO_pegaAbaPorNome(ListaAba lista, GString *nome) {
    Aba aba = Aba_new();
	guint tamlista = ListaAba_conta(lista);

	for (unsigned int i = 0; i < tamlista; i++) {
		aba = ListaAba_pesquisaItemOrd(lista, i);

        if (g_string_equal(aba->nome, nome)) {
            return aba;
        }
    }
    return NULL;
}
