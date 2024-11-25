#include "stdafx.h"

#include "DiretorioDAO.h"
#include "resource.h"
#include <stdio.h>

void DiretorioDAO_fecharSqlPreparado(sqlite3_stmt* pstmt) {
	sqlite3_finalize(pstmt);
}

Diretorio DiretorioDAO_novoObjeto(sqlite3_stmt* pstmt) {
    Diretorio ret;
	Aba aba;
	Tipo tipo;

    aba.codigo = sqlite3_column_int(pstmt, 0);
	ret.codigo = sqlite3_column_int(pstmt, 1);
	ret.ordem = sqlite3_column_int(pstmt, 2);
		
	if (sqlite3_column_type(pstmt, 3) != SQLITE_NULL) {
		ret.codDirPai = sqlite3_column_int(pstmt, 3);
	}
	else {
		ret.codDirPai = -1;
	}
	char* snome = (char*)sqlite3_column_text(pstmt, 4);
	ret.arquivo.nome = String_iniciar(snome);
	
	ret.arquivo.tamanho = sqlite3_column_int64(pstmt, 5);

	char* stipo = (char*)sqlite3_column_text(pstmt, 6);
	tipo.codigo = stipo[0];
		
	if (tipo.codigo == 'D') {
		tipo.nome = String_iniciar(Rotinas_lerStr(STR_TIPOLISTA_DIRETORIO));
	}
	else {
		tipo.nome = String_iniciar(Rotinas_lerStr(STR_TIPOLISTA_ARQUIVO));
	}

	ret.tipo = Tipo_copiar(tipo);

	char* smodificado = (char*)sqlite3_column_text(pstmt, 7);
	ret.modificadoFormatado = String_iniciar(smodificado);

	ret.arquivo.modificado = Rotinas_StringToDate(ret.modificadoFormatado);

	char* satributos = (char*)sqlite3_column_text(pstmt, 8);
	ret.arquivo.atributos = String_iniciar(satributos);

	char* scaminho = (char*)sqlite3_column_text(pstmt, 9);
	ret.caminho = String_iniciar(scaminho);

	char* sabanome = (char*)sqlite3_column_text(pstmt, 10);
	aba.nome = String_iniciar(sabanome);
	
	ret.aba = Aba_copiar(aba);

	char* snomepai = (char*)sqlite3_column_text(pstmt, 11);
	ret.nomePai = String_iniciar(Rotinas_testaNull(snomepai));

	char* scaminhoPai = (char*)sqlite3_column_text(pstmt, 12);
	ret.caminhoPai = String_iniciar(Rotinas_testaNull(scaminhoPai));
		
	ret.tamanhoFormatado = String_iniciar(Rotinas_MontaTamanho(ret.arquivo.tamanho));

	ret.caminhoOriginal = String_limpar();

    return ret;
}

int DiretorioDAO_consultarTotal(String sSQL, String sCondicaoTotal) {
	sqlite3_stmt* pstmt;

	int total = 0;
	String sTabela = String_iniciar("");
	
	if (String_cContainsStr(sSQL.str, "consultadirpai"))
		sTabela = String_copiar("consultadirpai");
	else if (String_cContainsStr(sSQL.str, "consultadirfilho"))
		sTabela = String_copiar("consultadirfilho");
	else if (String_cContainsStr(sSQL.str, "consultaarquivo"))
		sTabela = String_copiar("consultaarquivo");
	else
		sTabela = String_copiar("Diretorios");

	sSQL = String_concatenar("select count(*) from ", sTabela);
	
	if (String_Trim(sCondicaoTotal).length > 0) {
		sSQL = String_concatenar(sSQL, sCondicaoTotal);
	}
	
	const int ret = sqlite3_prepare_v2(Rotinas_getConexao(), 
		sSQL.str, sSQL.length, &pstmt, NULL);

	if (ret == SQLITE_OK) {
		if (Rotinas_BancoPasso(pstmt)) {
			total = sqlite3_column_int(pstmt, 0);
		}
	}
	else {
		Rotinas_BancoMostrarErro("DiretorioDAO_consultarTotal");
	}

	DiretorioDAO_fecharSqlPreparado(pstmt);

	return total;
}

ListaDiretorio DiretorioDAO_consultarTudo(String sSQL, String sCondicaoTotal,
	IProgressoLog progressoLog) {
	sqlite3_stmt* pstmt;

    Diretorio obj;
	ListaDiretorio lista = ListaDiretorio_inicia();
    Progresso pb;
	unsigned int i = 0;
	unsigned int total = DiretorioDAO_consultarTotal(sSQL, sCondicaoTotal);

	const int ret = sqlite3_prepare_v2(Rotinas_getConexao(), 
		sSQL.str, sSQL.length, &pstmt, NULL);

	if (ret == SQLITE_OK){
		pb.minimo = 0;
		pb.maximo = total - 1;
		pb.posicao = 0;
		pb.passo = 1;

		while (Rotinas_BancoPasso(pstmt)) {
			obj = DiretorioDAO_novoObjeto(pstmt);

			ListaDiretorio_insereFim(&lista, obj);

			pb.posicao = i;

			if (progressoLog != NULL) {
				progressoLog(pb);
			}

			i++;
		}
	}
	else {
		Rotinas_BancoMostrarErro("DiretorioDAO_consultarTudo");
	}

	DiretorioDAO_fecharSqlPreparado(pstmt);
	
    return lista;
}

VOID DiretorioDAO_atribuirCampos(sqlite3_stmt* pstmt, Diretorio obj) {
	int indice;

	indice = sqlite3_bind_parameter_index(pstmt, ":aba");
	sqlite3_bind_int(pstmt, indice, obj.aba.codigo);

	indice = sqlite3_bind_parameter_index(pstmt, ":cod");
	sqlite3_bind_int(pstmt, indice, obj.codigo);

	indice = sqlite3_bind_parameter_index(pstmt, ":ordem");
	sqlite3_bind_int(pstmt, indice, obj.ordem);

	indice = sqlite3_bind_parameter_index(pstmt, ":coddirpai");
	sqlite3_bind_int(pstmt, indice, obj.codDirPai);

	indice = sqlite3_bind_parameter_index(pstmt, ":nome");
	sqlite3_bind_text(pstmt, indice, obj.arquivo.nome.str, 
		obj.arquivo.nome.length, SQLITE_TRANSIENT);

	indice = sqlite3_bind_parameter_index(pstmt, ":tam");
	sqlite3_bind_int64(pstmt, indice, obj.arquivo.tamanho);

	indice = sqlite3_bind_parameter_index(pstmt, ":tipo");
	String stipo = String_iniciar(obj.tipo.codigo);
	sqlite3_bind_text(pstmt, indice, stipo.str, stipo.length, SQLITE_TRANSIENT);

	indice = sqlite3_bind_parameter_index(pstmt, ":modificado");
	sqlite3_bind_text(pstmt, indice, obj.modificadoFormatado.str, 
		obj.modificadoFormatado.length, SQLITE_TRANSIENT);

	indice = sqlite3_bind_parameter_index(pstmt, ":atributos");
	sqlite3_bind_text(pstmt, indice, obj.arquivo.atributos.str, 
		obj.arquivo.atributos.length, SQLITE_TRANSIENT);

	indice = sqlite3_bind_parameter_index(pstmt, ":caminho");
	sqlite3_bind_text(pstmt, indice, obj.caminho.str, 
		obj.caminho.length, SQLITE_TRANSIENT);
}

BOOL DiretorioDAO_incluir(Diretorio obj) {
	sqlite3_stmt* pstmt;
	int res = 0;	
	String sSQL = String_iniciar(
		"insert into Diretorios(aba, cod, ordem, coddirpai, nome, tam," \
		" tipo, modificado, atributos, caminho)" \
		" values (:aba, :cod, :ordem, :coddirpai, :nome, :tam," \
		" :tipo, :modificado, :atributos, :caminho)");

	int ret = sqlite3_prepare_v2(Rotinas_getConexao(),
		sSQL.str, sSQL.length, &pstmt, NULL);

	DiretorioDAO_atribuirCampos(pstmt, obj);
	res = Rotinas_BancoExecPasso(pstmt, ret, "DiretorioDAO_incluir");
	DiretorioDAO_fecharSqlPreparado(pstmt);

	return (res > 0);
}

BOOL DiretorioDAO_excluir(Aba aba, String sCaminho) {
	sqlite3_stmt* pstmt;
	int res = 0;
	String sSQL = String_iniciar("delete from Diretorios where caminho like :caminho and aba=:aba");

	int ret = sqlite3_prepare_v2(Rotinas_getConexao(),
		sSQL.str, sSQL.length, &pstmt, NULL);

	int indice = sqlite3_bind_parameter_index(pstmt, ":caminho");
	sCaminho = String_concatenar(sCaminho, "%");
	sqlite3_bind_text(pstmt, indice, sCaminho.str, sCaminho.length, SQLITE_TRANSIENT);

	indice = sqlite3_bind_parameter_index(pstmt, ":aba");
	sqlite3_bind_int(pstmt, indice, aba.codigo);

	res = Rotinas_BancoExecPasso(pstmt, ret, "DiretorioDAO_excluir");
	
	DiretorioDAO_fecharSqlPreparado(pstmt);
	
	return (res > 0);
}

BOOL DiretorioDAO_criarTabela() {
	BOOL ret;
	String sSQL = String_iniciar("");
	
	sSQL = String_copiar("create table if NOT EXISTS Diretorios(" \
		"aba int not null," \
		"cod int not null," \
		"ordem int not null," \
		"nome varchar(255) not null," \
		"tam numeric not null," \
		"tipo char(1) not null," \
		"modificado date not null," \
		"atributos varchar(20) not null," \
		"coddirpai int not null," \
		"caminho varchar(255) not null," \
		"primary key (aba, cod, ordem))");
	
	ret = Rotinas_BancoExec(sSQL);
    
    return ret;
}
