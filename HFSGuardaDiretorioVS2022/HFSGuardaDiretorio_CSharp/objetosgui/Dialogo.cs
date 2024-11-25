/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 07/07/2015
 * Time: 14:01
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.Drawing;
using System.Windows.Forms;

namespace HFSGuardaDiretorio.objetosgui
{
	/// <summary>
	/// Description of Dialogo.
	/// </summary>
	public class Dialogo
	{
		public Dialogo()
		{
		}
		
		public static void mensagemErro(String texto) {
			MessageBox.Show(texto, "Erro", MessageBoxButtons.OK, MessageBoxIcon.Error);
		}
		
		public static void mensagemInfo(String texto) {
			MessageBox.Show(texto, "Informação", MessageBoxButtons.OK, MessageBoxIcon.Information);
		}
		
		public static bool confirma(String texto) {
			DialogResult res = MessageBox.Show(texto, "Confirma", MessageBoxButtons.YesNo, MessageBoxIcon.Question); 			
			return (res == DialogResult.Yes);			 
		}
		
		public static String entrada(String texto, String valorInicial) {
			Form form = new Form();
			Label label = new Label();
			TextBox textBox = new TextBox();
			Button buttonOk = new Button();
			Button buttonCancel = new Button();
			
			form.Text = "Informa";
			label.Text = texto;
			textBox.Text = valorInicial;
			textBox.MaxLength = 10;
			
			buttonOk.Text = "OK";
			buttonCancel.Text = "Cancel";
			buttonOk.DialogResult = DialogResult.OK;
			buttonCancel.DialogResult = DialogResult.Cancel;
			
			label.SetBounds(9, 20, 372, 13);
			textBox.SetBounds(12, 36, 372, 20);
			buttonOk.SetBounds(228, 72, 75, 23);
			buttonCancel.SetBounds(309, 72, 75, 23);
			
			label.AutoSize = true;
			textBox.Anchor = textBox.Anchor | AnchorStyles.Right;
			buttonOk.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
			buttonCancel.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
			
			form.ClientSize = new Size(396, 107);
			form.Controls.AddRange(new Control[] { label, textBox, buttonOk, buttonCancel });
			form.ClientSize = new Size(Math.Max(300, label.Right + 10), form.ClientSize.Height);
			form.FormBorderStyle = FormBorderStyle.FixedDialog;
			form.StartPosition = FormStartPosition.CenterScreen;
			form.MinimizeBox = false;
			form.MaximizeBox = false;
			form.AcceptButton = buttonOk;
			form.CancelButton = buttonCancel;
			
			DialogResult res = form.ShowDialog();
			
			if (res == DialogResult.OK)
				return textBox.Text;
			else
				return "";
		}
		
		public static String entrada(String texto) {
			return entrada(texto, "");
		}
		
	}
}
