package hfsguardadir.objetosgui;

import hfsguardadir.comum.StringList;

import java.io.IOException;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.events.SelectionListener;
import org.eclipse.swt.layout.FillLayout;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.List;

public class CaixaLista extends Composite { 

	private List lista; 

	public CaixaLista(Composite pai) {
		super(pai, SWT.BORDER);
		setLayout(new FillLayout());
		
		lista = new List(this, SWT.FULL_SELECTION);

		lista.addSelectionListener(new SelectionListener() {

			public void widgetSelected(SelectionEvent evt) {
				valorSelecionadoMudou(evt);
			}

			public void widgetDefaultSelected(SelectionEvent evt) {
			}
		});
	}

	public void SaveToFile(String arquivo) throws IOException {
		StringList log = new StringList();
		for (int i = 0; i < lista.getItemCount(); i++) {
			log.add(lista.getItem(i));
		}
		log.SaveToFile(arquivo);
	}

	private void valorSelecionadoMudou(SelectionEvent evt) {
		/*
		if (!evt.getValueIsAdjusting()) {
			int sel = this.getSelectedIndex();
			if (sel != -1) {
				scrollRectToVisible(this.getCellBounds(sel, sel));
			}
		}
		*/
	}
	
	public List getLista(){
		return lista;
	}
}
