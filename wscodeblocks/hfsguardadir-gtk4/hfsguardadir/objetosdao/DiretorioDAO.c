#include "DiretorioDAO.h"

void DiretorioDAO_fecharSqlPreparado(sqlite3_stmt* pstmt) {
	sqlite3_finalize(pstmt);
}

Diretorio DiretorioDAO_novoObjeto(sqlite3_stmt* pstmt) {
    Diretorio ret = Diretorio_new();

    ret->aba->codigo = sqlite3_column_int(pstmt, 0);
	ret->codigo = sqlite3_column_int(pstmt, 1);
	ret->ordem = sqlite3_column_int(pstmt, 2);
		
	if (sqlite3_column_type(pstmt, 3) != SQLITE_NULL) {
		ret->codDirPai = sqlite3_column_int(pstmt, 3);
	}
	else {
		ret->codDirPai = -1;
	}
	char* snome = (char*)sqlite3_column_text(pstmt, 4);
	ret->arquivo->nome = g_string_new(Rotinas_retUTF8(snome));
	
	ret->arquivo->tamanho = sqlite3_column_int64(pstmt, 5);

	char* stipo = (char*)sqlite3_column_text(pstmt, 6);
	ret->tipo->codigo = stipo[0];
		
	if (ret->tipo->codigo == 'D') {
		ret->tipo->nome = Rotinas_getRecurso("TipoLista.diretorio");
	}
	else {
		ret->tipo->nome = Rotinas_getRecurso("TipoLista.arquivo");
	}

	char* smodificado = (char*)sqlite3_column_text(pstmt, 7);
	ret->modificadoFormatado = g_string_new(smodificado);

	ret->arquivo->modificado = Rotinas_StringToDate(ret->modificadoFormatado);

	char* satributos = (char*)sqlite3_column_text(pstmt, 8);
	ret->arquivo->atributos = g_string_new(satributos);

	char* scaminho = (char*)sqlite3_column_text(pstmt, 9);
	ret->caminho = g_string_new(Rotinas_retUTF8(scaminho));

	char* sabanome = (char*)sqlite3_column_text(pstmt, 10);
	ret->aba->nome = g_string_new(Rotinas_retUTF8(sabanome));
	
	char* snomepai = (char*)sqlite3_column_text(pstmt, 11);
	ret->nomePai = Rotinas_testaNull(Rotinas_retUTF8(snomepai));

	char* scaminhoPai = (char*)sqlite3_column_text(pstmt, 12);
	ret->caminhoPai = Rotinas_testaNull(Rotinas_retUTF8(scaminhoPai));
		
	ret->tamanhoFormatado = Rotinas_MontaTamanho(ret->arquivo->tamanho);

	ret->caminhoOriginal = g_string_new("");

    return ret;
}

int DiretorioDAO_consultarTotal(GString *sSQL, GString *sCondicaoTotal) {
	sqlite3_stmt* pstmt;

	int total = 0;
	GString *sTabela;
	
	if (Rotinas_cContainsStr(sSQL->str, "consultadirpai"))
		sTabela = g_string_new("consultadirpai");
	else if (Rotinas_cContainsStr(sSQL->str, "consultadirfilho"))
		sTabela = g_string_new("consultadirfilho");
	else if (Rotinas_cContainsStr(sSQL->str, "consultaarquivo"))
		sTabela = g_string_new("consultaarquivo");
	else
		sTabela = g_string_new("Diretorios");

	sSQL = g_string_append(g_string_new("select count(*) from "), 
		sTabela->str);
	
	if (Rotinas_Trim(sCondicaoTotal)->len > 0) {
		sSQL = g_string_append(sSQL, sCondicaoTotal->str);
	}
	
	const int ret = sqlite3_prepare_v2(Rotinas_getConexao(), 
		sSQL->str, (int)sSQL->len, &pstmt, NULL);

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

ListaDiretorio DiretorioDAO_consultarTudo(GString *sSQL, GString *sCondicaoTotal,
	IProgressoLog progressoLog) {
	sqlite3_stmt* pstmt;

    Diretorio obj;
	ListaDiretorio lista = ListaDiretorio_inicia();
    Progresso pb;
	pb.log = g_string_new("");
	unsigned int i = 0;
	unsigned int total = DiretorioDAO_consultarTotal(sSQL, sCondicaoTotal);

	const int ret = sqlite3_prepare_v2(Rotinas_getConexao(), 
		sSQL->str, (int)sSQL->len, &pstmt, NULL);

	if (ret == SQLITE_OK){
		pb.minimo = 0;
		pb.maximo = total - 1;
		pb.posicao = 0;
		pb.passo = 1;

		while (Rotinas_BancoPasso(pstmt)) {
			obj = DiretorioDAO_novoObjeto(pstmt);

			lista = ListaDiretorio_insere(lista, obj, i);

			pb.posicao = i;

			if (progressoLog != NULL) {
				progressoLog(pb);
				//pb.log = Rotinas_concatenar(Rotinas_cIntToStr(i), "\n");
				//OutputDebugString(pb.log->str);
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
	sqlite3_bind_int(pstmt, indice, obj->aba->codigo);

	indice = sqlite3_bind_parameter_index(pstmt, ":cod");
	sqlite3_bind_int(pstmt, indice, obj->codigo);

	indice = sqlite3_bind_parameter_index(pstmt, ":ordem");
	sqlite3_bind_int(pstmt, indice, obj->ordem);

	indice = sqlite3_bind_parameter_index(pstmt, ":coddirpai");
	sqlite3_bind_int(pstmt, indice, obj->codDirPai);

	indice = sqlite3_bind_parameter_index(pstmt, ":nome");
	sqlite3_bind_text(pstmt, indice, obj->arquivo->nome->str, 
		(int)obj->arquivo->nome->len, SQLITE_TRANSIENT);

	indice = sqlite3_bind_parameter_index(pstmt, ":tam");
	sqlite3_bind_int64(pstmt, indice, obj->arquivo->tamanho);

	indice = sqlite3_bind_parameter_index(pstmt, ":tipo");
	GString *stipo = g_string_new("");
	g_string_append_c_inline(stipo, obj->tipo->codigo);
	sqlite3_bind_text(pstmt, indice, stipo->str, (int)stipo->len, SQLITE_TRANSIENT);

	indice = sqlite3_bind_parameter_index(pstmt, ":modificado");
	sqlite3_bind_text(pstmt, indice, obj->modificadoFormatado->str, 
		(int)obj->modificadoFormatado->len, SQLITE_TRANSIENT);

	indice = sqlite3_bind_parameter_index(pstmt, ":atributos");
	sqlite3_bind_text(pstmt, indice, obj->arquivo->atributos->str, 
		(int)obj->arquivo->atributos->len, SQLITE_TRANSIENT);

	indice = sqlite3_bind_parameter_index(pstmt, ":caminho");
	sqlite3_bind_text(pstmt, indice, obj->caminho->str, 
		(int)obj->caminho->len, SQLITE_TRANSIENT);
}

gboolean DiretorioDAO_incluir(Diretorio obj) {
	sqlite3_stmt* pstmt;
	int res = 0;	
	GString *sSQL = g_string_new(
		"insert into Diretorios(aba, cod, ordem, coddirpai, nome, tam," \
		" tipo, modificado, atributos, caminho)" \
		" values (:aba, :cod, :ordem, :coddirpai, :nome, :tam," \
		" :tipo, :modificado, :atributos, :caminho)");

	int ret = sqlite3_prepare_v2(Rotinas_getConexao(),
		sSQL->str, (int)sSQL->len, &pstmt, NULL);

	DiretorioDAO_atribuirCampos(pstmt, obj);
	res = Rotinas_BancoExecPasso(pstmt, ret, "DiretorioDAO_incluir");
	DiretorioDAO_fecharSqlPreparado(pstmt);

	return (res > 0);
}

gboolean DiretorioDAO_excluir(Aba aba, GString *sCaminho) {
	sqlite3_stmt* pstmt;
	int res = 0;
	GString *sSQL = g_string_new("delete from Diretorios where caminho like :caminho and aba=:aba");

	int ret = sqlite3_prepare_v2(Rotinas_getConexao(),
		sSQL->str, (int)sSQL->len, &pstmt, NULL);

	int indice = sqlite3_bind_parameter_index(pstmt, ":caminho");
	sCaminho = g_string_append(sCaminho, "%");
	sqlite3_bind_text(pstmt, indice, sCaminho->str, (int)sCaminho->len, SQLITE_TRANSIENT);

	indice = sqlite3_bind_parameter_index(pstmt, ":aba");
	sqlite3_bind_int(pstmt, indice, aba->codigo);

	res = Rotinas_BancoExecPasso(pstmt, ret, "DiretorioDAO_excluir");
	
	DiretorioDAO_fecharSqlPreparado(pstmt);
	
	return (res > 0);
}

gboolean DiretorioDAO_criarTabela() {
	gboolean ret;
	GString *sSQL = g_string_new(
		"create table if NOT EXISTS Diretorios(" \
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
