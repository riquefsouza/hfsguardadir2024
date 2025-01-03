#include "ExtensaoDAO.h"

void ExtensaoDAO_fecharSqlPreparado(sqlite3_stmt* pstmt) {
	sqlite3_finalize(pstmt);
}

Extensao ExtensaoDAO_novoObjeto(sqlite3_stmt* pstmt) {
    Extensao ret = Extensao_new();

    ret->codigo = sqlite3_column_int(pstmt, 0);

	char* snome = (char*)sqlite3_column_text(pstmt, 1);
    ret->nome = g_string_new(snome);

	const void* blobBmp16 = sqlite3_column_blob(pstmt, 2);
	int tamanhoBmp16 = sqlite3_column_bytes(pstmt, 2);

	const void* blobBmp32 = sqlite3_column_blob(pstmt, 3);
	int tamanhoBmp32 = sqlite3_column_bytes(pstmt, 3);
	
	ret->bmp16 = Rotinas_BlobToPixbuf(blobBmp16, tamanhoBmp16);
	ret->tamanhoBmp16 = tamanhoBmp16;
	ret->bmp32 = Rotinas_BlobToPixbuf(blobBmp32, tamanhoBmp32);
	ret->tamanhoBmp32 = tamanhoBmp32;
	
    return ret;
}

int ExtensaoDAO_consultarTotal() {
	sqlite3_stmt* pstmt;
	int total = 0;
	char sSQL[TAM_MAX_STR];
	strcpy_s(sSQL, TAM_MAX_STR, "select count(*) from Extensoes");

	const int ret = sqlite3_prepare_v2(Rotinas_getConexao(), 
		sSQL, (int)strlen(sSQL), &pstmt, NULL);

	if (ret == SQLITE_OK) {
		if (Rotinas_BancoPasso(pstmt)) {
			total = sqlite3_column_int(pstmt, 0);
		}
	}
	else {
		Rotinas_BancoMostrarErro("Rotinas_BancoExec");
	}

	ExtensaoDAO_fecharSqlPreparado(pstmt);

	return total;
}

ListaExtensao ExtensaoDAO_consultarTudo(IProgressoLog progressoLog) {
	sqlite3_stmt* pstmt;
    Extensao obj;
	ListaExtensao lista = ListaExtensao_inicia();
    Progresso pb;
	unsigned int i = 0;
	unsigned int total = ExtensaoDAO_consultarTotal();
	char sSQL[TAM_MAX_STR];
	strcpy_s(sSQL, TAM_MAX_STR, "select cod, nome, bmp16, bmp32 from Extensoes");

	const int ret = sqlite3_prepare_v2(Rotinas_getConexao(), 
		sSQL, (int)strlen(sSQL), &pstmt, NULL);

	if (ret == SQLITE_OK){
		pb.minimo = 0;
		pb.maximo = total - 1;
		pb.posicao = 0;
		pb.passo = 1;

		while (Rotinas_BancoPasso(pstmt)) {
			obj = ExtensaoDAO_novoObjeto(pstmt);
			obj->ordem = i + 1;

			lista = ListaExtensao_insere(lista, obj, i);

			pb.posicao = i;

			if (progressoLog != NULL) {
				progressoLog(pb);
			}

			i++;
		}
	}
	else {
		Rotinas_BancoMostrarErro("Rotinas_BancoExec");
	}

	ExtensaoDAO_fecharSqlPreparado(pstmt);
	
    return lista;
}

VOID ExtensaoDAO_atribuirCampos(sqlite3_stmt* pstmt, Extensao obj) {
	int indice;

	indice = sqlite3_bind_parameter_index(pstmt, ":cod");
	sqlite3_bind_int(pstmt, indice, obj->codigo);

	indice = sqlite3_bind_parameter_index(pstmt, ":nome");
	sqlite3_bind_text(pstmt, indice, obj->nome->str, (int)obj->nome->len, SQLITE_TRANSIENT);

	indice = sqlite3_bind_parameter_index(pstmt, ":bmp16");
	void* blobBmp16 = NULL;
	size_t tamBmp16 = Rotinas_PixbufToBlob(obj->bmp16, &blobBmp16, Rotinas_EXTENSAO_BMP);
	
	sqlite3_bind_blob(pstmt, indice, blobBmp16, (int)tamBmp16, SQLITE_TRANSIENT);

	indice = sqlite3_bind_parameter_index(pstmt, ":bmp32");
	void* blobBmp32 = NULL;
	size_t tamBmp32 = Rotinas_PixbufToBlob(obj->bmp32, &blobBmp32, Rotinas_EXTENSAO_BMP);
	
	sqlite3_bind_blob(pstmt, indice, blobBmp32, (int)tamBmp32, SQLITE_TRANSIENT);
}

gboolean ExtensaoDAO_incluir(Extensao obj) {
	sqlite3_stmt* pstmt;
	int res = 0;	
	char sSQL[TAM_MAX_STR];
	strcpy_s(sSQL, TAM_MAX_STR, 
		"insert into Extensoes(cod, nome, bmp16, bmp32) values(:cod,:nome,:bmp16,:bmp32)");

	int ret = sqlite3_prepare_v2(Rotinas_getConexao(),
		sSQL, (int)strlen(sSQL), &pstmt, NULL);

	ExtensaoDAO_atribuirCampos(pstmt, obj);
	res = Rotinas_BancoExecPasso(pstmt, ret, "ExtensaoDAO_incluir");
	ExtensaoDAO_fecharSqlPreparado(pstmt);

	return (res > 0);
}

gboolean ExtensaoDAO_excluir(int codigo) {
	sqlite3_stmt* pstmt;
	int res = 0;
	char sSQL[TAM_MAX_STR];

	strcpy_s(sSQL, TAM_MAX_STR, "delete from Extensoes where cod=:cod");
	
	int ret = sqlite3_prepare_v2(Rotinas_getConexao(),
		sSQL, (int)strlen(sSQL), &pstmt, NULL);

	int indice = sqlite3_bind_parameter_index(pstmt, ":cod");
	sqlite3_bind_int(pstmt, indice, codigo);
	
	res = Rotinas_BancoExecPasso(pstmt, ret, "ExtensaoDAO_excluir");
	
	ExtensaoDAO_fecharSqlPreparado(pstmt);

	return (res > 0);
}

gboolean ExtensaoDAO_excluirTudo() {
	gboolean ret;
	GString* sSQL = g_string_new("delete from Extensoes");

	ret = Rotinas_BancoExec(sSQL);

	return ret;
}

gboolean ExtensaoDAO_criarTabela() {
	gboolean ret;
	GString* sSQL = g_string_new(
		"create table IF NOT EXISTS Extensoes(" \
		"cod integer not null," \
		"nome varchar(20) not null," \
		"bmp16 BLOB COLLATE NOCASE null," \
		"bmp32 BLOB COLLATE NOCASE null," \
		"primary key (cod))");
	
	ret = Rotinas_BancoExec(sSQL);
    
    return ret;
}
