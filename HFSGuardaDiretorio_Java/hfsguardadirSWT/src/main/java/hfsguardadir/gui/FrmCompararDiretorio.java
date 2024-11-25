package hfsguardadir.gui;

import hfsguardadir.catalogador.Catalogador;
import hfsguardadir.comum.Rotinas;
import hfsguardadir.comum.StringList;
import hfsguardadir.objetos.Aba;
import hfsguardadir.objetos.Diretorio;
import hfsguardadir.objetosbo.AbaBO;
import hfsguardadir.objetosbo.DiretorioBO;
import hfsguardadir.objetosgui.Arvore;
import hfsguardadir.objetosgui.Dialogo;
import hfsguardadir.objetosgui.Tabela;

import java.io.IOException;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Date;
import java.util.logging.Level;
import java.util.logging.Logger;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.events.SelectionListener;
import org.eclipse.swt.graphics.Cursor;
import org.eclipse.swt.layout.FillLayout;
import org.eclipse.swt.layout.FormAttachment;
import org.eclipse.swt.layout.FormData;
import org.eclipse.swt.layout.FormLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Combo;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Dialog;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Group;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.ProgressBar;
import org.eclipse.swt.widgets.Shell;

public class FrmCompararDiretorio extends Dialog {

	protected Object result;
	protected Shell shell;
	public ProgressBar pb;

	private FormData fd_tabelaComparador;
	private Button btnCompararDiretorios;
	private Button btnSalvarLog;
	private Group groupDiretorio1;
	private Group groupDiretorio2;
	private Combo cmbAba1;
	private Combo cmbAba2;
	private Label labDiferencasEncontradas;
	private Label barraStatus1;
	private Label barraStatus2;
	
	private FrmCompararDiretorioProgresso frmCompararDiretorioProgresso;
	private final Catalogador catalogador;

	private Arvore arvoreDiretorio1;
	private Arvore arvoreDiretorio2;

	public Tabela tabelaCompara;
	public ArrayList<Diretorio> listaCompara;

	/**
	 * Create the dialog.
	 * 
	 * @param parent
	 * @param style
	 */
	public FrmCompararDiretorio(Shell parent, Catalogador catalogador) {
		super(parent, SWT.DIALOG_TRIM | SWT.APPLICATION_MODAL);
		setText("Comparar Diretórios");
		createContents();

		mudarLingua();

		montarArvores();
		listaCompara = new ArrayList<>();
		frmCompararDiretorioProgresso = new FrmCompararDiretorioProgresso(this);

		this.catalogador = catalogador;

		LimparComparacao();
	}

	/**
	 * Open the dialog.
	 * 
	 * @return the result
	 */
	public Object open() {
		WindowOpened();
		
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
		shell = new Shell(getParent(), getStyle());
		shell.setSize(688, 572);
		shell.setText(getText());
		shell.setLayout(new FormLayout());

		Composite compositeBarraFerra = new Composite(shell, SWT.NONE);
		compositeBarraFerra.setLayout(new FormLayout());
		FormData fd_compositeBarraFerra = new FormData();
		fd_compositeBarraFerra.left = new FormAttachment(0);
		fd_compositeBarraFerra.right = new FormAttachment(100);
		compositeBarraFerra.setLayoutData(fd_compositeBarraFerra);

		btnCompararDiretorios = new Button(compositeBarraFerra, SWT.NONE);
		btnCompararDiretorios.setBounds(0, 0, 135, 25);
		FormData fd_btnCompararDiretorios = new FormData();
		fd_btnCompararDiretorios.right = new FormAttachment(0, 169);
		fd_btnCompararDiretorios.top = new FormAttachment(0);
		fd_btnCompararDiretorios.left = new FormAttachment(0);
		btnCompararDiretorios.setLayoutData(fd_btnCompararDiretorios);
		btnCompararDiretorios.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				btnCompararDiretoriosAction(e);
			}
		});
		btnCompararDiretorios.setText(Rotinas
				.getRecurso("FrmCompararDiretorio.btnCompararDiretorios"));

		pb = new ProgressBar(compositeBarraFerra, SWT.NONE);
		FormData fd_pb = new FormData();
		fd_pb.width = 450;
		fd_pb.left = new FormAttachment(0, 118);
		fd_pb.height = 17;
		fd_pb.top = new FormAttachment(0, 3);
		pb.setLayoutData(fd_pb);

		btnSalvarLog = new Button(compositeBarraFerra, SWT.NONE);
		FormData fd_btnSalvarLog = new FormData();
		fd_btnSalvarLog.width = 100;		
		fd_btnSalvarLog.left = new FormAttachment(pb);
		btnSalvarLog.setLayoutData(fd_btnSalvarLog);
		btnSalvarLog.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				btnSalvarLogAction(e);
			}
		});
		btnSalvarLog.setText(Rotinas
				.getRecurso("FrmCompararDiretorio.btnSalvarLog"));

		Composite compositeCentral = new Composite(shell, SWT.NONE);
		compositeCentral.setLayout(new FormLayout());
		FormData fd_compositeCentral = new FormData();
		fd_compositeCentral.bottom = new FormAttachment(97);
		fd_compositeCentral.top = new FormAttachment(compositeBarraFerra);
		fd_compositeCentral.left = new FormAttachment(0);
		fd_compositeCentral.right = new FormAttachment(100);
		compositeCentral.setLayoutData(fd_compositeCentral);

		Composite compositeDiretorios = new Composite(compositeCentral,
				SWT.NONE);
		compositeDiretorios.setLayout(new FillLayout(SWT.HORIZONTAL));
		FormData fd_compositeDiretorios = new FormData();
		fd_compositeDiretorios.height = 284;
		fd_compositeDiretorios.right = new FormAttachment(100);
		fd_compositeDiretorios.left = new FormAttachment(0);
		compositeDiretorios.setLayoutData(fd_compositeDiretorios);

		groupDiretorio1 = new Group(compositeDiretorios, SWT.NONE);
		groupDiretorio1.setText(Rotinas
				.getRecurso("FrmCompararDiretorio.panelDiretorio1"));
		groupDiretorio1.setBounds(0, 0, 70, 82);
		groupDiretorio1.setLayout(new FormLayout());

		cmbAba1 = new Combo(groupDiretorio1, SWT.READ_ONLY);
		FormData fd_cmbAba1 = new FormData();
		fd_cmbAba1.top = new FormAttachment(0);
		fd_cmbAba1.left = new FormAttachment(0);
		fd_cmbAba1.right = new FormAttachment(100);
		cmbAba1.setLayoutData(fd_cmbAba1);
		cmbAba1.addSelectionListener(new SelectionListener() {			
			@Override
			public void widgetSelected(SelectionEvent evt) {
				cmbAba1Action(evt);				
			}
			
			@Override
			public void widgetDefaultSelected(SelectionEvent evt) {
				cmbAba1Action(evt);				
			}
		});

		arvoreDiretorio1 = new Arvore(groupDiretorio1);
		FormData fd_arvoreDiretorio1 = new FormData();
		fd_arvoreDiretorio1.top = new FormAttachment(cmbAba1);
		fd_arvoreDiretorio1.right = new FormAttachment(100);
		fd_arvoreDiretorio1.left = new FormAttachment(0);
		fd_arvoreDiretorio1.bottom = new FormAttachment(100);
		arvoreDiretorio1.setLayoutData(fd_arvoreDiretorio1);

		groupDiretorio2 = new Group(compositeDiretorios, SWT.NONE);
		groupDiretorio2.setText(Rotinas
				.getRecurso("FrmCompararDiretorio.panelDiretorio2"));
		groupDiretorio2.setBounds(0, 0, 70, 82);
		groupDiretorio2.setLayout(new FormLayout());

		cmbAba2 = new Combo(groupDiretorio2, SWT.READ_ONLY);
		FormData fd_cmbAba2 = new FormData();
		fd_cmbAba2.top = new FormAttachment(0);
		fd_cmbAba2.right = new FormAttachment(100);
		fd_cmbAba2.left = new FormAttachment(0);
		cmbAba2.setLayoutData(fd_cmbAba2);
		cmbAba2.addSelectionListener(new SelectionListener() {			
			@Override
			public void widgetSelected(SelectionEvent evt) {
				cmbAba2Action(evt);				
			}
			
			@Override
			public void widgetDefaultSelected(SelectionEvent evt) {
				cmbAba2Action(evt);				
			}
		});

		arvoreDiretorio2 = new Arvore(groupDiretorio2);
		FormData fd_arvoreDiretorio2 = new FormData();
		fd_arvoreDiretorio2.top = new FormAttachment(cmbAba2);
		fd_arvoreDiretorio2.bottom = new FormAttachment(100);
		fd_arvoreDiretorio2.right = new FormAttachment(100);
		fd_arvoreDiretorio2.left = new FormAttachment(0);
		arvoreDiretorio2.setLayoutData(fd_arvoreDiretorio2);

		labDiferencasEncontradas = new Label(compositeCentral, SWT.NONE);
		FormData fd_labDiferencasEncontradas = new FormData();
		fd_labDiferencasEncontradas.top = new FormAttachment(
				compositeDiretorios);
		fd_labDiferencasEncontradas.right = new FormAttachment(100);
		fd_labDiferencasEncontradas.left = new FormAttachment(0);
		labDiferencasEncontradas.setLayoutData(fd_labDiferencasEncontradas);
		labDiferencasEncontradas.setText(Rotinas
				.getRecurso("FrmCompararDiretorio.labDiferencasEncontradas"));

		tabelaCompara = new Tabela(compositeCentral, true);
		fd_tabelaComparador = new FormData();
		fd_tabelaComparador.bottom = new FormAttachment(100);
		fd_tabelaComparador.top = new FormAttachment(labDiferencasEncontradas);
		fd_tabelaComparador.right = new FormAttachment(100);
		fd_tabelaComparador.left = new FormAttachment(0);
		tabelaCompara.setLayoutData(fd_tabelaComparador);

		Composite compositeBarraStatus = new Composite(shell, SWT.NONE);
		compositeBarraStatus.setLayout(new FormLayout());
		FormData fd_compositeBarraStatus = new FormData();
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
				.getRecurso("FrmCompararDiretorio.barraStatus1"));

		barraStatus2 = new Label(compositeBarraStatus, SWT.BORDER);
		FormData fd_barraStatus2 = new FormData();
		fd_barraStatus2.right = new FormAttachment(100);
		fd_barraStatus2.top = new FormAttachment(0);
		fd_barraStatus2.left = new FormAttachment(0, 200);
		barraStatus2.setLayoutData(fd_barraStatus2);

	}
	
	public Shell getShell(){
		return shell;
	}

	private void btnSalvarLogAction(SelectionEvent evt) {
		String sLog;
		StringList listaLocal;

		if (listaCompara.size() > 0) {
			listaLocal = new StringList();
			sLog = Rotinas.getParams().getDiretorioSistema()
					+ Rotinas.BARRA_INVERTIDA
					+ Rotinas
							.formataDate(Rotinas.FORMATO_DHARQUIVO, new Date())
					+ "_Comparacao.log";

			for (Diretorio diretorio : listaCompara) {
				listaLocal.add(diretorio.getCaminho());
			}

			try {
				listaLocal.SaveToFile(sLog);
			} catch (IOException ex) {
				Logger.getLogger(FrmCompararDiretorio.class.getName()).log(
						Level.SEVERE, null, ex);
			}
			Dialogo.mensagemInfo(shell,
					"FrmCompararDiretorio.LogSalvoMemoDirSistema");
		}
	}

	private void btnCompararDiretoriosAction(SelectionEvent evt) {
		String sCaminhoDir1 = "", sCaminhoDir2 = "";
		boolean bSelecionado;

		bSelecionado = false;
		if (arvoreDiretorio1.getArvore().getSelectionCount() > 0) {
			catalogador.LerArvoreDiretorio(
					arvoreDiretorio1.getArvore().getSelection()[0], "",
					barraStatus2);
			sCaminhoDir1 = barraStatus2.getText();

			if (arvoreDiretorio2.getArvore().getSelectionCount() > 0) {
				catalogador.LerArvoreDiretorio(
						arvoreDiretorio2.getArvore().getSelection()[0], "", barraStatus2);
				sCaminhoDir2 = barraStatus2.getText();
				bSelecionado = true;
			}
		}

		LimparComparacao();

		if (bSelecionado) {
			try {
				Comparar(sCaminhoDir1, sCaminhoDir2);
			} catch (SQLException ex) {
				Logger.getLogger(FrmCompararDiretorio.class.getName()).log(
						Level.SEVERE, null, ex);
			}
		} else {
			Dialogo.mensagemInfo(shell,
					"FrmCompararDiretorio.DiretoriosNaoSelecionados");
		}
	}

	private void cmbAba1Action(SelectionEvent evt) {
		Aba aba;
		
		shell.setCursor(new Cursor(shell.getDisplay(), SWT.CURSOR_WAIT));

		arvoreDiretorio1.getArvore().removeAll();
		aba = AbaBO.getInstancia().pegaAbaPorOrdem(catalogador.listaAbas,
				cmbAba1.getSelectionIndex() + 1);
		catalogador.CarregarArvore(arvoreDiretorio1, aba);
		arvoreDiretorio1.getArvore().select(arvoreDiretorio1.getArvore().getTopItem());
		LimparComparacao();

		shell.setCursor(new Cursor(shell.getDisplay(), SWT.CURSOR_ARROW));
	}

	private void cmbAba2Action(SelectionEvent evt) {
		Aba aba;

		shell.setCursor(new Cursor(shell.getDisplay(), SWT.CURSOR_WAIT));

		arvoreDiretorio2.getArvore().removeAll();
		aba = AbaBO.getInstancia().pegaAbaPorOrdem(catalogador.listaAbas,
				cmbAba2.getSelectionIndex() + 1);
		catalogador.CarregarArvore(arvoreDiretorio2, aba);
		arvoreDiretorio1.getArvore().select(arvoreDiretorio2.getArvore().getTopItem());
		LimparComparacao();

		shell.setCursor(new Cursor(shell.getDisplay(), SWT.CURSOR_ARROW));
	}

	private void WindowOpened() {
		Aba aba1;

		for (Aba aba : catalogador.listaAbas) {
			cmbAba1.add(aba.getNome());
			cmbAba2.add(aba.getNome());
		}
		cmbAba1.select(0);
		cmbAba2.select(0);

		aba1 = AbaBO.getInstancia().pegaAbaPorOrdem(catalogador.listaAbas,
				cmbAba1.getSelectionIndex() + 1);
		catalogador.CarregarArvore(arvoreDiretorio1, aba1);

		aba1 = AbaBO.getInstancia().pegaAbaPorOrdem(catalogador.listaAbas,
				cmbAba2.getSelectionIndex() + 1);
		catalogador.CarregarArvore(arvoreDiretorio2, aba1);
	}

	private void montarArvores() {
		//arvoreDiretorio1 = new Arvore(null);
		//scrollDiretorio1.setViewportView(arvoreDiretorio1);

		//arvoreDiretorio2 = new Arvore(null);
		//scrollDiretorio2.setViewportView(arvoreDiretorio2);
	}

	private void LimparComparacao() {
		pb.setSelection(0);
		tabelaCompara.getTabela().removeAll();
		btnSalvarLog.setEnabled(false);
		barraStatus2.setText("");
	}

	private String SQLCompara(Aba aba1, Aba aba2, String caminho1,
			String caminho2) {
		String sSQL;

		sSQL = DiretorioBO.SQL_CONSULTA_ARQUIVO + " WHERE aba="
				+ aba1.getCodigo() + " AND caminho LIKE "
				+ Rotinas.QuotedStr(caminho1 + "%")
				+ " AND nome NOT IN (SELECT nome FROM Diretorios "
				+ " WHERE aba=" + aba2.getCodigo() + " AND caminho LIKE "
				+ Rotinas.QuotedStr(caminho2 + "%") + ")" + " ORDER BY 1, 2, 3";
		return sSQL;
	}

	private void Comparar(String sCaminhoDir1, String sCaminhoDir2)
			throws SQLException {
		String sSQL;
		Aba aba1, aba2;
		int tamLista;

		aba1 = AbaBO.getInstancia().pegaAbaPorOrdem(catalogador.listaAbas,
				cmbAba1.getSelectionIndex() + 1);
		aba2 = AbaBO.getInstancia().pegaAbaPorOrdem(catalogador.listaAbas,
				cmbAba2.getSelectionIndex() + 1);

		sSQL = SQLCompara(aba1, aba2, sCaminhoDir1, sCaminhoDir2);
		listaCompara = DiretorioBO.getInstancia().carregarDiretorio(sSQL,
				frmCompararDiretorioProgresso);

		if (listaCompara.size() > 0) {
			tabelaCompara.montaTabela(listaCompara,
					catalogador.listaExtensoes, pb, true);
			tabelaCompara.getTabela().setSelection(0);
			tabelaCompara.setSombrearLinhas(true);
			tabelaCompara.setLayoutData(fd_tabelaComparador);

			tamLista = listaCompara.size();
			barraStatus2.setText(String.valueOf(tamLista));
			btnSalvarLog.setEnabled(true);
		} else {
			Dialogo.mensagemInfo(shell,
					"FrmCompararDiretorio.NenhumaDiferencaEncontrada");
		}
	}

	private void mudarLingua() {
		setText(Rotinas.getRecurso("FrmCompararDiretorio.titulo"));
		btnCompararDiretorios.setText(Rotinas
				.getRecurso("FrmCompararDiretorio.btnCompararDiretorios"));
		btnSalvarLog.setText(Rotinas
				.getRecurso("FrmCompararDiretorio.btnSalvarLog"));
		groupDiretorio1.setText(Rotinas
				.getRecurso("FrmCompararDiretorio.panelDiretorio1"));
		groupDiretorio2.setText(Rotinas
				.getRecurso("FrmCompararDiretorio.panelDiretorio2"));
		labDiferencasEncontradas.setText(Rotinas
				.getRecurso("FrmCompararDiretorio.labDiferencasEncontradas"));
		barraStatus1.setText(Rotinas
				.getRecurso("FrmCompararDiretorio.barraStatus1"));
	}

}
