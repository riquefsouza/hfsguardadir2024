package hfsguardadir.objetosdao;

import hfsguardadir.comum.Rotinas;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class VisaoDAO {

    private static VisaoDAO instancia;

    private Connection conexao;

    private PreparedStatement pstmt;

    private VisaoDAO() {
        super();
    }

    public static VisaoDAO getInstancia() {
        if (instancia == null) {
            instancia = new VisaoDAO();
        }
        return instancia;
    }

    private void fecharSqlPreparado() throws SQLException {
        if (pstmt != null) {
            pstmt.close();
        }
    }

    public int criarVisao(String visao) throws SQLException {
        int ret;
        conexao = Rotinas.getConexao();
        pstmt = conexao.prepareStatement(sqlVisao(visao));
        ret = pstmt.executeUpdate();
        this.fecharSqlPreparado();
        return ret;
    }
 
    private String sqlVisao(String visao) {
        String sSQL = "create view " + visao + " as "
                + "SELECT d.aba,d.cod,d.ordem,d.coddirpai,d.nome,d.tam,"
                + "d.tipo,d.modificado,d.atributos,d.caminho"
                + ",(select nome as nomeaba from Abas where cod=d.aba) as nomeaba"
                + ",(select nome as nomepai from Diretorios where cod=d.cod "
                + "  and ordem=d.coddirpai and aba=d.aba) as nomepai"
                + ",(select caminho as caminhopai from Diretorios where cod=d.cod "
                + " and ordem=d.coddirpai and aba=d.aba) as caminhopai "
                + "FROM Diretorios d ";

        if (visao.equals("consultadirpai")) {
            sSQL += "where d.tipo='D' and d.coddirpai = 0";
        } else if (visao.equals("consultadirfilho")) {
            sSQL += "where d.tipo='D' and d.coddirpai > 0";
        }

        return sSQL;
    }
    
}
