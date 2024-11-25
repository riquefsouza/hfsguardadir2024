package hfsguardadir.objetosdao;

import hfsguardadir.comum.IProgressoLog;
import hfsguardadir.comum.Progresso;
import hfsguardadir.comum.Rotinas;
import hfsguardadir.objetos.Extensao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

public class ExtensaoDAO {

    private static ExtensaoDAO instancia;

    private Connection conexao;

    private PreparedStatement pstmt;

    private ExtensaoDAO() {
        super();
    }

    public static ExtensaoDAO getInstancia() {
        if (instancia == null) {
            instancia = new ExtensaoDAO();
        }
        return instancia;
    }
    
    private void fecharSqlPreparado() throws SQLException {
        if (pstmt != null) {
            pstmt.close();
        }
    }

    private Extensao novoObjeto(ResultSet res) throws SQLException {
        Extensao ret = new Extensao();
        ret.setCodigo(res.getInt(1));
        ret.setNome(res.getString(2));
        ret.setBmp16(res.getBytes(3));
        ret.setBmp32(res.getBytes(4));
        if (ret.getBmp16()!=null) {
            ret.setGif16(Rotinas.BmpParaImagem(ret.getBmp16(), 
                    Rotinas.EXTENSAO_GIF));
        }
        if (ret.getBmp32()!=null) {
            ret.setGif32(Rotinas.BmpParaImagem(ret.getBmp32(), 
                    Rotinas.EXTENSAO_GIF));
        }
        return ret;
    }
    
    public int consultarTotal() throws SQLException {
        int total = 0;
        conexao = Rotinas.getConexao();
        pstmt = conexao.prepareStatement("select count(*) from Extensoes");
        ResultSet res = pstmt.executeQuery();

        if (res.next()) {
            total = res.getInt(1);
        }
        this.fecharSqlPreparado();

        return total;
    }
    
    public ArrayList<Extensao> consultarTudo(IProgressoLog progressoLog)
            throws SQLException {
        Extensao obj;
        ArrayList<Extensao> lista = new ArrayList<>();
        Progresso pb;
        int i = 0;
        int total = this.consultarTotal();

        conexao = Rotinas.getConexao();
        pstmt = conexao.prepareStatement(
                "select cod, nome, bmp16, bmp32 from Extensoes");
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
    
    public int incluir(Extensao obj) throws SQLException {
        int ret;
        conexao = Rotinas.getConexao();
        pstmt = conexao.prepareStatement(
            "insert into Extensoes(cod, nome, bmp16, bmp32) values(?,?,?,?)");
        pstmt.setInt(1, obj.getCodigo());
        pstmt.setString(2, obj.getNome());
        pstmt.setBytes(3, obj.getBmp16());
        pstmt.setBytes(4, obj.getBmp32());
        ret = pstmt.executeUpdate();
        this.fecharSqlPreparado();
        return ret;
    }
    
    public int excluir(int codigo) throws SQLException {
        int ret;
        conexao = Rotinas.getConexao();
        pstmt = conexao.prepareStatement("delete from Extensoes where cod=?");
        pstmt.setInt(1, codigo);
        ret = pstmt.executeUpdate();
        this.fecharSqlPreparado();
        return ret;
    }

    public int excluirTudo() throws SQLException {
        int ret;
        conexao = Rotinas.getConexao();
        pstmt = conexao.prepareStatement("delete from Extensoes");
        ret = pstmt.executeUpdate();
        this.fecharSqlPreparado();
        return ret;
    }
    

    public int criarTabela() throws SQLException {
        int ret;
        conexao = Rotinas.getConexao();
        pstmt = conexao.prepareStatement(
                "create table IF NOT EXISTS Extensoes("
                + "cod integer not null,"
                + "nome varchar(20) not null,"
                + "bmp16 BLOB COLLATE NOCASE null,"
                + "bmp32 BLOB COLLATE NOCASE null,"
                + "primary key (cod))");
        ret = pstmt.executeUpdate();
        this.fecharSqlPreparado();
        return ret;
    }

}
