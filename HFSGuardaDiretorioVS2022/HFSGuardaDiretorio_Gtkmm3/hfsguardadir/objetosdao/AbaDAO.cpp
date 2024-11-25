#include "AbaDAO.h"

namespace hfsguardadir {

namespace objetosdao {

AbaDAO* AbaDAO::instancia = NULL;

AbaDAO::AbaDAO()
{

}

AbaDAO::AbaDAO(AbaDAO const&) {

}

AbaDAO& AbaDAO::operator=(AbaDAO const&) {
	return *instancia;
}

AbaDAO* AbaDAO::getInstancia() {
	if (!instancia) {
		instancia = new AbaDAO();
	}
	return instancia;
}

void AbaDAO::fecharSqlPreparado(sqlite3_stmt* pstmt) {
	sqlite3_finalize(pstmt);
}

Aba AbaDAO::novoObjeto(sqlite3_stmt* pstmt) {
	Aba ret;

	ret.setCodigo(sqlite3_column_int(pstmt, 0));
	char* snome = (char*)sqlite3_column_text(pstmt, 1);
	ret.setNome(snome);
	return ret;
}

int AbaDAO::consultarTotal() {
	sqlite3_stmt* pstmt;

	int total = 0;
	char sSQL[TAM_MAX_STR];
	strcpy_s(sSQL, TAM_MAX_STR, "select count(*) from Abas");

	const int ret = sqlite3_prepare_v2(Rotinas::getInstancia()->getConexao(),
		sSQL, strlen(sSQL), &pstmt, NULL);

	if (ret == SQLITE_OK) {
		if (Rotinas::getInstancia()->BancoPasso(pstmt)) {
			total = sqlite3_column_int(pstmt, 0);
		}
	}
	else {
		Rotinas::getInstancia()->BancoMostrarErro("AbaDAO::consultarTotal");
	}

	AbaDAO::fecharSqlPreparado(pstmt);

	return total;
}

std::vector<Aba> AbaDAO::consultarTudo(IProgressoLog progressoLog) {
	sqlite3_stmt* pstmt;

	Aba obj;
	std::vector<Aba> lista;
	Progresso pb;
	unsigned int i = 0;
	unsigned int total = AbaDAO::consultarTotal();
	char sSQL[TAM_MAX_STR];
	strcpy_s(sSQL, TAM_MAX_STR, "select cod, nome from Abas");

	const int ret = sqlite3_prepare_v2(Rotinas::getInstancia()->getConexao(),
		sSQL, strlen(sSQL), &pstmt, NULL);

	if (ret == SQLITE_OK) {
		pb.minimo = 0;
		pb.maximo = total - 1;
		pb.posicao = 0;
		pb.passo = 1;

		while (Rotinas::getInstancia()->BancoPasso(pstmt)) {
			obj = AbaDAO::novoObjeto(pstmt);
			obj.setOrdem(i + 1);

			lista.push_back(obj);

			pb.posicao = i;

			if (progressoLog != NULL) {
				progressoLog(pb);
			}

			i++;
		}
	}
	else {
		Rotinas::getInstancia()->BancoMostrarErro("AbaDAO::consultarTudo");
	}

	AbaDAO::fecharSqlPreparado(pstmt);

	return lista;
}

void AbaDAO::atribuirCampos(sqlite3_stmt* pstmt, Aba obj) {
	int indice;

	indice = sqlite3_bind_parameter_index(pstmt, ":cod");
	sqlite3_bind_int(pstmt, indice, obj.getCodigo());

	indice = sqlite3_bind_parameter_index(pstmt, ":nome");
	const char* nome = obj.getNome().c_str();
	sqlite3_bind_text(pstmt, indice, nome, strlen(nome), SQLITE_TRANSIENT);
}

bool AbaDAO::incluir(Aba obj) {
	sqlite3_stmt* pstmt;
	int res = 0;
	char sSQL[TAM_MAX_STR];
	strcpy_s(sSQL, TAM_MAX_STR, "insert into Abas(cod, nome) values(:cod,:nome)");

	int ret = sqlite3_prepare_v2(Rotinas::getInstancia()->getConexao(),
		sSQL, strlen(sSQL), &pstmt, NULL);

	AbaDAO::atribuirCampos(pstmt, obj);
	res = Rotinas::getInstancia()->BancoExecPasso(pstmt, ret, "AbaDAO::incluir");
	AbaDAO::fecharSqlPreparado(pstmt);

	return (res > 0);
}

bool AbaDAO::alterar(Aba obj) {
	sqlite3_stmt* pstmt;
	int res = 0;
	char sSQL[TAM_MAX_STR];
	strcpy_s(sSQL, TAM_MAX_STR, "update Abas set nome=:nome where cod=:cod");

	int ret = sqlite3_prepare_v2(Rotinas::getInstancia()->getConexao(),
		sSQL, strlen(sSQL), &pstmt, NULL);

	AbaDAO::atribuirCampos(pstmt, obj);
	res = Rotinas::getInstancia()->BancoExecPasso(pstmt, ret, "AbaDAO::incluir");
	AbaDAO::fecharSqlPreparado(pstmt);

	return (res > 0);
}

bool AbaDAO::excluir(int codigo) {
	sqlite3_stmt* pstmt;
	int res = 0;
	Glib::ustring sSQL;

	sSQL = "delete from Diretorios where aba=:cod";
	int ret = sqlite3_prepare_v2(Rotinas::getInstancia()->getConexao(),
		sSQL.c_str(), sSQL.length(), &pstmt, NULL);
	int indice = sqlite3_bind_parameter_index(pstmt, ":cod");
	sqlite3_bind_int(pstmt, indice, codigo);
	res = Rotinas::getInstancia()->BancoExecPasso(pstmt, ret, "AbaDAO::excluir");
	AbaDAO::fecharSqlPreparado(pstmt);

	sSQL = "delete from Abas where cod=:cod";
	ret = sqlite3_prepare_v2(Rotinas::getInstancia()->getConexao(),
		sSQL.c_str(), sSQL.length(), &pstmt, NULL);
	indice = sqlite3_bind_parameter_index(pstmt, ":cod");
	sqlite3_bind_int(pstmt, indice, codigo);
	res = Rotinas::getInstancia()->BancoExecPasso(pstmt, ret, "AbaDAO::excluir");
	AbaDAO::fecharSqlPreparado(pstmt);

	return (res > 0);
}

bool AbaDAO::criarTabela() {
	bool ret;
	Glib::ustring sSQL;

	sSQL = "create table IF NOT EXISTS Abas(" \
		"cod integer not null, nome varchar(10) not null, " \
		"primary key (cod))";

	ret = Rotinas::getInstancia()->BancoExec(sSQL);

	return ret;
}

}
}
