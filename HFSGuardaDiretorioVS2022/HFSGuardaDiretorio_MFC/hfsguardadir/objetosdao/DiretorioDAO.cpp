#include "stdafx.h"

#include "DiretorioDAO.h"
#include "resource.h"
#include <stdio.h>

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
	ret.setNome(CString(snome));
	
	ret.setTamanho(sqlite3_column_int64(pstmt, 5));

	char* stipo = (char*)sqlite3_column_text(pstmt, 6);
	tipo.setCodigo(stipo[0]);
		
	if (tipo.getCodigo() == 'D') {
		tipo.setNome(Rotinas::lerStr(STR_TIPOLISTA_DIRETORIO));
	}
	else {
		tipo.setNome(Rotinas::lerStr(STR_TIPOLISTA_ARQUIVO));
	}

	ret.setTipo(tipo);

	char* smodificado = (char*)sqlite3_column_text(pstmt, 7);
	ret.setModificadoFormatado(CString(smodificado));

	ret.setModificado(Rotinas::StringToDate(ret.getModificadoFormatado()));

	char* satributos = (char*)sqlite3_column_text(pstmt, 8);
	ret.setAtributos(CString(satributos));

	char* scaminho = (char*)sqlite3_column_text(pstmt, 9);
	ret.setCaminho(CString(scaminho));

	char* sabanome = (char*)sqlite3_column_text(pstmt, 10);
	aba.setNome(CString(sabanome));
	
	ret.setAba(aba);

	char* snomepai = (char*)sqlite3_column_text(pstmt, 11);
	ret.setNomePai(Rotinas::testaNull(snomepai));

	char* scaminhoPai = (char*)sqlite3_column_text(pstmt, 12);
	ret.setCaminhoPai(Rotinas::testaNull(scaminhoPai));
		
	ret.setTamanhoFormatado(Rotinas::MontaTamanho(ret.getTamanho()));

	ret.setCaminhoOriginal(_T(""));

    return ret;
}

int DiretorioDAO::consultarTotal(const CString &sSQL, const CString &sCondicaoTotal) {
	sqlite3_stmt* pstmt;

	int total = 0;
	CString sTabela = _T("");
	CString condicaoTotal = sCondicaoTotal;
	
	if (Rotinas::ContainsStr(sSQL, CString("consultadirpai")))
		sTabela = "consultadirpai";
	else if (Rotinas::ContainsStr(sSQL, CString("consultadirfilho")))
		sTabela = "consultadirfilho";
	else if (Rotinas::ContainsStr(sSQL, CString("consultaarquivo")))
		sTabela = "consultaarquivo";
	else
		sTabela = "Diretorios";

	CString sql = _T("select count(*) from ") + sTabela;
	
	if (Rotinas::Trim(condicaoTotal).GetLength() > 0) {
		sql += condicaoTotal;
	}
	
	const char* csql = Rotinas::StringToChar(sql);
	const int ret = sqlite3_prepare_v2(Rotinas::getInstancia()->getConexao(), 
		csql, strlen(csql), &pstmt, NULL);

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

CList<Diretorio, Diretorio&>* DiretorioDAO::consultarTudo(const CString &sSQL, 
	const CString &sCondicaoTotal, IProgressoLog progressoLog) {
	sqlite3_stmt* pstmt;

    Diretorio obj;
	CList<Diretorio, Diretorio&>* lista = new CList<Diretorio, Diretorio&>();
    Progresso pb;
	unsigned int i = 0;
	unsigned int total = consultarTotal(sSQL, sCondicaoTotal);
	const char* csql = Rotinas::StringToChar(sSQL);

	const int ret = sqlite3_prepare_v2(Rotinas::getInstancia()->getConexao(), 
		csql, strlen(csql), &pstmt, NULL);

	if (ret == SQLITE_OK){
		pb.minimo = 0;
		pb.maximo = total - 1;
		pb.posicao = 0;
		pb.passo = 1;

		while (Rotinas::getInstancia()->BancoPasso(pstmt)) {	
			obj = novoObjeto(pstmt);

			lista->AddTail(obj);

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

VOID DiretorioDAO::atribuirCampos(sqlite3_stmt* pstmt, Diretorio obj) {
	int indice;

	indice = sqlite3_bind_parameter_index(pstmt, ":aba");
	sqlite3_bind_int(pstmt, indice, obj.getAba().getCodigo());

	indice = sqlite3_bind_parameter_index(pstmt, ":cod");
	sqlite3_bind_int(pstmt, indice, obj.getCodigo());

	indice = sqlite3_bind_parameter_index(pstmt, ":ordem");
	sqlite3_bind_int(pstmt, indice, obj.getOrdem());

	indice = sqlite3_bind_parameter_index(pstmt, ":coddirpai");
	sqlite3_bind_int(pstmt, indice, obj.getCodDirPai());

	indice = sqlite3_bind_parameter_index(pstmt, ":nome");
	const char* nome = Rotinas::StringToChar(obj.getNome());
	sqlite3_bind_text(pstmt, indice, nome, 
		strlen(nome), SQLITE_TRANSIENT);

	indice = sqlite3_bind_parameter_index(pstmt, ":tam");
	sqlite3_bind_int64(pstmt, indice, obj.getTamanho());

	indice = sqlite3_bind_parameter_index(pstmt, ":tipo");
	const char* stipo = Rotinas::StringToChar(CString(obj.getTipo().getCodigo()));
	sqlite3_bind_text(pstmt, indice, stipo, strlen(stipo), SQLITE_TRANSIENT);

	indice = sqlite3_bind_parameter_index(pstmt, ":modificado");
	const char* modificado = Rotinas::StringToChar(obj.getModificadoFormatado());
	sqlite3_bind_text(pstmt, indice, modificado,
		strlen(modificado), SQLITE_TRANSIENT);

	indice = sqlite3_bind_parameter_index(pstmt, ":atributos");
	const char* atributos = Rotinas::StringToChar(obj.getAtributos());
	sqlite3_bind_text(pstmt, indice, atributos, 
		strlen(atributos), SQLITE_TRANSIENT);

	indice = sqlite3_bind_parameter_index(pstmt, ":caminho");
	const char* caminho = Rotinas::StringToChar(obj.getCaminho());
	sqlite3_bind_text(pstmt, indice, caminho, 
		strlen(caminho), SQLITE_TRANSIENT);
}

BOOL DiretorioDAO::incluir(Diretorio obj) {
	sqlite3_stmt* pstmt;
	int res = 0;
	char sSQL[TAM_MAX_STR];
	strcpy_s(sSQL, TAM_MAX_STR,
		"insert into Diretorios(aba, cod, ordem, coddirpai, nome, tam," \
		" tipo, modificado, atributos, caminho)" \
		" values (:aba, :cod, :ordem, :coddirpai, :nome, :tam," \
		" :tipo, :modificado, :atributos, :caminho)");

	int ret = sqlite3_prepare_v2(Rotinas::getInstancia()->getConexao(),
		sSQL, strlen(sSQL), &pstmt, NULL);

	atribuirCampos(pstmt, obj);
	res = Rotinas::getInstancia()->BancoExecPasso(pstmt, ret, "DiretorioDAO::incluir");
	fecharSqlPreparado(pstmt);

	return (res > 0);
}

BOOL DiretorioDAO::excluir(Aba aba, const CString &sCaminho) {
	sqlite3_stmt* pstmt;
	int res = 0;
	CString scaminho = sCaminho;
	char sSQL[TAM_MAX_STR];
	strcpy_s(sSQL, TAM_MAX_STR, "delete from Diretorios where caminho like :caminho and aba=:aba");

	int ret = sqlite3_prepare_v2(Rotinas::getInstancia()->getConexao(),
		sSQL, strlen(sSQL), &pstmt, NULL);

	int indice = sqlite3_bind_parameter_index(pstmt, ":caminho");
	scaminho += "%";
	const char* caminho = Rotinas::StringToChar(scaminho);
	sqlite3_bind_text(pstmt, indice, caminho, strlen(caminho), SQLITE_TRANSIENT);

	indice = sqlite3_bind_parameter_index(pstmt, ":aba");
	sqlite3_bind_int(pstmt, indice, aba.getCodigo());

	res = Rotinas::getInstancia()->BancoExecPasso(pstmt, ret, "DiretorioDAO::excluir");
	
	fecharSqlPreparado(pstmt);
	
	return (res > 0);
}

BOOL DiretorioDAO::criarTabela() {
	BOOL ret;
	CString sSQL;
	
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
