package hfsguardadir.gui;

import hfsguardadir.comum.Rotinas;
import hfsguardadir.objetos.PropriedadeSistema;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.layout.FillLayout;
import org.eclipse.swt.layout.FormAttachment;
import org.eclipse.swt.layout.FormData;
import org.eclipse.swt.layout.FormLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Dialog;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Table;
import org.eclipse.swt.widgets.TableColumn;
import org.eclipse.swt.widgets.TableItem;
import org.eclipse.wb.swt.SWTResourceManager;

public class FrmSobre extends Dialog {

	protected Object result;
	protected Shell shell;
	private Table tabelaPropriedades;
	private int nMaxValor, nMaxNome;
	private Label label1, label2, label3, label4;

	/**
	 * Create the dialog.
	 * 
	 * @param parent
	 * @param style
	 */
	public FrmSobre(Shell parent) {
		super(parent, SWT.DIALOG_TRIM | SWT.APPLICATION_MODAL);
		setText(Rotinas.getRecurso("FrmSobre.titulo"));
		createContents();		
		mudarLingua();
		tabelaLinhas();
		
		tabelaPropriedades.select(0);
		tabelaPropriedades.getColumn(0).setWidth(nMaxNome * 6);
		tabelaPropriedades.getColumn(1).setWidth(nMaxValor * 5);
	}

	/**
	 * Open the dialog.
	 * 
	 * @return the result
	 */
	public Object open() {
		shell.open();
		shell.layout();
		Display display = getParent().getDisplay();
		while (!shell.isDisposed()) {
			if (!display.readAndDispatch()) {
				display.sleep();
			}
		}
		return result;
	}
	
	/**
	 * Create contents of the dialog.
	 */
	private void createContents() {
		shell = new Shell(getParent(), SWT.DIALOG_TRIM | SWT.APPLICATION_MODAL);
		shell.setSize(535, 438);
		shell.setText(getText());
		shell.setLayout(new FormLayout());

		Composite composite = new Composite(shell, SWT.NONE);
		FormData fd_composite = new FormData();
		fd_composite.right = new FormAttachment(100);
		fd_composite.top = new FormAttachment(0);
		fd_composite.left = new FormAttachment(0);
		composite.setLayoutData(fd_composite);
		composite.setLayout(new FillLayout(SWT.VERTICAL));

		label1 = new Label(composite, SWT.NONE);
		label1.setFont(SWTResourceManager.getFont("Segoe UI", 13, SWT.BOLD));
		label1.setAlignment(SWT.CENTER);
		label1.setText(Rotinas.getRecurso("FrmSobre.label1"));

		label2 = new Label(composite, SWT.NONE);
		label2.setAlignment(SWT.CENTER);
		label2.setText(Rotinas.getRecurso("FrmSobre.label2"));

		label3 = new Label(composite, SWT.NONE);
		label3.setAlignment(SWT.CENTER);
		label3.setText(Rotinas.getRecurso("FrmSobre.label3"));

		label4 = new Label(composite, SWT.NONE);
		label4.setAlignment(SWT.CENTER);
		label4.setText(Rotinas.getRecurso("FrmSobre.label4"));

		tabelaPropriedades = new Table(shell, SWT.BORDER | SWT.FULL_SELECTION);
		FormData fd_tabelaPropriedades = new FormData();
		fd_tabelaPropriedades.height = 250;
		fd_tabelaPropriedades.right = new FormAttachment(100);
		fd_tabelaPropriedades.left = new FormAttachment(0);
		fd_tabelaPropriedades.top = new FormAttachment(composite);

		tabelaPropriedades.setLayoutData(fd_tabelaPropriedades);
		tabelaPropriedades.setHeaderVisible(true);
		tabelaPropriedades.setLinesVisible(true);

		Composite composite_1 = new Composite(shell, SWT.NONE);
		FormData fd_composite_1 = new FormData();
		fd_composite_1.top = new FormAttachment(tabelaPropriedades);

		TableColumn colPropriedade = new TableColumn(tabelaPropriedades,
				SWT.NONE);
		colPropriedade.setWidth(194);
		colPropriedade.setText("Propriedade");

		TableColumn colValor = new TableColumn(tabelaPropriedades, SWT.NONE);
		colValor.setWidth(194);
		colValor.setText("Valor");

		fd_composite_1.bottom = new FormAttachment(100);
		fd_composite_1.right = new FormAttachment(100);
		fd_composite_1.left = new FormAttachment(0);
		composite_1.setLayoutData(fd_composite_1);

		Button btnOk = new Button(composite_1, SWT.CENTER);
		btnOk.setLocation(167, 10);
		btnOk.setSize(65, 25);
		btnOk.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				shell.dispose();
			}
		});
		btnOk.setText("Ok");
	}
	
	public Shell getShell(){
		return shell;
	}

    private void tabelaLinhas() {
    	TableItem tableItem;
        PropriedadeSistema[] propsSistema = Rotinas.getPropriedadesSistema();
        for (PropriedadeSistema Campos : propsSistema) {
        	tableItem = new TableItem(tabelaPropriedades, SWT.NONE);
        	tableItem.setText(new String[] { Campos.getNome(), Campos.getValor() });
            nMaxNome = Math.max(nMaxNome, Campos.getNome().length());
            nMaxValor = Math.max(nMaxValor, Campos.getValor().length());
        }
    }
	
	private void mudarLingua() {
		setText(Rotinas.getRecurso("FrmSobre.titulo"));
		label1.setText(Rotinas.getRecurso("FrmSobre.label1"));
		label2.setText(Rotinas.getRecurso("FrmSobre.label2"));
		label3.setText(Rotinas.getRecurso("FrmSobre.label3"));
		label4.setText(Rotinas.getRecurso("FrmSobre.label4"));
	}

}
