package hfsguardadir.objetosgui;

import hfsguardadir.comum.ICatalogador;
import hfsguardadir.comum.Rotinas;
import hfsguardadir.objetos.Diretorio;
import hfsguardadir.objetos.Extensao;
import hfsguardadir.objetosbo.ExtensaoBO;

import java.awt.Color;
import java.awt.Component;
import java.awt.Rectangle;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;
import java.util.Vector;
import javax.swing.ImageIcon;

import javax.swing.JProgressBar;
import javax.swing.JTable;
import javax.swing.JViewport;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.DefaultTableColumnModel;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableCellRenderer;
import javax.swing.table.TableColumn;
import javax.swing.table.TableModel;
import javax.swing.table.TableRowSorter;

public class Tabela extends JTable {

    private static final long serialVersionUID = 7875156411342009309L;

    private boolean bTabelaDir;

    private boolean sombrearLinhas;

    private boolean sombrearColunas;
    
    private ICatalogador catalogador;

    public Tabela(ICatalogador catalogador, ArrayList<Diretorio> diretorios,
            ArrayList<Extensao> extensoes,
            JProgressBar barraProgresso, boolean bTabelaDir) {
        super();
        this.catalogador = catalogador;
        this.bTabelaDir = bTabelaDir;
        this.sombrearLinhas = false;
        this.sombrearColunas = false;
        
        DefaultTableModel dtm = modeloTabela(diretorios, barraProgresso, bTabelaDir);
        this.setModel(dtm);
        this.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
        this.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        this.setFillsViewportHeight(true);
        acomodaColunas(this, 10);
        acomodaLinhas(this, 0);

        DefaultTableCellRenderer dtcr = new DefaultTableCellRenderer() {
            private static final long serialVersionUID = -1139006797853979939L;

            public Component getTableCellRendererComponent(JTable table,
                    Object value, boolean isSelected, boolean hasFocus,
                    int row, int column) {

                if (column == 0) {
                    setVisible(false);
                    String nome = (String) getValueAt(row, 0);
                    String tipo = (String) getValueAt(row, 2);
                    setIconePorExtensao(this, row, nome.toLowerCase(), tipo);
                }
                return super.getTableCellRendererComponent(table, value,
                        isSelected, hasFocus, row, column);
            }

            private void setIconePorExtensao(DefaultTableCellRenderer render,
                    int linha, String nome, String tipo) {

                String ext = nome.substring(nome.lastIndexOf('.') + 1);
                Extensao extensao = ExtensaoBO.getInstancia().
                        pegaExtensaoPorNome(extensoes, ext, tipo);
                if (extensao!=null) {
                    if (extensao.getGif16()!=null) {
                        setIcon(new ImageIcon(extensao.getGif16()));
                    } else {
                        setIcon(null);
                    }
                }
            }
        };
        this.getColumnModel().getColumn(0).setCellRenderer(dtcr);

        this.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                mouseClicou(e);
            }
        });

        this.getSelectionModel().addListSelectionListener(
                new ListSelectionListener() {
                    @Override
                    public void valueChanged(ListSelectionEvent evt) {
                        selecaoValorMudou(evt);
                    }
                });

        TableRowSorter<DefaultTableModel> sorter = new TableRowSorter<DefaultTableModel>(dtm);
        this.setRowSorter(sorter);
    }

    @Override
    public boolean isCellEditable(int rowIndex, int vColIndex) {
        return false;
    }

    private void selecaoValorMudou(ListSelectionEvent evt) {
        // this.scrollRectToVisible(this.getCellRect(this.getSelectedRow(), 0,
        // true));
        //scrollToCenter(this.getSelectedRow(), 0);
    }

    private void mouseClicou(MouseEvent evt) {
        JTable tabela = (JTable) evt.getSource();
        TableModel modelo = tabela.getModel();
        if (tabela.getSelectedRow() >= 0) {
            String nome = (String) modelo
                    .getValueAt(tabela.getSelectedRow(), 0);
            String tipo = (String) modelo
                    .getValueAt(tabela.getSelectedRow(), 2);

            if (bTabelaDir) {
                if (evt.getClickCount() == 2) {
                    catalogador.DuploCliqueLista(nome, tipo);
                }
            } else {
                if (evt.getClickCount() == 1) {
                    String nomeAba = (String) modelo.getValueAt(tabela
                            .getSelectedRow(), 6);
                    String caminho = (String) modelo.getValueAt(tabela
                            .getSelectedRow(), 5);
                    catalogador.EncontrarItemLista(nomeAba, nome, caminho);
                }
            }
        }
    }

    public int encontrarLinha(String nome) {
        String slinha;
        int nlinha = 0;
        for (int i = 0; i < this.getRowCount(); i++) {
            slinha = (String) this.getValueAt(i, 0);
            if (slinha.equals(nome)) {
                nlinha = i;
                break;
            }
        }
        return nlinha;
    }

    public Diretorio getLinhaSelecionada(boolean bTabelaDir){
        Diretorio dir = null;
        
        if (this.getSelectedRowCount() > 0) {        
            dir = new Diretorio();
            dir.setNome((String)this.getValueAt(this.getSelectedRow(), 0));
            dir.setTamanhoFormatado((String)this.getValueAt(this.getSelectedRow(), 1));
            dir.getTipo().setNome((String)this.getValueAt(this.getSelectedRow(), 2));
            dir.setModificadoFormatado((String)this.getValueAt(this.getSelectedRow(), 3));
            dir.setAtributos((String)this.getValueAt(this.getSelectedRow(), 4));
            dir.setCaminho((String)this.getValueAt(this.getSelectedRow(), 5));
            if (bTabelaDir) {                
                dir.getAba().setNome((String)this.getValueAt(this.getSelectedRow(), 6));
            }
        }
        
        return dir;
    }
    
    private void acomodaColuna(JTable table, int vColIndex, int margin) {
        DefaultTableColumnModel colModel = (DefaultTableColumnModel) table
                .getColumnModel();
        TableColumn col = colModel.getColumn(vColIndex);
        int width;

        // pega a largura do cabeçalho da coluna
        TableCellRenderer renderer = col.getHeaderRenderer();
        if (renderer == null) {
            renderer = table.getTableHeader().getDefaultRenderer();
        }
        Component comp = renderer.getTableCellRendererComponent(table, col
                .getHeaderValue(), false, false, 0, 0);
        width = comp.getPreferredSize().width;

        // pega a largura maxima do dado da coluna
        for (int r = 0; r < table.getRowCount(); r++) {
            renderer = table.getCellRenderer(r, vColIndex);
            comp = renderer.getTableCellRendererComponent(table, table
                    .getValueAt(r, vColIndex), false, false, r, vColIndex);
            width = Math.max(width, comp.getPreferredSize().width);
        }

        // Adiciona margem
        width += 2 * margin;

        // atribui a largura
        col.setPreferredWidth(width);
    }

    private void acomodaColunas(JTable table, int margin) {
        for (int c = 0; c < table.getColumnCount(); c++) {
            acomodaColuna(table, c, margin);
        }
    }

    // retorna a altura preferencial de uma linha.
    // o resultado é igual a mais alta celula na linha.
    private int AlturaLinhaPreferencial(JTable table, int rowIndex, int margin) {
        // pega a altura padrao para todas as linhas
        int height = table.getRowHeight();

        // Determina a mais alta celula na linha
        for (int c = 0; c < table.getColumnCount(); c++) {
            TableCellRenderer renderer = table.getCellRenderer(rowIndex, c);
            Component comp = table.prepareRenderer(renderer, rowIndex, c);
            int h = comp.getPreferredSize().height + 2 * margin;
            height = Math.max(height, h);
        }
        return height;
    }

    // Para cada linha >= ao inicio e < do que o fim, a altura de uma linha
    // É atribuida para a altura preferencial da mais alta celula na linha.
    private void acomodaLinhas(JTable table, int start, int end, int margin) {
        for (int r = 0; r < table.getRowCount(); r++) {
            // pega a altura preferencial
            int h = AlturaLinhaPreferencial(table, r, margin);

            // atribui a altura da linha usando a altura preferencial
            if (table.getRowHeight(r) != h) {
                table.setRowHeight(r, h);
            }
        }
    }

	// A altura da cada linha é atribuida para a altura preferencial da mais
    // alta celula na linha;
    private void acomodaLinhas(JTable table, int margin) {
        acomodaLinhas(table, 0, table.getRowCount(), margin);
    }
    
    private String[] modeloColunas(boolean bTabelaDir){
        String[] colNomes;

        if (bTabelaDir) {
            colNomes = new String[]{
                Rotinas.getRecurso("Tabela.nome"),
                Rotinas.getRecurso("Tabela.tamanho"),
                Rotinas.getRecurso("Tabela.tipo"),
                Rotinas.getRecurso("Tabela.modificado"),
                Rotinas.getRecurso("Tabela.atributos"),
                Rotinas.getRecurso("Tabela.caminho")
            };
        } else {
            colNomes = new String[]{
                Rotinas.getRecurso("Tabela.nome"),
                Rotinas.getRecurso("Tabela.tamanho"),
                Rotinas.getRecurso("Tabela.tipo"),
                Rotinas.getRecurso("Tabela.modificado"),
                Rotinas.getRecurso("Tabela.atributos"),
                Rotinas.getRecurso("Tabela.caminho"),
                Rotinas.getRecurso("Tabela.aba")
            };            
        }
        return colNomes;
    }

    private DefaultTableModel modeloTabela(ArrayList<Diretorio> diretorios,
            JProgressBar barraProgresso, boolean bTabelaDir) {
        DefaultTableModel dtm = new DefaultTableModel();
        String[] colNomes = modeloColunas(bTabelaDir);        
        Vector<String> ColunasNome = new Vector<>(colNomes.length);
        Vector<Vector<String>> Linhas = new Vector<Vector<String>>();
        Vector<String> novaLinha;

        for (String colNome : colNomes) {
            ColunasNome.addElement(colNome);
        }
        
        if (diretorios != null) {
            barraProgresso.setMinimum(0);
            barraProgresso.setMaximum(diretorios.size());
            barraProgresso.setValue(0);

            for (Diretorio Campos : diretorios) {
                novaLinha = new Vector<String>();

                novaLinha.addElement(Campos.getNome());
                if (Campos.getTipo().getCodigo() == 'D') {
                    novaLinha.addElement("");
                } else {
                    novaLinha.addElement(Campos.getTamanhoFormatado());
                }
                novaLinha.addElement(Campos.getTipo().getNome());
                novaLinha.addElement(Campos.getModificadoFormatado());
                novaLinha.addElement(Campos.getAtributos());
                novaLinha.addElement(Campos.getCaminho());
                
                if (!bTabelaDir){
                    novaLinha.addElement(Campos.getAba().getNome());
                }
                
                Linhas.addElement(novaLinha);
                
                barraProgresso.setValue(barraProgresso.getValue() + 1);
                barraProgresso.getUI().update(barraProgresso.getGraphics(),
                        barraProgresso);
            }
            barraProgresso.setValue(0);
        }
        dtm.setDataVector(Linhas, ColunasNome);        
        
        return dtm;
    }
   
	// Assume que a tabela está contida num JScrollPane. Rola a
    // celula (rowIndex, vColIndex) até que fique visivel no centro do viewport.
    public void scrollToCenter(int rowIndex, int vColIndex) {
        if (!(this.getParent() instanceof JViewport)) {
            return;
        }
        JViewport viewport = (JViewport) this.getParent();

		// Este retangulo é relativo a tabela onde o
        // a beirada noroeste da celula (0,0) é sempre (0,0).
        Rectangle rect = this.getCellRect(rowIndex, vColIndex, true);

        // A localização da view relativa para a tabela
        Rectangle viewRect = viewport.getViewRect();

		// Traduz a localização da celula para aquela que é relativa
        // a view, assumindo que a beirada noroeste da view é (0,0).
        rect.setLocation(rect.x - viewRect.x, rect.y - viewRect.y);

        // Calcula a localização do retangulo se está no cetro da view
        int centerX = (viewRect.width - rect.width) / 2;
        int centerY = (viewRect.height - rect.height) / 2;

		// Faz a localização da célula para que
        // scrollRectToVisible mova para o centro da célula
        if (rect.x < centerX) {
            centerX = -centerX;
        }
        if (rect.y < centerY) {
            centerY = -centerY;
        }
        rect.translate(centerX, centerY);

        // Rola para a area dentro da view.
        viewport.scrollRectToVisible(rect);
    }

    @Override
    public Component prepareRenderer(TableCellRenderer renderer, int rowIndex,
            int vColIndex) {
        Component c = super.prepareRenderer(renderer, rowIndex, vColIndex);
        if (this.sombrearLinhas) {
            c = sombrearLinhas(renderer, rowIndex, vColIndex);
        } else if (this.sombrearColunas) {
            c = sombrearColunas(renderer, rowIndex, vColIndex);
        }

        return c;
    }

    private Component sombrearLinhas(TableCellRenderer renderer, int rowIndex,
            int vColIndex) {
        Component c = super.prepareRenderer(renderer, rowIndex, vColIndex);
        if (rowIndex % 2 == 0 && !isCellSelected(rowIndex, vColIndex)) {
            c.setBackground(new Color(232, 232, 232));
        } else if (!isCellSelected(rowIndex, vColIndex)) {
            c.setBackground(getBackground());
        }
        return c;
    }

    private Component sombrearColunas(TableCellRenderer renderer, int rowIndex,
            int vColIndex) {
        Component c = super.prepareRenderer(renderer, rowIndex, vColIndex);
        if (vColIndex % 2 == 0 && !isCellSelected(rowIndex, vColIndex)) {
            c.setBackground(new Color(232, 232, 232));
        } else if (!isCellSelected(rowIndex, vColIndex)) {
            c.setBackground(getBackground());
        }
        return c;
    }

    public boolean isSombrearLinhas() {
        return sombrearLinhas;
    }

    public void setSombrearLinhas(boolean sombrearLinhas) {
        this.sombrearLinhas = sombrearLinhas;
    }

    public boolean isSombrearColunas() {
        return sombrearColunas;
    }

    public void setSombrearColunas(boolean sombrearColunas) {
        this.sombrearColunas = sombrearColunas;
    }

}
