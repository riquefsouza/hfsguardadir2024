package hfsguardadir.objetosgui;

import hfsguardadir.comum.Rotinas;
import hfsguardadir.objetos.Extensao;
import hfsguardadir.objetosbo.ExtensaoBO;

import java.awt.Component;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Vector;

import javax.swing.ImageIcon;
import javax.swing.JTable;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.DefaultTableModel;

public class TabelaExtensao extends JTable {

    private static final long serialVersionUID = 9849365060290773L;

    public TabelaExtensao(ArrayList<Extensao> extensaoLista) {
        super();
        construirModeloTabela(extensaoLista);
        this.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
        this.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        this.setFillsViewportHeight(true);       
        this.getColumnModel().getColumn(0).setPreferredWidth(100);

        DefaultTableCellRenderer dtcr = new DefaultTableCellRenderer() {
            private static final long serialVersionUID = -1139006797853979939L;

            @Override
            public Component getTableCellRendererComponent(JTable table,
                    Object value, boolean isSelected, boolean hasFocus,
                    int row, int column) {

                if (column == 1) {
                    setVisible(false);
                    String nome = (String) getValueAt(row, 0);                    
                    Extensao extensao = ExtensaoBO.getInstancia().
                            pegaExtensaoPorOrdem(extensaoLista, row+1);
                    if (extensao!=null) {                                                
                        if (extensao.getGif16()!=null && 
                                extensao.getNome().equals(nome)) {
                            setIcon(new ImageIcon(extensao.getGif16()));
                        } else {
                            setIcon(null);
                        }
                    }
                    value = "";
                }
                return super.getTableCellRendererComponent(table, value,
                        isSelected, hasFocus, row, column);
            }
        };
        this.getColumnModel().getColumn(1).setCellRenderer(dtcr);

        this.getSelectionModel().addListSelectionListener(
                new ListSelectionListener() {
                    @Override
                    public void valueChanged(ListSelectionEvent evt) {
                        selecaoValorMudou(evt);
                    }
                });
    }

    private void selecaoValorMudou(ListSelectionEvent evt) {
        this.scrollRectToVisible(this.getCellRect(this.getSelectedRow(), 0,
                true));
    }

    private Vector<String> modeloTabelaColunas() {
        String[] colNomes = new String[]{
            Rotinas.getRecurso("FrmCadExtensao.extensao"),
            Rotinas.getRecurso("FrmCadExtensao.icone")};
        Vector<String> ColunasNome = new Vector<>(colNomes.length);

        ColunasNome.addAll(Arrays.asList(colNomes));
        return ColunasNome;
    }

    private Vector<Vector<String>> modeloTabelaLinhas(
            ArrayList<Extensao> lista) {
        Vector<Vector<String>> Linhas = new Vector<>();        
        for (Extensao Campos : lista) {
            Vector<String> novaLinha = new Vector<>();
            novaLinha.add(Campos.getNome());
            novaLinha.add(Campos.getNome());
            Linhas.add(novaLinha);
        }
        return Linhas;
    }

    private void construirModeloTabela(ArrayList<Extensao> lista) {
        DefaultTableModel dtm = new DefaultTableModel(
                modeloTabelaLinhas(lista), modeloTabelaColunas()) {
            private static final long serialVersionUID = -1354365527378982821L;

            boolean[] canEdit = new boolean[]{false, false};

            @Override
            public boolean isCellEditable(int rowIndex, int columnIndex) {
                return canEdit[columnIndex];
            }
        };
        setModel(dtm);
    }

}
