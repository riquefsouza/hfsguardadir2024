package hfsguardadir.objetosdao;

import hfsguardadir.comum.IProgressoLog;
import hfsguardadir.comum.Progresso;
import hfsguardadir.comum.Rotinas;
import hfsguardadir.objetos.Aba;
import hfsguardadir.objetos.Diretorio;
import hfsguardadir.objetos.Tipo;
import hfsguardadir.objetosbo.DiretorioBO;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

public class DiretorioDAO {

    private static DiretorioDAO instancia;

    private Connection conexao;

    private PreparedStatement pstmt;

    private DiretorioDAO() {
        super();
    }

    public static DiretorioDAO getInstancia() {
        if (instancia == null) {
            instancia = new DiretorioDAO();
        }
        return instancia;
    }

    private void fecharSqlPreparado() throws SQLException {
        if (pstmt != null) {
            pstmt.close();
        }
    }

    private Diretorio novoObjeto(ResultSet res)
            throws SQLException {
        Diretorio ret = new Diretorio();
        Aba aba = new Aba();
        Tipo tipo;

        aba.setCodigo(res.getInt(1));
        ret.setCodigo(res.getInt(2));
        ret.setOrdem(res.getInt(3));
        if (res.getObject(4) != null) {
            ret.setCodDirPai(res.getInt(4));
        } else {
            ret.setCodDirPai(-1);
        }

        ret.setNome(res.getString(5));
        ret.setTamanho(res.getLong(6));
        tipo = new Tipo(res.getString(7).charAt(0), "");
        ret.setTipo(tipo);
        ret.setModificado(Rotinas.StringToDate(res.getString(8)));
        ret.setAtributos(res.getString(9));
        ret.setCaminho(res.getString(10));
        aba.setNome(res.getString(11));
        ret.setAba(aba);
        ret.setNomePai(Rotinas.testaNull(res.getString(12)));
        ret.setCaminhoPai(Rotinas.testaNull(res.getString(13)));
        ret.setTamanhoFormatado(
                DiretorioBO.getInstancia().MontaTamanho(ret.getTamanho()));
        if (tipo.getCodigo() == 'D') {
            tipo.setNome(Rotinas.getRecurso("TipoLista.diretorio"));
        } else {
            tipo.setNome(Rotinas.getRecurso("TipoLista.arquivo"));
        }
        ret.setModificadoFormatado(Rotinas.formataDate(
                Rotinas.FORMATO_DATAHORA, ret.getModificado()));

        return ret;
    }

    public int consultarTotal(String sSQL, 
            String sCondicaoTotal) throws SQLException {
        String sTabela;
        
        if (Rotinas.ContainsStr(sSQL, "consultadirpai"))
            sTabela = "consultadirpai";
        else if (Rotinas.ContainsStr(sSQL, "consultadirfilho"))
            sTabela = "consultadirfilho";
        else if (Rotinas.ContainsStr(sSQL, "consultaarquivo"))
            sTabela = "consultaarquivo";
        else
            sTabela = "Diretorios";
        
        sSQL = "select count(*) from " + sTabela;
        if (sCondicaoTotal.trim().length() > 0){
            sSQL += " " + sCondicaoTotal;
        }
        int total = 0;
        conexao = Rotinas.getConexao();
        pstmt = conexao.prepareStatement(sSQL);
        ResultSet res = pstmt.executeQuery();

        if (res.next()) {
            total = res.getInt(1);
        }
        this.fecharSqlPreparado();

        return total;
    }

    public ArrayList<Diretorio> consultarTudo(String sSQL, 
            String sCondicaoTotal, IProgressoLog progressoLog) 
            throws SQLException {
        Diretorio obj;
        ArrayList<Diretorio> lista = new ArrayList<>();
        Progresso pb;
        int i = 0;
        int total = this.consultarTotal(sSQL, sCondicaoTotal);

        conexao = Rotinas.getConexao();
        pstmt = conexao.prepareStatement(sSQL);
        ResultSet res = pstmt.executeQuery();

        if (total > 0) {
            pb = new Progresso();
            pb.setMinimo(0);
            pb.setMaximo(total - 1);
            pb.setPosicao(0);
            pb.setPasso(1);

            while (res.next()) {
                obj = novoObjeto(res);

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

    private void atribuirCampos(PreparedStatement pstmt, Diretorio obj)
            throws SQLException {
        pstmt.setInt(1, obj.getAba().getCodigo());
        pstmt.setInt(2, obj.getCodigo());
        pstmt.setInt(3, obj.getOrdem());
        pstmt.setInt(4, obj.getCodDirPai());
        pstmt.setString(5, obj.getNome());
        pstmt.setLong(6, obj.getTamanho());
        pstmt.setString(7, Character.toString(obj.getTipo().getCodigo()));
        pstmt.setString(8, Rotinas.formataDate(
                Rotinas.FORMATO_DATAHORA, obj.getModificado()));
        pstmt.setString(9, obj.getAtributos());
        pstmt.setString(10, obj.getCaminho());
    }

    public int incluir(Diretorio obj)
            throws SQLException {
        int ret;
        conexao = Rotinas.getConexao();
        pstmt = conexao.prepareStatement(
                "insert into Diretorios(aba, cod, ordem, coddirpai, nome, tam,"
                + " tipo, modificado, atributos, caminho)"
                + " values (?,?,?,?,?,?,?,?,?,?)");
        atribuirCampos(pstmt, obj);
        ret = pstmt.executeUpdate();
        this.fecharSqlPreparado();
        return ret;
    }

    public int excluir(Aba aba, String sCaminho) throws SQLException {
        int ret;
        conexao = Rotinas.getConexao();
        pstmt = conexao.prepareStatement(
                "delete from Diretorios where caminho like ? and aba=?");
        pstmt.setString(1, sCaminho + "%");
        pstmt.setInt(2, aba.getCodigo());
        ret = pstmt.executeUpdate();
        this.fecharSqlPreparado();
        return ret;
    }

    public int criarTabela() throws SQLException {
        String sSQL;
        int ret;

        sSQL = "create table if NOT EXISTS Diretorios("
                + "aba int not null,"
                + "cod int not null,"
                + "ordem int not null,"
                + "nome varchar(255) not null,"
                + "tam numeric not null,"
                + "tipo char(1) not null,"
                + "modificado date not null,"
                + "atributos varchar(20) not null,"
                + "coddirpai int not null,"
                + "caminho varchar(255) not null,"
                + "primary key (aba, cod, ordem))";

        conexao = Rotinas.getConexao();
        pstmt = conexao.prepareStatement(sSQL);
        ret = pstmt.executeUpdate();
        this.fecharSqlPreparado();
        return ret;
    }
    
}
