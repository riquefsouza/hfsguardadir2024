/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 11/12/2014
 * Time: 10:59
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.Drawing;
using System.Windows.Forms;

namespace HFSGuardaDiretorio.gui
{
	/// <summary>
	/// Description of FrmSobre.
	/// </summary>
	public partial class FrmSobre : Form
	{
		public FrmSobre()
		{
			//
			// The InitializeComponent() call is required for Windows Forms designer support.
			//
			InitializeComponent();
			
			//
			// TODO: Add constructor code after the InitializeComponent() call.
			//
		}
		
		void BtnOkClick(object sender, EventArgs e)
		{
			this.Close();
		}
	}
}
