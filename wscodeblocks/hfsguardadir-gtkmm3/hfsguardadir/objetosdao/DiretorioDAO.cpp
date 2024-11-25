#include "DiretorioDAO.h"
#include "resource.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosdao {

DiretorioDAO* DiretorioDAO::instancia = NULL;

DiretorioDAO::DiretorioDAO()
{

}

DiretorioDAO::DiretorioDAO(DiretorioDAO const&) {

}

DiretorioDAO& DiretorioDAO::operator=(DiretorioDAO const&) {
	return *instancia;
}

DiretorioDAO* DiretorioDAO::getInstancia() {
	if (!instancia) {
		instancia = new DiretorioDAO();
	}
	return instancia;
}

void DiretorioDAO::fecharSqlPreparado(sqlite3_stmt* pstmt) {
	sqlite3_finalize(pstmt);
}

Diretorio DiretorioDAO::novoObjeto(sqlite3_stmt* pstmt) {
    Diretorio ret;
	Aba aba;
	Tipo tipo;

    aba.setCodigo(sqlite3_column_int(pstmt, 0));
	ret.setCodigo(sqlite3_column_int(pstmt, 1));
	ret.setOrdem(sqlite3_column_int(pstmt, 2));
		
	if (sqlite3_column_type(pstmt, 3) != SQLITE_NULL) {
		ret.setCodDirPai(sqlite3_column_int(pstmt, 3));
	}
	else {
		ret.setCodDirPai(-1);
	}
	char* snome = (char*)sqlite3_column_text(pstmt, 4);
	ret.setNome(Rotinas::retUTF8(snome));
	
	ret.setTamanho(sqlite3_column_int64(pstmt, 5));

	char* stipo = (char*)sqlite3_column_text(pstmt, 6);
	tipo.setCodigo(stipo[0]);
		
	if (tipo.getCodigo() == 'D') {
		tipo.setNome(Rotinas::getRecurso("TipoLista.diretorio"));
	}
	else {
		tipo.setNome(Rotinas::getRecurso("TipoLista.arquivo"));
	}

	ret.setTipo(tipo);

	char* smodificado = (char*)sqlite3_column_text(pstmt, 7);
	ret.setModificadoFormatado(Glib::ustring(smodificado));

	ret.setModificado(Rotinas::StringToDate(ret.getModificadoFormatado()));

	char* satributos = (char*)sqlite3_column_text(pstmt, 8);
	ret.setAtributos(Glib::ustring(satributos));

	char* scaminho = (char*)sqlite3_column_text(pstmt, 9);
	ret.setCaminho(Rotinas::retUTF8(scaminho));

	char* sabanome = (char*)sqlite3_column_text(pstmt, 10);
	aba.setNome(Rotinas::retUTF8(sabanome));
	
	ret.setAba(aba);

	char* snomepai = (char*)sqlite3_column_text(pstmt, 11);
	ret.setNomePai(Rotinas::retUTF8(snomepai));

	char* scaminhoPai = (char*)sqlite3_column_text(pstmt, 12);
	ret.setCaminhoPai(Rotinas::retUTF8(scaminhoPai));
		
	ret.setTamanhoFormatado(Rotinas::MontaTamanho(ret.getTamanho()));

	ret.setCaminhoOriginal("");

    return ret;
}

int DiretorioDAO::consultarTotal(const Glib::ustring &sSQL, const Glib::ustring &sCondicaoTotal) {
	sqlite3_stmt* pstmt;

	int total = 0;
	Glib::ustring sTabela = "";
	Glib::ustring condicaoTotal = sCondicaoTotal;
	
	if (Rotinas::ContainsStr(sSQL, Glib::ustring("consultadirpai")))
		sTabela = "consultadirpai";
	else if (Rotinas::ContainsStr(sSQL, Glib::ustring("consultadirfilho")))
		sTabela = "consultadirfilho";
	else if (Rotinas::ContainsStr(sSQL, Glib::ustring("consultaarquivo")))
		sTabela = "consultaarquivo";
	else
		sTabela = "Diretorios";

	Glib::ustring sql = "select count(*) from " + sTabela;
	
	if (Rotinas::Trim(condicaoTotal).length() > 0) {
		sql += condicaoTotal;
	}
	
	const int ret = sqlite3_prepare_v2(Rotinas::getInstancia()->getConexao(), 
		sql.c_str(), sql.length(), &pstmt, NULL);

	if (ret == SQLITE_OK) {
		if (Rotinas::getInstancia()->BancoPasso(pstmt)) {
			total = sqlite3_column_int(pstmt, 0);
		}
	}
	else {
		Rotinas::getInstancia()->BancoMostrarErro("DiretorioDAO::consultarTotal");
	}

	fecharSqlPreparado(pstmt);

	return total;
}

std::vector<Diretorio> DiretorioDAO::consultarTudo(const Glib::ustring &sSQL,
	const Glib::ustring &sCondicaoTotal, IProgressoLog progressoLog) {
	sqlite3_stmt* pstmt;

    Diretorio obj;
	std::vector<Diretorio> lista;
    Progresso pb;
	unsigned int i = 0;
	unsigned int total = consultarTotal(sSQL, sCondicaoTotal);

	const int ret = sqlite3_prepare_v2(Rotinas::getInstancia()->getConexao(), 
		sSQL.c_str(), sSQL.length(), &pstmt, NULL);

	if (ret == SQLITE_OK){
		pb.minimo = 0;
		pb.maximo = total - 1;
		pb.posicao = 0;
		pb.passo = 1;

		while (Rotinas::getInstancia()->BancoPasso(pstmt)) {	
			obj = novoObjeto(pstmt);

			lista.push_back(obj);

			pb.posicao = i;

			if (progressoLog != NULL) {
				progressoLog(pb);
			}

			i++;
		}
	}
	else {
		Rotinas::getInstancia()->BancoMostrarErro("DiretorioDAO::consultarTudo");
	}

	fecharSqlPreparado(pstmt);
	
    return lista;
}

void DiretorioDAO::atribuirCampos(sqlite3_stmt* pstmt, Diretorio obj) {
	int indice;
	Glib::ustring ustipo;

	indice = sqlite3_bind_parameter_index(pstmt, ":aba");
	sqlite3_bind_int(pstmt, indice, obj.getAba().getCodigo());

	indice = sqlite3_bind_parameter_index(pstmt, ":cod");
	sqlite3_bind_int(pstmt, indice, obj.getCodigo());

	indice = sqlite3_bind_parameter_index(pstmt, ":ordem");
	sqlite3_bind_int(pstmt, indice, obj.getOrdem());

	indice = sqlite3_bind_parameter_index(pstmt, ":coddirpai");
	sqlite3_bind_int(pstmt, indice, obj.getCodDirPai());

	indice = sqlite3_bind_parameter_index(pstmt, ":nome");
	const char* nome = obj.getNome().c_str();
	sqlite3_bind_text(pstmt, indice, nome, 
		strlen(nome), SQLITE_TRANSIENT);

	indice = sqlite3_bind_parameter_index(pstmt, ":tam");
	sqlite3_bind_int64(pstmt, indice, obj.getTamanho());

	indice = sqlite3_bind_parameter_index(pstmt, ":tipo");	
	ustipo = obj.getTipo().getCodigo();
	const char* stipo = ustipo.c_str();
	sqlite3_bind_text(pstmt, indice, stipo, strlen(stipo), SQLITE_TRANSIENT);

	indice = sqlite3_bind_parameter_index(pstmt, ":modificado");
	const char* modificado = obj.getModificadoFormatado().c_str();
	sqlite3_bind_text(pstmt, indice, modificado,
		strlen(modificado), SQLITE_TRANSIENT);

	indice = sqlite3_bind_parameter_index(pstmt, ":atributos");
	const char* atributos = obj.getAtributos().c_str();
	sqlite3_bind_text(pstmt, indice, atributos, 
		strlen(atributos), SQLITE_TRANSIENT);

	indice = sqlite3_bind_parameter_index(pstmt, ":caminho");
	const char* caminho = obj.getCaminho().c_str();
	sqlite3_bind_text(pstmt, indice, caminho, 
		strlen(caminho), SQLITE_TRANSIENT);
}

bool DiretorioDAO::incluir(Diretorio obj) {
	sqlite3_stmt* pstmt;
	int res = 0;
	Glib::ustring sSQL;

	sSQL = "insert into Diretorios(aba, cod, ordem, coddirpai, nome, tam," \
		" tipo, modificado, atributos, caminho)" \
		" values (:aba, :cod, :ordem, :coddirpai, :nome, :tam," \
		" :tipo, :modificado, :atributos, :caminho)";

	int ret = sqlite3_prepare_v2(Rotinas::getInstancia()->getConexao(),
		sSQL.c_str(), sSQL.length(), &pstmt, NULL);

	atribuirCampos(pstmt, obj);
	res = Rotinas::getInstancia()->BancoExecPasso(pstmt, ret, "DiretorioDAO::incluir");
	fecharSqlPreparado(pstmt);

	return (res > 0);
}

bool DiretorioDAO::excluir(Aba aba, const Glib::ustring &sCaminho) {
	sqlite3_stmt* pstmt;
	int res = 0;
	Glib::ustring scaminho = sCaminho;
	Glib::ustring sSQL;

	sSQL = "delete from Diretorios where caminho like :caminho and aba=:aba";

	int ret = sqlite3_prepare_v2(Rotinas::getInstancia()->getConexao(),
		sSQL.c_str(), sSQL.length(), &pstmt, NULL);

	int indice = sqlite3_bind_parameter_index(pstmt, ":caminho");
	scaminho += "%";
	sqlite3_bind_text(pstmt, indice, scaminho.c_str(), 
		scaminho.length(), SQLITE_TRANSIENT);

	indice = sqlite3_bind_parameter_index(pstmt, ":aba");
	sqlite3_bind_int(pstmt, indice, aba.getCodigo());

	res = Rotinas::getInstancia()->BancoExecPasso(pstmt, ret, "DiretorioDAO::excluir");
	
	fecharSqlPreparado(pstmt);
	
	return (res > 0);
}

bool DiretorioDAO::criarTabela() {
	bool ret;
	Glib::ustring sSQL;
	
	sSQL = "create table if NOT EXISTS Diretorios(" \
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
		"primary key (aba, cod, ordem))";
	
	ret = Rotinas::getInstancia()->BancoExec(sSQL);
    
    return ret;
}

}
}
