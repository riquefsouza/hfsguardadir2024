package hfsguardadir.gui;

import hfsguardadir.comum.Rotinas;
import hfsguardadir.objetos.Diretorio;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.layout.FormAttachment;
import org.eclipse.swt.layout.FormData;
import org.eclipse.swt.layout.FormLayout;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Dialog;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Group;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Table;
import org.eclipse.swt.widgets.TableColumn;
import org.eclipse.swt.widgets.TableItem;

public class FrmInfoDiretorio extends Dialog {

	protected Object result;
	protected Shell shell;
	private Table tabelaInfo;
	private Label labArquivoComum;
	private Label labArquivoOculto;
	private Label labArquivoSistema;
	private Label labLegendaDiretorio;
	private Label labVolumeID;
	private Label labArquivoSomenteLeitura;
	private TableItem itemAba;
	private TableItem itemNome;
	private TableItem itemTamanho;
	private TableItem itemTipo;
	private TableItem itemModificado;
	private TableItem itemAtributos;
	private TableItem itemCaminho;

	/**
	 * Create the dialog.
	 * 
	 * @param parent
	 * @param style
	 */
	public FrmInfoDiretorio(Shell parent) {
		super(parent, SWT.DIALOG_TRIM | SWT.APPLICATION_MODAL);
		setText(Rotinas.getRecurso("FrmInfoDiretorio.titulo"));
		createContents();
		mudarLingua();

		tabelaInfo.select(0);
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
		shell = new Shell(getParent(), getStyle());
		shell.setSize(368, 312);
		shell.setText(getText());
		shell.setLayout(new FormLayout());

		Group grpLegendaDosAtributos = new Group(shell, SWT.NONE);
		grpLegendaDosAtributos.setText("Legenda dos Atributos");
		grpLegendaDosAtributos.setLayout(new GridLayout(2, true));
		FormData fd_grpLegendaDosAtributos = new FormData();
		fd_grpLegendaDosAtributos.top = new FormAttachment(0);
		fd_grpLegendaDosAtributos.left = new FormAttachment(0);
		fd_grpLegendaDosAtributos.right = new FormAttachment(100);
		grpLegendaDosAtributos.setLayoutData(fd_grpLegendaDosAtributos);

		labArquivoComum = new Label(grpLegendaDosAtributos, SWT.NONE);
		labArquivoComum.setLayoutData(new GridData(SWT.LEFT, SWT.FILL, false,
				false, 1, 1));
		labArquivoComum.setText(Rotinas
				.getRecurso("FrmInfoDiretorio.labArquivoComum"));

		labArquivoOculto = new Label(grpLegendaDosAtributos, SWT.NONE);
		labArquivoOculto.setText(Rotinas
				.getRecurso("FrmInfoDiretorio.labArquivoOculto"));

		labArquivoSistema = new Label(grpLegendaDosAtributos, SWT.NONE);
		labArquivoSistema.setText(Rotinas
				.getRecurso("FrmInfoDiretorio.labArquivoSistema"));

		labLegendaDiretorio = new Label(grpLegendaDosAtributos, SWT.NONE);
		labLegendaDiretorio.setText(Rotinas
				.getRecurso("FrmInfoDiretorio.labDiretorio"));

		labVolumeID = new Label(grpLegendaDosAtributos, SWT.NONE);
		labVolumeID.setText(Rotinas.getRecurso("FrmInfoDiretorio.labVolumeID"));

		labArquivoSomenteLeitura = new Label(grpLegendaDosAtributos, SWT.NONE);
		labArquivoSomenteLeitura.setText(Rotinas
				.getRecurso("FrmInfoDiretorio.labArquivoSomenteLeitura"));

		tabelaInfo = new Table(shell, SWT.BORDER | SWT.FULL_SELECTION);
		FormData fd_tabelaInfo = new FormData();
		fd_tabelaInfo.top = new FormAttachment(grpLegendaDosAtributos);
		new Label(grpLegendaDosAtributos, SWT.NONE);
		fd_tabelaInfo.height = 250;
		fd_tabelaInfo.right = new FormAttachment(100);
		fd_tabelaInfo.left = new FormAttachment(0);

		tabelaInfo.setLayoutData(fd_tabelaInfo);
		tabelaInfo.setHeaderVisible(true);
		tabelaInfo.setLinesVisible(true);

		Composite composite_1 = new Composite(shell, SWT.NONE);
		FormData fd_composite_1 = new FormData();
		fd_composite_1.top = new FormAttachment(tabelaInfo);

		TableColumn colPropriedade = new TableColumn(tabelaInfo, SWT.BOLD);
		colPropriedade.setWidth(80);
		colPropriedade.setText(Rotinas.getRecurso("FrmInfoDiretorio.item"));

		TableColumn colValor = new TableColumn(tabelaInfo, SWT.NONE);
		colValor.setWidth(200);
		colValor.setText(Rotinas.getRecurso("FrmInfoDiretorio.descricao"));

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

		itemAba = new TableItem(tabelaInfo, SWT.NONE);
		itemAba.setText(0, Rotinas.getRecurso("Tabela.aba"));

		itemNome = new TableItem(tabelaInfo, SWT.NONE);
		itemNome.setText(0, Rotinas.getRecurso("Tabela.nome"));

		itemTamanho = new TableItem(tabelaInfo, SWT.NONE);
		itemTamanho.setText(0, Rotinas.getRecurso("Tabela.tamanho"));

		itemTipo = new TableItem(tabelaInfo, SWT.NONE);
		itemTipo.setText(0, Rotinas.getRecurso("Tabela.tipo"));

		itemModificado = new TableItem(tabelaInfo, SWT.NONE);
		itemModificado.setText(0, Rotinas.getRecurso("Tabela.modificado"));

		itemAtributos = new TableItem(tabelaInfo, SWT.NONE);
		itemAtributos.setText(0, Rotinas.getRecurso("Tabela.atributos"));

		itemCaminho = new TableItem(tabelaInfo, SWT.NONE);
		itemCaminho.setText(0, Rotinas.getRecurso("Tabela.caminho"));
	}
	
	public Shell getShell(){
		return shell;
	}

	public void setDiretorio(Diretorio diretorio) {
		if (diretorio != null) {
			itemAba.setText(1, diretorio.getAba().getNome());
			itemNome.setText(1, diretorio.getNome());
			itemTamanho.setText(1, diretorio.getTamanhoFormatado());
			itemTipo.setText(1, diretorio.getTipo().getNome());
			itemModificado.setText(1, diretorio.getModificadoFormatado());
			itemAtributos.setText(1, diretorio.getAtributos());
			itemCaminho.setText(1, diretorio.getCaminho());

			tabelaInfo.getColumn(1).setWidth(
					diretorio.getCaminho().length() * 7);
		}
	}

	private void mudarLingua() {
		setText(Rotinas.getRecurso("FrmInfoDiretorio.titulo"));
		labArquivoComum.setText(Rotinas
				.getRecurso("FrmInfoDiretorio.labArquivoComum"));
		labArquivoOculto.setText(Rotinas
				.getRecurso("FrmInfoDiretorio.labArquivoOculto"));
		labArquivoSistema.setText(Rotinas
				.getRecurso("FrmInfoDiretorio.labArquivoSistema"));
		labLegendaDiretorio.setText(Rotinas
				.getRecurso("FrmInfoDiretorio.labDiretorio"));
		labVolumeID.setText(Rotinas.getRecurso("FrmInfoDiretorio.labVolumeID"));
		labArquivoSomenteLeitura.setText(Rotinas
				.getRecurso("FrmInfoDiretorio.labArquivoSomenteLeitura"));

		tabelaInfo.getColumn(0).setText(
				Rotinas.getRecurso("FrmInfoDiretorio.item"));
		tabelaInfo.getColumn(1).setText(
				Rotinas.getRecurso("FrmInfoDiretorio.descricao"));

		itemAba.setText(0, Rotinas.getRecurso("Tabela.aba"));
		itemNome.setText(0, Rotinas.getRecurso("Tabela.nome"));
		itemTamanho.setText(0, Rotinas.getRecurso("Tabela.tamanho"));
		itemTipo.setText(0, Rotinas.getRecurso("Tabela.tipo"));
		itemModificado.setText(0, Rotinas.getRecurso("Tabela.modificado"));
		itemAtributos.setText(0, Rotinas.getRecurso("Tabela.atributos"));
		itemCaminho.setText(0, Rotinas.getRecurso("Tabela.caminho"));
	}

}
