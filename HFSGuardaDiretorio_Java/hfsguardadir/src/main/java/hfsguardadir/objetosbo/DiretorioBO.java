package hfsguardadir.objetosbo;

import hfsguardadir.comum.DiretorioXML;
import hfsguardadir.comum.IProgressoLog;
import hfsguardadir.comum.Progresso;
import hfsguardadir.comum.Rotinas;
import hfsguardadir.comum.StringList;
import hfsguardadir.comum.TipoExportar;
import static hfsguardadir.comum.TipoExportar.teCSV;
import static hfsguardadir.comum.TipoExportar.teHTML;
import static hfsguardadir.comum.TipoExportar.teSQL;
import static hfsguardadir.comum.TipoExportar.teTXT;
import static hfsguardadir.comum.TipoExportar.teXML;
import hfsguardadir.objetos.Aba;
import hfsguardadir.objetos.Arquivo;
import hfsguardadir.objetos.Diretorio;
import hfsguardadir.objetos.DiretorioOrdem;
import hfsguardadir.objetos.Tipo;
import hfsguardadir.objetosdao.DiretorioDAO;
import java.io.File;
import java.io.IOException;
import java.math.BigDecimal;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Date;

public class DiretorioBO {

    private static DiretorioBO instancia;

    public static final String SQL_CONSULTA_ARQUIVO = "select aba, cod, "
            + "ordem, coddirpai, nome, tam, tipo, modificado, atributos, "
            + "caminho, nomeaba, nomepai, caminhopai from consultaarquivo";

    private DiretorioBO() {
        super();
    }

    public static DiretorioBO getInstancia() {
        if (instancia == null) {
            instancia = new DiretorioBO();
        }
        return instancia;
    }

    public ArrayList<Diretorio> carregarDiretorio(String sSQL, 
            IProgressoLog progressoLog) throws SQLException {
        return DiretorioDAO.getInstancia().consultarTudo(sSQL, "", 
                progressoLog);
    }
    
    public ArrayList<Diretorio> carregarDiretorio(String sSQL, 
            String sCondicaoTotal, IProgressoLog progressoLog) 
            throws SQLException {
        return DiretorioDAO.getInstancia().consultarTudo(sSQL, 
                sCondicaoTotal, progressoLog);
    }

    public String removerDrive(String sDiretorio) {
        File[] drives = File.listRoots();
        int i = 0;
        boolean bAchou = false;
        String sArq = Rotinas.testaNull(sDiretorio);

        if (sArq.length() > 0) {
            for (i = 0; i < drives.length; i++) {
                if (sArq.toUpperCase().contains(
                        drives[i].getPath().toUpperCase())) {
                    bAchou = true;
                    break;
                }
            }
        }
        sArq = Rotinas.trocaSeparador(sArq);
        if (bAchou) {
            return sArq.substring(drives[i].getPath().length());
        } else {
            return sArq;
        }
    }

    private String arquivoAtributos(File arquivo) {
        String sAtributos = "";

        if (arquivo!=null){        
            if (!arquivo.canWrite()) {
                sAtributos += "[ROL]";
            }
            if (arquivo.isHidden()) {
                sAtributos += "[HID]";
            }
            if (arquivo.isDirectory()) {
                sAtributos += "[DIR]";
            }
            if (arquivo.isFile()) {
                sAtributos += "[ARQ]";
            }	        
        }        
        return sAtributos;
    }

    private int retCodDirPai(int nAba, String sDiretorio,
            ArrayList<Diretorio> listaLocal) {
        for (Diretorio diretorio : listaLocal) {
            if (diretorio.getAba().getCodigo() == nAba) {
                if (diretorio.getCaminho().equals(sDiretorio)) {
                    return diretorio.getOrdem();
                }
            }
        }
        return 0;
    }

    public String MontaTamanhoBig(BigDecimal nTam) {
        BigDecimal nUmKilo, nUmMega, nUmGiga, nUmTera, nUmPeta;

        nUmKilo = new BigDecimal(1024);
        nUmMega = nUmKilo.multiply(nUmKilo);
        nUmGiga = nUmMega.multiply(nUmKilo);
        nUmTera = nUmGiga.multiply(nUmKilo);
        nUmPeta = nUmTera.multiply(nUmKilo);

        if (nTam.compareTo(nUmKilo) == -1) {
            return Rotinas.FormatDouble("#,##0.00", nTam.doubleValue()) + " Byte(s)";
        } else if (nTam.compareTo(nUmKilo) == 1 && nTam.compareTo(nUmMega) == -1) {
            nTam = nTam.divide(nUmKilo);
            return Rotinas.FormatDouble("#,##0.00", nTam.doubleValue()) + " KByte(s)";
        } else if (nTam.compareTo(nUmMega) == 1 && nTam.compareTo(nUmGiga) == -1) {
            nTam = nTam.divide(nUmMega);
            return Rotinas.FormatDouble("#,##0.00", nTam.doubleValue()) + " MByte(s)";
        } else if (nTam.compareTo(nUmGiga) == 1 && nTam.compareTo(nUmTera) == -1) {
            nTam = nTam.divide(nUmGiga);
            return Rotinas.FormatDouble("#,##0.00", nTam.doubleValue()) + " GByte(s)";
        } else if (nTam.compareTo(nUmTera) == 1 && nTam.compareTo(nUmPeta) == -1) {
            nTam = nTam.divide(nUmTera);
            return Rotinas.FormatDouble("#,##0.00", nTam.doubleValue()) + " TByte(s)";
        } else {
            nTam = nTam.divide(nUmPeta);
            return Rotinas.FormatDouble("#,##0.00", nTam.doubleValue()) + " PByte(s)";
        }
    }

    public String MontaTamanho(long nTam) {
        if (nTam > 0) {
            return MontaTamanhoBig(new BigDecimal(nTam));
        } else {
            return "";
        }
    }

    public Diretorio atribuiDiretorio(int nAba, int nCodDirRaiz,
            String sNomeDirRaiz, String sDiretorio, boolean bDiretorio,
            ArrayList<Diretorio> listaLocal, Arquivo arquivo,
            DiretorioOrdem dirOrdem) {
        int nOrdem = dirOrdem.getOrdem();
        Diretorio diretorio;
        String sCaminho, sDir;
		File fCaminho = null;

        sCaminho = removerDrive(sDiretorio);
		if (sDiretorio.length() > 0){
			fCaminho = new File(sDiretorio);
		}

        if ((sCaminho.length() > 0) && (sNomeDirRaiz.length() > 0)) {
            if (Rotinas.StartsStr(sNomeDirRaiz, sCaminho)) {
                sCaminho = Rotinas.SubString(sCaminho, sNomeDirRaiz.length()+2, 
                            sCaminho.length());
                sDir = Rotinas.SubString(sDiretorio, sNomeDirRaiz.length()+2, 
                                sDiretorio.length());
                fCaminho = new File(sDir);                
            } else {
                sCaminho = sNomeDirRaiz + Rotinas.BARRA_INVERTIDA + sCaminho;
                sDir = sNomeDirRaiz + Rotinas.BARRA_INVERTIDA + sDiretorio;
		fCaminho = new File(sDir);                
            }
        }

        diretorio = new Diretorio();
        Aba abaLocal = new Aba();
        Tipo tipoLocal = new Tipo();

        abaLocal.setCodigo(nAba);
        diretorio.setCodigo(nCodDirRaiz);
        diretorio.setOrdem(nOrdem);
        diretorio.setNome(arquivo.getNome());
        diretorio.setTamanho(arquivo.getTamanho());
        diretorio.setModificado(arquivo.getModificado());
        diretorio.setAtributos(arquivoAtributos(fCaminho));

        if (sDiretorio.isEmpty()) {
            diretorio.setCaminho(arquivo.getNome());
            diretorio.setCaminhoPai("");
        } else {
            diretorio.setCaminho(sCaminho);
            diretorio.setCaminhoPai(Rotinas.SubString(diretorio.getCaminho(), 1,
                    Rotinas.LastDelimiter(Rotinas.BARRA_INVERTIDA,
                            diretorio.getCaminho()) - 1));
        }

        if (bDiretorio) {
            tipoLocal.setCodigo('D');
            if (nOrdem == 1) {
                diretorio.setCodDirPai(0);
            } else {
                diretorio.setCodDirPai(retCodDirPai(abaLocal.getCodigo(),
                        diretorio.getCaminhoPai(), listaLocal));
            }
        } else {
            tipoLocal.setCodigo('A');
            diretorio.setCodDirPai(retCodDirPai(abaLocal.getCodigo(),
                    diretorio.getCaminhoPai(), listaLocal));
        }
        diretorio.setTipo(tipoLocal);
        abaLocal.setNome("");
        diretorio.setAba(abaLocal);
        diretorio.setNomePai("");
        diretorio.setTamanhoFormatado(MontaTamanho(diretorio.getTamanho()));
        if (diretorio.getTipo().getCodigo() == 'D') {
            diretorio.getTipo().setNome("Diretório");
        } else {
            diretorio.getTipo().setNome("Arquivo");
        }
        diretorio.setModificadoFormatado(Rotinas.formataDate(
                Rotinas.FORMATO_DATAHORA, diretorio.getModificado()));
        diretorio.setCaminhoOriginal(sDiretorio);

        nOrdem++;

        dirOrdem.setOrdem(nOrdem);

        return diretorio;
    }

    private Arquivo searchRecToArquivo(File SearchRec) {
        Arquivo arquivo = new Arquivo();
        arquivo.setNome(SearchRec.getName());
        arquivo.setTamanho(SearchRec.length());
        arquivo.setModificado(new Date(SearchRec.lastModified()));
        arquivo.setAtributos(arquivoAtributos(SearchRec));
        return arquivo;
    }

    public void atribuiListaDiretorio(int nAba, int nCodDirRaiz,
            String sNomeDirRaiz, String sDiretorio, ArrayList<Diretorio> listaLocal,
            File SearchRec, DiretorioOrdem dirOrdem, IProgressoLog progressoLog) {
        Diretorio diretorio;
        Progresso pb = new Progresso();

        if (Rotinas.FileExists(sDiretorio)) {
            diretorio = atribuiDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz,
                    sDiretorio, false, listaLocal, searchRecToArquivo(SearchRec),
                    dirOrdem);
            listaLocal.add(diretorio);
            
            if (progressoLog != null) {
                pb.setLog(sDiretorio);
                progressoLog.ProgressoLog(pb);
            }             
        } else if (Rotinas.DirectoryExists(sDiretorio)) {
            if ((!SearchRec.getName().equals(".")) && (!SearchRec.getName().equals(".."))) {
                diretorio = atribuiDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz,
                        sDiretorio, true, listaLocal, searchRecToArquivo(SearchRec),
                        dirOrdem);
                listaLocal.add(diretorio);

                if (progressoLog != null) {
                    pb.setLog(sDiretorio);
                    progressoLog.ProgressoLog(pb);
                }

                ImportarDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz, sDiretorio,
                        listaLocal, dirOrdem, progressoLog);
            }
        }

    }

    public void ImportarDiretorio(int nAba, int nCodDirRaiz,
            String sNomeDirRaiz, String sDiretorio, ArrayList<Diretorio> listaLocal,
            DiretorioOrdem dirOrdem, IProgressoLog progressoLog) {
        File SearchRec;
        String sCaminho, sSeparador;

        if (Rotinas.SubString(sDiretorio,
                sDiretorio.length(), 1).equals(File.separator)) {
            sSeparador = "";
        } else {
            sSeparador = File.separator;
        }

        sCaminho = sDiretorio + sSeparador;

        SearchRec = new File(sCaminho);
        if (SearchRec.exists()) {
            if (SearchRec.listFiles() != null) {
                for (File SearchRec2 : SearchRec.listFiles()) {
                    sCaminho = sDiretorio + sSeparador + SearchRec2.getName();
                    atribuiListaDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz,
                            sCaminho, listaLocal, SearchRec2, dirOrdem, 
                            progressoLog);
                }
            }
        }
    }

    public boolean verificaCodDir(int nAba, String sDiretorio,
            ArrayList<Diretorio> listaLocal) {

        if (sDiretorio.length() > 0) {
            for (Diretorio diretorio : listaLocal) {
                if (diretorio.getAba().getCodigo() == nAba) {
                    if (diretorio.getOrdem() == 1) {
                        if (diretorio.getCodDirPai() == 0) {
                            if (diretorio.getCaminho().equals(sDiretorio)) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    public int retMaxCodDir(int nAba, ArrayList<Diretorio> listaLocal) {
        int nMaior = -1;

        for (Diretorio diretorio : listaLocal) {
            if (diretorio.getAba().getCodigo() == nAba) {
                if (diretorio.getCodigo() > nMaior) {
                    nMaior = diretorio.getCodigo();
                }
            }
        }
        return nMaior + 1;
    }

    private String diretorioToSQL(Diretorio diretorio, boolean bInsert) {
        String sSQL = "";

        if (bInsert) {
            sSQL = "insert into Diretorios(aba, cod, ordem, coddirpai, nome, "
                    + "tam, tipo, modificado, atributos, caminho) values(";
        }

        sSQL += diretorio.getAba().getCodigo() + ",";
        sSQL += diretorio.getCodigo() + ",";
        sSQL += diretorio.getOrdem() + ",";
        sSQL += diretorio.getCodDirPai() + ",";
        sSQL += Rotinas.QuotedStr(diretorio.getNome()) + ",";
        sSQL += diretorio.getTamanho() + ",";
        sSQL += Rotinas.QuotedStr(diretorio.getTipo().getCodigo()) + ",";
        sSQL += Rotinas.QuotedStr(diretorio.getModificadoFormatado()) + ",";
        sSQL += Rotinas.QuotedStr(diretorio.getAtributos()) + ",";
        sSQL += Rotinas.QuotedStr(diretorio.getCaminho());

        if (bInsert) {
            sSQL += ")";
        }

        return sSQL;
    }

    public void salvarDiretorio(ArrayList<Diretorio> listaDiretorio,
            IProgressoLog progressoLog) throws SQLException {
        Diretorio diretorio;
        Progresso pb = new Progresso();
        pb.setMinimo(0);
        pb.setMaximo(listaDiretorio.size() - 1);
        pb.setPosicao(0);
        pb.setPasso(1);

        for (int i = 0; i < listaDiretorio.size(); i++) {
            diretorio = listaDiretorio.get(i);

            DiretorioDAO.getInstancia().incluir(diretorio);
            pb.setLog((i + 1) + " - Salvando Diretório: "
                    + diretorio.getCaminho());

            pb.setPosicao(i);

            if (progressoLog != null) {
                progressoLog.ProgressoLog(pb);
            }
        }
    }

    public boolean excluirDiretorio(Aba aba, String sCaminho)
            throws SQLException {
        return (DiretorioDAO.getInstancia().excluir(aba, sCaminho) > 0);
    }

    public void excluirListaDiretorio(ArrayList<Diretorio> listaDiretorio,
            Aba aba, String sCaminho) {
        Diretorio diretorio;

        for (int i = listaDiretorio.size() - 1; i >= 0; i--) {
            diretorio = listaDiretorio.get(i);

            if (diretorio.getAba().getCodigo() == aba.getCodigo()) {
                if (sCaminho.trim().length() > 0) {
                    if (Rotinas.StartsStr(sCaminho, diretorio.getCaminho())) {
                        listaDiretorio.remove(i);
                    }
                } else {
                    listaDiretorio.remove(i);
                }
            }
        }

    }

    private String diretorioToCSV(Diretorio diretorio) {
        String sCSV;

        sCSV = "\"";

        sCSV += diretorio.getAba().getNome() + "\";\"";
        sCSV += diretorio.getNome() + "\";\"";
        sCSV += diretorio.getTamanho() + "\";\"";
        sCSV += diretorio.getTamanhoFormatado() + "\";\"";
        sCSV += diretorio.getTipo().getNome() + "\";\"";
        sCSV += diretorio.getModificadoFormatado() + "\";\"";
        sCSV += diretorio.getAtributos() + "\";\"";
        sCSV += diretorio.getCaminho() + "\"";

        return sCSV;
    }

    private String diretorioToXML(Diretorio diretorio) {
        String sXML, sCR, sTAB, sTAB2;

        sTAB = "\t";
        sTAB2 = "\t\t";
        sCR = "\n";

        sXML = sTAB + "<arquivo>" + sCR;

        sXML += sTAB2 + "<aba>" + diretorio.getAba().getCodigo()
                + "</aba>" + sCR;
        sXML += sTAB2 + "<nomeAba>" + diretorio.getAba().getNome()
                + "</nomeAba>" + sCR;
        sXML += sTAB2 + "<codigo>" + diretorio.getCodigo()
                + "</codigo>" + sCR;
        sXML += sTAB2 + "<ordem>" + diretorio.getOrdem()
                + "</ordem>" + sCR;
        sXML += sTAB2 + "<nome>" + diretorio.getNome() + "</nome>" + sCR;
        sXML += sTAB2 + "<tamanho>" + diretorio.getTamanho()
                + "</tamanho>" + sCR;
        sXML += sTAB2 + "<tipo>" + diretorio.getTipo().getCodigo()
                + "</tipo>" + sCR;
        sXML += sTAB2 + "<modificado>" + diretorio.getModificadoFormatado()
                + "</modificado>" + sCR;
        sXML += sTAB2 + "<atributos>" + diretorio.getAtributos()
                + "</atributos>" + sCR;
        sXML += sTAB2 + "<codDirPai>" + diretorio.getCodDirPai()
                + "</codDirPai>" + sCR;
        sXML += sTAB2 + "<caminho>" + diretorio.getCaminho()
                + "</caminho>" + sCR;

        sXML += sTAB + "</arquivo>";

        return sXML;
    }

    private String diretorioToTXT(Diretorio diretorio) {
        String sTXT, sTAB;

        sTAB = "\t";
        sTXT = "";
        sTXT += diretorio.getAba().getNome() + sTAB;
        sTXT += diretorio.getNome() + sTAB;
        sTXT += diretorio.getTamanho() + sTAB;
        sTXT += diretorio.getTamanhoFormatado() + sTAB;
        sTXT += diretorio.getTipo().getNome() + sTAB;
        sTXT += diretorio.getModificadoFormatado() + sTAB;
        sTXT += diretorio.getAtributos() + sTAB;
        sTXT += diretorio.getCaminho();

        return sTXT;
    }

    private String diretorioToHTML(Diretorio diretorio) {
        String sHTML, sCR, sTAB, sTAB2;

        sTAB = "\t";
        sTAB2 = "\t\t";
        sCR = "\n";

        sHTML = sTAB + "<tr>" + sCR;

        sHTML += sTAB2 + "<td>" + diretorio.getAba().getNome() + "</td>" + sCR;
        sHTML += sTAB2 + "<td>" + diretorio.getNome() + "</td>" + sCR;
        sHTML += sTAB2 + "<td>" + diretorio.getTamanho() + "</td>" + sCR;
        sHTML += sTAB2 + "<td>" + Rotinas.StringReplaceAll(
                diretorio.getTamanhoFormatado(), " ", "&nbsp;") + "</td>" + sCR;
        sHTML += sTAB2 + "<td>" + diretorio.getTipo().getNome() + "</td>" + sCR;
        sHTML += sTAB2 + "<td>"
                + Rotinas.StringReplaceAll(diretorio.getModificadoFormatado(),
                        " ", "&nbsp;") + "</td>" + sCR;
        sHTML += sTAB2 + "<td>" + diretorio.getAtributos() + "</td>" + sCR;
        sHTML += sTAB2 + "<td>" + diretorio.getCaminho() + "</td>" + sCR;

        sHTML += sTAB + "</tr>";
        return sHTML;
    }

    public void exportarDiretorio(TipoExportar tipo, Aba aba,
            String sNomeArquivo, IProgressoLog progressoLog)
            throws SQLException, IOException {
        String sTexto = "", sCR, sTAB, sTAB2, sSQL, sCondicaoTotal;
        Aba abaLocal = new Aba();
        StringList listaLocal;
        ArrayList<Diretorio> listaDiretorio;

        sTAB = "\t";
        sTAB2 = "\t\t";
        sCR = "\n";

        sCondicaoTotal = " where aba=" + aba.getCodigo();
        sSQL = SQL_CONSULTA_ARQUIVO + sCondicaoTotal + " order by 1, 2, 3";
        listaDiretorio = carregarDiretorio(sSQL, sCondicaoTotal, progressoLog);

        listaLocal = new StringList();

        switch (tipo) {
            case teCSV: {
                sTexto = "\"Aba\";\"Nome\";\"TamanhoBytes\";\"Tamanho\";"
                        + "\"Tipo\";\"Modificado\";\"Atributos\";\"Caminho\"";
            }
            break;
            case teHTML: {
                sTexto = "<!DOCTYPE html>" + sCR;
                sTexto += "<html>" + sCR;
                sTexto += "<body>" + sCR;
                sTexto += "<table border=\"1\" cellpadding=\"5\" cellspacing=\"0\">"
                        + sCR;
                sTexto += sTAB + "<tr>" + sCR;
                sTexto += sTAB2 + "<th>Aba</th>" + sCR;
                sTexto += sTAB2 + "<th>Nome</th>" + sCR;
                sTexto += sTAB2 + "<th>Tamanho</th>" + sCR;
                sTexto += sTAB2 + "<th>Tamanho Formatado</th>" + sCR;
                sTexto += sTAB2 + "<th>Tipo</th>" + sCR;
                sTexto += sTAB2 + "<th>Modificado</th>" + sCR;
                sTexto += sTAB2 + "<th>Atributos</th>" + sCR;
                sTexto += sTAB2 + "<th>Caminho</th>" + sCR;
                sTexto += sTAB + "</tr>";
            }
            break;
            case teXML: {
                sTexto = "<diretorio>";
            }
            break;
            case teSQL: {
                abaLocal.setCodigo(listaDiretorio.get(0).getAba().getCodigo());
                abaLocal.setNome(listaDiretorio.get(0).getAba().getNome());
                sTexto = AbaBO.getInstancia().abaToSQL(abaLocal);
            }
            break;
            case teTXT: {
            }
        }
        listaLocal.add(sTexto);

        for (Diretorio diretorio : listaDiretorio) {
            if (diretorio.getAba().getCodigo() == aba.getCodigo()) {
                if (tipo == teTXT) {
                    sTexto = diretorioToTXT(diretorio);
                } else if (tipo == teCSV) {
                    sTexto = diretorioToCSV(diretorio);
                } else if (tipo == teHTML) {
                    sTexto = diretorioToHTML(diretorio);
                } else if (tipo == teXML) {
                    sTexto = diretorioToXML(diretorio);
                } else if (tipo == teSQL) {
                    sTexto = diretorioToSQL(diretorio, true) + ";";
                }

                listaLocal.add(sTexto);
            }
        }

        if (tipo == teHTML) {
            sTexto += sCR + "</table>" + sCR;
            sTexto += "</body>" + sCR;
            sTexto += "</html>" + sCR;
        } else if (tipo == teXML) {
            sTexto = "</diretorio>";
        }
        listaLocal.add(sTexto);

        listaLocal.SaveToFile(sNomeArquivo);

        listaDiretorio.clear();

    }

    public boolean criarTabelaDiretorios() throws SQLException {
        return (DiretorioDAO.getInstancia().criarTabela() > 0);
    }

    private int XMLParaDiretorio(String sTexto, int nArquivo, 
            DiretorioXML diretorioXML) {
        String sTagInicio = "", sValor = "", sTagFim = "";
        int resultado;                

        resultado = nArquivo;

        if (Rotinas.Pos(">", sTexto) > 0) {
            sTagInicio = Rotinas.SubString(sTexto, 1, Rotinas.Pos(">", sTexto));
        }
        if ((Rotinas.Pos(">", sTexto) > 0) && (Rotinas.Pos("</", sTexto) > 1)) {
            sValor = Rotinas.SubString(sTexto, Rotinas.Pos(">", sTexto) + 1,
                    Rotinas.Pos("</", sTexto) - Rotinas.Pos(">", sTexto) - 1);
        }
        if (Rotinas.LastDelimiter(">", sTexto) > 0) {
            sTagFim = Rotinas.SubString(sTexto,
                    Rotinas.LastDelimiter("<", sTexto),
                    Rotinas.LastDelimiter(">", sTexto));
        }

        if ((nArquivo == 1) && (!sTagInicio.equals("<arquivo>"))) {
            resultado = -1;
        }
        if ((nArquivo == 2) && (!sTagInicio.equals("<aba>"))
                && (!sTagFim.equals("</aba>"))) {
            // diretorio.aba.codigo = StrToInt(sValor);
            resultado = -1;
        }
        if ((nArquivo == 3) && (!sTagInicio.equals("<nomeAba>"))
                && (!sTagFim.equals("</nomeAba>"))) {
            // diretorio.aba.nome = sValor;
            resultado = -1;
        }
        if ((nArquivo == 4) && (sTagInicio.equals("<codigo>"))
                && (sTagFim.equals("</codigo>"))) {
            diretorioXML.getDiretorio().setCodigo(Integer.valueOf(sValor));
        }
        if ((nArquivo == 5) && (sTagInicio.equals("<ordem>"))
                && (sTagFim.equals("</ordem>"))) {
            diretorioXML.getDiretorio().setOrdem(Integer.valueOf(sValor));
        }
        if ((nArquivo == 6) && (sTagInicio.equals("<nome>"))
                && (sTagFim.equals("</nome>"))) {
            diretorioXML.getDiretorio().setNome(sValor);
        }
        if ((nArquivo == 7) && (sTagInicio.equals("<tamanho>"))
                && (sTagFim.equals("</tamanho>"))) {
            diretorioXML.getDiretorio().setTamanho(Long.valueOf(sValor));
        }
        if ((nArquivo == 8) && (sTagInicio.equals("<tipo>"))
                && (sTagFim.equals("</tipo>"))) {
            diretorioXML.getDiretorio().getTipo().setCodigo(sValor.charAt(0));
        }
        if ((nArquivo == 9) && (sTagInicio.equals("<modificado>"))
                && (sTagFim.equals("</modificado>"))) {
            diretorioXML.getDiretorio().setModificado(
                    Rotinas.StringToDate(sValor));
        }
        if ((nArquivo == 10) && (sTagInicio.equals("<atributos>"))
                && (sTagFim.equals("</atributos>"))) {
            diretorioXML.getDiretorio().setAtributos(sValor);
        }
        if ((nArquivo == 11) && (sTagInicio.equals("<codDirPai>"))
                && (sTagFim.equals("</codDirPai>"))) {
            diretorioXML.getDiretorio().setCodDirPai(Integer.valueOf(sValor));
        }
        if ((nArquivo == 12) && (sTagInicio.equals("<caminho>"))
                && (sTagFim.equals("</caminho>"))) {
            diretorioXML.getDiretorio().setCaminho(sValor);
        }
        if ((nArquivo == 13) && (!sTagInicio.equals("</arquivo>"))) {
            resultado = -1;
        }
        if (sTagInicio.equals("</diretorio>")) {
            resultado = -3;
        }
        
        return resultado;
    }

    public int importarDiretorioViaXML(Aba aba, String sNomeArquivo,
            ArrayList<Diretorio> listaDirPai, 
            IProgressoLog progressoLog) throws IOException, SQLException {
        String sTexto;
        int nArquivo, resultado;
        StringList listaLocal;
        DiretorioXML diretorioXML;
        ArrayList<Diretorio> listaDiretorio;        

        resultado = 0;
        diretorioXML = new DiretorioXML();        
        listaDiretorio = new ArrayList<>();
        listaLocal = new StringList();
        listaLocal.LoadFromFile(sNomeArquivo);

        if (!listaLocal.get(0).equals("<diretorio>")) {
            resultado = -1;
        } else {
            nArquivo = 0;
            for (String sTexto1 : listaLocal) {
                sTexto = sTexto1.trim();
                
                nArquivo = XMLParaDiretorio(sTexto, nArquivo, diretorioXML);

                if (nArquivo == -1) {
                    resultado = -1;
                    break;
                } else if (nArquivo == 13) {
                    nArquivo = 1;
                    diretorioXML.getDiretorio().setAba(aba);
                    listaDiretorio.add(diretorioXML.getDiretorio());

                    if (verificaCodDir(aba.getCodigo(), 
                            diretorioXML.getDiretorio().getCaminho(),
                            listaDirPai)) {
                        resultado = -2;
                        break;
                    }
                    
                    diretorioXML.setDiretorio(new Diretorio());
                } else if (nArquivo == -3) {
                    resultado = nArquivo;
                } else {
                    nArquivo++;
                }
            }
        }

        salvarDiretorio(listaDiretorio, progressoLog);
        listaDiretorio.clear();

        return resultado;
    }

    public boolean carregarSubDiretorios(String sDiretorio,
            StringList listaLocal) {
        File SearchRec;
        String sCaminho, sSeparador;

        if (Rotinas.SubString(sDiretorio, sDiretorio.length(), 1).
                equals(File.separator)) {
            sSeparador = "";
        } else {
            sSeparador = File.separator;
        }

        sCaminho = sDiretorio + sSeparador;
        SearchRec = new File(sCaminho);
        if (SearchRec.exists()) {
            if (SearchRec.listFiles() != null) {
                for (File SearchRec2 : SearchRec.listFiles()) {
                    sCaminho = sDiretorio + sSeparador + SearchRec2.getName();

                    if (SearchRec2.isDirectory()) {
                        if (Rotinas.DirectoryExists(sCaminho)) {
                            if ((!SearchRec2.getName().equals("."))
                                    && (!SearchRec2.getName().equals(".."))) {
                                listaLocal.add(sCaminho);
                            }
                        }
                    }
                }
            }
        }

        return (listaLocal.size() > 0);
    }

    public boolean carregarArquivos(String sDiretorio, StringList listaLocal) {
        File SearchRec;
        String sCaminho, sSeparador;

        if (Rotinas.SubString(sDiretorio, sDiretorio.length(), 1).
                equals(File.separator)) {
            sSeparador = "";
        } else {
            sSeparador = File.separator;
        }

        sCaminho = sDiretorio + sSeparador;
        SearchRec = new File(sCaminho);
        if (SearchRec.exists()) {
            if (SearchRec.listFiles() != null) {
                for (File SearchRec2 : SearchRec.listFiles()) {
                    sCaminho = sDiretorio + sSeparador + SearchRec2.getName();

                    if (SearchRec2.isFile()) {
                        if (Rotinas.FileExists(sCaminho)) {
                            if ((!SearchRec.getName().equals("."))
                                    && (!SearchRec.getName().equals(".."))) {
                                listaLocal.add(sCaminho);
                            }
                        }
                    }
                }
            }
        }

        return (listaLocal.size() > 0);
    }

    public boolean carregarTodosArquivos(String sDiretorio,
            StringList listaLocal) {
        File SearchRec;
        String sCaminho, sSeparador;

        if (Rotinas.SubString(sDiretorio, sDiretorio.length(), 1).
                equals(File.separator)) {
            sSeparador = "";
        } else {
            sSeparador = File.separator;
        }

        sCaminho = sDiretorio + sSeparador;
        SearchRec = new File(sCaminho);
        if (SearchRec.exists()) {
            sCaminho = sDiretorio + sSeparador + SearchRec.getName();

            if (Rotinas.FileExists(sCaminho)) {
                listaLocal.add(sCaminho);
            } else if (Rotinas.DirectoryExists(sCaminho)) {
                if ((!SearchRec.getName().equals("."))
                        && (!SearchRec.getName().equals(".."))) {
                    carregarTodosArquivos(sCaminho, listaLocal);
                }
            }

            if (SearchRec.listFiles() != null) {
                for (File SearchRec2 : SearchRec.listFiles()) {
                    sCaminho = sDiretorio + sSeparador + SearchRec2.getName();

                    if (Rotinas.FileExists(sCaminho)) {
                        listaLocal.add(sCaminho);
                    } else if (Rotinas.DirectoryExists(sCaminho)) {
                        if ((!SearchRec2.getName().equals("."))
                                && (!SearchRec2.getName().equals(".."))) {
                            carregarTodosArquivos(sCaminho, listaLocal);
                        }
                    }
                }
            }
        }
        return (listaLocal.size() > 0);
    }
    
    public ArrayList<Diretorio> itensFilhos(ArrayList<Diretorio> lista_pai,
            int aba, int codDirPai, int codigo) {
        ArrayList<Diretorio> lista = new ArrayList<>();

        for (Diretorio diretorio : lista_pai) {
            if (diretorio.getAba().getCodigo() == aba) {
                if (diretorio.getCodDirPai() == codDirPai) {
                    if (diretorio.getCodigo() == codigo) {
                        lista.add(diretorio);
                    }
                }
            }
        }
        return lista;
    }
        
}
