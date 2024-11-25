package hfsguardadir.catalogador;

import java.awt.BorderLayout;
import java.awt.Cursor;
import java.awt.event.ActionEvent;
import java.io.File;
import java.io.IOException;
import java.math.BigDecimal;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;

import javax.swing.AbstractAction;
import javax.swing.ButtonGroup;
import javax.swing.Icon;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JRadioButtonMenuItem;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.JViewport;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreePath;
import javax.xml.parsers.ParserConfigurationException;

import org.xml.sax.SAXException;

import hfsguardadir.comum.ICatalogador;
import hfsguardadir.comum.IProgressoLog;
import hfsguardadir.comum.Rotinas;
import hfsguardadir.comum.StringList;
import hfsguardadir.comum.TipoExportar;
import hfsguardadir.gui.FrmImportarDiretorio;
import hfsguardadir.gui.FrmPrincipal;
import hfsguardadir.gui.FrmSplash;
import hfsguardadir.gui.FrmSplashProgresso;
import hfsguardadir.objetos.Aba;
import hfsguardadir.objetos.Diretorio;
import hfsguardadir.objetos.DiretorioOrdem;
import hfsguardadir.objetos.Extensao;
import hfsguardadir.objetos.Importar;
import hfsguardadir.objetos.Parametro;
import hfsguardadir.objetosbo.AbaBO;
import hfsguardadir.objetosbo.DiretorioBO;
import hfsguardadir.objetosbo.ExtensaoBO;
import hfsguardadir.objetosdao.VisaoDAO;
import hfsguardadir.objetosgui.Arvore;
import hfsguardadir.objetosgui.Dialogo;
import hfsguardadir.objetosgui.EscolhaArquivo;
import hfsguardadir.objetosgui.Tabela;

public class Catalogador implements ICatalogador {

    private static final String CONSULTA_DIR_PAI
            = "select aba, cod, ordem, coddirpai, nome, tam, tipo, modificado, "
            + "atributos, caminho, nomeaba, nomepai, caminhopai "
            + "from consultadirpai "
            + "order by 1,2,3,4";
    private static final String CONSULTA_DIR_FILHO
            = "select aba, cod, ordem, coddirpai, nome, tam, tipo, modificado, "
            + "atributos, caminho, nomeaba, nomepai, caminhopai "
            + "from consultadirfilho "
            + "order by 1,2,3,4";
    public static final String CONSULTA_ARQUIVO
            = "select aba, cod, ordem, coddirpai, nome, tam, tipo, modificado, "
            + "atributos, caminho, nomeaba, nomepai, caminhopai "
            + "from consultaarquivo "
            + "order by tipo desc, ordem";

    private static final String MAC = "com.sun.java.swing.plaf.mac.MacLookAndFeel";
    private static final String METAL = "javax.swing.plaf.metal.MetalLookAndFeel";
    private static final String MOTIF = "com.sun.java.swing.plaf.motif.MotifLookAndFeel";
    private static final String WINDOWS = "com.sun.java.swing.plaf.windows.WindowsLookAndFeel";
    private static final String WINDOWS_CLASSIC = "com.sun.java.swing.plaf.windows.WindowsClassicLookAndFeel";
    private static final String GTK = "com.sun.java.swing.plaf.gtk.GTKLookAndFeel";
    private static final String NIMBUS = "javax.swing.plaf.nimbus.NimbusLookAndFeel";
        
    private static final String NO_RAIZ = "Raiz";
    
    private String currentLookAndFeel;
    private final boolean bSombrearLinhas, bSombrearColunas;

    //private static final Logger log = Logger.getLogger(Rotinas.HFSGUARDADIR);

    private ArrayList<Diretorio> listaDiretorioFilho;
    private ArrayList<Diretorio> listaArquivos;

    public DiretorioOrdem diretorioOrdem;

    public ArrayList<Aba> listaAbas;
    public ArrayList<Diretorio> listaDiretorioPai;
    public ArrayList<Extensao> listaExtensoes;

    private DefaultMutableTreeNode nodeRaiz;

    private final FrmPrincipal form;

    public Catalogador(FrmPrincipal form) {
        this.form = form;
        this.bSombrearLinhas = false;
        this.bSombrearColunas = false;
        this.currentLookAndFeel = METAL;

        diretorioOrdem = new DiretorioOrdem();
        
        listaAbas = new ArrayList<>();
        listaExtensoes = new ArrayList<>();
        listaDiretorioPai = new ArrayList<>();
        listaDiretorioFilho = new ArrayList<>();
        listaArquivos = new ArrayList<>();

        form.tabelaPesquisa = new Tabela(this, null, null, form.pb, false);
        
        criaMenuLookFeel();
        
        form.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));        
        FrmSplash frmSplash = new FrmSplash(form, false);       
        FrmSplashProgresso frmSplashProgresso = new FrmSplashProgresso(frmSplash);
        try {
            Rotinas.CentralizaDlg(frmSplash);
            frmSplash.setVisible(true);
            CarregarDados(frmSplashProgresso, true, true);
            CarregarAbas();
            tabPanelMudou();
            
            frmSplash.dispose();
            
        } catch (SQLException ex) {
            Logger.getLogger(Catalogador.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        form.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
    }
    
    public static void iniciarSistema(Parametro param) throws SAXException,
            IOException, ParserConfigurationException, SQLException,
            ClassNotFoundException {
        Aba aba;
        
        if (!Rotinas.carregarParametros(param.getArquivoConfiguracao())) {       
            Dialogo.mensagemErro(null, "HFSGuardaDir.ValidaArquivoConf");
        }
        
        Rotinas.registrarProvedorTIFF();        
        
        String sBanco = param.getDiretorioSistema() + 
                Rotinas.BARRA_INVERTIDA + "GuardaDir.db";
        
        if (!Rotinas.FileExists(sBanco)){
            Rotinas.Conectar();
            
            AbaBO.getInstancia().criarTabelaAbas();

            aba = new Aba(1,"DISCO1",0);
            AbaBO.getInstancia().incluirAba(aba);

            ExtensaoBO.getInstancia().criarTabelaExtensoes();
            DiretorioBO.getInstancia().criarTabelaDiretorios();
            VisaoDAO.getInstancia().criarVisao("consultadirpai");
            VisaoDAO.getInstancia().criarVisao("consultadirfilho");
            VisaoDAO.getInstancia().criarVisao("consultaarquivo");
        } else 
            Rotinas.Conectar();

        Dialogo.mudarLingua();
        EscolhaArquivo.mudarLingua();
    }

    public void mudarLingua(String lingua) {
        Parametro params = Rotinas.getParams();
        params.setLocalidadeLingua(lingua);
        params.setLocalidadePais("");
        form.mudarLingua();

        Dialogo.mudarLingua();
        EscolhaArquivo.mudarLingua();
    }
/*
    private boolean isAvailableLookAndFeel(String laf) {
        try {
            Class<?> lnfClass = Class.forName(laf);
            LookAndFeel newLAF = (LookAndFeel) (lnfClass.getDeclaredConstructor().newInstance());
            return newLAF.isSupportedLookAndFeel();
        } catch (ClassNotFoundException | InstantiationException | 
        		IllegalAccessException | IllegalArgumentException | 
        		InvocationTargetException | NoSuchMethodException | 
        		SecurityException e) {
            return false;
        }
    }
*/
    public String getLookAndFeel(String laf) {
        switch (laf) {
            case "mac":
                return MAC;
            case "metal":
                return METAL;
            case "motif":
                return MOTIF;
            case "windows":
                return WINDOWS;
            case "windows classic":
                return WINDOWS_CLASSIC;                
            case "gtk":
                return GTK;
            case "nimbus":
                return NIMBUS;
            default:
                return METAL;
        }
    }

    public void setLookAndFeel(String laf) {
        if (!currentLookAndFeel.equals(laf)) {
            currentLookAndFeel = laf;
            String lafName;

            lafName = null;
            if (laf.equals(MAC)) {
                lafName = Rotinas.getRecurso("LafMenu.mac_label");
                Rotinas.getParams().setLookAndFeel("mac");
            }
            if (laf.equals(METAL)) {
                lafName = Rotinas.getRecurso("LafMenu.java_label");
                Rotinas.getParams().setLookAndFeel("metal");
            }
            if (laf.equals(MOTIF)) {
                lafName = Rotinas.getRecurso("LafMenu.motif_label");
                Rotinas.getParams().setLookAndFeel("motif");
            }
            if (laf.equals(WINDOWS)) {
                lafName = Rotinas.getRecurso("LafMenu.windows_label");
                Rotinas.getParams().setLookAndFeel("windows");
            }
            if (laf.equals(WINDOWS_CLASSIC)) {
                lafName = Rotinas.getRecurso("LafMenu.windows_classic_label");
                Rotinas.getParams().setLookAndFeel("windows classic");
            }
            if (laf.equals(GTK)) {
                lafName = Rotinas.getRecurso("LafMenu.gtk_label");
                Rotinas.getParams().setLookAndFeel("gtk");
            }
            if (laf.equals(NIMBUS)) {
                lafName = Rotinas.getRecurso("LafMenu.nimbus_label");
                Rotinas.getParams().setLookAndFeel("nimbus");
            }

            try {
                UIManager.setLookAndFeel(currentLookAndFeel);

                Icon folhaIcon = (Icon) UIManager.get("Tree.closedIcon");
                UIManager.put("Tree.leafIcon", folhaIcon);

            } catch (ClassNotFoundException e) {
            } catch (InstantiationException e) {
            } catch (IllegalAccessException e) {
            } catch (UnsupportedLookAndFeelException e) {
            }
            SwingUtilities.updateComponentTreeUI(form);
            for (int i = 0; i < form.lafMenu.getItemCount(); i++) {
                JMenuItem item = form.lafMenu.getItem(i);
                if (item.getText().equals(lafName)) {
                    item.setSelected(true);
                } else {
                    item.setSelected(false);
                }
            }
        }
    }

    public JMenuItem createLafMenuItem(ButtonGroup lafMenuGroup,
            JMenu lafMenu, String label, String mnemonic,
            String accessibleDescription, String laf) {
        JMenuItem mi = (JRadioButtonMenuItem) lafMenu
                .add(new JRadioButtonMenuItem(Rotinas.getRecurso(label)));
        lafMenuGroup.add(mi);
        mi.setMnemonic(Rotinas.getMnemonico(mnemonic));
        mi.getAccessibleContext().setAccessibleDescription(
                Rotinas.getRecurso(accessibleDescription));
        mi.addActionListener(new ChangeLookAndFeelAction(this, laf));

        //mi.setEnabled(isAvailableLookAndFeel(laf));

        return mi;
    }

    public final void criaMenuLookFeel() {
        ButtonGroup lafMenuGroup = new ButtonGroup();

        //menuLafLabel.setText(Rotinas.getRecurso("LafMenu.laf_label"));
        //lafMenu = (JMenu) menuBarra.add(menuLafLabel);
        form.lafMenu.setMnemonic(Rotinas.getMnemonico("LafMenu.laf_mnemonic"));
        form.lafMenu.getAccessibleContext().setAccessibleDescription(
                Rotinas.getRecurso("LafMenu.laf_accessible_description"));

        JMenuItem mi = createLafMenuItem(lafMenuGroup, form.lafMenu,
                "LafMenu.java_label", "LafMenu.java_mnemonic",
                "LafMenu.java_accessible_description",
                METAL);
        mi.setSelected(true);

        UIManager.LookAndFeelInfo[] lafInfo = UIManager
                .getInstalledLookAndFeels();

        for (UIManager.LookAndFeelInfo lafInfo1 : lafInfo) {
            String className = lafInfo1.getClassName();
            switch (className) {
                case MAC:
                    createLafMenuItem(lafMenuGroup, form.lafMenu,
                            "LafMenu.mac_label", "LafMenu.mac_mnemonic",
                            "LafMenu.mac_accessible_description", MAC);
                    break;
                case MOTIF:
                    createLafMenuItem(lafMenuGroup, form.lafMenu,
                            "LafMenu.motif_label", "LafMenu.motif_mnemonic",
                            "LafMenu.motif_accessible_description", MOTIF);
                    break;
                case WINDOWS:
                    createLafMenuItem(lafMenuGroup, form.lafMenu,
                            "LafMenu.windows_label", "LafMenu.windows_mnemonic",
                            "LafMenu.windows_accessible_description", WINDOWS);
                    break;
                case WINDOWS_CLASSIC:
                    createLafMenuItem(lafMenuGroup, form.lafMenu,
                            "LafMenu.windows_classic_label", "LafMenu.windows_classic_mnemonic",
                            "LafMenu.windows_classic_accessible_description", WINDOWS_CLASSIC);
                    break;
                case GTK:
                    createLafMenuItem(lafMenuGroup, form.lafMenu,
                            "LafMenu.gtk_label", "LafMenu.gtk_mnemonic",
                            "LafMenu.gtk_accessible_description", GTK);
                    break;
                case NIMBUS:
                    createLafMenuItem(lafMenuGroup, form.lafMenu,
                            "LafMenu.nimbus_label", "LafMenu.nimbus_mnemonic",
                            "LafMenu.nimbus_accessible_description", NIMBUS);
                    break;
            }
        }

    }
    
    public void CarregarDados(IProgressoLog pLog, boolean bExtensao,
            boolean bDiretorio) throws SQLException {
        listaAbas = AbaBO.getInstancia().carregarAba(pLog);
        if (bExtensao) {
            listaExtensoes = ExtensaoBO.getInstancia().carregarExtensao(pLog);
        }
        if (bDiretorio) {
            listaDiretorioPai = DiretorioBO.getInstancia().carregarDiretorio(
                    CONSULTA_DIR_PAI, "consultadirpai", pLog);
            listaDiretorioFilho = DiretorioBO.getInstancia().carregarDiretorio(
                    CONSULTA_DIR_FILHO, "consultadirfilho", pLog);
            listaArquivos = DiretorioBO.getInstancia().carregarDiretorio(
                    CONSULTA_ARQUIVO, "consultaarquivo", pLog);
        }
    }

    public void ExcluirDados(Aba aba, String sCaminho) {
        DiretorioBO.getInstancia().excluirListaDiretorio(listaDiretorioPai, aba, sCaminho);
        DiretorioBO.getInstancia().excluirListaDiretorio(listaDiretorioFilho, aba, sCaminho);
        DiretorioBO.getInstancia().excluirListaDiretorio(listaArquivos, aba, sCaminho);
    }

    private void AddItemArvore(Diretorio diretorio, int Nivel,
            DefaultMutableTreeNode node1) {
        ArrayList<Diretorio> listaFilhos;
        DefaultMutableTreeNode node2;

        if (Nivel == 0) {
            node1 = new DefaultMutableTreeNode(diretorio.getNome());
            nodeRaiz.add(node1);
        }

        listaFilhos = DiretorioBO.getInstancia().itensFilhos(listaDiretorioFilho,
                diretorio.getAba().getCodigo(), diretorio.getOrdem(),
                diretorio.getCodigo());

        for (Diretorio filho : listaFilhos) {
            node2 = new DefaultMutableTreeNode(filho.getNome());
            node1.add(node2);
            AddItemArvore(filho, ++Nivel, node2);
        }
    }

    public void IncluirNovaAba() throws SQLException {
        Aba aba;
        String sAba = Dialogo.entrada(form, "FrmPrincipal.DigitaIncluirNovaAba");
        if ((sAba != null) && (sAba.trim().length() > 0)) {
            aba = new Aba();
            aba.setCodigo(AbaBO.getInstancia().retMaxCodAba(listaAbas));
            aba.setNome(Rotinas.SubString(sAba, 1, 10));
            aba.setOrdem(listaAbas.size() + 1);
            AbaBO.getInstancia().incluirAba(aba);
            IncluirNovaAba(aba.getNome());
            listaAbas.add(aba);
        }
    }
    
    public void AlterarNomeAbaAtiva(IProgressoLog pLog) throws SQLException {
        Aba aba = getAbaAtual();
        String sAba = Dialogo.entrada(form, "FrmPrincipal.DigitaAlterarNomeAba", 
                aba.getNome());
        if ((sAba != null) && (sAba.trim().length() > 0)) {
            aba.setNome(Rotinas.SubString(sAba, 1, 10));
            AbaBO.getInstancia().alterarAba(aba);
            form.tabPanel.setTitleAt(form.tabPanel.getSelectedIndex(), sAba);
            CarregarDados(pLog, false, true);
        }        
    }
    
    public void ExcluirAbaAtiva(IProgressoLog pLog) throws SQLException{
        Aba aba;
        int indiceSel = form.tabPanel.getSelectedIndex();
        if (indiceSel > 0) {
            int res = Dialogo.confirma(form, "FrmPrincipal.ConfirmaExcluirAba");
            if (res == Dialogo.YES_OPTION) {
                form.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
                
                aba = getAbaAtual();
                ExcluirDados(aba, "");
                AbaBO.getInstancia().excluirAba(aba);                
                form.tabPanel.removeTabAt(indiceSel);
                
                CarregarDados(pLog, false, false);

                form.barraStatus2.setText("");
                
                form.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
            }
        } else
                Dialogo.mensagemErro(form, "FrmPrincipal.ValidaExcluirAba");        
    }
    
    private void IncluirNovaAba(String nomeAba) {
        JPanel panelAba;
        JScrollPane scrollArvore;
        Arvore arvore;
        JSplitPane split;
        JScrollPane scrollTabela;
        Tabela tabela;

        panelAba = new JPanel();
        panelAba.setLayout(new BorderLayout());

        split = new JSplitPane();
        split.setDividerLocation(200);

        arvore = new Arvore(null);
        arvore.setName("arvore" + nomeAba);
        arvore.setComponentPopupMenu(form.menuPopup);
        arvore.addTreeSelectionListener(new TreeSelectionListener() {
            @Override
            public void valueChanged(TreeSelectionEvent evt) {
                arvoreValorMudou(evt);
            }
        });
        scrollArvore = new JScrollPane();
        scrollArvore.setViewportView(arvore);

        split.setLeftComponent(scrollArvore);

        tabela = new Tabela(this, null, null, form.pb, true);
        tabela.setSombrearLinhas(bSombrearLinhas);
        tabela.setSombrearColunas(bSombrearColunas);
        tabela.setName("tabela" + nomeAba);
        tabela.setComponentPopupMenu(form.menuPopup);

        scrollTabela = new JScrollPane();
        scrollTabela.setViewportView(tabela);

        split.setRightComponent(scrollTabela);

        panelAba.add(split, BorderLayout.CENTER);

        form.tabPanel.addTab(nomeAba, Rotinas.getImagem("cdouro.gif"), panelAba);
    }

    public Arvore getArvoreAtual() {
        return getArvoreAtual(form.tabPanel.getSelectedIndex());
    }

    public Arvore getArvoreAtual(int nIndicePagina) {
        JPanel panel = (JPanel) form.tabPanel.getComponentAt(nIndicePagina);
        JSplitPane split = (JSplitPane) panel.getComponent(0);
        JScrollPane rolagem = (JScrollPane) split.getLeftComponent();
        JViewport visao = (JViewport) rolagem.getComponent(0);
        Arvore arvore = (Arvore) visao.getComponent(0);
        return arvore;
    }

    public JSplitPane getSplitAtual() {
        int nIndicePagina = form.tabPanel.getSelectedIndex();
        JPanel panel = (JPanel) form.tabPanel.getComponentAt(nIndicePagina);
        JSplitPane split = (JSplitPane) panel.getComponent(0);
        return split;
    }

    public JScrollPane getScrollArvoreAtual() {
        int nIndicePagina = form.tabPanel.getSelectedIndex();
        JPanel panel = (JPanel) form.tabPanel.getComponentAt(nIndicePagina);
        JSplitPane split = (JSplitPane) panel.getComponent(0);
        JScrollPane rolagem = (JScrollPane) split.getLeftComponent();
        return rolagem;
    }
    
    public Tabela getTabelaAtual() {
        int nIndicePagina = form.tabPanel.getSelectedIndex();
        JPanel panel = (JPanel) form.tabPanel.getComponentAt(nIndicePagina);
        JSplitPane split = (JSplitPane) panel.getComponent(0);
        JScrollPane rolagem = (JScrollPane) split.getRightComponent();
        JViewport visao = (JViewport) rolagem.getComponent(0);
        Tabela tabela = (Tabela) visao.getComponent(0);
        return tabela;
    }

    public void setTabelaAtual(Tabela tabela) {
        int nIndicePagina = form.tabPanel.getSelectedIndex();

        tabela.setComponentPopupMenu(form.menuPopup);
        tabela.getSelectionModel().setSelectionInterval(0, 0);
        tabela.setSombrearLinhas(true);
        
        JPanel panel = (JPanel) form.tabPanel.getComponentAt(nIndicePagina);
        JSplitPane split = (JSplitPane) panel.getComponent(0);
        JScrollPane rolagem = (JScrollPane) split.getRightComponent();
        rolagem.setViewportView(tabela);
    }
    
    public void mostrarOcultarArvore(){
        Arvore arvore = getArvoreAtual();
        JScrollPane scroll = getScrollArvoreAtual();
        scroll.setVisible(!scroll.isVisible());
        if (arvore.isVisible()) {
            getSplitAtual().setDividerLocation(200);
        } else {
            getSplitAtual().setDividerLocation(0);
        }
    }
    
    public void CarregarArvore(Arvore tvAba, Aba aba) {
        DefaultTreeModel dtm;

        tvAba.limpar(aba.getNome());
        
        nodeRaiz = new DefaultMutableTreeNode(NO_RAIZ);
        for (Diretorio diretorio : listaDiretorioPai) {
            if (diretorio.getAba().getCodigo() == aba.getCodigo()) {
                AddItemArvore(diretorio, 0, null);
            }
        }

        dtm = new DefaultTreeModel(nodeRaiz);
        tvAba.setModel(dtm);
        tvAba.setRootVisible(false);
    }

    public void CarregarAbas() {
        Arvore tvAba;

        form.pb.setMinimum(0);
        form.pb.setMaximum(listaAbas.size() - 1);
        form.pb.setValue(0);

        for (int i = 0; i < listaAbas.size(); i++) {
            IncluirNovaAba(listaAbas.get(i).getNome());
            tvAba = getArvoreAtual(i);
            CarregarArvore(tvAba, listaAbas.get(i));
            form.pb.setValue(i);
        }
    }

    private Aba getAbaAtual() {
        return AbaBO.getInstancia().pegaAbaPorOrdem(
                listaAbas, form.tabPanel.getSelectedIndex() + 1);
    }

    public Tabela CarregarArquivosLista(boolean bLista1, String sCaminho) {
        String sPaiCaminho;
        ArrayList<Diretorio> listaLocal;
        Tabela lvArquivos;
        int nAba;

        listaLocal = new ArrayList<>();

        if (bLista1) {
            sPaiCaminho = sCaminho;
            if (!Rotinas.SubString(sCaminho, sCaminho.length(), 1).equals(Rotinas.BARRA_INVERTIDA)) {
                sCaminho = sCaminho + Rotinas.BARRA_INVERTIDA;
            }
            nAba = getAbaAtual().getCodigo();
            for (Diretorio diretorio : listaArquivos) {
                if (diretorio.getAba().getCodigo() == nAba) {
                    if (diretorio.getCaminhoPai().equals(sPaiCaminho)) {
                        if (Rotinas.StartsStr(sCaminho, diretorio.getCaminho())) {
                            listaLocal.add(diretorio);
                        }
                    }
                }
            }
        } else {
            for (Diretorio diretorio : listaArquivos) {
                if (Rotinas.ContainsStr(diretorio.getCaminho().toUpperCase(), 
                        sCaminho.toUpperCase())) {
                    listaLocal.add(diretorio);
                }
            }
        }
        lvArquivos = new Tabela(this, listaLocal, listaExtensoes, form.pb, bLista1);
        listaLocal.clear();

        return lvArquivos;
    }

    public void TamTotalDiretorio(String sCaminho) {
        long conta;
        int nAba;
        BigDecimal soma, tam;

        conta = 0;
        soma = new BigDecimal(0);

        for (Diretorio diretorio : listaArquivos) {
            nAba = getAbaAtual().getCodigo();
            if (diretorio.getAba().getCodigo() == nAba) {
                if (diretorio.getTipo().getCodigo() != 'D') {
                    if (sCaminho.trim().length() > 0) {
                        if (Rotinas.StartsStr(sCaminho, diretorio.getCaminho())) {
                            conta++;
                            tam = new BigDecimal(diretorio.getTamanho());
                            soma = soma.add(tam);
                        }
                    } else {
                        conta++;
                        tam = new BigDecimal(diretorio.getTamanho());
                        soma = soma.add(tam);
                    }
                }
            }
        }

        form.barraStatus1.setText(
                "Quantidade Total: " + Rotinas.FormatLong("0000", conta)
                + ", Tamanho Total: " + DiretorioBO.getInstancia().MontaTamanhoBig(soma));
    }

    private boolean testaSeparadorArquivo(String sDir) {
        sDir = Rotinas.SubString(sDir, sDir.length(), 1);
        if (sDir.equals(Rotinas.BARRA_INVERTIDA) 
                || sDir.equals(Rotinas.BARRA_NORMAL)
                || sDir.equals(Rotinas.BARRA_INVERTIDA)) {
            return true;
        } else {
            return false;
        }
    }

    private StringList montaCaminho(String sCaminho, boolean bRemover) {
        sCaminho = NO_RAIZ + Rotinas.BARRA_INVERTIDA + sCaminho;
        StringList sl = new StringList(sCaminho, Rotinas.BARRA_INVERTIDA.charAt(0));
        if (sl.get(sl.size() - 1).trim().length() == 0) {
            sl.remove(sl.size() - 1);
        }
        if (bRemover) {
            sl.remove(sl.size() - 1);
        }
        return sl;
    }

    public void Pesquisar() {
        Arvore arvoreLocal = getArvoreAtual();
        DefaultTreeModel modelo = (DefaultTreeModel) arvoreLocal.getModel();
        DefaultMutableTreeNode arvoreNode = (DefaultMutableTreeNode) modelo
                .getRoot();
        if (arvoreLocal.getModel().getChildCount(arvoreNode) > 0) {
            if (form.edtPesquisa.getText().length() >= 2) {
                form.scrollPesquisa.setVisible(true);
                form.spPesquisa.setDividerLocation(280);
                form.tabelaPesquisa = CarregarArquivosLista(false, 
                        form.edtPesquisa.getText());
                form.tabelaPesquisa.getSelectionModel().
                        setSelectionInterval(0, 0);
                form.tabelaPesquisa.setSombrearLinhas(true);                
                form.scrollPesquisa.setViewportView(form.tabelaPesquisa);                
            } else {
                form.scrollPesquisa.setVisible(false);
                form.spPesquisa.setDividerLocation(0);
                form.tabelaPesquisa = new Tabela(this, null, null, 
                        form.pb, false);
                form.scrollPesquisa.setViewportView(form.tabelaPesquisa);
                Dialogo.mensagemInfo(form, "FrmPrincipal.TamMaxPesquisa");
            }
        }
    }

    public void PesquisarArvoreDiretorio(String sCaminho, Aba aba) {
        form.tabPanel.setSelectedIndex(aba.getOrdem()-1);
        Arvore arvore = getArvoreAtual();
        StringList sl = montaCaminho(sCaminho, false); // Verifica Diretorio
        TreePath path = arvore.encontrarCaminhoPorNome(sl.toStringArray());
        if (path == null) {
            sl.set(1, sl.get(1) + Rotinas.BARRA_INVERTIDA);
            path = arvore.encontrarCaminhoPorNome(sl.toStringArray());

            if (path == null) {
                sl.clear();
                sl = montaCaminho(sCaminho, true); // Verifica Arquivo
                path = arvore.encontrarCaminhoPorNome(sl.toStringArray());

                if (path == null) {
                    sl.set(1, sl.get(1) + Rotinas.BARRA_INVERTIDA);
                    path = arvore.encontrarCaminhoPorNome(sl.toStringArray());
                }
            }
        }

        arvore.expandPath(path);
        arvore.setSelectionPath(path);
    }

    public void LerArvoreDiretorio(TreePath path,
            JLabel barraStatus) {
        String caminho = "", sCaminho = "";
        int ntotal = path.getPath().length;

        if (ntotal > 1) {
            for (int i = 1; i < ntotal; i++) {
                caminho += path.getPath()[i].toString()
                        + Rotinas.BARRA_INVERTIDA;
            }
            caminho = caminho.substring(0, caminho.length() - 1);
            for (int i = 0; i < caminho.length(); i++) {
                if (caminho.length() > 1) {
                    if (Rotinas.SubString(caminho, i + 1, 2).equals(
                            Rotinas.BARRA_INVERTIDA)) {
                        sCaminho += Rotinas.BARRA_INVERTIDA;
                        i++;
                    } else {
                        sCaminho += caminho.charAt(i);
                    }
                }
            }
            barraStatus.setText(sCaminho);
        }
    }

    public Tabela ListarArquivos() {
        Tabela tabela = CarregarArquivosLista(true, form.barraStatus2.getText());
        TamTotalDiretorio(form.barraStatus2.getText());
        return tabela;
    }
    
    public void tabPanelMudou(){
        Arvore arvore = getArvoreAtual();
        
        TamTotalDiretorio("");                
        arvore.setSelectionRow(0);
        if (!arvore.isSelectionEmpty()){
            LerArvoreDiretorio(arvore.getSelectionPath(), form.barraStatus2);
        }
    }

    public void arvoreValorMudou(TreeSelectionEvent evt) {
        LerArvoreDiretorio(evt.getPath(), form.barraStatus2);
        setTabelaAtual(ListarArquivos());
    }

    @Override
    public Aba getAbaSelecionada() {
        return getAbaAtual();
    }

    @Override
    public void DuploCliqueLista(String nome, String tipo) {
        if (tipo.equals(Rotinas.getRecurso("TipoLista.diretorio"))) {
            form.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
            String sCaminho = form.barraStatus2.getText();
            if (testaSeparadorArquivo(sCaminho)) {
                sCaminho += nome;
            } else {
                sCaminho += Rotinas.BARRA_INVERTIDA + nome;
            }
            
            PesquisarArvoreDiretorio(sCaminho, getAbaAtual());
            form.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
        }
    }

    @Override
    public void EncontrarItemLista(String nomeAba, String nome, String caminho) {
        form.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
        Aba aba = AbaBO.getInstancia().pegaAbaPorNome(listaAbas, nomeAba);        
        PesquisarArvoreDiretorio(caminho, aba);

        Tabela tabela = getTabelaAtual();
        int nlinha = tabela.encontrarLinha(nome);
        tabela.setRowSelectionInterval(nlinha, nlinha);        
        tabela.scrollRectToVisible(tabela.getCellRect(tabela.getSelectedRow(), 0, 
                true));
        tabela.scrollToCenter(tabela.getSelectedRow(), 0);
        form.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));        
    }
   
    public int verificaNomeDiretorio(String sCaminho, RotuloRaiz sRotuloRaiz) {
        sRotuloRaiz.setRotulo(
                DiretorioBO.getInstancia().removerDrive(sCaminho));
        if (sRotuloRaiz.getRotulo().length() == 0) {

            sRotuloRaiz.setRotulo(Dialogo.entrada(form,
                    "FrmPrincipal.DigitaNomeDiretorio"));

            if ((sRotuloRaiz.getRotulo() != null)
                    && (sRotuloRaiz.getRotulo().trim().length() > 0)) {
                sRotuloRaiz.setRotulo(sRotuloRaiz.getRotulo().trim());

                if (sRotuloRaiz.getRotulo().length() > 0) {
                    return 1;
                } else {
                    Dialogo.mensagemInfo(form, 
                            "FrmPrincipal.ValidaNomeDiretorio");
                    return 0;
                }
            } else {
                return 0;
            }
        } else if (Rotinas.Pos(Rotinas.BARRA_INVERTIDA,
                sRotuloRaiz.getRotulo()) > 0) {
            sRotuloRaiz.setRotulo(Rotinas.SubString(sRotuloRaiz.getRotulo(),
                    Rotinas.LastDelimiter(Rotinas.BARRA_INVERTIDA,
                            sRotuloRaiz.getRotulo()) + 1,
                    sRotuloRaiz.getRotulo().length()));
            return 2;
        } else {
            return 3;
        }
    }
    
    public void ExportarArquivo(TipoExportar tipo, IProgressoLog pLog) 
            throws SQLException, IOException {
        String sExtensao = "";

        switch (tipo) {
            case teTXT:
                sExtensao = "txt";
                break;
            case teCSV:
                sExtensao = "csv";
                break;
            case teHTML:
                sExtensao = "html";
                break;
            case teXML:
                sExtensao = "xml";
                break;
            case teSQL:
                sExtensao = "sql";
                break;
        }

        EscolhaArquivo escolha = new EscolhaArquivo(EscolhaArquivo.SAVE_DIALOG);
        Aba aba = getAbaAtual();
        String sArq = escolha.getCurrentDirectory()+
                Rotinas.BARRA_INVERTIDA+
                aba.getNome()+'.'+sExtensao;
        escolha.setSelectedFile(new File(sArq));
        int retval = escolha.mostrarSalvar(this.form);
        if (retval == EscolhaArquivo.APPROVE_OPTION) {
            File arquivo = escolha.getSelectedFile();
            if (arquivo != null) {
                form.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
                DiretorioBO.getInstancia().exportarDiretorio(tipo, getAbaAtual(),
                        arquivo.getPath(), pLog);
                form.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));

                Dialogo.mensagemErro(this.form, "FrmPrincipal.SucessoExportar");
            }
        } else if (retval == EscolhaArquivo.ERROR_OPTION) {
            Dialogo.mensagemErro(this.form, "FrmPrincipal.ErroSalvarArquivo");
        }
    }

    private StringList montaCaminho(TreePath path, boolean bRemoveRaiz) {
        StringList lista = new StringList();
        int nini = 0;
        if (bRemoveRaiz) {
            nini = 1;
        }
        for (int i = nini; i < path.getPath().length; i++) {
            lista.add(path.getPath()[i].toString());
            if (bRemoveRaiz) {
                lista.add(Rotinas.BARRA_INVERTIDA);
            }
        }
        if (bRemoveRaiz) {
            lista.remove(lista.size() - 1);
        }
        return lista;
    }
    
    public void ExcluirDiretorioSelecionado(IProgressoLog pLog) 
            throws SQLException {
        Arvore arvore = getArvoreAtual();
        TreePath path = arvore.getSelectionPath();

        if (arvore.isPathSelected(path) && path.toString().length() > 0) {
            Tabela tabela = getTabelaAtual();
            int res = Dialogo.confirma(this.form, "FrmPrincipal.ExcluirDiretorioSelecionado");
            if (res == Dialogo.YES_OPTION) {
                form.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
                StringList sl = montaCaminho(path, true);

                DiretorioBO.getInstancia().excluirDiretorio(getAbaAtual(), sl.getText());
                ExcluirDados(getAbaAtual(), sl.getText());

                StringList sl2 = montaCaminho(path, false);
                arvore.excluirNode(sl2.toStringArray());
                tabela.removeAll();

                CarregarDados(pLog, false, false);

                form.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
            }
        }
    }
    
    public void ImportarArquivo(StringList log, IProgressoLog pLog) 
            throws IOException, SQLException {
        int nResultado;

        EscolhaArquivo escolha = new EscolhaArquivo(
                EscolhaArquivo.PREVIEW_OPEN_DIALOG);
        int retval = escolha.mostrarAbrir(form);
        if (retval == EscolhaArquivo.APPROVE_OPTION) {
            File arquivo = escolha.getSelectedFile();
            if (arquivo != null) {
                form.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
                nResultado = DiretorioBO.getInstancia().importarDiretorioViaXML(
                getAbaAtual(), arquivo.getPath(), listaDiretorioPai, pLog);
                if (nResultado == -1) {
                    Dialogo.mensagemErro(this.form, 
                            "FrmPrincipal.ImportacaoNaoRealizada");
                } else if (nResultado == -2) {
                    Dialogo.mensagemErro(this.form, 
                            "FrmPrincipal.DiretorioExisteCatalogo");
                } else {                    
                    FinalizaImportacao(pLog);                    
                }
                form.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
            }
        }
    }
    
    public boolean ImportarDiretorios(StringList listaCaminho,
            boolean bSubDiretorio, FrmImportarDiretorio frmImportarDiretorio) {
        int nAba, nRotuloRaiz, nCodDirRaiz;
        RotuloRaiz sRotuloRaiz = new RotuloRaiz();
        String sCaminhoSemDrive;
        Importar importar = new Importar();

        nAba = getAbaAtual().getCodigo();
        nCodDirRaiz = DiretorioBO.getInstancia().retMaxCodDir(nAba, 
                listaDiretorioPai);

        for (String sCaminho : listaCaminho) {
            nRotuloRaiz = verificaNomeDiretorio(sCaminho, sRotuloRaiz);
            if (nRotuloRaiz > 0) {
                importar = new Importar();
                importar.setAba(nAba);
                importar.setCodDirRaiz(nCodDirRaiz);
                importar.setRotuloRaiz(sRotuloRaiz.getRotulo());
                if (nRotuloRaiz == 1) {
                    importar.setNomeDirRaiz(sRotuloRaiz.getRotulo());
                } else if (nRotuloRaiz == 2) {
                    sCaminhoSemDrive = DiretorioBO.getInstancia().removerDrive(sCaminho);
                    importar.setNomeDirRaiz(Rotinas.SubString(
                            sCaminhoSemDrive, 1,
                            Rotinas.LastDelimiter(Rotinas.BARRA_INVERTIDA,
                                    sCaminhoSemDrive) - 1));
                } else if (nRotuloRaiz == 3) {
                    importar.setNomeDirRaiz("");
                }
                importar.setCaminho(sCaminho);

                frmImportarDiretorio.listaImportar.add(importar);
                nCodDirRaiz++;
            }
        }

        frmImportarDiretorio.bSubDiretorio = bSubDiretorio;

        if (bSubDiretorio) {
            frmImportarDiretorio.setVisible(true);
            return true;
        } else {
            if (!DiretorioBO.getInstancia().verificaCodDir(
                    importar.getAba(), importar.getRotuloRaiz(),
                    listaDiretorioPai)) {
                frmImportarDiretorio.setVisible(true);
                return true;
            } else {
                Dialogo.mensagemErro(this.form,
                        "FrmPrincipal.DiretorioExisteCatalogo");

                return false;
            }
        }

    }
    
    public void FinalizaImportacao(IProgressoLog pLog) throws SQLException {
        Arvore tvAba;

        form.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));

        CarregarDados(pLog, true, true);
        tvAba = getArvoreAtual();
        CarregarArvore(tvAba, getAbaAtual());

        form.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
        Dialogo.mensagemInfo(this.form, "FrmPrincipal.DirImportacaoSucesso");

    }
    
 
    public void ComecaImportacao(boolean bSubDiretorios, IProgressoLog pLog) 
            throws SQLException {
        String sCaminho;
        StringList listaCaminho;
        FrmImportarDiretorio frmImportarDiretorio;

        EscolhaArquivo escolha = new EscolhaArquivo(
                EscolhaArquivo.CUSTOM_DIALOG);
        int retval = escolha.mostrar(this.form);
        if (retval == EscolhaArquivo.APPROVE_OPTION) {
            File arquivo = escolha.getSelectedFile();

            if (arquivo != null) {
                form.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
                sCaminho = arquivo.getPath();

                frmImportarDiretorio = new FrmImportarDiretorio(form, true);
                listaCaminho = new StringList();

                if (bSubDiretorios) {
                    DiretorioBO.getInstancia().
                            carregarSubDiretorios(sCaminho, listaCaminho);
                } else {
                    listaCaminho.add(sCaminho);
                }

                if (ImportarDiretorios(listaCaminho, bSubDiretorios, 
                        frmImportarDiretorio)) {
                    FinalizaImportacao(pLog);
                }

                form.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
            }
        } else if (retval == EscolhaArquivo.ERROR_OPTION) {
            Dialogo.mensagemErro(this.form, "FrmPrincipal.ErroAbrirDir");
        }

    }
    
}

class ChangeLookAndFeelAction extends AbstractAction {

    private static final long serialVersionUID = 8947296140794376812L;

    Catalogador catalogador;
    String laf;

    protected ChangeLookAndFeelAction(Catalogador catalogador, String laf) {
        super();
        this.catalogador = catalogador;
        this.laf = laf;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        catalogador.setLookAndFeel(laf);
    }
}



