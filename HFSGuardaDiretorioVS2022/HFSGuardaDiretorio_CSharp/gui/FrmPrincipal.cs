/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 10/12/2014
 * Time: 17:39
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using HFSGuardaDiretorio.catalogador;
using HFSGuardaDiretorio.comum;
using HFSGuardaDiretorio.objetosgui;

namespace HFSGuardaDiretorio.gui
{
	/// <summary>
	/// Description of MainForm.
	/// </summary>
	public partial class FrmPrincipal : Form
	{
		private FrmPrincipalProgresso frmPrincipalProgresso;
    	private readonly Catalogador catalogador;
    	private int colOrdem;
    	
		public FrmPrincipal()
		{
			colOrdem = -1;
			//
			// The InitializeComponent() call is required for Windows Forms designer support.
			//
			InitializeComponent();
			
			frmPrincipalProgresso = new FrmPrincipalProgresso(this);
	        catalogador = new Catalogador(this);			
		}
		
		public Catalogador Catalogador {
			get { return catalogador; }
		}
	
		void MenuIncluirNovaAbaClick(object sender, EventArgs e)
		{
			catalogador.IncluirNovaAba();			
		}
		
		void MenuAlterarNomeAbaAtivaClick(object sender, EventArgs e)
		{
			catalogador.AlterarNomeAbaAtiva(frmPrincipalProgresso);			
		}
		
		void MenuExcluirAbaAtivaClick(object sender, EventArgs e)
		{
			catalogador.ExcluirAbaAtiva(frmPrincipalProgresso);			
		}
		
		void MenuImportarDiretorioClick(object sender, EventArgs e)
		{
			catalogador.ComecaImportacao(false, frmPrincipalProgresso);			
		}
		
		void MenuImportarSubDiretoriosClick(object sender, EventArgs e)
		{
			catalogador.ComecaImportacao(true, frmPrincipalProgresso);			
		}
		
		void MenuCadastrarExtensaoArquivoClick(object sender, EventArgs e)
		{
			FrmCadExtensao frmCadExtensao = new FrmCadExtensao(this);
			frmCadExtensao.ShowDialog();
		}		

		void MenuCompararDiretoriosClick(object sender, EventArgs e)
		{
			FrmCompararDiretorio frmCompararDiretorio = new FrmCompararDiretorio(this);
			frmCompararDiretorio.ShowDialog();
		}
		
		void MenuSobreCatalogadorClick(object sender, EventArgs e)
		{
			FrmSobre frmSobre = new FrmSobre();
			frmSobre.ShowDialog();
		}
				
		void MenuExpandirDiretoriosClick(object sender, EventArgs e)
		{
			catalogador.getArvoreAtual().ExpandAll();
		}
		
		void MenuColapsarDiretoriosClick(object sender, EventArgs e)
		{
			catalogador.getArvoreAtual().CollapseAll();
		}
		
		void MenuTXTClick(object sender, EventArgs e)
		{
			catalogador.ExportarArquivo(TipoExportar.teTXT, frmPrincipalProgresso);
		}
		
		void MenuCSVClick(object sender, EventArgs e)
		{
			catalogador.ExportarArquivo(TipoExportar.teCSV, frmPrincipalProgresso);
		}
		
		void MenuHTMLClick(object sender, EventArgs e)
		{
			catalogador.ExportarArquivo(TipoExportar.teHTML, frmPrincipalProgresso);
		}
		
		void MenuXMLClick(object sender, EventArgs e)
		{
			catalogador.ExportarArquivo(TipoExportar.teXML, frmPrincipalProgresso);
		}
		
		void MenuSQLClick(object sender, EventArgs e)
		{
			catalogador.ExportarArquivo(TipoExportar.teSQL, frmPrincipalProgresso);			
		}
		
		void MenuImportarDiretoriosViaXMLClick(object sender, EventArgs e)
		{
	        StringList log = new StringList();
            catalogador.ImportarArquivo(log, frmPrincipalProgresso);
		}
		
		void MenuMostrarOcultArvoreDirAbaAtivaClick(object sender, EventArgs e)
		{
	        catalogador.mostrarOcultarArvore();
		}
		
		void MenuMostrarOcultarListaItensPesquisadosClick(object sender, EventArgs e)
		{
			spPesquisa.Panel2Collapsed = !spPesquisa.Panel2Collapsed;
		}
		
		void BtnImportarDiretorioClick(object sender, EventArgs e)
		{
			MenuImportarDiretorioClick(sender, e);
		}
		
		void BtnPesquisarClick(object sender, EventArgs e)
		{
			catalogador.Pesquisar();
		}
		
		void FrmPrincipalFormClosed(object sender, FormClosedEventArgs e)
		{
			Rotinas.Desconectar();
		}
				
		void MenuInformacoesDiretorioArquivoClick(object sender, EventArgs e)
		{
			catalogador.InformacoesDiretorioArquivo();
		}
		
		void MenuExcluirDiretorioSelecionadoClick(object sender, EventArgs e)
		{
			catalogador.ExcluirDiretorioSelecionado(frmPrincipalProgresso);
		}

		void MenuIconesClick(object sender, EventArgs e)
		{
			catalogador.getTabelaAtual().View = View.LargeIcon;
		}
		
		void MenuListaClick(object sender, EventArgs e)
		{
			catalogador.getTabelaAtual().View = View.List;
		}
		
		void MenuDetalhesClick(object sender, EventArgs e)
		{
			catalogador.getTabelaAtual().View = View.Details;
		}
		
		void MenuIconesPequenosClick(object sender, EventArgs e)
		{
			catalogador.getTabelaAtual().View = View.SmallIcon;
		}
		
		void MenuExpandirDiretorios2Click(object sender, EventArgs e)
		{
			MenuExpandirDiretoriosClick(sender, e);
		}
		
		void MenuColapsarDiretorios2Click(object sender, EventArgs e)
		{
			MenuColapsarDiretoriosClick(sender, e);
		}
		
		void MenuIncluirNovaAba2Click(object sender, EventArgs e)
		{
			MenuIncluirNovaAbaClick(sender, e);
		}
		
		void MenuAlterarNomeAbaAtiva2Click(object sender, EventArgs e)
		{
			MenuAlterarNomeAbaAtivaClick(sender, e);
		}
		
		void MenuExcluirAbaAtiva2Click(object sender, EventArgs e)
		{
			MenuExcluirAbaAtivaClick(sender, e);
		}
		
		void TabControl1SelectedIndexChanged(object sender, EventArgs e)
		{
			catalogador.tabPanelMudou();
		}
		
		public void LvFixaDoubleClick(object sender, EventArgs e)
		{
			ListView lvTabela = (ListView) sender;
			
			if (lvTabela.SelectedItems.Count > 0){
				string nome = lvTabela.SelectedItems[0].Text;
				string tipo = lvTabela.SelectedItems[0].SubItems[2].Text;
					
				catalogador.DuploCliqueLista(nome, tipo);
			}
		}
		
		public void LvFixaColumnClick(object sender, ColumnClickEventArgs e)
		{
			ListView lvTabela = (ListView) sender;
			colOrdem = catalogador.listaCompara(lvTabela, e.Column, colOrdem);
		}
				
		void LvPesquisaColumnClick(object sender, ColumnClickEventArgs e)
		{
			ListView lvTabela = (ListView) sender;
			colOrdem = catalogador.listaCompara(lvTabela, e.Column, colOrdem);			
		}
		
		void LvPesquisaClick(object sender, EventArgs e)
		{
			ListView lvPesquisa = (ListView) sender;
			
			if (lvPesquisa.SelectedItems.Count > 0){
				string nome = lvPesquisa.SelectedItems[0].Text;
				string caminho = lvPesquisa.SelectedItems[0].SubItems[5].Text;
				string nomeAba = lvPesquisa.SelectedItems[0].SubItems[6].Text;
					
				catalogador.EncontrarItemLista(nomeAba, nome, caminho);
			}			
		}
						
		public void TvFixaAfterSelect(object sender, TreeViewEventArgs e)
		{
			ListView lvTabela = catalogador.getTabelaAtual();
			catalogador.ListarArquivos(lvTabela, e.Node);			
		}
						
	}
}
