package hfsguardadir.objetosgui;

import hfsguardadir.comum.StringList;
import java.io.IOException;
import javax.swing.DefaultListModel;
import javax.swing.JList;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

public class CaixaLista extends JList<String> {
	private static final long serialVersionUID = 275199940906356477L;

	private DefaultListModel<String> modelo;

	public CaixaLista() {
		super();
		modelo = new DefaultListModel<>();

		setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		setModel(modelo);

		addListSelectionListener(new ListSelectionListener() {
			public void valueChanged(ListSelectionEvent evt) {
				valorSelecionadoMudou(evt);
			}
		});
	}

	public DefaultListModel<String> getModelo() {
		return modelo;
	}

        public void SaveToFile(String arquivo)
            throws IOException {
            StringList log = new StringList();
            for (int i = 0; i < modelo.size(); i++) {
                log.add(modelo.get(i));
            }
            log.SaveToFile(arquivo);
        }
        
	private void valorSelecionadoMudou(ListSelectionEvent evt) {
		if (!evt.getValueIsAdjusting()) {
			int sel = this.getSelectedIndex();
			if (sel != -1) {
				scrollRectToVisible(this.getCellBounds(sel, sel));
			}
		}
	}
}
