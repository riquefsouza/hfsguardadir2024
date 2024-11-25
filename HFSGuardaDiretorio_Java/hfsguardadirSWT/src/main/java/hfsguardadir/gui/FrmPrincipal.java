package hfsguardadir.gui;

import static hfsguardadir.comum.TipoExportar.teCSV;
import static hfsguardadir.comum.TipoExportar.teHTML;
import static hfsguardadir.comum.TipoExportar.teSQL;
import static hfsguardadir.comum.TipoExportar.teTXT;
import static hfsguardadir.comum.TipoExportar.teXML;
import hfsguardadir.catalogador.Catalogador;
import hfsguardadir.comum.Rotinas;
import hfsguardadir.comum.StringList;
import hfsguardadir.objetosgui.Arvore;
import hfsguardadir.objetosgui.Dialogo;
import hfsguardadir.objetosgui.Tabela;

import java.io.IOException;
import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;

import org.eclipse.swt.SWT;
import org.eclipse.swt.custom.SashForm;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.events.SelectionListener;
import org.eclipse.swt.layout.FormAttachment;
import org.eclipse.swt.layout.FormData;
import org.eclipse.swt.layout.FormLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Menu;
import org.eclipse.swt.widgets.MenuItem;
import org.eclipse.swt.widgets.ProgressBar;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.TabFolder;
import org.eclipse.swt.widgets.TabItem;
import org.eclipse.swt.widgets.Text;

public class FrmPrincipal {
    public FrmPrincipalProgresso frmPrincipalProgresso;
    private Catalogador catalogador;
	protected Shell shell;
	public TabFolder tabFolder;
	public Tabela tabelaPesquisa;
	public Tabela tabelaFixa;
	public Arvore arvoreFixa;
	public Text edtPesquisa;
	public SashForm sashFormPesquisa;
	public ProgressBar pb;
	public Label barraStatus1;
	public Label barraStatus2;	
	public MenuItem menuGravarLogImportacao;
		
	private MenuItem menuAba;
	private MenuItem menuDiretorio;
	private MenuItem menuExportarDiretoriosAbaAtiva;
	private MenuItem menuVisao;
	private MenuItem menuIncluirNovaAba;
	private MenuItem menuAlterarNomeAbaAtiva;
	private MenuItem menuExcluirAbaAtiva;
	private MenuItem menuImportarDiretorio;
	private MenuItem menuImportarSubDiretorios;
	private MenuItem menuCompararDiretorios;
	private MenuItem menuCadastrarExtensaoArquivo;
	private MenuItem menuExpandirDiretorios;
	private MenuItem menuColapsarDiretorios;
	private MenuItem menuTXT;
	private MenuItem menuCSV;
	private MenuItem menuHTML;
	private MenuItem menuXML;
	private MenuItem menuSQL;
	private MenuItem menuImportarDiretoriosViaXML;
	private MenuItem menuMostrarOcultarArvoreDirAbaAtiva;
	private MenuItem menuMostrarOcultarListaItensPesquisados;
	private MenuItem menuSobre;
	private MenuItem menuSobreCatalogador;
	
	private MenuItem menuIdioma;
	private MenuItem menuPortugues;
	private MenuItem menuIngles;
	private MenuItem menuEspanhol;
	private MenuItem menuFrances;
	private MenuItem menuItaliano;
	private MenuItem menuAlemao;
	private MenuItem menuJapones;
	private MenuItem menuCoreano;
	private MenuItem menuChinesTradicional;
	
	private Button btnImportarDiretorio;
	private Button btnPesquisa;

    public FrmPrincipal() {    	
    	createContents();    	
    	frmPrincipalProgresso = new FrmPrincipalProgresso(this);
    	catalogador = new Catalogador(this);
    	arvoreFixa.setCatalogador(catalogador);
    	tabelaFixa.setCatalogador(catalogador);
    	tabelaPesquisa.setCatalogador(catalogador);    	
    }
	
	public Shell getShell(){
		return this.shell;
	}
	
	public FrmPrincipalProgresso getFrmPrincipalProgresso(){
		return frmPrincipalProgresso;
	}
	
	/**
	 * Open the window.
	 */
	public void iniciar() {
		WindowOpened();

		shell.open();
		shell.layout();
		/*
		//Display display = Display.getDefault();		
		while (!shell.isDisposed()) {
			if (!display.readAndDispatch()) {
				display.sleep();
			}
		}
		*/
	}
	
	public void fechar(){
		WindowClosing();
		
		shell.close();
		shell.dispose();
	}
	
	/**
	 * Create contents of the window.
	 */
	protected void createContents() {
		shell = new Shell();
		shell.setSize(888, 472);
		shell.setText("HFSGuardaDiretorio 2.0 - Catalogador de Diretórios");
		shell.setLayout(new FormLayout());
		
		Menu menu = new Menu(shell, SWT.BAR);
		shell.setMenuBar(menu);

		menuAba = new MenuItem(menu, SWT.CASCADE);
		menuAba.setText("Aba");

		Menu menu_1 = new Menu(menuAba);
		menuAba.setMenu(menu_1);

		menuIncluirNovaAba = new MenuItem(menu_1, SWT.NONE);
		menuIncluirNovaAba.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuIncluirNovaAbaAction(e);
			}
		});
		menuIncluirNovaAba.setText("Incluir Nova Aba");

		menuAlterarNomeAbaAtiva = new MenuItem(menu_1, SWT.NONE);
		menuAlterarNomeAbaAtiva.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuAlterarNomeAbaAtivaAction(e);
			}
		});
		menuAlterarNomeAbaAtiva.setText("Alterar Nome da Aba Ativa");

		menuExcluirAbaAtiva = new MenuItem(menu_1, SWT.NONE);
		menuExcluirAbaAtiva.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuExcluirAbaAtivaAction(e);
			}
		});
		menuExcluirAbaAtiva.setText("Excluir Aba Ativa");

		menuDiretorio = new MenuItem(menu, SWT.CASCADE);
		menuDiretorio.setText("Diretório");

		Menu menu_2 = new Menu(menuDiretorio);
		menuDiretorio.setMenu(menu_2);

		menuImportarDiretorio = new MenuItem(menu_2, SWT.NONE);
		menuImportarDiretorio.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuImportarDiretorioAction(e);
			}
		});
		menuImportarDiretorio.setText("Importar Diretório");

		menuImportarSubDiretorios = new MenuItem(menu_2, SWT.NONE);
		menuImportarSubDiretorios.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuImportarSubDiretoriosAction(e);
			}
		});
		menuImportarSubDiretorios.setText("Importar Subdiretórios");

		menuCompararDiretorios = new MenuItem(menu_2, SWT.NONE);
		menuCompararDiretorios.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuCompararDiretoriosAction(e);
			}
		});
		menuCompararDiretorios.setText("Comparar Diretórios");

		menuCadastrarExtensaoArquivo = new MenuItem(menu_2, SWT.NONE);
		menuCadastrarExtensaoArquivo
				.addSelectionListener(new SelectionAdapter() {
					public void widgetSelected(SelectionEvent e) {
						menuCadastrarExtensaoArquivoAction(e);
					}
				});
		menuCadastrarExtensaoArquivo.setText("Cadastrar Extensão de Arquivo");

		new MenuItem(menu_2, SWT.SEPARATOR);

		menuExpandirDiretorios = new MenuItem(menu_2, SWT.NONE);
		menuExpandirDiretorios.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuExpandirDiretoriosAction(e);
			}
		});
		menuExpandirDiretorios.setText("Expandir Diretórios");

		menuColapsarDiretorios = new MenuItem(menu_2, SWT.NONE);
		menuColapsarDiretorios.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuColapsarDiretoriosAction(e);
			}
		});
		menuColapsarDiretorios.setText("Colapsar Diretórios");

		menuExportarDiretoriosAbaAtiva = new MenuItem(menu_2,
				SWT.CASCADE);
		menuExportarDiretoriosAbaAtiva
				.setText("Exportar Diretórios da Aba Ativa");

		Menu menu_3 = new Menu(menuExportarDiretoriosAbaAtiva);
		menuExportarDiretoriosAbaAtiva.setMenu(menu_3);

		menuTXT = new MenuItem(menu_3, SWT.NONE);
		menuTXT.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuTXTAction(e);
			}
		});
		menuTXT.setText("TXT");

		menuCSV = new MenuItem(menu_3, SWT.NONE);
		menuCSV.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuCSVAction(e);
			}
		});
		menuCSV.setText("CSV");

		menuHTML = new MenuItem(menu_3, SWT.NONE);
		menuHTML.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuHTMLAction(e);
			}
		});		
		menuHTML.setText("HTML");

		menuXML = new MenuItem(menu_3, SWT.NONE);
		menuXML.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuXMLAction(e);
			}
		});		
		menuXML.setText("XML");

		menuSQL = new MenuItem(menu_3, SWT.NONE);
		menuSQL.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuSQLAction(e);
			}
		});		
		menuSQL.setText("SQL");

		menuImportarDiretoriosViaXML = new MenuItem(menu_2, SWT.NONE);
		menuImportarDiretoriosViaXML.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuImportarDiretoriosViaXMLAction(e);
			}
		});			
		menuImportarDiretoriosViaXML.setText("Importar Diretórios Via XML");

		menuGravarLogImportacao = new MenuItem(menu_2, SWT.CHECK);
		menuGravarLogImportacao.setText("Gravar Log de Importação");

		menuVisao = new MenuItem(menu, SWT.CASCADE);
		menuVisao.setText("Visão");

		Menu menu_4 = new Menu(menuVisao);
		menuVisao.setMenu(menu_4);

		menuMostrarOcultarArvoreDirAbaAtiva = new MenuItem(menu_4,
				SWT.NONE);
		menuMostrarOcultarArvoreDirAbaAtiva.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuMostrarOcultarArvoreDirAbaAtivaAction(e);
			}
		});
		menuMostrarOcultarArvoreDirAbaAtiva
				.setText("Mostrar/Ocultar Árvore de Diretório da Aba Ativa");

		menuMostrarOcultarListaItensPesquisados = new MenuItem(menu_4,
				SWT.NONE);
		menuMostrarOcultarListaItensPesquisados.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuMostrarOcultarListaItensPesquisadosAction(e);
			}
		});
		menuMostrarOcultarListaItensPesquisados
				.setText("Mostrar/Ocultar Lista de Itens Pesquisados");

		menuIdioma = new MenuItem(menu, SWT.CASCADE);
        menuIdioma.setText(Rotinas.getRecurso("FrmPrincipal.menuIdioma"));

		Menu menu_5 = new Menu(menuIdioma);
		menuIdioma.setMenu(menu_5);
		
		menuPortugues = new MenuItem(menu_5, SWT.NONE);
		menuPortugues.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuPortuguesAction(e);
			}
		});
        menuPortugues.setText(Rotinas.getRecurso("FrmPrincipal.menuPortugues"));
		
		menuIngles = new MenuItem(menu_5, SWT.NONE);
		menuIngles.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuInglesAction(e);
			}
		});
        menuIngles.setText(Rotinas.getRecurso("FrmPrincipal.menuIngles"));
		
		menuEspanhol = new MenuItem(menu_5, SWT.NONE);
		menuEspanhol.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuEspanholAction(e);
			}
		});
        menuEspanhol.setText(Rotinas.getRecurso("FrmPrincipal.menuEspanhol"));
		
		menuFrances = new MenuItem(menu_5, SWT.NONE);
		menuFrances.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuFrancesAction(e);
			}
		});
        menuFrances.setText(Rotinas.getRecurso("FrmPrincipal.menuFrances"));
		
		menuItaliano = new MenuItem(menu_5, SWT.NONE);
		menuItaliano.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuItalianoAction(e);
			}
		});
        menuItaliano.setText(Rotinas.getRecurso("FrmPrincipal.menuItaliano"));
		
		menuAlemao = new MenuItem(menu_5, SWT.NONE);
		menuAlemao.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuAlemaoAction(e);
			}
		});
        menuAlemao.setText(Rotinas.getRecurso("FrmPrincipal.menuAlemao"));
		
		menuJapones = new MenuItem(menu_5, SWT.NONE);
		menuJapones.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuJaponesAction(e);
			}
		});
        menuJapones.setText(Rotinas.getRecurso("FrmPrincipal.menuJapones"));
		
		menuCoreano = new MenuItem(menu_5, SWT.NONE);
		menuCoreano.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuCoreanoAction(e);
			}
		});
        menuCoreano.setText(Rotinas.getRecurso("FrmPrincipal.menuCoreano"));
		
		menuChinesTradicional = new MenuItem(menu_5, SWT.NONE);
		menuChinesTradicional.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuChinesTradicionalAction(e);
			}
		});
        menuChinesTradicional.setText(Rotinas
                .getRecurso("FrmPrincipal.menuChinesTradicional"));

		menuSobre = new MenuItem(menu, SWT.CASCADE);
		menuSobre.setText("Sobre");

		Menu menu_6 = new Menu(menuSobre);
		menuSobre.setMenu(menu_6);

		menuSobreCatalogador = new MenuItem(menu_6, SWT.NONE);
		menuSobreCatalogador.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				menuSobreCatalogadorAction(e);
			}
		});
		menuSobreCatalogador.setText("Sobre o Catalogador");
		
		Composite compositeBarraFerra = new Composite(shell, SWT.NONE);
		compositeBarraFerra.setLayout(new FormLayout());
		FormData fd_compositeBarraFerra = new FormData();
		fd_compositeBarraFerra.left = new FormAttachment(0);
		fd_compositeBarraFerra.right = new FormAttachment(100);
		compositeBarraFerra.setLayoutData(fd_compositeBarraFerra);	
		
		btnImportarDiretorio = new Button(compositeBarraFerra, SWT.NONE);
		btnImportarDiretorio.setBounds(0, 0, 105, 25);
		FormData fd_btnImportarDiretorio = new FormData();
		fd_btnImportarDiretorio.right = new FormAttachment(0, 139);
		fd_btnImportarDiretorio.top = new FormAttachment(0);
		fd_btnImportarDiretorio.left = new FormAttachment(0);
		btnImportarDiretorio.setLayoutData(fd_btnImportarDiretorio);
		btnImportarDiretorio.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				btnImportarDiretorioAction(e);
			}
		});		
		btnImportarDiretorio.setText("Importar Diretório");

		Composite compositeBarraStatus = new Composite(shell, SWT.NONE);
		compositeBarraStatus.setLayout(new FormLayout());
		FormData fd_compositeBarraStatus = new FormData();
		fd_compositeBarraStatus.left = new FormAttachment(0);
		fd_compositeBarraStatus.right = new FormAttachment(100);
		fd_compositeBarraStatus.bottom = new FormAttachment(100);
		compositeBarraStatus.setLayoutData(fd_compositeBarraStatus);

		barraStatus1 = new Label(compositeBarraStatus, SWT.BORDER);
		FormData fd_barraStatus1 = new FormData();
		fd_barraStatus1.right = new FormAttachment(0, 400);
		fd_barraStatus1.top = new FormAttachment(0);
		fd_barraStatus1.left = new FormAttachment(0);
		barraStatus1.setLayoutData(fd_barraStatus1);
		barraStatus1.setText("Quantidade Total: , Tamanho Total:");

		barraStatus2 = new Label(compositeBarraStatus, SWT.BORDER);
		FormData fd_barraStatus2 = new FormData();
		fd_barraStatus2.right = new FormAttachment(100);
		fd_barraStatus2.top = new FormAttachment(0);
		fd_barraStatus2.left = new FormAttachment(0, 400);
		barraStatus2.setLayoutData(fd_barraStatus2);

		sashFormPesquisa = new SashForm(shell, SWT.VERTICAL);
		FormData fd_sashFormPesquisa = new FormData();
		fd_sashFormPesquisa.top = new FormAttachment(compositeBarraFerra);
		
		pb = new ProgressBar(compositeBarraFerra, SWT.NONE);
		FormData fd_pb = new FormData();
		fd_pb.width = 385;
		fd_pb.left = new FormAttachment(0, 109);
		fd_pb.height = 17;
		fd_pb.top = new FormAttachment(0, 3);
		pb.setLayoutData(fd_pb);
		
		edtPesquisa = new Text(compositeBarraFerra, SWT.BORDER | SWT.SEARCH);
		FormData fd_edtPesquisa = new FormData();
		fd_edtPesquisa.top = new FormAttachment(0, 2);
		fd_edtPesquisa.left = new FormAttachment(pb);
		fd_edtPesquisa.width = 276;		
		edtPesquisa.setLayoutData(fd_edtPesquisa);
		edtPesquisa.setTextLimit(255);
		
		btnPesquisa = new Button(compositeBarraFerra, SWT.NONE);
		FormData fd_btnPesquisa = new FormData();
		fd_btnPesquisa.width = 95;
		fd_btnPesquisa.left = new FormAttachment(edtPesquisa);
		btnPesquisa.setLayoutData(fd_btnPesquisa);
		btnPesquisa.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				btnPesquisaAction(e);
			}
		});
		btnPesquisa.setText("Pesquisar");
		shell.setDefaultButton(btnPesquisa);
		
		fd_sashFormPesquisa.bottom = new FormAttachment(compositeBarraStatus);
		fd_sashFormPesquisa.left = new FormAttachment(0);
		fd_sashFormPesquisa.right = new FormAttachment(100);
		
		sashFormPesquisa.setLayoutData(fd_sashFormPesquisa);

		tabFolder = new TabFolder(sashFormPesquisa, SWT.NONE);
		tabFolder.addSelectionListener(new SelectionListener() {
			@Override
			public void widgetSelected(SelectionEvent evt) {
				tabFolderChanged(evt);
			}
			
			@Override
			public void widgetDefaultSelected(SelectionEvent evt) {
				tabFolderChanged(evt);
			}
		});

        tabelaPesquisa = new Tabela(sashFormPesquisa, false);
        sashFormPesquisa.setWeights(new int[] {1, 0});
				
		TabItem tbFixa = new TabItem(tabFolder, SWT.NONE);
		tbFixa.setText("DISCO 1");
		tbFixa.setImage(Rotinas.getImagem(shell, "cdouro.gif"));
		
		final SashForm sashFormAba1 = new SashForm(tabFolder, SWT.NONE);
        tbFixa.setControl(sashFormAba1);
		
		arvoreFixa = new Arvore(sashFormAba1);
		arvoreFixa.getArvore().addSelectionListener(new SelectionListener() {			
			@Override
			public void widgetSelected(SelectionEvent evt) {
				catalogador.arvoreValorMudou(evt);
			}			
			@Override
			public void widgetDefaultSelected(SelectionEvent evt) {
				catalogador.arvoreValorMudou(evt);
			}
		});
		
		tabelaFixa = new Tabela(sashFormAba1, true);
		tabelaFixa.setSombrearLinhas(true);
		sashFormAba1.setWeights(new int[] {1, 3});
	}

    private void setIdiomaPadrao(String lingua) {
        switch (lingua) {
            case "pt":
                menuPortugues.setSelection(true);
                break;
            case "en":
                menuIngles.setSelection(true);
                break;
            case "es":
                menuEspanhol.setSelection(true);
                break;
            case "fr":
                menuFrances.setSelection(true);
                break;
            case "it":
                menuItaliano.setSelection(true);
                break;
            case "de":
                menuAlemao.setSelection(true);
                break;
            case "ja":
                menuJapones.setSelection(true);
                break;
            case "ko":
                menuCoreano.setSelection(true);
                break;
            case "zh":
                menuChinesTradicional.setSelection(true);
                break;
        }
    }

    public void mudarLingua() {
        shell.setText(Rotinas.getRecurso("FrmPrincipal.titulo"));        
        barraStatus1.setText(Rotinas.getRecurso("FrmPrincipal.barraStatus1"));
        btnImportarDiretorio.setText(
                Rotinas.getRecurso("FrmPrincipal.btnImportarDiretorio"));
        btnPesquisa.setText(Rotinas.getRecurso("FrmPrincipal.btnPesquisa"));
        menuAba.setText(Rotinas.getRecurso("FrmPrincipal.menuAba"));
        menuIncluirNovaAba.setText(Rotinas
                .getRecurso("FrmPrincipal.menuIncluirNovaAba"));
        menuAlterarNomeAbaAtiva.setText(
                Rotinas.getRecurso("FrmPrincipal.menuAlterarNomeAbaAtiva"));
        menuExcluirAbaAtiva.setText(
                Rotinas.getRecurso("FrmPrincipal.menuExcluirAbaAtiva"));
                
        menuDiretorio.setText(Rotinas.getRecurso("FrmPrincipal.menuDiretorio"));
        menuImportarDiretorio.setText(
                Rotinas.getRecurso("FrmPrincipal.menuImportarDiretorio"));
        menuImportarSubDiretorios.setText(
                Rotinas.getRecurso("FrmPrincipal.menuImportarSubDiretorios"));
        menuCompararDiretorios.setText(
                Rotinas.getRecurso("FrmPrincipal.menuCompararDiretorios"));
        menuCadastrarExtensaoArquivo.setText(
                Rotinas.getRecurso("FrmPrincipal.menuCadastrarExtensaoArquivo"));
        menuExpandirDiretorios.setText(
                Rotinas.getRecurso("FrmPrincipal.menuExpandirDiretorios"));
        menuColapsarDiretorios.setText(
                Rotinas.getRecurso("FrmPrincipal.menuColapsarDiretorios"));
        menuExportarDiretoriosAbaAtiva.setText(
                Rotinas.getRecurso("FrmPrincipal.menuExportarDiretoriosAbaAtiva"));
        menuImportarDiretoriosViaXML.setText(
                Rotinas.getRecurso("FrmPrincipal.menuImportarDiretoriosViaXML"));
        menuGravarLogImportacao.setText(
                Rotinas.getRecurso("FrmPrincipal.menuGravarLogImportacao"));
                
        menuVisao.setText(Rotinas.getRecurso("FrmPrincipal.menuVisao"));
        menuMostrarOcultarArvoreDirAbaAtiva.setText(
                Rotinas.getRecurso("FrmPrincipal.menuMostrarOcultarArvoreDirAbaAtiva"));
        menuMostrarOcultarListaItensPesquisados.setText(
                Rotinas.getRecurso("FrmPrincipal.menuMostrarOcultarListaItensPesquisados"));
                
        menuIdioma.setText(Rotinas.getRecurso("FrmPrincipal.menuIdioma"));
        menuPortugues.setText(Rotinas.getRecurso("FrmPrincipal.menuPortugues"));
        menuIngles.setText(Rotinas.getRecurso("FrmPrincipal.menuIngles"));
        menuEspanhol.setText(Rotinas.getRecurso("FrmPrincipal.menuEspanhol"));
        menuFrances.setText(Rotinas.getRecurso("FrmPrincipal.menuFrances"));
        menuItaliano.setText(Rotinas.getRecurso("FrmPrincipal.menuItaliano"));
        menuAlemao.setText(Rotinas.getRecurso("FrmPrincipal.menuAlemao"));
        menuJapones.setText(Rotinas.getRecurso("FrmPrincipal.menuJapones"));
        menuCoreano.setText(Rotinas.getRecurso("FrmPrincipal.menuCoreano"));
        menuChinesTradicional.setText(Rotinas
                .getRecurso("FrmPrincipal.menuChinesTradicional"));
        
        menuSobre.setText(Rotinas.getRecurso("FrmPrincipal.menuSobre"));
        menuSobreCatalogador.setText(
                Rotinas.getRecurso("FrmPrincipal.menuSobreCatalogador"));        
    }
    
    public Catalogador getCatalogador(){
        return catalogador;
    }

    private void menuIncluirNovaAbaAction(SelectionEvent evt) {
        try {
            catalogador.IncluirNovaAba();
        } catch (SQLException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private void menuAlterarNomeAbaAtivaAction(SelectionEvent evt) {
        try {
            catalogador.AlterarNomeAbaAtiva(frmPrincipalProgresso);
        } catch (SQLException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private void menuExcluirAbaAtivaAction(SelectionEvent evt) {
        try {
            catalogador.ExcluirAbaAtiva(frmPrincipalProgresso);
        } catch (SQLException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private void menuImportarDiretorioAction(SelectionEvent evt) {
        try {
            catalogador.ComecaImportacao(false, frmPrincipalProgresso);
        } catch (SQLException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private void menuImportarSubDiretoriosAction(SelectionEvent evt) {
        try {
            catalogador.ComecaImportacao(true, frmPrincipalProgresso);
        } catch (SQLException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private void menuCompararDiretoriosAction(SelectionEvent evt) {
		FrmCompararDiretorio frmCompararDiretorio = new FrmCompararDiretorio(shell, catalogador);
		Rotinas.CentralizaDlg(shell, frmCompararDiretorio.getShell());
		frmCompararDiretorio.open();
    }

    private void menuCadastrarExtensaoArquivoAction(SelectionEvent evt) {
		FrmCadExtensao frmCadExtensao = new FrmCadExtensao(shell, catalogador);
		Rotinas.CentralizaDlg(shell, frmCadExtensao.getShell());
		frmCadExtensao.open();
    }

    private void menuExpandirDiretoriosAction(SelectionEvent evt) {
        catalogador.getArvoreAtual().expandeTodos(true);
    }

    private void menuColapsarDiretoriosAction(SelectionEvent evt) {
        catalogador.getArvoreAtual().expandeTodos(false);
    }

    private void menuTXTAction(SelectionEvent evt) {
        try {
            catalogador.ExportarArquivo(teTXT, frmPrincipalProgresso);
        } catch (SQLException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private void menuCSVAction(SelectionEvent evt) {
        try {
            catalogador.ExportarArquivo(teCSV, frmPrincipalProgresso);
        } catch (SQLException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private void menuHTMLAction(SelectionEvent evt) {
        try {
            catalogador.ExportarArquivo(teHTML, frmPrincipalProgresso);
        } catch (SQLException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private void menuXMLAction(SelectionEvent evt) {
        try {
            catalogador.ExportarArquivo(teXML, frmPrincipalProgresso);
        } catch (SQLException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private void menuSQLAction(SelectionEvent evt) {
        try {
            catalogador.ExportarArquivo(teSQL, frmPrincipalProgresso);
        } catch (SQLException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private void menuImportarDiretoriosViaXMLAction(SelectionEvent evt) {
        StringList log = new StringList();
        try {
            catalogador.ImportarArquivo(log, frmPrincipalProgresso);
        } catch (IOException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        } catch (SQLException ex) {
            Logger.getLogger(FrmPrincipal.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private void menuMostrarOcultarArvoreDirAbaAtivaAction(SelectionEvent evt) {
        catalogador.mostrarOcultarArvore();
    }

    private void menuMostrarOcultarListaItensPesquisadosAction(SelectionEvent evt) {
		if (sashFormPesquisa.getWeights()[1]==0)
			sashFormPesquisa.setWeights(new int[] {2, 1});
		else
			sashFormPesquisa.setWeights(new int[] {1, 0});
    }

    private void btnImportarDiretorioAction(SelectionEvent evt) {
        menuImportarDiretorioAction(evt);
    }

    private void btnPesquisaAction(SelectionEvent evt) {
        catalogador.Pesquisar();
    }

    private void WindowOpened() {
    	//shell.setCursor(new Cursor(shell.getDisplay(), SWT.CURSOR_WAIT));        
        this.setIdiomaPadrao(Rotinas.getParams().getLocalidadeLingua());       
    	//shell.setCursor(new Cursor(shell.getDisplay(), SWT.CURSOR_ARROW));
    }

    private void WindowClosing() {
        try {
            Rotinas.Desconectar();
        } catch (SQLException e) {
                Dialogo.mensagemErro(shell, "FrmPrincipal.ErroDesconectar", e
                                .getLocalizedMessage());
        }
    }

    private void tabFolderChanged(SelectionEvent evt) {
        if (catalogador != null) {
            catalogador.tabPanelMudou();
        }
    }

    private void menuSobreCatalogadorAction(SelectionEvent evt) {
		FrmSobre frmSobre = new FrmSobre(shell);
		Rotinas.CentralizaDlg(shell, frmSobre.getShell());
		frmSobre.open();
    }

    private void menuPortuguesAction(SelectionEvent evt) {
        catalogador.mudarLingua("pt");
    }

    private void menuInglesAction(SelectionEvent evt) {
        catalogador.mudarLingua("en");
    }

    private void menuEspanholAction(SelectionEvent evt) {
        catalogador.mudarLingua("es");
    }

    private void menuFrancesAction(SelectionEvent evt) {
        catalogador.mudarLingua("fr");
    }

    private void menuItalianoAction(SelectionEvent evt) {
        catalogador.mudarLingua("it");
    }

    private void menuAlemaoAction(SelectionEvent evt) {
        catalogador.mudarLingua("de");
    }

    private void menuJaponesAction(SelectionEvent evt) {
        catalogador.mudarLingua("ja");
    }

    private void menuCoreanoAction(SelectionEvent evt) {
        catalogador.mudarLingua("ko");
    }

    private void menuChinesTradicionalAction(SelectionEvent evt) {
        catalogador.mudarLingua("zh");
    }
    
}
