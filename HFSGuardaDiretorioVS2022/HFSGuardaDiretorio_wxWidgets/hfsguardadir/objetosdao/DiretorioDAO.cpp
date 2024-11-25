#include "DiretorioDAO.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosdao {

DiretorioDAO* DiretorioDAO::instancia = NULL;

DiretorioDAO::DiretorioDAO()
{

}

DiretorioDAO::DiretorioDAO(DiretorioDAO const&){

}

DiretorioDAO& DiretorioDAO::operator=(DiretorioDAO const&){
    return *instancia;
}

DiretorioDAO* DiretorioDAO::getInstancia() {
    if (!instancia) {
        instancia = new DiretorioDAO();
    }
    return instancia;
}

void DiretorioDAO::fecharSqlPreparado() {
	if (pstmt.IsOk()) {
		pstmt.Finalize();
	}
}

Diretorio DiretorioDAO::novoObjeto(wxSQLite3ResultSet res) {
    Diretorio ret;
    Aba aba;
    Tipo tipo;
	wxString stipo;
	wxULongLong tamanho;
	
    aba.setCodigo(res.GetInt(0));
    ret.setCodigo(res.GetInt(1));
    ret.setOrdem(res.GetInt(2));

    if (!res.IsNull(3)) {
        ret.setCodDirPai(res.GetInt(3));
    } else {
        ret.setCodDirPai(-1);
    }
    ret.setNome(res.GetString(4));
	tamanho = res.GetInt64(5);
    ret.setTamanho(tamanho);

	stipo = res.GetString(6);
    tipo.setCodigo(stipo.GetChar(0));
	if (tipo.getCodigo() == 'D') {
		tipo.setNome(Rotinas::getRecurso("TipoLista.diretorio"));
	}
	else {
		tipo.setNome(Rotinas::getRecurso("TipoLista.arquivo"));
	}

    ret.setTipo(tipo);
	ret.setModificadoFormatado(res.GetString(7));
	ret.setModificado(Rotinas::StringToDate(ret.getModificadoFormatado()));
	ret.setAtributos(res.GetString(8));
    ret.setCaminho(res.GetString(9));
    aba.setNome(res.GetString(10));
    ret.setAba(aba);
    ret.setNomePai(Rotinas::testaNull(res.GetString(11)));
    ret.setCaminhoPai(Rotinas::testaNull(res.GetString(12)));
    ret.setTamanhoFormatado(Rotinas::MontaTamanho(tamanho.GetValue()));

	return ret;
}

int DiretorioDAO::consultarTotal(const wxString &sSQL,
                                 const wxString &sCondicaoTotal) {
    int total = 0;
    wxString sTabela, sql;

    if (Rotinas::ContainsStr(sSQL, "consultadirpai"))
        sTabela = "consultadirpai";
    else if (Rotinas::ContainsStr(sSQL, "consultadirfilho"))
        sTabela = "consultadirfilho";
    else if (Rotinas::ContainsStr(sSQL, "consultaarquivo"))
        sTabela = "consultaarquivo";
    else
        sTabela = "Diretorios";

    sql = "select count(*) from " + sTabela;
    if (Rotinas::Trim(sCondicaoTotal).length() > 0){
        sql += " " + sCondicaoTotal;
    }

	try
	{
		conexao = Rotinas::getInstancia()->getConexao();
		pstmt = conexao->PrepareStatement(sql);
		total = pstmt.ExecuteScalar();
		this->fecharSqlPreparado();
	}
	catch (wxSQLite3Exception& e) {
		Rotinas::getInstancia()->mostrarErro(e, "DiretorioDAO::consultarTotal");
	}

    return total;
}

wxVector<Diretorio> DiretorioDAO::consultarTudo(const wxString &sSQL,
                                             const wxString &sCondicaoTotal,
                                             IProgressoLog progressoLog) {
    Diretorio obj;
	wxVector<Diretorio> lista;
    Progresso pb;
    int i = 0;
    int total = this->consultarTotal(sSQL, sCondicaoTotal);

	try
	{
		conexao = Rotinas::getInstancia()->getConexao();
		pstmt = conexao->PrepareStatement(sSQL);
		wxSQLite3ResultSet res = pstmt.ExecuteQuery();

		if (total > 0) {
            pb.minimo = 0;
            pb.maximo = total - 1;
            pb.posicao = 0;
            pb.passo = 1;

			while (res.NextRow()) {
                obj = novoObjeto(res);

                lista.push_back(obj);

                pb.posicao = i;

                if (progressoLog != NULL) {
                    progressoLog(pb);
                }

                i++;
            }
        }

	    this->fecharSqlPreparado();
	}
	catch (wxSQLite3Exception& e) {
		Rotinas::getInstancia()->mostrarErro(e, "DiretorioDAO::consultarTudo");
	}

    return lista;
}

void DiretorioDAO::atribuirCampos(Diretorio obj) {
	wxLongLong tamanho;

	pstmt.Bind(pstmt.GetParamIndex(":aba"), obj.getAba().getCodigo());
	pstmt.Bind(pstmt.GetParamIndex(":cod"), obj.getCodigo());
    pstmt.Bind(pstmt.GetParamIndex(":ordem"), obj.getOrdem());
    pstmt.Bind(pstmt.GetParamIndex(":coddirpai"), obj.getCodDirPai());
    pstmt.Bind(pstmt.GetParamIndex(":nome"), obj.getNome());
	tamanho = obj.getTamanho();
    pstmt.Bind(pstmt.GetParamIndex(":tam"), tamanho);
    pstmt.Bind(pstmt.GetParamIndex(":tipo"), wxString(obj.getTipo().getCodigo()));
    pstmt.Bind(pstmt.GetParamIndex(":modificado"), obj.getModificadoFormatado());
    pstmt.Bind(pstmt.GetParamIndex(":atributos"), obj.getAtributos());
    pstmt.Bind(pstmt.GetParamIndex(":caminho"), obj.getCaminho());
}

bool DiretorioDAO::incluir(Diretorio obj) {
	int res = 0;
	wxString sSQL = "insert into Diretorios(aba, cod, ordem, coddirpai, nome, tam," \
		" tipo, modificado, atributos, caminho)" \
		" values (:aba, :cod, :ordem, :coddirpai, :nome, :tam," \
		" :tipo, :modificado, :atributos, :caminho)";

	try {
		conexao = Rotinas::getInstancia()->getConexao();
		pstmt = conexao->PrepareStatement(sSQL);
	    atribuirCampos(obj);
		res = pstmt.ExecuteUpdate();
		this->fecharSqlPreparado();
	}
	catch (wxSQLite3Exception& e) {
		Rotinas::getInstancia()->mostrarErro(e, "DiretorioDAO::incluir");
		return false;
	}
	return (res > 0);
}

bool DiretorioDAO::excluir(Aba aba, const wxString &sCaminho) {
	int res = 0;
	wxString sSQL = "delete from Diretorios where caminho like :caminho and aba=:aba";
	
	try {
		conexao = Rotinas::getInstancia()->getConexao();
		pstmt = conexao->PrepareStatement(sSQL);
		pstmt.Bind(pstmt.GetParamIndex(":caminho"), sCaminho + "%");
		pstmt.Bind(pstmt.GetParamIndex(":aba"), aba.getCodigo());
		res = pstmt.ExecuteUpdate();
	this->fecharSqlPreparado();
	}
	catch (wxSQLite3Exception& e) {
		Rotinas::getInstancia()->mostrarErro(e, "DiretorioDAO::excluir");
		return false;
	}
	return (res > 0);
}

bool DiretorioDAO::criarTabela() {
    wxString sSQL;
    bool ret;

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

	ret = Rotinas::getInstancia()->execConsulta(sSQL);

	return ret;
}

}
}
