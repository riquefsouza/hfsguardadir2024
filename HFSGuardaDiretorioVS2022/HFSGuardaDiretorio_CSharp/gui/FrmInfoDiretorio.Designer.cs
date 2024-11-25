/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 11/12/2014
 * Time: 11:11
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
namespace HFSGuardaDiretorio.gui
{
	partial class FrmInfoDiretorio
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
			System.Windows.Forms.ListViewItem listViewItem1 = new System.Windows.Forms.ListViewItem("Aba:");
			System.Windows.Forms.ListViewItem listViewItem2 = new System.Windows.Forms.ListViewItem("Nome:");
			System.Windows.Forms.ListViewItem listViewItem3 = new System.Windows.Forms.ListViewItem("Tamanho:");
			System.Windows.Forms.ListViewItem listViewItem4 = new System.Windows.Forms.ListViewItem("Tipo:");
			System.Windows.Forms.ListViewItem listViewItem5 = new System.Windows.Forms.ListViewItem("Modificado:");
			System.Windows.Forms.ListViewItem listViewItem6 = new System.Windows.Forms.ListViewItem("Atributos:");
			System.Windows.Forms.ListViewItem listViewItem7 = new System.Windows.Forms.ListViewItem("Caminho:");
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.label5 = new System.Windows.Forms.Label();
			this.label6 = new System.Windows.Forms.Label();
			this.label3 = new System.Windows.Forms.Label();
			this.label4 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.label1 = new System.Windows.Forms.Label();
			this.lvInfo = new System.Windows.Forms.ListView();
			this.columnHeader1 = new System.Windows.Forms.ColumnHeader();
			this.columnHeader2 = new System.Windows.Forms.ColumnHeader();
			this.btnOk = new System.Windows.Forms.Button();
			this.groupBox1.SuspendLayout();
			this.SuspendLayout();
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.label5);
			this.groupBox1.Controls.Add(this.label6);
			this.groupBox1.Controls.Add(this.label3);
			this.groupBox1.Controls.Add(this.label4);
			this.groupBox1.Controls.Add(this.label2);
			this.groupBox1.Controls.Add(this.label1);
			this.groupBox1.Location = new System.Drawing.Point(12, 12);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(340, 96);
			this.groupBox1.TabIndex = 0;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Legenda dos Atributos";
			// 
			// label5
			// 
			this.label5.Location = new System.Drawing.Point(166, 62);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(168, 23);
			this.label5.TabIndex = 5;
			this.label5.Text = "[ROL] - Arquivo Somente Leitura";
			this.label5.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// label6
			// 
			this.label6.Location = new System.Drawing.Point(6, 62);
			this.label6.Name = "label6";
			this.label6.Size = new System.Drawing.Size(154, 23);
			this.label6.TabIndex = 4;
			this.label6.Text = "[SYS] - Arquivo de Sistema";
			this.label6.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// label3
			// 
			this.label3.Location = new System.Drawing.Point(166, 39);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(168, 23);
			this.label3.TabIndex = 3;
			this.label3.Text = "[VOL] - Volume ID";
			this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// label4
			// 
			this.label4.Location = new System.Drawing.Point(6, 39);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(154, 23);
			this.label4.TabIndex = 2;
			this.label4.Text = "[HID] - Arquivo Oculto";
			this.label4.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// label2
			// 
			this.label2.Location = new System.Drawing.Point(166, 16);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(168, 23);
			this.label2.TabIndex = 1;
			this.label2.Text = "[DIR] - Diretório";
			this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(6, 16);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(154, 23);
			this.label1.TabIndex = 0;
			this.label1.Text = "[ARQ] - Arquivo comum";
			this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// lvInfo
			// 
			this.lvInfo.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
									this.columnHeader1,
									this.columnHeader2});
			this.lvInfo.GridLines = true;
			this.lvInfo.Items.AddRange(new System.Windows.Forms.ListViewItem[] {
									listViewItem1,
									listViewItem2,
									listViewItem3,
									listViewItem4,
									listViewItem5,
									listViewItem6,
									listViewItem7});
			this.lvInfo.Location = new System.Drawing.Point(18, 114);
			this.lvInfo.MultiSelect = false;
			this.lvInfo.Name = "lvInfo";
			this.lvInfo.OwnerDraw = true;
			this.lvInfo.Size = new System.Drawing.Size(328, 181);
			this.lvInfo.TabIndex = 1;
			this.lvInfo.UseCompatibleStateImageBehavior = false;
			this.lvInfo.View = System.Windows.Forms.View.Details;
			this.lvInfo.DrawColumnHeader += new System.Windows.Forms.DrawListViewColumnHeaderEventHandler(this.LvInfoDrawColumnHeader);
			this.lvInfo.DrawItem += new System.Windows.Forms.DrawListViewItemEventHandler(this.LvInfoDrawItem);
			this.lvInfo.DrawSubItem += new System.Windows.Forms.DrawListViewSubItemEventHandler(this.LvInfoDrawSubItem);
			// 
			// columnHeader1
			// 
			this.columnHeader1.Text = "Item";
			this.columnHeader1.Width = 108;
			// 
			// columnHeader2
			// 
			this.columnHeader2.Text = "Descrição";
			this.columnHeader2.Width = 214;
			// 
			// btnOk
			// 
			this.btnOk.Location = new System.Drawing.Point(146, 309);
			this.btnOk.Name = "btnOk";
			this.btnOk.Size = new System.Drawing.Size(75, 23);
			this.btnOk.TabIndex = 2;
			this.btnOk.Text = "&Ok";
			this.btnOk.UseVisualStyleBackColor = true;
			this.btnOk.Click += new System.EventHandler(this.BtnOkClick);
			// 
			// FrmInfoDiretorio
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(363, 344);
			this.Controls.Add(this.btnOk);
			this.Controls.Add(this.lvInfo);
			this.Controls.Add(this.groupBox1);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "FrmInfoDiretorio";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Informações do Diretório / Arquivo";
			this.groupBox1.ResumeLayout(false);
			this.ResumeLayout(false);
		}
		private System.Windows.Forms.ColumnHeader columnHeader2;
		private System.Windows.Forms.ColumnHeader columnHeader1;
		private System.Windows.Forms.Button btnOk;
		private System.Windows.Forms.ListView lvInfo;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Label label6;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.GroupBox groupBox1;
	}
}
