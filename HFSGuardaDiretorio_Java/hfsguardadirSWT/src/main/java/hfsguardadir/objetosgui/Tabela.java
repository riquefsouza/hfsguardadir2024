package hfsguardadir.objetosgui;

import hfsguardadir.catalogador.Catalogador;
import hfsguardadir.comum.Rotinas;
import hfsguardadir.objetos.Diretorio;
import hfsguardadir.objetos.Extensao;
import hfsguardadir.objetosbo.ExtensaoBO;

import java.io.ByteArrayInputStream;
import java.text.Collator;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Date;
import java.util.Locale;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.MenuDetectEvent;
import org.eclipse.swt.events.MenuDetectListener;
import org.eclipse.swt.events.MouseEvent;
import org.eclipse.swt.events.MouseListener;
import org.eclipse.swt.graphics.Color;
import org.eclipse.swt.graphics.Image;
import org.eclipse.swt.graphics.Rectangle;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.Listener;
import org.eclipse.swt.widgets.ProgressBar;
import org.eclipse.swt.widgets.Table;
import org.eclipse.swt.widgets.TableColumn;
import org.eclipse.swt.widgets.TableItem;

public class Tabela extends Composite {

	private Table tabela;

	private boolean bTabelaDir;

	private boolean sombrearLinhas;

	private Catalogador catalogador;

	boolean inDispose = false;
	
	public Tabela(Composite pai, boolean bTabelaDir) {
		super(pai, SWT.BORDER);

		tabela = new Table(this, SWT.FULL_SELECTION);
		tabela.setHeaderVisible(true);
		tabela.setLinesVisible(true);

		setBackground(tabela.getBackground());
		setForeground(tabela.getForeground());
		setFont(tabela.getFont());

		this.bTabelaDir = bTabelaDir;
		this.sombrearLinhas = false;
		montaColunas(bTabelaDir);
		acomodaColunas(tabela, 10);

		tabela.addMouseListener(new MouseListener() {
			@Override
			public void mouseUp(MouseEvent evt) {
			}

			@Override
			public void mouseDown(MouseEvent evt) {
				mouseClicou(evt);
			}

			@Override
			public void mouseDoubleClick(MouseEvent evt) {
			}
		});
		tabela.addMenuDetectListener(new MenuDetectListener() {			
			@Override
			public void menuDetected(MenuDetectEvent evt) {
				PopMenu popMenu = new PopMenu(catalogador);
				popMenu.mostrar(evt.x, evt.y);
			}
		});
		addListener(SWT.Resize, new Listener() {
			public void handleEvent(Event e) {
				onResize();
			}
		});
	}
	
	public void setCatalogador(Catalogador catalogador){
		this.catalogador = catalogador;
	}

	private void onResize() {
		Rectangle area = getClientArea();
		tabela.setBounds(0, 0, area.width, area.height);
	}

	private void mouseClicou(MouseEvent evt) {
		Table tabela = (Table) evt.widget;

		if (tabela.getSelectionCount() > 0) {
			String nome = tabela.getSelection()[0].getText(0);
			String tipo = tabela.getSelection()[0].getText(2);

			if (bTabelaDir) {				
				if (evt.button == 1 && evt.count == 2) {
					catalogador.DuploCliqueLista(nome, tipo);
				}
			} else {
				if (evt.button == 1 && evt.count == 1) {
					String nomeAba = tabela.getSelection()[0].getText(6);
					String caminho = tabela.getSelection()[0].getText(5);
					catalogador.EncontrarItemLista(nomeAba, nome, caminho);
				}
			}
		}
	}

	public int encontrarLinha(String nome) {
		String slinha;
		int nlinha = 0;
		for (int i = 0; i < tabela.getItemCount(); i++) {
			slinha = tabela.getItem(i).getText();
			if (slinha.equals(nome)) {
				nlinha = i;
				break;
			}
		}
		return nlinha;
	}

	public Diretorio getLinhaSelecionada(boolean bTabelaDir) {
		Diretorio dir = null;
		TableItem item;

		if (tabela.getSelectionCount() > 0) {
			item = tabela.getSelection()[0];
			
			dir = new Diretorio();
			dir.setNome(item.getText(0));
			dir.setTamanhoFormatado(item.getText(1));
			dir.getTipo().setNome(item.getText(2));
			dir.setModificadoFormatado(item.getText(3));
			dir.setAtributos(item.getText(4));
			dir.setCaminho(item.getText(5));
			if (bTabelaDir) {
				dir.getAba().setNome(item.getText(6));
			}
		}

		return dir;
	}

	private void acomodaColuna(Table table, int vColIndex, int margin) {
		TableColumn col = table.getColumn(vColIndex);
		int width;

		// pega a largura do cabeçalho da coluna
		width = col.getWidth();

		// pega a largura maxima do dado da coluna
		for (int r = 0; r < table.getItemCount(); r++) {
			width = Math.max(width, col.getWidth());
		}

		// Adiciona margem
		width += 2 * margin;

		// atribui a largura
		col.setWidth(width);
	}

	private void acomodaColunas(Table table, int margin) {
		for (int c = 0; c < table.getColumnCount(); c++) {
			acomodaColuna(table, c, margin);
		}
	}

	private String[] cabecalhoColunas(boolean bTabelaDir) {
		String[] colNomes;
		
		if (bTabelaDir) {
			colNomes = new String[] { Rotinas.getRecurso("Tabela.nome"),
					Rotinas.getRecurso("Tabela.tamanho"),
					Rotinas.getRecurso("Tabela.tipo"),
					Rotinas.getRecurso("Tabela.modificado"),
					Rotinas.getRecurso("Tabela.atributos"),
					Rotinas.getRecurso("Tabela.caminho") };
		} else {
			colNomes = new String[] { Rotinas.getRecurso("Tabela.nome"),
					Rotinas.getRecurso("Tabela.tamanho"),
					Rotinas.getRecurso("Tabela.tipo"),
					Rotinas.getRecurso("Tabela.modificado"),
					Rotinas.getRecurso("Tabela.atributos"),
					Rotinas.getRecurso("Tabela.caminho"),
					Rotinas.getRecurso("Tabela.aba") };
		}
		
		return colNomes;
	}
	
	private void montaColunas(boolean bTabelaDir) {
		TableColumn coluna;
		String[] colNomes = cabecalhoColunas(bTabelaDir);
		int[] colWidths = new int[] { 300, 100, 70, 120, 90, 500, 150 };
		int[] colSorts = new int[] { SortListenerFactory.STRING,
				SortListenerFactory.STRING, SortListenerFactory.STRING,
				SortListenerFactory.DATE, SortListenerFactory.STRING,
				SortListenerFactory.STRING, SortListenerFactory.STRING };

		for (int i = 0; i < colNomes.length; i++) {
			coluna = new TableColumn(tabela, SWT.NONE);
			coluna.setWidth(colWidths[i]);
			coluna.setText(colNomes[i]);
	        coluna.addListener(SWT.Selection, SortListenerFactory.getListener(colSorts[i]));
		}
	}

	public void montaTabela(ArrayList<Diretorio> diretorios, 
			ArrayList<Extensao> extensoes, ProgressBar barraProgresso, 
			boolean bTabelaDir) {		
		TableItem item;
		String[] colNomes;
				
		if (diretorios != null) {
			colNomes = cabecalhoColunas(bTabelaDir);
			for (int i = 0; i < tabela.getColumns().length; i++) {				
				tabela.getColumns()[i].setText(colNomes[i]);
			}
			colNomes = cabecalhoColunas(bTabelaDir);
			
			barraProgresso.setMinimum(0);
			barraProgresso.setMaximum(diretorios.size());
			barraProgresso.setSelection(0);
			
			tabela.removeAll();

			for (int linha = 0; linha < diretorios.size(); linha++) {
				Diretorio campo = diretorios.get(linha);

				item = new TableItem(tabela, SWT.NONE);
				item.setText(0, campo.getNome());

				if (campo.getTipo().getCodigo() == 'D') {
					item.setText(1, "");
				} else {
					item.setText(1, campo.getTamanhoFormatado());
				}
				item.setText(2, campo.getTipo().getNome());
				item.setText(3, campo.getModificadoFormatado());
				item.setText(4, campo.getAtributos());
				item.setText(5, campo.getCaminho());
				if (!bTabelaDir) {
					item.setText(6, campo.getAba().getNome());
				}
				
				sombrearLinhas(linha);
				setIconePorExtensao(extensoes, item, campo.getNome().toLowerCase(),
						campo.getTipo().getNome());

				barraProgresso.setSelection(barraProgresso.getSelection() + 1);
			}
			barraProgresso.setSelection(0);
		}
	}

	private void setIconePorExtensao(ArrayList<Extensao> extensoes,
			TableItem item, String nome, String tipo) {
		String ext = nome.substring(nome.lastIndexOf('.') + 1);
		Extensao extensao = ExtensaoBO.getInstancia().pegaExtensaoPorNome(
				extensoes, ext, tipo);
		if (extensao != null) {
			if (extensao.getGif16() != null) {
				Image img = new Image(getDisplay(), new ByteArrayInputStream(
						extensao.getGif16()));

				item.setImage(img);
			}
		}
	}

	private void sombrearLinhas(int rowIndex) {
		if (rowIndex % 2 == 0) {
			tabela.getItem(rowIndex).setBackground(
					new Color(this.getShell().getDisplay(), 232, 232, 232));
		}
	}

	public boolean isSombrearLinhas() {
		return sombrearLinhas;
	}

	public void setSombrearLinhas(boolean sombrearLinhas) {
		this.sombrearLinhas = sombrearLinhas;
	}

	public Table getTabela() {
		return tabela;
	}
}

class SortListenerFactory implements Listener {
	private Comparator<TableItem> currentComparator = null;

	private Collator col = Collator.getInstance(Locale.getDefault());

	public static final int INT = 0;
	public static final int STRING = 1;
	public static final int DATE = 2;
	public static final int DOUBLE = 3;
	public static final int HOUR = 4;

	private SortListenerFactory(int _comp) {
		switch (_comp) {
		case INT:
			currentComparator = intComparator;
			break;

		case STRING:
			currentComparator = strComparator;
			break;

		case DATE:
			currentComparator = dateComparator;
			break;

		case DOUBLE:
			currentComparator = doubleComparator;
			break;

		case HOUR:
			currentComparator = hourComparator;
			break;

		default:
			currentComparator = strComparator;
		}
	}

	public static Listener getListener(int _comp) {
		return new SortListenerFactory(_comp);
	}

	private int colIndex = 0;
	private int updown = 1;

	// Integer Comparator
	private Comparator<TableItem> intComparator = new Comparator<TableItem>() {
		@Override
		public int compare(TableItem t1, TableItem t2) {
			int v1 = Integer.parseInt(t1.getText(colIndex));
			int v2 = Integer.parseInt(t2.getText(colIndex));

			if (v1 < v2)
				return 1 * updown;
			if (v1 > v2)
				return -1 * updown;

			return 0;
		}
	};

	// String Comparator
	private Comparator<TableItem> strComparator = new Comparator<TableItem>() {
		@Override
		public int compare(TableItem t1, TableItem t2) {
			String v1 = (t1.getText(colIndex));
			String v2 = (t2.getText(colIndex));

			return (col.compare(v1, v2)) * updown;
		}
	};

	// Double Comparator
	private Comparator<TableItem> doubleComparator = new Comparator<TableItem>() {
		@Override
		public int compare(TableItem t1, TableItem t2) {
			double v1 = Double.parseDouble(t1.getText(colIndex));
			double v2 = Double.parseDouble(t2.getText(colIndex));

			if (v1 < v2)
				return 1 * updown;
			if (v1 > v2)
				return -1 * updown;

			return 0;
		}
	};

	// Hour Comparator (hh:mm:ss)
	private Comparator<TableItem> hourComparator = new Comparator<TableItem>() {
		@Override
		public int compare(TableItem t1, TableItem t2) {
			String v1 = (t1.getText(colIndex)).trim();
			String v2 = (t2.getText(colIndex)).trim();

			DateFormat df = new SimpleDateFormat("hh:mm:ss");

			Date d1 = null;
			Date d2 = null;

			try {
				d1 = df.parse(v1);
			} catch (ParseException e) {
				System.out.println("[WARNING] v1 " + v1);
				try {
					d1 = df.parse("01:01:01");
				} catch (ParseException e1) {
				}
			}

			try {
				d2 = df.parse(v2);
			} catch (ParseException e) {
				System.out.println("[WARNING] v2 " + v2);
				try {
					d2 = df.parse("01:01:01");
				} catch (ParseException e1) {
				}
			}

			if (d1.equals(d2))
				return 0;

			return updown * (d1.before(d2) ? 1 : -1);
		}
	};

	private Comparator<TableItem> dateComparator = new Comparator<TableItem>() {
		@Override
		public int compare(TableItem t1, TableItem t2) {
			String v1 = (t1.getText(colIndex)).trim();
			String v2 = (t2.getText(colIndex)).trim();

			v1.replaceAll("-", "/");
			v2.replaceAll("-", "/");

			DateFormat df_europe = new SimpleDateFormat("dd/MM/yyyy");
			// DateFormat df_usa = new SimpleDateFormat("yyyy/MM/dd");

			DateFormat df = df_europe;

			Date d1 = null;
			Date d2 = null;

			try {
				d1 = df.parse(v1);
			} catch (ParseException e) {
				d1 = Rotinas.StringToDate("01/01/1900");
			}

			try {
				d2 = df.parse(v2);
			} catch (ParseException e) {
				d2 = Rotinas.StringToDate("01/01/1900");
			}

			if (d1.equals(d2))
				return 0;

			return updown * (d1.before(d2) ? 1 : -1);
		}
	};

	public void handleEvent(Event e) {

		updown = (updown == 1 ? -1 : 1);

		TableColumn currentColumn = (TableColumn) e.widget;
		Table table = currentColumn.getParent();

		colIndex = searchColumnIndex(currentColumn);

		table.setRedraw(false);

		TableItem[] items = table.getItems();

		Arrays.sort(items, currentComparator);

		table.setItemCount(items.length);

		for (int i = 0; i < items.length; i++) {
			TableItem item = new TableItem(table, SWT.NONE, i);
			item.setText(getData(items[i]));
			item.setImage(getImage(items[i]));
			items[i].dispose();
		}

		table.setRedraw(true);
	}

	private String[] getData(TableItem t) {
		Table table = t.getParent();

		int colCount = table.getColumnCount();
		String[] s = new String[colCount];

		for (int i = 0; i < colCount; i++)
			s[i] = t.getText(i);

		return s;

	}

	private Image[] getImage(TableItem t) {
		Table table = t.getParent();

		int colCount = table.getColumnCount();
		Image[] s = new Image[colCount];

		for (int i = 0; i < colCount; i++)
			s[i] = t.getImage(i);

		return s;

	}

	private int searchColumnIndex(TableColumn currentColumn) {
		Table table = currentColumn.getParent();

		int in = 0;

		for (int i = 0; i < table.getColumnCount(); i++)
			if (table.getColumn(i) == currentColumn)
				in = i;

		return in;
	}
}
