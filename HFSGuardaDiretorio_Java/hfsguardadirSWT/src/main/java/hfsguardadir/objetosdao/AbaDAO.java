package hfsguardadir.objetosdao;

import hfsguardadir.comum.IProgressoLog;
import hfsguardadir.comum.Progresso;
import hfsguardadir.comum.Rotinas;
import hfsguardadir.objetos.Aba;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

public class AbaDAO {

    private static AbaDAO instancia;

    private Connection conexao;

    private PreparedStatement pstmt;

    private AbaDAO() {
        super();
    }

    public static AbaDAO getInstancia() {
        if (instancia == null) {
            instancia = new AbaDAO();
        }
        return instancia;
    }

    private void fecharSqlPreparado() throws SQLException {
        if (pstmt != null) {
            pstmt.close();
        }
    }

    private Aba novoObjeto(ResultSet res) throws SQLException {
        Aba ret = new Aba();
        ret.setCodigo(res.getInt(1));
        ret.setNome(res.getString(2));
        return ret;
    }

    public int consultarTotal() throws SQLException {
        int total = 0;
        conexao = Rotinas.getConexao();
        pstmt = conexao.prepareStatement("select count(*) from Abas");
        ResultSet res = pstmt.executeQuery();

        if (res.next()) {
            total = res.getInt(1);
        }
        this.fecharSqlPreparado();

        return total;
    }

    public ArrayList<Aba> consultarTudo(IProgressoLog progressoLog)
            throws SQLException {
        Aba obj;
        ArrayList<Aba> lista = new ArrayList<>();
        Progresso pb;
        int i = 0;
        int total = this.consultarTotal();

        conexao = Rotinas.getConexao();
        pstmt = conexao.prepareStatement("select cod, nome from Abas");
        ResultSet res = pstmt.executeQuery();

        if (total > 0) {
            pb = new Progresso();
            pb.setMinimo(0);
            pb.setMaximo(total - 1);
            pb.setPosicao(0);
            pb.setPasso(1);

            while (res.next()) {
                obj = novoObjeto(res);
                obj.setOrdem(i + 1);

                lista.add(obj);

                pb.setPosicao(i);

                if (progressoLog != null) {
                    progressoLog.ProgressoLog(pb);
                }

                i++;
            }
        }

        this.fecharSqlPreparado();

        return lista;
    }

    public int incluir(Aba obj) throws SQLException {
        int ret;
        conexao = Rotinas.getConexao();
        pstmt = conexao
                .prepareStatement("insert into Abas(cod, nome) values(?,?)");
        pstmt.setInt(1, obj.getCodigo());
        pstmt.setString(2, obj.getNome());
        ret = pstmt.executeUpdate();
        this.fecharSqlPreparado();
        return ret;
    }

    public int alterar(Aba obj) throws SQLException {
        int ret;
        conexao = Rotinas.getConexao();
        pstmt = conexao.prepareStatement("update Abas set nome=? where cod=?");
        pstmt.setString(1, obj.getNome());
        pstmt.setInt(2, obj.getCodigo());
        ret = pstmt.executeUpdate();
        this.fecharSqlPreparado();
        return ret;
    }

    public int excluir(int codigo) throws SQLException {
        int ret;
        conexao = Rotinas.getConexao();

        pstmt = conexao.prepareStatement("delete from Diretorios where aba=?");
        pstmt.setInt(1, codigo);
        pstmt.executeUpdate();

        pstmt = conexao.prepareStatement("delete from Abas where cod=?");
        pstmt.setInt(1, codigo);
        ret = pstmt.executeUpdate();
        this.fecharSqlPreparado();
        return ret;
    }

    public int criarTabela() throws SQLException {
        int ret;
        conexao = Rotinas.getConexao();
        pstmt = conexao.prepareStatement("create table IF NOT EXISTS Abas("
                + "cod integer not null, nome varchar(10) not null, "
                + "primary key (cod))");
        ret = pstmt.executeUpdate();
        this.fecharSqlPreparado();
        return ret;
    }

}
