package hfsguardadir.gui;

import hfsguardadir.catalogador.Catalogador;
import hfsguardadir.comum.Rotinas;
import hfsguardadir.comum.StringList;
import hfsguardadir.comum.TipoExportarExtensao;
import hfsguardadir.objetos.Extensao;
import hfsguardadir.objetosbo.ExtensaoBO;
import hfsguardadir.objetosgui.Dialogo;
import hfsguardadir.objetosgui.EscolhaArquivo;
import hfsguardadir.objetosgui.TabelaExtensao;

import java.io.File;
import java.io.IOException;
import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.layout.FormAttachment;
import org.eclipse.swt.layout.FormData;
import org.eclipse.swt.layout.FormLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Dialog;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Menu;
import org.eclipse.swt.widgets.MenuItem;
import org.eclipse.swt.widgets.Shell;

public class FrmCadExtensao extends Dialog {

	protected Object result;
	protected Shell shell;
	private FormData fd_tabelaExtensao;
	private TabelaExtensao tabelaExtensao;
	private Catalogador catalogador;
	private Button btnIncluir;
	private Button btnExcluir;
	private MenuItem menuExtensao;
	private MenuItem menuIncluirExtensao;
	private MenuItem menuExcluirExtensao;
	private MenuItem menuExcluirTodasExtensoes;
	private MenuItem menuExportarTodos;
	private MenuItem menuExportarBitmap;
	private MenuItem menuExportarIcone;
	private MenuItem menuExportarGIF;
	private MenuItem menuExportarJPEG;
	private MenuItem menuExportarPNG;
	private MenuItem menuExportarTIFF;
	private MenuItem menuImportarTodos;
	private MenuItem menuImportarIconesArquivos;
	private MenuItem menuExtrairIconesArquivos;

	/**
	 * Create the dialog.
	 * 
	 * @param parent
	 * @param style
	 */
	public FrmCadExtensao(Shell parent, Catalogador catalogador) {
		super(parent, SWT.DIALOG_TRIM | SWT.APPLICATION_MODAL);
		setText(Rotinas.getRecurso("FrmCadExtensao.titulo"));
		this.catalogador = catalogador;
		createContents();
		mudarLingua();
		CarregarExtensoesNaGrid(shell);
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
		shell.setSize(390, 380);
		shell.setText(getText());
		shell.setLayout(new FormLayout());

		Menu menu = new Menu(shell, SWT.BAR);
		shell.setMenuBar(menu);

		menuExtensao = new MenuItem(menu, SWT.CASCADE);
		menuExtensao.setText(Rotinas.getRecurso("FrmCadExtensao.menuExtensao"));

		Menu menu_1 = new Menu(menuExtensao);
		menuExtensao.setMenu(menu_1);

		menuIncluirExtensao = new MenuItem(menu_1, SWT.NONE);
		menuIncluirExtensao.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuIncluirExtensaoAction(e);
			}
		});
		menuIncluirExtensao.setText(Rotinas
				.getRecurso("FrmCadExtensao.menuIncluirExtensao"));

		menuExcluirExtensao = new MenuItem(menu_1, SWT.NONE);
		menuExcluirExtensao.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuExcluirExtensaoAction(e);
			}
		});
		menuExcluirExtensao.setText(Rotinas
				.getRecurso("FrmCadExtensao.menuExcluirExtensao"));

		menuExcluirTodasExtensoes = new MenuItem(menu_1, SWT.NONE);
		menuExcluirTodasExtensoes.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuExcluirTodasExtensoesAction(e);
			}
		});
		menuExcluirTodasExtensoes.setText(Rotinas
				.getRecurso("FrmCadExtensao.menuExcluirTodasExtensoes"));

		menuExportarTodos = new MenuItem(menu, SWT.CASCADE);
		menuExportarTodos.setText(Rotinas
				.getRecurso("FrmCadExtensao.menuExportarTodos"));

		Menu menu_2 = new Menu(menuExportarTodos);
		menuExportarTodos.setMenu(menu_2);

		menuExportarBitmap = new MenuItem(menu_2, SWT.NONE);
		menuExportarBitmap.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuExportarBitmapAction(e);
			}
		});
		menuExportarBitmap.setText(Rotinas
				.getRecurso("FrmCadExtensao.menuExportarBitmap"));

		menuExportarIcone = new MenuItem(menu_2, SWT.NONE);
		menuExportarIcone.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuExportarIconeAction(e);
			}
		});
		menuExportarIcone.setText(Rotinas
				.getRecurso("FrmCadExtensao.menuExportarIcone"));

		menuExportarGIF = new MenuItem(menu_2, SWT.NONE);
		menuExportarGIF.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuExportarGIFAction(e);
			}
		});
		menuExportarGIF.setText(Rotinas
				.getRecurso("FrmCadExtensao.menuExportarGIF"));

		menuExportarJPEG = new MenuItem(menu_2, SWT.NONE);
		menuExportarJPEG.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuExportarJPEGAction(e);
			}
		});
		menuExportarJPEG.setText(Rotinas
				.getRecurso("FrmCadExtensao.menuExportarJPEG"));

		menuExportarPNG = new MenuItem(menu_2, SWT.NONE);
		menuExportarPNG.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuExportarPNGAction(e);
			}
		});
		menuExportarPNG.setText(Rotinas
				.getRecurso("FrmCadExtensao.menuExportarPNG"));

		menuExportarTIFF = new MenuItem(menu_2, SWT.NONE);
		menuExportarTIFF.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuExportarTIFFAction(e);
			}
		});
		menuExportarTIFF.setText(Rotinas
				.getRecurso("FrmCadExtensao.menuExportarTIFF"));

		menuImportarTodos = new MenuItem(menu, SWT.CASCADE);
		menuImportarTodos.setText(Rotinas
				.getRecurso("FrmCadExtensao.menuImportarTodos"));

		Menu menu_3 = new Menu(menuImportarTodos);
		menuImportarTodos.setMenu(menu_3);

		menuImportarIconesArquivos = new MenuItem(menu_3, SWT.NONE);
		menuImportarIconesArquivos.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuImportarIconesArquivosAction(e);
			}
		});
		menuImportarIconesArquivos.setText(Rotinas
				.getRecurso("FrmCadExtensao.menuImportarIconesArquivos"));

		menuExtrairIconesArquivos = new MenuItem(menu_3, SWT.NONE);
		menuExtrairIconesArquivos.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuExtrairIconesArquivosAction(e);
			}
		});
		menuExtrairIconesArquivos.setText(Rotinas
				.getRecurso("FrmCadExtensao.menuExtrairIconesArquivos"));

		tabelaExtensao = new TabelaExtensao(shell);
		fd_tabelaExtensao = new FormData();
		fd_tabelaExtensao.height = 265;
		fd_tabelaExtensao.right = new FormAttachment(100);
		fd_tabelaExtensao.left = new FormAttachment(0);
		tabelaExtensao.setLayoutData(fd_tabelaExtensao);

		Composite composite = new Composite(shell, SWT.NONE);
		FormData fd_composite = new FormData();
		fd_composite.top = new FormAttachment(tabelaExtensao);
		fd_composite.bottom = new FormAttachment(300);
		fd_composite.right = new FormAttachment(100);
		fd_composite.left = new FormAttachment(0);
		composite.setLayoutData(fd_composite);

		btnIncluir = new Button(composite, SWT.CENTER);
		btnIncluir.setLocation(100, 10);
		btnIncluir.setSize(65, 25);
		btnIncluir.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				btnIncluirAction(e);
			}
		});
		btnIncluir.setText(Rotinas.getRecurso("FrmCadExtensao.btnIncluir"));

		btnExcluir = new Button(composite, SWT.CENTER);
		btnExcluir.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				btnExcluirAction(e);
			}
		});
		btnExcluir.setText(Rotinas.getRecurso("FrmCadExtensao.btnExcluir"));
		btnExcluir.setBounds(200, 10, 65, 25);

	}
	
	public Shell getShell(){
		return shell;
	}

	private void CarregarExtensoesNaGrid(Shell parent) {
		tabelaExtensao.getTabela().removeAll();
		tabelaExtensao.montaTabela(catalogador.listaExtensoes);
	}

	private void mudarLingua() {
		setText(Rotinas.getRecurso("FrmCadExtensao.titulo"));
		btnIncluir.setText(Rotinas.getRecurso("FrmCadExtensao.btnIncluir"));
		btnExcluir.setText(Rotinas.getRecurso("FrmCadExtensao.btnExcluir"));
		menuExtensao.setText(Rotinas.getRecurso("FrmCadExtensao.menuExtensao"));
		menuIncluirExtensao.setText(Rotinas
				.getRecurso("FrmCadExtensao.menuIncluirExtensao"));
		menuExcluirExtensao.setText(Rotinas
				.getRecurso("FrmCadExtensao.menuExcluirExtensao"));
		menuExcluirTodasExtensoes.setText(Rotinas
				.getRecurso("FrmCadExtensao.menuExcluirTodasExtensoes"));
		menuExportarTodos.setText(Rotinas
				.getRecurso("FrmCadExtensao.menuExportarTodos"));
		menuExportarBitmap.setText(Rotinas
				.getRecurso("FrmCadExtensao.menuExportarBitmap"));
		menuExportarIcone.setText(Rotinas
				.getRecurso("FrmCadExtensao.menuExportarIcone"));
		menuExportarGIF.setText(Rotinas
				.getRecurso("FrmCadExtensao.menuExportarGIF"));
		menuExportarJPEG.setText(Rotinas
				.getRecurso("FrmCadExtensao.menuExportarJPEG"));
		menuExportarPNG.setText(Rotinas
				.getRecurso("FrmCadExtensao.menuExportarPNG"));
		menuExportarTIFF.setText(Rotinas
				.getRecurso("FrmCadExtensao.menuExportarTIFF"));
		menuImportarTodos.setText(Rotinas
				.getRecurso("FrmCadExtensao.menuImportarTodos"));
		menuImportarIconesArquivos.setText(Rotinas
				.getRecurso("FrmCadExtensao.menuImportarIconesArquivos"));
		menuExtrairIconesArquivos.setText(Rotinas
				.getRecurso("FrmCadExtensao.menuExtrairIconesArquivos"));
	}

	private void btnIncluirAction(SelectionEvent evt) {
		menuIncluirExtensaoAction(null);
	}

	private void btnExcluirAction(SelectionEvent evt) {
		menuExcluirExtensaoAction(null);
	}

	private void menuIncluirExtensaoAction(SelectionEvent evt) {
		EscolhaArquivo escolha = new EscolhaArquivo(shell,
				EscolhaArquivo.PREVIEW_OPEN_DIALOG);
		String retval = escolha.mostrar();
		StringList log;

		if (retval.trim().length() > 0) {
			File arquivo = new File(retval);
			if (arquivo != null) {
				log = new StringList();
				try {
					if (ExtensaoBO.getInstancia().SalvarExtensao(
							catalogador.listaExtensoes, arquivo.getName(),
							arquivo.getAbsolutePath(), log)) {

						CarregarExtensoesNaGrid(shell);

						Dialogo.mensagemInfo(shell,
								"FrmCadExtensao.ExtensaoSalvaSucesso");
					} else {
						Dialogo.mensagemInfo(shell,
								"FrmCadExtensao.ExtensaoJaCadastrada");
					}
				} catch (SQLException ex) {
					Logger.getLogger(FrmCadExtensao.class.getName()).log(
							Level.SEVERE, null, ex);
				}
			}
		}
	}

	private void menuExcluirExtensaoAction(SelectionEvent evt) {
		Extensao extensao;

		if (catalogador.listaExtensoes.size() > 0) {
			int res = Dialogo.confirma(shell,
					"FrmCadExtensao.ExtensaoCertezaExcluir");
			if (res == SWT.YES) {
				extensao = ExtensaoBO.getInstancia().pegaExtensaoPorOrdem(
						catalogador.listaExtensoes,
						tabelaExtensao.getTabela().getSelectionIndex() + 1);

				try {
					if (ExtensaoBO.getInstancia().excluirExtensao(
							catalogador.listaExtensoes, extensao.getCodigo())) {
						CarregarExtensoesNaGrid(shell);
						Dialogo.mensagemInfo(shell,
								"FrmCadExtensao.ExtensaoExcluidaSucesso");
					}
				} catch (SQLException ex) {
					Logger.getLogger(FrmCadExtensao.class.getName()).log(
							Level.SEVERE, null, ex);
				}
			}
		}
	}

	private void menuExcluirTodasExtensoesAction(SelectionEvent evt) {
		if (catalogador.listaExtensoes.size() > 0) {
			int res = Dialogo.confirma(shell,
					"FrmCadExtensao.ExtensaoCertezaTodosExcluir");
			if (res == SWT.YES) {
				try {
					if (ExtensaoBO.getInstancia().excluirTodasExtensoes(
							catalogador.listaExtensoes)) {
						CarregarExtensoesNaGrid(shell);
						Dialogo.mensagemInfo(shell,
								"FrmCadExtensao.ExtensoesExcluidasSucesso");
					}
				} catch (SQLException ex) {
					Logger.getLogger(FrmCadExtensao.class.getName()).log(
							Level.SEVERE, null, ex);
				}
			}
		}

	}

	private void menuExportarIconeAction(SelectionEvent evt) {
		try {
			if (ExtensaoBO.getInstancia().ExportarExtensao(
					TipoExportarExtensao.teICO, catalogador.listaExtensoes)) {
				Dialogo.mensagemInfo(shell, "FrmCadExtensao.ExportarExtensao");
			}
		} catch (IOException ex) {
			Logger.getLogger(FrmCadExtensao.class.getName()).log(Level.SEVERE,
					null, ex);
		}
	}

	private void menuExportarGIFAction(SelectionEvent evt) {
		try {
			if (ExtensaoBO.getInstancia().ExportarExtensao(
					TipoExportarExtensao.teGIF, catalogador.listaExtensoes)) {
				Dialogo.mensagemInfo(shell, "FrmCadExtensao.ExportarExtensao");
			}
		} catch (IOException ex) {
			Logger.getLogger(FrmCadExtensao.class.getName()).log(Level.SEVERE,
					null, ex);
		}
	}

	private void menuExportarJPEGAction(SelectionEvent evt) {
		try {
			if (ExtensaoBO.getInstancia().ExportarExtensao(
					TipoExportarExtensao.teJPG, catalogador.listaExtensoes)) {
				Dialogo.mensagemInfo(shell, "FrmCadExtensao.ExportarExtensao");
			}
		} catch (IOException ex) {
			Logger.getLogger(FrmCadExtensao.class.getName()).log(Level.SEVERE,
					null, ex);
		}
	}

	private void menuExportarPNGAction(SelectionEvent evt) {
		try {
			if (ExtensaoBO.getInstancia().ExportarExtensao(
					TipoExportarExtensao.tePNG, catalogador.listaExtensoes)) {
				Dialogo.mensagemInfo(shell, "FrmCadExtensao.ExportarExtensao");
			}
		} catch (IOException ex) {
			Logger.getLogger(FrmCadExtensao.class.getName()).log(Level.SEVERE,
					null, ex);
		}
	}

	private void menuExportarTIFFAction(SelectionEvent evt) {
		try {
			if (ExtensaoBO.getInstancia().ExportarExtensao(
					TipoExportarExtensao.teTIF, catalogador.listaExtensoes)) {
				Dialogo.mensagemInfo(shell, "FrmCadExtensao.ExportarExtensao");
			}
		} catch (IOException ex) {
			Logger.getLogger(FrmCadExtensao.class.getName()).log(Level.SEVERE,
					null, ex);
		}
	}

	private void menuImportarIconesArquivosAction(SelectionEvent evt) {
		String sCaminho;
		EscolhaArquivo escolha = new EscolhaArquivo(shell,
				EscolhaArquivo.CUSTOM_DIALOG);
		String retval = escolha.mostrar();
		if (retval.trim().length() > 0) {
			File arquivo = new File(retval);

			if (arquivo != null) {
				sCaminho = arquivo.getPath();
				try {
					ExtensaoBO.getInstancia().ImportarExtensao(sCaminho,
							catalogador.listaExtensoes);
					CarregarExtensoesNaGrid(shell);
				} catch (SQLException ex) {
					Logger.getLogger(FrmCadExtensao.class.getName()).log(
							Level.SEVERE, null, ex);
				} catch (IOException ex) {
					Logger.getLogger(FrmCadExtensao.class.getName()).log(
							Level.SEVERE, null, ex);
				}
			}
		}
	}

	private void menuExtrairIconesArquivosAction(SelectionEvent evt) {
		String sCaminho;
		EscolhaArquivo escolha = new EscolhaArquivo(shell,
				EscolhaArquivo.CUSTOM_DIALOG);
		String retval = escolha.mostrar();
		if (retval.trim().length() > 0) {
			File arquivo = new File(retval);

			if (arquivo != null) {
				sCaminho = arquivo.getPath();
				try {
					ExtensaoBO.getInstancia().ExtrairExtensao(sCaminho,
							catalogador.listaExtensoes);
					CarregarExtensoesNaGrid(shell);
				} catch (SQLException ex) {
					Logger.getLogger(FrmCadExtensao.class.getName()).log(
							Level.SEVERE, null, ex);
				}
			}
		}
	}

	private void menuExportarBitmapAction(SelectionEvent evt) {
		try {
			ExtensaoBO.getInstancia().ExportarExtensao(
					TipoExportarExtensao.teBMP, catalogador.listaExtensoes);
		} catch (IOException ex) {
			Logger.getLogger(FrmCadExtensao.class.getName()).log(Level.SEVERE,
					null, ex);
		}
	}

}
