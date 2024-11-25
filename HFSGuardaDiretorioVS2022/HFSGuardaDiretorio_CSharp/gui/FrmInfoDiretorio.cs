/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 11/12/2014
 * Time: 11:11
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.Drawing;
using System.Windows.Forms;
using HFSGuardaDiretorio.objetos;

namespace HFSGuardaDiretorio.gui
{
	/// <summary>
	/// Description of FrmInfoDiretorio.
	/// </summary>
	public partial class FrmInfoDiretorio : Form
	{
		private Font fonte;
		
		public FrmInfoDiretorio()
		{
			//
			// The InitializeComponent() call is required for Windows Forms designer support.
			//
			InitializeComponent();
			
			fonte = new Font(lvInfo.Items[0].Font, FontStyle.Bold);
		}
		
		void BtnOkClick(object sender, EventArgs e)
		{
			this.Close();
		}
		
	    public void setDiretorio(Diretorio diretorio) {
	        if (diretorio!=null) {
				lvInfo.Items[0].SubItems.Add(diretorio.Aba.Nome);
				lvInfo.Items[1].SubItems.Add(diretorio.Nome);				
				lvInfo.Items[2].SubItems.Add(diretorio.TamanhoFormatado);
				lvInfo.Items[3].SubItems.Add(diretorio.Tipo.Nome);
				lvInfo.Items[4].SubItems.Add(diretorio.ModificadoFormatado);
				lvInfo.Items[5].SubItems.Add(diretorio.Atributos);
				lvInfo.Items[6].SubItems.Add(diretorio.Caminho);
				
				lvInfo.Columns[1].Width = diretorio.Caminho.Length * 8;				
	        }
	    }
		
		
		void LvInfoDrawColumnHeader(object sender, DrawListViewColumnHeaderEventArgs e)
		{
			e.DrawDefault = true;
		}
		
		void LvInfoDrawItem(object sender, DrawListViewItemEventArgs e)
		{
			e.DrawBackground();

			if ((e.State & ListViewItemStates.Selected) == ListViewItemStates.Selected) {
			    e.Graphics.FillRectangle(SystemBrushes.Highlight, e.Bounds);
			    e.Item.ForeColor = SystemColors.HighlightText;
			} else {
				e.Item.ForeColor = SystemColors.WindowText;
			}
			
			e.Item.Font = fonte;
			
			e.DrawText();
		}
		
		void LvInfoDrawSubItem(object sender, DrawListViewSubItemEventArgs e)
		{
			e.DrawBackground();

			if ((e.ItemState & ListViewItemStates.Selected) == ListViewItemStates.Selected) {
			    e.Graphics.FillRectangle(SystemBrushes.Highlight, e.Bounds);
			    e.SubItem.ForeColor = SystemColors.HighlightText;
			} else {
				e.SubItem.ForeColor = SystemColors.WindowText;
			}
			
		  	e.DrawText();			
		}
	}
}
