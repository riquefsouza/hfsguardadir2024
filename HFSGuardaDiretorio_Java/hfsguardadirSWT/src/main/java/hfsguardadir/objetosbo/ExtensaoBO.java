package hfsguardadir.objetosbo;

import hfsguardadir.comum.IProgressoLog;
import hfsguardadir.comum.Progresso;
import hfsguardadir.comum.Rotinas;
import hfsguardadir.comum.StringList;
import hfsguardadir.comum.TipoExportarExtensao;
import static hfsguardadir.comum.TipoExportarExtensao.teBMP;
import static hfsguardadir.comum.TipoExportarExtensao.teGIF;
import static hfsguardadir.comum.TipoExportarExtensao.teICO;
import static hfsguardadir.comum.TipoExportarExtensao.teJPG;
import static hfsguardadir.comum.TipoExportarExtensao.tePNG;
import static hfsguardadir.comum.TipoExportarExtensao.teTIF;
import hfsguardadir.objetos.Diretorio;
import hfsguardadir.objetos.Extensao;
import hfsguardadir.objetosdao.ExtensaoDAO;
import java.io.IOException;
import java.sql.SQLException;
import java.util.ArrayList;

public class ExtensaoBO {

    private static ExtensaoBO instancia;
    
    private byte[] diretorioGIF;
    private byte[] arquivoGIF;

    private ExtensaoBO() {
        super();
        diretorioGIF = Rotinas.getImagemByteArray("diretorio.gif");
        arquivoGIF = Rotinas.getImagemByteArray("arquivo.gif");
    }

    public static ExtensaoBO getInstancia() {
        if (instancia == null) {
            instancia = new ExtensaoBO();
        }
        return instancia;
    }

    public ArrayList<Extensao> carregarExtensao(IProgressoLog progressoLog) 
            throws SQLException {
        return ExtensaoDAO.getInstancia().consultarTudo(progressoLog);
    }

    public boolean existeExtensao(String sExtensao,
            ArrayList<Extensao> listaLocal) {
        if (sExtensao.trim().length() > 0) {
            for (Extensao extensao : listaLocal) {
                if (extensao.getNome().trim().toLowerCase().equals(
                        sExtensao.trim().toLowerCase())) {
                    return true;
                }
            }
        }
        return false;
    }

    public int retMaxCodExtensao(ArrayList<Extensao> listaLocal) {
        int nMaior = 0;
        for (Extensao extensao : listaLocal) {
            if (extensao.getCodigo() > nMaior) {
                nMaior = extensao.getCodigo();
            }
        }
        return nMaior + 1;
    }

    public boolean incluirExtensao(Extensao extensao) throws SQLException {
        return (ExtensaoDAO.getInstancia().incluir(extensao) > 0);
    }

    public boolean SalvarExtensao(ArrayList<Extensao> listaExtensao,
            String sNomeDiretorio, String sCaminhoOriginal, StringList log)
            throws SQLException {
        String sExtensao;
        Extensao extensao;

        if (Rotinas.LastDelimiter(".", sNomeDiretorio) > 0) {
            sExtensao = Rotinas.SubString(sNomeDiretorio,
                    Rotinas.LastDelimiter(".", sNomeDiretorio) + 1,
                    sNomeDiretorio.length());
            if (!existeExtensao(sExtensao, listaExtensao)) {
                extensao = new Extensao();
                extensao.setCodigo(retMaxCodExtensao(listaExtensao));
                extensao.setNome(sExtensao.toLowerCase());
                extensao.setOrdem(listaExtensao.size()+1);
                extensao.setBmp16(Rotinas.ArquivoParaBmp(sCaminhoOriginal, 16));
                extensao.setBmp32(Rotinas.ArquivoParaBmp(sCaminhoOriginal, 32));
                if (extensao.getBmp16()!=null) {
                    extensao.setGif16(Rotinas.BmpParaImagem(extensao.getBmp16(), 
                            Rotinas.EXTENSAO_GIF));
                }
                if (extensao.getBmp32()!=null) {
                    extensao.setGif32(Rotinas.BmpParaImagem(extensao.getBmp32(), 
                            Rotinas.EXTENSAO_GIF));
                }
                incluirExtensao(extensao);                
                listaExtensao.add(extensao);
                log.add("Salvando Extensão: " + extensao.getNome());
                return true;
            }
        }
        return false;
    }

    public void salvarExtensoes(ArrayList<Diretorio> listaDiretorio,
            ArrayList<Extensao> listaExtensao, 
            IProgressoLog progressoLog) throws SQLException {
        StringList log = new StringList();
        Diretorio diretorio;
        Progresso pb = new Progresso();

        pb.setMinimo(0);
        pb.setMaximo(listaDiretorio.size() - 1);
        pb.setPosicao(0);
        pb.setPasso(1);

        for (int i = 0; i < listaDiretorio.size(); i++) {
            diretorio = listaDiretorio.get(i);

            if (diretorio.getTipo().getCodigo() == 'A') {
                SalvarExtensao(listaExtensao, diretorio.getNome(),
                        diretorio.getCaminhoOriginal(), log);
                if (log.size() > 0){
                    pb.setLog(log.get(0));
                    log.clear();
                }
            }

            pb.setPosicao(i);

            if (progressoLog != null) {
                progressoLog.ProgressoLog(pb);
            }
        }
    }

    public boolean excluirExtensao(ArrayList<Extensao> listaExtensao,
            int codigo) throws SQLException {
        Extensao extensao;

        if (ExtensaoDAO.getInstancia().excluir(codigo) > 0) {
            for (int i = 0; i < listaExtensao.size(); i++) {
                extensao = listaExtensao.get(i);
                if (extensao.getCodigo() == codigo) {
                    listaExtensao.remove(i);
                    break;
                }
            }
            return true;
        } else {
            return false;
        }
    }

    public boolean excluirTodasExtensoes(ArrayList<Extensao> listaExtensao)
            throws SQLException {
        if (ExtensaoDAO.getInstancia().excluirTudo() > 0) {
            listaExtensao.clear();
            return true;
        } else {
            return false;
        }
    }

    public boolean criarTabelaExtensoes() throws SQLException {
        return (ExtensaoDAO.getInstancia().criarTabela() > 0);
    }

    public int indiceExtensao(ArrayList<Extensao> lista,
            String nomeExtensao) {
        nomeExtensao = Rotinas.SubString(nomeExtensao,
                Rotinas.LastDelimiter(".", nomeExtensao) + 1,
                nomeExtensao.length());

        for (Extensao extensao : lista) {
            if (extensao.getNome().trim().toLowerCase().equals(
                    nomeExtensao.trim().toLowerCase())) {
                return (extensao.getOrdem() + 1);
            }
        }
        return -1;
    }

    public Extensao pegaExtensaoPorOrdem(ArrayList<Extensao> lista,
            int ordem) {
        for (Extensao extensao : lista) {
            if (extensao.getOrdem() == ordem) {
                return extensao;
            }
        }
        return null;
    }

    public Extensao pegaExtensaoPorCodigo(ArrayList<Extensao> lista,
            int codigo) {
        for (Extensao extensao : lista) {
            if (extensao.getCodigo() == codigo) {
                return extensao;
            }
        }
        return null;
    }

    public Extensao pegaExtensaoPorNome(ArrayList<Extensao> lista,
            String nome, String tipo) {
        Extensao ext = null;
        
        if (tipo.equals(Rotinas.getRecurso("TipoLista.diretorio"))){
            ext = new Extensao();
            ext.setGif16(diretorioGIF);
        } else {        
            if (lista != null && lista.size() > 0) {
                for (Extensao extensao : lista) {
                    if (extensao.getNome().toLowerCase().equals(
                            nome.toLowerCase())) {
                        return extensao;
                    }
                }
            }
            if (tipo.equals(Rotinas.getRecurso("TipoLista.arquivo"))){
                ext = new Extensao();
                ext.setGif16(arquivoGIF);
            }            
        }
        return ext;
    }
    
    public boolean ExportarExtensao(TipoExportarExtensao tipo,
            ArrayList<Extensao> listaExtensao) throws IOException {
        String sCaminho, sImg16, sImg32, sExtensao;
        
        if (listaExtensao.size() > 0) {
            sCaminho = Rotinas.getParams().getDiretorioSistema() + 
                    Rotinas.BARRA_INVERTIDA;

            if (tipo == teBMP) {
                sExtensao = "." + Rotinas.EXTENSAO_BMP;
            } else if (tipo == teICO) {
                sExtensao = "." + Rotinas.EXTENSAO_ICO;
            } else if (tipo == teGIF) {
                sExtensao = "." + Rotinas.EXTENSAO_GIF;
            } else if (tipo == teJPG) {
                sExtensao = "." + Rotinas.EXTENSAO_JPEG;
            } else if (tipo == tePNG) {
                sExtensao = "." + Rotinas.EXTENSAO_PNG;
            } else if (tipo == teTIF) {
                sExtensao = "." + Rotinas.EXTENSAO_TIFF;
            } else {
                sExtensao = ".img";
            }

            for (Extensao extensao : listaExtensao) {
                sImg16 = sCaminho + extensao.getNome() + "16" + sExtensao;
                if (Rotinas.FileExists(sImg16)) {
                    Rotinas.DeleteFile(sImg16);
                }

                sImg32 = sCaminho + extensao.getNome() + "32" + sExtensao;
                if (Rotinas.FileExists(sImg32)) {
                    Rotinas.DeleteFile(sImg32);
                }

                switch (tipo) {
                    case teBMP: {
                        Rotinas.SaveToFile(extensao.getBmp16(), sImg16);
                        Rotinas.SaveToFile(extensao.getBmp32(), sImg32);
                    }
                    break;
                    case teICO: {
                        if (extensao.getBmp16() != null) {
                            Rotinas.SaveToFile(
                                    Rotinas.BmpParaImagem(extensao.getBmp16(),
                                    Rotinas.EXTENSAO_ICO), sImg16);
                        }
                        if (extensao.getBmp32() != null) {
                            Rotinas.SaveToFile(
                                    Rotinas.BmpParaImagem(extensao.getBmp32(),
                                    Rotinas.EXTENSAO_ICO), sImg32);
                        }
                    }
                    break;
                    case teGIF: {
                        Rotinas.SaveToFile(extensao.getGif16(), sImg16);
                        Rotinas.SaveToFile(extensao.getGif32(), sImg32);
                    }
                    break;
                    case teJPG: {
                        if (extensao.getBmp16() != null) {
                            Rotinas.SaveToFile(
                                    Rotinas.BmpParaImagem(extensao.getBmp16(),
                                    Rotinas.EXTENSAO_JPEG), sImg16);
                        }
                        if (extensao.getBmp32() != null) {
                            Rotinas.SaveToFile(
                                    Rotinas.BmpParaImagem(extensao.getBmp32(),
                                    Rotinas.EXTENSAO_JPEG), sImg32);
                        }
                    }
                    break;
                    case tePNG: {
                        if (extensao.getBmp16() != null) {
                            Rotinas.SaveToFile(
                                    Rotinas.BmpParaImagem(extensao.getBmp16(),
                                    Rotinas.EXTENSAO_PNG), sImg16);
                        }
                        if (extensao.getBmp32() != null) {
                            Rotinas.SaveToFile(
                                    Rotinas.BmpParaImagem(extensao.getBmp32(),
                                    Rotinas.EXTENSAO_PNG), sImg32);
                        }
                    }
                    break;
                    case teTIF: {
                        if (extensao.getBmp16() != null) {
                            Rotinas.SaveToFile(
                                    Rotinas.BmpParaImagem(extensao.getBmp16(),
                                    Rotinas.EXTENSAO_TIFF), sImg16);
                        }
                        if (extensao.getBmp32() != null) {
                            Rotinas.SaveToFile(
                                    Rotinas.BmpParaImagem(extensao.getBmp32(),
                                    Rotinas.EXTENSAO_TIFF), sImg32);
                        }
                    }
                    break;
                    case teNUL: {
                    }
                }

            }
            return true;
        }
        return false;
    }

    public void ImportarExtensao(String caminho,
            ArrayList<Extensao> listaExtensao) throws SQLException, IOException {
        StringList listaArquivos, log;
        listaArquivos = new StringList();
        log = new StringList();
        
        if (DiretorioBO.getInstancia().carregarArquivos(caminho, listaArquivos)) {
            for (String sArquivo : listaArquivos) {
                SalvarExtensao(listaExtensao, Rotinas.ExtractFileName(sArquivo),
                        sArquivo, log);
            }
        }

    }

    public void ExtrairExtensao(String caminho,
            ArrayList<Extensao> listaExtensao) throws SQLException {
        StringList listaArquivos, log;
        listaArquivos = new StringList();
        log = new StringList();

        if (DiretorioBO.getInstancia().carregarTodosArquivos(caminho, listaArquivos)) {
            for (String sArquivo : listaArquivos) {
                SalvarExtensao(listaExtensao, Rotinas.ExtractFileName(sArquivo),
                        sArquivo, log);
            }
        }
    }

}
