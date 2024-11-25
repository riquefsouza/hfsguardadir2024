#include "AbaDAO.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosdao {

AbaDAO* AbaDAO::instancia = NULL;

AbaDAO::AbaDAO()
{

}

AbaDAO::AbaDAO(AbaDAO const&){

}

AbaDAO& AbaDAO::operator=(AbaDAO const&){
    return *instancia;
}

AbaDAO* AbaDAO::getInstancia() {
    if (!instancia) {
        instancia = new AbaDAO();
    }
    return instancia;
}

void AbaDAO::fecharSqlPreparado() {	
	if (pstmt.IsOk()) {
		pstmt.Finalize();
	}
}

Aba AbaDAO::novoObjeto(wxSQLite3ResultSet res) {
    Aba ret;
    ret.setCodigo(res.GetInt(0));
    ret.setNome(res.GetString(1));
    return ret;
}

int AbaDAO::consultarTotal() {
    int total = 0;

	try {
		conexao = Rotinas::getInstancia()->getConexao();
		pstmt = conexao->PrepareStatement("select count(*) from Abas");
		total = pstmt.ExecuteScalar();
		this->fecharSqlPreparado();
	} 
	catch (wxSQLite3Exception& e) {
		Rotinas::getInstancia()->mostrarErro(e, "AbaDAO::consultarTotal");
	}

    return total;
}

wxVector<Aba> AbaDAO::consultarTudo(IProgressoLog progressoLog) {
    Aba obj;
	wxVector<Aba> lista;
    Progresso pb;
    int i = 0;
    int total = this->consultarTotal();

	try
	{
		conexao = Rotinas::getInstancia()->getConexao();
		pstmt = conexao->PrepareStatement("select cod, nome from Abas");
		wxSQLite3ResultSet res = pstmt.ExecuteQuery();

		if (total > 0) {
			pb.minimo = 0;
			pb.maximo = total - 1;
			pb.posicao = 0;
			pb.passo = 1;

			while (res.NextRow()) {
				obj = novoObjeto(res);
				obj.setOrdem(i + 1);

				lista.push_back(obj);

				pb.posicao = i;

				if (progressoLog != NULL) {
					progressoLog(pb);
				}

				i++;
			}
		}

		this->fecharSqlPreparado();

	} catch (wxSQLite3Exception& e) {
		Rotinas::getInstancia()->mostrarErro(e, "AbaDAO::consultarTudo");
	}

    return lista;
}

bool AbaDAO::incluir(Aba obj) {
	int res = 0;

	try {
		conexao = Rotinas::getInstancia()->getConexao();
		pstmt = conexao->PrepareStatement("insert into Abas(cod, nome) values(?,?)");
		pstmt.Bind(1, obj.getCodigo());
		pstmt.Bind(2, obj.getNome());
		res = pstmt.ExecuteUpdate();
		this->fecharSqlPreparado();		
	}
	catch (wxSQLite3Exception& e) {
		Rotinas::getInstancia()->mostrarErro(e, "AbaDAO::incluir");
		return false;
	}
	return (res > 0);
}

bool AbaDAO::alterar(Aba obj) {
	int res = 0;

	try {
		conexao = Rotinas::getInstancia()->getConexao();
		pstmt = conexao->PrepareStatement("update Abas set nome=? where cod=?");
		pstmt.Bind(1, obj.getNome());
		pstmt.Bind(2, obj.getCodigo());	
		res = pstmt.ExecuteUpdate();
		this->fecharSqlPreparado();
	}
	catch (wxSQLite3Exception& e) {
		Rotinas::getInstancia()->mostrarErro(e, "AbaDAO::alterar");
		return false;
	}
	return (res > 0);
}

bool AbaDAO::excluir(int codigo) {
	int res = 0;

	try {
		conexao = Rotinas::getInstancia()->getConexao();

		pstmt = conexao->PrepareStatement("delete from Diretorios where aba=?");
		pstmt.Bind(1, codigo);
		int res = pstmt.ExecuteUpdate();
		this->fecharSqlPreparado();

		pstmt = conexao->PrepareStatement("delete from Abas where cod=?");
		pstmt.Bind(1, codigo);
		res = pstmt.ExecuteUpdate();
		this->fecharSqlPreparado();
	}
	catch (wxSQLite3Exception& e) {
		Rotinas::getInstancia()->mostrarErro(e, "AbaDAO::excluir");
		return false;
	}
	return (res > 0);
}

bool AbaDAO::criarTabela() {
    bool ret;

    wxString sSQL = "create table IF NOT EXISTS Abas(" \
                  "cod integer not null, nome varchar(10) not null, " \
                  "primary key (cod))";
	ret = Rotinas::getInstancia()->execConsulta(sSQL);
    
    return ret;
}

}
}
