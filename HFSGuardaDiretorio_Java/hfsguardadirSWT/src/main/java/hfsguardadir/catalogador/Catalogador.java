package hfsguardadir.catalogador;

import hfsguardadir.comum.ICatalogador;
import hfsguardadir.comum.IProgressoLog;
import hfsguardadir.comum.Rotinas;
import hfsguardadir.comum.StringList;
import hfsguardadir.comum.TipoExportar;
import hfsguardadir.gui.FrmImportarDiretorio;
import hfsguardadir.gui.FrmPrincipal;
import hfsguardadir.objetos.Aba;
import hfsguardadir.objetos.Diretorio;
import hfsguardadir.objetos.DiretorioOrdem;
import hfsguardadir.objetos.Extensao;
import hfsguardadir.objetos.Importar;
import hfsguardadir.objetos.Parametro;
import hfsguardadir.objetosbo.AbaBO;
import hfsguardadir.objetosbo.DiretorioBO;
import hfsguardadir.objetosbo.ExtensaoBO;
import hfsguardadir.objetosdao.VisaoDAO;
import hfsguardadir.objetosgui.Arvore;
import hfsguardadir.objetosgui.Dialogo;
import hfsguardadir.objetosgui.EscolhaArquivo;
import hfsguardadir.objetosgui.Tabela;

import java.io.File;
import java.io.IOException;
import java.math.BigDecimal;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;

import javax.xml.parsers.ParserConfigurationException;

import org.eclipse.swt.SWT;
import org.eclipse.swt.custom.SashForm;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.events.SelectionListener;
import org.eclipse.swt.graphics.Cursor;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.TabItem;
import org.eclipse.swt.widgets.TreeItem;
import org.xml.sax.SAXException;

public class Catalogador implements ICatalogador {

    private static final String CONSULTA_DIR_PAI
            = "select aba, cod, ordem, coddirpai, nome, tam, tipo, modificado, "
            + "atributos, caminho, nomeaba, nomepai, caminhopai "
            + "from consultadirpai "
            + "order by 1,2,3,4";
    private static final String CONSULTA_DIR_FILHO
            = "select aba, cod, ordem, coddirpai, nome, tam, tipo, modificado, "
            + "atributos, caminho, nomeaba, nomepai, caminhopai "
            + "from consultadirfilho "
            + "order by 1,2,3,4";
    public static final String CONSULTA_ARQUIVO
            = "select aba, cod, ordem, coddirpai, nome, tam, tipo, modificado, "
            + "atributos, caminho, nomeaba, nomepai, caminhopai "
            + "from consultaarquivo "
            + "order by tipo desc, ordem";

    private final boolean bSombrearLinhas;

    //private static final Logger log = Logger.getLogger(Rotinas.HFSGUARDADIR);

    private ArrayList<Diretorio> listaDiretorioFilho;
    private ArrayList<Diretorio> listaArquivos;

    public DiretorioOrdem diretorioOrdem;

    public ArrayList<Aba> listaAbas;
    public ArrayList<Diretorio> listaDiretorioPai;
    public ArrayList<Extensao> listaExtensoes;

    private FrmPrincipal form;

    public Catalogador(FrmPrincipal form) {        
    	this.form = form;
    	this.bSombrearLinhas = true;
        //this.bSombrearColunas = false;

        diretorioOrdem = new DiretorioOrdem();
        
        listaAbas = new ArrayList<>();
        listaExtensoes = new ArrayList<>();
        listaDiretorioPai = new ArrayList<>();
        listaDiretorioFilho = new ArrayList<>();
        listaArquivos = new ArrayList<>();
    }
    
    public FrmPrincipal getForm(){
    	return form;
    }
    
    public void carregarDados(IProgressoLog pLog){
        try {            
            CarregarDados(pLog, true, true);            
            CarregarAbas();
            tabPanelMudou();                       
        } catch (SQLException ex) {
            Logger.getLogger(Catalogador.class.getName()).log(Level.SEVERE, null, ex);
        }        
    }
    
    public static void iniciarSistema(Parametro param) throws SAXException,
            IOException, ParserConfigurationException, SQLException,
            ClassNotFoundException {
        Aba aba;
        
        if (!Rotinas.carregarParametros(param.getArquivoConfiguracao())) {       
            Dialogo.mensagemErro(null, "HFSGuardaDir.ValidaArquivoConf");
        }
        
        Rotinas.registrarProvedorTIFF();        
        
        String sBanco = param.getDiretorioSistema() + 
                Rotinas.BARRA_INVERTIDA + "GuardaDir.db";
        
        if (!Rotinas.FileExists(sBanco)){
        	Rotinas.Conectar();
        	
            AbaBO.getInstancia().criarTabelaAbas();

            aba = new Aba(1,"DISCO1",0);
            AbaBO.getInstancia().incluirAba(aba);

            ExtensaoBO.getInstancia().criarTabelaExtensoes();
            DiretorioBO.getInstancia().criarTabelaDiretorios();
            VisaoDAO.getInstancia().criarVisao("consultadirpai");
            VisaoDAO.getInstancia().criarVisao("consultadirfilho");
            VisaoDAO.getInstancia().criarVisao("consultaarquivo");
        } else 
        	Rotinas.Conectar();

        Dialogo.mudarLingua();
        EscolhaArquivo.mudarLingua();
    }

    public void mudarLingua(String lingua) {
        Parametro params = Rotinas.getParams();
        params.setLocalidadeLingua(lingua);
        params.setLocalidadePais("");
        form.mudarLingua();

        Dialogo.mudarLingua();
        EscolhaArquivo.mudarLingua();
    }
    
    public void CarregarDados(IProgressoLog pLog, boolean bExtensao,
            boolean bDiretorio) throws SQLException {
        listaAbas = AbaBO.getInstancia().carregarAba(pLog);
        if (bExtensao) {
            listaExtensoes = ExtensaoBO.getInstancia().carregarExtensao(pLog);
        }
        if (bDiretorio) {
            listaDiretorioPai = DiretorioBO.getInstancia().carregarDiretorio(
                    CONSULTA_DIR_PAI, pLog);
            listaDiretorioFilho = DiretorioBO.getInstancia().carregarDiretorio(
                    CONSULTA_DIR_FILHO, pLog);
            listaArquivos = DiretorioBO.getInstancia().carregarDiretorio(
                    CONSULTA_ARQUIVO, pLog);
        }
    }

    public void ExcluirDados(Aba aba, String sCaminho) {
        DiretorioBO.getInstancia().excluirListaDiretorio(listaDiretorioPai, aba, sCaminho);
        DiretorioBO.getInstancia().excluirListaDiretorio(listaDiretorioFilho, aba, sCaminho);
        DiretorioBO.getInstancia().excluirListaDiretorio(listaArquivos, aba, sCaminho);
    }

    private void AddItemArvore(Diretorio diretorio, int Nivel, TreeItem node1) {
        ArrayList<Diretorio> listaFilhos;
        TreeItem node2;

        listaFilhos = DiretorioBO.getInstancia().itensFilhos(listaDiretorioFilho,
                diretorio.getAba().getCodigo(), diretorio.getOrdem(),
                diretorio.getCodigo());

        for (Diretorio filho : listaFilhos) {
            node2 = new TreeItem(node1, SWT.NONE);
            node2.setText(filho.getNome());
   			node2.setImage(Rotinas.getImagem(form.getShell(), "diretorio.gif"));    		
            AddItemArvore(filho, ++Nivel, node2);
        }
    }

    public void IncluirNovaAba() throws SQLException {
        Aba aba;
        String sAba = Dialogo.entrada(form.getShell(), "FrmPrincipal.DigitaIncluirNovaAba");
        if ((sAba != null) && (sAba.trim().length() > 0)) {
            aba = new Aba();
            aba.setCodigo(AbaBO.getInstancia().retMaxCodAba(listaAbas));
            aba.setNome(Rotinas.SubString(sAba, 1, 10));
            aba.setOrdem(listaAbas.size() + 1);
            AbaBO.getInstancia().incluirAba(aba);
            IncluirNovaAba(aba.getNome());
            listaAbas.add(aba);
        }
    }
    
    public void AlterarNomeAbaAtiva(IProgressoLog pLog) throws SQLException {
        Aba aba = getAbaAtual();
        String sAba = Dialogo.entrada(form.getShell(), "FrmPrincipal.DigitaAlterarNomeAba", 
                aba.getNome());
        if ((sAba != null) && (sAba.trim().length() > 0)) {
            aba.setNome(Rotinas.SubString(sAba, 1, 10));
            AbaBO.getInstancia().alterarAba(aba);            
            TabItem tabItem = form.tabFolder.getItem(form.tabFolder.getSelectionIndex());
            tabItem.setText(sAba);
            CarregarDados(pLog, false, true);
        }        
    }
    
    public void ExcluirAbaAtiva(IProgressoLog pLog) throws SQLException{
    	TabItem tab;
        Aba aba;
        int indiceSel = form.tabFolder.getSelectionIndex();
        if (indiceSel > 0) {
            int res = Dialogo.confirma(form.getShell(), "FrmPrincipal.ConfirmaExcluirAba");
            if (res == SWT.YES) {
            	form.getShell().setCursor(new Cursor(form.getShell().getDisplay(), SWT.CURSOR_WAIT));
                
                aba = getAbaAtual();
                ExcluirDados(aba, "");
                AbaBO.getInstancia().excluirAba(aba);                
                tab = form.tabFolder.getSelection()[0];
                tab.dispose();
                
                CarregarDados(pLog, false, false);

                form.barraStatus2.setText("");
                
                form.getShell().setCursor(new Cursor(form.getShell().getDisplay(), SWT.CURSOR_ARROW));
            }
        } else
                Dialogo.mensagemErro(form.getShell(), "FrmPrincipal.ValidaExcluirAba");        
    }
    
    private void IncluirNovaAba(String nomeAba) {
		TabItem tab = new TabItem(form.tabFolder, SWT.NONE);
		tab.setText(nomeAba);
		tab.setImage(Rotinas.getImagem(form.getShell(), "cdouro.gif"));
		
		final SashForm sashFormAba1 = new SashForm(form.tabFolder, SWT.NONE);
		tab.setControl(sashFormAba1);
		
		Arvore arvore = new Arvore(sashFormAba1);
        arvore.setCatalogador(this);
		arvore.getArvore().addSelectionListener(new SelectionListener() {			
			@Override
			public void widgetSelected(SelectionEvent evt) {
				arvoreValorMudou(evt);
			}			
			@Override
			public void widgetDefaultSelected(SelectionEvent evt) {
				arvoreValorMudou(evt);
			}
		});
		
		Tabela tabela = new Tabela(sashFormAba1, true);
		tabela.setCatalogador(this);
        tabela.setSombrearLinhas(bSombrearLinhas);
		
		sashFormAba1.setWeights(new int[] {1, 3});
    }

    public Arvore getArvoreAtual() {
        return getArvoreAtual(form.tabFolder.getSelectionIndex());
    }

    public Arvore getArvoreAtual(int nIndicePagina) {
   		TabItem tab = form.tabFolder.getItem(nIndicePagina);
   		SashForm sashFormAba = (SashForm) tab.getControl();
   		Arvore arvore = (Arvore) sashFormAba.getChildren()[0];
        return arvore;
    }
    
    public Tabela getTabelaAtual() {
    	TabItem tab = form.tabFolder.getItem(form.tabFolder.getSelectionIndex());
    	SashForm sashFormAba = (SashForm) tab.getControl();
    	Tabela tabela = (Tabela) sashFormAba.getChildren()[1];
        return tabela;
    }
    
    public void mostrarOcultarArvore(){
    	TabItem tab = form.tabFolder.getItem(form.tabFolder.getSelectionIndex());
    	SashForm sashFormAba = (SashForm) tab.getControl();
    	
    	if (sashFormAba.getWeights()[0]==250){
    		sashFormAba.setWeights(new int[] {0, 1});
    	} else {
   	    	sashFormAba.setWeights(new int[] {1, 3});
    	}    	
    }
    
    public void CarregarArvore(Arvore tvAba, Aba aba) {
    	TreeItem node1;
    	
    	tvAba.limpar();
    	
    	for (Diretorio diretorio : listaDiretorioPai) {
            if (diretorio.getAba().getCodigo() == aba.getCodigo()) {
            	
        		node1 = new TreeItem(tvAba.getArvore(), SWT.NONE);
        		node1.setText(diretorio.getNome());
       			node1.setImage(Rotinas.getImagem(form.getShell(), "diretorio.gif"));
            	
                AddItemArvore(diretorio, 0, node1);
            }
        }
    }

    public void CarregarAbas() {
        Arvore tvAba;

        form.pb.setMinimum(0);
        form.pb.setMaximum(listaAbas.size() - 1);
        form.pb.setSelection(0);

        for (int i = 0; i < listaAbas.size(); i++) {
        	if (i == 0) {
        		form.tabFolder.getItem(0).setText(listaAbas.get(i).getNome());
        	} else {
        		IncluirNovaAba(listaAbas.get(i).getNome());        		
        	}   
        	tvAba = getArvoreAtual(i);
            CarregarArvore(tvAba, listaAbas.get(i));
            form.pb.setSelection(i);
        }
    }

    private Aba getAbaAtual() {
        return AbaBO.getInstancia().pegaAbaPorOrdem(
                listaAbas, form.tabFolder.getSelectionIndex() + 1);
    }

    public void CarregarArquivosLista(Tabela tabela, boolean bLista1, String sCaminho) {
        String sPaiCaminho;
        ArrayList<Diretorio> listaLocal;
        int nAba;

        listaLocal = new ArrayList<>();

        if (bLista1) {
            sPaiCaminho = sCaminho;
            if (!Rotinas.SubString(sCaminho, sCaminho.length(), 1).equals(Rotinas.BARRA_INVERTIDA)) {
                sCaminho = sCaminho + Rotinas.BARRA_INVERTIDA;
            }
            nAba = getAbaAtual().getCodigo();
            for (Diretorio diretorio : listaArquivos) {
                if (diretorio.getAba().getCodigo() == nAba) {
                    if (diretorio.getCaminhoPai().equals(sPaiCaminho)) {
                        if (Rotinas.StartsStr(sCaminho, diretorio.getCaminho())) {
                            listaLocal.add(diretorio);
                        }
                    }
                }
            }
        } else {
            for (Diretorio diretorio : listaArquivos) {
                if (Rotinas.ContainsStr(diretorio.getCaminho().toUpperCase(), 
                        sCaminho.toUpperCase())) {
                    listaLocal.add(diretorio);
                }
            }
        }
        tabela.montaTabela(listaLocal, listaExtensoes, form.pb, bLista1);
                
        listaLocal.clear();
    }

    public void TamTotalDiretorio(String sCaminho) {
        long conta;
        int nAba;
        BigDecimal soma, tam;

        conta = 0;
        soma = new BigDecimal(0);

        for (Diretorio diretorio : listaArquivos) {
            nAba = getAbaAtual().getCodigo();
            if (diretorio.getAba().getCodigo() == nAba) {
                if (diretorio.getTipo().getCodigo() != 'D') {
                    if (sCaminho.trim().length() > 0) {
                        if (Rotinas.StartsStr(sCaminho, diretorio.getCaminho())) {
                            conta++;
                            tam = new BigDecimal(diretorio.getTamanho());
                            soma = soma.add(tam);
                        }
                    } else {
                        conta++;
                        tam = new BigDecimal(diretorio.getTamanho());
                        soma = soma.add(tam);
                    }
                }
            }
        }

        form.barraStatus1.setText(
                "Quantidade Total: " + Rotinas.FormatLong("0000", conta)
                + ", Tamanho Total: " + DiretorioBO.getInstancia().MontaTamanhoBig(soma));
    }

    private boolean testaSeparadorArquivo(String sDir) {
        sDir = Rotinas.SubString(sDir, sDir.length(), 1);
        if (sDir.equals(Rotinas.BARRA_INVERTIDA) 
                || sDir.equals(Rotinas.BARRA_NORMAL)) {
            return true;
        } else {
            return false;
        }
    }

    private StringList montaCaminho(String sCaminho, boolean bRemover) {
    	sCaminho = sCaminho + Rotinas.BARRA_INVERTIDA;
        StringList sl = new StringList(sCaminho, Rotinas.BARRA_INVERTIDA.charAt(0));
        if (sl.get(sl.size() - 1).trim().length() == 0) {
            sl.remove(sl.size() - 1);
        }
        if (bRemover) {
            sl.remove(sl.size() - 1);
        }
        return sl;
    }

    public void Pesquisar() {    	
        Arvore arvoreLocal = getArvoreAtual();
        if (arvoreLocal.getArvore().getItemCount() > 0) {
            if (form.edtPesquisa.getText().length() >= 2) {
            	form.sashFormPesquisa.setWeights(new int[] {2, 1});

                CarregarArquivosLista(form.tabelaPesquisa, false, form.edtPesquisa.getText());
                form.tabelaPesquisa.getTabela().select(0);
                form.tabelaPesquisa.setSombrearLinhas(true);                
            } else {
            	form.sashFormPesquisa.setWeights(new int[] {1, 0});
                form.tabelaPesquisa.getTabela().removeAll();
                Dialogo.mensagemInfo(form.getShell(), "FrmPrincipal.TamMaxPesquisa");
            }
        }
    }

    public void PesquisarArvoreDiretorio(String sCaminho, Aba aba) {
        form.tabFolder.setSelection(aba.getOrdem()-1);
        Arvore arvore = getArvoreAtual();
        StringList sl = montaCaminho(sCaminho, false); // Verifica Diretorio
        TreeItem item = arvore.encontrarCaminhoPorNome(sl.toStringArray());        
        if (item == null) {
        	sl.remove(sl.size() - 2);
            //sl.set(1, sl.get(1) + Rotinas.BARRA_INVERTIDA);
            item = arvore.encontrarCaminhoPorNome(sl.toStringArray());

            if (item == null) {
                sl.clear();
                sl = montaCaminho(sCaminho, true); // Verifica Arquivo
                item = arvore.encontrarCaminhoPorNome(sl.toStringArray());
                /*
                if (item == null) {
                    sl.set(1, sl.get(1) + Rotinas.BARRA_INVERTIDA);
                    item = arvore.encontrarCaminhoPorNome(sl.toStringArray());
                }
                */
            }
        }
        item.setExpanded(true);
        arvore.getArvore().select(item);
        LerArvoreDiretorio(item, "", form.barraStatus2);
    }

    public void LerArvoreDiretorio(TreeItem item, String caminho, Label barraStatus) {
        if (item!=null) {
        	caminho = item.getText() + Rotinas.BARRA_INVERTIDA + caminho;
        	barraStatus.setText(caminho.substring(0, caminho.length()-1));
        	if (item.getParentItem()!=null) {
        		LerArvoreDiretorio(item.getParentItem(), caminho, barraStatus);
        	} 
        }
    }

    public void ListarArquivos(Tabela tabela) {
        CarregarArquivosLista(tabela, true, form.barraStatus2.getText());
        TamTotalDiretorio(form.barraStatus2.getText());
    }
    
    public void tabPanelMudou(){
        Arvore arvore = getArvoreAtual();
        Tabela tabela = getTabelaAtual();
        TamTotalDiretorio("");
        if (arvore.getArvore().getItemCount() > 0){
        	arvore.getArvore().setSelection(arvore.getArvore().getTopItem());
            LerArvoreDiretorio(arvore.getArvore().getTopItem(), "", form.barraStatus2);            
            ListarArquivos(tabela);
        }
    }

    public void arvoreValorMudou(SelectionEvent evt) {
    	Tabela tabela = getTabelaAtual();
    	TreeItem item = (TreeItem) evt.item;    	
        LerArvoreDiretorio(item, "", form.barraStatus2);
        ListarArquivos(tabela);
    }

    @Override
    public Aba getAbaSelecionada() {
        return getAbaAtual();
    }

    @Override
    public void DuploCliqueLista(String nome, String tipo) {
        if (tipo.equals(Rotinas.getRecurso("TipoLista.diretorio"))) {
            form.getShell().setCursor(new Cursor(form.getShell().getDisplay(), SWT.CURSOR_WAIT));
            String sCaminho = form.barraStatus2.getText();
            if (testaSeparadorArquivo(sCaminho)) {
                sCaminho += nome;
            } else {
                sCaminho += Rotinas.BARRA_INVERTIDA + nome;
            }
            
            PesquisarArvoreDiretorio(sCaminho, getAbaAtual());
            Tabela tabela = getTabelaAtual();
            ListarArquivos(tabela);
            
            form.getShell().setCursor(new Cursor(form.getShell().getDisplay(), SWT.CURSOR_ARROW));
        }
    }

    @Override
    public void EncontrarItemLista(String nomeAba, String nome, String caminho) {
    	form.getShell().setCursor(new Cursor(form.getShell().getDisplay(), SWT.CURSOR_WAIT));
        Aba aba = AbaBO.getInstancia().pegaAbaPorNome(listaAbas, nomeAba);        
        PesquisarArvoreDiretorio(caminho, aba);

        Tabela tabela = getTabelaAtual();
        ListarArquivos(tabela);
        int nlinha = tabela.encontrarLinha(nome);
        tabela.getTabela().setSelection(nlinha);
        form.getShell().setCursor(new Cursor(form.getShell().getDisplay(), SWT.CURSOR_ARROW));        
    }
   
    public int verificaNomeDiretorio(String sCaminho, RotuloRaiz sRotuloRaiz) {
        sRotuloRaiz.setRotulo(
                DiretorioBO.getInstancia().removerDrive(sCaminho));
        if (sRotuloRaiz.getRotulo().length() == 0) {

            sRotuloRaiz.setRotulo(Dialogo.entrada(form.getShell(),
                    "FrmPrincipal.DigitaNomeDiretorio"));

            if ((sRotuloRaiz.getRotulo() != null)
                    && (sRotuloRaiz.getRotulo().trim().length() > 0)) {
                sRotuloRaiz.setRotulo(sRotuloRaiz.getRotulo().trim());

                if (sRotuloRaiz.getRotulo().length() > 0) {
                    return 1;
                } else {
                    Dialogo.mensagemInfo(form.getShell(), 
                            "FrmPrincipal.ValidaNomeDiretorio");
                    return 0;
                }
            } else {
                return 0;
            }
        } else if (Rotinas.Pos(Rotinas.BARRA_INVERTIDA,
                sRotuloRaiz.getRotulo()) > 0) {
            sRotuloRaiz.setRotulo(Rotinas.SubString(sRotuloRaiz.getRotulo(),
                    Rotinas.LastDelimiter(Rotinas.BARRA_INVERTIDA,
                            sRotuloRaiz.getRotulo()) + 1,
                    sRotuloRaiz.getRotulo().length()));
            return 2;
        } else {
            return 3;
        }
    }
    
    public void ExportarArquivo(TipoExportar tipo, IProgressoLog pLog) 
            throws SQLException, IOException {
        String sExtensao = "";

        switch (tipo) {
            case teTXT:
                sExtensao = "txt";
                break;
            case teCSV:
                sExtensao = "csv";
                break;
            case teHTML:
                sExtensao = "html";
                break;
            case teXML:
                sExtensao = "xml";
                break;
            case teSQL:
                sExtensao = "sql";
                break;
        }

        EscolhaArquivo escolha = new EscolhaArquivo(form.getShell(), EscolhaArquivo.SAVE_DIALOG);
        Aba aba = getAbaAtual();
        String sArq = Rotinas.getParams().getDiretorioSistema()+
                Rotinas.BARRA_INVERTIDA+
                aba.getNome()+'.'+sExtensao;
        String retval = escolha.mostrar(new File(sArq));
        if (retval.trim().length() > 0) {
            File arquivo = new File(retval);
            if (arquivo != null) {
            	form.getShell().setCursor(new Cursor(form.getShell().getDisplay(), SWT.CURSOR_WAIT));
                DiretorioBO.getInstancia().exportarDiretorio(tipo, getAbaAtual(),
                        arquivo.getPath(), pLog);
                form.getShell().setCursor(new Cursor(form.getShell().getDisplay(), SWT.CURSOR_ARROW));

                Dialogo.mensagemErro(form.getShell(), "FrmPrincipal.SucessoExportar");
            }
        //} else if (retval == EscolhaArquivo.ERROR_OPTION) {
          //  Dialogo.mensagemErro(form.getShell(), "FrmPrincipal.ErroSalvarArquivo");
        }
    }
    
    public void ExcluirDiretorioSelecionado(IProgressoLog pLog) 
            throws SQLException {
        Arvore arvore = getArvoreAtual();        
        TreeItem item = arvore.getArvore().getSelection()[0];

        if (arvore.getArvore().getSelectionCount() > 0 && item.getText().length() > 0) {
            Tabela tabela = getTabelaAtual();
            int res = Dialogo.confirma(form.getShell(), "FrmPrincipal.ExcluirDiretorioSelecionado");
            if (res == SWT.YES) {
            	form.getShell().setCursor(new Cursor(form.getShell().getDisplay(), SWT.CURSOR_WAIT));
                //StringList sl = montaCaminho(item);

                DiretorioBO.getInstancia().excluirDiretorio(getAbaAtual(), form.barraStatus2.getText());
                ExcluirDados(getAbaAtual(), form.barraStatus2.getText());

                //StringList sl2 = montaCaminho(item);
                //arvore.excluirNode(sl2.toStringArray());
                item.removeAll();
                item.dispose();
                tabela.getTabela().removeAll();

                CarregarDados(pLog, false, false);

                form.getShell().setCursor(new Cursor(form.getShell().getDisplay(), SWT.CURSOR_ARROW));
            }
        }
    }
    
    public void ImportarArquivo(StringList log, IProgressoLog pLog) 
            throws IOException, SQLException {
        int nResultado;

        EscolhaArquivo escolha = new EscolhaArquivo(form.getShell(), 
                EscolhaArquivo.OPEN_DIALOG);
        String retval = escolha.mostrar();
        if (retval.trim().length() > 0) {
            File arquivo = new File(retval);
            if (arquivo != null) {
            	form.getShell().setCursor(new Cursor(form.getShell().getDisplay(), SWT.CURSOR_WAIT));
                nResultado = DiretorioBO.getInstancia().importarDiretorioViaXML(
                getAbaAtual(), arquivo.getPath(), listaDiretorioPai, pLog);
                if (nResultado == -1) {
                    Dialogo.mensagemErro(form.getShell(), 
                            "FrmPrincipal.ImportacaoNaoRealizada");
                } else if (nResultado == -2) {
                    Dialogo.mensagemErro(form.getShell(), 
                            "FrmPrincipal.DiretorioExisteCatalogo");
                } else {                    
                    FinalizaImportacao(pLog);                    
                }
                form.getShell().setCursor(new Cursor(form.getShell().getDisplay(), SWT.CURSOR_ARROW));
            }
        }
    }
    
    public boolean ImportarDiretorios(StringList listaCaminho,
            boolean bSubDiretorio, FrmImportarDiretorio frmImportarDiretorio) {
        int nAba, nRotuloRaiz, nCodDirRaiz;
        RotuloRaiz sRotuloRaiz = new RotuloRaiz();
        String sCaminhoSemDrive;
        Importar importar = new Importar();

        nAba = getAbaAtual().getCodigo();
        nCodDirRaiz = DiretorioBO.getInstancia().retMaxCodDir(nAba, 
                listaDiretorioPai);

        for (String sCaminho : listaCaminho) {
            nRotuloRaiz = verificaNomeDiretorio(sCaminho, sRotuloRaiz);
            if (nRotuloRaiz > 0) {
                importar = new Importar();
                importar.setAba(nAba);
                importar.setCodDirRaiz(nCodDirRaiz);
                importar.setRotuloRaiz(sRotuloRaiz.getRotulo());
                if (nRotuloRaiz == 1) {
                    importar.setNomeDirRaiz(sRotuloRaiz.getRotulo());
                } else if (nRotuloRaiz == 2) {
                    sCaminhoSemDrive = DiretorioBO.getInstancia().removerDrive(sCaminho);
                    importar.setNomeDirRaiz(Rotinas.SubString(
                            sCaminhoSemDrive, 1,
                            Rotinas.LastDelimiter(Rotinas.BARRA_INVERTIDA,
                                    sCaminhoSemDrive) - 1));
                } else if (nRotuloRaiz == 3) {
                    importar.setNomeDirRaiz("");
                }
                importar.setCaminho(sCaminho);

                frmImportarDiretorio.listaImportar.add(importar);
                nCodDirRaiz++;
            }
        }

        frmImportarDiretorio.bSubDiretorio = bSubDiretorio;

        if (bSubDiretorio) {
            frmImportarDiretorio.open();
            return true;
        } else {
            if (!DiretorioBO.getInstancia().verificaCodDir(
                    importar.getAba(), importar.getRotuloRaiz(),
                    listaDiretorioPai)) {
                frmImportarDiretorio.open();
                return true;
            } else {
                Dialogo.mensagemErro(form.getShell(),
                        "FrmPrincipal.DiretorioExisteCatalogo");

                return false;
            }
        }

    }
    
    public void FinalizaImportacao(IProgressoLog pLog) throws SQLException {
        Arvore tvAba;

        form.getShell().setCursor(new Cursor(form.getShell().getDisplay(), SWT.CURSOR_WAIT));

        CarregarDados(pLog, true, true);
        tvAba = getArvoreAtual();
        CarregarArvore(tvAba, getAbaAtual());

        form.getShell().setCursor(new Cursor(form.getShell().getDisplay(), SWT.CURSOR_ARROW));
        Dialogo.mensagemInfo(form.getShell(), "FrmPrincipal.DirImportacaoSucesso");

    }
    
 
    public void ComecaImportacao(boolean bSubDiretorios, IProgressoLog pLog) 
            throws SQLException {
        String sCaminho;
        StringList listaCaminho;
        FrmImportarDiretorio frmImportarDiretorio;

        EscolhaArquivo escolha = new EscolhaArquivo(form.getShell(),
                EscolhaArquivo.CUSTOM_DIALOG);
        String retval = escolha.mostrar();
        if (retval.trim().length() > 0) {
            File arquivo = new File(retval);

            if (arquivo != null) {
            	form.getShell().setCursor(new Cursor(form.getShell().getDisplay(), SWT.CURSOR_WAIT));
                sCaminho = arquivo.getPath();

                frmImportarDiretorio = new FrmImportarDiretorio(form.getShell(), this, form);
                listaCaminho = new StringList();

                if (bSubDiretorios) {
                    DiretorioBO.getInstancia().
                            carregarSubDiretorios(sCaminho, listaCaminho);
                } else {
                    listaCaminho.add(sCaminho);
                }

                if (ImportarDiretorios(listaCaminho, bSubDiretorios, 
                        frmImportarDiretorio)) {
                    FinalizaImportacao(pLog);
                }

                form.getShell().setCursor(new Cursor(form.getShell().getDisplay(), SWT.CURSOR_ARROW));
            }
        } 
        //else if (retval == EscolhaArquivo.ERROR_OPTION) {
            //Dialogo.mensagemErro(form.getShell(), "FrmPrincipal.ErroAbrirDir");
        //}

    }
    
}
