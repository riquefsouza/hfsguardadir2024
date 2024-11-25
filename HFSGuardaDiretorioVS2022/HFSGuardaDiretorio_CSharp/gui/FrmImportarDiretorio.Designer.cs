/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 11/12/2014
 * Time: 11:24
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
namespace HFSGuardaDiretorio.gui
{
	partial class FrmImportarDiretorio
	{
		/// <summary>
		/// Designer variable used to keep track of non-visual components.
		/// </summary>
		private System.ComponentModel.IContainer components = null;
		
		/// <summary>
		/// Disposes resources used by the form.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing) {
				if (components != null) {
					components.Dispose();
				}
			}
			base.Dispose(disposing);
		}
		
		/// <summary>
		/// This method is required for Windows Forms designer support.
		/// Do not change the method contents inside the source code editor. The Forms designer might
		/// not be able to load this method if it was changed manually.
		/// </summary>
		private void InitializeComponent()
		{
			this.memoImportaDir = new System.Windows.Forms.TextBox();
			this.barraStatus = new System.Windows.Forms.StatusStrip();
			this.labStatus1 = new System.Windows.Forms.ToolStripStatusLabel();
			this.labStatus2 = new System.Windows.Forms.ToolStripStatusLabel();
			this.pbImportar = new System.Windows.Forms.ProgressBar();
			this.barraStatus.SuspendLayout();
			this.SuspendLayout();
			// 
			// memoImportaDir
			// 
			this.memoImportaDir.Dock = System.Windows.Forms.DockStyle.Top;
			this.memoImportaDir.Location = new System.Drawing.Point(0, 0);
			this.memoImportaDir.Multiline = true;
			this.memoImportaDir.Name = "memoImportaDir";
			this.memoImportaDir.ScrollBars = System.Windows.Forms.ScrollBars.Both;
			this.memoImportaDir.Size = new System.Drawing.Size(889, 505);
			this.memoImportaDir.TabIndex = 0;
			// 
			// barraStatus
			// 
			this.barraStatus.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
									this.labStatus1,
									this.labStatus2});
			this.barraStatus.Location = new System.Drawing.Point(0, 522);
			this.barraStatus.Name = "barraStatus";
			this.barraStatus.Size = new System.Drawing.Size(889, 22);
			this.barraStatus.TabIndex = 9;
			this.barraStatus.Text = "statusStrip1";
			// 
			// labStatus1
			// 
			this.labStatus1.AutoSize = false;
			this.labStatus1.BorderSides = ((System.Windows.Forms.ToolStripStatusLabelBorderSides)((((System.Windows.Forms.ToolStripStatusLabelBorderSides.Left | System.Windows.Forms.ToolStripStatusLabelBorderSides.Top) 
									| System.Windows.Forms.ToolStripStatusLabelBorderSides.Right) 
									| System.Windows.Forms.ToolStripStatusLabelBorderSides.Bottom)));
			this.labStatus1.BorderStyle = System.Windows.Forms.Border3DStyle.SunkenInner;
			this.labStatus1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
			this.labStatus1.Name = "labStatus1";
			this.labStatus1.Size = new System.Drawing.Size(200, 17);
			this.labStatus1.Text = "Total de linhas sendo processadas:";
			this.labStatus1.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// labStatus2
			// 
			this.labStatus2.BorderSides = ((System.Windows.Forms.ToolStripStatusLabelBorderSides)((((System.Windows.Forms.ToolStripStatusLabelBorderSides.Left | System.Windows.Forms.ToolStripStatusLabelBorderSides.Top) 
									| System.Windows.Forms.ToolStripStatusLabelBorderSides.Right) 
									| System.Windows.Forms.ToolStripStatusLabelBorderSides.Bottom)));
			this.labStatus2.BorderStyle = System.Windows.Forms.Border3DStyle.SunkenInner;
			this.labStatus2.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
			this.labStatus2.Name = "labStatus2";
			this.labStatus2.Size = new System.Drawing.Size(643, 17);
			this.labStatus2.Spring = true;
			this.labStatus2.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// pbImportar
			// 
			this.pbImportar.Dock = System.Windows.Forms.DockStyle.Bottom;
			this.pbImportar.Location = new System.Drawing.Point(0, 505);
			this.pbImportar.Name = "pbImportar";
			this.pbImportar.Size = new System.Drawing.Size(889, 17);
			this.pbImportar.Step = 1;
			this.pbImportar.TabIndex = 10;
			// 
			// FrmImportarDiretorio
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(889, 544);
			this.ControlBox = false;
			this.Controls.Add(this.pbImportar);
			this.Controls.Add(this.barraStatus);
			this.Controls.Add(this.memoImportaDir);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "FrmImportarDiretorio";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "Importando Diretório";
			this.Shown += new System.EventHandler(this.FrmImportarDiretorioShown);
			this.barraStatus.ResumeLayout(false);
			this.barraStatus.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();
		}
		public System.Windows.Forms.ToolStripStatusLabel labStatus2;
		private System.Windows.Forms.ToolStripStatusLabel labStatus1;
		public System.Windows.Forms.StatusStrip barraStatus;
		public System.Windows.Forms.ProgressBar pbImportar;
		public System.Windows.Forms.TextBox memoImportaDir;
	}
}
