/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 11/12/2014
 * Time: 11:58
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
namespace HFSGuardaDiretorio.gui
{
	partial class FrmCadExtensao
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
			this.components = new System.ComponentModel.Container();
			this.menuStrip1 = new System.Windows.Forms.MenuStrip();
			this.menuExtensao = new System.Windows.Forms.ToolStripMenuItem();
			this.menuIncluirExtensao = new System.Windows.Forms.ToolStripMenuItem();
			this.menuExcluirExtensao = new System.Windows.Forms.ToolStripMenuItem();
			this.menuExcluirTodasExtensoes = new System.Windows.Forms.ToolStripMenuItem();
			this.menuExportarTodos = new System.Windows.Forms.ToolStripMenuItem();
			this.menuExportarBitmap = new System.Windows.Forms.ToolStripMenuItem();
			this.menuExportarIcone = new System.Windows.Forms.ToolStripMenuItem();
			this.menuExportarGIF = new System.Windows.Forms.ToolStripMenuItem();
			this.menuExportarJPEG = new System.Windows.Forms.ToolStripMenuItem();
			this.menuExportarPNG = new System.Windows.Forms.ToolStripMenuItem();
			this.menuExportarTIFF = new System.Windows.Forms.ToolStripMenuItem();
			this.menuImportarTodos = new System.Windows.Forms.ToolStripMenuItem();
			this.menuImportarIconesArquivos = new System.Windows.Forms.ToolStripMenuItem();
			this.menuExtrairIconesArquivos = new System.Windows.Forms.ToolStripMenuItem();
			this.lvExtensao = new System.Windows.Forms.ListView();
			this.columnHeader1 = new System.Windows.Forms.ColumnHeader();
			this.columnHeader2 = new System.Windows.Forms.ColumnHeader();
			this.imgListExtensao = new System.Windows.Forms.ImageList(this.components);
			this.panel1 = new System.Windows.Forms.Panel();
			this.btnExcluir = new System.Windows.Forms.Button();
			this.btnIncluir = new System.Windows.Forms.Button();
			this.odEscolhaArquivo = new System.Windows.Forms.OpenFileDialog();
			this.menuStrip1.SuspendLayout();
			this.panel1.SuspendLayout();
			this.SuspendLayout();
			// 
			// menuStrip1
			// 
			this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
									this.menuExtensao,
									this.menuExportarTodos,
									this.menuImportarTodos});
			this.menuStrip1.Location = new System.Drawing.Point(0, 0);
			this.menuStrip1.Name = "menuStrip1";
			this.menuStrip1.Size = new System.Drawing.Size(280, 24);
			this.menuStrip1.TabIndex = 0;
			this.menuStrip1.Text = "menuStrip1";
			// 
			// menuExtensao
			// 
			this.menuExtensao.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
									this.menuIncluirExtensao,
									this.menuExcluirExtensao,
									this.menuExcluirTodasExtensoes});
			this.menuExtensao.Name = "menuExtensao";
			this.menuExtensao.Size = new System.Drawing.Size(65, 20);
			this.menuExtensao.Text = "&Extensão";
			// 
			// menuIncluirExtensao
			// 
			this.menuIncluirExtensao.Name = "menuIncluirExtensao";
			this.menuIncluirExtensao.Size = new System.Drawing.Size(197, 22);
			this.menuIncluirExtensao.Text = "Incluir Extensão";
			this.menuIncluirExtensao.Click += new System.EventHandler(this.MenuIncluirExtensaoClick);
			// 
			// menuExcluirExtensao
			// 
			this.menuExcluirExtensao.Name = "menuExcluirExtensao";
			this.menuExcluirExtensao.Size = new System.Drawing.Size(197, 22);
			this.menuExcluirExtensao.Text = "Excluir Extensão";
			this.menuExcluirExtensao.Click += new System.EventHandler(this.MenuExcluirExtensaoClick);
			// 
			// menuExcluirTodasExtensoes
			// 
			this.menuExcluirTodasExtensoes.Name = "menuExcluirTodasExtensoes";
			this.menuExcluirTodasExtensoes.Size = new System.Drawing.Size(197, 22);
			this.menuExcluirTodasExtensoes.Text = "Excluir Todas Extensões";
			this.menuExcluirTodasExtensoes.Click += new System.EventHandler(this.MenuExcluirTodasExtensoesClick);
			// 
			// menuExportarTodos
			// 
			this.menuExportarTodos.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
									this.menuExportarBitmap,
									this.menuExportarIcone,
									this.menuExportarGIF,
									this.menuExportarJPEG,
									this.menuExportarPNG,
									this.menuExportarTIFF});
			this.menuExportarTodos.Name = "menuExportarTodos";
			this.menuExportarTodos.Size = new System.Drawing.Size(98, 20);
			this.menuExportarTodos.Text = "Exportar &Todos";
			// 
			// menuExportarBitmap
			// 
			this.menuExportarBitmap.Name = "menuExportarBitmap";
			this.menuExportarBitmap.Size = new System.Drawing.Size(184, 22);
			this.menuExportarBitmap.Text = "Exportar para Bitmap";
			this.menuExportarBitmap.Click += new System.EventHandler(this.MenuExportarBitmapClick);
			// 
			// menuExportarIcone
			// 
			this.menuExportarIcone.Name = "menuExportarIcone";
			this.menuExportarIcone.Size = new System.Drawing.Size(184, 22);
			this.menuExportarIcone.Text = "Exportar para Ícone";
			this.menuExportarIcone.Click += new System.EventHandler(this.MenuExportarIconeClick);
			// 
			// menuExportarGIF
			// 
			this.menuExportarGIF.Name = "menuExportarGIF";
			this.menuExportarGIF.Size = new System.Drawing.Size(184, 22);
			this.menuExportarGIF.Text = "Exportar para GIF";
			this.menuExportarGIF.Click += new System.EventHandler(this.MenuExportarGIFClick);
			// 
			// menuExportarJPEG
			// 
			this.menuExportarJPEG.Name = "menuExportarJPEG";
			this.menuExportarJPEG.Size = new System.Drawing.Size(184, 22);
			this.menuExportarJPEG.Text = "Exportar para JPEG";
			this.menuExportarJPEG.Click += new System.EventHandler(this.MenuExportarJPEGClick);
			// 
			// menuExportarPNG
			// 
			this.menuExportarPNG.Name = "menuExportarPNG";
			this.menuExportarPNG.Size = new System.Drawing.Size(184, 22);
			this.menuExportarPNG.Text = "Exportar para PNG";
			this.menuExportarPNG.Click += new System.EventHandler(this.MenuExportarPNGClick);
			// 
			// menuExportarTIFF
			// 
			this.menuExportarTIFF.Name = "menuExportarTIFF";
			this.menuExportarTIFF.Size = new System.Drawing.Size(184, 22);
			this.menuExportarTIFF.Text = "Exportar para TIFF";
			this.menuExportarTIFF.Click += new System.EventHandler(this.MenuExportarTIFFClick);
			// 
			// menuImportarTodos
			// 
			this.menuImportarTodos.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
									this.menuImportarIconesArquivos,
									this.menuExtrairIconesArquivos});
			this.menuImportarTodos.Name = "menuImportarTodos";
			this.menuImportarTodos.Size = new System.Drawing.Size(101, 20);
			this.menuImportarTodos.Text = "&Importar Todos";
			// 
			// menuImportarIconesArquivos
			// 
			this.menuImportarIconesArquivos.Name = "menuImportarIconesArquivos";
			this.menuImportarIconesArquivos.Size = new System.Drawing.Size(229, 22);
			this.menuImportarIconesArquivos.Text = "Importar Ícones dos Arquivos";
			this.menuImportarIconesArquivos.Click += new System.EventHandler(this.MenuImportarIconesArquivosClick);
			// 
			// menuExtrairIconesArquivos
			// 
			this.menuExtrairIconesArquivos.Name = "menuExtrairIconesArquivos";
			this.menuExtrairIconesArquivos.Size = new System.Drawing.Size(229, 22);
			this.menuExtrairIconesArquivos.Text = "Extrair Ícones dos Arquivos";
			this.menuExtrairIconesArquivos.Click += new System.EventHandler(this.MenuExtrairIconesArquivosClick);
			// 
			// lvExtensao
			// 
			this.lvExtensao.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
									this.columnHeader1,
									this.columnHeader2});
			this.lvExtensao.GridLines = true;
			this.lvExtensao.Location = new System.Drawing.Point(0, 24);
			this.lvExtensao.MultiSelect = false;
			this.lvExtensao.Name = "lvExtensao";
			this.lvExtensao.OwnerDraw = true;
			this.lvExtensao.Size = new System.Drawing.Size(280, 325);
			this.lvExtensao.TabIndex = 2;
			this.lvExtensao.UseCompatibleStateImageBehavior = false;
			this.lvExtensao.View = System.Windows.Forms.View.Details;
			this.lvExtensao.DrawColumnHeader += new System.Windows.Forms.DrawListViewColumnHeaderEventHandler(this.LvExtensaoDrawColumnHeader);
			this.lvExtensao.DrawItem += new System.Windows.Forms.DrawListViewItemEventHandler(this.LvExtensaoDrawItem);
			this.lvExtensao.DrawSubItem += new System.Windows.Forms.DrawListViewSubItemEventHandler(this.LvExtensaoDrawSubItem);
			// 
			// columnHeader1
			// 
			this.columnHeader1.Text = "Extensão";
			this.columnHeader1.Width = 167;
			// 
			// columnHeader2
			// 
			this.columnHeader2.Text = "Ícone";
			this.columnHeader2.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			this.columnHeader2.Width = 58;
			// 
			// imgListExtensao
			// 
			this.imgListExtensao.ColorDepth = System.Windows.Forms.ColorDepth.Depth8Bit;
			this.imgListExtensao.ImageSize = new System.Drawing.Size(16, 16);
			this.imgListExtensao.TransparentColor = System.Drawing.Color.Transparent;
			// 
			// panel1
			// 
			this.panel1.Controls.Add(this.btnExcluir);
			this.panel1.Controls.Add(this.btnIncluir);
			this.panel1.Dock = System.Windows.Forms.DockStyle.Bottom;
			this.panel1.Location = new System.Drawing.Point(0, 347);
			this.panel1.Name = "panel1";
			this.panel1.Size = new System.Drawing.Size(280, 43);
			this.panel1.TabIndex = 3;
			// 
			// btnExcluir
			// 
			this.btnExcluir.Location = new System.Drawing.Point(155, 8);
			this.btnExcluir.Name = "btnExcluir";
			this.btnExcluir.Size = new System.Drawing.Size(75, 23);
			this.btnExcluir.TabIndex = 1;
			this.btnExcluir.Text = "&Excluir";
			this.btnExcluir.UseVisualStyleBackColor = true;
			this.btnExcluir.Click += new System.EventHandler(this.BtnExcluirClick);
			// 
			// btnIncluir
			// 
			this.btnIncluir.Location = new System.Drawing.Point(46, 8);
			this.btnIncluir.Name = "btnIncluir";
			this.btnIncluir.Size = new System.Drawing.Size(75, 23);
			this.btnIncluir.TabIndex = 0;
			this.btnIncluir.Text = "&Incluir";
			this.btnIncluir.UseVisualStyleBackColor = true;
			this.btnIncluir.Click += new System.EventHandler(this.BtnIncluirClick);
			// 
			// odEscolhaArquivo
			// 
			this.odEscolhaArquivo.Filter = "Todos os Arquivos (*.*)|*.*";
			// 
			// FrmCadExtensao
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(280, 390);
			this.Controls.Add(this.lvExtensao);
			this.Controls.Add(this.menuStrip1);
			this.Controls.Add(this.panel1);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.MainMenuStrip = this.menuStrip1;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "FrmCadExtensao";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "Cadastro de Extensão de Arquivo";
			this.menuStrip1.ResumeLayout(false);
			this.menuStrip1.PerformLayout();
			this.panel1.ResumeLayout(false);
			this.ResumeLayout(false);
			this.PerformLayout();
		}
		private System.Windows.Forms.ImageList imgListExtensao;
		private System.Windows.Forms.OpenFileDialog odEscolhaArquivo;
		private System.Windows.Forms.Button btnIncluir;
		private System.Windows.Forms.Button btnExcluir;
		private System.Windows.Forms.Panel panel1;
		private System.Windows.Forms.ColumnHeader columnHeader2;
		private System.Windows.Forms.ColumnHeader columnHeader1;
		private System.Windows.Forms.ListView lvExtensao;
		private System.Windows.Forms.ToolStripMenuItem menuExtrairIconesArquivos;
		private System.Windows.Forms.ToolStripMenuItem menuImportarIconesArquivos;
		private System.Windows.Forms.ToolStripMenuItem menuExportarTIFF;
		private System.Windows.Forms.ToolStripMenuItem menuExportarPNG;
		private System.Windows.Forms.ToolStripMenuItem menuExportarJPEG;
		private System.Windows.Forms.ToolStripMenuItem menuExportarGIF;
		private System.Windows.Forms.ToolStripMenuItem menuExportarIcone;
		private System.Windows.Forms.ToolStripMenuItem menuExportarBitmap;
		private System.Windows.Forms.ToolStripMenuItem menuExcluirTodasExtensoes;
		private System.Windows.Forms.ToolStripMenuItem menuExcluirExtensao;
		private System.Windows.Forms.ToolStripMenuItem menuIncluirExtensao;
		private System.Windows.Forms.ToolStripMenuItem menuImportarTodos;
		private System.Windows.Forms.ToolStripMenuItem menuExportarTodos;
		private System.Windows.Forms.ToolStripMenuItem menuExtensao;
		private System.Windows.Forms.MenuStrip menuStrip1;
	}
}
