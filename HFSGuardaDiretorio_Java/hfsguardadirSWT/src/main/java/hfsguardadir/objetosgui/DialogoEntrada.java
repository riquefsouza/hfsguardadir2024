package hfsguardadir.objetosgui;

import hfsguardadir.comum.Rotinas;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.layout.FillLayout;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Dialog;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Text;

import swing2swt.layout.FlowLayout;

public class DialogoEntrada extends Dialog {
	private Shell shell;
	private String mensagem;
	private String entrada;
	private String valorInicial;

	public DialogoEntrada(Shell parent, String texto, String mensagem,
			String valorInicial) {
		super(parent, SWT.DIALOG_TRIM | SWT.APPLICATION_MODAL);	
		setText(texto);
		setMensagem(mensagem);
		setValorInicial(valorInicial);
		createContents();
		Rotinas.CentralizaDlg(parent, shell);
	}
	
	public Shell getShell(){
		return shell;
	}

	public String getMensagem() {
		return mensagem;
	}

	public void setMensagem(String mensagem) {
		this.mensagem = mensagem;
	}

	public String getEntrada() {
		return entrada;
	}

	public void setEntrada(String entrada) {
		this.entrada = entrada;
	}

	public String getValorInicial() {
		return valorInicial;
	}

	public void setValorInicial(String valorInicial) {
		this.valorInicial = valorInicial;
	}

	public String open() {		
		shell.pack();
		shell.open();
		Display display = getParent().getDisplay();
		while (!shell.isDisposed()) {
			if (!display.readAndDispatch()) {
				display.sleep();
			}
		}
		return entrada;
	}

	private void createContents() {
		shell = new Shell(getParent(), getStyle());
		shell.setSize(375, 132);
		shell.setText(getText());
		
		FillLayout fl_shell = new FillLayout(SWT.VERTICAL);
		shell.setLayout(fl_shell);
		
		Composite composite = new Composite(shell, SWT.NONE);
		composite.setLayout(new GridLayout(1, false));
		
		Label lblNewLabel = new Label(composite, SWT.NONE);
		lblNewLabel.setText(mensagem);
		
		final Text text = new Text(composite, SWT.BORDER);
		text.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, false, 1, 1));
		text.setText(valorInicial);
		text.setTextLimit(10);
		
		Composite composite_1 = new Composite(shell, SWT.NONE);
		composite_1.setLayout(new FlowLayout(FlowLayout.RIGHT, 5, 15));
		
		Button btnOk = new Button(composite_1, SWT.NONE);
		btnOk.setText("      Ok      ");
		btnOk.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent event) {
				entrada = text.getText();
				shell.close();
			}
		});
		
		Button btnCancelar = new Button(composite_1, SWT.NONE);
		btnCancelar.setText(Rotinas.getRecurso("Dialogo.cancelButtonText"));
		btnCancelar.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent event) {
				entrada = null;
				shell.close();
			}
		});

		shell.setDefaultButton(btnOk);	
	}
}
