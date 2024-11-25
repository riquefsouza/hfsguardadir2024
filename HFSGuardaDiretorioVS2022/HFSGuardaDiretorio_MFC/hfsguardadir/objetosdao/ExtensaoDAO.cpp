#include "stdafx.h"

#include "ExtensaoDAO.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "FrmPrincipal.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosdao {

ExtensaoDAO* ExtensaoDAO::instancia = NULL;

ExtensaoDAO::ExtensaoDAO()
{

}

ExtensaoDAO::ExtensaoDAO(ExtensaoDAO const&) {

}

ExtensaoDAO& ExtensaoDAO::operator=(ExtensaoDAO const&) {
	return *instancia;
}

ExtensaoDAO* ExtensaoDAO::getInstancia() {
	if (!instancia) {
		instancia = new ExtensaoDAO();
	}
	return instancia;
}

void ExtensaoDAO::fecharSqlPreparado(sqlite3_stmt* pstmt) {
	sqlite3_finalize(pstmt);
}

Extensao ExtensaoDAO::novoObjeto(sqlite3_stmt* pstmt) {
    Extensao ret;

    ret.setCodigo(sqlite3_column_int(pstmt, 0));

	char* snome = (char*)sqlite3_column_text(pstmt, 1);
    ret.setNome(CString(snome));

	const void* blobBmp16 = sqlite3_column_blob(pstmt, 2);
	int tamanhoBmp16 = sqlite3_column_bytes(pstmt, 2);

	const void* blobBmp32 = sqlite3_column_blob(pstmt, 3);
	int tamanhoBmp32 = sqlite3_column_bytes(pstmt, 3);

	ret.setBmp16(Rotinas::BlobToBitmap(blobBmp16, tamanhoBmp16, 
		frmPrincipal->imageList16));
	ret.setBmp32(Rotinas::BlobToBitmap(blobBmp32, tamanhoBmp32, 
		frmPrincipal->imageList32));
	
    return ret;
}

int ExtensaoDAO::consultarTotal() {
	sqlite3_stmt* pstmt;
	int total = 0;
	char sSQL[TAM_MAX_STR];
	strcpy_s(sSQL, TAM_MAX_STR, "select count(*) from Extensoes");

	const int ret = sqlite3_prepare_v2(Rotinas::getInstancia()->getConexao(), 
		sSQL, strlen(sSQL), &pstmt, NULL);

	if (ret == SQLITE_OK) {
		if (Rotinas::getInstancia()->BancoPasso(pstmt)) {
			total = sqlite3_column_int(pstmt, 0);
		}
	}
	else {
		Rotinas::getInstancia()->BancoMostrarErro("Rotinas::getInstancia()->BancoExec");
	}

	ExtensaoDAO::fecharSqlPreparado(pstmt);

	return total;
}

CList<Extensao, Extensao&>* ExtensaoDAO::consultarTudo(IProgressoLog progressoLog) {
	sqlite3_stmt* pstmt;
    Extensao obj;
	CList<Extensao, Extensao&>* lista = new CList<Extensao, Extensao&>();
    Progresso pb;
	unsigned int i = 0;
	unsigned int total = consultarTotal();
	char sSQL[TAM_MAX_STR];
	strcpy_s(sSQL, TAM_MAX_STR, "select cod, nome, bmp16, bmp32 from Extensoes");

	const int ret = sqlite3_prepare_v2(Rotinas::getInstancia()->getConexao(), 
		sSQL, strlen(sSQL), &pstmt, NULL);

	if (ret == SQLITE_OK){
		pb.minimo = 0;
		pb.maximo = total - 1;
		pb.posicao = 0;
		pb.passo = 1;

		while (Rotinas::getInstancia()->BancoPasso(pstmt)) {
			obj = novoObjeto(pstmt);
			obj.setOrdem(i + 1);

			lista->AddTail(obj);

			pb.posicao = i;

			if (progressoLog != NULL) {
				progressoLog(pb);
			}

			i++;
		}
	}
	else {
		Rotinas::getInstancia()->BancoMostrarErro("Rotinas::getInstancia()->BancoExec");
	}

	fecharSqlPreparado(pstmt);
	
    return lista;
}

VOID ExtensaoDAO::atribuirCampos(sqlite3_stmt* pstmt, Extensao obj) {
	int indice;

	indice = sqlite3_bind_parameter_index(pstmt, ":cod");
	sqlite3_bind_int(pstmt, indice, obj.getCodigo());

	indice = sqlite3_bind_parameter_index(pstmt, ":nome");
	const char* nome = Rotinas::StringToChar(obj.getNome());
	sqlite3_bind_text(pstmt, indice, nome, strlen(nome), SQLITE_TRANSIENT);

	indice = sqlite3_bind_parameter_index(pstmt, ":bmp16");
	void* blobBmp16 = NULL;
	size_t tamBmp16 = Rotinas::BitmapToBlob(obj.getBmp16(), &blobBmp16);
	
	sqlite3_bind_blob(pstmt, indice, blobBmp16, tamBmp16, SQLITE_TRANSIENT);

	indice = sqlite3_bind_parameter_index(pstmt, ":bmp32");
	void* blobBmp32 = NULL;
	size_t tamBmp32 = Rotinas::BitmapToBlob(obj.getBmp32(), &blobBmp32);
	
	sqlite3_bind_blob(pstmt, indice, blobBmp32, tamBmp32, SQLITE_TRANSIENT);
}

BOOL ExtensaoDAO::incluir(Extensao obj) {
	sqlite3_stmt* pstmt;
	int res = 0;	
	char sSQL[TAM_MAX_STR];
	strcpy_s(sSQL, TAM_MAX_STR, 
		"insert into Extensoes(cod, nome, bmp16, bmp32) values(:cod,:nome,:bmp16,:bmp32)");

	int ret = sqlite3_prepare_v2(Rotinas::getInstancia()->getConexao(),
		sSQL, strlen(sSQL), &pstmt, NULL);

	atribuirCampos(pstmt, obj);
	res = Rotinas::getInstancia()->BancoExecPasso(pstmt, ret, "ExtensaoDAO::incluir");
	fecharSqlPreparado(pstmt);

	return (res > 0);
}

BOOL ExtensaoDAO::excluir(int codigo) {
	sqlite3_stmt* pstmt;
	int res = 0;
	char sSQL[TAM_MAX_STR];

	strcpy_s(sSQL, TAM_MAX_STR, "delete from Extensoes where cod=:cod");
	
	int ret = sqlite3_prepare_v2(Rotinas::getInstancia()->getConexao(),
		sSQL, strlen(sSQL), &pstmt, NULL);

	int indice = sqlite3_bind_parameter_index(pstmt, ":cod");
	sqlite3_bind_int(pstmt, indice, codigo);
	
	res = Rotinas::getInstancia()->BancoExecPasso(pstmt, ret, "ExtensaoDAO::excluir");
	
	fecharSqlPreparado(pstmt);

	return (res > 0);
}

BOOL ExtensaoDAO::excluirTudo() {
	BOOL ret;
	CString sSQL = _T("delete from Extensoes");

	ret = Rotinas::getInstancia()->BancoExec(sSQL);

	return ret;
}

BOOL ExtensaoDAO::criarTabela() {
	BOOL ret;
	CString sSQL;
	
	sSQL = _T("create table IF NOT EXISTS Extensoes(" \
		"cod integer not null," \
		"nome varchar(20) not null," \
		"bmp16 BLOB COLLATE NOCASE null," \
		"bmp32 BLOB COLLATE NOCASE null," \
		"primary key (cod))");
	
	ret = Rotinas::getInstancia()->BancoExec(sSQL);
    
    return ret;
}

}
}
