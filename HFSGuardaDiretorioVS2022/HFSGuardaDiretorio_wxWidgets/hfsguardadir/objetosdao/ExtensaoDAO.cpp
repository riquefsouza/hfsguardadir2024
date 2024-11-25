#include "ExtensaoDAO.h"
#include "FrmPrincipal.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosdao {

ExtensaoDAO* ExtensaoDAO::instancia = NULL;

ExtensaoDAO::ExtensaoDAO()
{

}

ExtensaoDAO::ExtensaoDAO(ExtensaoDAO const&){

}

ExtensaoDAO& ExtensaoDAO::operator=(ExtensaoDAO const&){
    return *instancia;
}

ExtensaoDAO* ExtensaoDAO::getInstancia() {
    if (!instancia) {
        instancia = new ExtensaoDAO();
    }
    return instancia;
}

void ExtensaoDAO::fecharSqlPreparado() {
	if (pstmt.IsOk()) {
		pstmt.Finalize();
	}
}

Extensao ExtensaoDAO::novoObjeto(wxSQLite3ResultSet res) {
    Extensao ret;
	wxMemoryBuffer bmp16, bmp32;

    ret.setCodigo(res.GetInt(0));
    ret.setNome(res.GetString(1));
	res.GetBlob(2, bmp16);
    ret.setBmp16(bmp16);
	res.GetBlob(3, bmp32);
    ret.setBmp32(bmp32);

	wxImage img = Rotinas::MemoryBufferToImage(bmp16, wxBITMAP_TYPE_BMP);
	wxBitmap *bmp = new wxBitmap(img);
	frmPrincipal->imageList16->Add(*bmp);

	img = Rotinas::MemoryBufferToImage(bmp32, wxBITMAP_TYPE_BMP);
	bmp = new wxBitmap(img);
	frmPrincipal->imageList32->Add(*bmp);

	/*
    if (!ret.getBmp16().isEmpty()) {
        ret.setGif16(Rotinas::BmpParaImagem(ret.getBmp16(),
                Rotinas::EXTENSAO_GIF));
    }
    if (ret.getBmp32().isEmpty()) {
        ret.setGif32(Rotinas::BmpParaImagem(ret.getBmp32(),
                Rotinas::EXTENSAO_GIF));
    }
    */
    return ret;
}

int ExtensaoDAO::consultarTotal() {
    int total = 0;

	try {
		conexao = Rotinas::getInstancia()->getConexao();
		pstmt = conexao->PrepareStatement("select count(*) from Extensoes");
		total = pstmt.ExecuteScalar();
		this->fecharSqlPreparado();
	}
	catch (wxSQLite3Exception& e) {
		Rotinas::getInstancia()->mostrarErro(e, "ExtensaoDAO::consultarTotal");
	}

    return total;
}

wxVector<Extensao> ExtensaoDAO::consultarTudo(IProgressoLog progressoLog) {
    Extensao obj;
	wxVector<Extensao> lista;
    Progresso pb;
    int i = 0;
    int total = this->consultarTotal();

	try
	{
		conexao = Rotinas::getInstancia()->getConexao();
		pstmt = conexao->PrepareStatement("select cod, nome, bmp16, bmp32 from Extensoes");
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
	}
	catch (wxSQLite3Exception& e) {
		Rotinas::getInstancia()->mostrarErro(e, "ExtensaoDAO::consultarTudo");
	}

    return lista;
}

bool ExtensaoDAO::incluir(Extensao obj) {
    int res = 0;

	try {
		conexao = Rotinas::getInstancia()->getConexao();
		pstmt = conexao->PrepareStatement(
			"insert into Extensoes(cod, nome, bmp16, bmp32) values(:cod,:nome,:bmp16,:bmp32)");
		pstmt.Bind(pstmt.GetParamIndex(":cod"), obj.getCodigo());
		pstmt.Bind(pstmt.GetParamIndex(":nome"), obj.getNome());
		pstmt.Bind(pstmt.GetParamIndex(":bmp16"), obj.getBmp16());
		pstmt.Bind(pstmt.GetParamIndex(":bmp32"), obj.getBmp32());
		res = pstmt.ExecuteUpdate();
		this->fecharSqlPreparado();
	}
	catch (wxSQLite3Exception& e) {
		Rotinas::getInstancia()->mostrarErro(e, "ExtensaoDAO::incluir");
		return false;
	}
	return (res > 0);
}

bool ExtensaoDAO::excluir(int codigo) {
	int res = 0;

	try {
		conexao = Rotinas::getInstancia()->getConexao();
		pstmt = conexao->PrepareStatement("delete from Extensoes where cod=:cod");
		pstmt.Bind(pstmt.GetParamIndex(":cod"), codigo);
		res = pstmt.ExecuteUpdate();
		this->fecharSqlPreparado();
	}
	catch (wxSQLite3Exception& e) {
		Rotinas::getInstancia()->mostrarErro(e, "ExtensaoDAO::excluir");
		return false;
	}
	return (res > 0);
}

bool ExtensaoDAO::excluirTudo() {
	int res = 0;

	try {
		conexao = Rotinas::getInstancia()->getConexao();
		pstmt = conexao->PrepareStatement("delete from Extensoes");
		res = pstmt.ExecuteUpdate();
		this->fecharSqlPreparado();
	}
	catch (wxSQLite3Exception& e) {
		Rotinas::getInstancia()->mostrarErro(e, "ExtensaoDAO::excluirTudo");
		return false;
	}
	return (res > 0);
}

bool ExtensaoDAO::criarTabela() {
	wxString sSQL;
    bool ret;

	sSQL = "create table IF NOT EXISTS Extensoes(" \
                  "cod integer not null," \
                  "nome varchar(20) not null," \
                  "bmp16 BLOB COLLATE NOCASE null," \
                  "bmp32 BLOB COLLATE NOCASE null," \
                  "primary key (cod))";
	ret = Rotinas::getInstancia()->execConsulta(sSQL);

    return ret;
}

}
}
