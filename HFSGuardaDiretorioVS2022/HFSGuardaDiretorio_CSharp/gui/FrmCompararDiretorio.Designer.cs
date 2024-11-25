/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 11/12/2014
 * Time: 11:44
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
namespace HFSGuardaDiretorio.gui
{
	partial class FrmCompararDiretorio
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FrmCompararDiretorio));
			this.panel1 = new System.Windows.Forms.Panel();
			this.pb = new System.Windows.Forms.ProgressBar();
			this.btnSalvarLog = new System.Windows.Forms.Button();
			this.btnCompararDiretorios = new System.Windows.Forms.Button();
			this.gpDiretorio1 = new System.Windows.Forms.GroupBox();
			this.tvDiretorio1 = new System.Windows.Forms.TreeView();
			this.imageList1 = new System.Windows.Forms.ImageList(this.components);
			this.cmbAba1 = new System.Windows.Forms.ComboBox();
			this.gpDiretorio2 = new System.Windows.Forms.GroupBox();
			this.tvDiretorio2 = new System.Windows.Forms.TreeView();
			this.cmbAba2 = new System.Windows.Forms.ComboBox();
			this.barraStatus = new System.Windows.Forms.StatusStrip();
			this.labStatus1 = new System.Windows.Forms.ToolStripStatusLabel();
			this.labStatus2 = new System.Windows.Forms.ToolStripStatusLabel();
			this.label1 = new System.Windows.Forms.Label();
			this.lvCompara = new System.Windows.Forms.ListView();
			this.columnHeader10 = new System.Windows.Forms.ColumnHeader();
			this.columnHeader11 = new System.Windows.Forms.ColumnHeader();
			this.columnHeader12 = new System.Windows.Forms.ColumnHeader();
			this.columnHeader13 = new System.Windows.Forms.ColumnHeader();
			this.columnHeader14 = new System.Windows.Forms.ColumnHeader();
			this.columnHeader15 = new System.Windows.Forms.ColumnHeader();
			this.panel1.SuspendLayout();
			this.gpDiretorio1.SuspendLayout();
			this.gpDiretorio2.SuspendLayout();
			this.barraStatus.SuspendLayout();
			this.SuspendLayout();
			// 
			// panel1
			// 
			this.panel1.Controls.Add(this.pb);
			this.panel1.Controls.Add(this.btnSalvarLog);
			this.panel1.Controls.Add(this.btnCompararDiretorios);
			this.panel1.Dock = System.Windows.Forms.DockStyle.Top;
			this.panel1.Location = new System.Drawing.Point(0, 0);
			this.panel1.Name = "panel1";
			this.panel1.Size = new System.Drawing.Size(687, 37);
			this.panel1.TabIndex = 0;
			// 
			// pb
			// 
			this.pb.Location = new System.Drawing.Point(136, 10);
			this.pb.Name = "pb";
			this.pb.Size = new System.Drawing.Size(446, 19);
			this.pb.Step = 1;
			this.pb.TabIndex = 2;
			// 
			// btnSalvarLog
			// 
			this.btnSalvarLog.Location = new System.Drawing.Point(588, 8);
			this.btnSalvarLog.Name = "btnSalvarLog";
			this.btnSalvarLog.Size = new System.Drawing.Size(87, 23);
			this.btnSalvarLog.TabIndex = 1;
			this.btnSalvarLog.Text = "&Salvar Log";
			this.btnSalvarLog.UseVisualStyleBackColor = true;
			this.btnSalvarLog.Click += new System.EventHandler(this.BtnSalvarLogClick);
			// 
			// btnCompararDiretorios
			// 
			this.btnCompararDiretorios.Location = new System.Drawing.Point(12, 8);
			this.btnCompararDiretorios.Name = "btnCompararDiretorios";
			this.btnCompararDiretorios.Size = new System.Drawing.Size(118, 23);
			this.btnCompararDiretorios.TabIndex = 0;
			this.btnCompararDiretorios.Text = "&Comparar Diretórios";
			this.btnCompararDiretorios.UseVisualStyleBackColor = true;
			this.btnCompararDiretorios.Click += new System.EventHandler(this.BtnCompararDiretoriosClick);
			// 
			// gpDiretorio1
			// 
			this.gpDiretorio1.Controls.Add(this.tvDiretorio1);
			this.gpDiretorio1.Controls.Add(this.cmbAba1);
			this.gpDiretorio1.Location = new System.Drawing.Point(12, 43);
			this.gpDiretorio1.Name = "gpDiretorio1";
			this.gpDiretorio1.Size = new System.Drawing.Size(329, 284);
			this.gpDiretorio1.TabIndex = 1;
			this.gpDiretorio1.TabStop = false;
			this.gpDiretorio1.Text = "Diretório 1";
			// 
			// tvDiretorio1
			// 
			this.tvDiretorio1.ImageIndex = 0;
			this.tvDiretorio1.ImageList = this.imageList1;
			this.tvDiretorio1.Location = new System.Drawing.Point(6, 46);
			this.tvDiretorio1.Name = "tvDiretorio1";
			this.tvDiretorio1.SelectedImageIndex = 0;
			this.tvDiretorio1.Size = new System.Drawing.Size(317, 232);
			this.tvDiretorio1.TabIndex = 1;
			// 
			// imageList1
			// 
			this.imageList1.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList1.ImageStream")));
			this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
			this.imageList1.Images.SetKeyName(0, "Fechar.bmp");
			this.imageList1.Images.SetKeyName(1, "Abrir.bmp");
			// 
			// cmbAba1
			// 
			this.cmbAba1.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.cmbAba1.FormattingEnabled = true;
			this.cmbAba1.Location = new System.Drawing.Point(6, 19);
			this.cmbAba1.Name = "cmbAba1";
			this.cmbAba1.Size = new System.Drawing.Size(317, 21);
			this.cmbAba1.TabIndex = 0;
			this.cmbAba1.SelectedIndexChanged += new System.EventHandler(this.CmbAba1SelectedIndexChanged);
			// 
			// gpDiretorio2
			// 
			this.gpDiretorio2.Controls.Add(this.tvDiretorio2);
			this.gpDiretorio2.Controls.Add(this.cmbAba2);
			this.gpDiretorio2.Location = new System.Drawing.Point(347, 43);
			this.gpDiretorio2.Name = "gpDiretorio2";
			this.gpDiretorio2.Size = new System.Drawing.Size(329, 284);
			this.gpDiretorio2.TabIndex = 2;
			this.gpDiretorio2.TabStop = false;
			this.gpDiretorio2.Text = "Diretório 2";
			// 
			// tvDiretorio2
			// 
			this.tvDiretorio2.ImageIndex = 0;
			this.tvDiretorio2.ImageList = this.imageList1;
			this.tvDiretorio2.Location = new System.Drawing.Point(6, 46);
			this.tvDiretorio2.Name = "tvDiretorio2";
			this.tvDiretorio2.SelectedImageIndex = 0;
			this.tvDiretorio2.Size = new System.Drawing.Size(317, 232);
			this.tvDiretorio2.TabIndex = 1;
			// 
			// cmbAba2
			// 
			this.cmbAba2.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.cmbAba2.FormattingEnabled = true;
			this.cmbAba2.Location = new System.Drawing.Point(6, 19);
			this.cmbAba2.Name = "cmbAba2";
			this.cmbAba2.Size = new System.Drawing.Size(317, 21);
			this.cmbAba2.TabIndex = 0;
			this.cmbAba2.SelectedIndexChanged += new System.EventHandler(this.CmbAba2SelectedIndexChanged);
			// 
			// barraStatus
			// 
			this.barraStatus.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
									this.labStatus1,
									this.labStatus2});
			this.barraStatus.Location = new System.Drawing.Point(0, 558);
			this.barraStatus.Name = "barraStatus";
			this.barraStatus.Size = new System.Drawing.Size(687, 22);
			this.barraStatus.TabIndex = 10;
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
			this.labStatus1.Text = "Total de diferenças encontradas:";
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
			this.labStatus2.Size = new System.Drawing.Size(472, 17);
			this.labStatus2.Spring = true;
			this.labStatus2.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(8, 330);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(138, 18);
			this.label1.TabIndex = 11;
			this.label1.Text = "Diferenças Encontradas";
			// 
			// lvCompara
			// 
			this.lvCompara.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
									this.columnHeader10,
									this.columnHeader11,
									this.columnHeader12,
									this.columnHeader13,
									this.columnHeader14,
									this.columnHeader15});
			this.lvCompara.FullRowSelect = true;
			this.lvCompara.GridLines = true;
			this.lvCompara.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable;
			this.lvCompara.Location = new System.Drawing.Point(0, 351);
			this.lvCompara.MultiSelect = false;
			this.lvCompara.Name = "lvCompara";
			this.lvCompara.Size = new System.Drawing.Size(687, 205);
			this.lvCompara.SmallImageList = this.imageList1;
			this.lvCompara.TabIndex = 12;
			this.lvCompara.UseCompatibleStateImageBehavior = false;
			this.lvCompara.View = System.Windows.Forms.View.Details;
			// 
			// columnHeader10
			// 
			this.columnHeader10.Text = "Nome";
			this.columnHeader10.Width = 300;
			// 
			// columnHeader11
			// 
			this.columnHeader11.Text = "Tamanho";
			this.columnHeader11.Width = 100;
			// 
			// columnHeader12
			// 
			this.columnHeader12.Text = "Tipo";
			this.columnHeader12.Width = 70;
			// 
			// columnHeader13
			// 
			this.columnHeader13.Text = "Modificado";
			this.columnHeader13.Width = 120;
			// 
			// columnHeader14
			// 
			this.columnHeader14.Text = "Atributos";
			this.columnHeader14.Width = 90;
			// 
			// columnHeader15
			// 
			this.columnHeader15.Text = "Caminho";
			this.columnHeader15.Width = 300;
			// 
			// FrmCompararDiretorio
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(687, 580);
			this.Controls.Add(this.lvCompara);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.barraStatus);
			this.Controls.Add(this.gpDiretorio2);
			this.Controls.Add(this.gpDiretorio1);
			this.Controls.Add(this.panel1);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "FrmCompararDiretorio";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "Comparar Diretórios";
			this.panel1.ResumeLayout(false);
			this.gpDiretorio1.ResumeLayout(false);
			this.gpDiretorio2.ResumeLayout(false);
			this.barraStatus.ResumeLayout(false);
			this.barraStatus.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();
		}
		private System.Windows.Forms.ColumnHeader columnHeader15;
		private System.Windows.Forms.ColumnHeader columnHeader14;
		private System.Windows.Forms.ColumnHeader columnHeader13;
		private System.Windows.Forms.ColumnHeader columnHeader12;
		private System.Windows.Forms.ColumnHeader columnHeader11;
		private System.Windows.Forms.ColumnHeader columnHeader10;
		private System.Windows.Forms.ListView lvCompara;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.ToolStripStatusLabel labStatus2;
		private System.Windows.Forms.ToolStripStatusLabel labStatus1;
		private System.Windows.Forms.StatusStrip barraStatus;
		private System.Windows.Forms.ImageList imageList1;
		private System.Windows.Forms.ComboBox cmbAba2;
		private System.Windows.Forms.TreeView tvDiretorio2;
		private System.Windows.Forms.GroupBox gpDiretorio2;
		private System.Windows.Forms.TreeView tvDiretorio1;
		private System.Windows.Forms.ComboBox cmbAba1;
		private System.Windows.Forms.GroupBox gpDiretorio1;
		public System.Windows.Forms.ProgressBar pb;
		private System.Windows.Forms.Button btnCompararDiretorios;
		private System.Windows.Forms.Button btnSalvarLog;
		private System.Windows.Forms.Panel panel1;
	}
}
