package hfsguardadir.objetosgui;

import hfsguardadir.catalogador.Catalogador;
import hfsguardadir.comum.Rotinas;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.MenuDetectEvent;
import org.eclipse.swt.events.MenuDetectListener;
import org.eclipse.swt.events.TreeEvent;
import org.eclipse.swt.events.TreeListener;
import org.eclipse.swt.layout.FillLayout;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Tree;
import org.eclipse.swt.widgets.TreeItem;

public class Arvore extends Composite {

	private Tree arvore;

	private Catalogador catalogador;

	public Arvore(Composite pai) {
		super(pai, SWT.BORDER);

		setLayout(new FillLayout());

		arvore = new Tree(this, SWT.FULL_SELECTION);
		setBackground(arvore.getBackground());
		setForeground(arvore.getForeground());
		setFont(arvore.getFont());

		arvore.addTreeListener(new TreeListener() {
			@Override
			public void treeExpanded(TreeEvent evt) {
				TreeItem item = (TreeItem) evt.item;
				item.setImage(Rotinas.getImagem(arvore.getShell(),
						"dir-aberto.gif"));
			}

			@Override
			public void treeCollapsed(TreeEvent evt) {
				TreeItem item = (TreeItem) evt.item;
				item.setImage(Rotinas.getImagem(arvore.getShell(),
						"diretorio.gif"));
			}
		});
		arvore.addMenuDetectListener(new MenuDetectListener() {
			@Override
			public void menuDetected(MenuDetectEvent evt) {
				PopMenu popMenu = new PopMenu(catalogador);
				popMenu.mostrar(evt.x, evt.y);
			}
		});
	}

	public void setCatalogador(Catalogador catalogador) {
		this.catalogador = catalogador;
	}

	public void excluirNode(String[] nomes) {
		TreeItem item = encontrarCaminhoPorNome(nomes);
		item.dispose();
	}

	public TreeItem encontrarCaminhoPorNome(String[] nomes) {
		for (TreeItem pai : arvore.getItems()) {
			String texto = pai.getText();
			if (texto.equals(nomes[0])) {
				if (nomes.length == 1)
					return pai;
				else
					return encontrarCaminho(pai, nomes, 1);
			}
		}
		return null;
	}

	private TreeItem encontrarCaminho(TreeItem item, String[] nomes, int nivel) {
		for (TreeItem filho : item.getItems()) {
			String texto = filho.getText();
			if (texto.equals(nomes[nivel])) {
				if (nomes.length == (nivel + 1))
					return filho;
				else
					return encontrarCaminho(filho, nomes, ++nivel);
			}
		}
		return null;
	}

	public void expandeTodos(boolean expandir) {
		for (TreeItem pai : arvore.getItems()) {
			pai.setExpanded(expandir);
			expandeTodos(pai, expandir);
		}
	}

	private void expandeTodos(TreeItem item, boolean expandir) {
		for (TreeItem filho : item.getItems()) {
			filho.setExpanded(expandir);
			expandeTodos(filho, expandir);
		}
	}

	public void limpar() {
		TreeItem[] items = arvore.getItems();
		List<TreeItem> lista = Arrays.asList(items); 
		Collections.reverse(lista);
		
		for (TreeItem pai : lista) {
			pai.dispose();			
		}
	}
	
	public Tree getArvore() {
		return arvore;
	}
}
