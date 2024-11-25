/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 07/07/2015
 * Time: 11:02
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.IO;
using System.Drawing;
using System.Collections.Generic;
using System.Windows.Forms;
using HFSGuardaDiretorio.comum;
using HFSGuardaDiretorio.objetos;
using HFSGuardaDiretorio.objetosbo;
using HFSGuardaDiretorio.objetosdao;
using HFSGuardaDiretorio.gui;
using HFSGuardaDiretorio.objetosgui;

namespace HFSGuardaDiretorio.catalogador
{
	/// <summary>
	/// Description of Catalogador.
	/// </summary>
	public class Catalogador : ICatalogador
	{	
		private static readonly string CONSULTA_DIR_PAI
				= "select aba, cod, ordem, coddirpai, nome, tam, tipo, modificado, "
				+ "atributos, caminho, nomeaba, nomepai, caminhopai "
				+ "from consultadirpai "
				+ "order by 1,2,3,4";
		private static readonly string CONSULTA_DIR_FILHO
				= "select aba, cod, ordem, coddirpai, nome, tam, tipo, modificado, "
				+ "atributos, caminho, nomeaba, nomepai, caminhopai "
				+ "from consultadirfilho "
				+ "order by 1,2,3,4";
		public static readonly string CONSULTA_ARQUIVO
				= "select aba, cod, ordem, coddirpai, nome, tam, tipo, modificado, "
				+ "atributos, caminho, nomeaba, nomepai, caminhopai "
				+ "from consultaarquivo "
				+ "order by tipo desc, ordem";
	
		private static readonly string NO_RAIZ = "Raiz";
		
		private static readonly ArquivoLog log = new ArquivoLog();//Logger.getLogger(Rotinas.HFSGUARDADIR);

		private List<Diretorio> listaDiretorioFilho;
		private List<Diretorio> listaArquivos;

		public DiretorioOrdem diretorioOrdem;

		public List<Aba> listaAbas;
		public List<Diretorio> listaDiretorioPai;
		public List<Extensao> listaExtensoes;

		private TreeNode nodeRaiz;

		private readonly FrmPrincipal form;

		public Catalogador(FrmPrincipal form) {
			this.form = form;

			diretorioOrdem = new DiretorioOrdem();
			
			listaAbas = new List<Aba>();
			listaExtensoes = new List<Extensao>();
			listaDiretorioPai = new List<Diretorio>();
			listaDiretorioFilho = new List<Diretorio>();
			listaArquivos = new List<Diretorio>();
			
			form.spPesquisa.Panel2Collapsed = true;
					
			form.Cursor = Cursors.WaitCursor;        
			FrmSplash frmSplash = new FrmSplash();       
			FrmSplashProgresso frmSplashProgresso = new FrmSplashProgresso(frmSplash);

			frmSplash.Show();
			frmSplash.Update();
			CarregarDados(frmSplashProgresso, true, true);
			CarregarAbas();
			tabPanelMudou();
			
			frmSplash.Close();
			frmSplash.Dispose();
			
			form.Cursor = Cursors.Default;
		}
		
		public static void iniciarSistema() {
			Aba aba;
			string sBanco = Rotinas.ExtractFilePath(Application.ExecutablePath) +
				Path.DirectorySeparatorChar + "GuardaDir.db";
			ConexaoParams cp = new ConexaoParams();
			cp.Nome = sBanco; 
			
			if (!Rotinas.FileExists(sBanco)){
				Rotinas.Conectar(cp);
				
				AbaBO.Instancia.criarTabelaAbas();

				aba = new Aba(1,"DISCO1",0);
				AbaBO.Instancia.incluirAba(aba);

				ExtensaoBO.Instancia.criarTabelaExtensoes();
				DiretorioBO.Instancia.criarTabelaDiretorios();
				VisaoDAO.Instancia.criarVisao("consultadirpai");
				VisaoDAO.Instancia.criarVisao("consultadirfilho");
				VisaoDAO.Instancia.criarVisao("consultaarquivo");
			} else 
				Rotinas.Conectar(cp);

		}

		public void CarregarDados(IProgressoLog pLog, bool bExtensao,
				bool bDiretorio) {
			listaAbas = AbaBO.Instancia.carregarAba(pLog);
			if (bExtensao) {
				listaExtensoes = ExtensaoBO.Instancia.carregarExtensao(pLog);
				ExtensaoBO.Instancia.carregarExtensoes(listaExtensoes, 
                                      form.imageList1, form.imageList2);
			}
			if (bDiretorio) {
				listaDiretorioPai = DiretorioBO.Instancia.carregarDiretorio(
						CONSULTA_DIR_PAI, "consultadirpai", pLog);
				listaDiretorioFilho = DiretorioBO.Instancia.carregarDiretorio(
						CONSULTA_DIR_FILHO, "consultadirfilho", pLog);
				listaArquivos = DiretorioBO.Instancia.carregarDiretorio(
						CONSULTA_ARQUIVO, "consultaarquivo", pLog);
			}
		}

		public void ExcluirDados(Aba aba, string sCaminho) {
			DiretorioBO.Instancia.excluirListaDiretorio(listaDiretorioPai, aba, sCaminho);
			DiretorioBO.Instancia.excluirListaDiretorio(listaDiretorioFilho, aba, sCaminho);
			DiretorioBO.Instancia.excluirListaDiretorio(listaArquivos, aba, sCaminho);
		}

		private void AddItemArvore(TreeView tv, Diretorio diretorio, int Nivel,
				TreeNode node1) {
			List<Diretorio> listaFilhos;
			TreeNode node2;

			if (Nivel == 0) {
				node1 = tv.Nodes.Add(diretorio.Nome);
			}

			listaFilhos = DiretorioBO.Instancia.itensFilhos(listaDiretorioFilho,
					diretorio.Aba.Codigo, diretorio.Ordem,
					diretorio.Codigo);

			foreach (Diretorio filho in listaFilhos) {
				node2 = node1.Nodes.Add(filho.Nome);				
				AddItemArvore(tv, filho, ++Nivel, node2);
			}
		}

		public void IncluirNovaAba() {
			Aba aba;
			string sAba = Dialogo.entrada("Digite o Nome da Nova Aba?");
			if ((sAba != null) && (sAba.Trim().Length > 0)) {
				aba = new Aba();
				aba.Codigo = AbaBO.Instancia.retMaxCodAba(listaAbas);
				aba.Nome = Rotinas.SubString(sAba, 1, 10);
				aba.Ordem = listaAbas.Count + 1;
				AbaBO.Instancia.incluirAba(aba);
				IncluirNovaAba(aba.Nome);
				listaAbas.Add(aba);
			}
		}
		
		public void AlterarNomeAbaAtiva(IProgressoLog pLog) {
			Aba aba = getAbaAtual();
			string sAba = Dialogo.entrada("Digite o Novo Nome da Aba Ativa?", 
					aba.Nome);
			if ((sAba != null) && (sAba.Trim().Length > 0)) {
				aba.Nome = Rotinas.SubString(sAba, 1, 10);
				AbaBO.Instancia.alterarAba(aba);
				form.tabControl1.SelectedTab.Text = sAba;
				CarregarDados(pLog, false, true);
			}        
		}
		
		public void ExcluirAbaAtiva(IProgressoLog pLog) {
			Aba aba;
			int indiceSel = form.tabControl1.SelectedIndex;
			if (indiceSel > 0) {
				bool res = Dialogo.confirma("Tem Certeza, que você deseja excluir esta aba, \n" +
				                            "isto implicará na destruição de todos os seus itens catalogados?");
				if (res) {
					form.Cursor = Cursors.WaitCursor;
					
					aba = getAbaAtual();
					ExcluirDados(aba, "");
					AbaBO.Instancia.excluirAba(aba);                
					form.tabControl1.Controls.RemoveAt(indiceSel);
					
					CarregarDados(pLog, false, false);

					form.barraStatus.Items[1].Text = "";
					
					form.Cursor = Cursors.Default;
				}
			} else
					Dialogo.mensagemErro("A primeira Aba não pode ser excluída!");        
		}
		
		private void IncluirNovaAba(string nomeAba) {
			TabPage tabPage1;
			TreeView arvore;
			SplitContainer sp;
			ListView tabela;
			ColumnHeader columnHeader15;
			ColumnHeader columnHeader14;
			ColumnHeader columnHeader13;
			ColumnHeader columnHeader12;
			ColumnHeader columnHeader11;
			ColumnHeader columnHeader10;
			

			tabPage1 = new TabPage();
			sp = new SplitContainer();
			arvore = new TreeView();
			tabela = new ListView();
			columnHeader10 = new ColumnHeader();
			columnHeader11 = new ColumnHeader();
			columnHeader12 = new ColumnHeader();
			columnHeader13 = new ColumnHeader();
			columnHeader14 = new ColumnHeader();
			columnHeader15 = new ColumnHeader();
			
			// 
			// tabPage1
			// 
			tabPage1.Controls.Add(sp);
			tabPage1.ImageIndex = 0;
			tabPage1.Location = new Point(4, 23);
			tabPage1.Name = "tabPage"+nomeAba;
			tabPage1.Padding = new Padding(3);
			tabPage1.Size = new Size(876, 267);
			tabPage1.TabIndex = 0;
			tabPage1.Text = nomeAba;
			tabPage1.UseVisualStyleBackColor = true;
			// 
			// sp
			// 
			sp.Dock = DockStyle.Fill;
			sp.Location = new Point(3, 3);
			sp.Name = "sp"+nomeAba;
			// 
			// sp.Panel1
			// 
			sp.Panel1.Controls.Add(arvore);
			// 
			// sp.Panel2
			// 
			sp.Panel2.Controls.Add(tabela);
			sp.Size = new Size(870, 261);
			sp.SplitterDistance = 290;
			sp.TabIndex = 0;
			// 
			// arvore
			// 
			arvore.Dock = DockStyle.Fill;
			arvore.ImageIndex = 0;
			arvore.ImageList = form.imageList1;
			arvore.Location = new Point(0, 0);
			arvore.Name = "arvore"+nomeAba;
			arvore.SelectedImageIndex = 1;
			arvore.Size = new Size(290, 261);
			arvore.TabIndex = 0;
			arvore.AfterSelect += new TreeViewEventHandler(form.TvFixaAfterSelect);
			// 
			// tabela
			// 
			tabela.Columns.AddRange(new ColumnHeader[] {
									columnHeader10,
									columnHeader11,
									columnHeader12,
									columnHeader13,
									columnHeader14,
									columnHeader15});
			tabela.Dock = DockStyle.Fill;
			tabela.FullRowSelect = true;
			tabela.GridLines = true;
			tabela.LargeImageList = form.imageList2;
			tabela.Location = new Point(0, 0);
			tabela.MultiSelect = false;
			tabela.Name = "tabela"+nomeAba;
			tabela.Size = new Size(576, 261);
			tabela.SmallImageList = form.imageList1;
			tabela.TabIndex = 1;
			tabela.UseCompatibleStateImageBehavior = false;
			tabela.View = View.Details;
			tabela.ColumnClick += new ColumnClickEventHandler(form.LvFixaColumnClick);
			tabela.DoubleClick += new System.EventHandler(form.LvFixaDoubleClick);
			// 
			// columnHeader10
			// 
			columnHeader10.Text = "Nome";
			columnHeader10.Width = 300;
			// 
			// columnHeader11
			// 
			columnHeader11.Text = "Tamanho";
			columnHeader11.Width = 100;
			// 
			// columnHeader12
			// 
			columnHeader12.Text = "Tipo";
			columnHeader12.Width = 70;
			// 
			// columnHeader13
			// 
			columnHeader13.Text = "Modificado";
			columnHeader13.Width = 120;
			// 
			// columnHeader14
			// 
			columnHeader14.Text = "Atributos";
			columnHeader14.Width = 90;
			// 
			// columnHeader15
			// 
			columnHeader15.Text = "Caminho";
			columnHeader15.Width = 300;
			

			form.tabControl1.Controls.Add(tabPage1);
		}

		public TreeView getArvoreAtual() {
			return getArvoreAtual(form.tabControl1.SelectedIndex);
		}

		public TreeView getArvoreAtual(int nIndicePagina) {
			TabPage tabPage = form.tabControl1.TabPages[nIndicePagina];
			SplitContainer split = (SplitContainer) tabPage.Controls[0];
			TreeView arvore = (TreeView) split.Panel1.Controls[0];
			return arvore;
		}

		public SplitContainer getSplitAtual() {
			TabPage tabPage = form.tabControl1.SelectedTab;
			SplitContainer split = (SplitContainer) tabPage.Controls[0];
			return split;
		}

		public ListView getTabelaAtual() {
			TabPage tabPage = form.tabControl1.SelectedTab;
			SplitContainer split = (SplitContainer) tabPage.Controls[0];
			ListView tabela = (ListView) split.Panel2.Controls[0];
			return tabela;
		}
	
		public void mostrarOcultarArvore(){
			getSplitAtual().Panel1Collapsed = !getSplitAtual().Panel1Collapsed; 
		}
		
		public void CarregarArvore(TreeView tvAba, Aba aba) {
			tvAba.Nodes.Clear();
			
			tvAba.BeginUpdate();
			
			nodeRaiz = new TreeNode(NO_RAIZ);
			foreach (Diretorio diretorio in listaDiretorioPai) {
				if (diretorio.Aba.Codigo == aba.Codigo) {
					AddItemArvore(tvAba, diretorio, 0, nodeRaiz);
				}
			}

			tvAba.EndUpdate();
		}

		public void CarregarAbas() {
			TreeView tvAba;

			form.pb.Minimum = 0;
			form.pb.Maximum = listaAbas.Count - 1;
			form.pb.Value = 0;

			for (int i = 0; i < listaAbas.Count; i++) {
				if (i > 0){
					IncluirNovaAba(listaAbas[i].Nome);
				}
				tvAba = getArvoreAtual(i);
				CarregarArvore(tvAba, listaAbas[i]);
				form.pb.Value = i;
			}
		}

		private Aba getAbaAtual() {
			return AbaBO.Instancia.pegaAbaPorOrdem(
					listaAbas, form.tabControl1.SelectedIndex + 1);
		}

		public void CarregarArquivosLista(bool bLista1, ListView lvArquivos, string sCaminho) {
			string sPaiCaminho;
			List<Diretorio> listaLocal;			
			int nAba;

			listaLocal = new List<Diretorio>();
			lvArquivos.Items.Clear();

			if (bLista1) {
				sPaiCaminho = sCaminho;
				if (!Rotinas.SubString(sCaminho, sCaminho.Length, 1).Equals(Rotinas.BARRA_INVERTIDA)) {
					sCaminho = sCaminho + Rotinas.BARRA_INVERTIDA;
				}
				nAba = getAbaAtual().Codigo;
				foreach (Diretorio diretorio in listaArquivos) {
					if (diretorio.Aba.Codigo == nAba) {
						if (diretorio.CaminhoPai.Equals(sPaiCaminho)) {
							if (Rotinas.StartsStr(sCaminho, diretorio.Caminho)) {
								listaLocal.Add(diretorio);
							}
						}
					}
				}
			} else {
				foreach (Diretorio diretorio in listaArquivos) {
					if (Rotinas.ContainsStr(diretorio.Caminho.ToUpper(), 
							sCaminho.ToUpper())) {
						listaLocal.Add(diretorio);
					}
				}
			}
			Tabela.Instancia.Carregar(bLista1, lvArquivos, listaLocal, listaExtensoes, form.pb.ProgressBar);
			
		}

		public void TamTotalDiretorio(string sCaminho) {
			long conta;
			int nAba;
			decimal soma, tam;

			conta = 0;
			soma = 0;

			foreach (Diretorio diretorio in listaArquivos) {
				nAba = getAbaAtual().Codigo;
				if (diretorio.Aba.Codigo == nAba) {
					if (diretorio.Tipo.Codigo != 'D') {
						if (sCaminho.Trim().Length > 0) {
							if (Rotinas.StartsStr(sCaminho, diretorio.Caminho)) {
								conta++;
								tam = diretorio.Tamanho;
								soma = soma + tam;
							}
						} else {
							conta++;
							tam = diretorio.Tamanho;
							soma = soma + tam;
						}
					}
				}
			}

			
			form.barraStatus.Items[0].Text =
					"Quantidade Total: " + Rotinas.FormatLong("0000", conta)
					+ ", Tamanho Total: " + DiretorioBO.Instancia.MontaTamanho(soma);
		}

		private bool testaSeparadorArquivo(string sDir) {
			sDir = Rotinas.SubString(sDir, sDir.Length, 1);
			if (sDir.Equals(Rotinas.BARRA_INVERTIDA) 
					|| sDir.Equals(Rotinas.BARRA_NORMAL)
					|| sDir.Equals(Rotinas.BARRA_INVERTIDA)) {
				return true;
			} else {
				return false;
			}
		}

		private StringList montaCaminho(string sCaminho, bool bRemover) {
			//sCaminho = NO_RAIZ + Rotinas.BARRA_INVERTIDA + sCaminho;
			StringList sl = new StringList(sCaminho, Rotinas.BARRA_INVERTIDA[0]);
			if (sl[sl.Count - 1].Trim().Length == 0) {
				sl.RemoveAt(sl.Count - 1);
			}
			if (bRemover) {
				sl.RemoveAt(sl.Count - 1);
			}
			return sl;
		}

		public void Pesquisar() {
			TreeView arvoreLocal = getArvoreAtual();
			if (arvoreLocal.VisibleCount > 0) {
				if (form.edtPesquisa.Text.Length >= 2) {
					form.spPesquisa.Panel2Collapsed = false;
					CarregarArquivosLista(false, form.lvPesquisa, 
							form.edtPesquisa.Text);
					form.lvPesquisa.Items[0].Selected = true;               
				} else {
					form.spPesquisa.Panel2Collapsed = true;
					form.lvPesquisa.Clear();
					Dialogo.mensagemInfo("A pesquisa só é feita com pelo menos 2 caracteres!");
				}
			}
		}

		public void PesquisarArvoreDiretorio(string sCaminho, Aba aba) {
			form.tabControl1.SelectedIndex = aba.Ordem-1;
			TreeView arvore = getArvoreAtual();
			StringList sl = montaCaminho(sCaminho, false); // Verifica Diretorio
			TreeNode node = Arvore.Instancia.encontrarCaminhoPorNome(arvore, sl.ToArray());
			
	        if (node == null) {
				sl.Insert(1, sl[1] + Rotinas.BARRA_INVERTIDA);
	            node = Arvore.Instancia.encontrarCaminhoPorNome(arvore, sl.ToArray());
	
	            if (node == null) {
	                sl.Clear();
	                sl = montaCaminho(sCaminho, true); // Verifica Arquivo
	                node = Arvore.Instancia.encontrarCaminhoPorNome(arvore, sl.ToArray());
	
	                if (node == null) {
	                    sl.Insert(1, sl[1] + Rotinas.BARRA_INVERTIDA);
	                    node = Arvore.Instancia.encontrarCaminhoPorNome(arvore, sl.ToArray());
	                }
	            }
	        }
			
			node.Expand();						
			arvore.SelectedNode = node;			
		}

		public void LerArvoreDiretorio(TreeNode node,
				StatusStrip barraStatus) {
			TreeNode NodeAnterior;
			string sSep, sCaminho;
			
			sCaminho = node.Text;			
			NodeAnterior = node.Parent;
			
			while (NodeAnterior != null)
			{
				if (Rotinas.SubString(NodeAnterior.Text, 
					NodeAnterior.Text.Length, 1) == Rotinas.BARRA_INVERTIDA)
				  sSep = "";
				else
				  sSep = Rotinas.BARRA_INVERTIDA;
				
				sCaminho = NodeAnterior.Text + sSep + sCaminho;
				
				NodeAnterior = NodeAnterior.Parent;
			}
			
			form.barraStatus.Items[1].Text = sCaminho;
		}

		public void ListarArquivos(ListView lvTabela, TreeNode node) {
			if (node != null) {
				if (node.IsSelected) {
					LerArvoreDiretorio(node, form.barraStatus);
					CarregarArquivosLista(true, lvTabela, form.barraStatus.Items[1].Text);
					TamTotalDiretorio(form.barraStatus.Items[1].Text);
				}
			}
		}
		
		public void tabPanelMudou(){
			TreeView arvore = getArvoreAtual();
			ListView lvTabela = getTabelaAtual();
			
			arvore.Select();
			if (arvore.Nodes.Count > 0){
				ListarArquivos(lvTabela, arvore.Nodes[0]);
			}
		}
	
		public Aba getAbaSelecionada() {
			return getAbaAtual();
		}

		
		public void DuploCliqueLista(string nome, string tipo) {
			if (tipo.Equals("Diretório")) {
				form.Cursor = Cursors.WaitCursor;
				string sCaminho = form.barraStatus.Items[1].Text;
				if (testaSeparadorArquivo(sCaminho)) {
					sCaminho += nome;
				} else {
					sCaminho += Rotinas.BARRA_INVERTIDA + nome;
				}
				
				PesquisarArvoreDiretorio(sCaminho, getAbaAtual());
				
				form.Cursor = Cursors.Default;
			}
		}

		
		public void EncontrarItemLista(string nomeAba, string nome, string caminho) {
			form.Cursor = Cursors.WaitCursor;
			Aba aba = AbaBO.Instancia.pegaAbaPorNome(listaAbas, nomeAba);        
			PesquisarArvoreDiretorio(caminho, aba);
			
			ListView tabela = getTabelaAtual();
			
			ListViewItem lvi = tabela.FindItemWithText(nome, false, 0, false);
			if (lvi!=null){
				tabela.FocusedItem = lvi;
				tabela.Select();
			}			
			form.Cursor = Cursors.Default;        
		}
	   
		public int verificaNomeDiretorio(string sCaminho, RotuloRaiz sRotuloRaiz) {
			sRotuloRaiz.Rotulo = 
					DiretorioBO.Instancia.removerDrive(sCaminho);
			if (sRotuloRaiz.Rotulo.Length == 0) {

				sRotuloRaiz.Rotulo = Dialogo.entrada("Este diretório não possui um nome.\nDigite o nome do diretório!");

				if ((sRotuloRaiz.Rotulo != null)
						&& (sRotuloRaiz.Rotulo.Trim().Length > 0)) {
					sRotuloRaiz.Rotulo = sRotuloRaiz.Rotulo.Trim();

					if (sRotuloRaiz.Rotulo.Length > 0) {
						return 1;
					} else {
						Dialogo.mensagemInfo("Nenhum nome de diretório informado!");
						return 0;
					}
				} else {
					return 0;
				}
			} else if (Rotinas.Pos(Rotinas.BARRA_INVERTIDA,
					sRotuloRaiz.Rotulo) > 0) {
				sRotuloRaiz.Rotulo = Rotinas.SubString(sRotuloRaiz.Rotulo,
						Rotinas.LastDelimiter(Rotinas.BARRA_INVERTIDA,
								sRotuloRaiz.Rotulo) + 1,
						sRotuloRaiz.Rotulo.Length);
				return 2;
			} else {
				return 3;
			}
		}
		
		public void ExportarArquivo(TipoExportar tipo, IProgressoLog pLog) {
			string sExtensao = "";

			switch (tipo) {
				case TipoExportar.teTXT:
					sExtensao = "txt";
					break;
				case TipoExportar.teCSV:
					sExtensao = "csv";
					break;
				case TipoExportar.teHTML:
					sExtensao = "html";
					break;
				case TipoExportar.teXML:
					sExtensao = "xml";
					break;
				case TipoExportar.teSQL:
					sExtensao = "sql";
					break;
			}

			
			Aba aba = getAbaAtual();
			form.sdExportar.InitialDirectory = Rotinas.ExtractFilePath(Application.ExecutablePath);
			form.sdExportar.FileName = aba.Nome+'.'+sExtensao;
			form.sdExportar.Filter = Rotinas.FILTRO_EXPORTAR;
			DialogResult retval  = form.sdExportar.ShowDialog();
			if (retval == DialogResult.OK) {
				FileInfo arquivo = new FileInfo(form.sdExportar.FileName);
				if (!arquivo.Exists) {
					form.Cursor = Cursors.WaitCursor;
					DiretorioBO.Instancia.exportarDiretorio(tipo, getAbaAtual(),
							arquivo.FullName, pLog);
					form.Cursor = Cursors.Default;

					Dialogo.mensagemErro("Exportação realizada com sucesso!");
				}
			}
		}

		public void ExcluirDiretorioSelecionado(IProgressoLog pLog) 
		{
			TreeView arvore = getArvoreAtual();
			TreeNode path = arvore.SelectedNode;

			if (path.Text.Length > 0) {
				ListView tabela = getTabelaAtual();
				bool res = Dialogo.confirma("Tem Certeza, que você deseja excluir este diretório, isto implicará na destruição de todos os seus items catalogados?");
				if (res) {
					form.Cursor = Cursors.WaitCursor;
					
					DiretorioBO.Instancia.excluirDiretorio(getAbaAtual(), path.Text);
					ExcluirDados(getAbaAtual(), path.Text);

					path.Remove();
					tabela.Clear();

					CarregarDados(pLog, false, false);

					form.Cursor = Cursors.Default;
				}
			}
		}
		
		public void ImportarArquivo(StringList log, IProgressoLog pLog) {
			int nResultado;

			form.odImportar.Filter = "Arquivo XML (*.xml)|*.xml";
			DialogResult retval  = form.odImportar.ShowDialog();
			if (retval == DialogResult.OK) {
				FileInfo arquivo = new FileInfo(form.odImportar.FileName);
				if (arquivo.Exists) {
					form.Cursor = Cursors.WaitCursor;
					nResultado = DiretorioBO.Instancia.importarDiretorioViaXML(
					getAbaAtual(), arquivo.FullName, listaDiretorioPai, pLog);
					if (nResultado == -1) {
						Dialogo.mensagemErro("Importação não realizada!");
					} else if (nResultado == -2) {
						Dialogo.mensagemErro("Este diretório já existe no catálogo!");
					} else {                    
						FinalizaImportacao(pLog);                    
					}
					form.Cursor = Cursors.Default;
				}
			}
		}
		
		public bool ImportarDiretorios(StringList listaCaminho,
				bool bSubDiretorio, FrmImportarDiretorio frmImportarDiretorio) {
			int nAba, nRotuloRaiz, nCodDirRaiz;
			RotuloRaiz sRotuloRaiz = new RotuloRaiz();
			string sCaminhoSemDrive;
			Importar importar = new Importar();

			nAba = getAbaAtual().Codigo;
			nCodDirRaiz = DiretorioBO.Instancia.retMaxCodDir(nAba, 
					listaDiretorioPai);

			foreach (string sCaminho in listaCaminho) {
				nRotuloRaiz = verificaNomeDiretorio(sCaminho, sRotuloRaiz);
				if (nRotuloRaiz > 0) {
					importar = new Importar();
					importar.Aba = nAba;
					importar.CodDirRaiz = nCodDirRaiz;
					importar.RotuloRaiz = sRotuloRaiz.Rotulo;
					if (nRotuloRaiz == 1) {
						importar.NomeDirRaiz = sRotuloRaiz.Rotulo;
					} else if (nRotuloRaiz == 2) {
						sCaminhoSemDrive = DiretorioBO.Instancia.removerDrive(sCaminho);
						importar.NomeDirRaiz = Rotinas.SubString(
								sCaminhoSemDrive, 1,
								Rotinas.LastDelimiter(Rotinas.BARRA_INVERTIDA,
										sCaminhoSemDrive) - 1);
					} else if (nRotuloRaiz == 3) {
						importar.NomeDirRaiz = "";
					}
					importar.Caminho = sCaminho;

					frmImportarDiretorio.listaImportar.Add(importar);
					nCodDirRaiz++;
				}
			}

			frmImportarDiretorio.bSubDiretorio = bSubDiretorio;

			if (bSubDiretorio) {
				frmImportarDiretorio.ShowDialog();
				return true;
			} else {
				if (!DiretorioBO.Instancia.verificaCodDir(
						importar.Aba, importar.RotuloRaiz,
						listaDiretorioPai)) {
					frmImportarDiretorio.ShowDialog();
					return true;
				} else {
					Dialogo.mensagemErro("Este diretório já existe no catálogo!");

					return false;
				}
			}

		}
		
		public void FinalizaImportacao(IProgressoLog pLog) {
			TreeView tvAba;

			form.Cursor = Cursors.WaitCursor;

			CarregarDados(pLog, true, true);
			tvAba = getArvoreAtual();
			CarregarArvore(tvAba, getAbaAtual());
			tabPanelMudou();
			
			form.Cursor = Cursors.Default;
			Dialogo.mensagemInfo("Importação do(s) diretório(s) realizada com sucesso!");

		}
		
	 
		public void ComecaImportacao(bool bSubDiretorios, IProgressoLog pLog) {
			string sCaminho;
			StringList listaCaminho;
			FrmImportarDiretorio frmImportarDiretorio;

			DialogResult retval  = form.escolherDir.ShowDialog();
			if (retval == DialogResult.OK) {
				FileInfo arquivo = new FileInfo(form.escolherDir.SelectedPath);
				if (arquivo.Directory.Exists) {
					form.Cursor = Cursors.WaitCursor;
					sCaminho = arquivo.FullName;

					frmImportarDiretorio = new FrmImportarDiretorio(form);
					listaCaminho = new StringList();

					if (bSubDiretorios) {
						DiretorioBO.Instancia.
								carregarSubDiretorios(sCaminho, listaCaminho);
					} else {
						listaCaminho.Add(sCaminho);
					}

					if (ImportarDiretorios(listaCaminho, bSubDiretorios, 
							frmImportarDiretorio)) {
						FinalizaImportacao(pLog);
					}

					form.Cursor = Cursors.Default;
				}
			}

		}
		
		public void InformacoesDiretorioArquivo()
		{
	        FrmInfoDiretorio frmInfo;
	        ListView tabela = getTabelaAtual();
	        if (tabela.SelectedItems.Count > 0) {
	            frmInfo = new FrmInfoDiretorio();
	            Aba aba = getAbaSelecionada();
	            Diretorio dir = Tabela.Instancia.getLinhaSelecionada(tabela, false);
	            dir.Aba.Nome = aba.Nome;
	            frmInfo.setDiretorio(dir);
	            frmInfo.ShowDialog();
	        }				
		}
		
		public int listaCompara(ListView lvTabela, int coluna, int colOrdem) {
			if (coluna != colOrdem) {
				colOrdem = coluna;
				lvTabela.Sorting = SortOrder.Ascending;
			} else {
		       if (lvTabela.Sorting == SortOrder.Ascending)
		            lvTabela.Sorting = SortOrder.Descending;
		        else
		            lvTabela.Sorting = SortOrder.Ascending;
			}
			
		    lvTabela.Sort();
		    lvTabela.ListViewItemSorter = new TabelaItemComparer(coluna,
		                                                      lvTabela.Sorting);
		    return colOrdem;
		}
	}
}
