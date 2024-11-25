/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 10/12/2014
 * Time: 17:39
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.Windows.Forms;
using HFSGuardaDiretorio.gui;
using HFSGuardaDiretorio.catalogador;

namespace HFSGuardaDiretorio
{
	/// <summary>
	/// Class with program entry point.
	/// </summary>
	internal sealed class Program
	{
		/// <summary>
		/// Program entry point.
		/// </summary>
		[STAThread]
		private static void Main(string[] args)
		{			
			Catalogador.iniciarSistema();
			//Rotinas.iniciarLogArquivo(log);
		
			Application.EnableVisualStyles();
			Application.SetCompatibleTextRenderingDefault(false);
			Application.Run(new FrmPrincipal());			
		}
	}
}
