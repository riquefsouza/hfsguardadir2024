/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package hfsguardadir.gui;

import hfsguardadir.comum.Rotinas;
import hfsguardadir.objetos.PropriedadeSistema;
import java.util.Vector;
import java.util.Arrays;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableModel;
import javax.swing.table.TableRowSorter;

public class FrmSobre extends javax.swing.JDialog {

    private static final long serialVersionUID = 1L;
    
	private DefaultTableModel modelo;
    private int nMaxValor, nMaxNome;
        
    /**
     * Creates new form FrmSobre
     */
    public FrmSobre(java.awt.Frame parent, boolean modal) {
        super(parent, modal);
        construirModeloTabela();
        initComponents();
        mudarLingua();
        tabelaPropriedades.getSelectionModel().setSelectionInterval(0, 0);
        
        tabelaPropriedades.getColumnModel().getColumn(0).setPreferredWidth(
        nMaxNome*6);        
        tabelaPropriedades.getColumnModel().getColumn(1).setPreferredWidth(
        nMaxValor*5);        
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        panelSuperior = new javax.swing.JPanel();
        jLabel1 = new javax.swing.JLabel();
        jLabel2 = new javax.swing.JLabel();
        jLabel3 = new javax.swing.JLabel();
        jLabel4 = new javax.swing.JLabel();
        panelRolagem = new javax.swing.JScrollPane();
        tabelaPropriedades = new javax.swing.JTable();
        panelBotao = new javax.swing.JPanel();
        btnOk = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);
        java.util.ResourceBundle bundle = java.util.ResourceBundle.getBundle("recursos/hfsguardadiretorio_pt"); // NOI18N
        setTitle(bundle.getString("FrmSobre.titulo")); // NOI18N
        setModal(true);
        setName("FrmSobre"); // NOI18N
        setResizable(false);

        panelSuperior.setLayout(new java.awt.GridLayout(4, 1));

        jLabel1.setFont(new java.awt.Font("Tahoma", 1, 14)); // NOI18N
        jLabel1.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jLabel1.setText(bundle.getString("FrmSobre.label1")); // NOI18N
        panelSuperior.add(jLabel1);

        jLabel2.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jLabel2.setText(bundle.getString("FrmSobre.label2")); // NOI18N
        panelSuperior.add(jLabel2);

        jLabel3.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jLabel3.setText(bundle.getString("FrmSobre.label3")); // NOI18N
        panelSuperior.add(jLabel3);

        jLabel4.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jLabel4.setText(bundle.getString("FrmSobre.label4")); // NOI18N
        panelSuperior.add(jLabel4);

        getContentPane().add(panelSuperior, java.awt.BorderLayout.NORTH);

        tabelaPropriedades.setModel(modelo);
        tabelaPropriedades.setAutoResizeMode(javax.swing.JTable.AUTO_RESIZE_OFF);
        tabelaPropriedades.setRowSorter(new TableRowSorter<TableModel>(tabelaPropriedades.getModel()));
        tabelaPropriedades.setSelectionMode(javax.swing.ListSelectionModel.SINGLE_SELECTION);
        panelRolagem.setViewportView(tabelaPropriedades);

        getContentPane().add(panelRolagem, java.awt.BorderLayout.CENTER);

        btnOk.setMnemonic('O');
        btnOk.setText("Ok");
        btnOk.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnOkActionPerformed(evt);
            }
        });
        panelBotao.add(btnOk);

        getContentPane().add(panelBotao, java.awt.BorderLayout.SOUTH);

        pack();
        setLocationRelativeTo(null);
    }// </editor-fold>//GEN-END:initComponents

    private void btnOkActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnOkActionPerformed
        this.dispose();
    }//GEN-LAST:event_btnOkActionPerformed

    // Variables declaration - do not modify//GEN-BEGIN:variables
    javax.swing.JButton btnOk;
    javax.swing.JLabel jLabel1;
    javax.swing.JLabel jLabel2;
    javax.swing.JLabel jLabel3;
    javax.swing.JLabel jLabel4;
    javax.swing.JPanel panelBotao;
    javax.swing.JScrollPane panelRolagem;
    javax.swing.JPanel panelSuperior;
    javax.swing.JTable tabelaPropriedades;
    // End of variables declaration//GEN-END:variables

    private Vector<String> modeloTabelaColunas() {
        String[] colNomes = new String[]{
            Rotinas.getRecurso("FrmSobre.Propriedade"),
            Rotinas.getRecurso("FrmSobre.Valor")};
        Vector<String> ColunasNome = new Vector<>(colNomes.length);

        ColunasNome.addAll(Arrays.asList(colNomes));
        return ColunasNome;
    }

    private Vector<Vector<String>> modeloTabelaLinhas() {
        Vector<Vector<String>> Linhas = new Vector<>();
        PropriedadeSistema[] propsSistema = Rotinas.getPropriedadesSistema();
        for (PropriedadeSistema Campos : propsSistema) {
            Vector<String> novaLinha = new Vector<>();
            novaLinha.add(Campos.getNome());
            novaLinha.add(Campos.getValor());
            Linhas.add(novaLinha);
            nMaxNome = Math.max(nMaxNome, Campos.getNome().length());
            nMaxValor = Math.max(nMaxValor, Campos.getValor().length());
        }

        return Linhas;
    }

    private void construirModeloTabela() {
        modelo = new DefaultTableModel(modeloTabelaLinhas(), 
                modeloTabelaColunas()) {
            private static final long serialVersionUID = -1354365527378982821L;

            boolean[] canEdit = new boolean[]{false, false};

            @Override
            public boolean isCellEditable(int rowIndex, int columnIndex) {
                return canEdit[columnIndex];
            }
        };        
    }
    
    private void mudarLingua() {
	setTitle(Rotinas.getRecurso("FrmSobre.titulo"));
	jLabel1.setText(Rotinas.getRecurso("FrmSobre.label1"));
	jLabel2.setText(Rotinas.getRecurso("FrmSobre.label2"));
	jLabel3.setText(Rotinas.getRecurso("FrmSobre.label3"));
	jLabel4.setText(Rotinas.getRecurso("FrmSobre.label4"));
    }
}
