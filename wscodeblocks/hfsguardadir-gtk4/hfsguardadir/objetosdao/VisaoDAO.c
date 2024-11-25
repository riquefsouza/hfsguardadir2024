#include "VisaoDAO.h"

GString* VisaoDAO_sqlVisao(GString *visao) {
	GString *sSQL = g_string_new("");

	g_string_printf(sSQL, "create view %s%s", visao->str, " as " \
		 "SELECT d.aba,d.cod,d.ordem,d.coddirpai,d.nome,d.tam," \
		 "d.tipo,d.modificado,d.atributos,d.caminho" \
		 ",(select nome as nomeaba from Abas where cod=d.aba) as nomeaba" \
		 ",(select nome as nomepai from Diretorios where cod=d.cod " \
		 "  and ordem=d.coddirpai and aba=d.aba) as nomepai" \
		 ",(select caminho as caminhopai from Diretorios where cod=d.cod " \
		 " and ordem=d.coddirpai and aba=d.aba) as caminhopai " \
		 "FROM Diretorios d ");

	if (g_string_equal(visao, g_string_new("consultadirpai"))) {
		sSQL = g_string_append(sSQL, "where d.tipo='D' and d.coddirpai = 0");
	}
	else if (g_string_equal(visao, g_string_new("consultadirfilho"))) {
		sSQL = g_string_append(sSQL, "where d.tipo='D' and d.coddirpai > 0");
	}

	return sSQL;
}

gboolean VisaoDAO_criarVisao(GString *visao) {
	gboolean ret;
	
	ret = Rotinas_BancoExec(VisaoDAO_sqlVisao(visao));
    
    return ret;
}
