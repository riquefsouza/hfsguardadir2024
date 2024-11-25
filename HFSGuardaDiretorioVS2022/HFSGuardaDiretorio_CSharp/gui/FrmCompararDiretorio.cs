/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 11/12/2014
 * Time: 11:44
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.IO;
using System.Drawing;
using System.Windows.Forms;
using System.Collections.Generic;
using HFSGuardaDiretorio.catalogador;
using HFSGuardaDiretorio.comum;
using HFSGuardaDiretorio.objetos;
using HFSGuardaDiretorio.objetosbo;
using HFSGuardaDiretorio.objetosgui;

namespace HFSGuardaDiretorio.gui
{
	/// <summary>
	/// Description of FrmCompararDiretorio.
	/// </summary>
	public partial class FrmCompararDiretorio : Form
	{
	    private FrmCompararDiretorioProgresso frmCompararDiretorioProgresso;
	    private readonly Catalogador catalogador;    
	    
	    public List<Diretorio> listaCompara;		
		
		public FrmCompararDiretorio(FrmPrincipal frmPrincipal)
		{
			//
			// The InitializeComponent() call is required for Windows Forms designer support.
			//
			InitializeComponent();

			listaCompara = new List<Diretorio>();
	        frmCompararDiretorioProgresso = new FrmCompararDiretorioProgresso(this);
			catalogador = frmPrincipal.Catalogador;
	        CarregarDados();	        
			LimparComparacao();
		}
		
		void BtnSalvarLogClick(object sender, EventArgs e)
		{
			string sLog;
			StringList listaLocal;

			if (listaCompara.Count > 0) {
				listaLocal = new StringList();
				sLog = Rotinas.ExtractFilePath(Application.ExecutablePath)+
						Path.DirectorySeparatorChar +
						Rotinas.formataDate(Rotinas.FORMATO_DHARQUIVO, DateTime.Now) +
						"_Comparacao.log";

				foreach (Diretorio diretorio in listaCompara) {
					listaLocal.Add(diretorio.Caminho);
				}

				listaLocal.SaveToFile(sLog);

				Dialogo.mensagemInfo("Log salvo no mesmo diretório do sistema!");
			}

		}
		
		void BtnCompararDiretoriosClick(object sender, EventArgs e)
		{
			string sCaminhoDir1 = "", sCaminhoDir2 = "";
			bool bSelecionado;

			bSelecionado = false;
			if (tvDiretorio1.SelectedNode.IsSelected) {
				catalogador.LerArvoreDiretorio(tvDiretorio1.SelectedNode,
						barraStatus);
				sCaminhoDir1 = labStatus2.Text;

				if (tvDiretorio2.SelectedNode.IsSelected) {
					catalogador.LerArvoreDiretorio(
							tvDiretorio2.SelectedNode, barraStatus);
					sCaminhoDir2 = labStatus2.Text;
					bSelecionado = true;
				}
			}

			LimparComparacao();

			if (bSelecionado) {
				Comparar(sCaminhoDir1, sCaminhoDir2);
			} else {
				Dialogo.mensagemInfo("Diretórios não selecionados!");
			}			
		}
		
		void CmbAba1SelectedIndexChanged(object sender, EventArgs e)
		{
			Aba aba;
			
			Cursor = Cursors.WaitCursor;
			
			tvDiretorio1.Nodes.Clear();
			aba = AbaBO.Instancia.pegaAbaPorOrdem(catalogador.listaAbas, 
						cmbAba1.SelectedIndex + 1);
			catalogador.CarregarArvore(tvDiretorio1, aba);
			tvDiretorio1.Select();
			LimparComparacao();
			
			Cursor = Cursors.Default;
		}
		
		void CmbAba2SelectedIndexChanged(object sender, EventArgs e)
		{
			Aba aba;
			
			Cursor = Cursors.WaitCursor;
			
			tvDiretorio2.Nodes.Clear();
			aba = AbaBO.Instancia.pegaAbaPorOrdem(catalogador.listaAbas, 
						cmbAba2.SelectedIndex + 1);
			catalogador.CarregarArvore(tvDiretorio2, aba);
			tvDiretorio2.Select();
			LimparComparacao();
			
			Cursor = Cursors.Default;
		}
		
		private void CarregarDados(){
	        foreach (Aba aba in catalogador.listaAbas) {
				cmbAba1.Items.Add(aba.Nome);
				cmbAba2.Items.Add(aba.Nome);
			}
	        cmbAba1.SelectedIndex = 0;
	        cmbAba2.SelectedIndex = 0;	
		}
		
		private void LimparComparacao() {
			pb.Value = 0;
			lvCompara.Items.Clear();
			btnSalvarLog.Enabled = false;
			labStatus2.Text = "";
		}

		private string SQLCompara(Aba aba1, Aba aba2, string caminho1,
				string caminho2) {
			string sSQL;

			sSQL = DiretorioBO.SQL_CONSULTA_ARQUIVO + " WHERE aba=" + aba1.Codigo
					+ " AND caminho LIKE " + Rotinas.QuotedStr(caminho1 + "%")
					+ " AND nome NOT IN (SELECT nome FROM Diretorios "
					+ " WHERE aba=" + aba2.Codigo + " AND caminho LIKE "
					+ Rotinas.QuotedStr(caminho2 + "%") + ")" + " ORDER BY 1, 2, 3";
			return sSQL;
		}

		private void Comparar(string sCaminhoDir1, string sCaminhoDir2) {
			string sSQL;
			Aba aba1, aba2;
			int tamLista;

			aba1 = AbaBO.Instancia.pegaAbaPorOrdem(catalogador.listaAbas,
					cmbAba1.SelectedIndex + 1);
			aba2 = AbaBO.Instancia.pegaAbaPorOrdem(catalogador.listaAbas,
					cmbAba2.SelectedIndex + 1);

			sSQL = SQLCompara(aba1, aba2, sCaminhoDir1, sCaminhoDir2);
			listaCompara = DiretorioBO.Instancia.carregarDiretorio(sSQL, 
					"consultaarquivo", frmCompararDiretorioProgresso);

			if (listaCompara.Count > 0) {
				Tabela.Instancia.Carregar(true, lvCompara, listaCompara, catalogador.listaExtensoes, pb);

				tamLista = listaCompara.Count;
				labStatus2.Text = tamLista.ToString();
				btnSalvarLog.Enabled = true;
			} else {
				Dialogo.mensagemInfo("Nenhuma diferença encontrada!");
			}
		}
				
	}
}
