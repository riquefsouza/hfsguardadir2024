package hfsguardadir.comum;

import java.awt.Dimension;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.Point;
import java.awt.Toolkit;
import java.awt.image.BufferedImage;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.text.DecimalFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Enumeration;
import java.util.List;
import java.util.Locale;
import java.util.Properties;
import java.util.ResourceBundle;
import java.util.logging.ConsoleHandler;
import java.util.logging.FileHandler;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.stream.Collectors;

import javax.imageio.ImageIO;
import javax.imageio.spi.IIORegistry;
import javax.swing.ImageIcon;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JWindow;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.geotoolkit.image.io.plugin.RawTiffImageReader;
import org.w3c.dom.Document;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import hfsguardadir.objetos.ConexaoParams;
import hfsguardadir.objetos.Parametro;
import hfsguardadir.objetos.PropriedadeSistema;
import net.sf.image4j.codec.bmp.BMPEncoder;
import net.sf.image4j.codec.ico.ICOEncoder;

public final class Rotinas {

    private static Connection db;

    public static final String HFSGUARDADIR = "HFSGuardaDir";

    public static final String BARRA_NORMAL = "\\";

    public static final String BARRA_INVERTIDA = "/";
    
    public static final String FORMATO_DATA = "dd/MM/yyyy";
    
    public static final String FORMATO_DATAHORA = "dd/MM/yyyy HH:mm:ss";
    
    public static final String FORMATO_DHARQUIVO = "yyy-MM-dd_HH_mm_ss";

    private static final Parametro params = new Parametro();

    private static String modeloName = "";

    private static String modeloDriver = "";

    private static String modeloURL = "";

    public static String EXTENSAO_BMP = "bmp";
    
    public static String EXTENSAO_ICO = "ico";
    
    public static String EXTENSAO_GIF = "gif";
    
    public static String EXTENSAO_JPEG = "jpg";
    
    public static String EXTENSAO_PNG = "png";
    
    public static String EXTENSAO_TIFF = "tif";

    public static void registrarProvedorTIFF() {
        IIORegistry registry = IIORegistry.getDefaultInstance();   
        registry.registerServiceProvider(new RawTiffImageReader.Spi());
    }

    public static int LastDelimiter(String subtexto, String texto) {
        return texto.lastIndexOf(subtexto) + 1;
    }

    public static int LastDelimiter(char subtexto, String texto) {
        return texto.lastIndexOf(subtexto) + 1;
    }

    public static int Pos(String subtexto, String texto) {
        return texto.indexOf(subtexto) + 1;
    }

    public static int Pos(char subtexto, String texto) {
        return texto.indexOf(subtexto) + 1;
    }
    
    public static boolean StartsStr(String subtexto, String texto) {
        return texto.startsWith(subtexto);
    }

    public static boolean ContainsStr(String texto, String subtexto) {
        return (Pos(subtexto, texto) > 0);
    }
    
    public static boolean EndsStr(String subtexto, String texto) {
        return (LastDelimiter(subtexto, texto) > 0);
    }

    public static String SubString(String texto, int inicio, int tamanho) {
        if ((inicio + tamanho - 1) > texto.length()) {
            tamanho = texto.length();
        } else {
            tamanho = inicio + tamanho - 1;
        }
        return texto.substring(inicio - 1, tamanho);
    }

    public static String StringReplaceAll(String texto, String velho, 
            String novo){
        return texto.replaceAll(velho, novo);
    }
    
    public static String QuotedStr(String texto){
        return "'" + texto + "'";
    }

    public static String QuotedStr(char texto){
        return "'" + texto + "'";
    }
    
    public static String ExtractFilePath(String sCaminho) {
        String retorno;

        File file = new File(sCaminho);
        retorno = file.getAbsolutePath();

        return retorno;
    }

    public static String ExtractFileName(String sCaminho) {
        String retorno;

        File file = new File(sCaminho);
        retorno = file.getName();

        return retorno;
    }

    public static boolean FileExists(String sNomeArquivo) {
        File file = new File(sNomeArquivo);
        if (file.exists()) {
            return file.isFile();
        } else
            return false;
    }
    
    public static boolean DirectoryExists(String sNomeArquivo) {
        File file = new File(sNomeArquivo);
        if (file.exists()) {
            return file.isDirectory();
        } else
            return false;
    }

    public static boolean DeleteFile(String sNomeArquivo) {
        File file = new File(sNomeArquivo);
        return file.delete();
    }

    public static void SaveToFile(byte[] imagem, String sNomeArquivo)
            throws FileNotFoundException, IOException {
        try (FileOutputStream fos = new FileOutputStream(sNomeArquivo)) {
            fos.write(imagem);
        }
    }

    public static byte[] LoadFromFile(String sNomeArquivo)
            throws FileNotFoundException, IOException {
        byte[] imagem = null;

        try (FileInputStream fis = new FileInputStream(sNomeArquivo)) {
            fis.read(imagem);
        }

        return imagem;
    }

    public static void iniciarLogArquivo(Logger logger) {
        logger.setLevel(Level.ALL);
        logger.setUseParentHandlers(false);
        ConsoleHandler ch = new ConsoleHandler();
        ch.setFormatter(new LogFormato());
        logger.addHandler(ch);
        if (params.getArquivoLog().trim().length() > 0) {
            try {
				// String pattern = "GuardaDir%g.log";
                // int limit = 1000000; // em bytes
                // int numLogFiles = 3;
                // FileHandler fh = new FileHandler(pattern, limit, numLogFiles,
                // true);
                FileHandler fh = new FileHandler(params.getArquivoLog(), true);
                fh.setFormatter(new LogFormato());
				// fh.setFormatter(new SimpleFormatter());
                // fh.setFormatter(new XMLFormatter());
                // fh.setFormatter(new HtmlFormatter());
                logger.addHandler(fh);
            } catch (IOException e) {
                logger.severe(e.getLocalizedMessage());
            }
        }
    }

    public static Parametro getParams() {
        return params;
    }

    public static String getRecurso(String chave) {
        Locale localidade = Locale.of(params.getLocalidadeLingua(), params
                .getLocalidadePais());
        return ResourceBundle.getBundle("recursos/hfsguardadiretorio",
                localidade).getString(chave);
    }

    public static ImageIcon getImagem(String arquivo) {
        String caminho = "/recursos/imagens/" + arquivo;
        return new ImageIcon(Rotinas.class.getResource(caminho));
    }

    public static InputStream getImagemStream(String arquivo) {
        String caminho = "/recursos/imagens/" + arquivo;
        return Rotinas.class.getResourceAsStream(caminho);
    }
    
    public static byte[] getImagemByteArray(String arquivo) {
        return inputStreamToByteArray(getImagemStream(arquivo));
    }

    private static byte[] inputStreamToByteArray(InputStream is) {
        int nTam;
        int tamanho = 1024;
        byte[] buffer = null;
        
        try {
            if (is instanceof ByteArrayInputStream) {
                tamanho = is.available();
                buffer = new byte[tamanho];
                is.read(buffer, 0, tamanho);
            } else {
                ByteArrayOutputStream bos = new ByteArrayOutputStream();
                buffer = new byte[tamanho];
                while ((nTam = is.read(buffer, 0, tamanho)) != -1) {
                    bos.write(buffer, 0, nTam);
                }
                buffer = bos.toByteArray();
            }
        } catch (IOException ex) {
            Logger.getLogger(Rotinas.class.getName()).log(
                    Level.SEVERE, null, ex);
        }
        return buffer;
    }
    
    public static char getMnemonico(String chave) {
        return (Rotinas.getRecurso(chave)).charAt(0);
    }

    public static String formataDate(String formato, java.util.Date dt) {
        String ds = "";
        if (dt != null) {
            SimpleDateFormat sdf = new SimpleDateFormat(formato);
            ds = sdf.format(dt);
        }
        return ds;
    }

    public static Date StringToDate(String sData) {
        Date data = null;
        SimpleDateFormat sdf;
        if (sData.trim().length() > 0) {
            try {
                if (sData.trim().length() == 10)
                    sdf = new SimpleDateFormat(FORMATO_DATA);
                else
                    sdf = new SimpleDateFormat(FORMATO_DATAHORA);
                    
                data = sdf.parse(sData);
            } catch (Exception ex) {
                System.err.println("Erro na rotina StringToDate: "
                        + ex.getMessage());
            }
        }
        return data;
    }

    public static String FormatLong(String formato, long valor) {
        DecimalFormat fmt = new DecimalFormat(formato);
        return fmt.format(valor);
    }

    public static String FormatDouble(String formato, double valor) {
        DecimalFormat fmt = new DecimalFormat(formato);
        return fmt.format(valor);
    }

    public static String testaNull(String res) {
        return (res == null ? "" : res.trim());
    }
 
    public static InputStream getTextoDentroJar(Object obj, String str) {
        return obj.getClass().getResourceAsStream(str);
    }

    public static void CentralizaDlg(JFrame frm1, JDialog dlg1) {
        Dimension dlgTam = dlg1.getPreferredSize();
        Dimension frmTam = frm1.getSize();
        Point loc = frm1.getLocation();
        dlg1.setLocation(((frmTam.width - dlgTam.width) / 2) + loc.x,
                ((frmTam.height - dlgTam.height) / 2)
                + (loc.y + (dlgTam.height / 4)));
    }

    public static void CentralizaDlg(JPanel pnl1, JDialog dlg1) {
        Dimension dlgTam = dlg1.getPreferredSize();
        Dimension pnlTam = pnl1.getPreferredSize();
        Point loc = pnl1.getLocationOnScreen();
        dlg1.setLocation(((pnlTam.width - dlgTam.width) / 2) + loc.x,
                ((pnlTam.height - dlgTam.height) / 2) + loc.y);
    }

    public static void CentralizaDlg(JDialog dlg1) {
        Dimension TamTela = Toolkit.getDefaultToolkit().getScreenSize();
        dlg1.setLocation((TamTela.width - dlg1.getPreferredSize().width) / 2,
                (TamTela.height - dlg1.getPreferredSize().height) / 2);
    }

    public static void CentralizaFrm(JFrame frm1) {
        Dimension TelaTam = Toolkit.getDefaultToolkit().getScreenSize();
        Dimension frameTam = frm1.getSize();
        if (frameTam.height > TelaTam.height) {
            frameTam.height = TelaTam.height;
        }
        if (frameTam.width > TelaTam.width) {
            frameTam.width = TelaTam.width;
        }
        frm1.setLocation((TelaTam.width - frameTam.width) / 2,
                (TelaTam.height - frameTam.height) / 2);
        frm1.setVisible(true);
    }

    public static void CentralizaPanel(JPanel pnl) {
        Dimension TamTela = Toolkit.getDefaultToolkit().getScreenSize();
        pnl.setLocation((TamTela.width - pnl.getPreferredSize().width) / 2,
                (TamTela.height - pnl.getPreferredSize().height) / 2);
    }

    public static void CentralizaWindow(JWindow janela) {
        Dimension TamTela = Toolkit.getDefaultToolkit().getScreenSize();
        janela.setLocation(
                (TamTela.width - janela.getPreferredSize().width) / 2,
                (TamTela.height - janela.getPreferredSize().height) / 2);
    }

    public static Connection getConexao() {
        return db;
    }

    public static void Conectar() throws ClassNotFoundException, SQLException {
        ConexaoParams cp = new ConexaoParams();
        cp.setDriver(params.getBanco().getDriver());
        cp.setUrl(params.getBanco().getUrl());
        cp.setLogin(params.getBanco().getLogin());
        cp.setSenha(params.getBanco().getSenha());
        db = Conectar(cp);
    }

    public static Connection Conectar(ConexaoParams cp)
            throws ClassNotFoundException, SQLException {
        Class.forName(cp.getDriver());
        return DriverManager.getConnection(cp.getUrl(), cp.getLogin(), cp
                .getSenha());
    }

    public static void Desconectar() throws SQLException {
        Desconectar(db);
    }

    public static void Desconectar(Connection con) throws SQLException {
        if (con != null) {
            con.close();
        }
    }

    public static PropriedadeSistema[] getPropriedadesSistema() {
        List<PropriedadeSistema> lista = new ArrayList<PropriedadeSistema>();
        Properties props = System.getProperties();
        PropriedadeSistema propSis;
        Enumeration<?> enum1 = props.propertyNames();
        for (; enum1.hasMoreElements();) {
            String propName = (String) enum1.nextElement();
            String propValue = (String) props.get(propName);
            propSis = new PropriedadeSistema(propName, propValue);
            lista.add(propSis);
        }
        //Collections.sort(lista);
        lista = lista.stream().sorted()
        		.collect(Collectors.toList());
        
        return (PropriedadeSistema[]) lista
                .toArray(new PropriedadeSistema[lista.size()]);
    }

    private static Document carregarXml(boolean lerArquivo, String arquivoXML,
            InputStream streamXML, boolean validarDTD) throws SAXException,
            IOException, ParserConfigurationException {
        DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        factory.setValidating(validarDTD);
        factory.setIgnoringComments(true);
        factory.setIgnoringElementContentWhitespace(true);
        Document doc;
        if (lerArquivo) {
            doc = factory.newDocumentBuilder().parse(new File(arquivoXML));
        } else {
            doc = factory.newDocumentBuilder().parse(streamXML);
        }
        return doc;
    }

    public static Document carregarXml(String arquivoXML, boolean validarDTD)
            throws SAXException, IOException, ParserConfigurationException {
        return carregarXml(true, arquivoXML, null, validarDTD);
    }
    
    public static void visitaNodesDOM(Node node, int level, boolean bModelo) {
        Node nodePai = node.getParentNode();
        if (nodePai != null) {
            switch (nodePai.getNodeName()) {
                case "localeLanguage":
                    params.setLocalidadeLingua(node.getNodeValue());
                    break;
                case "localeCountry":
                    params.setLocalidadePais(node.getNodeValue());
                    break;
                case "lookAndFeel":
                    params.setLookAndFeel(node.getNodeValue());
                    break;
                case "logFile":
                    params.setArquivoLog(node.getNodeValue());
                    break;
                case "databaseName":
                    params.getBanco().setNome(node.getNodeValue());
                    break;
                case "databaseDriver":
                    params.getBanco().setDriver(node.getNodeValue());
                    break;
                case "databaseURL":
                    params.getBanco().setUrl(node.getNodeValue());
                    break;
                case "databaseLogin":
                    params.getBanco().setLogin(node.getNodeValue());
                    break;
                case "databasePassword":
                    params.getBanco().setSenha(node.getNodeValue());
                    break;
                case "modelConnection":
                    bModelo = true;
                    break;
                case "modelName":
                    modeloName = node.getNodeValue();
                    break;
                case "modelDriver":
                    modeloDriver = node.getNodeValue();
                    break;
                case "modelURL":
                    modeloURL = node.getNodeValue();
                    break;
            }

            if (bModelo) {
                if (modeloName.trim().length() > 0
                        && modeloDriver.trim().length() > 0
                        && modeloURL.trim().length() > 0) {
                    ConexaoParams cp = new ConexaoParams();
                    cp.setNome(modeloName);
                    cp.setDriver(modeloDriver);
                    cp.setUrl(modeloURL);
                    params.setModelo(cp);

                    bModelo = false;
                    modeloName = "";
                    modeloDriver = "";
                    modeloURL = "";
                }
            }
        }

        NodeList list = node.getChildNodes();
        for (int i = 0; i < list.getLength(); i++) {
            Node childNode = list.item(i);
            visitaNodesDOM(childNode, level + 1, bModelo);
        }
    }
    
    public static boolean carregarParametros(String arquivo) 
            throws SAXException, IOException, ParserConfigurationException {
        File arq = new File(arquivo);
        if (arq.exists()) {
            Document doc = carregarXml(arquivo, false);
            visitaNodesDOM(doc, 0, false);
        } else {
            return false;            
        }
        return true;
    }

    public static String trocaSeparador(String texto) {
        String res = "";
        if (texto != null && texto.length() > 0) {
            char[] pedacos = texto.toCharArray();
            for (int i = 0; i < pedacos.length; i++) {
                if (pedacos[i] == BARRA_NORMAL.charAt(0)) {
                    pedacos[i] = BARRA_INVERTIDA.charAt(0);
                }
            }
            res = new String(pedacos);
        }
        return res;
    }
    
    public static String pathDaClasse(Class<?> klass) {
        String className = "/" + klass.getName().replace('.', '/') + ".class";
        URL u = klass.getResource(className);
        String s = u.toString();
        if (s.startsWith("jar:file:/")) {
			// Deve ser algo como
            // "jar:file:/C:/Program%20Files/Java/jre1.5.0_08/jre/lib/rt.jar!/java/lang/String.class"
            int pos = s.indexOf(".jar!/");
            if (pos != -1) {
                if (File.separator.equals("\\")) {
                    s = s.substring("jar:file:/".length(), pos
                            + ".jar".length());
                } else {
                    s = s
                            .substring("jar:file:".length(), pos
                                    + ".jar".length());
                }
                s = s.replaceAll("%20", " ");
            } else {
                s = "?";
            }
        } else if (s.startsWith("file:/")) {
            // Algo como "file:/C:/temp2/java/TestePathDaClasse.class"
            if (File.separator.equals("\\")) {
                s = s.substring("file:/".length());
            } else {
                s = s.substring("file:".length());
            }
            s = s.substring(0, s.lastIndexOf(className)).replaceAll("%20", " ");
        } else {
            s = "?";
        }
        return s;
    }
    
    public static byte[] BmpParaImagem(byte[] imagemBMP, String formato) {
        
        byte[] imagemSaida = null;
        try {
            InputStream in = new ByteArrayInputStream(imagemBMP);
            BufferedImage buffer = ImageIO.read(in);
            buffer.flush();
            
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            if (formato.equals(EXTENSAO_ICO))
                ICOEncoder.write(buffer, baos);
            else
                ImageIO.write(buffer, formato, baos);
            baos.flush();
            imagemSaida = baos.toByteArray();
            baos.close();
            in.close();
            
        } catch (IOException ex) {
            Logger.getLogger(Rotinas.class.getName()).log(
                    Level.SEVERE, null, ex);
        }
        return imagemSaida;
    }
    
    public static byte[] ArquivoParaBmp(String arquivo, int tamanho){
        byte[] imagemSaida = null;
        try {
            File arq = new File(arquivo);
            //String nomeArq = arq.getName();
            //String formato = nomeArq.substring(nomeArq.lastIndexOf('.') + 1);           
            /*
            BufferedImage buffer = ImageIO.read(arq);
            buffer.flush();            
            Image img = buffer.getScaledInstance(tamanho, tamanho, 
                    Image.SCALE_SMOOTH);
            img.flush();
            */
            BufferedImage rbuffer = new BufferedImage(tamanho, tamanho,
                    BufferedImage.TYPE_INT_RGB);
            Graphics2D g2d = rbuffer.createGraphics();
            Image img = ImageIO.read(arq);
            g2d.drawImage(img, 0, 0, tamanho, tamanho, null);
            g2d.dispose();
            
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            //ImageIO.write(rbuffer, "bmp", baos);
            BMPEncoder.write(rbuffer, baos);
            baos.flush();
            imagemSaida = baos.toByteArray();
            baos.close();
            
        } catch (IOException ex) {
            Logger.getLogger(Rotinas.class.getName()).log(
                    Level.SEVERE, null, ex);
        }
        return imagemSaida;        
    }
    
}
