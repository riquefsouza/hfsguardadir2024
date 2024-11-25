package hfsguardadir.gui;

import hfsguardadir.catalogador.Catalogador;
import hfsguardadir.comum.Rotinas;
import hfsguardadir.objetos.Diretorio;
import hfsguardadir.objetos.Importar;
import hfsguardadir.objetosbo.DiretorioBO;
import hfsguardadir.objetosbo.ImportarBO;
import hfsguardadir.objetosgui.CaixaLista;
import hfsguardadir.objetosgui.Dialogo;

import java.io.IOException;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Date;
import java.util.logging.Level;
import java.util.logging.Logger;

import org.eclipse.swt.SWT;
import org.eclipse.swt.graphics.Cursor;
import org.eclipse.swt.layout.FormAttachment;
import org.eclipse.swt.layout.FormData;
import org.eclipse.swt.layout.FormLayout;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Dialog;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.ProgressBar;
import org.eclipse.swt.widgets.Shell;

public class FrmImportarDiretorio extends Dialog {

	protected Object result;
	protected Shell shell;
	public CaixaLista memoImportaDir;
	public ProgressBar pbImportar;
	public Label barraStatus1;
	public Label barraStatus2;

	private final FrmImportarDiretorioProgresso frmImportarDiretorioProgresso;
	private final FrmPrincipal frmPrincipal;
	private final Catalogador catalogador;

	public boolean bSubDiretorio;
	public ArrayList<Importar> listaImportar;
	public ArrayList<Diretorio> listaDiretorio;

	public FrmImportarDiretorio(Shell parent, Catalogador catalogador,
			FrmPrincipal frmPrincipal) {
		super(parent, SWT.DIALOG_TRIM | SWT.APPLICATION_MODAL);
		setText(Rotinas.getRecurso("FrmImportarDiretorio.titulo"));
		createContents();
		this.frmPrincipal = frmPrincipal;
		this.catalogador = catalogador;
		mudarLingua();

		frmImportarDiretorioProgresso = new FrmImportarDiretorioProgresso(this);
		listaImportar = new ArrayList<>();
		Rotinas.CentralizaDlg(parent, shell);
	}

	public Object open() {
		shell.open();
		shell.layout();
		
		WindowOpened();
		/*
		Display display = getParent().getDisplay();
		while (!shell.isDisposed()) {
			if (!display.readAndDispatch()) {
				display.sleep();
			}
		}
		*/
		shell.close();

		return result;
	}

	/**
	 * Create contents of the dialog.
	 */
	private void createContents() {
		shell = new Shell(getParent(), SWT.BORDER);
		shell.setSize(895, 572);
		shell.setText(getText());
		shell.setLayout(new FormLayout());

		memoImportaDir = new CaixaLista(shell);
		FormData fd_memoImportaDir = new FormData();
		fd_memoImportaDir.height = 526;
		fd_memoImportaDir.right = new FormAttachment(100);
		fd_memoImportaDir.top = new FormAttachment(0);
		fd_memoImportaDir.left = new FormAttachment(0);
		memoImportaDir.setLayoutData(fd_memoImportaDir);

		pbImportar = new ProgressBar(shell, SWT.NONE);
		FormData fd_pbImportar = new FormData();
		fd_pbImportar.top = new FormAttachment(memoImportaDir);
		fd_pbImportar.left = new FormAttachment(0);
		fd_pbImportar.right = new FormAttachment(100);
		pbImportar.setLayoutData(fd_pbImportar);

		Composite compositeBarraStatus = new Composite(shell, SWT.NONE);
		compositeBarraStatus.setLayout(new FormLayout());
		FormData fd_compositeBarraStatus = new FormData();
		fd_compositeBarraStatus.top = new FormAttachment(pbImportar);
		fd_compositeBarraStatus.left = new FormAttachment(0);
		fd_compositeBarraStatus.right = new FormAttachment(100);
		fd_compositeBarraStatus.bottom = new FormAttachment(100);
		compositeBarraStatus.setLayoutData(fd_compositeBarraStatus);

		barraStatus1 = new Label(compositeBarraStatus, SWT.BORDER);
		FormData fd_barraStatus1 = new FormData();
		fd_barraStatus1.right = new FormAttachment(0, 200);
		fd_barraStatus1.top = new FormAttachment(0);
		fd_barraStatus1.left = new FormAttachment(0);
		barraStatus1.setLayoutData(fd_barraStatus1);
		barraStatus1.setText(Rotinas
				.getRecurso("FrmImportarDiretorio.barraStatus1"));

		barraStatus2 = new Label(compositeBarraStatus, SWT.BORDER);
		FormData fd_barraStatus2 = new FormData();
		fd_barraStatus2.right = new FormAttachment(100);
		fd_barraStatus2.top = new FormAttachment(0);
		fd_barraStatus2.left = new FormAttachment(0, 200);
		barraStatus2.setLayoutData(fd_barraStatus2);
	}

	private void WindowOpened() {
		String sLog;

		for (Importar importar : this.listaImportar) {
			catalogador.diretorioOrdem.setOrdem(1);

			if (!bSubDiretorio) {
				shell.setCursor(new Cursor(shell.getDisplay(), SWT.CURSOR_WAIT));

				try {
					ImportarBO.getInstancia().ImportacaoCompleta(importar,
							catalogador.diretorioOrdem,
							catalogador.listaExtensoes,
							frmImportarDiretorioProgresso);
				} catch (SQLException ex) {
					Logger.getLogger(FrmImportarDiretorio.class.getName()).log(
							Level.SEVERE, null, ex);
				}

				shell.setCursor(new Cursor(shell.getDisplay(), SWT.CURSOR_ARROW));
			} else {
				if (!DiretorioBO.getInstancia().verificaCodDir(
						importar.getAba(), importar.getRotuloRaiz(),
						catalogador.listaDiretorioPai)) {
					shell.setCursor(new Cursor(shell.getDisplay(),
							SWT.CURSOR_WAIT));

					try {
						ImportarBO.getInstancia().ImportacaoCompleta(importar,
								catalogador.diretorioOrdem,
								catalogador.listaExtensoes,
								frmImportarDiretorioProgresso);
					} catch (SQLException ex) {
						Logger.getLogger(FrmImportarDiretorio.class.getName())
								.log(Level.SEVERE, null, ex);
					}

					shell.setCursor(new Cursor(shell.getDisplay(),
							SWT.CURSOR_ARROW));
				} else {
					Dialogo.mensagemInfo(shell,
							"FrmImportarDiretorio.DiretorioExisteCatalogo");
				}
			}
		}

		if (frmPrincipal.menuGravarLogImportacao.getSelection()) {
			if (memoImportaDir.getLista().getItemCount() > 0) {
				sLog = Rotinas.getParams().getDiretorioSistema()
						+ Rotinas.BARRA_INVERTIDA
						+ Rotinas.formataDate(Rotinas.FORMATO_DHARQUIVO,
								new Date()) + "_Importacao.log";
				try {
					memoImportaDir.SaveToFile(sLog);
				} catch (IOException ex) {
					Logger.getLogger(FrmImportarDiretorio.class.getName()).log(
							Level.SEVERE, null, ex);
				}
			}
		}
	}

	private void mudarLingua() {
		setText(Rotinas.getRecurso("FrmImportarDiretorio.titulo"));
		barraStatus1.setText(Rotinas
				.getRecurso("FrmImportarDiretorio.barraStatus1"));
	}

}
