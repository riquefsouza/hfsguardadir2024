package hfsguardadir.gui;

import hfsguardadir.catalogador.Catalogador;
import hfsguardadir.comum.Rotinas;
import hfsguardadir.comum.StringList;
import static hfsguardadir.comum.TipoExportar.teCSV;
import static hfsguardadir.comum.TipoExportar.teHTML;
import static hfsguardadir.comum.TipoExportar.teSQL;
import static hfsguardadir.comum.TipoExportar.teTXT;
import static hfsguardadir.comum.TipoExportar.teXML;
import hfsguardadir.objetos.Aba;
import hfsguardadir.objetos.Diretorio;
import hfsguardadir.objetosgui.Dialogo;
import java.awt.Cursor;
import java.sql.SQLException;
import hfsguardadir.objetosgui.Tabela;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

public class FrmPrincipal extends javax.swing.JFrame {
    private static final long serialVersionUID = 1L;
    
	private FrmPrincipalProgresso frmPrincipalProgresso;
    private final Catalogador catalogador;
    
    public Tabela tabelaPesquisa;
    
    public FrmPrincipal() {
        initComponents();
        frmPrincipalProgresso = new FrmPrincipalProgresso(this);
        catalogador = new Catalogador(this);
                
        scrollPesquisa.setViewportView(tabelaPesquisa);
        scrollPesquisa.setVisible(false);
        spPesquisa.setDividerLocation(0);
    }

    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        menuPopup = new javax.swing.JPopupMenu();
        menuInformacoesDiretorioArquivo = new javax.swing.JMenuItem();
        menuExcluirDiretorioSelecionado = new javax.swing.JMenuItem();
        menuExpandirDiretorios2 = new javax.swing.JMenuItem();
        menuColapsarDiretorios2 = new javax.swing.JMenuItem();
        jSeparator2 = new javax.swing.JPopupMenu.Separator();
        menuIncluirNovaAba2 = new javax.swing.JMenuItem();
        menuAlterarNomeAbaAtiva2 = new javax.swing.JMenuItem();
        menuExcluirAbaAtiva2 = new javax.swing.JMenuItem();
        grupoIdioma = new javax.swing.ButtonGroup();
        barraFerra = new javax.swing.JToolBar();
        btnImportarDiretorio = new javax.swing.JButton();
        pb = new javax.swing.JProgressBar();
        edtPesquisa = new javax.swing.JTextField();
        btnPesquisa = new javax.swing.JButton();
        spPesquisa = new javax.swing.JSplitPane();
        tabPanel = new javax.swing.JTabbedPane();
        scrollPesquisa = new javax.swing.JScrollPane();
        barraStatus = new javax.swing.JPanel();
        barraStatus1 = new javax.swing.JLabel();
        barraStatus2 = new javax.swing.JLabel();
        barraMenu = new javax.swing.JMenuBar();
        menuAba = new javax.swing.JMenu();
        menuIncluirNovaAba = new javax.swing.JMenuItem();
        menuAlterarNomeAbaAtiva = new javax.swing.JMenuItem();
        menuExcluirAbaAtiva = new javax.swing.JMenuItem();
        menuDiretorio = new javax.swing.JMenu();
        menuImportarDiretorio = new javax.swing.JMenuItem();
        menuImportarSubDiretorios = new javax.swing.JMenuItem();
        menuCompararDiretorios = new javax.swing.JMenuItem();
        menuCadastrarExtensaoArquivo = new javax.swing.JMenuItem();
        jSeparator1 = new javax.swing.JPopupMenu.Separator();
        menuExpandirDiretorios = new javax.swing.JMenuItem();
        menuColapsarDiretorios = new javax.swing.JMenuItem();
        menuExportarDiretoriosAbaAtiva = new javax.swing.JMenu();
        menuTXT = new javax.swing.JMenuItem();
        menuCSV = new javax.swing.JMenuItem();
        menuHTML = new javax.swing.JMenuItem();
        menuXML = new javax.swing.JMenuItem();
        menuSQL = new javax.swing.JMenuItem();
        menuImportarDiretoriosViaXML = new javax.swing.JMenuItem();
        menuGravarLogImportacao = new javax.swing.JCheckBoxMenuItem();
        menuVisao = new javax.swing.JMenu();
        menuMostrarOcultarArvoreDirAbaAtiva = new javax.swing.JMenuItem();
        menuMostrarOcultarListaItensPesquisados = new javax.swing.JMenuItem();
        lafMenu = new javax.swing.JMenu();
        menuIdioma = new javax.swing.JMenu();
        menuPortugues = new javax.swing.JRadioButtonMenuItem();
        menuIngles = new javax.swing.JRadioButtonMenuItem();
        menuEspanhol = new javax.swing.JRadioButtonMenuItem();
        menuFrances = new javax.swing.JRadioButtonMenuItem();
        menuItaliano = new javax.swing.JRadioButtonMenuItem();
        menuAlemao = new javax.swing.JRadioButtonMenuItem();
        menuJapones = new javax.swing.JRadioButtonMenuItem();
        menuCoreano = new javax.swing.JRadioButtonMenuItem();
        menuChinesTradicional = new javax.swing.JRadioButtonMenuItem();
        menuSobre = new javax.swing.JMenu();
        menuSobreCatalogador = new javax.swing.JMenuItem();

        java.util.ResourceBundle bundle = java.util.ResourceBundle.getBundle("recursos/hfsguardadiretorio_pt"); // NOI18N
        menuInformacoesDiretorioArquivo.setText(bundle.getString("FrmPrincipal.menuInformacoesDiretorioArquivo")); // NOI18N
        menuInformacoesDiretorioArquivo.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuInformacoesDiretorioArquivoActionPerformed(evt);
            }
        });
        menuPopup.add(menuInformacoesDiretorioArquivo);

        menuExcluirDiretorioSelecionado.setText(bundle.getString("FrmPrincipal.menuExcluirDiretorioSelecionado")); // NOI18N
        menuExcluirDiretorioSelecionado.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuExcluirDiretorioSelecionadoActionPerformed(evt);
            }
        });
        menuPopup.add(menuExcluirDiretorioSelecionado);

        menuExpandirDiretorios2.setText(bundle.getString("FrmPrincipal.menuExpandirDiretorios")); // NOI18N
        menuExpandirDiretorios2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuExpandirDiretorios2ActionPerformed(evt);
            }
        });
        menuPopup.add(menuExpandirDiretorios2);

        menuColapsarDiretorios2.setText(bundle.getString("FrmPrincipal.menuColapsarDiretorios")); // NOI18N
        menuColapsarDiretorios2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuColapsarDiretorios2ActionPerformed(evt);
            }
        });
        menuPopup.add(menuColapsarDiretorios2);
        menuPopup.add(jSeparator2);

        menuIncluirNovaAba2.setText(bundle.getString("FrmPrincipal.menuIncluirNovaAba")); // NOI18N
        menuIncluirNovaAba2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuIncluirNovaAba2ActionPerformed(evt);
            }
        });
        menuPopup.add(menuIncluirNovaAba2);

        menuAlterarNomeAbaAtiva2.setText(bundle.getString("FrmPrincipal.menuAlterarNomeAbaAtiva")); // NOI18N
        menuAlterarNomeAbaAtiva2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuAlterarNomeAbaAtiva2ActionPerformed(evt);
            }
        });
        menuPopup.add(menuAlterarNomeAbaAtiva2);

        menuExcluirAbaAtiva2.setText(bundle.getString("FrmPrincipal.menuExcluirAbaAtiva")); // NOI18N
        menuExcluirAbaAtiva2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuExcluirAbaAtiva2ActionPerformed(evt);
            }
        });
        menuPopup.add(menuExcluirAbaAtiva2);

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle(bundle.getString("FrmPrincipal.titulo")); // NOI18N
        setMinimumSize(new java.awt.Dimension(888, 472));
        setName("FrmPrincipal"); // NOI18N
        addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosing(java.awt.event.WindowEvent evt) {
                formWindowClosing(evt);
            }
            public void windowOpened(java.awt.event.WindowEvent evt) {
                formWindowOpened(evt);
            }
        });

        barraFerra.setFloatable(false);
        barraFerra.setRollover(true);

        btnImportarDiretorio.setMnemonic('I');
        btnImportarDiretorio.setText(bundle.getString("FrmPrincipal.btnImportarDiretorio")); // NOI18N
        btnImportarDiretorio.setBorder(null);
        btnImportarDiretorio.setFocusable(false);
        btnImportarDiretorio.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        btnImportarDiretorio.setMinimumSize(new java.awt.Dimension(109, 25));
        btnImportarDiretorio.setPreferredSize(new java.awt.Dimension(109, 25));
        btnImportarDiretorio.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        btnImportarDiretorio.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnImportarDiretorioActionPerformed(evt);
            }
        });
        barraFerra.add(btnImportarDiretorio);

        pb.setMinimum(1);
        pb.setMinimumSize(new java.awt.Dimension(385, 21));
        pb.setPreferredSize(new java.awt.Dimension(385, 21));
        barraFerra.add(pb);

        edtPesquisa.setToolTipText("");
        edtPesquisa.setMinimumSize(new java.awt.Dimension(276, 20));
        edtPesquisa.setPreferredSize(new java.awt.Dimension(276, 20));
        barraFerra.add(edtPesquisa);

        btnPesquisa.setMnemonic('P');
        btnPesquisa.setText(bundle.getString("FrmPrincipal.btnPesquisa")); // NOI18N
        btnPesquisa.setBorder(null);
        btnPesquisa.setFocusable(false);
        btnPesquisa.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        btnPesquisa.setMinimumSize(new java.awt.Dimension(75, 25));
        btnPesquisa.setPreferredSize(new java.awt.Dimension(75, 25));
        btnPesquisa.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        btnPesquisa.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnPesquisaActionPerformed(evt);
            }
        });
        barraFerra.add(btnPesquisa);

        getContentPane().add(barraFerra, java.awt.BorderLayout.NORTH);

        spPesquisa.setDividerLocation(280);
        spPesquisa.setOrientation(javax.swing.JSplitPane.VERTICAL_SPLIT);

        tabPanel.addChangeListener(new javax.swing.event.ChangeListener() {
            public void stateChanged(javax.swing.event.ChangeEvent evt) {
                tabPanelStateChanged(evt);
            }
        });
        spPesquisa.setTopComponent(tabPanel);
        spPesquisa.setRightComponent(scrollPesquisa);

        getContentPane().add(spPesquisa, java.awt.BorderLayout.CENTER);

        barraStatus.setPreferredSize(new java.awt.Dimension(630, 20));
        barraStatus.setLayout(new java.awt.BorderLayout());

        barraStatus1.setText(bundle.getString("FrmPrincipal.barraStatus1")); // NOI18N
        barraStatus1.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));
        barraStatus1.setMaximumSize(new java.awt.Dimension(300, 18));
        barraStatus1.setMinimumSize(new java.awt.Dimension(300, 18));
        barraStatus1.setPreferredSize(new java.awt.Dimension(300, 18));
        barraStatus.add(barraStatus1, java.awt.BorderLayout.WEST);

        barraStatus2.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));
        barraStatus.add(barraStatus2, java.awt.BorderLayout.CENTER);

        getContentPane().add(barraStatus, java.awt.BorderLayout.SOUTH);

        menuAba.setText(bundle.getString("FrmPrincipal.menuAba")); // NOI18N

        menuIncluirNovaAba.setText(bundle.getString("FrmPrincipal.menuIncluirNovaAba")); // NOI18N
        menuIncluirNovaAba.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuIncluirNovaAbaActionPerformed(evt);
            }
        });
        menuAba.add(menuIncluirNovaAba);

        menuAlterarNomeAbaAtiva.setText(bundle.getString("FrmPrincipal.menuAlterarNomeAbaAtiva")); // NOI18N
        menuAlterarNomeAbaAtiva.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuAlterarNomeAbaAtivaActionPerformed(evt);
            }
        });
        menuAba.add(menuAlterarNomeAbaAtiva);

        menuExcluirAbaAtiva.setText(bundle.getString("FrmPrincipal.menuExcluirAbaAtiva")); // NOI18N
        menuExcluirAbaAtiva.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuExcluirAbaAtivaActionPerformed(evt);
            }
        });
        menuAba.add(menuExcluirAbaAtiva);

        barraMenu.add(menuAba);

        menuDiretorio.setText(bundle.getString("FrmPrincipal.menuDiretorio")); // NOI18N

        menuImportarDiretorio.setText(bundle.getString("FrmPrincipal.menuImportarDiretorio")); // NOI18N
        menuImportarDiretorio.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuImportarDiretorioActionPerformed(evt);
            }
        });
        menuDiretorio.add(menuImportarDiretorio);

        menuImportarSubDiretorios.setText(bundle.getString("FrmPrincipal.menuImportarSubDiretorios")); // NOI18N
        menuImportarSubDiretorios.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuImportarSubDiretoriosActionPerformed(evt);
            }
        });
        menuDiretorio.add(menuImportarSubDiretorios);

        menuCompararDiretorios.setText(bundle.getString("FrmPrincipal.menuCompararDiretorios")); // NOI18N
        menuCompararDiretorios.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuCompararDiretoriosActionPerformed(evt);
            }
        });
        menuDiretorio.add(menuCompararDiretorios);

        menuCadastrarExtensaoArquivo.setText(bundle.getString("FrmPrincipal.menuCadastrarExtensaoArquivo")); // NOI18N
        menuCadastrarExtensaoArquivo.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuCadastrarExtensaoArquivoActionPerformed(evt);
            }
        });
        menuDiretorio.add(menuCadastrarExtensaoArquivo);
        menuDiretorio.add(jSeparator1);

        menuExpandirDiretorios.setText(bundle.getString("FrmPrincipal.menuExpandirDiretorios")); // NOI18N
        menuExpandirDiretorios.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuExpandirDiretoriosActionPerformed(evt);
            }
        });
        menuDiretorio.add(menuExpandirDiretorios);

        menuColapsarDiretorios.setText(bundle.getString("FrmPrincipal.menuColapsarDiretorios")); // NOI18N
        menuColapsarDiretorios.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuColapsarDiretoriosActionPerformed(evt);
            }
        });
        menuDiretorio.add(menuColapsarDiretorios);

        menuExportarDiretoriosAbaAtiva.setText(bundle.getString("FrmPrincipal.menuExportarDiretoriosAbaAtiva")); // NOI18N

        menuTXT.setText(bundle.getString("FrmPrincipal.menuTXT")); // NOI18N
        menuTXT.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuTXTActionPerformed(evt);
            }
        });
        menuExportarDiretoriosAbaAtiva.add(menuTXT);

        menuCSV.setText(bundle.getString("FrmPrincipal.menuCSV")); // NOI18N
        menuCSV.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuCSVActionPerformed(evt);
            }
        });
        menuExportarDiretoriosAbaAtiva.add(menuCSV);

        menuHTML.setText(bundle.getString("FrmPrincipal.menuHTML")); // NOI18N
        menuHTML.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuHTMLActionPerformed(evt);
            }
        });
        menuExportarDiretoriosAbaAtiva.add(menuHTML);

        menuXML.setText(bundle.getString("FrmPrincipal.menuXML")); // NOI18N
        menuXML.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuXMLActionPerformed(evt);
            }
        });
        menuExportarDiretoriosAbaAtiva.add(menuXML);

        menuSQL.setText(bundle.getString("FrmPrincipal.menuSQL")); // NOI18N
        menuSQL.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuSQLActionPerformed(evt);
            }
        });
        menuExportarDiretoriosAbaAtiva.add(menuSQL);

        menuDiretorio.add(menuExportarDiretoriosAbaAtiva);

        menuImportarDiretoriosViaXML.setText(bundle.getString("FrmPrincipal.menuImportarDiretoriosViaXML")); // NOI18N
        menuImportarDiretoriosViaXML.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuImportarDiretoriosViaXMLActionPerformed(evt);
            }
        });
        menuDiretorio.add(menuImportarDiretoriosViaXML);

        menuGravarLogImportacao.setText(bundle.getString("FrmPrincipal.menuGravarLogImportacao")); // NOI18N
        menuGravarLogImportacao.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuGravarLogImportacaoActionPerformed(evt);
            }
        });
        menuDiretorio.add(menuGravarLogImportacao);

        barraMenu.add(menuDiretorio);

        menuVisao.setText(bundle.getString("FrmPrincipal.menuVisao")); // NOI18N

        menuMostrarOcultarArvoreDirAbaAtiva.setText(bundle.getString("FrmPrincipal.menuMostrarOcultarArvoreDirAbaAtiva")); // NOI18N
        menuMostrarOcultarArvoreDirAbaAtiva.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuMostrarOcultarArvoreDirAbaAtivaActionPerformed(evt);
            }
        });
        menuVisao.add(menuMostrarOcultarArvoreDirAbaAtiva);

        menuMostrarOcultarListaItensPesquisados.setText(bundle.getString("FrmPrincipal.menuMostrarOcultarListaItensPesquisados")); // NOI18N
        menuMostrarOcultarListaItensPesquisados.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuMostrarOcultarListaItensPesquisadosActionPerformed(evt);
            }
        });
        menuVisao.add(menuMostrarOcultarListaItensPesquisados);

        barraMenu.add(menuVisao);

        lafMenu.setText(bundle.getString("LafMenu.laf_label")); // NOI18N
        barraMenu.add(lafMenu);

        menuIdioma.setText(bundle.getString("FrmPrincipal.menuIdioma")); // NOI18N

        grupoIdioma.add(menuPortugues);
        menuPortugues.setSelected(true);
        menuPortugues.setText(bundle.getString("FrmPrincipal.menuPortugues")); // NOI18N
        menuPortugues.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuPortuguesActionPerformed(evt);
            }
        });
        menuIdioma.add(menuPortugues);

        grupoIdioma.add(menuIngles);
        menuIngles.setText(bundle.getString("FrmPrincipal.menuIngles")); // NOI18N
        menuIngles.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuInglesActionPerformed(evt);
            }
        });
        menuIdioma.add(menuIngles);

        grupoIdioma.add(menuEspanhol);
        menuEspanhol.setText(bundle.getString("FrmPrincipal.menuEspanhol")); // NOI18N
        menuEspanhol.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuEspanholActionPerformed(evt);
            }
        });
        menuIdioma.add(menuEspanhol);

        grupoIdioma.add(menuFrances);
        menuFrances.setText(bundle.getString("FrmPrincipal.menuFrances")); // NOI18N
        menuFrances.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuFrancesActionPerformed(evt);
            }
        });
        menuIdioma.add(menuFrances);

        grupoIdioma.add(menuItaliano);
        menuItaliano.setText(bundle.getString("FrmPrincipal.menuItaliano")); // NOI18N
        menuItaliano.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuItalianoActionPerformed(evt);
            }
        });
        menuIdioma.add(menuItaliano);

        grupoIdioma.add(menuAlemao);
        menuAlemao.setText(bundle.getString("FrmPrincipal.menuAlemao")); // NOI18N
        menuAlemao.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuAlemaoActionPerformed(evt);
            }
        });
        menuIdioma.add(menuAlemao);

        grupoIdioma.add(menuJapones);
        menuJapones.setText(bundle.getString("FrmPrincipal.menuJapones")); // NOI18N
        menuJapones.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuJaponesActionPerformed(evt);
            }
        });
        menuIdioma.add(menuJapones);

        grupoIdioma.add(menuCoreano);
        menuCoreano.setText(bundle.getString("FrmPrincipal.menuCoreano")); // NOI18N
        menuCoreano.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuCoreanoActionPerformed(evt);
            }
        });
        menuIdioma.add(menuCoreano);

        grupoIdioma.add(menuChinesTradicional);
        menuChinesTradicional.setText(bundle.getString("FrmPrincipal.menuChinesTradicional")); // NOI18N
        menuChinesTradicional.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuChinesTradicionalActionPerformed(evt);
            }
        });
        menuIdioma.add(menuChinesTradicional);

        barraMenu.add(menuIdioma);

        menuSobre.setText(bundle.getString("FrmPrincipal.menuSobre")); // NOI18N

        menuSobreCatalogador.setText(bundle.getString("FrmPrincipal.menuSobreCatalogador")); // NOI18N
        menuSobreCatalogador.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                menuSobreCatalogadorActionPerformed(evt);
            }
        });
        menuSobre.add(menuSobreCatalogador);

        barraMenu.add(menuSobre);

        setJMenuBar(barraMenu);

        setSize(new java.awt.Dimension(924, 526));
        setLocationRelativeTo(null);
    }// </editor-fold>//GEN-END:initComponents

    private void menuIncluirNovaAbaActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuIncluirNovaAbaActionPerformed
        try {
            catalogador.IncluirNovaAba();
        } catch (SQLException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        }
    }//GEN-LAST:event_menuIncluirNovaAbaActionPerformed

    private void menuAlterarNomeAbaAtivaActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuAlterarNomeAbaAtivaActionPerformed
        try {
            catalogador.AlterarNomeAbaAtiva(frmPrincipalProgresso);
        } catch (SQLException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        }
    }//GEN-LAST:event_menuAlterarNomeAbaAtivaActionPerformed

    private void menuExcluirAbaAtivaActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuExcluirAbaAtivaActionPerformed
        try {
            catalogador.ExcluirAbaAtiva(frmPrincipalProgresso);
        } catch (SQLException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        }
    }//GEN-LAST:event_menuExcluirAbaAtivaActionPerformed

    private void menuImportarDiretorioActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuImportarDiretorioActionPerformed
        try {
            catalogador.ComecaImportacao(false, frmPrincipalProgresso);
        } catch (SQLException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        }
    }//GEN-LAST:event_menuImportarDiretorioActionPerformed

    private void menuImportarSubDiretoriosActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuImportarSubDiretoriosActionPerformed
        try {
            catalogador.ComecaImportacao(true, frmPrincipalProgresso);
        } catch (SQLException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        }
    }//GEN-LAST:event_menuImportarSubDiretoriosActionPerformed

    private void menuCompararDiretoriosActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuCompararDiretoriosActionPerformed
        FrmCompararDiretorio frmComparar = new FrmCompararDiretorio(this, true);
        frmComparar.setVisible(true);
    }//GEN-LAST:event_menuCompararDiretoriosActionPerformed

    private void menuCadastrarExtensaoArquivoActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuCadastrarExtensaoArquivoActionPerformed
        FrmCadExtensao frmCadExtensao = new FrmCadExtensao(this, true);
        frmCadExtensao.setVisible(true);
    }//GEN-LAST:event_menuCadastrarExtensaoArquivoActionPerformed

    private void menuExpandirDiretoriosActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuExpandirDiretoriosActionPerformed
        catalogador.getArvoreAtual().expandeTodos(true);
    }//GEN-LAST:event_menuExpandirDiretoriosActionPerformed

    private void menuColapsarDiretoriosActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuColapsarDiretoriosActionPerformed
        catalogador.getArvoreAtual().expandeTodos(false);
    }//GEN-LAST:event_menuColapsarDiretoriosActionPerformed

    private void menuTXTActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuTXTActionPerformed
        try {
            catalogador.ExportarArquivo(teTXT, frmPrincipalProgresso);
        } catch (SQLException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        }
    }//GEN-LAST:event_menuTXTActionPerformed

    private void menuCSVActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuCSVActionPerformed
        try {
            catalogador.ExportarArquivo(teCSV, frmPrincipalProgresso);
        } catch (SQLException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        }
    }//GEN-LAST:event_menuCSVActionPerformed

    private void menuHTMLActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuHTMLActionPerformed
        try {
            catalogador.ExportarArquivo(teHTML, frmPrincipalProgresso);
        } catch (SQLException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        }
    }//GEN-LAST:event_menuHTMLActionPerformed

    private void menuXMLActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuXMLActionPerformed
        try {
            catalogador.ExportarArquivo(teXML, frmPrincipalProgresso);
        } catch (SQLException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        }
    }//GEN-LAST:event_menuXMLActionPerformed

    private void menuSQLActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuSQLActionPerformed
        try {
            catalogador.ExportarArquivo(teSQL, frmPrincipalProgresso);
        } catch (SQLException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        }
    }//GEN-LAST:event_menuSQLActionPerformed

    private void menuImportarDiretoriosViaXMLActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuImportarDiretoriosViaXMLActionPerformed
        StringList log = new StringList();
        try {
            catalogador.ImportarArquivo(log, frmPrincipalProgresso);
        } catch (IOException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        } catch (SQLException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        }
    }//GEN-LAST:event_menuImportarDiretoriosViaXMLActionPerformed

    private void menuGravarLogImportacaoActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuGravarLogImportacaoActionPerformed
        //menuGravarLogImportacao.setSelected(menuGravarLogImportacao.isSelected());
    }//GEN-LAST:event_menuGravarLogImportacaoActionPerformed

    private void menuMostrarOcultarArvoreDirAbaAtivaActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuMostrarOcultarArvoreDirAbaAtivaActionPerformed
        catalogador.mostrarOcultarArvore();
    }//GEN-LAST:event_menuMostrarOcultarArvoreDirAbaAtivaActionPerformed

    private void menuMostrarOcultarListaItensPesquisadosActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuMostrarOcultarListaItensPesquisadosActionPerformed
        scrollPesquisa.setVisible(!scrollPesquisa.isVisible());
        if (scrollPesquisa.isVisible()) {
            spPesquisa.setDividerLocation(280);
        } else {
            spPesquisa.setDividerLocation(0);
        }
    }//GEN-LAST:event_menuMostrarOcultarListaItensPesquisadosActionPerformed

    private void btnImportarDiretorioActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnImportarDiretorioActionPerformed
        menuImportarDiretorioActionPerformed(evt);
    }//GEN-LAST:event_btnImportarDiretorioActionPerformed

    private void btnPesquisaActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnPesquisaActionPerformed
        catalogador.Pesquisar();
    }//GEN-LAST:event_btnPesquisaActionPerformed

    private void formWindowOpened(java.awt.event.WindowEvent evt) {//GEN-FIRST:event_formWindowOpened
        setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
        this.update(this.getGraphics());
        
        this.setIdiomaPadrao(Rotinas.getParams().getLocalidadeLingua());
        setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
    }//GEN-LAST:event_formWindowOpened

    private void formWindowClosing(java.awt.event.WindowEvent evt) {//GEN-FIRST:event_formWindowClosing
        try {
            Rotinas.Desconectar();
        } catch (SQLException e) {
                Dialogo.mensagemErro(this, "FrmPrincipal.ErroDesconectar", e
                                .getLocalizedMessage());
        }
    }//GEN-LAST:event_formWindowClosing

    private void tabPanelStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_tabPanelStateChanged
        if (catalogador != null) {
            catalogador.tabPanelMudou();
        }
    }//GEN-LAST:event_tabPanelStateChanged

    private void menuSobreCatalogadorActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuSobreCatalogadorActionPerformed
        FrmSobre frmSobre = new FrmSobre(this, true);
        frmSobre.setVisible(true);
    }//GEN-LAST:event_menuSobreCatalogadorActionPerformed

    private void menuInformacoesDiretorioArquivoActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuInformacoesDiretorioArquivoActionPerformed
        FrmInfoDiretorio frmInfo;
        Tabela tabela = catalogador.getTabelaAtual();
        if (tabela.getSelectedRowCount() > 0) {
            frmInfo = new FrmInfoDiretorio(this, true);
            Aba aba = catalogador.getAbaSelecionada();
            Diretorio dir = tabela.getLinhaSelecionada(false);
            dir.getAba().setNome(aba.getNome());
            frmInfo.setDiretorio(dir);
            frmInfo.setVisible(true);
        }
    }//GEN-LAST:event_menuInformacoesDiretorioArquivoActionPerformed

    private void menuPortuguesActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuPortuguesActionPerformed
        catalogador.mudarLingua("pt");
    }//GEN-LAST:event_menuPortuguesActionPerformed

    private void menuInglesActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuInglesActionPerformed
        catalogador.mudarLingua("en");
    }//GEN-LAST:event_menuInglesActionPerformed

    private void menuEspanholActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuEspanholActionPerformed
        catalogador.mudarLingua("es");
    }//GEN-LAST:event_menuEspanholActionPerformed

    private void menuFrancesActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuFrancesActionPerformed
        catalogador.mudarLingua("fr");
    }//GEN-LAST:event_menuFrancesActionPerformed

    private void menuItalianoActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuItalianoActionPerformed
        catalogador.mudarLingua("it");
    }//GEN-LAST:event_menuItalianoActionPerformed

    private void menuAlemaoActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuAlemaoActionPerformed
        catalogador.mudarLingua("de");
    }//GEN-LAST:event_menuAlemaoActionPerformed

    private void menuJaponesActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuJaponesActionPerformed
        catalogador.mudarLingua("ja");
    }//GEN-LAST:event_menuJaponesActionPerformed

    private void menuCoreanoActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuCoreanoActionPerformed
        catalogador.mudarLingua("ko");
    }//GEN-LAST:event_menuCoreanoActionPerformed

    private void menuChinesTradicionalActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuChinesTradicionalActionPerformed
        catalogador.mudarLingua("zh");
    }//GEN-LAST:event_menuChinesTradicionalActionPerformed

    private void menuExcluirDiretorioSelecionadoActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuExcluirDiretorioSelecionadoActionPerformed
        try {
            catalogador.ExcluirDiretorioSelecionado(frmPrincipalProgresso);
        } catch (SQLException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        }
    }//GEN-LAST:event_menuExcluirDiretorioSelecionadoActionPerformed

    private void menuExpandirDiretorios2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuExpandirDiretorios2ActionPerformed
        this.menuExpandirDiretoriosActionPerformed(evt);
    }//GEN-LAST:event_menuExpandirDiretorios2ActionPerformed

    private void menuColapsarDiretorios2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuColapsarDiretorios2ActionPerformed
        this.menuColapsarDiretoriosActionPerformed(evt);
    }//GEN-LAST:event_menuColapsarDiretorios2ActionPerformed

    private void menuIncluirNovaAba2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuIncluirNovaAba2ActionPerformed
        this.menuIncluirNovaAbaActionPerformed(evt);
    }//GEN-LAST:event_menuIncluirNovaAba2ActionPerformed

    private void menuAlterarNomeAbaAtiva2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuAlterarNomeAbaAtiva2ActionPerformed
        this.menuAlterarNomeAbaAtivaActionPerformed(evt);
    }//GEN-LAST:event_menuAlterarNomeAbaAtiva2ActionPerformed

    private void menuExcluirAbaAtiva2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuExcluirAbaAtiva2ActionPerformed
        this.menuExcluirAbaAtivaActionPerformed(evt);
    }//GEN-LAST:event_menuExcluirAbaAtiva2ActionPerformed

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JToolBar barraFerra;
    private javax.swing.JMenuBar barraMenu;
    private javax.swing.JPanel barraStatus;
    public javax.swing.JLabel barraStatus1;
    public javax.swing.JLabel barraStatus2;
    private javax.swing.JButton btnImportarDiretorio;
    private javax.swing.JButton btnPesquisa;
    public javax.swing.JTextField edtPesquisa;
    private javax.swing.ButtonGroup grupoIdioma;
    private javax.swing.JPopupMenu.Separator jSeparator1;
    private javax.swing.JPopupMenu.Separator jSeparator2;
    public javax.swing.JMenu lafMenu;
    private javax.swing.JMenu menuAba;
    private javax.swing.JRadioButtonMenuItem menuAlemao;
    private javax.swing.JMenuItem menuAlterarNomeAbaAtiva;
    private javax.swing.JMenuItem menuAlterarNomeAbaAtiva2;
    private javax.swing.JMenuItem menuCSV;
    private javax.swing.JMenuItem menuCadastrarExtensaoArquivo;
    private javax.swing.JRadioButtonMenuItem menuChinesTradicional;
    private javax.swing.JMenuItem menuColapsarDiretorios;
    private javax.swing.JMenuItem menuColapsarDiretorios2;
    private javax.swing.JMenuItem menuCompararDiretorios;
    private javax.swing.JRadioButtonMenuItem menuCoreano;
    private javax.swing.JMenu menuDiretorio;
    private javax.swing.JRadioButtonMenuItem menuEspanhol;
    private javax.swing.JMenuItem menuExcluirAbaAtiva;
    private javax.swing.JMenuItem menuExcluirAbaAtiva2;
    private javax.swing.JMenuItem menuExcluirDiretorioSelecionado;
    private javax.swing.JMenuItem menuExpandirDiretorios;
    private javax.swing.JMenuItem menuExpandirDiretorios2;
    private javax.swing.JMenu menuExportarDiretoriosAbaAtiva;
    private javax.swing.JRadioButtonMenuItem menuFrances;
    public javax.swing.JCheckBoxMenuItem menuGravarLogImportacao;
    private javax.swing.JMenuItem menuHTML;
    private javax.swing.JMenu menuIdioma;
    private javax.swing.JMenuItem menuImportarDiretorio;
    private javax.swing.JMenuItem menuImportarDiretoriosViaXML;
    private javax.swing.JMenuItem menuImportarSubDiretorios;
    private javax.swing.JMenuItem menuIncluirNovaAba;
    private javax.swing.JMenuItem menuIncluirNovaAba2;
    private javax.swing.JMenuItem menuInformacoesDiretorioArquivo;
    private javax.swing.JRadioButtonMenuItem menuIngles;
    private javax.swing.JRadioButtonMenuItem menuItaliano;
    private javax.swing.JRadioButtonMenuItem menuJapones;
    private javax.swing.JMenuItem menuMostrarOcultarArvoreDirAbaAtiva;
    private javax.swing.JMenuItem menuMostrarOcultarListaItensPesquisados;
    public javax.swing.JPopupMenu menuPopup;
    private javax.swing.JRadioButtonMenuItem menuPortugues;
    private javax.swing.JMenuItem menuSQL;
    private javax.swing.JMenu menuSobre;
    private javax.swing.JMenuItem menuSobreCatalogador;
    private javax.swing.JMenuItem menuTXT;
    private javax.swing.JMenu menuVisao;
    private javax.swing.JMenuItem menuXML;
    public javax.swing.JProgressBar pb;
    public javax.swing.JScrollPane scrollPesquisa;
    public javax.swing.JSplitPane spPesquisa;
    public javax.swing.JTabbedPane tabPanel;
    // End of variables declaration//GEN-END:variables

    private void setIdiomaPadrao(String lingua) {
        switch (lingua) {
            case "pt":
                menuPortugues.setSelected(true);
                break;
            case "en":
                menuIngles.setSelected(true);
                break;
            case "es":
                menuEspanhol.setSelected(true);
                break;
            case "fr":
                menuFrances.setSelected(true);
                break;
            case "it":
                menuItaliano.setSelected(true);
                break;
            case "de":
                menuAlemao.setSelected(true);
                break;
            case "ja":
                menuJapones.setSelected(true);
                break;
            case "ko":
                menuCoreano.setSelected(true);
                break;
            case "zh":
                menuChinesTradicional.setSelected(true);
                break;
        }
    }

    public void mudarLingua() {
        setTitle(Rotinas.getRecurso("FrmPrincipal.titulo"));
        barraStatus1.setText(Rotinas.getRecurso("FrmPrincipal.barraStatus1"));
        btnImportarDiretorio.setText(
                Rotinas.getRecurso("FrmPrincipal.btnImportarDiretorio"));
        btnPesquisa.setText(Rotinas.getRecurso("FrmPrincipal.btnPesquisa"));
        menuAba.setText(Rotinas.getRecurso("FrmPrincipal.menuAba"));
        menuIncluirNovaAba.setText(Rotinas
                .getRecurso("FrmPrincipal.menuIncluirNovaAba"));
        menuAlterarNomeAbaAtiva.setText(
                Rotinas.getRecurso("FrmPrincipal.menuAlterarNomeAbaAtiva"));
        menuExcluirAbaAtiva.setText(
                Rotinas.getRecurso("FrmPrincipal.menuExcluirAbaAtiva"));
                
        menuDiretorio.setText(Rotinas.getRecurso("FrmPrincipal.menuDiretorio"));
        menuImportarDiretorio.setText(
                Rotinas.getRecurso("FrmPrincipal.menuImportarDiretorio"));
        menuImportarSubDiretorios.setText(
                Rotinas.getRecurso("FrmPrincipal.menuImportarSubDiretorios"));
        menuCompararDiretorios.setText(
                Rotinas.getRecurso("FrmPrincipal.menuCompararDiretorios"));
        menuCadastrarExtensaoArquivo.setText(
                Rotinas.getRecurso("FrmPrincipal.menuCadastrarExtensaoArquivo"));
        menuExpandirDiretorios.setText(
                Rotinas.getRecurso("FrmPrincipal.menuExpandirDiretorios"));
        menuColapsarDiretorios.setText(
                Rotinas.getRecurso("FrmPrincipal.menuColapsarDiretorios"));
        menuExportarDiretoriosAbaAtiva.setText(
                Rotinas.getRecurso("FrmPrincipal.menuExportarDiretoriosAbaAtiva"));
        menuImportarDiretoriosViaXML.setText(
                Rotinas.getRecurso("FrmPrincipal.menuImportarDiretoriosViaXML"));
        menuGravarLogImportacao.setText(
                Rotinas.getRecurso("FrmPrincipal.menuGravarLogImportacao"));
                
        menuVisao.setText(Rotinas.getRecurso("FrmPrincipal.menuVisao"));
        menuMostrarOcultarArvoreDirAbaAtiva.setText(
                Rotinas.getRecurso("FrmPrincipal.menuMostrarOcultarArvoreDirAbaAtiva"));
        menuMostrarOcultarListaItensPesquisados.setText(
                Rotinas.getRecurso("FrmPrincipal.menuMostrarOcultarListaItensPesquisados"));
                
        menuIdioma.setText(Rotinas.getRecurso("FrmPrincipal.menuIdioma"));
        menuPortugues.setText(Rotinas.getRecurso("FrmPrincipal.menuPortugues"));
        menuIngles.setText(Rotinas.getRecurso("FrmPrincipal.menuIngles"));
        menuEspanhol.setText(Rotinas.getRecurso("FrmPrincipal.menuEspanhol"));
        menuFrances.setText(Rotinas.getRecurso("FrmPrincipal.menuFrances"));
        menuItaliano.setText(Rotinas.getRecurso("FrmPrincipal.menuItaliano"));
        menuAlemao.setText(Rotinas.getRecurso("FrmPrincipal.menuAlemao"));
        menuJapones.setText(Rotinas.getRecurso("FrmPrincipal.menuJapones"));
        menuCoreano.setText(Rotinas.getRecurso("FrmPrincipal.menuCoreano"));
        menuChinesTradicional.setText(Rotinas
                .getRecurso("FrmPrincipal.menuChinesTradicional"));
        lafMenu.setMnemonic(Rotinas.getMnemonico("LafMenu.laf_mnemonic"));
        lafMenu.getAccessibleContext().setAccessibleDescription(
                Rotinas.getRecurso("LafMenu.laf_accessible_description"));
        
        menuSobre.setText(Rotinas.getRecurso("FrmPrincipal.menuSobre"));
        menuSobreCatalogador.setText(
                Rotinas.getRecurso("FrmPrincipal.menuSobreCatalogador"));
    }
    
    public Catalogador getCatalogador(){
        return catalogador;
    }
}
