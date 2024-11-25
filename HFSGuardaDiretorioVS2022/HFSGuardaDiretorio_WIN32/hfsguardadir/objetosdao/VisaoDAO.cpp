#include "stdafx.h"

#include "VisaoDAO.h"

String VisaoDAO_sqlVisao(String visao) {
	String sSQL = String_iniciar("");

	sSQL = String_concatenar(sSQL, 3, "create view ", visao.str, " as " \
		 "SELECT d.aba,d.cod,d.ordem,d.coddirpai,d.nome,d.tam," \
		 "d.tipo,d.modificado,d.atributos,d.caminho" \
		 ",(select nome as nomeaba from Abas where cod=d.aba) as nomeaba" \
		 ",(select nome as nomepai from Diretorios where cod=d.cod " \
		 "  and ordem=d.coddirpai and aba=d.aba) as nomepai" \
		 ",(select caminho as caminhopai from Diretorios where cod=d.cod " \
		 " and ordem=d.coddirpai and aba=d.aba) as caminhopai " \
		 "FROM Diretorios d ");

	if (String_comparar(visao, "consultadirpai")) {
		sSQL = String_concatenar(sSQL, "where d.tipo='D' and d.coddirpai = 0");
	}
	else if (String_comparar(visao, "consultadirfilho")) {
		sSQL = String_concatenar(sSQL, "where d.tipo='D' and d.coddirpai > 0");
	}

	return sSQL;
}

BOOL VisaoDAO_criarVisao(String visao) {
	BOOL ret;
	
	ret = Rotinas_BancoExec(VisaoDAO_sqlVisao(visao));
    
    return ret;
}
