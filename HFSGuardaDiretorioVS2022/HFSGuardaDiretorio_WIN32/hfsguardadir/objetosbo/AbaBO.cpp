#include "stdafx.h"

#include "AbaBO.h"
#include "hfsguardadir/objetosdao/AbaDAO.h"

ListaAba AbaBO_carregarAba(IProgressoLog progressoLog) {
    return AbaDAO_consultarTudo(progressoLog);
}

int AbaBO_retMaxCodAba(ListaAba listaLocal) {
    ListaAba local;
	int nMaior = 0;
    Aba aba;

    for (local = listaLocal; local != NULL; local = local->proximo) {
        aba = local->aba;

        if (aba.codigo > nMaior) {
            nMaior = aba.codigo;
        }
    }
    return nMaior + 1;
}

String AbaBO_abaToSQL(Aba aba) {
	String sql = String_iniciar("insert into Abas(cod, nome) values(");
	sql = String_concatenar(sql, String_FromInt(aba.codigo), 
		String_QuotedStr(aba.nome));

    return sql;
}

BOOL AbaBO_incluirAba(Aba aba) {
    return AbaDAO_incluir(aba);
}

BOOL AbaBO_alterarAba(Aba aba) {
    return AbaDAO_alterar(aba);
}

BOOL AbaBO_excluirAba(Aba aba) {
    return AbaDAO_excluir(aba.codigo);
}

BOOL AbaBO_criarTabelaAbas() {
    return AbaDAO_criarTabela();
}

Aba* AbaBO_pegaAbaPorOrdem(ListaAba lista, int ordem) {
    Aba *aba = Aba_new();
	ListaAba local;

    for (local = lista; local != NULL; local = local->proximo) {
        *aba = local->aba;

        if (aba->ordem == ordem) {
            return aba;
        }
    }
    return NULL;
}

Aba* AbaBO_getElemento(ListaAba lista, int codigo) {
    Aba *aba = Aba_new();
	ListaAba local;

    for (local = lista; local != NULL; local = local->proximo) {
        *aba = local->aba;

        if (aba->codigo == codigo) {
            return aba;
        }
    }
    return NULL;
}

Aba* AbaBO_pegaAbaPorNome(ListaAba lista, String nome) {
    Aba *aba = Aba_new();
	ListaAba local;

    for (local = lista; local != NULL; local = local->proximo) {
        *aba = local->aba;

        if (String_comparar(aba->nome, nome)) {
            return aba;
        }
    }
    return NULL;
}
