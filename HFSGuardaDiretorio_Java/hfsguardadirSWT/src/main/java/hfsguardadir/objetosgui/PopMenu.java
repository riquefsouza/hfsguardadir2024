package hfsguardadir.objetosgui;

import hfsguardadir.catalogador.Catalogador;
import hfsguardadir.comum.Rotinas;
import hfsguardadir.gui.FrmInfoDiretorio;
import hfsguardadir.gui.FrmPrincipal;
import hfsguardadir.objetos.Aba;
import hfsguardadir.objetos.Diretorio;

import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.widgets.Menu;
import org.eclipse.swt.widgets.MenuItem;
import org.eclipse.swt.widgets.Shell;

public class PopMenu {
	private Shell shell;
	private Catalogador catalogador;

	private Menu menuPopup;
	private MenuItem menuInformacoesDiretorioArquivo;
	private MenuItem menuExcluirDiretorioSelecionado;
	private MenuItem menuExpandirDiretorios2;
	private MenuItem menuColapsarDiretorios2;
	private MenuItem menuIncluirNovaAba2;
	private MenuItem menuAlterarNomeAbaAtiva2;
	private MenuItem menuExcluirAbaAtiva2;

	public PopMenu(Catalogador catalogador) {
		this.shell = catalogador.getForm().getShell();
		this.catalogador = catalogador;
		createContents();
	}

	public void mostrar(int x, int y) {
		menuPopup.setLocation(x, y);
		menuPopup.setVisible(true);

		while (!menuPopup.isDisposed() && menuPopup.isVisible()) {
			if (!shell.getDisplay().readAndDispatch())
				shell.getDisplay().sleep();
		}
		
		menuPopup.dispose();
	}

	public void createContents() {
		menuPopup = new Menu(shell, SWT.POP_UP);

		menuInformacoesDiretorioArquivo = new MenuItem(menuPopup, SWT.NONE);
		menuInformacoesDiretorioArquivo
				.addSelectionListener(new SelectionAdapter() {
					public void widgetSelected(SelectionEvent e) {
						menuInformacoesDiretorioArquivoAction(e);
					}
				});
		menuInformacoesDiretorioArquivo.setText(Rotinas
				.getRecurso("FrmPrincipal.menuInformacoesDiretorioArquivo"));

		menuExcluirDiretorioSelecionado = new MenuItem(menuPopup, SWT.NONE);
		menuExcluirDiretorioSelecionado
				.addSelectionListener(new SelectionAdapter() {
					public void widgetSelected(SelectionEvent e) {
						menuExcluirDiretorioSelecionadoAction(e);
					}
				});
		menuExcluirDiretorioSelecionado.setText(Rotinas
				.getRecurso("FrmPrincipal.menuExcluirDiretorioSelecionado"));

		menuExpandirDiretorios2 = new MenuItem(menuPopup, SWT.NONE);
		menuExpandirDiretorios2.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuExpandirDiretorios2Action(e);
			}
		});
		menuExpandirDiretorios2.setText(Rotinas
				.getRecurso("FrmPrincipal.menuExpandirDiretorios"));

		menuColapsarDiretorios2 = new MenuItem(menuPopup, SWT.NONE);
		menuColapsarDiretorios2.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuColapsarDiretorios2Action(e);
			}
		});
		menuColapsarDiretorios2.setText(Rotinas
				.getRecurso("FrmPrincipal.menuColapsarDiretorios"));

		menuIncluirNovaAba2 = new MenuItem(menuPopup, SWT.NONE);
		menuIncluirNovaAba2.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuIncluirNovaAba2Action(e);
			}
		});
		menuIncluirNovaAba2.setText(Rotinas
				.getRecurso("FrmPrincipal.menuIncluirNovaAba"));

		menuAlterarNomeAbaAtiva2 = new MenuItem(menuPopup, SWT.NONE);
		menuAlterarNomeAbaAtiva2.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuAlterarNomeAbaAtiva2Action(e);
			}
		});
		menuAlterarNomeAbaAtiva2.setText(Rotinas
				.getRecurso("FrmPrincipal.menuAlterarNomeAbaAtiva"));

		menuExcluirAbaAtiva2 = new MenuItem(menuPopup, SWT.NONE);
		menuExcluirAbaAtiva2.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuExcluirAbaAtiva2Action(e);
			}
		});
		menuExcluirAbaAtiva2.setText(Rotinas
				.getRecurso("FrmPrincipal.menuExcluirAbaAtiva"));
	}

	private void menuInformacoesDiretorioArquivoAction(SelectionEvent evt) {
		FrmInfoDiretorio frmInfo;
		Tabela tabela = catalogador.getTabelaAtual();
		if (tabela.getTabela().getSelectionCount() > 0) {
			frmInfo = new FrmInfoDiretorio(shell);
			Aba aba = catalogador.getAbaSelecionada();
			Diretorio dir = tabela.getLinhaSelecionada(false);
			dir.getAba().setNome(aba.getNome());
			frmInfo.setDiretorio(dir);
			Rotinas.CentralizaDlg(shell, frmInfo.getShell());
			frmInfo.open();			
		}
	}

	private void menuExcluirDiretorioSelecionadoAction(SelectionEvent evt) {
		try {
			catalogador.ExcluirDiretorioSelecionado(catalogador.getForm().getFrmPrincipalProgresso());
		} catch (SQLException ex) {
			Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE,
					null, ex);
		}
	}

	private void menuExpandirDiretorios2Action(SelectionEvent evt) {
		catalogador.getArvoreAtual().expandeTodos(true);
	}

	private void menuColapsarDiretorios2Action(SelectionEvent evt) {
		catalogador.getArvoreAtual().expandeTodos(false);
	}

	private void menuIncluirNovaAba2Action(SelectionEvent evt) {
		try {
			catalogador.IncluirNovaAba();
		} catch (SQLException ex) {
			Logger.getLogger(PopMenu.class.getName()).log(Level.SEVERE, null,
					ex);
		}

	}

	private void menuAlterarNomeAbaAtiva2Action(SelectionEvent evt) {
		try {
			catalogador.AlterarNomeAbaAtiva(catalogador.getForm().getFrmPrincipalProgresso());
		} catch (SQLException ex) {
			Logger.getLogger(PopMenu.class.getName()).log(Level.SEVERE, null,
					ex);
		}

	}

	private void menuExcluirAbaAtiva2Action(SelectionEvent evt) {
		try {
			catalogador.ExcluirAbaAtiva(catalogador.getForm().getFrmPrincipalProgresso());
		} catch (SQLException ex) {
			Logger.getLogger(PopMenu.class.getName()).log(Level.SEVERE, null,
					ex);
		}
	}

}
