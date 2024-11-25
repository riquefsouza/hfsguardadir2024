#include "AbaDAO.h"

void AbaDAO_fecharSqlPreparado(sqlite3_stmt* pstmt) {
	sqlite3_finalize(pstmt);
}

Aba AbaDAO_novoObjeto(sqlite3_stmt* pstmt) {
    Aba ret = Aba_new();

    ret->codigo = sqlite3_column_int(pstmt, 0);
	char* snome = (char*)sqlite3_column_text(pstmt, 1);   
	ret->nome = g_string_new(snome);
    return ret;
}

int AbaDAO_consultarTotal() {
	sqlite3_stmt* pstmt;

	int total = 0;
	GString *sSQL = g_string_new("select count(*) from Abas");
	
	const int ret = sqlite3_prepare_v2(Rotinas_getConexao(), 
		sSQL->str, (int)sSQL->len, &pstmt, NULL);

	if (ret == SQLITE_OK) {
		if (Rotinas_BancoPasso(pstmt)) {
			total = sqlite3_column_int(pstmt, 0);
		}
	}
	else {
		Rotinas_BancoMostrarErro("AbaDAO_consultarTotal");
	}

	AbaDAO_fecharSqlPreparado(pstmt);

	return total;
}

ListaAba AbaDAO_consultarTudo(IProgressoLog progressoLog) {
	sqlite3_stmt* pstmt;

	Aba obj;
	ListaAba lista = ListaAba_inicia();
	Progresso pb;
	unsigned int i = 0;
	unsigned int total = AbaDAO_consultarTotal();
	GString *sSQL = g_string_new("select cod, nome from Abas");

	const int ret = sqlite3_prepare_v2(Rotinas_getConexao(), 
		sSQL->str, (int)sSQL->len, &pstmt, NULL);

	if (ret == SQLITE_OK){
		pb.minimo = 0;
		pb.maximo = total - 1;
		pb.posicao = 0;
		pb.passo = 1;

		while (Rotinas_BancoPasso(pstmt)) {
			obj = AbaDAO_novoObjeto(pstmt);
			obj->ordem = i + 1;

			lista = ListaAba_insere(lista, obj, i);

			pb.posicao = i;

			if (progressoLog != NULL) {
				progressoLog(pb);
			}

			i++;
		}
	}
	else {
		Rotinas_BancoMostrarErro("AbaDAO_consultarTudo");
	}

	AbaDAO_fecharSqlPreparado(pstmt);
	
    return lista;
}

void AbaDAO_atribuirCampos(sqlite3_stmt* pstmt, Aba obj) {
	int indice;

	indice = sqlite3_bind_parameter_index(pstmt, ":cod");
	sqlite3_bind_int(pstmt, indice, obj->codigo);

	indice = sqlite3_bind_parameter_index(pstmt, ":nome");
	sqlite3_bind_text(pstmt, indice, obj->nome->str, (int)obj->nome->len, SQLITE_TRANSIENT);
}

gboolean AbaDAO_incluir(Aba obj) {
	sqlite3_stmt* pstmt;
	int res = 0;	
	char sSQL[TAM_MAX_STR];
	strcpy_s(sSQL, TAM_MAX_STR, "insert into Abas(cod, nome) values(:cod,:nome)");

	int ret = sqlite3_prepare_v2(Rotinas_getConexao(),
		sSQL, (int)strlen(sSQL), &pstmt, NULL);

	AbaDAO_atribuirCampos(pstmt, obj);
	res = Rotinas_BancoExecPasso(pstmt, ret, "AbaDAO_incluir");
	AbaDAO_fecharSqlPreparado(pstmt);

	return (res > 0);
}

gboolean AbaDAO_alterar(Aba obj) {
	sqlite3_stmt* pstmt;
	int res = 0;
	char sSQL[TAM_MAX_STR];
	strcpy_s(sSQL, TAM_MAX_STR, "update Abas set nome=:nome where cod=:cod");

	int ret = sqlite3_prepare_v2(Rotinas_getConexao(),
		sSQL, (int)strlen(sSQL), &pstmt, NULL);

	AbaDAO_atribuirCampos(pstmt, obj);
	res = Rotinas_BancoExecPasso(pstmt, ret, "AbaDAO_incluir");
	AbaDAO_fecharSqlPreparado(pstmt);

	return (res > 0);
}

gboolean AbaDAO_excluir(int codigo) {
	sqlite3_stmt* pstmt;
	int res = 0;
	char sSQL[TAM_MAX_STR];

	strcpy_s(sSQL, TAM_MAX_STR, "delete from Diretorios where aba=:cod");
	int ret = sqlite3_prepare_v2(Rotinas_getConexao(),
		sSQL, (int)strlen(sSQL), &pstmt, NULL);
	int indice = sqlite3_bind_parameter_index(pstmt, ":cod");
	sqlite3_bind_int(pstmt, indice, codigo);
	res = Rotinas_BancoExecPasso(pstmt, ret, "AbaDAO_excluir");
	AbaDAO_fecharSqlPreparado(pstmt);

	strcpy_s(sSQL, TAM_MAX_STR, "delete from Abas where cod=:cod");
	ret = sqlite3_prepare_v2(Rotinas_getConexao(),
		sSQL, (int)strlen(sSQL), &pstmt, NULL);
	indice = sqlite3_bind_parameter_index(pstmt, ":cod");
	sqlite3_bind_int(pstmt, indice, codigo);
	res = Rotinas_BancoExecPasso(pstmt, ret, "AbaDAO_excluir");
	AbaDAO_fecharSqlPreparado(pstmt);

	return (res > 0);
}

gboolean AbaDAO_criarTabela() {
	gboolean ret;
	GString* sSQL;
	
	sSQL = g_string_new("create table IF NOT EXISTS Abas(" \
                  "cod integer not null, nome varchar(10) not null, " \
                  "primary key (cod))");
	
	ret = Rotinas_BancoExec(sSQL);
    
    return ret;
}
