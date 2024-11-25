#include "stdafx.h"

#include "VisaoDAO.h"

namespace hfsguardadir {

namespace objetosdao {

VisaoDAO* VisaoDAO::instancia = NULL;

VisaoDAO::VisaoDAO()
{

}

VisaoDAO::VisaoDAO(VisaoDAO const&) {

}

VisaoDAO& VisaoDAO::operator=(VisaoDAO const&) {
	return *instancia;
}

VisaoDAO* VisaoDAO::getInstancia() {
	if (!instancia) {
		instancia = new VisaoDAO();
	}
	return instancia;
}

CString VisaoDAO::sqlVisao(const CString &visao) {
	CString sSQL;

	sSQL = _T("create view ") + visao +
		 _T(" as SELECT d.aba,d.cod,d.ordem,d.coddirpai,d.nome,d.tam," \
		 "d.tipo,d.modificado,d.atributos,d.caminho" \
		 ",(select nome as nomeaba from Abas where cod=d.aba) as nomeaba" \
		 ",(select nome as nomepai from Diretorios where cod=d.cod " \
		 "  and ordem=d.coddirpai and aba=d.aba) as nomepai" \
		 ",(select caminho as caminhopai from Diretorios where cod=d.cod " \
		 " and ordem=d.coddirpai and aba=d.aba) as caminhopai " \
		 "FROM Diretorios d ");

	if (visao == "consultadirpai") {
		sSQL += "where d.tipo='D' and d.coddirpai = 0";
	}
	else if (visao == "consultadirfilho") {
		sSQL += "where d.tipo='D' and d.coddirpai > 0";
	}

	return sSQL;
}

BOOL VisaoDAO::criarVisao(const CString &visao) {
	BOOL ret;
	
	ret = Rotinas::getInstancia()->BancoExec(VisaoDAO::sqlVisao(visao));
    
    return ret;
}

}
}
