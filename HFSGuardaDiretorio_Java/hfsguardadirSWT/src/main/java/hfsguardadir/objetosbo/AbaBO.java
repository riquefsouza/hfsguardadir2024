package hfsguardadir.objetosbo;

import hfsguardadir.comum.IProgressoLog;
import hfsguardadir.comum.Rotinas;
import hfsguardadir.objetos.Aba;
import hfsguardadir.objetosdao.AbaDAO;
import java.sql.SQLException;
import java.util.ArrayList;

public class AbaBO {

    private static AbaBO instancia;

    private AbaBO() {
        super();
    }

    public static AbaBO getInstancia() {
        if (instancia == null) {
            instancia = new AbaBO();
        }
        return instancia;
    }

    public ArrayList<Aba> carregarAba(IProgressoLog progressoLog)
            throws SQLException {
        return AbaDAO.getInstancia().consultarTudo(progressoLog);
    }

    public int retMaxCodAba(ArrayList<Aba> listaLocal) {
        int nMaior = 0;
        for (Aba aba : listaLocal) {
            if (aba.getCodigo() > nMaior) {
                nMaior = aba.getCodigo();
            }
        }
        return nMaior + 1;
    }

    public String abaToSQL(Aba aba) {
        return "insert into Abas(cod, nome) values(" + aba.getCodigo() + ","
                + Rotinas.QuotedStr(aba.getNome()) + ")";
    }

    public boolean incluirAba(Aba aba) throws SQLException {
        return (AbaDAO.getInstancia().incluir(aba) > 0);
    }

    public boolean alterarAba(Aba aba) throws SQLException {
        return (AbaDAO.getInstancia().alterar(aba) > 0);
    }

    public boolean excluirAba(Aba aba) throws SQLException {
        return (AbaDAO.getInstancia().excluir(aba.getCodigo()) > 0);
    }

    public boolean criarTabelaAbas() throws SQLException {
        return (AbaDAO.getInstancia().criarTabela() > 0);
    }

    public Aba pegaAbaPorOrdem(ArrayList<Aba> lista, int ordem) {
        for (Aba aba : lista) {
            if (aba.getOrdem() == ordem) {
                return aba;
            }
        }
        return null;
    }

    public Aba getElemento(ArrayList<Aba> lista, int codigo) {
        for (Aba elemento : lista) {
            if (elemento.getCodigo() == codigo) {
                return elemento;
            }
        }
        return null;
    }

    public Aba pegaAbaPorNome(ArrayList<Aba> lista, String nome) {
        for (Aba aba : lista) {
            if (aba.getNome().equals(nome)) {
                return aba;
            }
        }
        return null;
    }
    
}
