package hfsguardadir.objetosgui;

import hfsguardadir.comum.Rotinas;
import hfsguardadir.objetos.Extensao;

import java.io.ByteArrayInputStream;
import java.util.ArrayList;

import org.eclipse.swt.SWT;
import org.eclipse.swt.graphics.Image;
import org.eclipse.swt.graphics.Rectangle;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.Listener;
import org.eclipse.swt.widgets.Table;
import org.eclipse.swt.widgets.TableColumn;
import org.eclipse.swt.widgets.TableItem;

public class TabelaExtensao extends Composite {

	private Table tabela;

    public TabelaExtensao(Composite pai) {
        super(pai, SWT.BORDER);
        tabela = new Table(this, SWT.FULL_SELECTION);       
        tabela.setHeaderVisible(true);
        tabela.setLinesVisible(true);
               
        montaColunas();

		addListener(SWT.Resize, new Listener() {
			public void handleEvent(Event e) {
				onResize();
			}
		});        
    }

	private void onResize() {
		Rectangle area = getClientArea();
		tabela.setBounds(0, 0, area.width, area.height);
	}
    
    private void montaColunas() {
		TableColumn colExtensao = new TableColumn(tabela, SWT.NONE);
		colExtensao.setWidth(146);
		colExtensao.setText(Rotinas.getRecurso("FrmCadExtensao.extensao"));

		TableColumn colIcone = new TableColumn(tabela, SWT.NONE);
		colIcone.setWidth(129);
		colIcone.setText(Rotinas.getRecurso("FrmCadExtensao.icone"));
    }

    public void montaTabela(ArrayList<Extensao> lista) {
    	TableItem item;
    	Image img;
    	
    	for (Extensao campo : lista) {
    		item = new TableItem(tabela, SWT.NONE);
    		item.setText(0, campo.getNome());
    		
    		img = new Image(getDisplay(), new ByteArrayInputStream(campo.getGif16()));
    		item.setImage(1, img);
    	}
    }

    public Table getTabela(){
    	return tabela;
    }
   
}
