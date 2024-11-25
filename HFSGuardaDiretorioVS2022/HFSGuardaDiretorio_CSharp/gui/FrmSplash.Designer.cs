/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 11/12/2014
 * Time: 10:52
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
namespace HFSGuardaDiretorio.gui
{
	partial class FrmSplash
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
			this.label1 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.pb = new System.Windows.Forms.ProgressBar();
			this.SuspendLayout();
			// 
			// label1
			// 
			this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 20F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label1.Location = new System.Drawing.Point(21, 9);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(332, 34);
			this.label1.TabIndex = 0;
			this.label1.Text = "HFSGuardaDiretorio 2.0";
			// 
			// label2
			// 
			this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label2.Location = new System.Drawing.Point(47, 53);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(267, 29);
			this.label2.TabIndex = 1;
			this.label2.Text = "Catalogador de Diretórios";
			// 
			// pb
			// 
			this.pb.Dock = System.Windows.Forms.DockStyle.Bottom;
			this.pb.Location = new System.Drawing.Point(0, 96);
			this.pb.Name = "pb";
			this.pb.Size = new System.Drawing.Size(375, 17);
			this.pb.Step = 1;
			this.pb.TabIndex = 2;
			// 
			// FrmSplash
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(375, 113);
			this.ControlBox = false;
			this.Controls.Add(this.pb);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.label1);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "FrmSplash";
			this.ShowIcon = false;
			this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "FrmSplash";
			this.ResumeLayout(false);
		}
		public System.Windows.Forms.ProgressBar pb;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label1;
	}
}
