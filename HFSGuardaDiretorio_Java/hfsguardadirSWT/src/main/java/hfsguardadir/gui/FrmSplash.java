package hfsguardadir.gui;

import hfsguardadir.catalogador.Catalogador;
import hfsguardadir.comum.Rotinas;

import org.eclipse.swt.SWT;
import org.eclipse.swt.layout.FillLayout;
import org.eclipse.swt.layout.FormAttachment;
import org.eclipse.swt.layout.FormData;
import org.eclipse.swt.layout.FormLayout;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.ProgressBar;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.wb.swt.SWTResourceManager;

public class FrmSplash {

	protected Object result;
	protected Shell shell;
	public ProgressBar pb;
	private Label label1, label2;

	private final FrmSplashProgresso frmSplashProgresso;

	public FrmSplash(final Catalogador catalogador) {
		shell = new Shell(SWT.ON_TOP);

		createContents();
		mudarLingua();

		frmSplashProgresso = new FrmSplashProgresso(this);

		shell.open();
		shell.layout();

		Rotinas.CentralizaFrm(shell);
		catalogador.carregarDados(frmSplashProgresso);

		shell.close();

	}

	private void createContents() {
		shell.setSize(375, 110);
		shell.setLayout(new FormLayout());

		Composite composite = new Composite(shell, SWT.NONE);
		FormData fd_composite = new FormData();
		fd_composite.right = new FormAttachment(100);
		fd_composite.top = new FormAttachment(0);
		fd_composite.left = new FormAttachment(0);
		composite.setLayoutData(fd_composite);
		composite.setLayout(new FillLayout(SWT.VERTICAL));

		label1 = new Label(composite, SWT.NONE);
		label1.setFont(SWTResourceManager.getFont("Segoe UI", 24, SWT.BOLD));
		label1.setAlignment(SWT.CENTER);
		label1.setText(Rotinas.getRecurso("FrmSplash.label1"));

		label2 = new Label(composite, SWT.NONE);
		label2.setFont(SWTResourceManager.getFont("Segoe UI", 18, SWT.BOLD));
		label2.setAlignment(SWT.CENTER);
		label2.setText(Rotinas.getRecurso("FrmSplash.label2"));

		pb = new ProgressBar(composite, SWT.NONE);
	}

	public Shell getShell() {
		return shell;
	}

	private void mudarLingua() {
		label1.setText(Rotinas.getRecurso("FrmSplash.label1"));
		label2.setText(Rotinas.getRecurso("FrmSplash.label2"));
	}

}
