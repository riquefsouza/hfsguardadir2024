/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 11/12/2014
 * Time: 11:58
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.IO;
using System.Drawing;
using System.Windows.Forms;
using HFSGuardaDiretorio.catalogador;
using HFSGuardaDiretorio.objetos;
using HFSGuardaDiretorio.objetosgui;
using HFSGuardaDiretorio.objetosbo;
using HFSGuardaDiretorio.comum;

namespace HFSGuardaDiretorio.gui
{
	/// <summary>
	/// Description of FrmCadExtensao.
	/// </summary>
	public partial class FrmCadExtensao : Form
	{
		private readonly Catalogador catalogador;
		    
		public FrmCadExtensao(FrmPrincipal frmPrincipal)
		{
			//
			// The InitializeComponent() call is required for Windows Forms designer support.
			//
			InitializeComponent();
			
			odEscolhaArquivo.Filter = Rotinas.FILTRO_IMAGEM;
			
			catalogador = frmPrincipal.Catalogador;
	        CarregarExtensoesNaGrid();
		}
		
		private void CarregarExtensoesNaGrid() {
			ListViewItem item;
			
			lvExtensao.Items.Clear();
			imgListExtensao.Images.Clear();
			
			foreach (Extensao extensao in catalogador.listaExtensoes) {
				item = lvExtensao.Items.Add(extensao.Nome);
				item.SubItems.Add("icone");
				imgListExtensao.Images.Add(Rotinas.byteArrayToBitmap(extensao.Bmp16));
			}
		}
				
		void LvExtensaoDrawColumnHeader(object sender, DrawListViewColumnHeaderEventArgs e)
		{
			e.DrawDefault = true;
		}
		
		void LvExtensaoDrawItem(object sender, DrawListViewItemEventArgs e)
		{	
			e.DrawBackground();

			if ((e.State & ListViewItemStates.Selected) == ListViewItemStates.Selected) {
			    e.Graphics.FillRectangle(SystemBrushes.Highlight, e.Bounds);
			    e.Item.ForeColor = SystemColors.HighlightText;
			} else {
				e.Item.ForeColor = SystemColors.WindowText;
			}
			
		  	e.DrawText();  
		}
		
		void LvExtensaoDrawSubItem(object sender, DrawListViewSubItemEventArgs e)
		{						
			if (e.ColumnIndex > 0) {
			    e.DrawBackground();
			    
				if ((e.ItemState & ListViewItemStates.Selected) == ListViewItemStates.Selected) {
				    e.Graphics.FillRectangle(SystemBrushes.Highlight, e.Bounds);
				    e.SubItem.ForeColor = SystemColors.HighlightText;
				} else {
					e.SubItem.ForeColor = SystemColors.WindowText;
				}		    
			    
				Rectangle rect = new Rectangle(e.SubItem.Bounds.Left + 20, e.SubItem.Bounds.Top, 
			                                e.SubItem.Bounds.Width, e.SubItem.Bounds.Height);
				e.Graphics.DrawImageUnscaled(imgListExtensao.Images[e.ItemIndex], rect);
			}
		}
		
		
		void MenuIncluirExtensaoClick(object sender, EventArgs e)
		{
			StringList log;
			DialogResult retval  = odEscolhaArquivo.ShowDialog();
			if (retval == DialogResult.OK) {
				FileInfo arquivo = new FileInfo(odEscolhaArquivo.FileName);
				if (arquivo.Exists) {
					log = new StringList();
					
                    if (ExtensaoBO.Instancia.SalvarExtensao(
                            catalogador.listaExtensoes, arquivo.Name,
                            arquivo.FullName, log)) {

                        CarregarExtensoesNaGrid();

                        Dialogo.mensagemInfo("Extensão salva com sucesso!");
                    } else {
                        Dialogo.mensagemInfo("Extensão já existe cadastrada!");
                    }					
				}
			}
			
		}
		
		void MenuExcluirExtensaoClick(object sender, EventArgs e)
		{
	        Extensao extensao;
	        
	        if (catalogador.listaExtensoes.Count > 0) {
				bool res = Dialogo.confirma("Tem Certeza, que você deseja excluir esta extensão?");
				if (res) {
	                extensao = ExtensaoBO.Instancia.pegaExtensaoPorOrdem(
	                        catalogador.listaExtensoes, lvExtensao.SelectedIndices[0]+1);
	
	                    if (ExtensaoBO.Instancia.excluirExtensao(
	                            catalogador.listaExtensoes, extensao.Codigo)) {
	                        CarregarExtensoesNaGrid();
	                        Dialogo.mensagemInfo("Extensão excluída com sucesso!");
	                    }
	            }
	        }

		}
		
		void MenuExcluirTodasExtensoesClick(object sender, EventArgs e)
		{
			bool res = Dialogo.confirma("Tem Certeza, que você deseja excluir todas as extensões?");
            if (res) {
                if (ExtensaoBO.Instancia.excluirTodasExtensoes(
                        catalogador.listaExtensoes)) {
                    CarregarExtensoesNaGrid();
                    Dialogo.mensagemInfo("Extensões excluídas com sucesso!");
                }
			}
		}
		
		void MenuExportarBitmapClick(object sender, EventArgs e)
		{
			ExtensaoBO.Instancia.ExportarExtensao(
				TipoExportarExtensao.teBMP, catalogador.listaExtensoes);
		}
		
		void MenuExportarIconeClick(object sender, EventArgs e)
		{
			ExtensaoBO.Instancia.ExportarExtensao(
				TipoExportarExtensao.teICO, catalogador.listaExtensoes);			
		}
		
		void MenuExportarGIFClick(object sender, EventArgs e)
		{
			ExtensaoBO.Instancia.ExportarExtensao(
				TipoExportarExtensao.teGIF, catalogador.listaExtensoes);			
		}
		
		void MenuExportarJPEGClick(object sender, EventArgs e)
		{
			ExtensaoBO.Instancia.ExportarExtensao(
				TipoExportarExtensao.teJPG, catalogador.listaExtensoes);			
		}
		
		void MenuExportarPNGClick(object sender, EventArgs e)
		{
			ExtensaoBO.Instancia.ExportarExtensao(
				TipoExportarExtensao.tePNG, catalogador.listaExtensoes);			
		}
		
		void MenuExportarTIFFClick(object sender, EventArgs e)
		{
			ExtensaoBO.Instancia.ExportarExtensao(
				TipoExportarExtensao.teTIF, catalogador.listaExtensoes);			
		}
		
		void MenuImportarIconesArquivosClick(object sender, EventArgs e)
		{
			DialogResult retval  = odEscolhaArquivo.ShowDialog();
			if (retval == DialogResult.OK) {
				FileInfo arquivo = new FileInfo(odEscolhaArquivo.FileName);
				if (arquivo.Exists) {
                    ExtensaoBO.Instancia.ImportarExtensao(arquivo.FullName,
                            catalogador.listaExtensoes);
                    CarregarExtensoesNaGrid();					
				}
			}
		}
		
		void MenuExtrairIconesArquivosClick(object sender, EventArgs e)
		{
			DialogResult retval  = odEscolhaArquivo.ShowDialog();
			if (retval == DialogResult.OK) {
				FileInfo arquivo = new FileInfo(odEscolhaArquivo.FileName);
				if (arquivo.Exists) {
                    ExtensaoBO.Instancia.ExtrairExtensao(arquivo.FullName,
                            catalogador.listaExtensoes);
                    CarregarExtensoesNaGrid();					
				}
			}			
		}
		
		void BtnIncluirClick(object sender, EventArgs e)
		{
			MenuIncluirExtensaoClick(sender, e);
		}
		
		void BtnExcluirClick(object sender, EventArgs e)
		{
			MenuExcluirExtensaoClick(sender, e);
		}
	}
}
